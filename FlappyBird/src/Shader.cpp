#include "Shader.h"

#include "Error.h"

#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>
#include <memory>


Shader::Shader(const std::string & path_vertex_shader, const std::string & path_fragment_shader)
{
	// TODO: check if compilation went good
	GLuint vertex_shader = CompileShader(path_vertex_shader, GL_VERTEX_SHADER);
	GLuint fragment_shader = CompileShader(path_fragment_shader, GL_FRAGMENT_SHADER);

	GLCall(m_RendererID = glCreateProgram());
	GLCall(glAttachShader(m_RendererID, vertex_shader));
	GLCall(glAttachShader(m_RendererID, fragment_shader));
	GLCall(glLinkProgram(m_RendererID));
	GLCall(glValidateProgram(m_RendererID));

	GLCall(glDeleteShader(vertex_shader));
	GLCall(glDeleteShader(fragment_shader));
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_RendererID));
}

GLint Shader::GetUniformLocation(const std::string & name)
{
	if (m_LocationCache.find(name) != m_LocationCache.end())
	{
		return m_LocationCache.at(name);
	}
	else
	{
		GLCall(GLint location = glGetUniformLocation(m_RendererID, name.c_str()));
		if (location == -1)
			std::cerr << "Could not find the uniform variable " << name << "!\n";
		else
			m_LocationCache[name] = location;

		return location;
	}
	
}

GLuint Shader::CompileShader(const std::string& filepath, GLenum shader_type)
{
	std::ifstream shader_file(filepath);
	std::string shader_source = "";

	for (std::string line; std::getline(shader_file, line);)
	{
		shader_source += line + '\n';
	}

	GLCall(GLuint shader = glCreateShader(shader_type));
	const char *shader_source_cstr = shader_source.c_str();
	GLCall(glShaderSource(shader, 1, &shader_source_cstr, NULL));
	GLCall(glCompileShader(shader));

	GLint vertex_compiled;
	GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &vertex_compiled));
	if (vertex_compiled == GL_FALSE)
	{
		GLsizei log_length;
		GLCall(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length));
		std::unique_ptr<GLchar[]> log_buffer = std::make_unique<GLchar[]>(log_length);
		GLCall(glGetShaderInfoLog(shader, 1024, &log_length, log_buffer.get()));

		std::cerr << "Failed to compile the "
			<< (shader_type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT")
			<< " shader: " << log_buffer << '\n';

		GLCall(glDeleteShader(shader));

		return 0;
	}

	return shader;
}
