#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <cstdint>
#include <chrono>

using namespace std;

// Tunables — adjust based on your gem5 cache config
constexpr size_t DATA_SIZE = 1 << 22;   // 1M ints = 4 MB (bigger than typical L2)
constexpr size_t NUM_ACCESSES = 1 << 17; // 256K accesses
constexpr int PF_DISTANCE = 32;          // prefetch this many iterations ahead

vector<uint64_t> load_trace(const string& path) {
    vector<uint64_t> trace;
    ifstream infile(path);
    if (!infile.is_open()) return trace;

    string token;
    while (infile >> token) {
        size_t pos = token.find("0x");
        if (pos == string::npos) continue;
        uint64_t addr = stoull(token.substr(pos + 2), nullptr, 16);
        trace.push_back(addr);
    }
    return trace;
}

int main() {
    const string trace_path = "/Users/dakshesh/gem5/515tests/MAY17/bench-run/prefetch_addrs.txt";
    auto trace = load_trace(trace_path);
    const bool prefetch_enabled = !trace.empty();

    cout << (prefetch_enabled ? "Prefetch enabled" : "Baseline run") << endl;

    vector<int> data(DATA_SIZE);
    for (size_t i = 0; i < DATA_SIZE; i++) {
        data[i] = (int)(i * 2654435761u);  
    }

    vector<size_t> indices(NUM_ACCESSES);
    mt19937 rng(42);  
    uniform_int_distribution<size_t> dist(0, DATA_SIZE - 1);
    for (size_t i = 0; i < NUM_ACCESSES; i++) {
        indices[i] = dist(rng);
    }

    long long sum = 0;

    if (prefetch_enabled) {
        for (size_t i = 0; i < NUM_ACCESSES; i++) {
            if (i + PF_DISTANCE < NUM_ACCESSES) {
                __builtin_prefetch(&data[indices[i + PF_DISTANCE]], 0, 0);
            }
            sum += data[indices[i]];
        }
    } else {
        for (size_t i = 0; i < NUM_ACCESSES; i++) {
            sum += data[indices[i]];
        }
    }

    cout << "sum = " << sum << endl;
    return 0;
}