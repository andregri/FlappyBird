#pragma once

#include <GL/glew.h>

class VertexArray
{
public:
	VertexArray() {};
	VertexArray(int count);
	VertexArray(int n_vertices, float positions[], float tex_coord[], int n_indices, unsigned int indices[]);
	~VertexArray();
	void Bind();
	void Unbind();
	void Draw();
	void Render();

private:
	int m_NumIndices;

	GLuint m_VertexArrayObject;
	GLuint m_PositionBufferObject;
	GLuint m_TexCoordObject;
	GLuint m_IndicesObject;

	GLint m_PositionAttribLocation;
	GLint m_TexCoordAttribLocation;
};

