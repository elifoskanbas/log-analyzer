#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <unordered_map>
#include <ctime>


using namespace std;

class StringCount {
public:
  string string_value;
  int count;
  // constructor
  StringCount(const string& str = "", int num = 0) :
    string_value(str), count(num) {}

};





class SimpleHashTable {
private:
    vector<StringCount> table; // array to store StringCount obj
    // hash function to map strings to bucket indices
    int hash(const string& str) const {// Sum the ASCII values of all characters in the string
    int hash_value = 0;
    for (int i = 0; i < str.length(); ++i) {
    char c = str[i];
     hash_value += static_cast<int>(c);}
 // Modulo by table size to get a bucket index within range
  return hash_value % 331 ; // Replace 331 with your actual table size
}

public:
    SimpleHashTable() : table(331) {}// size of table equal to 331

     // add a new element or increment count for existing one
    void insert(const string& filename) {
        int bucket = hash(filename);
        bool found = false;
        for (int i = bucket; i < bucket +331 && !found; ++i) {
            int j = i % 331;
            if (table[j].string_value == filename) {
                table[j].count++;
                found = true;
                break;} 
            else if (table[j].string_value.empty()) {
                table[j] = StringCount(filename, 1);
                found = true;
                break; }
        }
    }

    // print all entries in the table
    void printTable() {
        for (int i = 0; i < 331; ++i) {
            if (!table[i].string_value.empty()) {
        cout << "String: " << table[i].string_value << " - Count: " << table[i].count  << endl;  } }
    }

    // get all StringCount objects as  vector
    vector<StringCount> getStringCounts() {
        vector<StringCount> counts;
        for (int i = 0; i <331; ++i) {
            if (!table[i].string_value.empty()) { counts.push_back(table[i]); }
        }
        return counts; }

   // remove entries not containing "GET"
void removeGetRequests() {
    for (int i = 0; i < 331; ++i) {
        if (!table[i].string_value.empty() && table[i].string_value.find("GET") == string::npos) {
            table[i].count--; // decreasing
            if (table[i].count == 0) { table[i] = StringCount();  }
        } }
}
    // print top N elements based on count
    void printTopN(int top_n) {
     vector<StringCount> counts = getStringCounts();
    vector<StringCount> top_elements; // create a new vector to hold the top N elements
    // use a loop to find the most accessed
     for (int i = 0; i < counts.size() && i < top_n; ++i) {
    int max_index = 0;
    for (int j = 1; j < counts.size(); ++j) {
      if (counts[j].count > counts[max_index].count) { max_index = j; }}
      // add the most accessed element and remove from list
    top_elements.push_back(counts[max_index]);
    counts.erase(counts.begin() + max_index);}
    // print the top N elements
  for (int i = 0; i < top_elements.size(); ++i) {
  StringCount element = top_elements[i];
  cout <<  element.string_value << " : " << element.count << "  visits." << endl;}}

};



int main() {
    ifstream file("access_log");

    if (!file.is_open()) {
    cout << "Unable to open file!" << endl;
    return -1;}

    clock_t start = clock();


  SimpleHashTable table; // Create a new hash table

  string line;
 while (getline(file, line)) {
    size_t first_quote = line.find('"');
    size_t second_quote = line.find('"', first_quote + 1);
     if (first_quote != string::npos && second_quote != string::npos) {
        string filename = line.substr(first_quote + 1, second_quote - first_quote - 1);
        table.insert(filename); } 
}

file.close();

// remove elemets which is not consist "GET"
table.removeGetRequests();

clock_t stop = clock();
double time = static_cast<double>(stop - start) / CLOCKS_PER_SEC;

// print top 10
table.printTopN(10);


    cout <<endl ;
    cout<< endl ;  

cout << "Total Elapsed Time : " << time << " seconds." << endl;
return 0;
}
