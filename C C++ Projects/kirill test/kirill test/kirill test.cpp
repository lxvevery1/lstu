#include <iostream>

using namespace std;

class Basic     // абстрактный класс
{
public:
    virtual double  calculate(double x) = 0;
};

class Function
{
private:
    double y;
public:
    Function(Basic* function, double x, int n)
    {
        y = function->calculate(x);
        cout << "f(x)=" << y << endl;
    }
};

class Function1 : public Basic  // функция a*sin(b*x)
{
private:
    double a = 0, b = 0;
public:
    Function1(double a, double b)
    {
        this->a = a;
        this->b = b;
    }
    double calculate(double x)
    {
        cout << "a=" << a << " b=" << b << endl;
        return (a * sin(b * x));
    }
};

class Function2 : public Basic // функция a * x * x + b * x + c
{
private:
    double a = 0, b = 0, c = 0;
public:
    Function2(double a, double b, double c)
    {
        this->a = a;
        this->b = b;
        this->c = c;
    }
    double calculate(double x)
    {
        cout << "a=" << a << " b=" << b << "c=" << c << endl;
        return (a * pow(x, 2) + b * x + c);
    }
};

int main()
{
    setlocale(LC_ALL, "RUS");
    system("color F0");
    int n = 0;
    double x;
    int option;
    cout << "Введите количество функций: " << endl;
    cin >> n;
    while (n <= 0)
    {
        cout << "Количество функций не может быть меньше или равно нулю! Введите другое значение: " << endl;
        cin >> n;
    }

    Basic** f = new Basic * [n];
    for (int i = 0; i < n; i++)
    {
        cout << "Введите '1', чтобы вызвать функцию a*sin(b*x). " << endl;
        cout << "Введите '2', чтобы вызвать функцию a * x * x + b * x + c. " << endl;
        cin >> option;
        if (option == 1) {
            double a, b;
            cout << "Введите значения (a, b) для функции: ";
            cin >> a >> b;
            f[i] = new Function1(a, b);
        }
        if (option == 2) {
            double a, b, c;
            cout << "Введите значения (а, b, c) для функции: ";
            cin >> a >> b >> c;
            f[i] = new Function2(a, b, c);
        }
    }
    while(true) {
        cout << "Введите x: " << endl;
        cin >> x;
        for (int i = 0; i < n; i++)
            Function r(f[i], x, n);
    }
    return 0;
}
