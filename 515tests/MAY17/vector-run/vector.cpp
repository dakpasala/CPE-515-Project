#include <iostream>
#include <vector>
#include <fstream>
#include <cstdint>

using namespace std;

vector<uint64_t> load_trace(const string& path) {
    vector<uint64_t> trace;
    ifstream infile(path);

    if (!infile.is_open()) {
        return trace;  
    }

    uint64_t addr;
    while (infile >> std::hex >> addr) {
        trace.push_back(addr);
    }

    return trace;
}

int main() {
    const string trace_path = "/Users/dakshesh/gem5/515tests/MAY17/vector-run/prefetch_addrs.txt";
    auto trace = load_trace(trace_path);

    const bool prefetch_enabled = !trace.empty();
    cout << (prefetch_enabled ? "Prefetch enabled" : "Baseline run") << endl;

    const int N = 1000;
    vector<int> values;
    values.reserve(N);
    for (int i = 0; i < N; i++) {
        values.push_back(i);
    }

    long long sum = 0;
    size_t trace_idx = 0;

    for (int i = 0; i < N; i += 10) {
        if (prefetch_enabled && trace_idx < trace.size()) {
            __builtin_prefetch((void*)trace[trace_idx]);
            trace_idx++;
        }

        sum += values[i];
    }

    cout << "sum = " << sum << endl;
    return 0;
}