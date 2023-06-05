#include <iostream>
using namespace std;
int main(int argc, const char * argv[])
{
    int a[20] = { 1,2,3,4,5,6,7,7,7,8,9,9,11,11,12,16,20,20,20,20 };

    for(int * p = lower_bound(a,a+20,10);
        p != upper_bound(a,a+20,20); ++p)
        cout << *p << " ";
    cout << endl;

}