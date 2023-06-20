// C++ Includes
#include <algorithm>

// glm Includes
#include <glm/geometric.hpp>

// BakedEngine Includes
#include "BakedEngine/SpriteBatch.h"

namespace BakedEngine
{

Glyph::Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color)
	: _texture(texture), _depth(depth)
{
	_topLeft.color = color;
	_topLeft.setPosition(destRect.x, (destRect.y + destRect.w));
	_topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

	_bottomLeft.color = color;
	_bottomLeft.setPosition(destRect.x, destRect.y);
	_bottomLeft.setUV(uvRect.x, uvRect.y);

	_bottomRight.color = color;
	_bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
	_bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

	_topRight.color = color;
	_topRight.setPosition(destRect.x + destRect.z, (destRect.y + destRect.w));
	_topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
};

Glyph::Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color, float angle)
	: _texture(texture), _depth(depth)
{
	glm::vec2 halfDimensions(destRect.z / 2.0f, destRect.w / 2.0f);

	// Get points cenetered at origin
	glm::vec2 tl(-halfDimensions.x, halfDimensions.y);
	glm::vec2 bl(-halfDimensions.x, -halfDimensions.y);
	glm::vec2 br(halfDimensions.x, -halfDimensions.y);
	glm::vec2 tr(halfDimensions.x, halfDimensions.y);

	// Rotate the points
	tl = rotatePoint(tl, angle) + halfDimensions;
	bl = rotatePoint(bl, angle) + halfDimensions;
	br = rotatePoint(br, angle) + halfDimensions;
	tr = rotatePoint(tr, angle) + halfDimensions;


	_topLeft.color = color;
	_topLeft.setPosition(destRect.x + tl.x, destRect.y + tl.y);
	_topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

	_bottomLeft.color = color;
	_bottomLeft.setPosition(destRect.x + bl.x, destRect.y + bl.y);
	_bottomLeft.setUV(uvRect.x, uvRect.y);

	_bottomRight.color = color;
	_bottomRight.setPosition(destRect.x + br.x, destRect.y + br.y);
	_bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

	_topRight.color = color;
	_topRight.setPosition(destRect.x + tr.x, destRect.y + tr.y);
	_topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
};

glm::vec2 Glyph::rotatePoint(glm::vec2 pos, float angle)
{
	glm::vec2 newv;
	newv.x = (float)(pos.x * cos(angle) - pos.y * sin(angle));
	newv.y = (float)(pos.x * sin(angle) + pos.y * cos(angle));

	return newv;
}

SpriteBatch::SpriteBatch() : _vbo(0), _vao(0)
{

}

SpriteBatch::~SpriteBatch()
{

}

void SpriteBatch::init()
{
	createVertexArray();
}

void SpriteBatch::begin(GlyphSortType sortType/* = GlyphSortType::TEXTURE*/)
{
	_sortType = sortType;
	_renderBatches.clear();
	_glyphs.clear();
}

void SpriteBatch::end()
{
	_glyphPointers.resize(_glyphs.size());
	const unsigned long long int GLYPH_SIZE = _glyphs.size();
	for (unsigned int i = 0; i < GLYPH_SIZE; i++)
	{
		_glyphPointers[i] = &_glyphs[i];
	}
	sortGlyphs();
	createRenderBatches();
}

// void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color)
// {
// 	_glyphs.emplace_back(destRect, uvRect, texture, depth, color);
// }

// void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color, float angle)
// {
// 	_glyphs.emplace_back(destRect, uvRect, texture, depth, color, angle);
// }

// void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color, const glm::vec2& dir)
// {
// 	const glm::vec2 right(1.0f, 0.0f);
// 	float angle = (float)acos(glm::dot(right, dir));
// 	if (dir.y < 0.0f) angle = -angle;

// 	_glyphs.emplace_back(destRect, uvRect, texture, depth, color, angle);
// }

// void SpriteBatch::renderBatch()
// {
// 	glBindVertexArray(_vao);

// 	for (unsigned int i = 0; i < _renderBatches.size(); i++)
// 	{
// 		glBindTexture(GL_TEXTURE_2D, _renderBatches[i].texture);

// 		glDrawArrays(GL_TRIANGLES, _renderBatches[i].offset, _renderBatches[i].numVertices);
// 	}

// 	glBindVertexArray(0);
// }

void SpriteBatch::createRenderBatches()
{
	std::vector<VertexData> vertices;
	vertices.resize(_glyphPointers.size() * 6);

	if (_glyphPointers.empty())
	{
		return;
	}

	GLuint offset = 0;
	int currentVertex = 0;
	_renderBatches.emplace_back(offset, (GLuint)6, (GLuint)_glyphPointers[0]->_texture);

	vertices[currentVertex++] = _glyphPointers[0]->_topLeft;
	vertices[currentVertex++] = _glyphPointers[0]->_bottomLeft;
	vertices[currentVertex++] = _glyphPointers[0]->_bottomRight;
	vertices[currentVertex++] = _glyphPointers[0]->_bottomRight;
	vertices[currentVertex++] = _glyphPointers[0]->_topRight;
	vertices[currentVertex++] = _glyphPointers[0]->_topLeft;
	offset += 6;

	unsigned int glyphSize = (unsigned int) _glyphPointers.size();
	for (unsigned int currentGlyph = 1; currentGlyph < glyphSize; currentGlyph++)
	{
		if (_glyphPointers[currentGlyph]->_texture != _glyphPointers[currentGlyph - 1]->_texture)
		{
			_renderBatches.emplace_back(offset, (GLuint)6, (GLuint)_glyphPointers[currentGlyph]->_texture);
		}
		else
		{
			_renderBatches.back().numVertices += 6;
		}

		vertices[currentVertex++] = _glyphPointers[currentGlyph]->_topLeft;
		vertices[currentVertex++] = _glyphPointers[currentGlyph]->_bottomLeft;
		vertices[currentVertex++] = _glyphPointers[currentGlyph]->_bottomRight;
		vertices[currentVertex++] = _glyphPointers[currentGlyph]->_bottomRight;
		vertices[currentVertex++] = _glyphPointers[currentGlyph]->_topRight;
		vertices[currentVertex++] = _glyphPointers[currentGlyph]->_topLeft;
		offset += 6;
	}

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	// Orphan the data
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexData), nullptr, GL_DYNAMIC_DRAW);
	// Upload the data
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(VertexData), vertices.data());

	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void SpriteBatch::createVertexArray()
{
	if (_vao == 0)
	{
		glGenVertexArrays(1, &_vao);
	}
	glBindVertexArray(_vao);

	if (_vbo == 0)
	{
		glGenBuffers(1, &_vbo);
	}
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	// Tell opengl that we want to use the first
	// attribute array. We only need one array right
	// now since we are only using position
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	// This is the position attribute pointer
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, position));
	// This is the color attribute pointer
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(VertexData), (void*)offsetof(VertexData, color));
	// This is the UV attribute pointer
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, uv));

	glBindVertexArray(0);
}

// void SpriteBatch::sortGlyphs()
// {
// 	switch (_sortType)
// 	{
// 		case GlyphSortType::BACK_TO_FRONT:
// 			std::stable_sort(_glyphPointers.begin(), _glyphPointers.end(), compareBackToFront);
// 			break;
// 		case GlyphSortType::FRONT_TO_BACK:
// 			std::stable_sort(_glyphPointers.begin(), _glyphPointers.end(), compareFrontToBack);
// 			break;
// 		case GlyphSortType::TEXTURE:
// 			std::stable_sort(_glyphPointers.begin(), _glyphPointers.end(), compareTexture);
// 			break;
// 		case GlyphSortType::NONE:
// 			break;
// 	}
// }

// bool SpriteBatch::compareFrontToBack(Glyph* a, Glyph* b)
// {
// 	return (a->_depth < b->_depth);
// }

// bool SpriteBatch::compareBackToFront(Glyph* a, Glyph* b)
// {
// 	return (a->_depth > b->_depth);
// }

// bool SpriteBatch::compareTexture(Glyph* a, Glyph* b)
// {
// 	return (a->_texture < b->_texture);
// }

} // End of namespace BakedEngine
