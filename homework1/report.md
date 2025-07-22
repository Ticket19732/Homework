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

本題要求撰寫一個遞迴函式，計算一個集合的「冪集合（powerset）」。
冪集合指的是：一個集合的所有子集合的集合。
例如：若集合 S = {a, b, c}，則 powerset(S) 包含
{ {}, {a}, {b}, {c}, {a,b}, {a,c}, {b,c}, {a,b,c} } 

### 解題策略
使用遞迴方式來實作冪集合的計算。

對於集合中的每個元素，有「包含」或「不包含」兩種選擇。

採用遞迴方式，從第 0 個元素開始決定是否納入子集合，最終組合出所有可能子集合。

資料結構
vector<T>：儲存輸入集合與中途子集合，方便重複存取與插入、移除尾端元素。

遞迴呼叫堆疊：天然的深度優先搜尋，保留選取路徑的狀態。
   
### 程式實作

```cpp
#include <iostream>
using namespace std;

#define MAX_N 10 

// 印出子集
void print_subset(char subset[], int subset_size) {
    cout << "{";
    for (int i = 0; i < subset_size; ++i) {
        cout << subset[i];
        if (i < subset_size - 1) cout << ",";
    }
    cout << "}" << endl;
}

void powerset(char S[], int n, int idx, char subset[], int subset_size) {
    if (idx == n) {
        print_subset(subset, subset_size);
        return;
    }
    // 不選 S[idx]
    powerset(S, n, idx + 1, subset, subset_size);
    // 選 S[idx]
    subset[subset_size] = S[idx];
    powerset(S, n, idx + 1, subset, subset_size + 1);
}

int main() {
    char S[MAX_N] = {'a', 'b', 'c'}; // 輸入集合
    int n = 3;
    char subset[MAX_N]; // 暫存子集
    powerset(S, n, 0, subset, 0);
    return 0;
}


```

### 效能分析

時間複雜度：O(2ⁿ)
空間複雜度：O(2ⁿ)


    
### 測試與驗證

輸入：

S = {'a', 'b', 'c'}

輸出：
{}
{c}
{b}
{b,c}
{a}
{a,c}
{a,b}
{a,b,c}


### 編譯與執行指令

```shell
$ g++ powerset.cpp -std=c++17 -o powerset       
$ ./powerset                                    
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

實做時錯誤
char subset[] = {} 輸出時用了字串""非''字元 導致型別不符

遞迴天然適合樹狀狀態（每個元素二選一）。

陣列（char[]）記憶體連續，存取效率高，適合處理固定長度資料。



