#pragma once
#include <vector.hpp>
#include <matrix.hpp>
typedef Matrix<4, 4, float> TransformMatrix;
class Camera
{
  public:
	Vector3f position;
	float fieldOfView;

  public:
	Camera(Vector3f pos, float fov);
	TransformMatrix getTranformMatrix();
};