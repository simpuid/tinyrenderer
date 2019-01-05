#pragma once
#include <iostream>
#include <cmath>

template <class T>
struct Vector2
{
  public:
	T x;
	T y;

  public:
	Vector2() : x{0}, y{0} {};
	Vector2(T x, T y) : x{x}, y{y} {};
	Vector2<T> operator+(Vector2<T> other) { return Vector2<T>(x + other.x, y + other.y); }
	Vector2<T> operator-(Vector2<T> other) { return Vector2<T>(x - other.x, y - other.y); }
	T operator*(Vector2<T> other) { return (x * other.x + y * other.y); }
	Vector2<T> operator*(float f) { return Vector2<T>(x * f, y * f); }
	float magnitude() { return std::sqrt(x * x + y * y); };
	T squareMagnitude() { return (x * x + y * y); }
	Vector2<T> normalise(T length = 1) { return (*this = (*this) * (length / magnitude())); }
};
template <class T>
struct Vector3
{
  public:
	T x;
	T y;
	T z;

  public:
	Vector3() : x{0}, y{0}, z{0} {};
	Vector3(T x, T y, T z) : x{x}, y{y}, z{z} {};
	Vector3<T> operator+(Vector3<T> other) { return Vector3<T>(x + other.x, y + other.y, z + other.z); }
	Vector3<T> operator-(Vector3<T> other) { return Vector3<T>(x - other.x, y - other.y, z - other.z); }
	T operator*(Vector3<T> other) { return (x * other.x + y * other.y + z * other.z); }
	Vector3<T> operator*(float f) { return Vector3<T>(x * f, y * f, z * f); }
	Vector3<T> operator^(Vector3<T> other) { return Vector3<T>(y * other.z - other.y * z, z * other.x - x * other.z, x * other.y - other.x * y); }
	float magnitude() { return std::sqrt(x * x + y * y + z * z); };
	T squareMagnitude() { return (x * x + y * y + z * z); }
	Vector2<T> normalise(T length = 1) { return (*this = (*this) * (length / magnitude())); }
};
template <class T>
std::ostream &operator<<(std::ostream &stream, Vector2<T> vector2)
{
	stream << '(' << vector2.x << ',' << vector2.y << ')';
	return stream;
}
template <class T>
std::ostream &operator<<(std::ostream &stream, Vector3<T> vector3)
{
	stream << '(' << vector3.x << ',' << vector3.y << ',' << vector3.z << ')';
	return stream;
}
typedef Vector2<int> Vector2i;
typedef Vector2<float> Vector2f;
typedef Vector3<int> Vector3i;
typedef Vector3<float> Vector3f;
