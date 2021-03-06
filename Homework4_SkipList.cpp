#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <iomanip>

template<typename T, typename U>
class SkipList {
private:

    //Узел
    struct SkipNode {
        T key;
        U value;
        std::vector<SkipNode*> forward;

        SkipNode(T key, U value, int level): key(key), value(value), forward(level, nullptr) {}
    };

    SkipNode* head; //указатель на первый узел
    SkipNode* NIL;  //последний узел
    const float probability;
    const int maxLevel;

    //Генератор случайных чисел для создания уровня узла в диапазоне [1, maxLevel]   
    int randomLevel() const {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distr(0, 1);
        int level = 0;       
        while (distr(gen) < probability and level < head->forward.size()) {
            level++;
        }
        return level;
    }

public:
  
    SkipList() : probability(0.25), maxLevel(16)
    {
        //constexpr - значение вычисляется во время компиляции
        //Создаём узел head, присваиваем ему минимальное мозможное значение
        constexpr T headKey = std::numeric_limits<T>::min();
        head = new SkipNode(headKey, 0, maxLevel);

        //Создаём узел NIL, присваиваем ему максимальное возможное значение
        constexpr T nilKey = std::numeric_limits<T>::max();
        NIL = new SkipNode(nilKey, 10000, maxLevel);
        
        //делаем все указатели от head в NIL
        std::fill(head->forward.begin(), head->forward.end(), NIL);
        //for (size_t i = 0; i < head->forward.size(); ++i) {
        //    head->forward[i] = NIL;
        //}
    }

      ~SkipList()
    {
        SkipNode* node = head->forward[0];
       //Удаляет узлы
        while (node != NIL) {
            SkipNode* temp = node;
            node = node->forward[0];
            delete temp;
        }
        delete head;
        delete NIL;
        std::cout << "\nSkipList is delete\n";
    }

    bool empty() const {
        if (head->forward[0] == NIL) return true;
        else return false;
    }

    //Поиск по ключу. Возвращает указатель на найденный узел.
    SkipNode* find(T searchKey) {
        SkipNode* node = head;        
        for (size_t i = head->forward.size(); i-- > 0;) {
            while (node->forward[i]->key < searchKey) {
                node = node->forward[i];
            }
        }
        node = node->forward[0];
        if (node->key == searchKey) return node;
        else return nullptr;
    }
   
    //Вставка по ключу
    void insert(T searchKey, const U& newValue) {
        //Поиск места вставки. В векторе update сохряняются элементы перед вставляемым
        std::vector<SkipNode*> update(head->forward.size(), nullptr);
        SkipNode* node = head;
        for (size_t i = head->forward.size(); i-- > 0;) {
            while (node->forward[i]->key < searchKey) {
                node = node->forward[i];
            }
            update[i] = node;   
        }
        node = node->forward[0];        
        //Создание нового узла
        const int newNodeLevel = randomLevel();
        auto newNodePtr = new SkipNode(searchKey, newValue, newNodeLevel);
        // создание указателей для нового узла
        for (size_t i = 0; i < newNodeLevel; ++i) {
            newNodePtr->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNodePtr;
        }
    }

    //Удаляет элемент по ключу, если он есть. 
    void erase(T searchKey) {
        std::vector<SkipNode*> update(head->forward.size(), nullptr);
        SkipNode* node = head;
        for (size_t i = head->forward.size(); i-- > 0;) {
            while (node->forward[i]->key < searchKey) {
                node = node->forward[i];
            }
            update[i] = node;
        }
        node = node->forward[0];
        //проверяет существование узла
        SkipNode* node_x = update[0]->forward[0];
        if (node_x->key != searchKey) {
            return;
        }
        // обновляет указатели и удаляет узел
        for (size_t i = 0; i < node->forward.size(); ++i) {
            update[i]->forward[i] = node->forward[i];
        }
        delete node;
        std::cout << "\nNode with key " << searchKey << " is deleted\n";
    }

    //Печатает ключ, значение, уровень каждого узла
    void print() const {
        SkipNode* list = head->forward[0];
        std::cout << "\n{\n";
        while (list != NIL) {
            std::cout  << std::setw(4) << "value: " << std::setw(3) << list->value  << std::right
                       << std::setw(4) << "  key: " << std::setw(3) << list->key  << std::right
                       << std::setw(4) << "  level: " << std::setw(3) << list->forward.size() << '\n';
            list = list->forward[0];
        }
        std::cout << "}\n" << '\n';
    }
};


int main() {

    //Создаём объект класса
    SkipList<int, int> s;

    //Проверка на пустоту
    if(s.empty())
        std::cout << "List is empty" << '\n';
    else 
        std::cout << "List is NOT empty" << '\n';

    //Вставка (заполенние)
    for (int i = 0; i < 10; ++i) {
        s.insert(i, i*2);
    }
    s.print();

    //Проверка на пустоту
    if (s.empty())
        std::cout << "List is empty" << '\n';
    else
        std::cout << "List is NOT empty" << '\n';

    //Поиск  
    int key1 = 5;
    int key2 = 100;
    if (s.find(key1)) std::cout << "Node with key " << key1 << " found!\n";
    else std::cout << "Node with key " << key1 << " NOT found!\n";
        
    if (s.find(key2)) std::cout << "Node with key " << key2 << " found!\n";
    else std::cout << "Node with key " << key2 << " NOT found!\n";

    //Вставка
    s.insert(20, 500);
    s.print();

    s.insert(1, 600);
    s.print();
 
    //Удаление
    s.erase(20);
    s.print();
}
