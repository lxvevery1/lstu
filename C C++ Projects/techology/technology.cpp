#include <iostream>

using namespace std;

int main()
{
    int N, max, min, L, k;
    cout << "Enter an array size:" << endl;
    cout << "N = ";
    cin >> N;
    int* A = new int[N];
    max = INT_MIN;
    min = INT_MAX;
    cout << "Enter an array:" << endl;
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
        if (A[i] > max)
            max = A[i];
        if (A[i] < min)
            min = A[i];
    }
    L = max - min + 1;
    int* B = new int[L];
    for (int i = 0; i < L; i++)
    {
        B[i] = 0;
    }
    for (int i = 0; i < N; i++)
    {
        B[A[i] - min]++;
    }
    k = 0;
    for (int i = 0; i < L; i++)
    {
        for (int j = 0; j < B[i]; j++)
        {
            A[k++] = i + min;
        }
    }
    cout << "Array after sorting:" << endl;
    for (int i = 0; i < N; i++)
    {
        cout << A[i] << " ";
    }
    cout << endl;
    delete[] A;
    delete[] B;
    system("pause");
    return 0;
}