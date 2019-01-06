#pragma once
using byte = unsigned char;

struct Color
{
  private:
	byte pixelData[4];

  public:
	Color();
	Color(byte r, byte g, byte b, byte a);
	byte &operator[](const int index);
	Color operator*(float factor);
};