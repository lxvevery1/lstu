// программа считывает данные с файла, и выполняет одну из семи функций. Каждое действие автоматически переписывает файл
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <locale.h>
#include <iomanip>
using namespace std;
////////////
void couta(string name)
{
    string stroka;
    ifstream in(name); // открываем файл для чтения
    if (!in.is_open())
    {
        cout << "Ошибка: невозможно открыть файл: " << name << endl; return;
    }
    if (in.is_open())
    {
        while (getline(in, stroka))
        {
            cout << stroka << endl;
        }
    }
    in.close();
}
////////////
struct magazine1
{
    char name[100];
    int year;
};
void couttable(string name)
{
    FILE* file;
    ifstream input;
    
    int i = 0; //string magazine;
    struct magazine1 info[100];
    string magazine, minmagazine;
    int year = 1; int minyear = INT_MAX, n = 1, minn = 1;

    input.open(name);
    file = fopen(name.c_str(), "r"); //для вывода стринг из си
    if (!input.is_open())
    {
        cout << "Ошибка: невозможно открыть файл: " << name << endl; return;
    }

    cout << "-------------------------------------------" << endl;
    cout << left << setw(14) << "Номер" << setw(23) << "Название" << right << "Год" << endl;
    cout << "-------------------------------------------" << endl;
    while (fscanf(file, "%s %d", info[i].name, &(info[i].year)) != EOF) // Пока невыведенные элементы есть в текстовом  док-те, они выводятся
    {
        cout << left << "|" << i+1 << setw(12) << "|" << setw(23) << info[i].name << right << info[i].year << endl;
        if (info[i].year < minyear) minyear = info[i].year;
        i++;
    }
    cout << "-------------------------------------------" << endl;
    cout << left << setw(37) << "Минимальная дата: " << minyear << endl;
    cout << "-------------------------------------------" << endl;
    input.close();
}
////////////
void oldestmagazine(string name)
{
    FILE* file;
    ifstream input;
    string magazine, minmagazine; 
    int year, minyear = INT_MAX, n = 1, minn = INT_MAX;
    int i = 0; struct magazine1 info[100];
    input.open(name);
    if (!input.is_open()) 
    {
        cout << "Ошибка: нельзя открыть файл " << name << endl; return;
    }
    file = fopen(name.c_str(), "r");
    while (fscanf(file, "%s %d", info[i].name, &(info[i].year)) != EOF) // Пока невыведенные элементы есть в текстовом  док-те, они выводятся
    {
        if (info[i].year < minyear)
        {
            minyear = info[i].year;
            minmagazine = info[i].name;
            n = i+1;
        }
        i++;
    }
    cout << left << setw(30) << "Журнал с минимальная датой: " << endl << n << " " << minmagazine << " " << minyear << endl; return;
    cout << "Ошибка: файл пустой или повреждён!"; return;
}
////////////
void addstroke(string name)
{
    ofstream output;
    string magazine; int year;
    output.open(name, ios_base::app);
    if (!output.is_open())
    { 
        cout << "Ошибка: нельзя открыть файл " << name; return; 
    }
    cout << "Введите название журнала: "<< endl;
    cin >> magazine;
    cout << "Введите его год выпуска: " << endl;
    cin >> year;
    output << endl << magazine << " " << year; 
    output.close(); return;
    cout << "Ошибка: файл пустой или повреждён!"; return;
}
////////////
void deletestroke(string name)
{
     ifstream in;
     in.open(name);

     if (!in.is_open())
     {
         cout << "Ошибка: невозможно открыть файл: " << name << endl; return;
     }

     int i_number_line_delete = 0; //для хранения номера строки который нужно удалить
     cin >> i_number_line_delete;

     int i_number_line_now = 0; //счётчик строк
     string line; //для хранения строки
     string line_file_text; //для хранения текста файла

     while (getline(in, line))
     {
         i_number_line_now++;

         if (!(i_number_line_now == i_number_line_delete))
         {
             line_file_text.insert(line_file_text.size(), line); //добавить строку
             //добавить перенос на следующую строку
             line_file_text.insert(line_file_text.size(), "\r\n");
         }
     }
     if (i_number_line_now < i_number_line_delete)
         cout << "Ошибка: такой строки нет" << endl;
     in.close();

     //теперь в line_file_text будет содержаться измененный текст файла, теперь можно перезаписать файл

     ofstream out;
     out.open(name, ios::trunc | ios::binary); //открыть и обрезать

     //записать

     out.write(line_file_text.c_str(), line_file_text.size());
     out.clear();

}
////////////
int main()
{
    setlocale(LC_ALL, "");
    int N;
    string name;
    cout << "Введите путь к файлу (например: D:\\magazine.txt): ";
    cin >> name;
    // Мейн меню
    cout << "---Что делаем?---" << endl
         << "1. Чтение файла" << endl
         << "2. Вывод содержимого файла в виде таблицы" << endl
         << "3. Вывод самого первого журнала по дате" << endl
         << "4. Добавить одну запись в конец массива" << endl 
         << "5. Удаление записи по её номеру" << endl 
         << "6. Выход из программы" << endl;
    
    while (1) 
    {
        cin >> N;
        if (N == 1)
        {
            cout << "1. Чтение файла:" << endl;
            //cin >> magazine;
            couta(name);
        }
        else if (N == 2)
        {
            cout << "2. Вывод содержимого файла в виде таблицы:" << endl;
            couttable(name);
        }
        else if (N == 3)
        {
            cout << "3. Вывод самого первого журнала по дате" << endl;
            oldestmagazine(name);
        }
        else if (N == 4)
        {
            cout << "4. Добавить одну запись в конец массива" << endl;
            addstroke(name);
        }
        else if (N == 5)
        {
            cout << "5. Удаление записи по её номеру" << endl;
            cout << "Введите номер строки для удаления: " << endl;
            deletestroke(name);
        }
        else if (N == 6)
        {
            cout << "6. Выход из программы";
            break;
        }
    }
}