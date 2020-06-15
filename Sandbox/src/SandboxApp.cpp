#include <SolutionShelves.h>

#include "ImGui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public SolutionShelves::Layer
{
public:
	ExampleLayer()
		: Layer("Teste Layer"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(SolutionShelves::VertexArray::Create());

		float vertices[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<SolutionShelves::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(SolutionShelves::VertexBuffer::Create(vertices, sizeof(vertices)));
		SolutionShelves::BufferLayout layout = {
			{ SolutionShelves::ShaderDataType::Float3, "a_Position" },
			{ SolutionShelves::ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<SolutionShelves::IndexBuffer> indexBuffer;
		indexBuffer.reset(SolutionShelves::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(SolutionShelves::VertexArray::Create());

		float squareVertices[3 * 4] =
		{
			-0.5f, -0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f
		};

		std::shared_ptr<SolutionShelves::VertexBuffer> squareVB;
		squareVB.reset(SolutionShelves::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ SolutionShelves::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<SolutionShelves::IndexBuffer> squareIB;
		squareIB.reset(SolutionShelves::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
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

		m_Shader.reset(new SolutionShelves::Shader(vertexSrc, fragmentSrc));


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

			uniform vec4 u_Color;

			void main()
			{
				color = u_Color;
			}
		)";

		m_FlatColorShader.reset(new SolutionShelves::Shader(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));

	}

	void OnUpdate(SolutionShelves::Timestep ts) override
	{
		// Movendo camêra
		if (SolutionShelves::Input::IsKeyPressed(SS_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (SolutionShelves::Input::IsKeyPressed(SS_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (SolutionShelves::Input::IsKeyPressed(SS_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (SolutionShelves::Input::IsKeyPressed(SS_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		// Rotação camêra
		if (SolutionShelves::Input::IsKeyPressed(SS_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		else if (SolutionShelves::Input::IsKeyPressed(SS_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;


		SolutionShelves::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		SolutionShelves::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		SolutionShelves::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		
		glm::vec4 redColor(0.8f, 0.2f, 0.3f, 1.0f);
		glm::vec4 blueColor(0.2f, 0.3f, 0.8f, 1.0f);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				if (x % 2 == 0)
					m_FlatColorShader->UploadUniformFloat4("u_Color", redColor);
				else
					m_FlatColorShader->UploadUniformFloat4("u_Color", blueColor);

				SolutionShelves::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}
		
		SolutionShelves::Renderer::Submit(m_Shader, m_VertexArray);

		SolutionShelves::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{

	}

	void OnEvent(SolutionShelves::Event& event) override
	{

	}

private:
	std::shared_ptr<SolutionShelves::Shader> m_Shader;
	std::shared_ptr<SolutionShelves::VertexArray> m_VertexArray;

	std::shared_ptr<SolutionShelves::Shader> m_FlatColorShader;
	std::shared_ptr<SolutionShelves::VertexArray> m_SquareVA;

	SolutionShelves::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 1.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 50.0f;

};

class SandBox : public SolutionShelves::Application
{
public:
	SandBox()
	{
		PushLayer(new ExampleLayer());
	}

	~SandBox()
	{

	}
};

SolutionShelves::Application* SolutionShelves::CreateApplication()
{
	return new SandBox();
}