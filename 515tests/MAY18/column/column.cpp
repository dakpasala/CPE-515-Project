#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

constexpr size_t N = 256;  // same matrix size as bench_row

int main() {
    cout << "Column-major traversal: " << N << "x" << N << " matrix, "
         << (N * N * sizeof(int)) / (256 * 256) << " MB" << endl;

    // SAME row-major storage layout as bench_row -- this is key
    // We only change *how we traverse it*, not how it's stored
    vector<int> matrix(N * N);

    // Same initialization
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
            matrix[i * N + j] = (int)(i + j);
        }
    }

    // Hot loop: traverse column by column (j outer, i inner)
    // This jumps N*4 = 4096 bytes between consecutive accesses
    // Each access is a different cache line -> every access likely misses
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