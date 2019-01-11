#include <camera.hpp>
#include <matrix.hpp>
#include <vector.hpp>
#include <iostream>

Camera::Camera(Vector3f position, Vector3f target, Vector3f up, Vector2f viewPortPosition, Vector3f viewPortDimension, float fov) : position{position}, target{target}, up{up}, viewPortPosition{viewPortPosition}, viewPortDimension{viewPortDimension}, fieldOfView{fov} {}
Matrixf<4, 4> Camera::getTranformMatrix()
{
	Matrixf<4, 4> persepective{{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, -1.0f / fieldOfView, 1}};
	Matrixf<4, 4> centerAdjustment{{1, 0, 0, -viewPortDimension.x * 0.5f, 0, 1, 0, -viewPortDimension.y * 0.5f, 0, 0, 1, -viewPortDimension.z * 0.5f, 0, 0, 0, 1}};
	Matrixf<4, 4> centerAdjustmentInverse{{1, 0, 0, viewPortDimension.x * 0.5f, 0, 1, 0, viewPortDimension.y * 0.5f, 0, 0, 1, viewPortDimension.z * 0.5f, 0, 0, 0, 1}};
	Matrixf<4, 4> identity{{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1}};
	Matrixf<4, 4> relativeToCamera{{1, 0, 0, -position.x, 0, 1, 0, -position.y, 0, 0, 1, -position.z, 0, 0, 0, 1}};
	Matrixf<4, 4> rotateWorld = getRotationMatrix();
	Matrixf<4, 4> viewPort{{viewPortDimension.x * 0.5f, 0, 0, viewPortPosition.x + viewPortDimension.x * 0.5f, 0, viewPortDimension.y * 0.5f, 0, viewPortPosition.y + viewPortDimension.y * 0.5f, 0, 0, viewPortDimension.z * 0.5f, viewPortDimension.z * 0.5f, 0, 0, 0, 1}};
	return centerAdjustmentInverse * persepective * rotateWorld * centerAdjustment * relativeToCamera * viewPort;
}
Matrixf<4, 4> Camera::getRotationMatrix()
{
	Vector3f z = (position - target).normalise();
	Vector3f x = (up ^ z).normalise();
	Vector3f y = z ^ x;
	return Matrixf<4, 4>{{x.x, x.y, x.z, 0, y.x, y.y, y.z, 0, z.x, z.y, z.z, 0, 0, 0, 0, 1}};
}
void Camera::setCameraParameters(Vector3f position, Vector3f target, Vector3f up)
{
	this->position = position;
	this->target = target;
	this->up = up;
}
void Camera::setViewPort(Vector2f viewPortPosition, Vector3f viewPortDimension)
{
	this->viewPortDimension = viewPortDimension;
	this->viewPortPosition = viewPortPosition;
}