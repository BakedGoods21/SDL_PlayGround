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

typedef glm::vec2 Position;
typedef glm::vec2 UV;

struct VertexData
{
	VertexData() {};
	VertexData(const glm::vec2& newPos, const ColorRGBA8 newColor, const glm::vec2 newUV) : position(newPos), color(newColor), uv(newUV) {};
	VertexData(const GLfloat& newX, const GLfloat& newY, const GLubyte& r, const GLubyte& g, const GLubyte& b, const GLubyte& a, const GLfloat& newU, const GLfloat& newV)
						: position(newX, newY), color(r, g, b, a), uv(newU, newV) {};
	VertexData(const glm::vec2& newPos, const GLubyte& r, const GLubyte& g, const GLubyte& b, const GLubyte& a, const glm::vec2& newUV)
						: position(newPos), color(r, g, b, a), uv(newUV) {};

	Position position;
	ColorRGBA8 color;
	UV uv;

	void setPosition(const GLfloat& x, const GLfloat& y)
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

	void setUV(const GLfloat& u, const GLfloat& v)
	{
		uv.x = u;
		uv.y = v;
	}
};

constexpr GLint POSITION_ELEMENT_SIZE = (sizeof(Position) / (sizeof(float)));
constexpr GLint UV_ELEMENT_SIZE = (sizeof(UV) / (sizeof(float)));
constexpr GLint VERTEX_DATA_SIZE = sizeof(VertexData);

} // End of namespace BakedEngine
