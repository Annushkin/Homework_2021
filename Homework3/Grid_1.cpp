#include <iostream>

template <typename T>
class Grid {
private:
    T* memory;
    size_t x_size, y_size;

public:
    Grid() : Grid(0, 0) { }
    Grid(size_t x_size, size_t y_size): x_size(x_size), y_size(y_size), memory(new T[x_size * y_size]) { }

    Grid(Grid const& cgr) : Grid(cgr.x_size, cgr.y_size)
    {
        for (size_t i = 0; i < x_size * y_size; i++)
            memory[i] = cgr.memory[i];
    }
    
    ~Grid() { delete[] memory; }

    T operator()(size_t x_idx, size_t y_idx) const
    {
        return memory[x_idx * y_size + y_idx];
    }

    T& operator()(size_t x_idx, size_t y_idx)
    {
        return memory[x_idx * y_size + y_idx];
    }

    size_t get_xsize() const
    {
        return x_size;
    }
    
    size_t get_ysize() const
    {
        return y_size;
    }

    Grid& operator=(Grid const& cgr)
    {
        Grid<T> tmp(cgr);
        std::swap(this->memory, tmp.memory);
        std::swap(this->x_size, tmp.x_size);
        std::swap(this->y_size, tmp.y_size);
        return *this;
    }
    
    Grid& operator=(T a)
    {
        for (size_t i = 0; i < x_size * y_size; i++) {
            memory[i] = a;
        }
        return *this;
    }

    template <typename T1>friend std::ostream& operator<<(std::ostream&, Grid<T1> const&);
    template <typename T1>friend std::istream& operator>>(std::istream&, Grid<T1>&);
};

template <typename T1>
std::ostream& operator<<(std::ostream& os, Grid<T1> const& gr)
{
  
    for (size_t i = 0; i < gr.get_xsize(); i++)
    {
        for (size_t j = 0; j < gr.get_ysize(); j++)        
            os << gr(i, j) << " ";         
        os << '\n';
    }
    os << '\n';
    return os;
}

template <typename T1>
std::istream& operator>>(std::istream& is, Grid<T1> & gr)
{
    for (size_t i = 0; i < gr.get_xsize(); i++)    
        for (size_t j = 0; j < gr.get_ysize(); j++)
            is >> gr(i, j);    
    return is;
}


int main()
{    
    Grid<float> G1(3, 4); 
    G1 = 4.1f;
    std::cout << G1 << '\n';    
    G1(1, 3) = 25.5;
    std::cout << G1 << '\n';
    
    Grid<int> G2(2, 3);
    std::cin >> G2;
    std::cout << '\n' << G2(1, 2) << '\n';
    std::cout << '\n' << G2 << '\n';
}
