#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <cstdlib>
using namespace std;

int main() {
    unordered_map<int, int> map;
    for (int i = 0; i <= 1000; i++)
        map[i] = i;
    
    int max = 0;
    for (const auto &pair : map)
        max = std::max(max, pair.first);
    
    return 0;
}