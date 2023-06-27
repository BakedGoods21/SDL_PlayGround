// C++ Includes
#include <algorithm>

// BakedEngine Includes
#include "BakedEngine/SpriteBatch.h"
#include "BakedEngine/Vertex.h"

namespace BakedEngine
{

SpriteBatch::SpriteBatch()
{
	// Tell OpenGL to generate a Vertex Array Object buffer and Vertex Buffer Object buffer
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);

	// Tell OpenGL to bind to these objects as we are getting ready to start using them
	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	// Tell OpenGL that their is going to be 3 attributes it needs to know about to parse
	glEnableVertexAttribArray((int)VO_ATTRIBUTES::POSITION);
	glEnableVertexAttribArray((int)VO_ATTRIBUTES::COLOR);
	glEnableVertexAttribArray((int)VO_ATTRIBUTES::UV);

	// This is the position attribute pointer
	glVertexAttribPointer((int)VO_ATTRIBUTES::POSITION, (sizeof(Position) / (sizeof(float))), GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, position));

	// This is the color attribute pointer
	glVertexAttribPointer((int)VO_ATTRIBUTES::COLOR, sizeof(BakedEngine::ColorRGBA8), GL_UNSIGNED_BYTE, GL_TRUE, sizeof(VertexData), (void*)offsetof(VertexData, color));

	// This is the UV attribute pointer
	glVertexAttribPointer((int)VO_ATTRIBUTES::UV, (sizeof(UV) / (sizeof(float))), GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*) offsetof(VertexData, uv));

	// Unbind the vbo and vao as we are done using them
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

SpriteBatch::~SpriteBatch() { }


void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, const float& depth, const ColorRGBA8& color)
{
	_glyphLeftovers.emplace_back(texture, depth);
	_glyphs.emplace_back(destRect, uvRect, color);
}

void SpriteBatch::render()
{
	_glyphPointers.resize(_glyphs.size());
	const unsigned int GLYPH_SIZE = (int)_glyphs.size();
	for (unsigned int i = 0; i < GLYPH_SIZE; i++)
	{
		_glyphPointers[i] = &_glyphs[i];
	}

	sortGlyphs(0, GLYPH_SIZE);
	prepareBatches();
	renderBatches();
	resetBatches();
}

void SpriteBatch::prepareBatches()
{
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	std::vector<Glyph> drawGlyphs;
	drawGlyphs.reserve(_glyphPointers.size());

	for (Glyph* glyph : _glyphPointers)
	{
		drawGlyphs.push_back(*glyph);
	}

	const int NUM_OF_VERTICES = (int)(drawGlyphs.size() * GLYPH_OFFSET_SIZE);

	// Orphan the data
	glBufferData(GL_ARRAY_BUFFER, NUM_OF_VERTICES, nullptr, GL_DYNAMIC_DRAW);
	// Upload the data
	glBufferSubData(GL_ARRAY_BUFFER, 0, NUM_OF_VERTICES, drawGlyphs.data());

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SpriteBatch::renderBatches()
{
	glBindVertexArray(_vao);

	for (unsigned int i = 0; i < _glyphLeftovers.size(); i++)
	{
		glBindTexture(GL_TEXTURE_2D, _glyphLeftovers[i]._texture);

		glDrawArrays(GL_TRIANGLES, i * GLYPH_OFFSET_SIZE, GLYPH_OFFSET_SIZE);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	glBindVertexArray(0);
}

void SpriteBatch::resetBatches()
{
	// _renderBatches.clear();
	_glyphPointers.clear();
	_glyphs.clear();
	_glyphLeftovers.clear();
}


int SpriteBatch::partition(int start, int end)
{
    GlyphLeftOvers& pivot = _glyphLeftovers[start];

    int count = 0;
    for (int i = start + 1; i <= end; i++)
	{
        if (_glyphLeftovers[i]._texture <= pivot._texture)
		{
            count++;
		}
    }

    // Giving pivot element its correct position
    int pivotIndex = start + count;
    std::swap(_glyphLeftovers[pivotIndex], _glyphLeftovers[start]);
    std::swap(_glyphPointers[pivotIndex], _glyphPointers[start]);

    // Sorting left and right parts of the pivot element
    int i = start, j = end;

    while (i < pivotIndex && j > pivotIndex)
	{
        while (_glyphLeftovers[i]._texture <= pivot._texture)
		{
            i++;
        }

        while (_glyphLeftovers[j]._texture > pivot._texture)
		{
            j--;
        }

        if (i < pivotIndex && j > pivotIndex)
		{
            std::swap(_glyphLeftovers[i++], _glyphLeftovers[j--]);
            std::swap(_glyphPointers[i++], _glyphPointers[j--]);

            std::swap(_glyphLeftovers[i++], _glyphLeftovers[j--]);
            std::swap(_glyphPointers[i++], _glyphPointers[j--]);
        }
    }

    return pivotIndex;
}

// Uses quickSort algorithm
void SpriteBatch::sortGlyphs(int start, int end)
{
    // base case
    if (start >= end)
        return;

    // partitioning the array
    int p = partition(start, end);

    // Sorting the left part
    sortGlyphs(start, p - 1);

    // Sorting the right part
    sortGlyphs(p + 1, end);
}


} // End of namespace BakedEngine
