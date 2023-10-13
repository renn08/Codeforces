#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

// find the peak idx, (valid when that vec is strictly 凸)
int ternarySearch(vector<int>& vec) {
    int n = vec.size();
    int start = 0;
    int end = n - 1;
    while (start <= end) {
        int q1 = start + (end - start) / 3;
        int q2 = end - (end - start) / 3;
        if (vec[q1] < vec[q2]) {
            start = q1 + 1;
        }
        else if (vec[q1] > vec[q2]) {
            end = q2 - 1;
        }
        else {
            if (start == end) break; // on the same elem is just the peak
            start++;
            end--;
        }
    }
    return start;
}

int main() {
    vector<int> a = {1, 2, 3, 4, 5};
    cout << ternarySearch(a) << endl; // 4
    vector<int> b = {1, 2, 3, 5, 4};
    cout << ternarySearch(b) << endl;  // 3
    vector<int> c = {5, 4, 3, 2, 1};
    cout << ternarySearch(c) << endl;  // 0
    vector<int> d = {1, 2, 2, 3, 3, 3, 3, 3, 2, 1}; // one of the max is returned, to find the first
    // occurance of max or last we can iterate from that index and check.
    cout << ternarySearch(d) << endl;  // 3
    return 0;
}