#include <iostream>
using namespace std;
// Размер лабиринта
#define Nx 5 //5
#define Ny 6 //6
// Координаты старта
#define startx 4 //4
#define starty 0 //0
// Координаты финиша
#define solx 0 //0
#define soly 5 //5


// Вывод лабиринта
void printSolution(int sol[Nx][Ny])
{
	for (int i = 0; i < Nx; i++) {
		for (int j = 0; j < Ny; j++)
			cout << " " << sol[i][j] << " ";
		cout << endl;
	}
}

// Не уходим за пределы лабиринта
bool isSafe(int maze[Nx][Ny], int x, int y)
{
	if (x >= 0 && x < Nx && y >= 0 && y < Ny && maze[x][y] == 1)
		return 1;
	return 0;
}

// Функция (алгоритм) нахождения верного пути
bool solveMazeUtil(int maze[Nx][Ny], int x, int y, int sol[Nx][Ny])
{
	if (x == solx && y == soly && maze[x][y] == 1) { // Проверяем текущий шаг на финиш
		sol[x][y] = 2;
		return 1;
	}
	
	if (isSafe(maze, x, y) == 1) 
	{
		if (sol[x][y] == 1) // Если мы сейчас находимся тут, значит этот путь уже исследован
			return 0;
		sol[x][y] = 1; // Задаем нашу позицию как исследованную
		
		// Двигаемся по x
		if (solveMazeUtil(maze, x + 1, y, sol) == 1) {
			return 1;
		}

		if (solveMazeUtil(maze, x - 1, y, sol) == 1) {
			return 1;
		}
		// Двигаемся по y
		if (solveMazeUtil(maze, x, y + 1, sol) == 1) {
			return 1;
		}
		if (solveMazeUtil(maze, x, y - 1, sol) == 1) {
			return 1;
		}
		
		// Если путь не нашелся, возвращаемся назад
		sol[x][y] = 0;
		return 0; //Если выполнился этот ретёрн, значит наш путь не подходит
	}
	return 0;
}

bool solveMaze(int maze[Nx][Ny])
{
	int sol[Nx][Ny] = { { 0, 0, 0, 0, 0, 0 }, // лабиринт решения S, который будет выглядеть иначе по окончании работы программы
			  	  	    { 0, 0, 0, 0, 0, 0 },
					    { 0, 0, 0, 0, 0, 0 },
					    { 0, 0, 0, 0, 0, 0 },
					    { 0, 0, 0, 0, 0, 0 } };
	if (solveMazeUtil(maze, startx, starty, sol) == 0) { // В параметрах функции на место x, y указываем интересующий нас старт
		cout << "Solution doesn't exist";
		return 0;
	}
	printSolution(sol);
	return 1;
}

int main()
{
	int maze[Nx][Ny] = { { 1, 0, 1, 0, 1, 1}, // В нашем алгоритме это A - заданный пользователем лабиринт
					     { 1, 1, 1, 0, 1, 1},
					     { 0, 0, 1, 0, 0, 1},
					     { 0, 1, 1, 1, 0, 1},
					     { 1, 1, 0, 1, 1, 1} };
	solveMaze(maze);
	return 0;
}