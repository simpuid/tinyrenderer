#pragma once
#include <vector>
#include <string>
#include <vector.hpp>
#include <shapes.hpp>
#include <image.hpp>
#include <zbuffer.hpp>
#include <camera.hpp>

class Model
{
  private:
	struct IndexedTriangle
	{
		int vertexIndex[3];
		int textureIndex[3];
		int normalIndex[3];
	};

  private:
	std::vector<Vector3f> *vertexList;
	std::vector<Vector3f> *normalList;
	std::vector<Vector2f> *textureList;
	std::vector<Model::IndexedTriangle> *triangleList;

  public:
	Model();
	~Model();
	void loadFromFile(std::string path);
	Triangle3d getTriangle(int index);
	int getTraingleCount();
	void drawWireframe(Image &image);
	void draw(Image &image, Image &texture, ZBuffer &zbuffer, TransformMatrix matrix);
};