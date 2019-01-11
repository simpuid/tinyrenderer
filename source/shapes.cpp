#include <image.hpp>
#include <color.hpp>
#include <utility>
#include <cmath>
#include <shapes.hpp>
#include <limits>
#include <zbuffer.hpp>
#include <iostream>
#include <cmath>

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
void Triangle3d::draw(Image &image, Image &texture, ZBuffer &zBuffer, TransformMatrix &matrix, Vector3f lightDirection)
{
	Vector3f vertexWorld[3];
	Vector2i minimum{std::numeric_limits<int>::max(), std::numeric_limits<int>::max()}, maximum{std::numeric_limits<int>::min(), std::numeric_limits<int>::min()};
	for (int i = 0; i < 3; i++)
	{
		Matrixf<1, 4> vertex{{vertices[i].x, vertices[i].y, vertices[i].z, 1.0f}};
		Matrixf<1, 4> result = matrix * vertex;
		vertexWorld[i] = Vector3f{result.data(0, 0) / result.data(0, 3), result.data(0, 1) / result.data(0, 3), result.data(0, 2) / result.data(0, 3)};
		minimum.x = std::max<float>(0.0f, std::min<float>(minimum.x, vertexWorld[i].x - 1));
		minimum.y = std::max<float>(0.0f, std::min<float>(minimum.y, vertexWorld[i].y - 1));
		maximum.y = std::min<float>(image.height, std::max<float>(maximum.y, vertexWorld[i].y + 1));
		maximum.x = std::min<float>(image.width, std::max<float>(maximum.x, vertexWorld[i].x + 1));
	}
	if (((vertexWorld[1] - vertexWorld[0]) ^ (vertexWorld[2] - vertexWorld[0])) * Vector3f(0, 0, 1) >= 0)
	{
		for (int x{minimum.x}; x <= maximum.x; x++)
		{
			for (int y{minimum.y}; y <= maximum.y; y++)
			{
				Vector3f point = Vector3f(x, y, 0) - vertexWorld[0];
				Vector3f parameters = Vector3f(vertexWorld[1].x - vertexWorld[0].x, vertexWorld[2].x - vertexWorld[0].x, -point.x) ^ Vector3f(vertexWorld[1].y - vertexWorld[0].y, vertexWorld[2].y - vertexWorld[0].y, -point.y);
				if (parameters.z != 0)
				{
					parameters = parameters * (1 / parameters.z);
					if (parameters.x >= 0 && parameters.y >= 0 && parameters.x + parameters.y <= 1)
					{

						float zDepth = (vertexWorld[0].z * (1 - parameters.x - parameters.y) + vertexWorld[1].z * parameters.x + vertexWorld[2].z * parameters.y);
						if (zBuffer.getBuffer(x, y) < zDepth)
						{
							Vector3f pixelNormal = (normals[0] * (1 - parameters.x - parameters.y) + normals[1] * parameters.x + normals[2] * parameters.y);
							Vector2f texturePosition = (textureCordinates[0] + (textureCordinates[1] - textureCordinates[0]) * parameters.x + (textureCordinates[2] - textureCordinates[0]) * parameters.y);
							image.setColor(x, y, texture.getColor(texturePosition.x * texture.width, texturePosition.y * texture.height) * (pixelNormal.normalise() * lightDirection));
							zBuffer.setBuffer(x, y, zDepth);
						}
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