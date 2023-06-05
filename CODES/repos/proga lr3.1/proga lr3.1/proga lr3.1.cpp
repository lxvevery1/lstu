#include <iostream>
#include <fstream>
using namespace std;

struct Node //описание узла списка
{
	double key = 0; //ключевое поле
	string data; //информационное поле
	Node* next = nullptr; //указатель на следующий элемент
};
struct Queue //описание очереди
{
	size_t size = 0; //счетчик размера очереди динамического массива
	Node* first = nullptr; //указатель на начало очереди
	Node* last = nullptr; //указатель на конец очереди
};
struct StaticQueue //описание очереди
{
	const size_t staticSize = 5; //счетчик размера очереди статического массива
	Node* first = nullptr; //указатель на начало очереди
	Node* last = nullptr; //указатель на конец очереди
};

bool IsEmpty(Queue* Q) //проверка очереди на пустоту
{
	return Q->first == nullptr;
}
bool SIsEmpty(StaticQueue* SQ) //проверка очереди на пустоту
{
	return SQ->first == nullptr;
}
string Top(Queue* Q) //вывод начального элемента
{
	return IsEmpty(Q) ? "" : Q->first->data;
}

void Add(Queue* Q, double key, string data) //добавление элемента в динамическом
{
	if (IsEmpty(Q))
	{
		Q->first = Q->last = new Node;
		Q->first->key = key;
		Q->first->data = data;
		Q->size++;
		return;
	}

	Q->last->next = new Node;
	Q->last = Q->last->next;
	Q->last->key = key; //добавление ключа в конец
	Q->last->data = data; //добавление элемента в конец
	Q->size++;
}
void StaticAdd(StaticQueue* SQ, double key, string data) //добавление элемента в статическом
{
	if (SIsEmpty(SQ))
	{
		SQ->first = SQ->last = new Node;
		SQ->first->key = key;
		SQ->first->data = data;
		return;
	}
	if (SQ->last->key == NULL)
	{
		SQ->last->next = new Node;
		SQ->last = SQ->last->next;
		SQ->last->key = key; //добавление ключа в конец
		SQ->last->data = data; //добавление элемента в конец
	}
	else cout << "\nОчередь заполнена!";
}
void Delete(Queue* Q) //удаление first элемента
{
	if (IsEmpty(Q)) return; // проверка на пустоту

	Node* tmp = Q->first;
	Q->first = Q->first->next; //смещение указателя
	delete tmp;
	Q->size--;
}
void Clear_Queue(Queue* Q) //удаление всех элементов очереди
{
	if (IsEmpty(Q)) return; // проверка на пустоту

	for (Node* currentStr = Q->first; currentStr;)
	{
		//<--- Если мы освобождаем блок - есть шанс, что в него сразу что-то может записаться
		//Потому сначала запоминаем указатель
		Node* tmp = currentStr;
		//Потом сдвигаемся на следующий
		currentStr = currentStr->next;
		//И только после этого освобождаем память
		delete tmp;
		Q->size--;
	}

	Q->first = Q->last = nullptr;
}
size_t Size(Queue* Q) //размер очереди
{
	return Q->size;
}
string SearchString(Queue* Q, double key1) {
	for (Node* currentString = Q->first; currentString; currentString = currentString->next)  // перемещаемся по элементам
	{
		//если значения ключей совпадают
		if (key1 == currentString->key)
		{
			cout << "\nИнформационное поле этого ключа: " << currentString->data << "\n";
			//выводим его инфу
			return currentString->data;
		}
		else cout << "\nТакого значения нет\n";
	}
}
bool Save(Queue* Q, string Name)
{
	ofstream fout(Name);
	if (fout.is_open())
	{
		for (Node* currentStr = Q->first; currentStr; currentStr = currentStr->next) {
			fout << currentStr->key << " " << currentStr->data << endl;
			if (!fout) break;
		}
	}
	fout.close();
	return (bool)fout;
}
bool Load(Queue* Q, string Name)
{
	ifstream fin(Name);
	if (!fin) return false;

	Clear_Queue(Q);

	while (!fin.eof()) {
		double key; string data;
		fin >> key >> data;
		if (!fin) break;
		Add(Q, key, data);
	}
	fin.close();

	return (bool)fin;
}
void EditCustom(Queue* Q, int index, double key, string data) //Изменение строчки
{
	Node* temp;
	temp = Q->first;
	while (index != 0 && temp != Q->last)
	{
		temp = temp->next;
		index--;
	}
	if (index == 0)
	{
		//на указанное место перезаписываем данные
		temp->key = key;
		temp->data = data;
		//выходим
		return;
	}
}


int main()
{
	const string fileNameSave = "D:\\QueueSave.txt";
	const string fileNameLoad = "D:\\QueueLoad.txt";

	setlocale(LC_ALL, "Rus");

	Queue Q; StaticQueue SQ; char number; double key = 0; string data; double key1 = 0; size_t index;
	do
	{
		cout << "1. Добавить элемент\n"
				"2. Удалить элемент\n"
				"3. Вывести верхний элемент\n"
				"4. Узнать размер очереди\n"
				"5. Записать данные в файл\n"
				"6. Считать данные из файла\n"
				"7. Очистить очередь\n"
				"8. Поиск элемента по ключу\n"
				"9. Замена «старого» значения элемента на заданное новое\n"
				"0. Выйти\n\n"
			"Номер команды > ";
		cin >> number;
		switch (number)
		{
			//-----------------------------------------------
		case '1':
			cout << "\nВведите ключ и инф. поле < ";
			cin >> key >> data;
			Add(&Q, key, data);
			cout << "\nЭлемент добавлен\n\n";
			break;
			//-----------------------------------------------
		case '2':
			if (IsEmpty(&Q))
				cout << "\nОчередь пуста\n\n";
			else
				Delete(&Q);
			break;
			//-----------------------------------------------
		case '3':
			if (IsEmpty(&Q))
				cout << endl << "Очередь пуста\n\n";
			else
				cout << "\nНачальный элемент: " << Top(&Q) << "\n\n";
			break;
			//-----------------------------------------------
		case '4':
			if (IsEmpty(&Q))
				cout << endl << "Очередь пуста\n\n";
			else
				cout << "\nРазмер очереди: " << Size(&Q) << "\n\n";
			break;
			//-----------------------------------------------
		case '5':
			if (IsEmpty(&Q)) {
				cout << endl << "Очередь пуста\n\n";
				break;
			}
			if (Save(&Q, fileNameSave)) //проверка удачно ли прошла запись
				cout << "\nФайл перезаписан\n\n";
			else
				cout << "\nОшибка записи файла\n\n";
			break;
		case '6':
			if (Load(&Q, fileNameLoad)) //проверка удачно ли прошло чтение
				cout << "\nДанные считаны\n\n";
			else
				cout << "\nОшибка чтения данных\n\n";
			break;
		case '7':
			Clear_Queue(&Q); cout << "\nОчередь очищена\n\n";
			break;
		case '8':
			if (IsEmpty(&Q)) 
			{
				cout << endl << "Очередь пуста\n\n";
				break;
			}
			cout << "\nВведите ключ < ";
			cin >> key1;
			SearchString(&Q, key1);
			cout << "\n\n";
			break;
		case '9':
			if (IsEmpty(&Q))
			{
				cout << endl << "Очередь пуста\n\n";
				break;
			}
			cout << "\nВведите индекс < ";
			cin >> index;
			cout << "\nВведите ключ < ";
			cin >> key;
			cout << "\nВведите инф. поле < ";
			cin >> data;
			EditCustom(&Q, index, key, data);
			cout << "\n\n";
			break;
		case '88':
			cout << "\nВведите ключ и инф. поле < ";
			cin >> key >> data; //можно сразу так
			StaticAdd(&SQ, key, data);
			cout << "\nЭлемент добавлен\n\n";
			break;
			//-----------------------------------------------
		case '0':
			break;
		default:
			cout << endl << "Команда не определена\n\n";
			break;
		}
	} while (number != '0');

	Clear_Queue(&Q); //очистка очереди перед выходом

	return 0;
}
