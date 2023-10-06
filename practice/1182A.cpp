// https://codeforces.com/problemset/problem/1182/A
#include<iostream>

// state: n = i, the number of ways
// state vars: i
// recurrence relationship: f(i) = f(i - 2) * 2 if i - 2 is valid
// base case: f(0) = 1, f(1) = 0
int main() {
    int n = 0;
    std::cin >> n;
    
    // base case
    int prevTwo = 1; // 0
    int prevOne = 0; // 1

    for (int i = 2; i <= n; ++i) {
        int temp = prevOne;
        prevOne = prevTwo * 2;
        prevTwo = temp;
    }

    std::cout << prevOne << std::endl;

    return 0;
}