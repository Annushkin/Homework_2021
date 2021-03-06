#include <iostream>
#include <map>

template <typename T>
class Grid {
private:
    T* memory;
    size_t x_size, y_size;
    std::map<size_t, Grid> SG = {};

public:

    Grid() : Grid(0, 0) { }
    Grid(size_t x_size, size_t y_size) : x_size(x_size), y_size(y_size), memory(new T[x_size * y_size]) { }

    ~Grid() { delete[] memory; }

    //конструктор копирования
    Grid(Grid const& src) : Grid(src.x_size, src.y_size)
    {
        for (size_t i = 0; i < x_size * y_size; i++)
            memory[i] = src.memory[i];
    }
   
    //Оператор копирующего присваивания
    Grid& operator=(Grid const& src)
    {
        Grid<T> tmp(src);
        std::swap(this->memory, tmp.memory);
        std::swap(this->x_size, tmp.x_size);
        std::swap(this->y_size, tmp.y_size);
        return *this;
    }
    //Оператор копирующего присваивания с одним параметром
    Grid& operator=(T a)
    {
        for (size_t i = 0; i < x_size * y_size; i++) {
            memory[i] = a;
        }
        return *this;
    }

    size_t get_xsize() const { return x_size; }

    size_t get_ysize() const { return y_size; }

   //Нахождение среднего арифметического
   T average()
    {
        T sum = 0;
        for (size_t i = 0; i < x_size * y_size; i++) {
            sum += memory[i];
        }
        return sum / (x_size * y_size);
    }

   
 //SubGrid//////////////////////////////////////////////  
    Grid<T>& make_subgrid(size_t x_idx, size_t y_idx, size_t x_sub_size, size_t y_sub_size)
    {      
        size_t key = x_idx * y_size + y_idx;      //ключ map равен индексу элемента в одномернм массиве
        Grid<T> SubGrid(x_sub_size, y_sub_size);  //Создаём подматрицу
        SubGrid = memory[key];                    //Заменяем элементы подматрицы на значение элемената родительской ячейки
       // if (is_subrid(x_idx, y_idx)) SG.erase(key); //Оператор копирующего присваивания перезапишет элементы
        SG.insert({ key, SubGrid });              //Добавляем подматрицу в map
        return *this;   
    }   

   bool is_subrid(size_t x_idx, size_t y_idx) const
   {
       size_t key = x_idx * y_size + y_idx;
       if (SG.find(key) != SG.end()) return true;
       else return false;
   }

    Grid<T>& collapse_subgrid(size_t x_idx, size_t y_idx)
    {
        size_t key = x_idx * y_size + y_idx;
        if (is_subrid(x_idx, y_idx)) {
        T av = SG[key].average();              //находим среднее значение элементов подматрицы
        memory[key] = av;                      //заменяем значение элемента в родительской ячейке на среднее подматрицы
        SG.erase(key);                         //удаляем подматрицу из map
        }
        return *this;
    }

    Grid<T>& get_subgrid(size_t x_idx, size_t y_idx)
    {
        size_t key = x_idx * y_size + y_idx;
        if (is_subrid(x_idx, y_idx)) return SG[key];
    }
  
//////////////////////////////////////////////////////////
    T operator()(size_t x_idx, size_t y_idx) const
    {
        //???В случае обращения к подсетке перегрузка для константного объекта возвращает копию среднего значения на сетке
        return memory[x_idx * y_size + y_idx];
    }

    T& operator()(size_t x_idx, size_t y_idx)
    { 
        return memory[x_idx * y_size + y_idx];
    }

    template <typename T1>friend std::ostream& operator<<(std::ostream&, Grid<T1> const&);
    template <typename T1>friend std::istream& operator>>(std::istream&, Grid<T1>&);
};

template <typename T1>
std::ostream& operator<<(std::ostream& os, Grid<T1> const& gr)
{

    for (size_t i = 0; i < gr.x_size; i++)
    {
        for (size_t j = 0; j < gr.y_size; j++)
        {
            if (gr.is_subrid(i, j))
                os << "SG ";
            else
                os << gr(i, j) << " ";
        }
        os << '\n';
    }
    os << '\n';
    return os;
}

template <typename T1>
std::istream& operator>>(std::istream& is, Grid<T1>& gr)
{
    for (size_t i = 0; i < gr.x_size; i++)    
        for (size_t j = 0; j < gr.y_size; j++)           
            is >> gr(i, j);    
    return is;
}

int main()
{
    Grid<int> G1(2, 3);
    std::cin >> G1;
    std::cout << '\n';
    std::cout << G1.average() << '\n' << '\n';
    G1.make_subgrid(1, 1, 3, 3);
    std::cout << G1.is_subrid(1, 1) << '\n' << '\n';
    std::cout << G1.get_subgrid(1, 1);
    G1.get_subgrid(1, 1) = 100;
    G1.get_subgrid(1, 1)(1, 2) = 56;
    std::cout << G1.get_subgrid(1, 1);
    G1.get_subgrid(1, 1) = 80;
    std::cout << G1.get_subgrid(1, 1);
    std::cout << G1;
    G1.collapse_subgrid(1, 1);
    std::cout << G1.is_subrid(1, 1) << '\n' << '\n';
    std::cout << G1; 
}
