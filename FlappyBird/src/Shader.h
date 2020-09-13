#pragma once

#include <string>
#include <map>

#include <GL/glew.h>

#include "Error.h"

class Shader
{
public:
	Shader(const std::string& path_vertex_shader, const std::string& path_fragment_shader);
	~Shader();
	void Bind() { GLCall(glUseProgram(m_RendererID)); }
	void Unbind() { GLCall(glUseProgram(0)); }
	GLuint GetRendererID() const { return m_RendererID; }
	GLint GetUniformLocation(const std::string& name);

private:
	GLuint m_RendererID;
	std::map<std::string, GLint> m_LocationCache;

	GLuint CompileShader(const std::string& filepath, GLenum shader_type);
};

