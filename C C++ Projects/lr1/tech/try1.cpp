#include<iostream>
#include<iomanip>
#include <vector>
 
using namespace std;
 
typedef vector< vector<int> > MatrixInt;
 
int main() {
    size_t rows = 5, cols = 5;       // неконстантные переменные
    MatrixInt v(rows);
    for (auto &array : v)
        array.resize(cols);
 
    // присваивание значений
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j)
            v[i][j] = (i + 1) * 10 + (j + 1);
    }
 
    // вывод значений на консоль
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j)
            cout << setw(4) << v[i][j];
        cout << endl;
    }
}