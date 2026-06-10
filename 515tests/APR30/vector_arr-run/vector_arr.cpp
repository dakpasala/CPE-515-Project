#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> values;

    // Dynamic-array version of the simple sequential walk.
    for (int i = 0; i <= 1000; i++)
        values.push_back(i);
    
    int sum = 0;
    for (int value : values)
        sum += value;

    return 0;
}
