# 41142132

作業一

### 解題說明

Ackermann函數 A(m,n)

$$
A(m,n) = \begin{cases}
n + 1 & \text{if } m = 0 \\
A(m-1, 1) & \text{if } n = 0 \\
A(m-1, A(m, n-1)) & \text{otherwise}
\end{cases}
$$

題目要求

寫出遞迴版本的程式碼計算
再寫出非遞迴的演算法計算

### 解題策略
當 m=0 時，返回 n+1
當n=0 時，遞迴呼叫 A(m-1, 1)
其他，遞迴呼叫 A(m-1, A(m, n-1))

1	遞迴法：按照定義直接寫 int64_t Ack(m,n)
2	非遞迴法：用 std::stack 模擬呼叫堆疊，手動展開遞迴。

### 程式實作

遞迴版本
```cpp
#include <iostream>
using namespace std;

int ackermann_recursive(int m, int n) {
    if (m == 0) return n + 1;
    else if (n == 0) return ackermann_recursive(m - 1, 1);
    else return ackermann_recursive(m - 1, ackermann_recursive(m, n - 1));
}

int main() {
    int m, n;
    cout << "Enter m and n: ";
    cin >> m >> n;
    cout << "Ackermann(" << m << ", " << n << ") = " << ackermann_recursive(m, n) << endl;
    return 0;
}
```

非遞迴

```cpp

#include <bits/stdc++.h>
using namespace std;
using int64 = long long;

int64 AckNR(int64 m, int64 n) {
    stack<pair<int64,int64>> st;
    st.emplace(m, n);
    while (!st.empty()) {
        auto [mm, nn] = st.top(); st.pop();

        if (mm == 0) {
            n = nn + 1;               
        } else if (nn == 0) {
            st.emplace(mm - 1, 1);       
        } else {
            st.emplace(mm - 1, -1);       
            st.emplace(mm, nn - 1);      
        }

        if (!st.empty() && st.top().second == -1) {
            st.pop();                     
            st.emplace(mm - 1, n);        
        }
    }
    return n;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int64 m, n;
    cout << "Input m n: ";
    if (cin >> m >> n) {
        cout << "A(" << m << "," << n << ") = " << AckNR(m, n) << '\n';
    }
}
```


### 效能分析


遞迴版本：

時間複雜度：O(2ⁿ) =<3 的情況
空間複雜度：O(2ⁿ) =<3 的情況

非遞迴版本：

時間複雜度：O(2ⁿ) 跟遞迴一樣
空間複雜度：O(2ⁿ)

### 測試與驗證

| 測試案例 | 輸入 (m,n) | 預期輸出 | 實際輸出 |
|----------|------------|----------|----------|
| 測試一   | (0,0)      | 1        | 1        |
| 測試二   | (0,1)      | 2        | 2        |
| 測試三   | (1,1)      | 3        | 3        |
| 測試四   | (3,3)      | 61       | 61       |

### 編譯與執行指令

```shell
$ g++ -std=c++17 -o ackermann_recursive ackermann_recursive.cpp
$ ./ackermann_recursive.exe
Input m n: A(0,1) = 2
```
## 申論及開發報告

資料結構選擇

遞迴版利用 隱式呼叫堆疊，直接就是數學定義

非遞迴版採用顯式 std::stack，可自行控制記憶體

演算法理由：Ackermann 直接模擬是最簡單方法。

實做時的錯誤

實做時忘了設定if (n == 0) 無線的遞迴 導致Stack overflow 益位 程式崩潰

 

作業二:

### 問題描述

Power set（冪集）：給定一個含 n 個元素的集合 S，其冪集 P(S) 為 S 的所有子集合

題目要求撰寫遞迴函式，計算並列出冪集合

### 解題策略
遞迴

定義遞迴函式 generate(idx, current)：

idx 表示目前考慮第 idx 個元素是否放入當前子集合 current。

對每個元素做「選擇／不選擇」兩種決策：

選擇：將 S[idx] 加到 current，再遞迴 idx+1。

不選擇：跳過 S[idx]，直接遞迴 idx+1。

當 idx == n 時，將 current 加入結果集。

所需資料結構

vector<T> current：暫存目前子集合。

vector<vector<T>> result：儲存所有子集合。

### 程式實作

```cpp
#include <iostream>
using namespace std;

#include <iostream>
#include <vector>
using namespace std;

template<typename T>
void generatePowerset(const vector<T>& S,
                      int idx,
                      vector<T>& current,
                      vector<vector<T>>& result) {
    if (idx == (int)S.size()) {
        result.push_back(current);
        return;
    }
    // 不選擇 S[idx]
    generatePowerset(S, idx + 1, current, result);

    // 選擇 S[idx]
    current.push_back(S[idx]);
    generatePowerset(S, idx + 1, current, result);
    current.pop_back();
}

int main() {
    int n;
    cout << "請輸入數字 n：";
    cin >> n;
    vector<string> S(n);
    cout << "依序輸入 " << n << " 個元素：\n";
    for (int i = 0; i < n; i++) {
        cin >> S[i];
    }

    vector<vector<string>> powerset;
    vector<string> current;
    generatePowerset(S, 0, current, powerset);

    cout << "此集合的冪集合有 " << powerset.size() << " 個子集合：\n";
    for (const auto& subset : powerset) {
        cout << "{";
        for (int i = 0; i < (int)subset.size(); i++) {
            cout << subset[i] << (i + 1 < (int)subset.size() ? "," : "");
        }
        cout << "}\n";
    }
    return 0;
}

```

### 效能分析

時間複雜度：O(2ⁿ)
空間複雜度：O(2ⁿ)


    
### 測試與驗證

**測試案例：S = {a, b, c}**



### 編譯與執行指令

```shell
$ g++ -std=c++17 -o AckNR AckNR.cpp
$ ./AckNR.exe
{}
{c}
{b}
{b,c}
{a}
{a,c}
{a,b}
{a,b,c}
```

## 申論及開發報告

1.遞迴架構設計：將整體解空間視為一棵二元遞迴樹，每層做「選或不選」的分支。
2.回溯技巧讓我能在每次「包含元素」之後，退回並「移除該元素」，以便進入另一條不包含它的遞迴分支
3.這種結構具有清晰的決策樹（decision tree）結構，便於控制與理解。


