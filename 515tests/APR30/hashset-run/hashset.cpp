#include <iostream>
#include <unordered_set>
using namespace std;

int main() {
    unordered_set<int> keys;

    for (int i = 0; i <= 1000; i++)
        keys.insert(i);
    
    int max_key = 0;
    for (int key : keys) max_key = std::max(max_key, key);
    
    return 0;
}
