#include "Sandbox2D.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include "ImGui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{
}

void Sandbox2D::OnAttach()
{
	m_SquareVA = SolutionShelves::VertexArray::Create();

	float squareVertices[3 * 4] =
	{
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	SolutionShelves::Ref<SolutionShelves::VertexBuffer> squareVB;
	squareVB = SolutionShelves::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
	squareVB->SetLayout({
		{ SolutionShelves::ShaderDataType::Float3, "a_Position" }
		});
	m_SquareVA->AddVertexBuffer(squareVB);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	SolutionShelves::Ref<SolutionShelves::IndexBuffer> squareIB;
	squareIB = SolutionShelves::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
	m_SquareVA->SetIndexBuffer(squareIB);

	m_FlatColorShader = SolutionShelves::Shader::Create("assets/shaders/FlatColor.glsl");

}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(SolutionShelves::Timestep ts)
{
	// Update
	m_CameraController.OnUpdate(ts);


	// Render
	SolutionShelves::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	SolutionShelves::RenderCommand::Clear();

	SolutionShelves::Renderer::BeginScene(m_CameraController.GetCamera());

	std::dynamic_pointer_cast<SolutionShelves::OpenGLShader>(m_FlatColorShader)->Bind();
	std::dynamic_pointer_cast<SolutionShelves::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

	SolutionShelves::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	SolutionShelves::Renderer::EndScene();

}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Cor sb2d");
	ImGui::ColorEdit4("Cor", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(SolutionShelves::Event& e)
{
	m_CameraController.OnEvent(e);
}
