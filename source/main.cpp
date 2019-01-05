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
	Image img(2000, 2000);
	Model m;
	m.loadFromFile("african_head.obj");
	m.draw(img);
	Image::writeToFile(img, "wireframe.ppm", true);
	return 0;
}