#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <cstdint>

using namespace std;

vector<uint64_t> load_trace() {
    vector<uint64_t> trace;
    trace.reserve(1000);

    ifstream infile("/Users/dakshesh/gem5/515tests/MAY3/queue-run/prefetch_addrs.txt");

    if (!infile.is_open()) {
        return trace;
    }

    uint64_t addr;
    int count = 0;

    while (infile >> std::hex >> addr && count < 1000) {
        trace.push_back(addr);
        count++;
    }

    return trace;
}

int main() {
    auto trace = load_trace();

    if (trace.empty()) {
        cout << "Baseline run\n";
    } else {
        cout << "Prefetch enabled\n";
    }

    queue<int> q;

    for (int i = 0; i <= 1000; i++) {
        q.push(i);
    }

    long long sum = 0;
    int idx = 0;

    while (!q.empty()) {
        if (idx + 10 < trace.size()) {
            __builtin_prefetch((void*)trace[idx + 10]);
        }

        sum += q.front();
        q.pop();
        idx++;
    }

    cout << sum << endl;
}