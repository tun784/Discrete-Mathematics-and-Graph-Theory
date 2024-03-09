#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <set>
#include <cstdio>
#include <stack>

using namespace std;

//Ap dung tim duong di va chu trinh Euler 
//Do thi vo huong

int n, m;
set<int> a[10001];
int bac[10001];

void nhap() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        a[x].insert(y);
        a[y].insert(x);
        bac[x]++;
        bac[y]++;
    }
}

bool isConnected() {
    vector<bool> visited(n + 1, false);
    stack<int> st;

    st.push(1);
    while (!st.empty()) {
        int x = st.top();
        st.pop();
        visited[x] = true;

        for (int neighbor : a[x]) {
            if (!visited[neighbor]) {
                st.push(neighbor);
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            return false;
        }
    }

    return true;
}

bool KiemTraChuTrinhEuler() {
    if (!isConnected()) {
        return false;
    }

    for (int i = 1; i <= n; ++i) {
        if (bac[i] % 2 != 0) {
            return false;
        }
    }

    return true;
}

void euler(int x, bool isCycle) {
    stack<int> st;
    vector<int> result;

    st.push(x);
    while (!st.empty()) {
        int current = st.top();

        if (a[current].empty()) {
            st.pop();
            result.push_back(current);
        } else {
            int next = *a[current].begin();
            st.push(next);
            a[current].erase(next);
            a[next].erase(current);
        }
    }

    if (isCycle) {
        reverse(result.begin(), result.end());
        result.push_back(result.front());
    }

    for (int node : result) {
        cout << node << " ";
    }
    cout << endl;
}

void TimVaXuatChuTrinhHoacDuongDiEuler() {
    if (KiemTraChuTrinhEuler()) {
        cout << "---------- Do thi co chu trinh Euler ----------" << endl;
        euler(1, true);
    } else {
        cout << "----------- Do thi khong co chu trinh Euler ----------" << endl;
        cout<<"Duong Di Euler: ";
        int startNode = 1;
        for (int i = 1; i <= n; ++i) {
            if (bac[i] % 2 != 0) {
                startNode = i;
                break;
            }
        }

        euler(startNode, false);
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    nhap();
    TimVaXuatChuTrinhHoacDuongDiEuler();
    return 0;
}