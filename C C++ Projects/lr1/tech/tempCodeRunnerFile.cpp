#include <iostream>
#include <vector>
#include <list>

using namespace std;
template <typename T>
void Sort(vector<T>& array) {
    /**
    * T - это тип данных, могут быть любыми, лишь бы у них было поле key типа char
    **/
    char max = array.at(0).key;
    char min = array.at(0).key;
    for (const auto &x : array)
        if (x.key > max) max =  x.key;
        else if (x.key < min) min = x.key;
    // массив длиной max-min, каждый который содержит список элекментов с данным ключом    
    auto c = vector<list<T>>(max+1-min);
    for (const auto &x : array)
        c[x.key - min].push_back(x);
    // записываем обратно в массив array данные по порядку ключей    
    unsigned b = 0;
    for (const auto &lst : c)
        for (const auto & x: lst)
            array[b++] = x;
}

struct Data
{
    char key;
    string data;
    int info[2];
};

int main()
{
    //*int n = 3;
    system("chcp 1251 > nul");
    std::vector<Data> array {{'c', "раз", 123, 321}, {'a',"раз",123, 321}, {'b',"раз",123, 321}, {'D', "раз",123, 321}, {'b', "два",123, 321},
    {'D', "два", 123, 321}, {'b', "три", 123, 321}, {'Z', "раз", 123, 321}};
    
    Sort(array);
    for (const auto&item: array)
        std::cout << item.key << ": " << item.data << ", " << item.info[1] << "\n";
    return 0;
}