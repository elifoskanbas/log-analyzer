#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

class StringCount {
public:
    string string_value;
    int count;
    // constructor
    StringCount(const string& str = "", int num = 0) :
        string_value(str), count(num) {}
};

bool compareByCount(const StringCount& a, const StringCount& b) {
    return a.count > b.count;
}

int main() {
    ifstream file("access_log");

    if (!file.is_open()) {
        cout << "Unable to open file!" << endl;
        return -1;
    }

     clock_t start = clock();

    unordered_map<string, StringCount> table;

    string line;
    while (getline(file, line)) {
        size_t first_quote = line.find('"');
        size_t second_quote = line.find('"', first_quote + 1);
        if (first_quote != string::npos && second_quote != string::npos) {
            string filename = line.substr(first_quote + 1, second_quote - first_quote - 1);
            if (table.count(filename) > 0) {
                table[filename].count++;
            } else {
                table[filename] = StringCount(filename, 1);
            }
        }
    }

    file.close();

    vector<StringCount> top_elements;
    for (auto it = table.begin(); it != table.end(); ++it) {
        if (it->first.find("GET") != string::npos) {
            top_elements.push_back(it->second);
        }
    }

    sort(top_elements.begin(), top_elements.end(), compareByCount);

    clock_t stop = clock();
    double time = static_cast<double>(stop - start) / CLOCKS_PER_SEC;

    int count = 0;
    for (const auto& element : top_elements) {
        cout << element.string_value << " : " << element.count << " visits." << endl;
        ++count;
        if (count == 10) {
            break;
        }
    }

    cout <<endl ;
    cout<< endl ;


    cout << "Total Elapsed Time : " << time << " seconds." << endl;

    return 0;
}
