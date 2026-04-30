#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <cstdlib>
using namespace std;

int main() {
    vector<int> arr;
    for (int i = 0; i <= 1000; i++)
        arr.push_back(i);
    
    int sum = 0;
    for (int a : arr)
        sum += a;

    return 0;
}