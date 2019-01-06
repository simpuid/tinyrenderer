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

int main()
{
	Image *texture = Image::readFromFile("african_head_diffuse.ppm");
	Image image(1000, 1000);
	ZBuffer buff(image.width, image.height);
	Model m;
	m.loadFromFile("african_head.obj");
	m.draw(image, *texture, buff);
	Image::writeToFile(image, "wireframe.ppm", true);
	return 0;
}