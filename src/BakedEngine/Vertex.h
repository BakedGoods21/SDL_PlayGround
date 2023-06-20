#pragma once

// GL Includes
#include <GL/glew.h>

// glm Includes
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

namespace BakedEngine
{

struct ColorRGBA8
{
	ColorRGBA8() : red(0), green(0), blue(0), alpha(0) {}
	ColorRGBA8(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
				: red(r), green(g), blue(b), alpha(a) {}
	GLubyte red{0};
	GLubyte green{0};
	GLubyte blue{0};
	GLubyte alpha{0};
};

struct VertexData
{
	VertexData() {};
	VertexData(glm::vec2 newPos, ColorRGBA8 newColor, glm::vec2 newUV) : position(newPos), color(newColor), uv(newUV) {};
	VertexData(GLfloat newX, GLfloat newY, GLubyte r, GLubyte g, GLubyte b, GLubyte a, GLfloat newU, GLfloat newV)
						: position(newX, newY), color(r, g, b, a), uv(newU, newV) {};
	VertexData(glm::vec2 newPos, GLubyte r, GLubyte g, GLubyte b, GLubyte a, glm::vec2 newUV)
						: position(newPos), color(r, g, b, a), uv(newUV) {};

	glm::vec2 position;
	ColorRGBA8 color;
	glm::vec2 uv;

	void setPosition(GLfloat x, GLfloat y)
	{
		position.x = x;
		position.y = y;
	}

	void setColor(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha)
	{
		color.red = red;
		color.green = green;
		color.blue = blue;
		color.alpha = alpha;
	}

	void setUV(GLfloat u, GLfloat v)
	{
		uv.x = u;
		uv.y = v;
	}
};

} // End of namespace BakedEngine
