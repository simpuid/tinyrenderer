#include <image.hpp>
#include <color.hpp>
#include <exception>
#include <fstream>
#include <iostream>
#include <cmath>
#include <limits>

Image::Image(int width, int height) : width(width), height(height), colorMap(new Color[width * height]) {}
Image::~Image()
{
	delete[] colorMap;
}
Color Image::getColor(int x, int y)
{
	if (x < width && x >= 0 && y < height && y >= 0)
	{
		return colorMap[(x) + y * width];
	}
	return Color();
}
bool Image::setColor(int x, int y, Color color)
{
	if (x < width && x >= 0 && y < height && y >= 0)
	{
		colorMap[(x) + y * width] = color;
		return true;
	}
	return false;
}
void readDataAscii(std::ifstream &file, Image &image)
{
	for (int y = 0; y < image.height; y++)
	{
		for (int x = 0; x < image.width; x++)
		{
			int r{0}, g{0}, b{0};
			file >> r >> g >> b;
			image.setColor(x, image.height - 1 - y, Color(r, g, b, 255));
			if (file.fail())
			{
				throw std::ios_base::failure("file data insufficient");
			}
		}
	}
}
void readDataRaw(std::ifstream &file, Image &image)
{
	char *inputData = new char[image.width * image.height * 3];
	file.read(inputData, image.width * image.height * 3);
	if (file.fail())
	{
		delete[] inputData;
		throw std::ios_base::failure("file data insufficient");
	}
	for (int y = 0; y < image.height; y++)
	{
		for (int x = 0; x < image.width; x++)
		{
			int index = (x + y * image.width) * 3;
			image.setColor(x, image.height - 1 - y, Color((byte)inputData[index + 0], (byte)inputData[index + 1], (byte)inputData[index + 2], 255));
		}
	}
	delete[] inputData;
}
void writeDataAscii(std::ofstream &file, Image &image)
{
	for (int y = 0; y < image.height; y++)
	{
		for (int x = 0; x < image.width; x++)
		{
			Color color = image.getColor(x, image.height - 1 - y);
			file << (int)color[0] << ' ' << (int)color[1] << ' ' << (int)color[2] << '\n';
		}
		if (file.fail())
		{
			throw std::ios_base::failure("file write error");
		}
	}
}
void writeDataRaw(std::ofstream &file, Image &image)
{
	byte *arrayToWrite = new byte[image.width * image.height * 3];
	for (int y = 0; y < image.height; y++)
	{
		for (int x = 0; x < image.width; x++)
		{
			Color color = image.getColor(x, y);
			for (int i = 0; i < 3; i++)
			{
				arrayToWrite[(x + (image.height - 1 - y) * image.width) * 3 + i] = color[i];
			}
		}
	}
	file.write(reinterpret_cast<char const *>(arrayToWrite), image.width * image.height * 3);
	if (file.fail())
	{
		delete[] arrayToWrite;
		throw std::ios_base::failure("file write error");
	}
	delete[] arrayToWrite;
}
void Image::writeToFile(Image &image, std::string path, bool isRaw)
{
	std::ofstream file;
	file.open(path, std::ios::binary | std::ios::out);
	if (!file)
	{
		file.close();
		throw std::ios_base::failure("file open error");
	}
	file << (isRaw ? "P6" : "P3") << '\n';
	file << image.width << ' ' << image.height << '\n';
	file << "255\n";
	if (isRaw)
		writeDataRaw(file, image);
	else
		writeDataAscii(file, image);
	if (file.fail())
	{
		file.close();
		throw std::ios_base::failure("file operation failed");
	}
	file.close();
}
Image *Image::readFromFile(std::string path)
{
	Image *image = nullptr;
	std::ifstream file;
	file.open(path);
	if (!file)
	{
		file.close();
		throw std::ios_base::failure("file open error");
	}
	auto lambdaSkipComments = [&file]() mutable {
		int nextCharacter{file.peek()};
		while ((nextCharacter == '#') || (nextCharacter == '\n') || (nextCharacter == ' '))
		{
			if (nextCharacter == ' ' || nextCharacter == '\n')
				file.ignore(1);
			else
				file.ignore(1024, '\n');
			nextCharacter = file.peek();
		}
		if (file.fail())
		{
			file.close();
			throw std::ios_base::failure("file read error");
		}
	};
	std::string header{""};
	file >> header;
	if (header != "P6" && header != "P3")
	{
		file.close();
		throw std::ios_base::failure("file header parse error");
	}
	lambdaSkipComments();
	int width{0}, height{0}, range{0};
	file >> width;
	lambdaSkipComments();
	file >> height;
	lambdaSkipComments();
	file >> range;
	lambdaSkipComments();
	image = new Image(width, height);
	try
	{
		if (header == "P6")
			readDataRaw(file, *image);
		else
			readDataAscii(file, *image);
	}
	catch (std::exception e)
	{
		file.close();
		delete image;
		throw e;
	}
	file.close();
	return image;
}