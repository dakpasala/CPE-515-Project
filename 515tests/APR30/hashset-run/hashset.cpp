#include <iostream>
#include <vector>
#include <list>
#include <unordered_set>
#include <cstdlib>
using namespace std;

int main() {
    unordered_set<int> set;
    for (int i = 0; i <= 1000; i++)
        set.insert(i);
    
    int max = 0;
    for (int s : set) max = std::max(max, s);
    
    return 0;
}