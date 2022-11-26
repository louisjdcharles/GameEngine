#pragma once

#include <glad/glad.h>
#include <unordered_map>
#include <glm/glm.hpp>

class Shader
{
private:
	GLint Id = 0;
	std::string VertFilePath = "";
	std::string FragFilePath = "";
	std::unordered_map < std::string, GLint > UniformLocationCache;

public:
	Shader() = default;
	~Shader();

	void AddProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

	void Bind() const;
	void Unbind() const;

	void SetUniform1i(const std::string& name, int value);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniform1f(const std::string& name, float f);
	void SetUniformMat4f(const std::string& name, const glm::mat4& mat);
	void SetUniform1b(const std::string& name, const bool val);

private:
	GLint CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	GLint CompileShader(const std::string& src, GLenum type);
	GLint GetUniformLocation(const std::string& name);
};
