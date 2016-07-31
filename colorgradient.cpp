// Copyright © 2016 Mikko Ronkainen <firstname@mikkoronkainen.com>
// License: MIT, see the LICENSE file.

#include "colorgradient.h"

#include <cassert>

void ColorGradient::addSegment(const Color& start, const Color& end, uint32_t length)
{
	assert(length >= 1);

	ColorGradientSegment segment;

	segment.startColor = start;
	segment.endColor = end;
	segment.startIndex = totalLength;
	segment.endIndex = totalLength + length;

	segments.push_back(segment);

	segmentCount = uint32_t(segments.size());
	totalLength += length;
}

Color ColorGradient::getColor(float alpha) const
{
	assert(alpha >= 0.0f && alpha <= 1.0f);

	Color result;
	uint32_t index = uint32_t(ceil(alpha * totalLength));

	for (uint32_t i = 0; i < segmentCount; ++i)
	{
		const ColorGradientSegment& segment = segments[i];

		if (index >= segment.startIndex && index <= segment.endIndex)
		{
			float alphaStart = segment.startIndex / float(totalLength);
			float alphaEnd = segment.endIndex / float(totalLength);
			float segmentAlpha = (alpha - alphaStart) / (alphaEnd - alphaStart);

			result = Color::lerp(segment.startColor, segment.endColor, segmentAlpha);

			break;
		}
	}

	return result;
}
