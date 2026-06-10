#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    unordered_map<int, int> lookup;

    for (int i = 0; i <= 1000; i++)
        lookup[i] = i;
    
    int max_key = 0;
    for (const auto &entry : lookup)
        max_key = std::max(max_key, entry.first);
    
    return 0;
}
