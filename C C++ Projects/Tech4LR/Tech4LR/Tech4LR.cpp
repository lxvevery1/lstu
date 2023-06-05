#include <iostream>
#include <vector>

//ОТЛИЧНАЯ ПРОГРАММА РАБОТАЛ 8 ДНЕЙ БЕЗ ОТДЫХА

using namespace std;

const size_t blockSize = 9;

struct record //запись с данными
{
	float key; //ключ
	vector<int> intData; //должен быть массивом
	vector<char> charData; // должен быть массивом
	float floatData; //инфа
};

struct block //блок
{
	size_t      cnt;                //кол-во записей в блоке
	record      cells[blockSize];   //ячейки блока
	block* prev = nullptr;     //предыдущий элемент
	block* next = nullptr;     //следующий элемент
};

struct blockList //список
{
	block* head = nullptr;     //указатель на голову списка
	block* tail = nullptr;     //указатель на хвост списка
};

void blockList_add_begin(blockList* l, record* r) //добавляет запись в начало списка
{
	if (!l || !r)
		return;

	//Если список пуст (указатель на голову == nullptr)
	if (!l->head) {
		//Создаем новый блок c этой записью и задаем head
		l->head = new block{ 1, *r };
		//также задаем tail, т.к. это один блок
		l->tail = l->head;
		//выходим
		return;
	}

	//Если сюда попали, значит список не пуст
	//Если блок в начале (head) может вместить данные
	if (l->head->cnt < blockSize)
	{ 
		//сдвигаем содержимое блоков на 1, освобождая 0 место
		for (size_t i = l->head->cnt; i > 0; i--) 
		{
			l->head->cells[i] = l->head->cells[i - 1];
		}
		//на освободившееся записываем данные
		l->head->cells[0] = *r;
		//увеличиваем счетчик записей
		l->head->cnt++;
		//выходим
		return;
	}
	else if (l->head->cnt >= blockSize && l->head->next->cnt < blockSize)
	{
		for (int i = l->head->next->cnt; i > 0; i--) 
		{
			l->head->next->cells[i] = l->head->next->cells[i - 1]; //сдвигаем содержимое след. блока на 1 вправо
		}
		l->head->next->cells[0] = l->head->cells[blockSize - 1]; // помещаем в нулевую позицию последний элемент текущего блока
		l->head->next->cnt++; //увеличиваем счетчик следующего блока

		for (int j = blockSize-1; j > 0; j--)
		{
			l->head->cells[j] = l->head->cells[j - 1]; //сдвигаем содержимое текущего блока на 1 вправо
		}
		l->head->cells[0] = *r;
		
		return;
	}
	else
	{
		//Если сюда попали, значит список не пуст и нет мест в head
		//создаем новый блок с записью
		block* p = new block{ 1, *r };
		//связываем блоки
		p->next = l->head;
		l->head = p;
		return;
	}
}
void blockList_add_end(blockList* l, record* r)//добавляет запись в конец списка
{
	//если l или r == nullptr
	if (!l || !r)
		//выходим
		return;

	//если список пуст (указатель на голову == nullptr)
	if (!l->head) 
	{
		//создаем новый блок и задаем head
		l->head = new block{ 1, *r };
		//также задаем tail, т.к. это один блок
		l->tail = l->head;
		//выходим
		return;
	}

	//если попали сюда, значит список не пуст и ищем свободный блок
	//перемещаясь по списку с головы до хвоста
	for (block* currentBlock = l->head; currentBlock; currentBlock = currentBlock->next) 
		if (currentBlock = l->tail){{
		//если текущий блок может вместить в себя запись
				if (currentBlock->cnt < blockSize) 
				{
					//добавляем её
					currentBlock->cells[currentBlock->cnt] = *r;
					//увеличиваем счетчик записей
					currentBlock->cnt++;
					//выход
					return;
				}
		}
	}

	//если попали сюда, значит свободных блоков не было, надо добавить новый
	block* p = new block{ 1, *r };
	//у последнего элемента next связываем с новым блоком
	l->tail->next = p;
	//связываем новый элемент с предыдущим последним
	p->prev = l->tail;
	//передвигаем хвост на созданный блок
	l->tail = p;
}

void blockList_add_custom(blockList* l, record* r, size_t indexBlock, const size_t indexCell) //Удаление строчки
{
	//если l или r == nullptr
	if (!l || !r)
		//выходим
		return;

	block* temp = l->head;
	//Если список пуст (указатель на голову == nullptr)
	if (!temp)
	{
		//Создаем новый блок c этой записью и задаем head
		temp = new block{ 1, *r };
		//выходим
		return;
	}
	/*считаем блоки, не доходя до последнего.
	Если это последний блок, проверяем не превышало значение indexBlock фактическому
	количеству блоков. Если нет, тогда добавляем из массива записей этого блока переданные в функцию
	номер блока->номер строчки, при условии, что indexCell < blockSize*/
	while (indexBlock != 0 && temp != l->tail) // перемещаемся по блоклисту в поиске нужного юзерблока
	{
		temp = temp->next;
		indexBlock--;
	}
	if (indexBlock == 0 && indexCell < blockSize) // Когда нашли
	{
		if (temp->cnt < blockSize) // Есть свободные слоты?
		{
			for (size_t i = temp->cnt; i > indexCell; i--) // смещаем
			{
				temp->cells[i] = temp->cells[i - 1];
			}
			//на освободившееся место записываем данные
			temp->cells[indexCell] = *r;
			//увеличиваем счетчик записей
			temp->cnt++;
			//выходим
			return;
		}
		else if (temp->cnt >= blockSize && temp->next->cnt < blockSize)
		{
			for (int i = temp->next->cnt; i > 0; i--)
			{
				temp->next->cells[i] = temp->next->cells[i - 1]; //сдвигаем содержимое след. блока на 1 вправо
			}
			temp->next->cells[0] = temp->cells[blockSize - 1]; // помещаем в 0 позицию последний элемент текущего блока
			temp->next->cnt++; //увеличиваем счетчик следующего блока

			for (int j = blockSize - 1; j > indexCell; j--)
			{
				temp->cells[j] = temp->cells[j - 1]; //сдвигаем содержимое текущего блока на 1 вправо
			}
			temp->cells[indexCell] = *r;
			return;
		}
		else
		{
			//Если сюда попали, значит список не пуст и нет мест в temp[indexBlock]
			//создаем новый блок с записью 
			block* k = new block{ 1, *r };
			//связываем блоки
			k->next = temp->next;
			temp->next = k;
			k->prev = temp;
			return;
		}
	}
}
void blockList_edit_custom(blockList* l, const record* r, size_t indexBlock, const size_t indexCell) //Изменение строчки
{
	//если l или r == nullptr
	if (!l || !r)
		//выходим
		return;
	block* temp = l->head;
		/*считаем блоки, не доходя до последнего. Если это последний блок, проверяем не превышало значение indexBlock фактическому количеству блоков. Если нет,  тогда добавляем в массив записей этого блока переданную в функцию запись, при условии, что indexCell < blockSize*/
		while (indexBlock != 0 && temp != l->tail) 
		{
			temp = temp->next;
			indexBlock--;
		}
		if (indexBlock == 0 && indexCell < blockSize)
		{
			if (temp->cnt <= blockSize)
			{
				//на указанное место перезаписываем данные
				temp->cells[indexCell] = *r;
				//выходим
				return;
			}
		}
}
void blockList_delete_custom(blockList* l, size_t indexBlock, const size_t indexCell) //Удаление строчки
{
	//если l или r == nullptr
	if (!l)
		//выходим
		return;
	block* temp = l->head;
	/*считаем блоки, не доходя до последнего.
	Если это последний блок, проверяем не превышало значение indexBlock фактическому
	количеству блоков. Если нет, тогда удаляем из массива записей этого блока переданные в функцию
	номер блока->номер строчки, при условии, что indexCell < blockSize*/
	while (indexBlock != 0 && temp != l->tail) // перемещаемся по блоклисту в поиске нужного юзерблока
	{
		temp = temp->next;
		indexBlock--;
	}
		if (temp->cnt > 1) { // если в текущем блоке остаются элементы (т.е. cnt > 1), то сдвинуть содержимое
		//блока на одну позицию влево, начиная с последней заполненной ячейки,
		//до позиции удаляемого элемента; уменьшить счетчик на единицу
			{
				for (size_t i = indexCell+1; i < temp->cnt; i++) // Сдвигаем влево
				{
					temp->cells[i-1] = temp->cells[i];
				}
				//Удаляем ячейку
				temp->cnt--;
				//выходим
				return;
			}
		}
	if (temp->cnt <= 1) { //исключить опустевший блок полностью, удалив узел в двусвязном списке, настроив указатели previous и next, где необходимо
			//связываем указ. предыдущего элемента, указывающий на следующий с указателем на следующим за temp
			if (temp->prev)
				temp->prev->next = temp->next;
			//если за удаляемым ещё есть элемент - связываем его prev с предыдущим temp
			if (temp->next)
				temp->next->prev = temp->prev;
			if (temp == l->head)
				l->head = temp->next;
			if (temp == l->tail)
				l->tail = temp->prev;
			//Удаляем из памяти
			delete temp;
			return;
		}
}

void Search_record(blockList* l, record* r)
{
	for (block* currentBlock = l->head; currentBlock; currentBlock = currentBlock->next)  // перемещаемся по блокам
	{
		for (size_t j = 0; j < currentBlock->cnt; j++)
		{
			//если значения ключей совпадают
			if (r->key == currentBlock->cells[j].key)
			{
				cout << "Result of searching: ";
				//выводим их инфу
				for (size_t i = 0; i < currentBlock->cells[j].intData.size(); i++)
				{
					cout << currentBlock->cells[j].intData[i] << " ";
				}
				for (size_t i = 0; i < currentBlock->cells[j].charData.size(); i++)
				{
					cout << currentBlock->cells[j].charData[i] << " ";
				}
				cout << currentBlock->cells[j].floatData << endl;
			}
		}
	}
}

void record_print(record* r) { // Функция перебора каждого значения в блоке + вывод
	if (!r)
		return;

	cout <<
		"{" << endl
		<< "  key\t:" << r->key << endl
		<< "  data\t:";

	for (size_t i = 0; i < r->intData.size(); i++)
	{
		cout << r->intData[i] << " ";
	}
	for (size_t i = 0; i < r->charData.size(); i++)
	{
		cout << r->charData[i] << " ";
	}

	cout << r->floatData
		<< endl
		<< "}" << endl;
}
void blockList_printItem(block* p) { // Вызывает функцию вывода содержимого блока + его вместимость
	if (!p)
		return;

	cout << "block (capacity:" << blockSize - p->cnt << ")\n";
	for (size_t i = 0; i < p->cnt; i++)
	{
		record_print(&p->cells[i]);
	}
}
void blockList_print(blockList* l) //Функция пробегается по всем блокам и применяет к ним предыдущую функцию
{
	if (!l)
		return;

	for (block* currentBlock = l->head; currentBlock; currentBlock = currentBlock->next) 
	{
		blockList_printItem(currentBlock);
	}
}


void record_Just_print(record* r) { // Функция перебора каждой cells в блоке + вывод
	if (!r)
		return;

	cout << r->key << " ";

	for (size_t i = 0; i < r->intData.size(); i++)
	{
		cout << r->intData[i] << " ";
	}
	for (size_t i = 0; i < r->charData.size(); i++)
	{
		cout << r->charData[i] << " ";
	}

	cout << r->floatData
		<< endl;
}
void blockList_Just_printItem(block* p) { // Вызывает функцию вывода содержимого блока + проход по всему блоку
	if (!p)
		return;

	for (size_t i = 0; i < p->cnt; i++)
	{
		record_Just_print(&p->cells[i]);
	}
}
void blockList_Just_Print(blockList* l)
{
	if (!l)
		return;
	for (block* currentBlock = l->head; currentBlock; currentBlock = currentBlock->next) {
		blockList_Just_printItem(currentBlock);
	}
}

void blockList_clear(blockList* l)
{
	if (!l)
		return;

	for (block* currentBlock = l->head; currentBlock;)
	{
		block* tmp = currentBlock;
		currentBlock = currentBlock->next;
		delete tmp;
	}

	l->head = nullptr;
	l->tail = nullptr;
}

int main()
{
	
	blockList l;
	// blok 0
	blockList_add_end(&l, new record{ 2, {1, 5}, {'g', 'J', 'K'}, 1.5});
	blockList_add_end(&l, new record{ 5, {3, 5}, {'e', 'J', 'K'}, 5.2 });
	blockList_add_end(&l, new record{ 6, {2, 5}, {'g', 'J', 'm'}, 7.5 });
	blockList_add_end(&l, new record{ 8, {3, 5}, {'f', 'J', 'K'}, 3.5 });
	blockList_add_end(&l, new record{ 12, {3, 5}, {'g', 'J', 'K'}, 5.5 });
	blockList_add_end(&l, new record{ 3, {3, 5}, {'g', 'g', 'K'}, 4.5 });
	blockList_add_end(&l, new record{ 7, {4, 67, 76,45}, {'D', 'Z', 'x', 'C'}, 5.3 });
	blockList_add_end(&l, new record{ 4, {4,34}, {'E','F'}, 4.0 });
	blockList_add_end(&l, new record{ 5, {5,35}, {'G','H'}, 5.0 });
	// blok 1
	blockList_add_end(&l, new record{ 3, {3,33}, {'D'}, 3.0 });
	blockList_add_end(&l, new record{ 4, {4,34}, {'E','F'}, 4.0 });
	blockList_add_end(&l, new record{ 5, {5,35}, {'G','H'}, 5.0 });
	blockList_add_end(&l, new record{ 6, {6,36}, {'I'}, 6.1 });
	blockList_add_end(&l, new record{ 1, {1,31}, {'A','B'}, 1.0 });
	blockList_add_end(&l, new record{ 2, {2,32}, {'C'}, 2.0 });
	blockList_add_end(&l, new record{ 4, {4,34}, {'E','F'}, 4.0 });
	blockList_add_end(&l, new record{ 9, {9,777}, {'D','b'}, 4.0 });
	blockList_add_end(&l, new record{ 5, {5,35}, {'G','H'}, 5.0 });
	// blok 2
	blockList_add_end(&l, new record{ 9, {9,777}, {'D','b'}, 4.0 });
	blockList_add_end(&l, new record{ 5, {5,35}, {'G','H'}, 5.0 });

	int N, n;
	char P;
	int K;
	cout << "---Main menu---" << endl
		<< "1. Input to the start" << endl
		<< "2. input to the end" << endl
		<< "3. Input to the custom position" << endl
		<< "4. Delete the custom position" << endl
		<< "5. Edit the custom position" << endl
		<< "6. Clear block list" << endl
		<< "7. Search by the key" << endl
		<< "8. Output info" << endl
		<< "9. Output better info" << endl
		<< "10. Exit" << endl;

	while (1)
	{
		cin >> N;
		if (N == 1)
		{
			cout << "1. Input to the start:" << endl;
			record r;
			cout << "Input key: ";
			cin >> r.key;

			cout << "input intData: ";
			cin >> n;
			for (int i = 0; i < n; i++) //один способ
			{
				cin >> K;
				r.intData.push_back(K);
			}
			char P;
			cout << "input charData: ";
			cin >> n;
			for (int i = 0; i < n; i++) //один способ
			{
				cin >> P;
				r.charData.push_back(P);
			}
			cout << "input floatData: ";
			cin >> r.floatData;

			blockList_add_begin(&l, &r);
		}
		if (N == 2)
		{
			cout << "2. Input to the end:" << endl;
			record r;
			cout << "Input key: ";
			cin >> r.key;

			cout << "input intData: ";
			cin >> n;
			for (int i = 0; i < n; i++) //один способ
			{
				cin >> K;
				r.intData.push_back(K);
			}
			char P;
			cout << "input charData: ";
			cin >> n;
			for (int i = 0; i < n; i++) //один способ
			{
				cin >> P;
				r.charData.push_back(P);
			}
			cout << "input floatData: ";
			cin >> r.floatData;

			blockList_add_end(&l, &r);
		}
		if (N == 3)
		{
			size_t indexBlock, indexCell; record r;
			cout << "3. Input to the custom position:" << endl;
			cout << "Input index of block:"; cin >> indexBlock;
			cout << "Input index of cell:"; cin >> indexCell;
			cout << "Input key: ";
			cin >> r.key;

			cout << "input intData: ";
			cin >> n;
			for (int i = 0; i < n; i++) //один способ
			{
				cin >> K;
				r.intData.push_back(K);
			}
			char P;
			cout << "input charData: ";
			cin >> n;
			for (int i = 0; i < n; i++) //один способ
			{
				cin >> P;
				r.charData.push_back(P);
			}
			cout << "input floatData: ";
			cin >> r.floatData;

			blockList_add_custom(&l, &r, indexBlock, indexCell);
		}
		if (N == 4)
		{
			size_t indexBlock, indexCell;
			cout << "4. Delete the custom position :" << endl;
			cout << "Input index of block:"; cin >> indexBlock;
			cout << "Input index of cell:"; cin >> indexCell;
			blockList_delete_custom(&l, indexBlock, indexCell);
		}
		if (N == 5)
		{
			size_t indexBlock, indexCell; record r;
			cout << "5. Edit the custom position:" << endl;
			cout << "Input index of block: "; cin >> indexBlock;
			cout << "Input index of cell: "; cin >> indexCell;
			cout << "Input key: ";
			cin >> r.key;

			cout << "input intData: ";
			cin >> n;
			for (int i = 0; i < n; i++) //один способ
			{
				cin >> K;
				r.intData.push_back(K);
			}
			char P;
			cout << "input charData: ";
			cin >> n;
			for (int i = 0; i < n; i++) //один способ
			{
				cin >> P;
				r.charData.push_back(P);
			}
			cout << "input floatData: ";
			cin >> r.floatData;

			blockList_edit_custom(&l, &r, indexBlock, indexCell);
		}
		if (N == 6)
		{
			blockList_clear(&l);
		}
		if (N == 7)
		{
			cout << "7. Search by the key: " << endl;
			record r;
			cout << "Input key: ";
			cin >> r.key;

			Search_record(&l, &r);
		}
		if (N == 8)
		{
			blockList_Just_Print(&l);
		}
		if (N == 9)
		{
			blockList_print(&l);
		}
		if (N == 10)
		{
			cout << "10. Exit";
			break;
		}
	}
}