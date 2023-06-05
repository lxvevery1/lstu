#include <iostream>
#include <windows.h>

#pragma comment(lib, "Winmm.lib")
using namespace std;

struct Node
{
	int key = 0; //ключ
	int id = 0; //индекс
	int level = 0; //уровень в иерархии
	Node* parent = nullptr; //указатель на родителя
	Node** son = nullptr; //массив указателей на сыновей
	int count_son = 0; //количество сыновей
};

Node* Root(Node* node)
{
	return node;
}

Node* createTree(Node* node, int id, int level, int dispersion, int maxlvl)
{
	if (node->level < maxlvl) {
		node->id = id;
		node->level = level;
		node->key = rand() % 100;

		node->count_son = rand() % ((4 + dispersion)-(4 - dispersion)+1)+(4 - dispersion); //dispersion can't be > than 4; [b-a+1] + a
		node->son = new Node * [node->count_son];
		level++;

		for (int i = 0; i < node->count_son; i++)
		{
			node->son[i] = new Node;
			node->son[i]->parent = node;
			if (node->level!=0)
			node->son[i]->id = i; //i
			node->son[i]->level = level;
			node->son[i]->key = rand() % 100;
		}
		for (int i = 0; i < node->count_son; i++)
			createTree(node->son[i], i, level, dispersion, maxlvl);
		return node;
	}
	else node->count_son = 0;
	return node;
}

void printTree(Node* node)
{
	if (node != nullptr) {
		if (node->level >= 0) {
			for (int i = 0; i < node->level; i++) cout << "| ";
			if (node->son != NULL) cout << "[+]";
			cout << "(" << node->level << "-" << node->key << ")" << endl;
			if (node->count_son > 0)
				for (int i = 0; i < node->count_son; i++)
					printTree(node->son[i]);
		}
	}
}

Node* Find(Node* node, int key) // Ищет узел с указанным ключом
{
	if (node != nullptr) 
	{
		if (node->key == key)
			return node;
		if (node->count_son > 0)
		{
			for (int i = 0; i < node->count_son; i++)
			{
				auto found = Find(node->son[i], key);
				if (found)
					return found;
			}
		}
	}
	return nullptr;
}

Node* FindNonKey(Node* node, int level, int id) // Ищет узел с указанным ключом
{
	if (node->level == level && node->id == id)
		return node;
	if (node->count_son > 0) 
	{
		for (int i = 0; i < node->count_son; i++)
		{
			auto found = FindNonKey(node->son[i], level, id);
			if (found)
				return found;
		}
	}
	return nullptr;
}

int editKey(Node* node, int key, int keykey)
{
	auto found = Find(node, key);
	if (found) {
		found->key = keykey;
		return found->key;
	}
	return 0;
}

Node* parentNode(Node* node, int key)//возвращает предка
{
	auto Node = Find(node, key); 
	auto ParentNode = Node->parent;
	return ParentNode;
}

bool nodeKill(Node* root, int key)
{
	Node* DelNode = Find(root, key); Node* ParentNode = DelNode->parent; Node* NewNode;

	//0-ой случай, когда дерево пустое
	if (DelNode == NULL)
		return true;

	if (DelNode->count_son == 0)
	{
		DelNode->parent = nullptr;
		ParentNode->son[DelNode->id] = nullptr;
		if (DelNode == ParentNode->son[ParentNode->count_son])
			ParentNode->count_son--;
		DelNode = nullptr;
		delete DelNode;
		
		return true;
	}

	//1-ый случай, если сын один
	if (DelNode->count_son == 1)
	{
		NewNode = DelNode->son[0];
		NewNode->parent = ParentNode;
		ParentNode->son[ParentNode->count_son - 1] = NewNode;
		NewNode->level = DelNode->level;
		NewNode->id = DelNode->id;
		delete DelNode;

		return true;
	}

	//2-ой случай, когда дерево имеет несколько потомков
	if (DelNode->count_son > 1)
	{
		NewNode = DelNode->son[0];
		NewNode->level = DelNode->level;
		NewNode->id = DelNode->id;
		for (int i = 0; i < ParentNode->count_son; i++)
		{
			if (ParentNode->son[i] == DelNode) {
				ParentNode->son[i] = NewNode;
				break;
			}
		}
		NewNode->parent = ParentNode;// указателю родителя дочернего узла присваиваем адрес родительского узла удаляемого элемента теперь удаляемый элемент исключен из дерева и как бы висит в воздухе вместе с потомками, кроме самого левого
		// нужно оставшихся потомков перепривязать к новому узлу
		Node** tmp = new Node * [NewNode->count_son + DelNode->count_son - 1];
		for (int j = 0; j < NewNode->count_son; j++)
			tmp[j] = NewNode->son[j];

		for (int j = 1; j < DelNode->count_son; j++) // копируем все указатели на потомков из удаляемого узла в новый массив нового узла
			tmp[NewNode->count_son + j - 1] = DelNode->son[j];

		delete[] NewNode->son; // удаляем старый массив указателей на потомков
		NewNode->son = tmp; // запоминаем новый массив указателей 
		NewNode->count_son = DelNode->count_son - 1; // сохраняем новое количество потомков
		
		// Теперь удаляем старый узел
		delete[] DelNode->son; // сначала удаляем массив указателей на потомков
		delete DelNode;

		return true;
	}
	return false;
}

int countSon(Node* node, int key)
{
	auto found = Find(node, key);
	return found->count_son;
}

Node* nodeAdd(Node* node, int key, int keykey)
{
	auto found = Find(node, key);
	Node* NewNode = new Node;

	if (found->count_son > 0) 
	{
		NewNode->parent = found;
		NewNode->son = nullptr;
		NewNode->key = keykey;
		NewNode->level = found->level + 1;
		found->son[found->count_son] = NewNode;
		found->count_son++;
	}
	else 
	{
		found->son = new Node*[1];
		found->son[0] = NewNode;
		found->count_son++;
		NewNode->parent = found;
		NewNode->son = nullptr;
		NewNode->key = keykey;
		NewNode->level = found->level + 1;
		NewNode->id = 0;
	}
	
	return NewNode;
}

Node* leftSonNode(Node* node, int key)//возвращает самого левого сына
{
	auto Node = Find(node, key);
	if (Node->count_son > 0) {
		auto SonNode = Node->son[0];
		return SonNode;
	}
	return NULL;	
}

Node* rightSiblingNode(Node* node, int key)//возвращает самого правого брата
{
	auto found = Find(node, key);
	for (auto i = 1; i < found->parent->count_son; i++) {
		if (found->parent->son[found->parent->count_son - i] != nullptr) {
			auto SiblingNode = found->parent->son[found->parent->count_son - i];

			return SiblingNode;
		}
	}
}

void clearTree(Node* node) 
{
	if (node == NULL) return;
	for (int i = 0; i < node->count_son; i++)
		clearTree(node->son[i]);
	delete node;
}

int main()
{
	setlocale(LC_ALL, "");
	int key, level, id, keykey, dispersion; Node* root; size_t N; int const maxlvl = 2;
	root = new Node; root->parent = nullptr;
	cout << "Введите значение дисперсии: "; cin >> dispersion;
	if (dispersion >= 4) 
	{
		cout << "Дисперсия не может быть >= 4";
		return 0;
	}
	root->parent = root; // Это для 7
	root = createTree(root, 0, 0, dispersion, maxlvl);
	cout << "\n-----Получившееся дерево-----\n";
	printTree(root);
	while (1) {
		cout << "\n---Главное меню---";
		cout << "\n1. Вернуть корень.";
		cout << "\n2. Изменить ключ узла.";
		cout << "\n3. Поиск в дереве по ключу.";
		cout << "\n4. Добавить узел как дочернюю вершину.";
		cout << "\n5. Удалить узел по ключу.";
		cout << "\n6. Вернуть родителя узла.";
		cout << "\n7. Вернуть самого левого сына узла.";
		cout << "\n8. Вернуть правого соседа (левого, если !правый).";
		cout << "\n9. Сделать дерево пустым.";
		cout << "\n10. Вывести дерево.";
		cout << "\n0. Выход.\n";
		cin >> N;
		if (N == 1)
		{
			auto rootc = Root(root);
			cout << rootc->key;
		}
		/*if (N == 2)
		{
			cout << "\nВведите уровень и индекс узла, ключ которого хотите найти > ";
			cin >> level >> id;
			auto found = FindNonKey(root, level, id);
			cout << found->key << "\n";
		}*/
		if (N == 2)
		{
			cout << "\nВведите ключ узла, который хотите изменить > ";
			cin >> key;
			cout << "\nВведите новый ключ > ";
			cin >> keykey;
			if (editKey(root, key, keykey)) cout << "\nКлюч изменён\n";
			else cout << "\nОшибка в изменении ключа\n";
		}
		if (N == 3)
		{
			cout << "\nВведите ключ узла, который хотите найти > "; cin >> key;
			auto found = Find(root, key);
			cout << found->level << "-" << found->id << "\n";
		}
		if (N == 4)
		{
			cout << "\nВведите ключ узла, которому хотите добавить сына > "; cin >> key;
			cout << "\nВведите ключ узла, который хотите присвоить новому сыну > "; cin >> keykey;
			if (nodeAdd(root, key, keykey))	cout << "\nДочерний узел добавлен\n";
			else cout << "\nДобавить узел не удалось\n";
		}
		if (N == 5)
		{
			cout << "\nВведите ключ узла, которого хотите убить > "; cin >> key;
			if (nodeKill(root, key)) cout << "\nУзел удалён\n";
			else cout << "\nОшибка в удалении узла\n";
		}
		if (N == 6)
		{
			cout << "\nВведите ключ узла, если хотите познакомиться с его родителями > "; cin >> key;
			auto found = parentNode(root, key);
			if (found) cout << found->key;
			else cout << "\nВернуть отца не удалось...\n";
		}
		if (N == 7)
		{
			cout << "\nВведите ключ узла, если хотите узнать его левого сына поближе > "; cin >> key;
			auto found = leftSonNode(root, key);
			if (found) cout << found->key;
			else cout << "\nВернуть сына не удалось...\n";
		}
		if (N == 8)
		{
			cout << "\nВведите ключ узла, если хотите узнать его правого брата поближе > "; cin >> key;
			auto found = rightSiblingNode(root, key);
			if (found) cout << found->key;
			else cout << "\nВернуть брата не удалось...\n";
		}
		if (N == 9) {
			clearTree(root);
			cout << "\nДерево очищено";
		}
		if (N == 10)
		{
			printTree(root);
		}
		/*if (N == 12) {
			cout << "Введите ключ: "; cin >> key;
			cout << countSon(root, key);
		}*/
		if (N == 0) {
			clearTree(root); //очищаем память + выходим
			break;
		}
	}
	return 0;
}