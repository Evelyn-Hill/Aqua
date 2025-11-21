#include "Aqua/Core/Texture.hpp"
#include <Aqua/Core/Render.hpp>
#include <Aqua/Core/Log.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

Aqua::Renderer::Renderer() {
	GLuint vbo;
	float verticies[] = {
		// pos      tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &this->quadVAO);
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

	glBindVertexArray(this->quadVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Aqua::Renderer::~Renderer() {}

void Aqua::Renderer::SetShader(Shader* shader) {
	this->shader = shader;
}

void Aqua::Renderer::DrawSprite(Texture* texture, vec2 pos, vec2 scale, float rotation, vec3 color) {
	if (shader == nullptr) {
		Aqua::Log::AquaLog()->Error("No shader set!");
		return;
	}

	this->shader->Use();

	mat4 model = mat4(1.0);

	model = glm::translate(model, vec3(pos, 0.0f));
	model = glm::translate(model, vec3(0.5f * scale.x, 0.5 * scale.y, 0.0f));
	model = glm::rotate(model, glm::radians(rotation), glm::vec3(0, 0, 1));
	model = glm::translate(model, vec3(-0.5f * scale.x, -0.5 * scale.y, 0.0f));

	model = glm::scale(model, glm::vec3(scale, 0));

    this->shader->SetMat4("model", model);
    this->shader->SetVec3f("spriteColor", color);
	
	glActiveTexture(GL_TEXTURE0);
	texture->Bind();

	glBindVertexArray(this->quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}
