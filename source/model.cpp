#include <model.hpp>
#include <color.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <zbuffer.hpp>
#include <iostream>

Model::Model() : vertexList{new std::vector<Vector3f>()}, normalList{new std::vector<Vector3f>()}, textureList{new std::vector<Vector2f>()}, triangleList{new std::vector<Model::IndexedTriangle>()}
{
	vertexList = new std::vector<Vector3f>();
	normalList = new std::vector<Vector3f>();
	textureList = new std::vector<Vector2f>();
	triangleList = new std::vector<Model::IndexedTriangle>();
}
Model::~Model()
{
	vertexList->clear();
	normalList->clear();
	textureList->clear();
	triangleList->clear();
	delete vertexList;
	delete normalList;
	delete textureList;
	delete triangleList;
}
Model::Model(std::string path) : vertexList{new std::vector<Vector3f>()}, normalList{new std::vector<Vector3f>()}, textureList{new std::vector<Vector2f>()}, triangleList{new std::vector<Model::IndexedTriangle>()}
{
	std::ifstream file;
	file.open(path);
	std::string header;
	while (!file.eof())
	{
		file >> header;
		if (header == "v")
		{
			float x, y, z;
			file >> x >> y >> z;
			vertexList->push_back((Vector3f(x, y, z)));
		}
		else if (header == "vt")
		{
			float x, y, z;
			file >> x >> y >> z;
			textureList->push_back(Vector2f(x, y));
		}
		else if (header == "vn")
		{
			float x, y, z;
			file >> x >> y >> z;
			normalList->push_back(Vector3f(x, y, z));
		}
		else if (header == "f")
		{
			IndexedTriangle triangle;
			for (int i = 0; i < 3; i++)
			{
				file >> triangle.vertexIndex[i];
				file.ignore(1);
				file >> triangle.textureIndex[i];
				file.ignore(1);
				file >> triangle.normalIndex[i];
			}
			triangleList->push_back(triangle);
		}
		else
		{
			file.ignore(1024 * 1024 * 1024 /* some big number */, '\n');
		}
	}
	file.close();
}
int Model::getTraingleCount()
{
	return triangleList->size();
}
Triangle3d Model::getTriangle(int index)
{
	Triangle3d triangle;
	for (int i = 0; i < 3; i++)
	{
		triangle.vertices[i] = (*vertexList)[(*triangleList)[index].vertexIndex[i] - 1];
		triangle.textureCordinates[i] = (*textureList)[(*triangleList)[index].textureIndex[i] - 1];
		triangle.normals[i] = (*normalList)[(*triangleList)[index].normalIndex[i] - 1];
	}
	return triangle;
}
void Model::drawWireframe(Image &image)
{
	for (int i = 0; i < getTraingleCount(); i++)
	{
		Triangle3d triangle = getTriangle(i);
		Color color(rand() % 255, rand() % 255, rand() % 255, 255);
		triangle.drawWireframe(image, color);
	}
}
void Model::draw(Image &image, Image &texture, ZBuffer &zBuffer, TransformMatrix matrix, TransformMatrix normalMatrix, Vector3f lightDirection)
{
	for (int i = 0; i < getTraingleCount(); i++)
	{
		Triangle3d triangle = getTriangle(i);
		Vector3f calculatedNormal = ((triangle.vertices[1] - triangle.vertices[0]) ^ (triangle.vertices[2] - triangle.vertices[0])).normalise();
		float intensity = calculatedNormal * lightDirection;
		triangle.draw(image, texture, zBuffer, matrix, lightDirection);
	}
}