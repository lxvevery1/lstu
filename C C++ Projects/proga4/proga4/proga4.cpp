#include <iostream>
#include <vector>
using namespace std;

template <class T>
class Matrix
{
private:
    int rows_, cols_;
    double** arr;

    void Swap(Matrix<T>& M)
    {
        int t = rows_; rows_ = M.rows_; M.rows_ = t;
        t = cols_; cols_ = M.cols_; M.cols_ = t;
        double** p = arr; arr = M.arr; M.arr = p;
    }

public:

    Matrix(const int rows = 0, const int cols = 0) // Конструктор
    {

        rows_ = rows; cols_ = cols; arr = nullptr;
        if (rows_ && cols_)
        {
            arr = new double* [rows_];
            for (int i = 0; i < rows_; i++)
                arr[i] = new double[cols_];
        }
    }

    Matrix(const Matrix<T>& M) // Конструктор копирования
    {

        rows_ = M.rows_; cols_ = M.cols_; arr = nullptr;
        if (rows_ && cols_)
        {
            arr = new double* [rows_];
            for (int i = 0; i < rows_; i++)
            {
                arr[i] = new double[cols_];
                for (int j = 0; j < cols_; ++j)
                    arr[i][j] = M.arr[i][j];
            }
        }
    }

    ~Matrix()
    {

        if (arr != nullptr)
        {
            for (int i = 0; i < rows_; i++)
                delete arr[i];
            delete[] arr;
        }
    }

    Matrix operator = (const Matrix<T> M) // Пример перегрузки оператора = как метода класса
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

    

    double* operator[](int i) { return arr[i]; }
    const double* operator[](int i) const { return arr[i]; }
};
template<class T>
void Print(const Matrix<T>& M) {
    for (int i = 0; i < M.rows(); i++)
    {
        for (int j = 0; j < M.cols(); j++)
            cout << M[i][j] << ' '; // []const
        cout << endl;
    }
    cout << endl;
}


template<class T>
Matrix<T> operator -(const Matrix<T>& M1, const Matrix<T>& M2) // Пример перегрузки оператора - как глобальной ф.
{
    Matrix<T> temp(M1.rows(), M1.cols());
    for (int i = 0; i < M1.rows(); i++)
    {
        for (int j = 0; j < M1.cols(); j++)
        {
            temp[i][j] = M1[i][j] - M2[i][j]; // [] = []const
        }
    }
    return temp;
}

class Dekart
{
public:
    double x{ 0 }, y{ 0 }, z{ 0 };
    Dekart() 
    {
        this->x = 0;
        this->y = 0;
        this->z = 0;
    }
    // конструктор с двумя параметрами для создания вектора;
    // у любого вектора на плоскости имеются две координаты,
    // которые равны координатам конечной точки вектора,
    // если переместить начальную точку вектора в точку (0, 0)
    Dekart(double x, double y)
    {
        this->x = x;
        this->y = y;
        z = NULL;
    }
    // конструктор, в который передаются координаты трех точек:
    // координаты начальной точки вектора и координата конечной точки вектора;
    // данная функция как бы "перемещает" начальную точку вектора в точку (0, 0, 0)
    Dekart(double x, double y, double z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    void printCoordinates()
    {
        cout << "Vector coordinates: x = " << x << ", y = " << y << endl;
    }
    static Dekart rand_value() {
        Dekart D;
        D.x = 1 + rand() % 9;
        D.y = 1 + rand() % 9;
        D.z = 1 + rand() % 9;
        return D;
    }
    Dekart operator =(Dekart& other) {

        return Dekart(this->x = other.x, this->y = other.y, this->z = other.z);
    }
    Dekart operator -(Dekart& other) {
        return Dekart(this->x - other.x, this->y - other.y, this->z - other.z);
    }
};

template<class T>
void Input(Matrix<T>& M) {
    Dekart D(3.56, 4.5, 7.8);
    D.printCoordinates();
    for (int i = 0; i < M.rows(); i++)
    {
        for (int j = 0; j < M.cols(); j++) {
            M[i][j] = T::rand_val();
        }
    }
    cout << endl;
}

int main()
{
    srand(time(0));
    int a, a1, b, b1;
    cout << "Input: (x1, y1; x2, y2): ";
    cin >> a >> a1 >> b >> b1;

    Matrix<Dekart> A(a1, a), B(b1, b), C; 
    cout << "Obyavili matrici A(a1, a), B(b1, b), C" << endl;
    cout << "Input matrix A( " << a1 << ',' << a << "): "; Input(A);
    cout << "Input matrix B( " << b1 << ',' << b << "): "; Input(B);

    cout << "A = " << endl; Print(A);
    cout << "B = " << endl; Print(B);

    cout << "C = " << endl; C = A - B;

    Print(C);

    return 0;
}
