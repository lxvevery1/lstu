// Реализация хеш-таблицы через остаток от деления
// Добавление и поиск элементов осуществлятся через имя (name). В реальных условиях
// такая таблица будет иметь много коллизий, но, поскольку задание является тестовым,
// я избрал самый простой, быстрый и наглядный метод реализации.

#include <iostream>
#include <string>

#define PRIME_SIZE 29 // Использовано просто число

using namespace std;

class Person // Класс, который содержит немного информации о человеке.
{
public:
    Person* next; // При возникновении коллизии элементы будут помещены в односвязный список.
    string name;
    string surname;
    int age;

    Person()
    {
        this->next = NULL;
    }

    Person(string name, string surname, int age = 0)
    {
        this->name = name;
        this->surname = surname;
        this->age = age;
        this->next = NULL;
    }

    ~Person()
    {
        //cout << "Delete " << this->name << endl;
        if (this->next != NULL)
        {
            delete this->next;
        }
    }
};

class HashTable // Хеш-таблица, представленная в виде массива элементов (которые в свою очередь представляют список).
{
    Person* table[PRIME_SIZE];

    // Самая простоя хеш-функция. Считает сумму ASCII кодов, делит на константу и
    // получает остаток от деления.
    static int hash(string str)
    {
        int asciisum = 0;
        for (int i = 0; i < str.length(); i++)
        {
            asciisum += str[i];
        }
        return asciisum % PRIME_SIZE;
    }

public:

    HashTable()
    {
        for (int i = 0; i < PRIME_SIZE; i++)
        {
            table[i] = NULL;
        }
    }

    ~HashTable()
    {
        //cout << "Delete table\n";
        for (int i = 0; i < PRIME_SIZE; i++)
        {
            delete table[i];
        }
    }

    // Вставляет элемент в таблицу
    void push(string name, string surname, int age)
    {
        int hashNumber = hash(name);
        Person* pers = new Person(name, surname, age);
        Person* place = table[hashNumber];
        if (place == NULL)
        {
            table[hashNumber] = pers;
            return;
        }

        while (place->next != NULL)
        {
            place = place->next;
        }
        place->next = pers;
    }

    // Получает элемент из таблицы по его имени.
    Person* find(string name)
    {
        int hashNumber = hash(name);
        Person* result = table[hashNumber];
        if (!result)
        {
            cout << "Element not found" << endl;
            return NULL;
        }
        while (result->name != name)
        {
            if (!result->next)
            {
                cout << "Element not found" << endl;
                return NULL;
            }
            result = result->next;
        }
        return result;
    }
};

int main()
{
    HashTable newTable;
    newTable.push("Artyom", "Devyatov", 20);
    newTable.push("Vasya", "Petrov", 23);
    newTable.push("Ilja", "Saveljev", 28);
    newTable.push("Ilaj", "Savanna", 43); // Имеет коллизию с Ilja
    newTable.push("Dmitry", "Kuzychev", 31);

    Person* search = newTable.find("Ilja");
    if (search)
    {
        cout << search->surname << " " << search->age << endl;
    }

    return 0;
}