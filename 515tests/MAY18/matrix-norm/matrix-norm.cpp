#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

constexpr size_t N = 128;  // 256x256 matrices = 256KB each (4-byte ints)

int main() {
    cout << "Naive matmul: " << N << "x" << N << " matrices, "
         << (N * N * sizeof(int)) / 1024 << " KB each" << endl;

    vector<int> A(N * N), B(N * N), C(N * N, 0);

    // Initialize A and B with deterministic values
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
            A[i * N + j] = (int)((i + j) % 7);
            B[i * N + j] = (int)((i * 2 + j) % 5);
        }
    }

    // Naive triple-nested loop
    // For each C[i][j], we sweep across row i of A and column j of B
    // Column j of B has poor locality -- each B[k][j] is on a different cache line
    // By the time we move to C[i][j+1], all of B has been evicted, so we reload it
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
            int acc = 0;
            for (size_t k = 0; k < N; k++) {
                acc += A[i * N + k] * B[k * N + j];
            }
            C[i * N + j] = acc;
        }
    }

    // Touch result to prevent dead-code elimination
    long long checksum = 0;
    for (size_t i = 0; i < N * N; i++) checksum += C[i];
    cout << "checksum = " << checksum << endl;
    return 0;
}