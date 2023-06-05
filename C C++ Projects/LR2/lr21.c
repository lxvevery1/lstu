//33. Исправьте ошибки в коде
#include<conio.h>
#include<stdio.h>
#include<windows.h>
#include<locale.h>
//Задача №33 из задачника
int main()
{
//Объявляем переменные - целые числа
setlocale(LC_ALL, "");
int x, y;
//Исправляем кодовую страницу
//не забыть исправить шрифт после запуска программы на "Lucida Console"
SetConsoleOutputCP(1251); //на вывод
SetConsoleCP(1251); //на ввод - в этой программе не обязательно
//Запрашиваем значения переменных с клавиатуры
printf("Введите значение x ");
scanf("%d", &x);
printf("Введите значение y ");
scanf("%d", &y);
printf("Задание а)\n");
if(x>y)
printf("max=x=%d\n",x);
else
printf("max=y=%d\n",y);
printf("Задание б)\n");
if(x<y) {
printf("min=x=%d\n",x);
}
else {
printf("min=y=%d\n",y);
}
printf("Задание в)\n");
if(x<y)
{
printf("min=x=%d\n",x);
printf("max=y=%d\n",y);
}
else
{
printf("min=y=%d\n",y);
printf("max=x=%d\n",x);
}
getch();
return 0;
}
