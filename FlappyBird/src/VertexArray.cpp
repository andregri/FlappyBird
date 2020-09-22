#include "VertexArray.h"

#include <GL/glew.h>

#include "Error.h"

VertexArray::VertexArray(int count)
	: m_NumIndices(count), m_IndicesObject(0)
{
	GLCall(glGenVertexArrays(1, &m_VertexArrayObject));
}

VertexArray::VertexArray(int n_vertices, float positions[], float tex_coord[], int n_indices, unsigned int indices[])
	: m_PositionAttribLocation(0), m_TexCoordAttribLocation(1)
{
	m_NumIndices = n_indices;

	GLCall(glGenVertexArrays(1, &m_VertexArrayObject));
	GLCall(glBindVertexArray(m_VertexArrayObject));

	GLCall(glGenBuffers(1, &m_PositionBufferObject));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_PositionBufferObject));
	GLCall(glBufferData(GL_ARRAY_BUFFER, 3 * n_vertices * sizeof(float), positions, GL_STATIC_DRAW));
	GLCall(glEnableVertexAttribArray(m_PositionAttribLocation));
	GLCall(glVertexAttribPointer(m_PositionAttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0));

	GLCall(glGenBuffers(1, &m_TexCoordObject));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_TexCoordObject));
	GLCall(glBufferData(GL_ARRAY_BUFFER, 2 * n_vertices * sizeof(float), tex_coord, GL_STATIC_DRAW));
	GLCall(glEnableVertexAttribArray(m_TexCoordAttribLocation));
	GLCall(glVertexAttribPointer(m_TexCoordAttribLocation, 2, GL_FLOAT, GL_FALSE, 0, 0));

	GLCall(glGenBuffers(1, &m_IndicesObject));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndicesObject));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_NumIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW));

	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindVertexArray(0));
}


VertexArray::~VertexArray()
{
	/*
	Unbind();
	GLCall(glDeleteBuffers(1, &m_PositionBufferObject));
	GLCall(glDeleteBuffers(1, &m_TexCoordObject));
	GLCall(glDeleteBuffers(1, &m_IndicesObject));
	GLCall(glDeleteVertexArrays(1, &m_VertexArrayObject));*/
}

void VertexArray::Bind()
{
	GLCall(glBindVertexArray(m_VertexArrayObject));
	if(m_IndicesObject > 0)
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndicesObject));
}

void VertexArray::Unbind()
{
	if (m_IndicesObject > 0)
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	GLCall(glBindVertexArray(0));
}

void VertexArray::Draw()
{
	if (m_IndicesObject > 0)
	{
		GLCall(glDrawElements(GL_TRIANGLES, m_NumIndices, GL_UNSIGNED_INT, 0));
	}
	else
	{
		GLCall(glDrawArrays(GL_TRIANGLES, 0, m_NumIndices));
	}
}

void VertexArray::Render()
{
	Bind();
	Draw();
}
