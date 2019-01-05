#pragma once
#include <image.hpp>
#include <vector.hpp>

struct Line2d
{
	Vector2i start;
	Vector2i end;
	Color color;
	Line2d(Vector2i start, Vector2i end, Color color);
	void draw(Image &image);
};
struct Triangle3d
{
  public:
	Vector3f vertices[3];
	Vector3f normals[3];
	Vector2f textureCordinates[3];

  public:
	void draw(Image &image, Color color);
	void drawWireframe(Image &Image, Color color);
};