#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <locale.h>
using namespace std;

struct node 
{
    int a;
    node* left, * right;
};

node* Sozdanie_dereva(int n) 
{
    node* ce; //нод, с которым будем создавать дерево
    if (!n) //n - число уровней дерева
        return NULL;
    ce = (node*) malloc(sizeof* ce); //Выделение памяти для ce
    ce->a = rand()%9+1; //Определяет значение вершин дерева (рандомные от 1 до 9)
    ce->left = Sozdanie_dereva(n-1); //Продолжение дерева по левым рёбрам
    ce->right = Sozdanie_dereva(n-1); //Продолжение дерева по правым рёбрам
    return ce;
}

void Uroven_dereva(int n, int s, node * cn) //Функция, которая визуально строит наше дерево
{
    int i, d; //индекс и текущее положение вершины в дереве
    char str[81]; //Пробелы между вершинами
    if (s == n) // Выполнится, если текущий уровень совпадает с S
    {
        memset(str, 0, 81);
        d = 1;
        d = (d << (s - 1)) + 1;
        for (i = 0; i < 80 / d; i++)
            str[i] = 32;
        cout << str << cn->a;
    }
    else
    {
        Uroven_dereva(n + 1, s, cn->left); //Переход к следующему левому уровню дерева и его красивый вывод
        Uroven_dereva(n + 1, s, cn->right); //Переход к следующему правому уровню дерева и его красивый вывод
    }
}

typedef struct sNode
{
    node* data;
    struct sNode* next;
} tNode;


tNode* Sozdanie_node(node* data) 
{
    tNode* node = (tNode*) malloc(sizeof* node);
    node->data = data;
    node->next = NULL;
    return node;
}

void Pool_dereva(tNode** list, node* data) 
{
    tNode* new_node = Sozdanie_node(data);
    tNode* temp = *list;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = new_node;
}

tNode* Udalenie_node(tNode* list) // Когда все вершины будут добавлены в пул, они будут удаляться согласно поиску
{
    tNode* temp = list;
    list = list->next;
    cout << endl << (temp->data)->a << " - удалено" << endl << endl;
    return list;
}


int Obhod_dereva(node* crn) 
{
    cout << crn->a << " - добавлено" << endl << endl; //Старт
    tNode* ochered = Sozdanie_node(crn);
    tNode* temp;

    while (ochered != NULL) // Выполняем операции, пока в нашем дереве есть непройденные элементы
    {
        temp = ochered;
        cout << "\n/////////////\n" << "До: \n";
        while (temp != NULL) //Если вершина находящаяся в очереди есть, она выводится.
        {
            cout << (temp->data)->a << " ";
            temp = temp->next;
        }
        cout << "\n\n";
        if ((ochered->data)->left) // Если в нашей очереди по левому ребру есть вершина, то
        {
            Pool_dereva(&ochered, (ochered->data)->left); //Добавляем в наш пул вершину по левой ветке
            cout << ((ochered->data)->left)->a << " - добавлено" << endl << endl; //Вывод этой вершины
        }
        if ((ochered->data)->right) // Если в нашей очереди по правому ребру есть вершина, то 
        {
            Pool_dereva(&ochered, (ochered->data)->right); //Добавляем в наш пул вершину по левой ветке
            cout << endl << ((ochered->data)->right)->a << " - добавлено" << endl << endl; //Вывод этой вершины
        }
        ochered = Udalenie_node(ochered); //Удаляем наш использованный нод
        temp = ochered;
        cout << "\n" << "После: \n";
        while (temp != NULL) //Выводим полученный пул вершин
        {
            cout << (temp->data)->a << " ";
            temp = temp->next;
        }
        cout << "\n/////////////\n\n" << endl << endl;
    }
    if (crn == NULL) return 0; // Нужно, чтобы фунция выводила что-нибудь
}

int main() 
{
    setlocale(LC_ALL, "");
    node* a; int lvl; // b - текущий уровень дерева
    int maxlvl = 4; // Число уровней в дереве
    cout << "--------------------------------------Дерево--------------------------------------\n\n";
    a = Sozdanie_dereva(maxlvl); // Аргумент - число уровней дерева >= b
    for (lvl = 1; lvl <= maxlvl; lvl++) // Цикл для визуального отображения нашего дерева
    {
        Uroven_dereva(1, lvl, a);
        cout << endl;
    }
    cout << "\n-----------------------------------Обход дерева-----------------------------------\n\n";
    Obhod_dereva(a);
    return 0;
}