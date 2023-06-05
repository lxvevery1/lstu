/* Написать программу, реализующую один из алгоритмов программного
поиска данных в информационном массиве, расположенном в оперативной памяти, используя формат ключа: char; формат инфо полей записи: int[], char; тип информационного поиска: одноаспектный поиск по совпадению и одноаcпектный поиск по интервалу, метод поиска: Блочный поиск */
// Программа идеальна ( ͡~ ͜ʖ ͡°), почти
#include <iostream>
#include <locale.h>
#include <stdlib.h>
#include <map>
#include <string>
#include <math.h>
using namespace std;

int main()
{
    setlocale(LC_ALL, "RUS");
    struct info
    {
        int numbers[2]; //значение объёма массива должно быть const
        char CHAR;
    };
    int i;
    char name, min, max;
    map <char, info> my_map = { {'H', {1 , 5, 'h'}},
                                {'K', {2 , 3, 'k'}},
                                {'A', {2 , 4, 'a'}},
                                {'D', {9 , 0, 'd'}},
                                {'C', {5 , 6, 'c'}},
                                {'S', {3 , 4, 's'}},
                                {'F', {7 , 2, 'f'}},
                                {'G', {2 , 7, 'g'}},
                                {'Z', {4 , 4, 'z'}},
                                {'Q', {1 , 3, 'z'}},
                                {'J', {7 , 0, 'z'}},
                                {'B', {4 , 7, 'b'}} };

    // Блоки
    char name_for_block; int tmp = 0;
    auto size = my_map.size(); //размерность map
    auto N_blocks = size / 2; //число элементов в 1 блоке
    auto it1 = my_map.begin();
    
    advance(it1, N_blocks);

    auto head_block = map{
        make_move_iterator(my_map.begin()),
        make_move_iterator(it1)
    };
    auto tail_block = map{
        make_move_iterator(it1),
        make_move_iterator(my_map.end())
    };

    cout << "Block 1\n"; //вывод 1-го блока
    for (auto [key, value] : head_block) {
        cout << key << " => " << value.numbers[0] << " " << value.numbers[1] << " " << value.CHAR << "\n";
    }
    cout << "\n\nBlock 2\n"; //вывод 2-го блока
    for (auto [key, value] : tail_block) {
        cout << key << " => " << value.numbers[0] << " " << value.numbers[1] << " " << value.CHAR << "\n";
    }
    cout << "\nВведите элемент поиска: ";
    cin >> name_for_block;

     //Одноаспектный поиск по совпадению

     //ищем в 1-ом блоке
     if (tmp == 0) 
     {
         cout << "\n\nBlock 1\n"; 
         if (name_for_block <= head_block.rbegin()->first)
         {
             auto it = head_block.find(name_for_block);
             if (it != head_block.end()) {
                 cout << it->first << " => " << it->second.numbers[0] << " " << it->second.numbers[1] << " " << it->second.CHAR << endl << endl;
                 tmp = 1;
             }
             else cout << "Такого ключевого значения нет" << endl;
             tmp = 0;
         }
     }
     else {
         cout << "Такого ключевого значения нет" << endl;
         tmp = 0;
     }

     //ищем во 2-ом блоке
     if (tmp == 0)
     {
         cout << "\n\nBlock 2\n"; 
         if (name_for_block <= tail_block.rbegin()->first)
         {
             auto it = tail_block.find(name_for_block);
             if (it != tail_block.end()) {
                 cout << it->first << " => " << it->second.numbers[0] << " " << it->second.numbers[1] << " " << it->second.CHAR << endl << endl;
                 tmp = 1;
             }
             else cout << "Такого ключевого значения нет" << endl;
             tmp = 0;
         }
     }
     else {
         cout << "Такого ключевого значения нет" << endl;
         tmp = 0;
     }

     // Одноаспектный поиск по интервалу  

     cout << endl << "Одноаспектный поиск по интервалу [";
     cin >> min; system("cls");
     cout << "Одноаспектный поиск по интервалу[" << min << ";";
     cin >> max; system("cls");
     cout << "Одноаспектный поиск по интервалу[" << min << ";" << max << "]" << endl;

     //////////////

     if (min < max)
     {
         cout << "\n\nBlock 1\n";
         if (min <= head_block.rbegin()->first)
         {
             auto it1 = head_block.lower_bound(min), it2 = head_block.upper_bound(max);
             for (auto pos = it1; pos != it2; ++pos)
                 cout << pos->first << " => " << pos->second.numbers[0] << " " << pos->second.numbers[1]
                 << " " << pos->second.CHAR << endl;
         }
         else cout << "Такого(их) ключевого(ых) значения(й) нет" << endl;
         cout << "\nBlock 2\n";
         if (max >= tail_block.begin()->first)
         {
             auto it3 = tail_block.lower_bound(min), it4 = tail_block.upper_bound(max);
             for (auto pos = it3; pos != it4; ++pos)
                 cout << pos->first << " => " << pos->second.numbers[0] << " " << pos->second.numbers[1]
                 << " " << pos->second.CHAR << endl;
         }
         else cout << "Такого(их) ключевого(ых) значения(й) нет" << endl;
     }
     else // на случай подвоха
     {
         cout << "\n\nBlock 1\n";
         if (min >= head_block.begin()->first) 
         {
             auto it1 = head_block.upper_bound(min), it2 = head_block.lower_bound(max); swap(it1, it2);
             for (auto pos = it1; pos != it2; ++pos)
                 cout << pos->first << " => " << pos->second.numbers[0] << " " << pos->second.numbers[1]
                 << " " << pos->second.CHAR << endl;
         }
         else cout << "Такого(их) ключевого(ых) значения(й) нет" << endl;
         cout << "\nBlock 2\n";
         
         if (max <= tail_block.rbegin()->first)
         {
             auto it3 = tail_block.upper_bound(min), it4 = tail_block.lower_bound(max); swap(it3, it4);
             for (auto pos = it3; pos != it4; ++pos)
                 cout << pos->first << " => " << pos->second.numbers[0] << " " << pos->second.numbers[1]
                 << " " << pos->second.CHAR << endl;
         }
         else cout << "Такого(их) ключевого(ых) значения(й) нет" << endl;
     }
     return 0;
}