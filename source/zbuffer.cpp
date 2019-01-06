#include <zbuffer.hpp>
#include <limits>

ZBuffer::ZBuffer(int width, int height) : width{width}, height{height}
{
	bufferData = new float[width * height];
	reset();
}
ZBuffer::~ZBuffer()
{
	delete[] bufferData;
}
float ZBuffer::getBuffer(int x, int y)
{
	if (x >= 0 && x < width && y >= 0 && y < height)
	{
		return bufferData[x + y * width];
	}
	return std::numeric_limits<float>::lowest();
}
bool ZBuffer::setBuffer(int x, int y, float data)
{
	if (x >= 0 && x < width && y >= 0 && y < height)
	{
		bufferData[x + y * width] = data;
		return true;
	}
	return false;
}
void ZBuffer::reset()
{
	float infinity = std::numeric_limits<float>::lowest();
	for (int i = 0; i < width * height; i++)
	{
		bufferData[i] = infinity;
	}
}
