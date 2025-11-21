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
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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

	vec2 scalePostSegment = scale / texture->GetSegments();

	model = glm::translate(model, vec3(pos, 0.0f));
	model = glm::translate(model, vec3(0.5f * scalePostSegment.x, 0.5 * scalePostSegment.y, 0.0f));
	model = glm::rotate(model, glm::radians(rotation), glm::vec3(0, 0, 1));
	model = glm::translate(model, vec3(-0.5f * scalePostSegment.x, -0.5 * scalePostSegment.y, 0.0f));

	model = glm::scale(model, glm::vec3(scalePostSegment, 0));

    this->shader->SetMat4("model", model);
    this->shader->SetVec4f("spriteColor", vec4(color, 1.0f));
	//OPTIM: This doesnt need called every frame.
    this->shader->SetVec2f("texCoordDivisor", texture->GetSegments());
	this->shader->SetInt("activeCell", 4);
	
	glActiveTexture(GL_TEXTURE0);
	texture->Bind();

	glBindVertexArray(this->quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}
