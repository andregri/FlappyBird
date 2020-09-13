#include "Error.h"

#include <stdexcept>
#include <iostream>
#include <GL/glew.h>

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char *function, const char *file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cerr << "[OpenGL error] (" << error << "): " << file << ": "
			<< function << ": " << line << '\n';
		return false;
	}
	return true;
}