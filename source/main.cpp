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
	for (float i = 0; i < 8; i += 0.2f)
	{
		Image render{1080, 1080};
		ZBuffer buffer{render.width, render.height};
		Camera camera{{std::sin(i) * 100, 0, std::cos(i) * 100}, Vector3f{0, 0, 0}, Vector3f(0, 1, 0), Vector2f{0, 0}, Vector3f{float(render.width), float(render.height), float(render.height)}, float(800)};
		Model model("renders/african_head.obj");
		Image *texture = Image::readFromFile("renders/african_head_diffuse.ppm");
		buffer.reset();
		model.draw(render, *texture, buffer, camera.getTranformMatrix(), camera.getRotationMatrix(), (camera.position - camera.target).normalise());
		delete texture;
		Image::writeToFile(render, "renders/test.ppm", true);
	}
	cout << "run end" << endl;
}