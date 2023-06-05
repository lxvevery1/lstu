#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <cstdlib>
#include <ctime>
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

int** lent_create(int countelementinlent, int countlent) {

	int** lent = (int**)malloc(countelementinlent * sizeof(int*));

	for (int i = 0; i < countelementinlent; i++) {

		lent[i] = (int*)malloc(countlent * sizeof(int));
	}

	return lent;

}

int** sortlent(int countlent, int countelementinlent, int** lent) {

	int tmp, noSwap;

	for (int k = 0; k < countlent; k++) {

		for (int i = countelementinlent; i > 1; i--) {

			noSwap = 1;

			for (int j = 0; j < i - 1; j++) {

				if (lent[k][j] > lent[k][j + 1]) {

					tmp = lent[k][j];

					lent[k][j] = lent[k][j + 1];

					lent[k][j + 1] = tmp;

					noSwap = 0;

				}

			}

			if (noSwap == 1) {

				break;

			}

		}

	}

	return lent;

}

int main() {

	SetConsoleCP(1251);

	SetConsoleOutputCP(1251);

	int N, tmp, noSwap, zn = 0, ch = 0;

	cout << "Введите количество эллементов ленты: ";

	cin >> N;

	int* arr = new int[N];

	for (int i = 0; i < N; i++) {

		arr[i] = rand() % 401 - 200;

	}

	cout << "Введенная лента: ";

	for (int i = 0; i < N; i++) {

		cout << arr[i] << " ";

	}

	int countlent = sqrt(N);

	int countelementinlent = (N / countlent);

	cout << endl << "Количество лент: " << countlent << ", Количество элементов в каждой ленте: " << countelementinlent;

	int** lent = lent_create(countelementinlent, countlent);

	for (int i = 0; i < countlent; i++) {

		for (int j = 0; j < countelementinlent; j++) {

			lent[i][j] = arr[zn];

			zn++;

		}

	}

	sortlent(countlent, countelementinlent, lent);

	cout << endl;

	for (int i = 0; i < countlent; i++) {

		cout << "Отсортированная подлента №" << i + 1;

		for (int j = 0; j < countelementinlent; j++) {

			cout << " " << lent[i][j];

			zn++;

		}

		cout << endl;

	}

	//coedinie lent v odny

	int* biglent = new int[N];

	int* forsort = new int[countlent];

	for (int h = 0; h < N; h++) {

		for (int i = 0; i < countlent; i++) {

			forsort[i] = lent[i][0];

		}

		for (int i = countlent; i > 1; i--) {

			noSwap = 1;

			for (int j = 0; j < i - 1; j++) {

				if (forsort[j] > forsort[j + 1]) {

					tmp = forsort[j];

					forsort[j] = forsort[j + 1];

					forsort[j + 1] = tmp;

					noSwap = 0;

				}

			}

			if (noSwap == 1) {

				break;

			}

		}

		if (forsort[0] != 99999) biglent[h] = forsort[0];

		for (int i = 0; i < countlent; i++) {

			bool exit = false;

			if (biglent[h] == lent[i][0]) {

				lent[i][0] = 99999;

				exit = true;

			}

			if (exit == true) break;

		}

		sortlent(countlent, countelementinlent, lent);

	}

	cout << endl << "Отсортированная введеная лента: ";

	for (int h = 0; h < N; h++) {

		cout << " " << biglent[h] << " ";

	}

}