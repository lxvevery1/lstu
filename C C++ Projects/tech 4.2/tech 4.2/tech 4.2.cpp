#include <iostream>
using namespace std;

struct Node {
	int key = NULL; //ключ
	int id = NULL; //индекс
	int countson = NULL; //число потомков
	Node* sibling = nullptr; //братья
	Node* son = nullptr; //сын
};

void initAdd(Node* Root, int count, int* id, int* N)
{
	if (Root == 0)
		return;

	Node* newson = new Node;
	Node* tmp = newson;
	if (tmp != 0) {
		Root->son = newson;
		*id += 1;
		tmp->id = *id;
		tmp->key = rand() % 100;
		for (int i = 1; i < count; i++) {
			Node* newsibling = new Node;
			tmp->sibling = newsibling;
			tmp = tmp->sibling;
			*id += 1;
			tmp->id = *id;
			tmp->key = rand() % 100;
		}
	}
	*N -= count;
}

void initialise(Node* Root, int* N, int* id, int dispersion)
{
	int count;
	Node* tmp = Root;
	while (*N > 0 && tmp != nullptr) {
		do count = rand() % (4-dispersion) + dispersion;
		while (*N != 0 && *N - count < 0);
		initAdd(tmp, count, id, N);
		tmp->countson = count;

		do count = rand() % (4-dispersion) + dispersion;
		while (*N != 0 && *N - count < 0);
		if (*N <= 0) break;
		initAdd(tmp->sibling, count, id, N);
		if (tmp->sibling != 0) tmp->sibling->countson = count;
		tmp = tmp->son;
	}
}

void idsearch(Node* Root, Node** result, int* id, bool* flag)
{
	Node* tmp = Root;
	if (tmp == NULL || *flag == true)
		return;

	if (tmp->id == *id) {
		*result = tmp;
		*flag = true;
	}

	idsearch(tmp->son, result, id, flag);
	if (*flag == true)
		return;
	idsearch(tmp->sibling, result, id, flag);
	if (*flag == true)
		return;
}

void editKey(Node* Root, int* id, bool* flag)
{
	Node* tmp = Root;

	if (tmp == NULL)
		return;

	if (tmp->id == *id)
	{
		cout << "Enter new key value: ";
		cin >> tmp->key;
		*flag = true;
		return;
	}

	editKey(tmp->sibling, id, flag);
	if (*flag == true)
		return;
	editKey(tmp->son, id, flag);
	if (*flag == true)
		return;
}

void add(Node** Root, int* NodeNum, int* id)
{
	Node* tmp = *Root;
	Node* newnode = new Node;
	bool flag = false;
	if (tmp == 0) {
		newnode->key = rand() % 100;
		newnode->id = *NodeNum;
		*NodeNum = *NodeNum = 1;
		*Root = newnode;
		return;
	}
	idsearch(*Root, &tmp, id, &flag);

	if (tmp->countson >= 4) { //степень дерева = 4
		cout << "This node has the maximum number of sons!" << endl;
		return;
	}
	else {
		if (tmp->countson == 0) {
			tmp->countson++;
			tmp->son = newnode;
		}
		else {
			tmp->countson++;
			tmp = tmp->son;
			while (tmp->sibling != 0) {
				tmp = tmp->sibling;
			}
			tmp->sibling = newnode;
		}
	}
	newnode->key = rand() % 100;
	newnode->id = *NodeNum;
	*NodeNum = *NodeNum + 1;
}

void search(Node* Root, int* key, bool* flag)
{
	Node* tmp = Root;
	if (tmp == 0)
		return;
	if (tmp->key == *key) {
		cout << "id: " << tmp->id << endl;
		cout << "Key: ";
		cout << tmp->key << " ";
		*flag = true;
		return;
	}
	search(tmp->sibling, key, flag);
	if (*flag == true)
		return;
	search(tmp->son, key, flag);
	if (*flag == true)
		return;
}

void parentsearch(Node* Root, Node* parent, Node** result, int* id, bool* flag)
{
	Node* tmp = Root;
	if (tmp == 0 || *flag == true)
		return;

	if (tmp->id == *id) {
		*result = parent;
		*flag = true;
	}
	parentsearch(tmp->sibling, parent, result, id, flag);
	if (*flag == true)
		return;
	parent = tmp;
	parentsearch(tmp->son, parent, result, id, flag);
	if (*flag == true)
		return;
}

void deleteNode(Node** Root, int* id, bool* flag)
{
	Node* tmp = 0, * parent = 0, * sibling, * tmpSib, * del;
	int sonCount;

	if ((*Root)->id == *id)
	{
		del = *Root;
		sonCount = (*Root)->countson - 1;
		tmp = (*Root)->son;
		tmpSib = tmp->sibling;
		(*Root) = tmp;
		if ((*Root)->son == 0)
		{
			(*Root)->son = tmpSib;
			(*Root)->son->countson = sonCount;
		}
		else
		{
		m1:
			tmp = tmp->son;
			while (tmp->sibling != 0 && tmp->son != 0)
				tmp = tmp->sibling;
			if (tmp->countson != 0)
				goto m1;
			else
			{
				tmp->son = tmpSib;
				tmp->countson = sonCount;
			}

		}
		(*Root)->sibling = 0;
		delete del;
		return;
	}

	parentsearch((*Root), parent, &tmp, id, flag);
	if (tmp->son->id != *id)
	{
		parent = tmp;
		tmp = tmp->son;
		while (tmp->sibling->id != *id)
			tmp = tmp->sibling;
	}

	if (tmp->sibling != 0 && tmp->sibling->id == *id) {
		del = tmp->sibling;
		sibling = tmp;
		tmp = sibling->sibling;
		if (tmp->son == 0) {
			sibling->sibling = tmp->sibling;
			parent->countson--;
			delete tmp;
			return;
		}
		tmpSib = tmp->son->sibling;
		sonCount = tmp->countson - 1;
		tmp->son->sibling = tmp->sibling;
		if (tmp->son->son == 0) {
			sibling->sibling = tmp->son;
			tmp->son->son = tmpSib;
			tmp->son->countson = sonCount;
			delete del;
			return;
		}
		else
		{
			tmp = tmp->son;
		m2:
			tmp = tmp->son;
			while (tmp->sibling != 0 && tmp->son != 0)
				tmp = tmp->sibling;
			if (tmp->countson != 0)
				goto m2;
			else
			{
				tmp->son = tmpSib;
				tmp->countson = sonCount;
			}
		}
	}
	else
	{
		del = tmp->son;
		parent = tmp;
		tmp = tmp->son;
		if (tmp->son == 0)
		{
			parent->son = tmp->sibling;
			parent->countson--;
			delete del;
			return;
		}
		else
		{
			parent->son = tmp->son;
			tmpSib = tmp->son->sibling;
			tmp->son->sibling = tmp->sibling;
			sonCount = tmp->countson - 1;
			if (tmp->son->son == 0)
			{
				tmp->son->son = tmpSib;
				tmp->son->countson = sonCount;
				delete del;
				return;
			}
			else
			{
				tmp = tmp->son;
			m3:
				tmp = tmp->son;
				while (tmp->sibling != NULL && tmp->son != NULL)
					tmp = tmp->sibling;
				if (tmp->countson != 0)
					goto m3;
				else
				{
					tmp->son = tmpSib;
					tmp->countson = sonCount;
				}
			}
		}
	}
	delete del;
}

void outputKey(Node* Root, int* id, bool* flag)
{
	Node* tmp = Root;

	if (tmp == NULL)
		return;

	if (tmp->id == *id)
	{
		cout << "Key: ";
		cout << tmp->key << " ";
		*flag = true;
		return;
	}

	outputKey(tmp->sibling, id, flag);
	if (*flag == true)
		return;
	outputKey(tmp->son, id, flag);
	if (*flag == true)
		return;
}

void deleteNode(Node* Root, int idcounter)
{
	Node* tmp = Root;
	if (tmp == 0)
		return;
	if (tmp->sibling == 0 && tmp->son == 0) {
		delete tmp;
		return;
	}
	deleteNode(tmp->sibling, idcounter);
	tmp->sibling = 0;
	deleteNode(tmp->son, idcounter);
	tmp->son;
	Root = 0; idcounter = 0;
	delete tmp;
}

void print(Node* Root, int* space) // вывод дерева
{
	Node* tmp = Root;

	if (tmp->son != nullptr)
		*space += 1;

	for (int i = 0; i < *space; i++) cout << " |";
	if (tmp->son != nullptr) cout << "[+]";
	cout << "(" << Root->id << "-" << tmp->key << ")" << endl;
	if (tmp->countson > 0)
		for (int i = 0; i < tmp->countson; i++)
			print(&tmp->son[i], space);
	else return;
}


int main()
{
	setlocale(LC_ALL, "");
	int NodeNum, space = 0, idCounter = 0, choise, id, dispersion;
	bool flag = false;
	size_t N;
	Node* Root = new Node;
	Root->id = 0;
	Root->key = rand() % 100;
	cout << "---Tree creation---" << endl;
	cout << "Enter the number of entries > ";
	cin >> NodeNum;
	cout << "Enter the value of dispersion > ";
	cin >> dispersion;
	initialise(Root, &NodeNum, &idCounter, dispersion);
	idCounter++;
	while (1)
	{
		cout << endl;
		cout << "---Main menu---" << endl;
		cout << "1. Add a node" << endl;
		cout << "2. Delete a node" << endl;
		cout << "3. Search" << endl;
		cout << "4. Change the key of specific node" << endl;
		cout << "5. Clear Node" << endl;
		cout << "6. Output Node" << endl;
		cout << "7. Output key of the specific node" << endl;
		cout << "0. Exit" << endl;
		cin >> N;
		if (N == 1) {
			cout << "Enter the id of the element to which to add the new node > ";
			cin >> id;
			add(&Root, &idCounter, &id);
			cout << "Done." << endl;
		}
		if (N == 2) {
			flag = false;
			cout << "Enter the id of the element to be removed > ";
			cin >> id;
			deleteNode(&Root, &id, &flag);
		}
		if (N == 3) {
			int* key = new int;
			flag = false;
			cout << "Enter key >";
			cin >> *key;
			search(Root, key, &flag);
		}
		if (N == 4) {
			flag = false;
			cout << "Ender node id > ";
			cin >> id;
			editKey(Root, &id, &flag);
		}
		if (N == 5)
			deleteNode(Root, idCounter);
		if (N == 6)
			print(Root, &space);
		if (N == 7) {
			flag = false;
			cout << "Enter node id > ";
			cin >> id;
			outputKey(Root, &id, &flag);
		}
		if (N == 0)
			break;
	}
}
