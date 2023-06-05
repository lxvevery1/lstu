#include <iostream>
using namespace std;

class Zero : public exception { //ввод нуля
public:
    Zero(const char* message) : exception(message) {}
};

class Invalid : public exception { //ввод неверного значения
public:
    Invalid(const char* message) : exception(message) {}
};

class Scanner {
public:
    void get(int& x) {
        while (1) {
            try
            {
                cin >> x;
                if (cin.fail())
                    throw Invalid("Ошибка: недопустимое значение. Повторите попытку!");
                if (x == 0)
                    throw Zero("Ошибка: нулевое значение. Повторите попытку!");
                break;
            }
            catch (Zero& ex)
            {
                printf("%s", ex.what());
            }
            catch (Invalid& ex) {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                printf("%s", ex.what());
            }
        }
    }
};

class Matrix {
public:
    Matrix()
    {
        _n = 0;
        _values = NULL;
    }

    //параметры
    Matrix(float** A, int n)
    {
        _n = n;
        _values = new float* [_n];
        for (int i = 0; i < _n; i++)
            _values[i] = new float[_n];
        for (int i = 0; i < _n; i++) {
            for (int j = 0; j < _n; j++)
                _values[i][j] = A[i][j];
        }
    }

    //конструктор копирования
    Matrix(Matrix& A)
    {
        _n = A._n;
        _values = new float* [_n];
        for (int i = 0; i < A._n; i++)
            _values[i] = new float[_n];
        for (int i = 0; i < A._n; i++) {
            for (int j = 0; j < A._n; j++)
                _values[i][j] = A._values[i][j];
        }
    }

    Matrix operator = (Matrix&& A) {
        _n = A._n;
        if (_values != NULL)
            delete _values;
        _values = new float* [_n];
        for (int i = 0; i < _n; i++)
            _values[i] = new float[_n];
        for (int i = 0; i < _n; i++) {
            for (int j = 0; j < _n; j++)
                _values[i][j] = A._values[i][j];
        }
        return *this;
    }

    //деструктор
    ~Matrix()
    {
        if (_values != NULL) {
            for (int i = 0; i < _n; i++) {
                delete[] _values[i];
            }
            delete[] _values;
        }
    }
    //перегрузка операторов через дружественную функцию
    friend Matrix operator - (Matrix& B, Matrix& C);
    friend Matrix operator + (Matrix& B, Matrix& C);
    friend Matrix operator / (Matrix& B, Matrix& C);
    friend Matrix operator * (Matrix& B, Matrix& C);

    void print_class(string str)
    {
        cout << endl << str << endl;
        if (_values == NULL) {
            cout << "Класс пуст" << endl << endl;
            return;
        }
        for (int i = 0; i < _n; i++) {
            for (int j = 0; j < _n; j++)
                cout << _values[i][j] << " ";
            cout << endl;
        }
    }
private:
    float** _values;
    int _n;
};

Matrix operator - (Matrix& B, Matrix& C) {
    float** N = new float* [B._n];
    for (int i = 0; i < B._n; i++)
        N[i] = new float[B._n];
    for (int i = 0; i < B._n; i++) {
        for (int j = 0; j < B._n; j++)
            N[i][j] = B._values[i][j] - C._values[i][j];
    }
    Matrix new_A(N, B._n);
    for (int i = 0; i < B._n; i++) {
        delete[] N[i];
    }
    delete[] N;
    return new_A;
}

Matrix operator + (Matrix& B, Matrix& C) {
    float** N = new float* [B._n];
    for (int i = 0; i < B._n; i++)
        N[i] = new float[B._n];
    for (int i = 0; i < B._n; i++) {
        for (int j = 0; j < B._n; j++)
            N[i][j] = B._values[i][j] + C._values[i][j];
    }
    Matrix new_A(N, B._n);
    for (int i = 0; i < B._n; i++) {
        delete[] N[i];
    }
    delete[] N;
    return new_A;
}

Matrix operator / (Matrix& B, Matrix& C) {
    float** N = new float* [B._n];
    for (int i = 0; i < B._n; i++)
        N[i] = new float[B._n];
    for (int i = 0; i < B._n; i++) {
        for (int j = 0; j < B._n; j++)
            N[i][j] = B._values[i][j] / C._values[i][j];
    }
    Matrix new_A(N, B._n);
    for (int i = 0; i < B._n; i++) {
        delete[] N[i];
    }
    delete[] N;
    return new_A;
}

Matrix operator * (Matrix& B, Matrix& C) {
    float** N = new float* [B._n];
    for (int i = 0; i < B._n; i++)
        N[i] = new float[B._n];
    for (int i = 0; i < B._n; i++) {
        for (int j = 0; j < B._n; j++)
            N[i][j] = B._values[i][j] * C._values[i][j];
    }
    Matrix new_A(N, B._n);
    for (int i = 0; i < B._n; i++) {
        delete[] N[i];
    }
    delete[] N;
    return new_A;
}

int main()
{
    setlocale(LC_ALL, "rus");
    float** mass1;
    float** mass2;
    Scanner* scanner = new Scanner;
    int n;
    cout << "Укажите размер матрицы: ";
    scanner->get(n);
    mass1 = new float* [n];
    for (int i = 0; i < n; i++)
        mass1[i] = new float[n];
    cout << "Заполнение первой матрицы: " << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cin >> mass1[i][j];
    }
    mass2 = new float* [n];
    for (int i = 0; i < n; i++)
        mass2[i] = new float[n];
    cout << "Заполнение второй матрицы: " << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cin >> mass2[i][j];
    }
    Matrix A;
    Matrix B(mass1, n);
    Matrix C(mass2, n);
    A.print_class("Класс A");
    B.print_class("Класс B");
    C.print_class("Класс C");
    A = B - C;
    cout << endl << "Операция вычитания";
    A.print_class("Класс A");
    A = B + C;
    cout << endl << "Операция сложения";
    A.print_class("Класс A");
    A = B / C;
    cout << endl << "Операция деления";
    A.print_class("Класс A");
    A = B * C;
    cout << endl << "Операция умножения";
    A.print_class("Класс A");
    for (int i = 0; i < n; i++) {
        delete[] mass1[i];
        delete[] mass2[i];
    }
    delete[] mass1;
    delete[] mass2;
}
