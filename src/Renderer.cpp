#include "Aqua/Core/Texture.hpp"
#include <Aqua/Core/Log.hpp>
#include <Aqua/Core/Renderer.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>

Aqua::Renderer::Renderer() {}

void Aqua::Renderer::InitRenderData(Shader *shader) {
  GLuint vbo;

  const int VTX_STRIDE = 4;
  float verticies[] = {
      // pos(NDC)
      0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
      0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
  };

  glGenVertexArrays(1, &this->quadVAO);
  glGenBuffers(1, &vbo);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

  glBindVertexArray(this->quadVAO);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, VTX_STRIDE, GL_FLOAT, GL_FALSE,
                        VTX_STRIDE * sizeof(GLfloat), (void *)0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // TODO: Make this variable to account for screen size.
  mat4 projection = glm::ortho(0.0f, 1176.0f, 768.0f, 0.0f, -1.0f, 1.0f);

  SetShader(shader);

  shader->Use();
  shader->SetInt("image", 0);
  shader->SetMat4("projection", projection);
}

Aqua::Renderer::~Renderer() {}

void Aqua::Renderer::SetShader(Shader *shader) { this->shader = shader; }

void Aqua::Renderer::DrawSprite(Texture *texture, vec2 pos, vec2 scale,
                                float rotation, vec3 color) {
  if (shader == nullptr) {
    Aqua::Log::AquaLog()->Error("No shader set!");
    return;
  }

  this->shader->Use();

  mat4 model = mat4(1.0);

  vec2 scalePostSegment = scale / texture->GetSegments();

  model = glm::translate(model, vec3(pos, 0.0f));
  model = glm::translate(
      model, vec3(0.5f * scalePostSegment.x, 0.5 * scalePostSegment.y, 0.0f));
  model = glm::rotate(model, glm::radians(rotation), glm::vec3(0, 0, 1));

  // NOTE: This recenters the position around top left, I think we want this
  // to be modular via an offset so we can have the sprite moved against the
  // parent object? Depends on how I setup entities.. - EPH
  model = glm::translate(
      model, vec3(-0.5f * scalePostSegment.x, -0.5 * scalePostSegment.y, 0.0f));

  model = glm::scale(model, glm::vec3(scalePostSegment, 0));

  this->shader->SetMat4("model", model);
  this->shader->SetVec4f("spriteColor", vec4(color, 1.0f));

	/* Sprite sheet animation stuff. */
  this->shader->SetInt("segmentIndex", texture->GetActiveSprite());
  this->shader->SetVec2f("segmentCount", texture->GetSegments());

  glBindVertexArray(this->quadVAO);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);
}
