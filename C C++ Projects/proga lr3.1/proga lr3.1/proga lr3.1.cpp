#include <iostream>
#include <fstream>
using namespace std;
////////////
struct Node //описание узла списка
{
	double key = 0; //ключевое поле
	string data; //информационное поле
	Node* next = nullptr; //указатель на следующий элемент
};
struct Queue //описание очереди
{
	size_t size = 0; //счетчик размера очереди массива
	Node* first = nullptr; //указатель на начало очереди
	Node* last = nullptr; //указатель на конец очереди
};
////////////
struct SqueueItem 
{
	double key = 0;
	string value;
};
// Статическая очередь реализована в почти ООП, так как теперь функции внутри структуры
struct Squeue
{
	static const size_t maxSize = 3;
	//пуста ли очередь
	bool empty() const { return size == 0; }
	//полна ли очередь
	bool full() const { return size == maxSize; }
	//признак ошибки
	bool error() const { return errorState; }

	//добавление элемента, передаваемого через указатель
	bool push(const SqueueItem* item) 
	{
		//если очередь полная - устанавливаем флаг ошибки, выходим
		if (full()) { errorState = true; return false; }

		//сохраняем элемент в очереди
		data[size] = *item;
		//увеличиваем кол-во элементов
		size++;
		//возвращаем что всё в порядке
		return true;
	}
	bool push(const SqueueItem item) //добавление элемента, передаваемого по значению
	//вредная штука, если данных в queueItem много
	//лучше использовать ссылки
	{
		//просто вызываем добавление через указатель
		return push(&item);
	}
	SqueueItem pop() //выталкивание элемента
	{
		//вообще при пустой очереди лучше выкидывать исключение
		//тогда errorState не нужен и можно красиво обрабатывать ошибки
		if (empty()) { errorState = true; return SqueueItem{}; }

		//уменьшаем размер
		size--;

		//Запоминаем выталкиваемый элемент
		SqueueItem top = data[0];

		//лучше использовать memmove или std::copy
		//сдвиг всех элементов очереди
		for (size_t i = 0; i < size; i++)
			data[i] = data[i + 1];
		
		//возвращаем выталкиваемый элемент
		return top;
	}
	void clear() //очистка очереди
	{
		Squeue::size = 0;
		errorState = false;
	}
	void SqueueCurrentSize(Squeue* Sq) //Текущий размер очереди
	{
		cout << "\nМаксимальный размер очереди: " << Squeue::maxSize << "\n";
		cout << "\nТекущее кол-во элементов: " << Sq->size << "\n\n";
	}
	bool SSave(Squeue* Sq, SqueueItem* SqI, string Name) //неправильно
	{
		ofstream fout(Name);
		if (fout.is_open())
		{
			for ( size_t i = 0; i < Sq->size ; i++) 
			{
				fout << &SqI->key << " " << &SqI->value << "\n";
				if (!fout) break;
			}
		}
		fout.close();
		return (bool)fout;
	}
	bool SLoad(Squeue* Sq, SqueueItem* SqI, string Name)
	{

		ifstream fin(Name);
		if (!fin) return false;

		Squeue::clear();

		while (!fin.eof()) 
		{
			double key; string data;
			fin >> key >> data;
			if (!fin) break;
			push(SqI);
		}
		fin.close();

		return (bool)fin;
	}

	//признак была ли ошибка (т.к. исключения не проходили,
	//а передавать состояние без них красиво не получается)
	bool        errorState = false;
	//количество элементов в очереди
	size_t      size = 0;
	//статический массив с элементами
	SqueueItem   data[Squeue::maxSize];
};
const SqueueItem SqueueItemEmpty = { 0, "" };

//////Dynamic
bool IsEmpty(Queue* Q) //проверка очереди на пустоту
{
	return Q->first == nullptr;
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
string SearchString(Queue* Q, double key1) 
{
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
void EditByIndex(Queue* Q, int index, double key, string data) //Изменение строчки по индексу
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
void EditByKey(Queue* Q, double key1, double key, string data) //Изменение строчки по ключу
{
	for (Node* currentString = Q->first; currentString; currentString = currentString->next)  // перемещаемся по элементам
	{
		//если значения ключей совпадают
		if (key1 == currentString->key)
		{
			currentString->key = key;
			currentString->data = data;
			return;
		}
		else cout << "\nТакого значения нет\n";
	}
}
void SearchByIndex(Queue* Q, size_t index) //Изменение строчки по ключу
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
		cout << temp->data;
		return;
	}
}
///////Dynamic
///////Static
bool SqueueItemIsEmpty(const SqueueItem* item) 
{
	return  item && item->key == SqueueItemEmpty.key && item->value == SqueueItemEmpty.value;
}
void SqueueItemPrint(const SqueueItem* item) 
{
	//if (!item) return;
	cout << item->key << " : " << item->value << endl;
}
void SqueueItemPrint(const SqueueItem item) 
{
	SqueueItemPrint(&item);
}
bool SqueueIsEmpty(const Squeue* Sq) 
{
	return Sq == nullptr || Sq->size == 0;
}
bool SqueuePush(Squeue* Sq, SqueueItem* item) 
{
	if (!Sq || !item || Sq->size == Squeue::maxSize) return false;

	Sq->data[Sq->size] = *item;
	Sq->size++;
	return true;
}
SqueueItem SqueuePop(Squeue* Sq)  //вообще лучше возвращать const ссылку
{
	//вообще при пустой очереди лучше выкидывать исключение
	if (SqueueIsEmpty(Sq)) 
	{
		cout << "\nОчередь пуста\n\n";
		return SqueueItemEmpty;
	}

	Sq->size--;

	SqueueItem top = Sq->data[0];

	for (size_t i = 0; i < Sq->size; i++)
	{
		Sq->data[i] = Sq->data[i + 1]; //сдвигаем наш массив, в сторону удалённого эл-та
	}
	cout << "\nЭлемент удалён\n\n";
	return top;
}
void SqueueClear(Squeue* Sq) {
	if (!SqueueIsEmpty(Sq))
		Sq->size = 0;
}
void SqueuePrint(const Squeue* Sq) {
	if (SqueueIsEmpty(Sq))
		cout << "\nОчередь пуста\n";
	else
		for (size_t i = 0; i < Sq->size; i++)
			SqueueItemPrint(&Sq->data[i]);
}
void SqueueTopPrint(const Squeue* Sq) {
	if (SqueueIsEmpty(Sq))
		cout << "\nОчередь пуста\n\n";
	else
		SqueueItemPrint(&Sq->data[0]);
}

//Функции вывода в консоль вынесены отдельно
//Классы/структуры не должны быть завязаны на консоль внутри себя,
// ведь консоли может и не быть
//В C++ это решается перегрузкой операторов, но Вы ее скорее всего не проходили
///////Static

int main()
{
	const string fileNameSave = "D:\\QueueSave.txt";
	const string fileNameLoad = "D:\\QueueLoad.txt";

	setlocale(LC_ALL, "Rus");
	Queue Q; int number; double key = 0; string data; double key1 = 0; size_t index;
	Squeue Sq; SqueueItem SqI;

	cout << "Введите 1 для динамического массива и 2 для статического < ";
	cin >> number;
	if (number == 1)
	{
	do
	{
		cout << "--Динамическая очередь\n"
			"1. Добавить элемент\n"
			"2. Удалить элемент\n"
			"3. Вывести верхний элемент\n"
			"4. Узнать размер очереди\n"
			"5. Записать данные в файл\n"
			"6. Считать данные из файла\n"
			"7. Очистить очередь\n"
			"8. Поиск элемента по ключу\n"
			"9. Установка значения элемента по заданному индексу (поиск по индексу)\n"
			"10. Замена «старого» значения элемента на заданное новое (поиск по значению)\n"
			"11. Получение значения элемента по заданному индексу\n"

			"0. Выйти\n\n"
			"Номер команды > ";
		cin >> number;
			switch (number)
			{
				//-----------------------------------------------
			case 1:
				cout << "\nВведите ключ и инф. поле < ";
				cin >> key >> data;
				Add(&Q, key, data);
				cout << "\nЭлемент добавлен\n\n";
				break;
				//-----------------------------------------------
			case 2:
				if (IsEmpty(&Q))
					cout << "\nОчередь пуста\n\n";
				else
					Delete(&Q);
				break;
				//-----------------------------------------------
			case 3:
				if (IsEmpty(&Q))
					cout << endl << "Очередь пуста\n\n";
				else
					cout << "\nНачальный элемент: " << Top(&Q) << "\n\n";
				break;
				//-----------------------------------------------
			case 4:
				if (IsEmpty(&Q))
					cout << endl << "Очередь пуста\n\n";
				else
					cout << "\nРазмер очереди: " << Size(&Q) << "\n\n";
				break;
				//-----------------------------------------------
			case 5:
				if (IsEmpty(&Q)) 
				{
					cout << endl << "Очередь пуста\n\n";
					break;
				}
				if (Save(&Q, fileNameSave)) //проверка удачно ли прошла запись
					cout << "\nФайл перезаписан\n\n";
				else
					cout << "\nОшибка записи файла\n\n";
				break;
				//-----------------------------------------------
			case 6:
				if (Load(&Q, fileNameLoad)) //проверка удачно ли прошло чтение
					cout << "\nДанные считаны\n\n";
				else
					cout << "\nОшибка чтения данных\n\n";
				break;
				//-----------------------------------------------
			case 7:
				Clear_Queue(&Q); cout << "\nОчередь очищена\n\n";
				break;
				//-----------------------------------------------
			case 8:
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
				//-----------------------------------------------
			case 9:
				if (IsEmpty(&Q))
				{
					cout << "\nОчередь пуста\n\n";
					break;
				}
				cout << "\nВведите индекс < ";
				cin >> index;
				cout << "\nВведите ключ < ";
				cin >> key;
				cout << "\nВведите инф. поле < ";
				cin >> data;
				EditByIndex(&Q, index, key, data);
				cout << "\n\n";
				break;
				//-----------------------------------------------
			case 10:
				if (IsEmpty(&Q))
				{
					cout << "\nОчередь пуста\n\n";
					break;
				}
				cout << "\nВведите ключ записи < "; cin >> key1;
				cout << "\nВведите новый ключ < "; cin >> key;
				cout << "\nВведите новое инф. поле < "; cin >> data;
				EditByKey(&Q, key1, key, data);
				cout << "\n\n";
				break;
				//-----------------------------------------------
			case 11:
				if (IsEmpty(&Q))
				{
					cout << "\nОчередь пуста\n\n";
					break;
				}
				cout << "\nВведите индекс записи < "; cin >> index;
				SearchByIndex(&Q, index);
				cout << "\n\n";
				break;
			case 0:
				break;
			default:
				cout << endl << "Команда не определена\n\n";
				break;
			}
		}
	 while (number != 0);

	Clear_Queue(&Q); //обязательная очистка очереди перед выходом
	}
	if (number == 2)
	{
		do
		{
			cout << "--Статическая очередь--\n"
				"1. Добавить элемент\n"
				"2. Удалить элемент\n"
				"3. Вывести верхний элемент\n"
				"4. Узнать размер очереди\n"
				"5. Записать данные в файл\n"
				"6. Считать данные из файла\n"
				"7. Очистить очередь\n"
				"8. Поиск элемента по ключу\n"
				"9. Установка значения элемента по заданному индексу (поиск по индексу)\n"
				"10. Замена «старого» значения элемента на заданное новое (поиск по значению)\n"
				"11. Получение значения элемента по заданному индексу\n"

				"0. Выйти\n\n"
				"Номер команды > ";
			cin >> number;
			switch (number)
			{
			//-----------------------------------------------
			case 1:
				cout << "\nВведите ключ и инф. поле < ";
				cin >> key >> data;
				SqueuePush(&Sq, new SqueueItem{ key, data });
				cout << "\nЭлемент добавлен\n\n";
				break;
			//-----------------------------------------------
			case 2:
				SqueuePop(&Sq);
				break;
			//-----------------------------------------------
			case 3:
				SqueueTopPrint(&Sq);
				break;
			//-----------------------------------------------
			case 4:
				Sq.SqueueCurrentSize(&Sq);
				break;
			//-----------------------------------------------
			case 5:
				if ( Sq.SSave(&Sq, &SqI, fileNameSave) ) cout << "\nФайл перезаписан\n\n";
				else cout << "\nОшибка записи файла\n\n";
				break;
			//-----------------------------------------------
			case 6:
				if ( Sq.SLoad(&Sq, &SqI, fileNameLoad) ) //проверка удачно ли прошло чтение
					cout << "\nДанные считаны\n\n";
				else
					cout << "\nОшибка чтения данных\n\n";
				
				break;
			//-----------------------------------------------
			case 7:
				Sq.clear();
				cout << "\nОчередь очищена\n\n";
				break;
			//-----------------------------------------------
			case 8:

			case 0:
				break;
			//-----------------------------------------------
			default:
				cout << endl << "Команда не определена\n\n";
				break;
			}
		}
		while (number != 0);
	}

	return 0;
}
