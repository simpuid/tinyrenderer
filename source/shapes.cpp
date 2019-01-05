#include <image.hpp>
#include <utility>
#include <cmath>
#include <shapes.hpp>

Line2d::Line2d(Vector2i start, Vector2i end, Color color) : start{start}, end{end}, color{color} {}
void Line2d::draw(Image &image)
{
	Vector2i delta = end - start;
	bool steep = (std::abs(delta.x) < std::abs(delta.y));
	if (steep)
	{
		std::swap(start.x, start.y);
		std::swap(end.x, end.y);
	}
	delta = end - start;
	if (delta.x < 0)
	{
		std::swap(start, end);
	}
	delta = end - start;
	Vector2i delta2{delta.x * 2, std::abs(delta.y * 2)};
	int yIncrease = end.y > start.y ? 1 : -1;
	for (int x{start.x}, y{start.y}, yError{0}; x <= end.x; x += 1)
	{
		steep ? image.setColor(y, x, color) : image.setColor(x, y, color);
		if ((yError += delta2.y) > delta.x)
		{
			yError -= delta2.x;
			y += yIncrease;
		}
	}
}
void Triangle3d::draw(Image &image, Color color)
{
	Vector2f vertexWorld[3];
	Vector2i scale(image.width * 0.5f, image.height * 0.5f);
	Vector2i minimum{INT32_MAX, INT32_MAX}, maximum{INT32_MIN, INT32_MIN};
	auto lambdaRound = [](float f) -> int { return (int)f; };
	for (int i = 0; i < 3; i++)
	{
		vertexWorld[i] = Vector2f(lambdaRound((vertices[i].x + 1) * scale.x), lambdaRound((vertices[i].y + 1) * scale.y));
		minimum.x = vertexWorld[i].x - 1 < minimum.x ? vertexWorld[i].x - 1 : minimum.x;
		minimum.y = vertexWorld[i].y - 1 < minimum.y ? vertexWorld[i].y - 1 : minimum.y;
		maximum.x = vertexWorld[i].x + 1 > maximum.x ? vertexWorld[i].x + 1 : maximum.x;
		maximum.y = vertexWorld[i].y + 1 > maximum.y ? vertexWorld[i].y + 1 : maximum.y;
	}
	for (int x{minimum.x}; x <= maximum.x; x++)
	{
		for (int y{minimum.y}; y <= maximum.y; y++)
		{
			Vector2f side1 = vertexWorld[1] - vertexWorld[0];
			Vector2f side2 = vertexWorld[2] - vertexWorld[0];
			Vector2f point = Vector2f(x, y) - vertexWorld[0];
			Vector3f parameters = Vector3f(side1.x, side2.x, -point.x) ^ Vector3f(side1.y, side2.y, -point.y);
			if (parameters.z != 0)
			{
				parameters = parameters * (1 / parameters.z);
				if (parameters.x >= 0 && parameters.y >= 0 && parameters.x + parameters.y <= 1)
				{
					image.setColor(x, y, color);
				}
			}
		}
	}
}
void Triangle3d::drawWireframe(Image &image, Color color)
{
	for (int i = 0; i < 3; i++)
	{
		Vector3f v1 = vertices[i];
		Vector3f v2 = vertices[(i + 1) % 3];
		Vector2i scale(image.width * 0.5f, image.height * 0.5f);
		Line2d line(Vector2i((v1.x + 1) * scale.x, (v1.y + 1) * scale.y), Vector2i((v2.x + 1) * scale.x, (v2.y + 1) * scale.y), color);
		line.draw(image);
	}
}