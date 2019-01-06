#include <color.hpp>

Color::Color() : Color(0, 0, 0, 0) {}
Color::Color(byte r, byte g, byte b, byte a) : pixelData{r, g, b, a} {}
byte &Color::operator[](const int index)
{
	return pixelData[index];
}
Color Color::operator*(float factor)
{
	factor = factor < 0 ? 0 : (factor > 1 ? 1 : factor);
	return Color(pixelData[0] * factor, pixelData[1] * factor, pixelData[2] * factor, pixelData[3] * factor);
}