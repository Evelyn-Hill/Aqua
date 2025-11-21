#pragma once
#include <string>
#include <glad/glad.h>
#include <Aqua/Core/Types.hpp>

namespace Aqua {
class Shader {
public:
	Shader(std::string vertexPath, std::string fragmentPath);
	~Shader();
	
	bool CompileShader(GLuint shader);
	bool CompileProgram(GLuint vertexShader, GLuint fragmentShader);

	void Use();

	void SetMat4(std::string name, mat4 value);
	void SetVec3f(std::string name, vec3 value);
	void SetVec4f(std::string name, vec4 value);
	void SetInt(std::string name, int value);
	void SetFloat(std::string name, float value);
	void SetVec2f(std::string name, vec2 value);
private:
	GLuint shader;
};
}
