#pragma once

class ZBuffer
{
  private:
	float *bufferData;

  public:
	const int width;
	const int height;

  public:
	ZBuffer(int width, int height);
	~ZBuffer();
	float getBuffer(int x, int y);
	bool setBuffer(int x, int y, float data);
	void reset();
};