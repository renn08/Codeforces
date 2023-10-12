#include<iostream>
#include<vector>

using namespace std;

int upperBound(vector<int>& vec, int target) {
    // idea is to find the index of strictly larger than target, and return it
    int n = vec.size();
    int start = 0;
    int end = n - 1;
    int ans = n; // default will be the post last
    while (start <= end) {
        int mid = (start + end) / 2;
        if (vec[mid] <= target) {
            start = mid + 1; // if equal we continue higher in case target consecutive (to right)
        }
        else {
            ans = mid;
            end = mid - 1;
        }
    }
    return ans;
}

int lowerBound(vector<int>& vec, int target) {
    // idea is to find the index of strictly smaller than target, and return ans + 1
    int n = vec.size();
    int start = 0;
    int end = n - 1;
    int ans = -1; // in case the answer is 0
    while (start <= end) {
        int mid = (start + end) / 2;
        if (vec[mid] >= target) { // if equal, we continue probe left in case target 
        // prev consecutive (to left)
            end = mid - 1;
        }
        else {
            ans = mid; // ans store the index of element that is strictly smaller than the target
            start = mid + 1;
        }
    }
    return ans + 1;
}


int main() {
    vector<int> a = {1, 2, 3, 3, 3, 3, 4, 5};
    cout << lowerBound(a, 1) << endl;
    vector<int> b = {1, 2, 3, 3, 3, 3, 4, 5};
    cout << upperBound(b, 0) << endl;
    return 0;
}