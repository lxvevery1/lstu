#include <iostream>
using namespace std;
size_t size(const char* line) 
{
    size_t n = 0;
    while (line[n]) ++n;
    return n;
}
void clear(char* line) 
{
    size_t i = 0;
    while (line[i]) line[i++] = 0;
}
void copy(char* dest, const char* src) 
{
    size_t i = 0;
    while (src[i]) 
    {
        dest[i] = src[i];
        ++i;
    }
    dest[i] = 0;
}
    char* shortest_word(const char* line) 
    {
    size_t length = size(line);
    char* word = new char[length];
    char* tmp = new char[length];
    tmp[0] = word[0] = 0;
    size_t i = 0;
    while (line[i] && line[i] == ' ') ++i;
    size_t j = 0;
    while (line[i] && line[i] != ' ') word[j++] = line[i++];
    word[j] = 0;
    j = 0;
    while (line[i]) 
    {
    if (line[i] == ' ' && size(tmp) > 0 && size(tmp) < size(word)) 
    {
        copy(word, tmp);
        clear(tmp);
        j = 0;
    }
while (line[i] && line[i] == ' ') ++i;
while (line[i] && line[i] != ' ') tmp[j++] = line[i++];
tmp[j] = 0;
if (!line[i] && size(tmp) > 0 && size(tmp) < size(word)) 
{
    copy(word, tmp);
}
}
delete[] tmp;
return word;
}
int main() {
cout << "String: ";
const size_t buffer = 0xFFF;
char line[buffer];
cin.getline(line, buffer);
char* word = shortest_word(line);
if (size(word)) cout << "Shortest word: " << word << '\n';
else puts("Not found!");
delete[] word;
}