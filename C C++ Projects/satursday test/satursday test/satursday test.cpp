#include<stdlib.h>
#include<cstdlib>
#include<cstdint>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#define N 20

struct book
{
    float* Index;
    char* Name;
    int Value;
} inform[N];

void Sort_By_Change(struct book* array, int size);

int main()
{
    srand(time(NULL));
    printf("\t\t ***Начинаю разбиение на ленты***\t\t\n");
    for (int i = 0; i < N; i++) {
        inform[i].Value = rand() % 101 - 51;
        printf("%d ", inform[i].Value);
    }
    printf("\n");
    int const Elem_at_Tape = ceil(sqrt(N));
    int const Numb_of_Tapes = ceil((float)N / Elem_at_Tape);
    printf("\n%d - количество элементов в ленте, %d - количество лент\n\n", Numb_of_Tapes, Elem_at_Tape);

    struct book Tape[Numb_of_Tapes][Elem_at_Tape];
    int k = 0;
    int buffer = 1;
    printf("[");
    for (int i = 0; i < Numb_of_Tapes; i += 1) {
        for (int j = 0; j < Elem_at_Tape; j += 1) {
            if (k < N) {
                Tape[i][j] = inform[k];
            }
            else {
                Tape[i][j].Value = -1;
            }
            if (buffer % 4 != 0)
                printf("%d ", Tape[i][j].Value);
            else
                if (Tape[i][j].Value == Tape[Numb_of_Tapes - 1][Elem_at_Tape - 1].Value)
                    printf("%d]", Tape[i][j].Value);
                else
                    printf("%d] [", Tape[i][j].Value);
            k += 1;
            buffer++;
        }
    }

    printf("\n");
    printf("\t\t***Разбиение на ленты завершено***\t\t\n");
    printf("\n");
    for (int j = 0; j < Numb_of_Tapes; j += 1) {
        printf("Сортировка №%d: ", j);
        Sort_By_Change(Tape[j], Elem_at_Tape);
        for (int i = 0; i < Elem_at_Tape; i += 1) {
            printf("%d ", Tape[j][i].Value);
        }

        printf("\n");
    }

    printf("\n\t\t ***Начало слияния***\t\t\n");

    int min;
    int* temporary;
    temporary = (int*)malloc(N * sizeof(int));

    for (int i = 0; i < N; i++) {
        min = 0;

        for (int j = 0; j < Numb_of_Tapes; j += 1) {
            if ((Tape[min][temporary[min]].Value > Tape[j][temporary[j]].Value && temporary[j] < Elem_at_Tape) || temporary[min] > Elem_at_Tape - 1) {
                min = j;
            }
        }

        inform[i].Value = Tape[min][temporary[min]].Value;
        temporary[min] += 1;

        if (Tape[min][temporary[min]].Value == -1) {
            temporary[min] = Elem_at_Tape;
        }

        printf("[%d]", temporary[min]);

    }

    printf("\n\t// Каждое число означает позицию элемента в его ленте\n");
    printf("\nЗавершаю внутреннюю сортировку.\n");
    printf("\t\t***Завершение слияния***\t\t\n\n");
    printf("Отсортированный массив чисел имеет вид:\n");

    for (int i = 0; i < N; i += 1) {
        printf("%d ", inform[i].Value);
    }

}

void Sort_By_Change(struct book* num, int size)
{
    uint32_t tmp;

    for (uint32_t i = 0; i < size; ++i) {
        for (uint32_t j = size - 1; j > i; --j) {
            if (num[j - 1].Value > num[j].Value) {
                tmp = num[j - 1].Value;
                num[j - 1].Value = num[j].Value;
                num[j].Value = tmp;
            }
        }
    }
}
