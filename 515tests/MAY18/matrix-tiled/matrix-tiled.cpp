#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

constexpr size_t N = 128;       // same matrix size
constexpr size_t TILE = 32;     // 32x32 tile = 4 KB per tile, easily fits in L1 (32 KB)

int main() {
    cout << "Tiled matmul: " << N << "x" << N << " matrices, "
         << "tile size " << TILE << "x" << TILE << endl;

    vector<int> A(N * N), B(N * N), C(N * N, 0);

    // Same initialization as naive
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
            A[i * N + j] = (int)((i + j) % 7);
            B[i * N + j] = (int)((i * 2 + j) % 5);
        }
    }

    // Tiled six-nested loop
    // Outer 3 loops walk through tile coordinates (ii, jj, kk)
    // Inner 3 loops do a small matmul on the current tiles
    // The TILE x TILE block of B stays in L1 for all TILE iterations of i within ii
    for (size_t ii = 0; ii < N; ii += TILE) {
        for (size_t jj = 0; jj < N; jj += TILE) {
            for (size_t kk = 0; kk < N; kk += TILE) {

                // Multiply the current tiles, accumulate into C tile
                for (size_t i = ii; i < ii + TILE; i++) {
                    for (size_t j = jj; j < jj + TILE; j++) {
                        int acc = C[i * N + j];
                        for (size_t k = kk; k < kk + TILE; k++) {
                            acc += A[i * N + k] * B[k * N + j];
                        }
                        C[i * N + j] = acc;
                    }
                }

            }
        }
    }

    long long checksum = 0;
    for (size_t i = 0; i < N * N; i++) checksum += C[i];
    cout << "checksum = " << checksum << endl;
    return 0;
}