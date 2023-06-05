#include <iostream>
using namespace std;
int main() {
const auto m = 1 << 6;
cout << "x: ";
double x;
cin >> x;
auto num = 1.0;
auto den = 1.0;
for (auto n = 2; n <= m; n <<= 1) {
auto a = x - n;
auto b = a + 1;
if (!b) {
puts("Division by zero!");
den = 0.0;
break;
}
num *= a;
den *= b;
}
if (den) {
auto res = num / den;
cout << "Result: " << res << '\n';
}
system("pause > nul");
}