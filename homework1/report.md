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
啟動遞迴	從索引 idx = 0 開始，遞迴處理每個元素是否加入目前子集合 current。
列舉分支	對於索引 idx：
a. 不選 S[idx] → 遞迴到下一個索引。
b. 選擇 S[idx] → 將元素加入 current，再遞迴到下一個索引。
終止條件	若 idx == S.size()，代表已決定每個元素是否被選取，此時把 current 複製至結果 result。
完成一條遞迴路徑後，將先前加入的元素移除 (pop_back) 以還原狀態，繼續探索其他分支。

資料結構
vector<T>：儲存輸入集合與中途子集合，方便重複存取與插入、移除尾端元素。

遞迴呼叫堆疊：天然的深度優先搜尋，保留選取路徑的狀態。
   
### 程式實作

```cpp
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
    cout << "請依序輸入 " << n << " 個元素（以空格分隔）：\n";
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


```

### 效能分析

時間複雜度：O(2ⁿ)
空間複雜度：O(2ⁿ)


    
### 測試與驗證

| 測試案例 | 輸入參數 $n$ | 預期輸出 | 實際輸出 |
|----------|--------------|----------|----------|
| 測試一   | 3 a b c      | {}
{c}
{b}
{b,c}
{a}
{a,c}
{a,b}
{a,b,c}        | {}
{c}
{b}
{b,c}
{a}
{a,c}
{a,b}
{a,b,c}        |




### 編譯與執行指令

```shell
$ g++ -std=c++17 -o Powerset Powerset.cpp
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




# 41143263

作業一

## 解題說明

本題要求實現一個遞迴函式，計算從 $1$ 到 $n$ 的連加總和。

### 解題策略

1. 使用遞迴函式將問題拆解為更小的子問題：
   $$\Sigma(n) = n + \Sigma(n-1)$$
2. 當 $n \leq 1$ 時，返回 $n$ 作為遞迴的結束條件。  
3. 主程式呼叫遞迴函式，並輸出計算結果。

## 程式實作

以下為主要程式碼：

```cpp
#include <iostream>
using namespace std;

int sigma(int n) {
    if (n < 0)
        throw "n < 0";
    else if (n <= 1)
        return n;
    return n + sigma(n - 1);
}

int main() {
    int result = sigma(3);
    cout << result << '\n';
}
```

## 效能分析

1. 時間複雜度：程式的時間複雜度為 $O(\log n)$。
2. 空間複雜度：空間複雜度為 $O(100\times \log n + \pi)$。

## 測試與驗證

### 測試案例

| 測試案例 | 輸入參數 $n$ | 預期輸出 | 實際輸出 |
|----------|--------------|----------|----------|
| 測試一   | $n = 0$      | 0        | 0        |
| 測試二   | $n = 1$      | 1        | 1        |
| 測試三   | $n = 3$      | 6        | 6        |
| 測試四   | $n = 5$      | 15       | 15       |
| 測試五   | $n = -1$     | 異常拋出 | 異常拋出 |

### 編譯與執行指令

```shell
$ g++ -std=c++17 -o sigma sigma.cpp
$ ./sigma
6
```

### 結論

1. 程式能正確計算 $n$ 到 $1$ 的連加總和。  
2. 在 $n < 0$ 的情況下，程式會成功拋出異常，符合設計預期。  
3. 測試案例涵蓋了多種邊界情況（$n = 0$、$n = 1$、$n > 1$、$n < 0$），驗證程式的正確性。

## 申論及開發報告

### 選擇遞迴的原因

在本程式中，使用遞迴來計算連加總和的主要原因如下：

1. **程式邏輯簡單直觀**  
   遞迴的寫法能夠清楚表達「將問題拆解為更小的子問題」的核心概念。  
   例如，計算 $\Sigma(n)$ 的過程可分解為：  

   $$
   \Sigma(n) = n + \Sigma(n-1)
   $$

   當 $n$ 等於 1 或 0 時，直接返回結果，結束遞迴。

2. **易於理解與實現**  
   遞迴的程式碼更接近數學公式的表示方式，特別適合新手學習遞迴的基本概念。  
   以本程式為例：  

   ```cpp
   int sigma(int n) {
       if (n < 0)
           throw "n < 0";
       else if (n <= 1)
           return n;
       return n + sigma(n - 1);
   }
   ```

3. **遞迴的語意清楚**  
   在程式中，每次遞迴呼叫都代表一個「子問題的解」，而最終遞迴的返回結果會逐層相加，完成整體問題的求解。  
   這種設計簡化了邏輯，不需要額外變數來維護中間狀態。

透過遞迴實作 Sigma 計算，程式邏輯簡單且易於理解，特別適合展示遞迴的核心思想。然而，遞迴會因堆疊深度受到限制，當 $n$ 值過大時，應考慮使用迭代版本來避免 Stack Overflow 問題。
