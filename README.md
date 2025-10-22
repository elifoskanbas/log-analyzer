## README

### Project Title: Access Log Analyzer

This project contains two C++ implementations for analyzing an Apache-style `access_log` file. Both programs read the log file, extract the requested resource (the string between the first pair of double quotes), count the occurrences of each unique resource, filter to include only those containing "GET", and then print the top 10 most frequently requested "GET" resources along with the total execution time.

The two implementations, `main.cpp` and `main2.cpp`, differ primarily in their data structures for storing and counting the resources:

1. **`main.cpp`**: Uses a custom-implemented `SimpleHashTable` class with a fixed size and linear probing for collision resolution.  
2. **`main2.cpp`**: Uses the C++ Standard Library's `std::unordered_map`.

### Files Included

- `main.cpp`: C++ source file using a custom `SimpleHashTable`.  
- `main2.cpp`: C++ source file using `std::unordered_map`.  
- `access_log`: (Assumed) The input file containing the access logs.

### Compilation and Execution

Both programs require a file named `access_log` in the same directory to run successfully.

#### Using `main.cpp` (Custom Hash Table)

1. **Compile:**
    ```bash
    g++ -o log_analyzer_custom main.cpp
    ```
2. **Run:**
    ```bash
    ./log_analyzer_custom
    ```

#### Using `main2.cpp` (STL `unordered_map`)

1. **Compile:**
    ```bash
    g++ -o log_analyzer_stl main2.cpp
    ```
2. **Run:**
    ```bash
    ./log_analyzer_stl
    ```

### Program Description

Both programs perform the following steps:

1. **File Reading**: Opens and reads the `access_log` file line by line.  
2. **Resource Extraction**: Extracts the request string enclosed between the first pair of double quotes (e.g., `"GET /index.html HTTP/1.1"`).  
3. **Counting**: Stores the unique resource strings and their frequencies in a data structure:  
   - `main.cpp`: The custom `SimpleHashTable` class.  
   - `main2.cpp`: `std::unordered_map<string, StringCount>`.  
4. **Filtering**: Filters the results to include only those resources whose string value contains the substring "GET":  
   - `main.cpp`: Implements `removeGetRequests()` which decrements the count and removes the entry if the count becomes 0 for non-"GET" requests.  
   - `main2.cpp`: Filters the elements when moving them from the `unordered_map` to a `std::vector` for sorting.  
5. **Sorting and Top 10**:  
   - `main.cpp`: Uses an inefficient selection-sort-like logic within `printTopN` to find and print the top 10 elements.  
   - `main2.cpp`: Uses `std::sort` with a custom comparison function (`compareByCount`) to sort all "GET" elements and then prints the first 10.  
6. **Output**: Prints the top 10 "GET" requests with their visit counts and the total elapsed time for the processing.

#### `StringCount` Class

A helper class used in both implementations to store the resource string and its access count:

```cpp
class StringCount {
public:
    string string_value;
    int count;
    // constructor
    StringCount(const string& str = "", int num = 0) :
        string_value(str), count(num) {}
};
```

### SimpleHashTable (Used in `main.cpp`)

- **Size:** Fixed size of 331 (a prime number)  
- **Hash Function:** Simple sum of ASCII values modulo 331  
- **Collision Handling:** Linear Probing  

---

### Comparative Analysis

| Feature | `main.cpp` (Custom Hash Table) | `main2.cpp` (`std::unordered_map`) |
|---------|-------------------------------|----------------------------------|
| **Data Structure** | Custom `SimpleHashTable` (Array/Vector based) | `std::unordered_map` |
| **Hashing** | Simple ASCII sum, fixed table size | Standard library robust hashing, dynamic size |
| **Collision** | Linear Probing | Implementation dependent (usually separate chaining or open addressing) |
| **Sorting** | Manual selection sort (inefficient $O(N \cdot K)$ where $K=10$) | `std::sort` ($O(N \log N)$) |
| **Efficiency** | Highly dependent on input and hash function quality; fixed size limit | Generally more robust and efficient ($O(1)$ average access) |
| **Code Complexity** | Higher, due to custom implementation | Lower, leveraging STL |
