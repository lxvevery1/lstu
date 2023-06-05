#include <iostream>
#include <fstream>
using namespace std;

struct Node //описание узла списка
{
	double key; //ключевое поле
	string data; //информационное поле
	Node* next = nullptr; //указатель на следующий элемент
};
struct Queue //описание очереди
{
	int size; //счетчик размера очереди
	Node* first = nullptr; //указатель на начало очереди
	Node* last = nullptr; //указатель на конец очереди
};
void Creation(Queue* Q) //создание очереди
{
	Q->first = new Node;
	Q->first->next = NULL;
	Q->last = Q->first;
	Q->size = 0;
}
bool Full(Queue* Q) //проверка очереди на пустоту
{
	if (Q->first == Q->last) return true;
	else return false;
}
string Top(Queue* Q) //вывод начального элемента
{
	return Q->first->next->data;
}
void Add(Queue* Q) //добавление элемента
{
	double key;
	string value;
	cout << "\nЗначение > "; cin >> key; cin >> value;
	Q->last->next = new Node;
	Q->last = Q->last->next;
	Q->last->key = key; //добавление ключа в конец
	Q->last->data = value; //добавление элемента в конец
	Q->last->next = NULL; //обнуление указателя на следующий элемент
	Q->size++;
	cout << "\nЭлемент добавлен\n\n";
}
void Delete(Queue* Q) //удаление элемента
{
	Q->first = Q->first->next; //смещение указателя
	Q->size--;
	cout << "\nЭлемент удален\n\n";
}
int Size(Queue* Q) //размер очереди
{
	return Q->size;
}
void fileout(Queue* Q)
{
	ofstream fout("D:\\Queue.txt");
	for (Node* currentStr = Q->first; currentStr; currentStr = currentStr->next)
		fout << currentStr->key << " " << currentStr->data << endl;
	fout.close();
}
void filein(Queue* Q)
{
	fstream fin("D:\\Queue.txt");
}
int main()
{
	setlocale(LC_ALL, "Rus");
	Queue Q;
	Creation(&Q);
	char number;
	do
	{
		cout << "1. Добавить элемент" << endl;
		cout << "2. Удалить элемент" << endl;
		cout << "3. Вывести верхний элемент" << endl;
		cout << "4. Узнать размер очереди" << endl;
		cout << "5. Записать данные в файл" << endl;
		cout << "6. Считать данные из файла" << endl;
		cout << "0. Выйти\n\n";
		cout << "Номер команды > "; cin >> number;
		switch (number)
		{
		case '1': Add(&Q);
			break;
			//-----------------------------------------------
		case '2':
			if (Full(&Q)) cout << endl << "Очередь пуста\n\n";
			else Delete(&Q);
			break;
			//-----------------------------------------------
		case '3':
			if (Full(&Q)) cout << endl << "Очередь пуста\n\n";
			else { cout << "\nНачальный элемент: " << Top(&Q) << "\n\n"; }
			break;
			//-----------------------------------------------
		case '4':
			if (Full(&Q)) cout << endl << "Очередь пуста\n\n";
			else cout << "\nРазмер очереди: " << Size(&Q) << "\n\n";
			break;
			//-----------------------------------------------
		case '5':
			if (Full(&Q)) cout << endl << "Очередь пуста\n\n";
			else { fileout(&Q); cout << "\nФайл перезаписан" << "\n\n"; }
			break;
		case '6':
			filein(&Q); cout << "\nДанные считаны" << "\n\n";
			break;
			//-----------------------------------------------
		case '0': break;
		default: cout << endl << "Команда не определена\n\n";
			break;
		}
	} while (number != '0');
	system("pause");
	return 0;
}