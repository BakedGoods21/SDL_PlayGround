#pragma once

// C++ Includes
#include <vector>

// Glew Includes
#include <GL/glew.h>

// Baked Engine Includes
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

class RenderBatch
{
public:
	RenderBatch(GLuint newOffset, GLuint newNumVertices, GLuint newTexture) : offset(newOffset), numVertices(newNumVertices), texture(newTexture)
	{ }
	GLuint offset;
	GLuint numVertices;
	GLuint texture;
};

class SpriteBatch
{
public:
	SpriteBatch();
	~SpriteBatch();

	void init();

	void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
	void end();

	void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color);
	void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color, float angle);
	void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color, const glm::vec2& dir);

	void renderBatch();


private:
	void createRenderBatches();
	void createVertexArray();
	void sortGlyphs();

	static bool compareFrontToBack(Glyph* a, Glyph* b);
	static bool compareBackToFront(Glyph* a, Glyph* b);
	static bool compareTexture(Glyph* a, Glyph* b);

	GLuint _vbo;
	GLuint _vao;

	GlyphSortType _sortType;

	std::vector<Glyph> _glyphs; // For sorting glyphs
	std::vector<Glyph*> _glyphPointers; // For sorting
	std::vector<RenderBatch> _renderBatches;
};

}
