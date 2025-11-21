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
private:
	GLuint shader;
};
}
