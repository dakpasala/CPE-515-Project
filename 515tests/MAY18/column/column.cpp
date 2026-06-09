#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

constexpr size_t N = 256;  // same matrix size as bench_row

int main() {
    vector<int> matrix(N * N);

    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
            matrix[i * N + j] = (int)(i + j);
        }
    }
    
    long long sum = 0;
    for (int iter = 0; iter < 5; iter++) {
        for (size_t j = 0; j < N; j++) {
            for (size_t i = 0; i < N; i++) {
                sum += matrix[i * N + j];
            }
        }
    }

    cout << "sum = " << sum << endl;
    return 0;
}
