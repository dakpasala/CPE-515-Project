#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

struct Particle {
    float x, y, z;       // position
    float vx, vy, vz;    // velocity
    float mass, charge;  // properties
};

constexpr size_t N = 1 << 16;  

int main() {
    cout << "AoS run: " << N << " particles, "
         << (N * sizeof(Particle)) / (1024 * 1024) << " MB total" << endl;

    vector<Particle> particles(N);

    for (size_t i = 0; i < N; i++) {
        particles[i].x = (float)i;
        particles[i].y = (float)i * 2.0f;
        particles[i].z = (float)i * 3.0f;
        particles[i].vx = 0.1f;
        particles[i].vy = 0.2f;
        particles[i].vz = 0.3f;
        particles[i].mass = 1.0f;
        particles[i].charge = -1.0f;
    }

    float checksum = 0.0f;
    for (int iter = 0; iter < 10; iter++) {
        for (size_t i = 0; i < N; i++) {
            particles[i].x += particles[i].vx;
        }
        checksum += particles[N / 2].x;
    }

    cout << "checksum = " << checksum << endl;
    return 0;
}
