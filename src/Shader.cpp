#include <Aqua/Core/Shader.hpp>
#include <Aqua/Core/Log.hpp>

#include <fstream>
#include <sstream>

Aqua::Shader::Shader(std::string vertexPath, std::string fragmentPath) {
	std::ifstream vertexFile(vertexPath);
	std::ifstream fragmentFile(fragmentPath);

	std::string vertexCode;
	std::string fragmentCode;
	
	if (!vertexFile) {
		Aqua::Log::AquaLog()->Error("SHDRERR: Could not load vertex shader at: ", vertexPath);
		return;
	}

	if (!fragmentFile) {
		Aqua::Log::AquaLog()->Error("SHDRERR: Could not load fragment shader at: ", fragmentPath);
		return;
	}

	std::ostringstream vertexStream, fragmentStream;
	vertexStream   << vertexFile.rdbuf();
	fragmentStream << fragmentFile.rdbuf();

	vertexCode   = vertexStream.str();
	fragmentCode = fragmentStream.str();

	if (vertexCode.empty()) {
		Aqua::Log::AquaLog()->Error("SHDRERR: Could not read vertex shader!");
		return;
	}

	if (fragmentCode.empty()) {
		Aqua::Log::AquaLog()->Error("SHDRERR: Could not read fragment shader!");
		return;
	}
	GLuint vertex   = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

	if (!vertex) {
		Aqua::Log::AquaLog()->Error("SHDRERR: Could not create vertex shader!");
		return;
	}

	if (!fragment) {
		Aqua::Log::AquaLog()->Error("SHDRERR: Could not create fragment shader!");
		return;
	}

	const char* vertexCodeCStr   = vertexCode.c_str();
	const char* fragmentCodeCStr = fragmentCode.c_str();

	glShaderSource(vertex, 1, &vertexCodeCStr, NULL);
	glShaderSource(fragment, 1, &fragmentCodeCStr, NULL);

	if (!CompileShader(vertex)) { 
		glDeleteShader(fragment);
		glDeleteShader(vertex);
		return; 
	}

	if (!CompileShader(fragment)) { 
		glDeleteShader(fragment);
		glDeleteShader(vertex);
		return; 
	}

	if (!CompileProgram(vertex, fragment)) { 
		glDeleteShader(fragment);
		glDeleteShader(vertex);
		return; 
	}

	
	
	Aqua::Log::AquaLog()->Info("Successfully compiled shader ", shader);
}

Aqua::Shader::~Shader() {}


void Aqua::Shader::SetMat4(std::string name, mat4 value) {
	int location = glGetUniformLocation(shader, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
}

void Aqua::Shader::SetVec3f(std::string name, vec3 value) {
	int location = glGetUniformLocation(shader, name.c_str());
	if (location == -1) {
		Aqua::Log::AquaLog()->Error("Could not find Uniform Vec3: ", name);
	}
	glUniform3f(location, value.x, value.y, value.z);
}

void Aqua::Shader::SetVec4f(std::string name, vec4 value) {
	int location = glGetUniformLocation(shader, name.c_str());
	if (location == -1) {
		Aqua::Log::AquaLog()->Error("Could not find Uniform Vec3: ", name);
	}

	glUniform4f(location, value.x, value.y, value.z, value.w);
}

void Aqua::Shader::SetInt(std::string name, int value) {
	int location = glGetUniformLocation(shader, name.c_str());
	glUniform1i(location, value);
}

void Aqua::Shader::SetFloat(std::string name, float value) {
	int location = glGetUniformLocation(shader, name.c_str());
	glUniform1f(location, value);
}


void Aqua::Shader::SetVec2f(std::string name, vec2 value) {
	int location = glGetUniformLocation(shader, name.c_str());
	if (location == -1) {
		Aqua::Log::AquaLog()->Error("Could not find Uniform Vec2: ", name);
	}

	glUniform2f(location, value.x, value.y);
}

bool Aqua::Shader::CompileShader(GLuint shader) {
	const int LOG_SIZE = 512;
	int success;
	char infoLog[LOG_SIZE];
	glCompileShader(shader);
	
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(shader, LOG_SIZE, NULL, infoLog);
		Aqua::Log::AquaLog()->Error("SHDRERR: Could not compile shader! \n", infoLog);
		return false;
	}

	return true;

}

bool Aqua::Shader::CompileProgram(GLuint vertexShader, GLuint fragmentShader) {
	const int LOG_SIZE = 512;
	int success;
	char infoLog[LOG_SIZE];
	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(program, LOG_SIZE, NULL, infoLog);
		Aqua::Log::AquaLog()->Error("SHDRERR: Could not link shader program! \n", infoLog);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		return false;
	}
	
	shader = program;
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return true;
}

void Aqua::Shader::Use() {
	if (shader == -1) {
		Aqua::Log::AquaLog()->Error("Could not use shader: ", shader);
		return;
	}

	glUseProgram(shader);
}
