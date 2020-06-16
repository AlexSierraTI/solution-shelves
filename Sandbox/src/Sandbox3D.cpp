#include "Sandbox3D.h"

#include "ImGui/imgui.h"

#include <glm/gtc/type_ptr.hpp>

Sandbox3D::Sandbox3D()
	: Layer("Teste Layer"), m_CameraController(1280.0f / 720.0f, true)
{
}

void Sandbox3D::OnAttach()
{
	m_VertexArray = SolutionShelves::VertexArray::Create();

	float vertices[3 * 7] =
	{
		-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
		 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
		 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
	};

	SolutionShelves::Ref<SolutionShelves::VertexBuffer> vertexBuffer;
	vertexBuffer = SolutionShelves::VertexBuffer::Create(vertices, sizeof(vertices));
	SolutionShelves::BufferLayout layout = {
		{ SolutionShelves::ShaderDataType::Float3, "a_Position" },
		{ SolutionShelves::ShaderDataType::Float4, "a_Color" }
	};

	vertexBuffer->SetLayout(layout);
	m_VertexArray->AddVertexBuffer(vertexBuffer);

	uint32_t indices[3] = { 0, 1, 2 };
	SolutionShelves::Ref<SolutionShelves::IndexBuffer> indexBuffer;
	indexBuffer = SolutionShelves::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
	m_VertexArray->SetIndexBuffer(indexBuffer);

	m_SquareVA = SolutionShelves::VertexArray::Create();

	float squareVertices[5 * 4] =
	{
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
	};

	SolutionShelves::Ref<SolutionShelves::VertexBuffer> squareVB;
	squareVB = SolutionShelves::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
	squareVB->SetLayout({
		{ SolutionShelves::ShaderDataType::Float3, "a_Position" },
		{ SolutionShelves::ShaderDataType::Float2, "a_TextCoord" }
		});
	m_SquareVA->AddVertexBuffer(squareVB);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	SolutionShelves::Ref<SolutionShelves::IndexBuffer> squareIB;
	squareIB = SolutionShelves::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
	m_SquareVA->SetIndexBuffer(squareIB);

	std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;			

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";
	std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

	m_Shader = SolutionShelves::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

	std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";
	std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			
			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

	m_FlatColorShader = SolutionShelves::Shader::Create("FlatColot", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);
	auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

	m_Texture = SolutionShelves::Texture2D::Create("assets/textures/Checkerboard.png");
	m_LuanaTexture = SolutionShelves::Texture2D::Create("assets/textures/luana.png");

	textureShader->Bind();
	textureShader->SetFloat4("u_Color", glm::vec4(1.0f));
	textureShader->SetInt("u_Texture", 0);
}

void Sandbox3D::OnDetach()
{
}

void Sandbox3D::OnUpdate(SolutionShelves::Timestep ts)
{
	// Update
	m_CameraController.OnUpdate(ts);


	// Render
	SolutionShelves::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	SolutionShelves::RenderCommand::Clear();

	SolutionShelves::Renderer::BeginScene(m_CameraController.GetCamera());

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

	/////
	m_FlatColorShader->Bind();
	m_FlatColorShader->SetFloat3("u_Color", m_SquareColor);

	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 20; x++)
		{
			glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
			SolutionShelves::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
		}
	}
	/////

	/////
	auto textureShader = m_ShaderLibrary.Get("Texture");

	m_Texture->Bind(0);
	SolutionShelves::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	m_LuanaTexture->Bind(0);
	SolutionShelves::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
	/////

	// Triangulo
	// SolutionShelves::Renderer::Submit(m_Shader, m_VertexArray);
	/////

	SolutionShelves::Renderer::EndScene();
}

void Sandbox3D::OnImGuiRender()
{
	ImGui::Begin("Cor sb");
	ImGui::ColorEdit3("Cor", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox3D::OnEvent(SolutionShelves::Event& e)
{
	m_CameraController.OnEvent(e);
}
