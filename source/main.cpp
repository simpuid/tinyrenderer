#include <iostream>
#include <fstream>
#include <exception>
#include <string>
#include <image.hpp>
#include <memory>
#include <shapes.hpp>
#include <model.hpp>
#include <vector.hpp>
#include <matrix.hpp>
#include <cmath>
#include <camera.hpp>

using namespace std;

int main()
{
	cout << "run start\n";
	Image render{1000, 1000};
	ZBuffer buffer{render.width, render.height};
	Camera camera{Vector3f{0, 0, 0}, 3};
	Model model;
	model.loadFromFile("renders/african_head.obj");
	Image *texture = Image::readFromFile("renders/african_head_diffuse.ppm");
	buffer.reset();
	model.draw(render, *texture, buffer, camera.getTranformMatrix());
	delete texture;
	Image::writeToFile(render, "renders/test.ppm", true);
	cout << "run end" << endl;
}