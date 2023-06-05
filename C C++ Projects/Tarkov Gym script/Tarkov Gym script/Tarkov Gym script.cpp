#include <iostream>
#include <Windows.h>
using namespace std;

void menu()
{
	cout << "Press 'X' to enable and 'Z' to disable autoclicker\n";
}

void clicker()
{
	bool clicker = false; //sets click to false
	UINT32 time = 1800;
	while (true)
	{
		if (GetAsyncKeyState('X')) //if X is pressed click = true
		{
			clicker = true;
		}
		else if (GetAsyncKeyState('Z')) //if 'Z' is pressed click = false
		{
			clicker = false;
		}
		if (clicker == true)
		{
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			Sleep(time); //you can adjust the speed of the click here
			time += 100;
		}
	}
}

int main()
{
	menu();
	clicker();

	return 0;
}