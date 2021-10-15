#include <iostream>

template <typename T>
class Grid {
private:
    T* memory;
    size_t x_size, y_size;

public:
    Grid(size_t x_size, size_t y_size): x_size(x_size), y_size(y_size)
    {
        memory = new T[x_size * y_size];
    }

    ~Grid()
    {
        delete[] memory;
    }

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
        return this->x_size;
    }
    
    size_t get_ysize() const
    {
        return this->y_size;
    }

    Grid& operator=(T A)
    {
        for (size_t i = 0; i < x_size * y_size; i++) {
            memory[i] = A;
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
    {
        for (size_t j = 0; j < gr.get_ysize(); j++)
        {
            T1 temp;
            is >> temp;
            gr(i, j) = temp;
        }
    }
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