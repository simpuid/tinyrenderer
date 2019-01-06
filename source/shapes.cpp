#include <image.hpp>
#include <color.hpp>
#include <utility>
#include <cmath>
#include <shapes.hpp>
#include <limits>
#include <zbuffer.hpp>

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
void Triangle3d::draw(Image &image, Image &texture, ZBuffer &zBuffer, float intensity)
{
	Vector3f vertexWorld[3];
	Vector2i scale(image.width * 0.5f, image.height * 0.5f);
	Vector2i minimum{std::numeric_limits<int>::max(), std::numeric_limits<int>::max()}, maximum{std::numeric_limits<int>::min(), std::numeric_limits<int>::min()};
	for (int i = 0; i < 3; i++)
	{
		vertexWorld[i] = Vector3f((vertices[i].x + 1) * scale.x, (vertices[i].y + 1) * scale.y, vertices[i].z);
		minimum.x = vertexWorld[i].x - 1 < minimum.x ? vertexWorld[i].x - 1 : minimum.x;
		minimum.y = vertexWorld[i].y - 1 < minimum.y ? vertexWorld[i].y - 1 : minimum.y;
		maximum.x = vertexWorld[i].x + 1 > maximum.x ? vertexWorld[i].x + 1 : maximum.x;
		maximum.y = vertexWorld[i].y + 1 > maximum.y ? vertexWorld[i].y + 1 : maximum.y;
	}
	Vector3f side1 = vertexWorld[1] - vertexWorld[0];
	Vector3f side2 = vertexWorld[2] - vertexWorld[0];
	for (int x{minimum.x}; x <= maximum.x; x++)
	{
		for (int y{minimum.y}; y <= maximum.y; y++)
		{
			Vector3f point = Vector3f(x, y, 0) - vertexWorld[0];
			Vector3f parameters = Vector3f(side1.x, side2.x, -point.x) ^ Vector3f(side1.y, side2.y, -point.y);
			if (parameters.z != 0)
			{
				parameters = parameters * (1 / parameters.z);
				if (parameters.x >= 0 && parameters.y >= 0 && parameters.x + parameters.y <= 1)
				{
					float zDepth = (vertexWorld[0].z + side1.z * parameters.x + side2.z * parameters.y);
					if (zBuffer.getBuffer(x, y) < zDepth)
					{
						Vector2f texturePosition = (textureCordinates[0] + (textureCordinates[1] - textureCordinates[0]) * parameters.x + (textureCordinates[2] - textureCordinates[0]) * parameters.y);
						image.setColor(x, y, texture.getColor(texturePosition.x * texture.width, texturePosition.y * texture.height) * intensity);
						zBuffer.setBuffer(x, y, zDepth);
					}
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