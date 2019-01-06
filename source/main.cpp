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
	Image img(1000, 1000);
	ZBuffer buff(img.width, img.height);
	Model m;
	m.loadFromFile("african_head.obj");
	m.draw(img, buff);
	Image::writeToFile(img, "wireframe.ppm", true);
	return 0;
}