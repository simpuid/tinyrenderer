#include <iostream>
#include <fstream>
#include <exception>
#include <string>
#include <image.hpp>
#include <memory>
#include <shapes.hpp>
#include <model.hpp>
#include <vector.hpp>

using namespace std;

void drawWireframe(Model &model, Image &image)
{
	for (int i = 0; i < model.getTraingleCount(); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			Triangle3d triangle = model.getTriangle(i);
			triangle.drawWireframe(image, Color(255, 255, 255, 255));
			/*
			Vector3f v1 = triangle.vertices[j];
			Vector3f v2 = triangle.vertices[(j + 1) % 3];
			int x1 = (v1.x + 1) * image.width * 0.5f;
			int y1 = (v1.y + 1) * image.height * 0.5f;
			int x2 = (v2.x + 1) * image.width * 0.5f;
			int y2 = (v2.y + 1) * image.height * 0.5f;
			Line2d line(Vector2i(x1, y1), Vector2i(x2, y2), Color(255, 255, 255, 255));
			line.draw(image);*/
		}
	}
}

int main()
{
	try
	{
		Model *m = new Model();
		m->loadFromFile("african_head.obj");
		Image *img = new Image(2560, 2560);

		drawWireframe(*m, *img);
		Image::writeToFile(*img, "wireframe.ppm", true);
	}
	catch (exception e)
	{
		std::cerr << e.what();
	}
	return 0;
}