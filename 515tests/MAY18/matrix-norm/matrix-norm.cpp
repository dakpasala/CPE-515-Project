#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

constexpr size_t N = 128; 
int main() {
    vector<int> A(N * N), B(N * N), C(N * N, 0);

    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
            A[i * N + j] = (int)((i + j) % 7);
            B[i * N + j] = (int)((i * 2 + j) % 5);
        }
    }


    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
            int acc = 0;
            for (size_t k = 0; k < N; k++) {
                acc += A[i * N + k] * B[k * N + j];
            }
            C[i * N + j] = acc;
        }
    }

    long long checksum = 0;
    for (size_t i = 0; i < N * N; i++) checksum += C[i];
    cout << "checksum = " << checksum << endl;
    return 0;
}
