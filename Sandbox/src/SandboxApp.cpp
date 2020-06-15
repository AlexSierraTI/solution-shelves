#include <SolutionShelves.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "ImGui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public SolutionShelves::Layer
{
public:
	ExampleLayer()
		: Layer("Teste Layer"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
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

		m_Shader = SolutionShelves::Shader::Create(vertexSrc, fragmentSrc);


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

		m_FlatColorShader = SolutionShelves::OpenGLShader::Create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc);

		std::string textureShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TextCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec2 v_TextCoord;

			void main()
			{
				v_TextCoord = a_TextCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";
		std::string textureShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			
			in vec2 v_TextCoord;

			uniform sampler2D u_Texture;

			void main()
			{
				color = texture(u_Texture, v_TextCoord);
			}
		)";

		m_TextureShader = SolutionShelves::OpenGLShader::Create(textureShaderVertexSrc, textureShaderFragmentSrc);

		m_Texture = SolutionShelves::Texture2D::Create("assets/textures/luana.png");

		std::dynamic_pointer_cast<SolutionShelves::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<SolutionShelves::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
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
		
		std::dynamic_pointer_cast<SolutionShelves::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<SolutionShelves::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				SolutionShelves::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		m_Texture->Bind(0);
		SolutionShelves::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		
		// Triangulo
		// SolutionShelves::Renderer::Submit(m_Shader, m_VertexArray);

		SolutionShelves::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Teste Cores");
		ImGui::ColorEdit3("Cor dos Quadrados", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(SolutionShelves::Event& event) override
	{

	}

private:
	SolutionShelves::Ref<SolutionShelves::Shader> m_Shader;
	SolutionShelves::Ref<SolutionShelves::VertexArray> m_VertexArray;

	SolutionShelves::Ref<SolutionShelves::Shader> m_FlatColorShader, m_TextureShader;
	SolutionShelves::Ref<SolutionShelves::VertexArray> m_SquareVA;

	SolutionShelves::Ref<SolutionShelves::Texture2D> m_Texture;

	SolutionShelves::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 1.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 50.0f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };

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