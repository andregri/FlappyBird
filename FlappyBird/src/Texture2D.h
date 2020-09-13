#pragma once

#include "GL/glew.h"
#include "Error.h"
#include <string>

class Texture2D
{
public:
	Texture2D() {};
	Texture2D(const std::string& path);
	~Texture2D();
	void Bind() { GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureID)); };
	void Unbind() { GLCall(glBindTexture(GL_TEXTURE_2D, 0)); };

private:
	GLuint m_TextureID;
	unsigned char *m_Data;

	void Load(const std::string & path);
};

