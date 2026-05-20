#include <iostream>
#include <vector>
#include <cstdint>
using namespace std;

constexpr size_t N = 1 << 14;  

int main() {
    cout << "Vector sum: " << N << " elements" << endl;
    vector<int> v(N);
    for (size_t i = 0; i < N; i++) v[i] = (int)i;

    long long sum = 0;
    for (int iter = 0; iter < 4; iter++) {
        for (size_t i = 0; i < N; i++) sum += v[i];
    }
    cout << "sum = " << sum << endl;
    return 0;
}