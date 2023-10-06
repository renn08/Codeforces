// https://codeforces.com/problemset/problem/580/A
#include<iostream>

int main() {
    int n = 0;
    std::cin >> n;
    int prev = INT_MIN;
    int cur = 0;
    int len = 0;
    int maxLen = 1;
    for (int i = 0; i < n; ++i) {
        std::cin >> cur;
        if (cur >= prev) len++;
        else {
            maxLen = std::max(maxLen, len);
            len = 1;
        }
        prev = cur;
    }
    maxLen = std::max(maxLen, len);
    std::cout << maxLen << std::endl;
    
    return 0;
}