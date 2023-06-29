#pragma once

// C++ Includes
#include <vector>
#include <iostream>

// glm Includes
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

// Glew Includes
#include <GL/glew.h>

// BakedEngine Includes
#include "BakedEngine/Vertex.h"
#include "BakedEngine/Glyph.h"

namespace BakedEngine
{

enum class VO_ATTRIBUTES
{
	POSITION,
	COLOR,
	UV
};

class SpriteBatch
{
public:
	SpriteBatch();
	~SpriteBatch();

	void begin();

	void init();

	void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, const float& depth, const ColorRGBA8& color);
	void render();

private:
	void prepareBatches();
	void renderBatches();
	void resetBatches();

	// Sorting Algorithms
	int partition(int start, int end);
	void sortGlyphs(int lowIndex, int highIndex);

	GLuint _vbo;
	GLuint _vao;

	std::vector<GlyphVAOInfo> vaoInfo;
	std::vector<Glyph> _glyphs;
	std::vector<Glyph*> _glyphPointers;
};

} // End of namespace BakedEngine
