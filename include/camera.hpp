#pragma once
#include <vector.hpp>
#include <matrix.hpp>
typedef Matrix<4, 4, float> TransformMatrix;
class Camera
{
  public:
	Vector3f position;
	Vector3f target;
	Vector3f up;
	Vector2f viewPortPosition;
	Vector3f viewPortDimension;
	float fieldOfView;

  public:
	Camera(Vector3f position, Vector3f target, Vector3f up, Vector2f viewPortPositon, Vector3f viewPortDimension, float fov);
	TransformMatrix getTranformMatrix();
	void setCameraParameters(Vector3f position, Vector3f target, Vector3f up);
	void setViewPort(Vector2f viewPortPositon, Vector3f viewPortDimension);
	Matrixf<4, 4> getRotationMatrix();
};