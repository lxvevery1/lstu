#include <iostream>
#include <audiere.h>
#include <conio.h>

using namespace std;
using namespace audiere;

const int n = 8;
int i, j;
bool* visited = new bool[n];

int graph[n][n]; //матрица смежности графа

void customGenerate() {
	cout << "Вводи матрицу смежности графа " << "(n = " << n << ")\n";
	for (int i = 0; i < n; i++)
	{
		visited[i] = false;
		for (int j = 0; j < n; j++) {  
			cin >> graph[i][j];
		}
	}
}

void randomGenerate(){
	cout << "Рандомная матрица смежности графа " << "(n = " << n << ")\n";
	for (int i = 0; i < n; i++) 
	{
		visited[i] = false;
		for (int j = 0; j < n; j++) {
			graph[i][j] = 0 + rand() % 2;

			cout << graph[i][j] << ", ";
		}
		cout << endl;
	}
}

void DFS(int st) //поиск в глубину
{
	cout << st + 1 << " ";
	visited[st] = true;
	for (int v = 0; v <= n; v++)
		if ((graph[st][v] != 0) && (!visited[v])) // "пока не наткнемся на тупик"
			DFS(v); // "перемещаемся вдоль ребер"
}

void main()
{
	AudioDevicePtr device = OpenDevice();
	OutputStreamPtr sound = OpenSound(device, "D:\\main1.mp3", true);
	OutputStreamPtr sound1 = OpenSound(device, "D:\\func1.mp3", true);
	OutputStreamPtr sound2 = OpenSound(device, "D:\\func2.mp3", true);
	OutputStreamPtr sound3 = OpenSound(device, "D:\\goodending.mp3", true);
	sound->play();
	sound->setVolume(3.0f); sound1->setVolume(3.0f); sound2->setVolume(3.0f);

	srand(time(NULL)); //долгожданный рандом
	setlocale(LC_ALL, "Rus");
	int start; bool flag = true; size_t N;

	while (flag == true) {
		cout << "Хотите вписать свою матрицу смежности или предпочтёте довериться рандому?";
		cout << "\n1. Хочу сам!";
		cout << "\n2. Время рандома!\n";
		cin >> N;

		if (N == 1) {
			sound->stop();
			sound1->play();
			customGenerate();
			cout << "\nМатрица введена";
			flag = false;
		}
		if (N == 2) {
			sound->stop();
			sound2->play();
			randomGenerate();
			flag = false;
		}
	}

	cout << "\nСтартовая вершина >> "; cin >> start;
	
	bool* vis = new bool[n]; //массив посещенных вершин
	cout << "Порядок обхода: ";
	DFS(start - 1);
	sound1->stop(); sound2->stop();
	sound3->play();
	_getch();
	delete[] visited; // очищаем память
}