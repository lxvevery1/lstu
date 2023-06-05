#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
using namespace std;
unsigned integer(istream& inp, const char* msg) {
cout << msg;
unsigned value;
inp >> value;
inp.ignore(inp.rdbuf()->in_avail());
return value;
}
struct Home {
unsigned number;
unsigned level;
char name[0x30];
Home() : number(0), level(0) {
memset(name, 0, sizeof(name));
}
friend istream& operator>>(istream& inp, Home& h) {
cout << "Название улицы: ";
inp.getline(h.name, size(h.name));
h.number = integer(inp, "Номер дома: ");
h.level = integer(inp, "Количество этажей: ");
return inp;
}
friend ostream& operator<<(ostream& out, const Home& h) {
return out << "Улица " << h.name << ", дом " << h.number << ", этажей: " << h.level;
}
} ;
void show(const char* title, Home* box, const size_t n) {
cout << '\t' << title << '\n';
for (auto i = 0U; i < n; ++i) cout << box[i] << '\n';
puts("");
}
int main() {
system("chcp 1251 > nul");
Home box[5];
for (auto& x : box) cin >> x;
box[size(box) - 1].level = 12;
show("После изменения этажности в последней записи:", box, size(box));
cout << "Улица " << box[1].name << "\n\n";
auto count = 0U;
auto num = integer(cin, "Введите номер дома: ");
for (const auto& x : box) {
if (x.number == num) {
cout << x << '\n';
++count;
break;
}
}
cout << "Итого: найдено " << count << " совпадений\n";
size_t i, j;
do {
i = integer(cin, "Введите первый индекс: ");
} while (!i || i >= size(box));
do {
j = integer(cin, "Введите первый индекс: ");
} while (!j || j >= size(box) || j == i);
swap(box[i], box[j]);
show("После обмена: ", box, size(box));
sort(begin(box), end(box), [](const Home& a, const Home& b) {
return string(a.name) > string(b.name);
} );
show("После сортировки по названию: ", box, size(box));
sort(begin(box), end(box), [](const Home& a, const Home& b) {
return a.number > b.number;
} );
show("После сортировки по номеру дома: ", box, size(box));
sort(begin(box), end(box), [](const Home& a, const Home& b) {
return a.level > b.level;
} );
show("После сортировки по этажности: ", box, size(box));
do {
i = integer(cin, "Введите индекс: ");
} while (!i || i >= size(box));
cout << box[i] << '\n';
do {
i = integer(cin, "Введите первый индекс диапазона: ");
} while (!i || i >= size(box));
do {
j = integer(cin, "Введите первый индекс диапазона: ");
} while (!j || j >= size(box) || j == i);
for (auto f = i; f <= j; ++f) cout << box[f] << '\n';
system("pause > nul");
}