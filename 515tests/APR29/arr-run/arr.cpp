#include <iostream>
using namespace std;

int main() {
    int values[1000];

    for (int i = 0; i < 1000; i++) {
        values[i] = i;
    }

    int sum = 0;
    for (int i = 0; i < 1000; i++) {
        sum += values[i];
    }

    cout << sum << endl;
    return 0;
}
