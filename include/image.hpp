#pragma once
#include <string>
#include <color.hpp>

class Image
{
  public:
	const int width;
	const int height;

  private:
	Color *colorMap;

  public:
	Image(int width, int height);
	Color getColor(int x, int y);
	bool setColor(int x, int y, Color color);
	~Image();

  public:
	static void writeToFile(Image &image, std::string path, bool raw);
	static Image *readFromFile(std::string path);
};