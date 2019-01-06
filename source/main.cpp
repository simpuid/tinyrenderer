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

using namespace std;

int main()
{
	Matrixf<1, 3> vertices[3]{
		Matrixf<1, 3>{-0.3f, 0.3f, 1}, Matrixf<1, 3>{0.3f, 0.3f, 1}, Matrixf<1, 3>{0.3f, -0.3f, 1}};
	float angle = M_PI / float(16);
	float sinv{std::sin(angle)}, cosv{cos(angle)};
	Matrixf<3, 3> rotate({cosv, -sinv, 0, sinv, cosv, 0, 0, 0, 1});
	Matrixf<3, 3> translate({1, 0, -1, 0, 1, -1, 0, 0, 0});
	Image image(600, 600);
	Triangle3d triangle;
	cout << "run";
	for (int i = 0; i < 3; i++)
	{
		auto r = (translate * rotate * vertices[i]);
		triangle.vertices[i] = Vector3f(r.data(0, 0), r.data(0, 1), 0);
	}
	triangle.drawWireframe(image, Color{255, 255, 255, 255});
	Image::writeToFile(image, "wireframe.ppm", true);
	cout << "write";
}