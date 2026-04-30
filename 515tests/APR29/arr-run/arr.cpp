#include <iostream>
using namespace std;

int main() {
    int arr[1000];
    for (int i = 0; i < 1000; i++) {
        arr[i] = i;
    }

    int sum = 0;
    for (int i = 0; i < 1000; i++) {
        sum += arr[i];
    }

    cout << sum << endl;
    return 0;
}