#include <iostream>
#include <sstream> 
using namespace std;
 
int main()
{
    setlocale( LC_ALL, "" );
    int i, count;
    string str;

    cout << "Введите строку:\n";
    getline(cin, str);
    while (count > i)
    {
        i=0;
        count=0;
        while (str[i])
        {
        if (str[i]=='x') count++;
        i++;
        }
        cout << "Число символов 'x': " << count << endl;        
    }
    
system("pause");
return 0;
}