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
	Vector2i vertexWorld[3];
	Vector2i scale(image.width * 0.5f, image.height * 0.5f);
	auto lambdaRound = [](float f) -> int { return (int)f; };
	for (int i = 0; i < 3; i++)
	{
		vertexWorld[i] = Vector2i(lambdaRound((vertices[i].x + 1) * scale.x), lambdaRound((vertices[i].y + 1) * scale.y));
	}
	if (vertexWorld[0].y > vertexWorld[1].y)
		std::swap(vertexWorld[0], vertexWorld[1]);
	if (vertexWorld[0].y > vertexWorld[2].y)
		std::swap(vertexWorld[0], vertexWorld[2]);
	if (vertexWorld[1].y > vertexWorld[2].y)
		std::swap(vertexWorld[1], vertexWorld[2]);

	auto lambdaGetPointOnLine = [lambdaRound](Vector2i start, Vector2i end, int y) {
		double param = float(y - end.y) / float(start.y - end.y);
		return Vector2i(round(start.x * param + (1 - param) * end.x), y);
	};
	auto lambdaFillTrapezium = [lambdaGetPointOnLine, lambdaRound](Vector2i line1Start, Vector2i line1End, Vector2i line2Start, Vector2i line2End, int startY, int endY, Image &image, Color color) {
		for (int y{startY}; y < endY; y++)
		{
			Line2d line(lambdaGetPointOnLine(line1Start, line1End, y), lambdaGetPointOnLine(line2Start, line2End, y), color);
			line.draw(image);
		}
	};
	lambdaFillTrapezium(vertexWorld[0], vertexWorld[2], vertexWorld[0], vertexWorld[1], vertexWorld[0].y, vertexWorld[1].y, image, color);
	lambdaFillTrapezium(vertexWorld[0], vertexWorld[2], vertexWorld[2], vertexWorld[1], vertexWorld[1].y, vertexWorld[2].y, image, color);
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