// C++ Includes
#include <algorithm>

// BakedEngine Includes
#include "BakedEngine/SpriteBatch.h"
#include "BakedEngine/Vertex.h"

namespace BakedEngine
{

SpriteBatch::SpriteBatch() {}

void SpriteBatch::init()
{
	// Tell OpenGL to generate a Vertex Array Object buffer and Vertex Buffer Object buffer
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);

	// Tell OpenGL to bind to these objects as we are getting ready to start using them
	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	// Tell OpenGL that their is going to be 3 attributes it needs to know about to parse
	glEnableVertexAttribArray((GLuint)VO_ATTRIBUTES::POSITION);
	glEnableVertexAttribArray((GLuint)VO_ATTRIBUTES::COLOR);
	glEnableVertexAttribArray((GLuint)VO_ATTRIBUTES::UV);

	// This is the position attribute pointer
	glVertexAttribPointer((GLuint)VO_ATTRIBUTES::POSITION, POSITION_ELEMENT_SIZE, GL_FLOAT, GL_FALSE, VERTEX_DATA_SIZE, (void*)offsetof(VertexData, position));

	// This is the color attribute pointer
	glVertexAttribPointer((GLuint)VO_ATTRIBUTES::COLOR, sizeof(BakedEngine::ColorRGBA8), GL_UNSIGNED_BYTE, GL_TRUE, VERTEX_DATA_SIZE, (void*)offsetof(VertexData, color));

	// This is the UV attribute pointer
	glVertexAttribPointer((GLuint)VO_ATTRIBUTES::UV, UV_ELEMENT_SIZE, GL_FLOAT, GL_FALSE, VERTEX_DATA_SIZE, (void*)offsetof(VertexData, uv));

	// Unbind the vbo and vao as we are done using them
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

SpriteBatch::~SpriteBatch() { }

void SpriteBatch::begin()
{
	resetBatches();
}

void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, const float& depth, const ColorRGBA8& color)
{
	_glyphs.emplace_back(destRect, uvRect, color, texture, depth);
}

void SpriteBatch::render()
{
	_glyphPointers.reserve(_glyphs.size());
	const unsigned int GLYPH_SIZE = (int)_glyphs.size();
	for (unsigned int i = 0; i < GLYPH_SIZE; i++)
	{
		_glyphPointers.push_back(&_glyphs[i]);
	}

	sortGlyphs(0, GLYPH_SIZE-1);
	prepareBatches();
	renderBatches();
}

void SpriteBatch::prepareBatches()
{
	int offset = 0;
	std::vector<GlyphVertices> drawGlyphs;
	drawGlyphs.reserve(_glyphPointers.size());

	const unsigned int num_of_glyphs = (unsigned int)_glyphPointers.size();
	if (num_of_glyphs > 0)
	{
		drawGlyphs.push_back(_glyphPointers[0]->_vertices);
		vaoInfo.emplace_back(_glyphPointers[0]->_texture, GLYPH_VERTICE_SIZE, offset);
	}

	for (unsigned int i = 1; i < num_of_glyphs; i++)
	{
		Glyph* glyph = _glyphPointers[i];
		drawGlyphs.push_back(glyph->_vertices);

		if (glyph->_texture != vaoInfo.back()._texture)
		{
			vaoInfo.emplace_back(glyph->_texture, GLYPH_VERTICE_SIZE, (offset += 6));
		}
		else
		{
			offset += GLYPH_VERTICE_SIZE;
			vaoInfo.back().increaseVerticeCount(GLYPH_VERTICE_SIZE);
		}
	}

	const int NUM_OF_VERTICES = (int)(drawGlyphs.size() * GLYPH_VERTICE_SIZE);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	// Orphan the data
	glBufferData(GL_ARRAY_BUFFER, NUM_OF_VERTICES * VERTEX_DATA_SIZE, nullptr, GL_DYNAMIC_DRAW);
	// glBufferData(GL_ARRAY_BUFFER, NUM_OF_VERTICES * VERTEX_DATA_SIZE, drawGlyphs.data(), GL_DYNAMIC_DRAW);
	// Upload the data
	glBufferSubData(GL_ARRAY_BUFFER, 0, NUM_OF_VERTICES * VERTEX_DATA_SIZE, drawGlyphs.data());

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SpriteBatch::renderBatches()
{
	glBindVertexArray(_vao);

	for (unsigned int i = 0; i < vaoInfo.size(); i++)
	{
		glBindTexture(GL_TEXTURE_2D, vaoInfo[i]._texture);

		glDrawArrays(GL_TRIANGLES, vaoInfo[i]._offset, vaoInfo[i]._numOfVertices);

		// glBindTexture(GL_TEXTURE_2D, 0);
	}

	glBindVertexArray(0);
}

void SpriteBatch::resetBatches()
{
	vaoInfo.clear();
	_glyphPointers.clear();
	_glyphs.clear();
}


int SpriteBatch::partition(int start, int end)
{
    Glyph* pivot = _glyphPointers[start];

    int count = 0;
    for (int i = start + 1; i <= end; i++)
	{
        if (_glyphPointers[i]->_texture <= pivot->_texture)
		{
            count++;
		}
    }

    // Giving pivot element its correct position
    int pivotIndex = start + count;
    std::swap(_glyphPointers[pivotIndex], _glyphPointers[start]);

    // Sorting left and right parts of the pivot element
    int i = start, j = end;

    while (i < pivotIndex && j > pivotIndex)
	{
        while (_glyphPointers[i]->_texture <= pivot->_texture)
		{
            i++;
        }

        while (_glyphPointers[j]->_texture > pivot->_texture)
		{
            j--;
        }

        if (i < pivotIndex && j > pivotIndex)
		{
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
