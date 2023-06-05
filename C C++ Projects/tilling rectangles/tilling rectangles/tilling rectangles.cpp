#include <iostream>
#include <vector>
using namespace std;

class Rect {
public:
    Rect(int _x, int _y, int _size_x, int _size_y) : x(_x), y(_y), size_x(_size_x), size_y(_size_y) {}

    int x, y;
    int size_x, size_y;
};

vector<vector<Rect>> solves;
vector<Rect> solve;
int x_size, y_size, min_count_rects;

bool putRectIn(vector<vector<int>>& field, pair<int, int> cords, pair<int, int>& size, int& rect_count) {
    if (cords.first + size.first > x_size || cords.second + size.second > y_size) return false;
    int count_used_cells = 0;
    for (int i = cords.first; i < cords.first + size.first; i++) {
        for (int j = cords.second; j < cords.second + size.second; j++) {
            if (field[i][j] != 0) count_used_cells++;
        }
    }
    if (count_used_cells != 0) return false;
    for (int i = cords.first; i < cords.first + size.first; i++) {
        for (int j = cords.second; j < cords.second + size.second; j++) {
            field[i][j] = rect_count;
        }
    }
    return true;
}

void takeRectFrom(vector<pair<int, int>>& rects_sizes, pair<int, int> size) {
    for (int i = 0; i < rects_sizes.size(); i++) {
        if ((rects_sizes[i].first == size.first || rects_sizes[i].second == size.second) ||
            (size.first == size.second && rects_sizes[i].first == rects_sizes[i].second)) {
            rects_sizes.erase(rects_sizes.begin() + i);
            i--;
        }
    }
}

void print_field(vector<vector<int>> field) {
    for (int i = 0; i < x_size; i++) {
        for (int j = 0; j < y_size; j++) {
            cout << field[i][j] << " ";
        }
        cout << '\n';
    }
}

void print(const vector<Rect>& rect) {
    for (auto& r : rect) {
    }
}

void func(vector<vector<int>> field_def, vector<pair<int, int>> rects_sizes, int rects_count) {
    while (!rects_sizes.empty()) {
        for (int i = 0; i < x_size; i++) {
            for (int j = 0; j < y_size; j++) {
                if (field_def[i][j] == 0) {
                    vector<vector<int>> field = field_def;
                    if (putRectIn(field, make_pair(i, j), rects_sizes[rects_sizes.size() - 1], rects_count)) {
                        Rect rect(i, j, rects_sizes[rects_sizes.size() - 1].first,
                            rects_sizes[rects_sizes.size() - 1].second);
                        solve.emplace_back(rect);
                        vector<pair<int, int>> changed_rects_sizes = rects_sizes;
                        takeRectFrom(changed_rects_sizes, make_pair(rect.size_x, rect.size_y));
                        func(field, changed_rects_sizes, rects_count + 1);
                        solve.pop_back();
                    }
                }
            }
        }
        rects_sizes.erase(rects_sizes.end() - 1);
    }
    int count_empty_cells = 0;
    for (int i = 0; i < x_size; i++) {
        for (int j = 0; j < y_size; j++) {
            if (field_def[i][j] == 0) count_empty_cells++;
        }
    }
    if (count_empty_cells == 0 && rects_count > min_count_rects) {
        solves.emplace_back(solve);
        cout << "Solution found\n";
        print(solve);
        print_field(field_def);
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    cout << "Input size m*n of rectangle: ";
    cin >> x_size >> y_size;
    cout << "Input minimal amount of rectangles, that are required for tilling field: ";
    cin >> min_count_rects;
    vector<vector<int>> field(x_size, vector<int>(y_size, 0));

    vector<pair<int, int>> rects_sizes;
    for (int i = 1; i < x_size; i++) {
        for (int j = y_size - 1; j > 0; j--) {
            rects_sizes.emplace_back(make_pair(i, j));
        }
    }

    func(field, rects_sizes, 1);

    return 0;
}