#include <iostream>
using namespace std;


unsigned int size(const char* array)
{
    auto space = '\0';
    unsigned int size = 0;
    for(unsigned i = 0; array[i] != space; i++)
    {
        size++;
    }
    return size++;
}
unsigned int findMinWord(char* array)
{
    unsigned int j = size(array)-1;
    unsigned int min = j;
    for(int i = 0; i<j; i++)
    {
        int counter = 0;
        while(array[i] != ' ' && i != j)
        {
            counter++;
            i++;
        }
        if(counter < min)
        min = counter;
    }
    return min;
}
int main()
{
    setlocale (LC_ALL, "");
    int N;
    cout << "Введите кол-во слов: "; 
    cin >> N;
    N++;
    cin.ignore();
    char arr[N];
    cout << "Введите строку: "; 
    cin.getline(arr,N);
    cout << "Минимальное число элементов в слове: " << findMinWord(arr);
    return 0;
}