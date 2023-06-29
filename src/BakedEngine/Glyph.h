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

struct GlyphVertices
{
	GlyphVertices() {};
	GlyphVertices(const glm::vec4& destRect, const glm::vec4& uvRect, const ColorRGBA8& color);
	GlyphVertices(const glm::vec4& destRect, const glm::vec4& uvRect, const ColorRGBA8& color, const float& angle);

	glm::vec2 rotatePoint(const glm::vec2& pos, float angle);

	VertexData _topLeft;
	VertexData _bottomLeft;
	VertexData _bottomRight;
	VertexData _bottomRight1;
	VertexData _topRight;
	VertexData _topLeft1;
};

struct GlyphVAOInfo
{
	GlyphVAOInfo() {}
	GlyphVAOInfo(const GLuint& texture, const int& numOfVertices) : _texture(texture), _numOfVertices(numOfVertices) {}
	GlyphVAOInfo(const GLuint& texture, const int& numOfVertices, int offset) :
						_texture(texture), _numOfVertices(numOfVertices), _offset(offset) {}

	void setOffset(int value) { _offset = value; }
	void increaseVerticeCount(int value) { _numOfVertices += value; }

	GLuint _texture{0};
	int _numOfVertices{0};
	int _offset{0};
};


class Glyph
{
public:
	Glyph() {};
	Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, const ColorRGBA8& color, GLuint texture, const float& depth) :
					 _texture(texture), _depth(depth), _vertices(destRect, uvRect, color) {}
	Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, const ColorRGBA8& color, GLuint texture, const float& depth, const float& angle) :
					 _texture(texture), _depth(depth), _vertices(destRect, uvRect, color, angle) {}

	GLuint _texture;
	float _depth;
	GlyphVertices _vertices;

private:
};

constexpr int GLYPH_VERTICE_SIZE = sizeof(GlyphVertices) / sizeof(VertexData);

} // End of namespace BakedEngine
