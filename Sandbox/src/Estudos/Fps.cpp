#include "Fps.h"
using namespace std;

float fPlayerX = 8.0f;
float fPlayerY = 8.0f;
float fPlayerA = 0.0f;

int nMapHeight = 16;
int nMapWidth = 16;

wstring map;

float fFOV = glm::radians(45.0f);
float fDepth = 16.0f;

float moveSpeed = 5.0f;
float moveDelta = 0.0f;

float rotateSpeed = 1.4f;
float turnDelta = 0.0f;

Fps::Fps(uint32_t width, uint32_t height, uint32_t pixelSize)
	: PixelEngineWrapper(width, height, pixelSize)
{
	map += L"################";
	map += L"#              #";
	map += L"#  ##########  #";
	map += L"#         #    #";
	map += L"#         ###  #";
	map += L"#              #";
	map += L"#####      #####";
	map += L"#  #           #";
	map += L"#  #       #####";
	map += L"#              #";
	map += L"#              #";
	map += L"#              #";
	map += L"#       ########";
	map += L"#   #          #";
	map += L"#   #          #";
	map += L"################";

}

void Fps::OnUpdate(SolutionShelves::Timestep ts)
{
	turnDelta = rotateSpeed * ts;
	moveDelta = moveSpeed * ts;

	int playerCurrentPos = (int)fPlayerY * nMapWidth + (int)fPlayerX;

	if (SolutionShelves::Input::IsKeyPressed(SolutionShelves::Key::A))
		fPlayerA -= turnDelta;

	if (SolutionShelves::Input::IsKeyPressed(SolutionShelves::Key::D))
		fPlayerA += turnDelta;

	if (SolutionShelves::Input::IsKeyPressed(SolutionShelves::Key::W))
	{
		fPlayerX += glm::sin(fPlayerA) * moveDelta;
		fPlayerY += glm::cos(fPlayerA) * moveDelta;

		if (map[playerCurrentPos] == '#')
		{
			fPlayerX -= glm::sin(fPlayerA) * moveDelta;
			fPlayerY -= glm::cos(fPlayerA) * moveDelta;
		}

	}

	if (SolutionShelves::Input::IsKeyPressed(SolutionShelves::Key::S))
	{
		fPlayerX -= glm::sin(fPlayerA) * moveDelta;
		fPlayerY -= glm::cos(fPlayerA) * moveDelta;
		
		if (map[playerCurrentPos] == '#')
		{
			fPlayerX += glm::sin(fPlayerA) * moveDelta;
			fPlayerY += glm::cos(fPlayerA) * moveDelta;
		}
	}

	for (uint32_t x = 0; x < Fps::ScreenWidth(); x++)
	{
		float fRayAngle = (fPlayerA - fFOV / 2.0f) + ((float)x / (float)Fps::ScreenWidth()) * fFOV;

		float fDistanceToWall = 0;
		bool bHitWall = false;
		bool bBoundary = false;

		glm::vec2 fEye = { glm::sin(fRayAngle), glm::cos(fRayAngle) };

		while (!bHitWall && fDistanceToWall < fDepth)
		{
			fDistanceToWall += 0.1f;

			int nTestX = (int)(fPlayerX + fEye.x * fDistanceToWall);
			int nTestY = (int)(fPlayerY + fEye.y * fDistanceToWall);

			if (nTestX < 0 || nTestX >= nMapWidth || nTestY < 0 || nTestY >= nMapHeight)
			{
				bHitWall = true;
				fDistanceToWall = fDepth;
			}
			else
			{
				uint64_t index = ((uint64_t)nTestY * (uint64_t)nMapWidth + (uint64_t)nTestX) % map.length();
				bHitWall = map[index] == '#';
			}
			if (bHitWall) 
			{
				vector<pair<float, float>> p; 
				for (int tx = 0; tx < 2; tx++)
					for (int ty = 0; ty < 2; ty++)
					{
						float vy = (float)nTestY + ty - fPlayerY;
						float vx = (float)nTestX + tx - fPlayerX;
						float d = sqrt(vx*vx + vy*vy);
						float dot = (fEye.x * vx /d) + (fEye.y * vy / d);
						p.push_back(make_pair(d, dot));
					}

				sort(p.begin(), p.end(), [](const pair<float, float>& left, const pair<float, float>& right) { return left.first < right.first; });

				float fBound = 0.01f;
				if (glm::acos(p.at(0).second) < fBound) bBoundary = true;
				if (glm::acos(p.at(1).second) < fBound) bBoundary = true;
				// if (glm::acos(p.at(3).second) < fBound) bBoundary = true;
			}
		}

		double nCeiling = glm::floor((Fps::ScreenHeight() / 2.0) - Fps::ScreenHeight() / fDistanceToWall);
		double nFloor = Fps::ScreenHeight() - nCeiling;

		glm::vec4 nShade = { 0.5f, 0.0f, 0.1f, 1.0f };

		if (fDistanceToWall <= fDepth / 10.0f)		nShade = { 1.0f, 0.0f, 0.1f, 1.0f }; // Perto
		else if (fDistanceToWall < fDepth / 9.0f)	nShade = { 0.9f, 0.0f, 0.1f, 1.0f };
		else if (fDistanceToWall < fDepth / 8.0f)	nShade = { 0.8f, 0.0f, 0.1f, 1.0f };
		else if (fDistanceToWall < fDepth / 7.0f)	nShade = { 0.7f, 0.0f, 0.1f, 1.0f };
		else if (fDistanceToWall < fDepth / 6.0f)	nShade = { 0.6f, 0.0f, 0.1f, 1.0f };
		else if (fDistanceToWall < fDepth / 5.0f)	nShade = { 0.5f, 0.0f, 0.1f, 1.0f };
		else if (fDistanceToWall < fDepth / 4.0f)	nShade = { 0.4f, 0.0f, 0.1f, 1.0f };
		else if (fDistanceToWall < fDepth / 3.0f)	nShade = { 0.3f, 0.0f, 0.1f, 1.0f };
		else if (fDistanceToWall < fDepth / 2.0f)	nShade = { 0.2f, 0.0f, 0.1f, 1.0f };
		else if (fDistanceToWall < fDepth )			nShade = { 0.1f, 0.0f, 0.1f, 1.0f };
		else										nShade = { 0.0f, 0.0f, 0.1f, 1.0f }; //Longe

		if (bBoundary) nShade = { 0.0f, 0.0f, 0.0f, 0.8f }; // Perto


		for (uint32_t y = 0; y < Fps::ScreenHeight(); y++)
		{
			if (y < nCeiling)
				Fps::DrawPixel(x, y, { 0.2f, 0.3f, 0.8f, 1.0f });
			else if (y > nCeiling && y <= nFloor)
				Fps::DrawPixel(x, y, nShade);
			else
			{
				glm::vec4 nShadeFloor;
				float b = 1.0f - (((float)y - Fps::ScreenHeight() / 2.0f) / ((float)Fps::ScreenHeight() / 2.0f));
				if ( b < 0.25)		  nShadeFloor = { 1.0f, 1.0f, 1.0f, 1.0f };
				else if (b < 0.5)	  nShadeFloor = { 0.8f, 0.8f, 0.8f, 1.0f };
				else if (b < 0.75)	  nShadeFloor = { 0.6f, 0.6f, 0.6f, 1.0f };
				else if (b < 0.9)	  nShadeFloor = { 0.4f, 0.4f, 0.4f, 1.0f };
				else 				  nShadeFloor = { 0.2f, 0.2f, 0.2f, 1.0f };

				Fps::DrawPixel(x, y, nShadeFloor);
			}
		}


	}
}

void Fps::OnEvent(SolutionShelves::Event& event)
{

}

