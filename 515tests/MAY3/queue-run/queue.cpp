#include <iostream>
#include <queue>
using namespace std;

int main() {
    queue<int> q;

    for (int i = 0; i <= 1000; i++) 
        q.push(i);
    
    long long sum = 0;

    while (!q.empty()) {
        sum += q.front();
        q.pop();
    }

    cout << sum << endl;

    return 0;
}