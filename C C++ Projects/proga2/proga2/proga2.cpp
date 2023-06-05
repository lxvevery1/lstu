#include <iostream>
using namespace std;

class Matrix
{
private:
    int rows_, cols_;
    int** arr;

    void Swap(Matrix& M)
    {
        int t = rows_; rows_ = M.rows_; M.rows_ = t;
        t = cols_; cols_ = M.cols_; M.cols_ = t;
        int** p = arr; arr = M.arr; M.arr = p;
    }
    
public:

    Matrix(const int rows = 0, const int cols = 0) // Конструктор
    {
        
        rows_ = rows; cols_ = cols; arr = nullptr;
        if (rows_ && cols_)
        {
            arr = new int* [rows_];
            for (int i = 0; i < rows_; i++)
                arr[i] = new int[cols_];
        }
        cout << "Konstruktor" << endl;
    }
   
    Matrix(const Matrix& M) // Конструктор копирования
    {
        
        rows_ = M.rows_; cols_ = M.cols_; arr = nullptr;
        if (rows_ && cols_)
        {
            arr = new int* [rows_];
            for (int i = 0; i < rows_; i++)
            {
                arr[i] = new int[cols_];
                for (int j = 0; j < cols_; ++j)
                    arr[i][j] = M.arr[i][j];
            }
        }
        cout << "Copy Konstruktor" << endl;
    }

    ~Matrix()
    {
        
        if (arr != nullptr)
        {
            for (int i = 0; i < rows_; i++)
                delete arr[i];
            delete[] arr;
        }
        cout << "Destructor" << endl;
    }

    Matrix operator = (const Matrix M) // Пример перегрузки оператора = как метода класса
    {
        Matrix tmp(M);
        Swap(tmp);
        return *this; // Возвращает копию себя
    }

    int rows() const
    {
        return rows_;
    }

    int cols() const
    {
        return cols_;
    }

    int* operator[](int i) { return arr[i]; }
    const int* operator[](int i) const { return arr[i]; }
};

void Print(const Matrix& M) {
    for (int i = 0; i < M.rows(); i++)
    {
        for (int j = 0; j < M.cols(); j++)
            cout << M[i][j] << ' '; // []const
        cout << endl;
    }
    cout << endl;
}

void Input(Matrix& M) {
    for (int i = 0; i < M.rows(); i++)
    {
        for (int j = 0; j < M.cols(); j++) {
            M[i][j] = 1 + rand() % 9; // []
        }
    }
    cout << endl;
}

Matrix operator * (const Matrix& M, const int m) // Пример перегрузки оператора * как глобальной ф.
{
    Matrix temp(M.rows(), M.cols());
    for (int i = 0; i < M.rows(); i++)
    {
        for (int j = 0; j < M.cols(); j++)
        {
            temp[i][j] = M[i][j] * m; // [] = []const
        }
    }
    return temp;
}

int main() 
{
    srand(time(0));
    int b, a, a1;
    cout << "Input: multiplier, x, y: ";
    cin >> b >> a >> a1;
    
    Matrix A(a1, a), C; cout << "Obyavili matrici A(a1, a), C" << endl;
    cout << "Input matrix A( " << a1 << ',' << a << "): ";
    Input(A); cout << "Zainputili matricu A(a1, a)" << endl;

    cout << "A = " << endl;
    Print(A); cout << "Viveli matricu A" << endl;
    cout << "A*b = C" << endl;
    
    C = A * b; cout << "Poschitali C" << endl;

    Print(C);
    cout << "Viveli C" << endl;
    cout << endl;

    cout << "A = " << endl;
    Print(A);
    cout << "Viveli A" << endl;
    return 0;
}
