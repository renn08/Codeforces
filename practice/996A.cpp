// https://codeforces.com/problemset/problem/996/A
#include<iostream>

int main() {
    int n = 0;
    std::cin >> n;
    int result = 0;
    result += n / 100;
    n %= 100;
    result += n / 20;
    n %= 20;
    result += n / 10;
    n %= 10;
    result += n / 5;
    n %= 5;
    result += n;
    std::cout << result << std::endl;
    return 0;
}
// 100 20 10 5 1
// 1 - 1e9
