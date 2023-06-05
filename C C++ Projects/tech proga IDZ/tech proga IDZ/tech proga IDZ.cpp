#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
using namespace std;
const int V = 4; // тут менять размерность матрицы
int GR[V][V];
//алгоритм Дейкстры
void Dijkstra(int GR[V][V], int st)
{
	int distance[V], count, index, i, u, m = st + 1;
	bool visited[V];
	for (i = 0; i < V; i++)
	{
		distance[i] = INT_MAX; visited[i] = false;
	}
	distance[st] = 0;
	for (count = 0; count < V - 1; count++)
	{
		int min = INT_MAX;
		for (i = 0; i < V; i++)
			if (!visited[i] && distance[i] <= min)
			{
				min = distance[i]; index = i;
			}
		u = index;
		visited[u] = true;
		for (i = 0; i < V; i++)
			if (!visited[i] && GR[u][i] && distance[u] != INT_MAX &&
				distance[u] + GR[u][i] < distance[i])
				distance[i] = distance[u] + GR[u][i];
	}
	cout << "Стоимость пути из начальной вершины до остальных:\t\n";
	for (i = 0; i < V; i++) if (distance[i] != INT_MAX)
		cout << m << " > " << i + 1 << " = " << distance[i] << endl;
	else cout << m << " > " << i + 1 << " = " << "маршрут недоступен" << endl;
}

void customGenerate() {
	cout << "Введите матрицу веса графа " << "(n = " << V << ")\n";
	for (int i = 0; i < V; i++)
	{
		for (int j = 0; j < V; j++) {
			cin >> GR[i][j];
		}
	}
}
void randomGenerate() {
	cout << "Рандомная матрица веса графа " << "(n = " << V << ")\n";
	for (int i = 0; i < V; i++)
	{
		for (int j = 0; j < V; j++) {
			GR[i][j] = 0 + rand() % 11;

			cout << GR[i][j] << ", ";
		}
		cout << endl;
	}
}
void readfile() {
	FILE* f;
	f = fopen("file.txt", "r");
	for (int i = 0; i < V; i++)
	{
		for (int j = 0; j < V; j++)
			fscanf(f, "%d", &GR[i][j]);
	}
	fclose(f);
}
void showGR() {
	for (int i = 0; i < V; i++)
	{
		for (int j = 0; j < V; j++) {
			cout << GR[i][j] << ", ";
		}
		cout << endl;
	}
}
int main()
{
	setlocale(LC_ALL, "Rus");
	int start; size_t number;
	srand(time(0));
	while (1) {
		cout << "Как ввести матрицу смежности?";
		cout << "\n1. Кастомный ввод";
		cout << "\n2. Рандомный ввод";
		cout << "\n3. Прочесть из файла";
		cout << "\n0. Выход из программы\n";
		cin >> number;
		
		if (number == 1) {
			customGenerate();
			showGR();
			cout << "\nНачальная вершина >> "; cin >> start;
			Dijkstra(GR, start - 1);
		}
		if (number == 2) {
			randomGenerate();
			cout << "\nНачальная вершина >> "; cin >> start;
			Dijkstra(GR, start - 1);
		}
		if (number == 3) {
			readfile();
			showGR();
			cout << "\nНачальная вершина >> "; cin >> start;
			Dijkstra(GR, start - 1);
		}
		if (number == 0)
			break;
	}
	system("pause");
	return 0;
}