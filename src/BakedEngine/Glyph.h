#pragma once

// glm Includes
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

// BakedEngine Includes
#include "BakedEngine/Vertex.h"

namespace BakedEngine
{

enum class GlyphSortType
{
	NONE,
	BACK_TO_FRONT,
	FRONT_TO_BACK,
	TEXTURE
};

class Glyph
{
public:
	Glyph() {};
	Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color);
	Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color, float angle);

	GLuint _texture;
	float _depth;

	VertexData _topLeft;
	VertexData _bottomLeft;
	VertexData _topRight;
	VertexData _bottomRight;
private:
	glm::vec2 rotatePoint(glm::vec2 pos, float angle);
};

} // End of namespace BakedEngine
