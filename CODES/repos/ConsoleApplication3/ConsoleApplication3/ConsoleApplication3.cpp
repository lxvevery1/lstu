#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;
struct Node {
	int key;
	string value;
private:
	friend bool operator<(const Node& a, const Node& b) {
		if (a.key < b.key) return true;
		if (a.key == b.key) return a.value < b.value;
		return false;
	}
};
void show(const vector<Node>& box) {
	for (const auto& [key, value] : box) cout << key << ": " << value << '\n';
	puts("");
}
int main() {
	system("chcp 1251 > nul");
	vector<Node> box{
	{ 3, "раз" } ,
	{ 2, "три" } ,
	{ 1, "раз" } ,
	{ 2, "раз" } ,
	{ 4, "раз" } ,
	{ 2, "два" } ,
	{ 4, "два" } ,
	{ 5, "раз" }
	};
	show(box);
	sort(box.begin(), box.end());
	show(box);
	system("pause > nul");
}