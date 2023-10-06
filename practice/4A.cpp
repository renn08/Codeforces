// https://codeforces.com/problemset/problem/4/A
#include<iostream>

int main() {
    int w = 0;
    std::cin >> w;
    // dividable into two even number means has to be a even number >= 4, smallest even number is 2
    std::string result = (w >= 4 && w % 2 == 0) ? "YES" : "NO";
    std::cout << result << std::endl;
    return 0;
}
