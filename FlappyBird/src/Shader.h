#pragma once

#include <string>
#include <GL/glew.h>

class Shader
{
public:
	Shader(const std::string& path_vertex_shader, const std::string& path_fragment_shader);
	~Shader();

	GLuint GetRendererID() const { return m_RendererID; }

private:
	GLuint m_RendererID;

	GLuint CompileShader(const std::string& filepath, GLenum shader_type);
};

