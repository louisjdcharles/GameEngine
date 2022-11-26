#include "Shader.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <iostream>
#include <assert.h>

std::string ReadFile(const std::string& path)
{
	std::ifstream stream(path);

	if (!stream.is_open())
	{
		std::cout << "Error opening file!\n";
		return "";
	}

	std::stringstream ss;

	std::string line;
	while (getline(stream, line))
	{
		ss << line << "\n";
	}

	return ss.str();
}

GLint Shader::CompileShader(const std::string& src, GLenum type)
{
	GLuint id = glCreateShader(type);
	const char* src_as_cstring = src.c_str();
	glShaderSource(id, 1, &src_as_cstring, nullptr);
	glCompileShader(id);

	GLint result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
	{
		int len;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);

		char* msg = (char*)alloca(len * sizeof(char));

		glGetShaderInfoLog(id, len, &len, msg);

		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << "\n";
		std::cout << msg << "\n";

		return 0;
	}

	return id;
}

GLint Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	GLint program = glCreateProgram();
	GLint vs = CompileShader(vertexShader, GL_VERTEX_SHADER);
	GLint fs = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);

	GLint result;
	glGetProgramiv(program, GL_LINK_STATUS, &result);

	if (result == GL_FALSE)
	{
		int len;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);

		char* msg = (char*)alloca(len * sizeof(char));

		glGetProgramInfoLog(program, len, &len, msg);

		std::cout << "Failed to link shader:" << std::endl;
		std::cout << msg << "\n";

		assert(false);
	}

	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

void Shader::AddProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
	VertFilePath = vertexShaderPath;
	FragFilePath = fragmentShaderPath;

	std::string vertShaderSrc = ReadFile(vertexShaderPath);
	std::string fragShaderSrc = ReadFile(fragmentShaderPath);

	Id = CreateShader(vertShaderSrc, fragShaderSrc);

	UniformLocationCache = std::unordered_map<std::string, GLint>();
}

Shader::~Shader()
{
	glDeleteProgram(Id);
}

void Shader::Bind() const
{
	glUseProgram(Id);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

void Shader::SetUniform1i(const std::string& name, int value)
{
	glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniform1f(const std::string& name, float f)
{
	glUniform1f(GetUniformLocation(name), f);
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& mat)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}

GLint Shader::GetUniformLocation(const std::string& name)
{
	if (UniformLocationCache.find(name) != UniformLocationCache.end())
		return UniformLocationCache[name];

	GLint location = glGetUniformLocation(Id, name.c_str());

	UniformLocationCache[name] = location;

	return location;
}