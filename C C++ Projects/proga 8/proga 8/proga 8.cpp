#include <iostream>

using namespace std;

class Invalid : public exception {
public:
    Invalid(const char* message) : exception(message) {}
};

class Zero : public exception {
public:
    Zero(const char* message) : exception(message) {}
};

class Scanner {
public:
    void get(int& x) {
        while (true) {
            try
            {
                cin >> x;
                if (cin.fail())
                    throw Invalid("Wrong value!");
                if (x == 0)
                    throw Zero("Value is 0!");
                break;
            }
            catch (Zero& ex)
            {
                cout << ex.what();
            }
            catch (Invalid& ex) {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cout << ex.what(); 
            }
        }
    }
};

class Matrix
{
private:
    size_t rows_, cols_;
    int** arr;

    void copy(Matrix& M)
    {
        size_t t = rows_; rows_ = M.rows_; M.rows_ = t;
        t = cols_; cols_ = M.cols_; M.cols_ = t;
        int** p = arr; arr = M.arr; M.arr = p;
    }

public:
    Matrix(const size_t rows = 0, const size_t cols = 0)
    {
        rows_ = rows; cols_ = cols; arr = nullptr;
        if (rows_ && cols_)
        {
            arr = new int* [rows_];
            for (size_t i = 0; i < rows_; i++)
                arr[i] = new int[cols_];
        }
    }

    Matrix(const Matrix& M)
    {
        rows_ = M.rows_; cols_ = M.cols_; arr = nullptr;
        if (rows_ && cols_)
        {
            arr = new int* [rows_];
            for (size_t i = 0; i < rows_; i++)
            {
                arr[i] = new int[cols_];
                for (size_t j = 0; j < cols_; ++j)
                    arr[i][j] = M.arr[i][j];
            }
        }
    }

    Matrix& operator = (const Matrix& M)
    {
        Matrix tmp(M);
        copy(tmp);
        return *this;
    }

    ~Matrix()
    {
        if (arr != nullptr)
        {
            for (size_t i = 0; i < rows_; i++)
                delete arr[i];
            delete[] arr;
        }
    }

    size_t rows() const
    {
        return rows_;
    };

    size_t cols() const
    {
        return cols_;
    };

    int* operator[](size_t i) { return arr[i]; }
    const int* operator[](size_t i) const { return arr[i]; }
};

void Print(Matrix& M) {
    for (size_t i = 0; i < M.rows(); i++)
    {
        for (size_t j = 0; j < M.cols(); j++)
            cout << M[i][j] << ' ';
        cout << endl;
    }
}

void Input(Matrix& M) {
    for (size_t i = 0; i < M.rows(); i++)
    {
        for (size_t j = 0; j < M.cols(); j++)
            cin >> M[i][j];
    }
}

Matrix operator + (const Matrix& M, int m)
{
    Matrix temp(M.rows(), M.cols());
    for (size_t i = 0; i < M.rows(); i++)
    {
        for (size_t j = 0; j < M.cols(); j++)
        {
            temp[i][j] = M[i][j] + m;
        }
    }
    return temp;
}
Matrix operator - (const Matrix& M, int m)
{
    Matrix temp(M.rows(), M.cols());
    for (size_t i = 0; i < M.rows(); i++)
    {
        for (size_t j = 0; j < M.cols(); j++)
        {
            temp[i][j] = M[i][j] - m;
        }
    }
    return temp;
}
Matrix operator * (const Matrix& M, int m)
{
    Matrix temp(M.rows(), M.cols());
    for (size_t i = 0; i < M.rows(); i++)
    {
        for (size_t j = 0; j < M.cols(); j++)
        {
            temp[i][j] = M[i][j] * m;
        }
    }
    return temp;
}
Matrix operator / (const Matrix & M, int m)
{
    Matrix temp(M.rows(), M.cols());
    for (size_t i = 0; i < M.rows(); i++)
    {
        for (size_t j = 0; j < M.cols(); j++)
        {
            temp[i][j] = M[i][j] / m;
        }
    }
    return temp;
}

int main()
{
    Scanner* scan = new Scanner;
    
    int a, b;
    int m;
    cout << "Enter size of matrix A(a, b): ";
    scan->get(a);
    scan->get(b);
    cout << "Enter m-value: ";
    scan->get(m);
    Matrix A(a, b), B;

    cout << "A = \n";
    Input(A);

    cout << "\nA = \n";
    Print(A);
    cout << "\nA + m = B\n";
    B = A + m;
    Print(B);
    cout << endl;

    cout << "A - m = B\n";
    B = A - m;
    Print(B);
    cout << endl;

    cout << "\nA * m = B\n";
    B = A * m;
    Print(B);
    cout << endl;

    cout << "\nA / m = B\n";
    B = A / m;
    Print(B);
    cout << endl;

    return 0;
}
