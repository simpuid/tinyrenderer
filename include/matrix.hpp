#include <initializer_list>
template <unsigned int width, unsigned int height, class T>
struct Matrix
{
  private:
	T storageData[width * height];

  public:
	Matrix() {}
	Matrix(const std::initializer_list<T> &value)
	{
		int i = 0;
		for (T v : value)
		{
			storageData[i] = v;
			i++;
		}
	}
	T &data(int x, int y)
	{
		return storageData[x + y * width];
	}
	Matrix<width, height, T> operator+(Matrix<width, height, T> other)
	{
		Matrix<width, height, T> r;
		for (unsigned int x = 0; x < width; x++)
		{
			for (unsigned int y = 0; y < height; y++)
			{
				r.data(x, y) = data(x, y) + other.data(x, y);
			}
		}
		return r;
	}
	Matrix<width, height, T> operator-(Matrix<width, height, T> other)
	{
		Matrix<width, height, T> r;
		for (unsigned int x = 0; x < width; x++)
		{
			for (unsigned int y = 0; y < height; y++)
			{
				r.data(x, y) = data(x, y) - other.data(x, y);
			}
		}
		return r;
	}
	template <class T2>
	Matrix<width, height, T> operator*(T2 other)
	{
		for (unsigned int i{0}; i < width * height; i++)
		{
			storageData[i] *= other;
		}
	}
	template <unsigned int width2>
	Matrix<width2, height, T> operator*(Matrix<width2, width, T> other)
	{
		Matrix<width2, height, T> r;
		for (unsigned int row{0}; row < height; row++)
		{
			for (unsigned int column{0}; column < width2; column++)
			{
				T sum = 0;
				for (unsigned int parameter{0}; parameter < width; parameter++)
				{
					sum += data(parameter, row) * other.data(column, parameter);
				}
				r.data(column, row) = sum;
			}
		}
		return r;
	}
};

template <unsigned int width, unsigned int height>
using Matrixi = Matrix<width, height, int>;
template <unsigned int width, unsigned int height>
using Matrixf = Matrix<width, height, float>;
