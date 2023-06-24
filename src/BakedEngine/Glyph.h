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

struct GlyphLeftOvers
{
	GlyphLeftOvers() {};
	GlyphLeftOvers(GLuint texture, const float& depth) : _texture(texture), _depth(depth) {};

	GLuint _texture;
	float _depth;

	// VertexData _topLeft;
	// VertexData _bottomLeft;
	// VertexData _topRight;
	// VertexData _bottomRight;
};


class Glyph
{
public:
	Glyph() {};
	Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, const ColorRGBA8& color);
	Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, const ColorRGBA8& color, const float& angle);

	// GLuint _texture;
	// float _depth;

	VertexData _topLeft;
	VertexData _bottomLeft;
	VertexData _bottomRight;
	VertexData _bottomRight1;
	VertexData _topRight;
	VertexData _topLeft1;
private:
	glm::vec2 rotatePoint(const glm::vec2& pos, float angle);
};

constexpr int GLYPH_OFFSET_SIZE = sizeof(Glyph) / sizeof(VertexData);

} // End of namespace BakedEngine
