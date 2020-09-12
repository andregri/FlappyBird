#include "Shader.h"

#include <iostream>
#include <string>
#include <fstream>
#include <memory>


Shader::Shader(const std::string & path_vertex_shader, const std::string & path_fragment_shader)
{
	// TODO: check if compilation went good
	GLuint vertex_shader = CompileShader(path_vertex_shader, GL_VERTEX_SHADER);
	GLuint fragment_shader = CompileShader(path_fragment_shader, GL_FRAGMENT_SHADER);

	m_RendererID = glCreateProgram();
	glAttachShader(m_RendererID, vertex_shader);
	glAttachShader(m_RendererID, fragment_shader);
	glLinkProgram(m_RendererID);
	glValidateProgram(m_RendererID);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
}

Shader::~Shader()
{
	glDeleteProgram(m_RendererID);
}

GLuint Shader::CompileShader(const std::string& filepath, GLenum shader_type)
{
	std::ifstream shader_file(filepath);
	std::string shader_source = "";

	for (std::string line; std::getline(shader_file, line);)
	{
		shader_source += line + '\n';
	}

	GLuint shader = glCreateShader(shader_type);
	const char *shader_source_cstr = shader_source.c_str();
	glShaderSource(shader, 1, &shader_source_cstr, NULL);
	glCompileShader(shader);

	GLint vertex_compiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &vertex_compiled);
	if (vertex_compiled == GL_FALSE)
	{
		GLsizei log_length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);
		std::unique_ptr<GLchar[]> log_buffer = std::make_unique<GLchar[]>(log_length);
		glGetShaderInfoLog(shader, 1024, &log_length, log_buffer.get());

		std::cerr << "Failed to compile the "
			<< (shader_type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT")
			<< " shader: " << log_buffer << '\n';

		glDeleteShader(shader);

		return 0;
	}

	return shader;
}
