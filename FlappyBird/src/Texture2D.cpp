#include "Texture2D.h"

#include <iostream>
#include <stdexcept>

#include "stb_image/stb_image.h"

#include "Error.h"


Texture2D::Texture2D(const std::string & path)
{
	Load(path);
}

Texture2D::~Texture2D()
{
	//glDeleteTextures(1, &m_TextureID);
}

void Texture2D::Load(const std::string& path)
{
	GLCall(glGenTextures(1, &m_TextureID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureID));

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

	int width, height, n_channels;
	stbi_set_flip_vertically_on_load(1);
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &n_channels, 4);
	if (data)
	{
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
	}
	else
	{
		std::cerr << "Failed to load the texture: '" << path << "'\n";
	}
	stbi_image_free(data);

	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
