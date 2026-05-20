#include <iostream>
#include <list>
#include <cstdint>
using namespace std;

constexpr size_t N = 1 << 14;

int main() {
    cout << "List sum: " << N << " elements" << endl;
    list<int> l;
    for (size_t i = 0; i < N; i++) l.push_back((int)i);

    long long sum = 0;
    for (int iter = 0; iter < 4; iter++) {
        for (int x : l) sum += x;
    }
    cout << "sum = " << sum << endl;
    return 0;
}