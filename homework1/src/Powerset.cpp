#include <iostream>
#include <vector>
using namespace std;

template<typename T>
void Powerset(const vector<T>& S,
                      int idx,
                      vector<T>& current,
                      vector<vector<T>>& result) {
    if (idx == (int)S.size()) {
        result.push_back(current);
        return;
    }

    Powerset(S, idx + 1, current, result);


    current.push_back(S[idx]);
    Powerset(S, idx + 1, current, result);
    current.pop_back();
}

int main() {
    int n;
    cout << "請輸入集合元素個數 n：";
    cin >> n;
    vector<string> S(n);
    cout << "請依序輸入 " << n << " 個元素：\n";
    for (int i = 0; i < n; i++) {
        cin >> S[i];
    }

    vector<vector<string>> powerset;
    vector<string> current;
    Powerset(S, 0, current, powerset);

    cout << "該集合的冪集合共 " << powerset.size() << " 個子集合：\n";
    for (const auto& subset : powerset) {
        cout << "{";
        for (int i = 0; i < (int)subset.size(); i++) {
            cout << subset[i] << (i + 1 < (int)subset.size() ? "," : "");
        }
        cout << "}\n";
    }
    return 0;
}
