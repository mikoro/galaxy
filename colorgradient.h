// Copyright © 2016 Mikko Ronkainen <firstname@mikkoronkainen.com>
// License: MIT, see the LICENSE file.

#pragma once

#include <cstdint>
#include <vector>

struct Color
{
	Color()
	{
	}

	Color(float r_, float g_, float b_, float a_ = 1.0f) : r(r_), g(g_), b(b_), a(a_)
	{
	}

	float r = 0.0f;
	float g = 0.0f;
	float b = 0.0f;
	float a = 1.0f;

	static Color lerp(const Color& start, const Color& end, float alpha)
	{
		Color c;

		c.r = start.r + (end.r - start.r) * alpha;
		c.g = start.g + (end.g - start.g) * alpha;
		c.b = start.b + (end.b - start.b) * alpha;
		c.a = start.a + (end.a - start.a) * alpha;

		return c;
	}
};

struct ColorGradientSegment
{
	Color startColor;
	Color endColor;
	uint32_t startIndex = 0;
	uint32_t endIndex = 0;
};

class ColorGradient
{
public:

	void addSegment(const Color& start, const Color& end, uint32_t length);
	Color getColor(float alpha) const;

private:

	uint32_t segmentCount = 0;
	uint32_t totalLength = 0;
	std::vector<ColorGradientSegment> segments;
};
