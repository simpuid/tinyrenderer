#pragma once
#include <memory>
#include <string>
#include <fstream>

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
	void flipVertically();
	~Image();

  public:
	static void writeToFile(Image &image, std::string path, bool raw);
	static Image *readFromFile(std::string path);

  private:
	static void readDataAscii(std::ifstream &file, Image &image);
	static void readDataRaw(std::ifstream &file, Image &image);
	static void writeDataAscii(std::ofstream &file, Image &image);
	static void writeDataRaw(std::ofstream &file, Image &image);
};