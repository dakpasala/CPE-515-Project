#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

struct Particles {
    vector<float> x, y, z;
    vector<float> vx, vy, vz;
    vector<float> mass, charge;

    Particles(size_t n)
        : x(n), y(n), z(n), vx(n), vy(n), vz(n), mass(n), charge(n) {}
};

constexpr size_t N = 1 << 16;  

int main() {
    cout << "SoA run: " << N << " particles, "
         << (N * 8 * sizeof(float)) / (1024 * 1024) << " MB total" << endl;

    Particles particles(N);

    for (size_t i = 0; i < N; i++) {
        particles.x[i] = (float)i;
        particles.y[i] = (float)i * 2.0f;
        particles.z[i] = (float)i * 3.0f;
        particles.vx[i] = 0.1f;
        particles.vy[i] = 0.2f;
        particles.vz[i] = 0.3f;
        particles.mass[i] = 1.0f;
        particles.charge[i] = -1.0f;
    }

    float checksum = 0.0f;
    for (int iter = 0; iter < 10; iter++) {
        for (size_t i = 0; i < N; i++)
            particles.x[i] += particles.vx[i];
        checksum += particles.x[N / 2];
    }

    cout << "checksum = " << checksum << endl;
    return 0;
}
