// https://codeforces.com/problemset/problem/706/B
#include<iostream>
#include<vector>
#include<algorithm>

// binary search would be O((n+q)logn) O(n)
// dynamic programming would be O(nlogn + n) O(largest price)
// binary search slightly worse in time while dynamic programming might be a lot of worse in space 
// so I choose binary search
int main() {
    int n = 0;
    std::cin >> n;
    std::vector<int> prices(n, 0);
    for (int i = 0; i < n; ++i) {
        std::cin >> prices[i];
    }
    std::sort(prices.begin(), prices.end());
    int q = 0;
    std::cin >> q;
    int coins = 0;
    for (int i = 0; i < q; ++i) {
        std::cin >> coins;
        auto it = std::upper_bound(prices.begin(), prices.end(), coins); // first larger than
        std::cout << it - prices.begin() << std::endl;
    }
    return 0;
}