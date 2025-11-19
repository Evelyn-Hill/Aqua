#pragma once
#include <string>
#include <glad/glad.h>

namespace Aqua {
class Shader {
public:
	Shader(std::string vertexPath, std::string fragmentPath);
	~Shader();
	
	bool CompileShader(GLuint shader);
	bool CompileProgram(GLuint vertexShader, GLuint fragmentShader);

	void Use();
private:
	GLuint shader;

};
}
