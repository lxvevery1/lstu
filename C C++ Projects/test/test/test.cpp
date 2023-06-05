#include <iostream>

using namespace std;

class matrix {
private:
    int w;
    int h;
    int** cell;
public:

    matrix(int N, int M) {
        w = N;
        h = M;
        cell = new int* [h];
        for (int i = 0; i < w; i++) {
            cell[i] = new int[w];
        }
        for (int i = 0; i < w; i++) {
            for (int j = 0; j < h; j++) {
                cell[i][j] = i + j * 2;

            }
        }
    }

    void show() {
        for (int i = 0; i < w; i++) {
            for (int j = 0; j < h; j++) {
                cout << cell[i][j] << " ";
            }
            cout << endl;
        }
    }

    int* operator[](int i) {
        return cell[i];
    }

    ~matrix() {
        for (int i = 0; i < w; i++) {
            delete[] cell[i];
        }
        delete[] cell;
    }
};

int main() {
    setlocale(LC_ALL, "RUS");
    int h, w, indH, indW;
    cout << "Введите размеры матрицы ";
    cin >> w >> h;
    matrix A(w, h);
    A.show();
    cout << "Введите позицию в матрице для обращения и последующего вывода ";
    cin >> indH >> indW;
    cout << endl << A[indH][indW] << endl;

    system("pause");
}
