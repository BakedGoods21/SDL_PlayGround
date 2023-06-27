// BakedEngine Includes
#include "BakedEngine/Glyph.h"
#include "BakedEngine/FastTrig.h"

namespace BakedEngine
{

Glyph::Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, const ColorRGBA8& color)
{
	_topLeft.color = color;
	_topLeft.setPosition(destRect.x, (destRect.y + destRect.w));
	_topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);
	_topLeft1 = _topLeft;

	_bottomLeft.color = color;
	_bottomLeft.setPosition(destRect.x, destRect.y);
	_bottomLeft.setUV(uvRect.x, uvRect.y);

	_bottomRight.color = color;
	_bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
	_bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);
	_bottomRight1 = _bottomRight;

	_topRight.color = color;
	_topRight.setPosition(destRect.x + destRect.z, (destRect.y + destRect.w));
	_topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
};

Glyph::Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, const ColorRGBA8& color, const float& angle)
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
	_topLeft1 = _topLeft;

	_bottomLeft.color = color;
	_bottomLeft.setPosition(destRect.x + bl.x, destRect.y + bl.y);
	_bottomLeft.setUV(uvRect.x, uvRect.y);

	_bottomRight.color = color;
	_bottomRight.setPosition(destRect.x + br.x, destRect.y + br.y);
	_bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);
	_bottomRight1 = _bottomRight;

	_topRight.color = color;
	_topRight.setPosition(destRect.x + tr.x, destRect.y + tr.y);
	_topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
};

glm::vec2 Glyph::rotatePoint(const glm::vec2& pos, float angle)
{
	while (angle >= 360) { angle -= 360; }
	while (angle < 0) { angle += 360; }

	glm::vec2 newv;
	newv.x = (float)(pos.x * bakedCos[(int)angle] - pos.y * bakedSin[(int)angle]);
	newv.y = (float)(pos.x * bakedSin[(int)angle] + pos.y * bakedCos[(int)angle]);

	return newv;
}

} // End of namespace BakedEngine

