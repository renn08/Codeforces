// https://codeforces.com/problemset/problem/961/B
// theorems written down in additional wake ups using secret + normal wake up theorems
#include<iostream>
#include<vector>
#include<numeric>

using namespace std;

int main() {
    int n = 0, k = 0;
    cin >> n;
    cin >> k;
    vector<int> a(n, 0);
    for (int i = 0; i < n; ++i) cin >> a[i];
    vector<int> t(n, 0);
    for (int i = 0; i < n; ++i) cin >> t[i];

    int normal = 0;
    int maxAdd = 0;
    int curAdd = 0;
    // init
    for (int i = 0; i < k; ++i) {
        if (t[i] == 1) normal += a[i];
        else {
            curAdd += a[i];
        }
    }
    maxAdd = curAdd;
    for (int i = 1; i <= n - k; ++i) { // start
        if (t[i - 1] == 0) curAdd -= a[i - 1];
        if (t[i + k - 1] == 0) {
            curAdd += a[i + k - 1];
            maxAdd = max(maxAdd, curAdd);
        }
        else normal += a[i + k - 1];
    }

    cout << normal + maxAdd << endl;
    return 0;
}