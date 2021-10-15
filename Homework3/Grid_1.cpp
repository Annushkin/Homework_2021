#include<iostream>

template <typename T>
class Grid
{
private:
	T** memory;
	size_t x_size, y_size;

public:
	Grid(size_t x_size, size_t y_size) : x_size(x_size), y_size(y_size)
	{
		memory = new T* [x_size];
		for (size_t i = 0; i < x_size; i++)
			memory[i] = new T[y_size];

		for (size_t i = 0; i < x_size; i++)
			for (size_t j = 0; j < y_size; j++)
				memory[i][j] = 0;
	}

	size_t get_xsize() const
	{
		return x_size;
	}

	size_t get_ysize() const
	{
		return y_size;
	}

	T operator()(size_t x_idx, size_t y_idx) const
	{
		std::cout << memory[x_idx][y_idx] << '\n';
	}

	T& operator()(size_t x_idx, size_t y_idx, T a)
	{
		return memory[x_idx][y_idx] = a;
	}

	~Grid()
	{
		for (size_t i = 0; i < x_size; ++i)
			delete[] memory[i];
		delete[] memory;
	}

	Grid operator=(T a)
	{
		for (size_t i = 0; i < this->x_size; ++i)
			delete[] this->memory[i];
		delete[] this->memory;

		this->x_size = x_size;
		this->y_size = y_size;

		this->memory = new T* [x_size];
		for (size_t i = 0; i < x_size; ++i)
			this->memory[i] = new T[y_size];

		for (size_t i = 0; i < x_size; i++)
			for (size_t j = 0; j < y_size; j++)
				this->memory[i][j] = a;
		return *this;
	}

	template <typename T1> friend std::ostream& operator << (std::ostream& os, Grid<T1>& memory);
	template <typename T1> friend std::istream& operator >> (std::istream& is, Grid<T1>& memory);
};

template <typename T1>
std::ostream& operator<<(std::ostream& os, Grid<T1>& memory)
{
	for (size_t i = 0; i < memory.x_size; i++)
	{
		for (size_t j = 0; j < memory.y_size; j++)
			os << memory.memory[i][j] << " ";
		std::cout << '\n';
	}
	std::cout << '\n';
	return os;
}

template <typename T1>
std::istream& operator >> (std::istream& is, Grid<T1>& memory)
{
	for (size_t i = 0; i < memory.x_size; i++)
		for (size_t j = 0; j < memory.y_size; j++)
			is >> memory.memory[i][j];

	return is;
}

int main()
{
	Grid <float>G1(2, 2);
	G1 = 4;
	std::cout << G1 << '\n';

	Grid <int>G2(2, 3);
	std::cin >> G2;
	std::cout << '\n' << G2;

	G2(0, 1);
	G2(0, 1, 25);
	std::cout << '\n' << G2;
}
