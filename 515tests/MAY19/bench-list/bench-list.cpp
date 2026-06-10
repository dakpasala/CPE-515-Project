#include <iostream>
#include <list>
#include <cstdint>
using namespace std;

constexpr size_t N = 1 << 14;

int main() {
    list<int> values;
    for (size_t i = 0; i < N; i++) values.push_back((int)i);

    long long sum = 0;
    for (int iter = 0; iter < 4; iter++) {
        for (int value : values) sum += value;
    }
    cout << "sum = " << sum << endl;
    return 0;
}
