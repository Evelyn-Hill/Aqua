#pragma once
#include <Aqua/Core/Texture.hpp>
#include <Aqua/Core/Types.hpp>
#include <glad/glad.h>
#include <Aqua/Core/Shader.hpp>
#include <Aqua/Core/Color.hpp>

namespace Aqua {
class Renderer {
public:
	Renderer();
	~Renderer();

	void DrawSprite(Texture* texture, vec2 pos, vec2 scale, float rotation, vec3 color);
	void ClearColor(Color color);
	void SetShader(Shader* shader);
private:
	Shader* shader = nullptr;
	GLuint quadVAO;
	Color clearColor;

};
}
