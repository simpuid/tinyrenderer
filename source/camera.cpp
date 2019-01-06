#include <camera.hpp>
#include <matrix.hpp>
#include <vector.hpp>

Camera::Camera(Vector3f pos, float fov)
{
	this->position = pos;
	this->fieldOfView = fov;
}
Matrixf<4, 4> Camera::getTranformMatrix()
{
	Matrixf<4, 4> prospective{{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, -1.0f / fieldOfView, 1}};
	return prospective;
}