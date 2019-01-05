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
void Triangle3d::draw(Image &image)
{
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