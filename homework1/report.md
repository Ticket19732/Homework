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

時間複雜度：O(A(m,n))，運算次數是指數成長
空間複雜度：O(A(m,n))，會與最大的遞迴深度成正比

非遞迴版本：

時間複雜度：O(A(m,n))，跟遞迴一樣
空間複雜度：O(A(m,n))，不受堆疊大小限制

### 測試與驗證

| 測試案例 | 輸入 (m,n) | 預期輸出 | 實際輸出 |
|----------|------------|----------|----------|
| 測試一   | (0,0)      | 1        | 1        |
| 測試二   | (0,1)      | 2        | 2        |
| 測試三   | (1,1)      | 3        | 3        |
| 測試四   | (3,3)      | 61       | 61       |

### 編譯與執行指令

```shell
$ g++ -std=c++17 -o main main.cpp
$ ./main.exe
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

如果 S 是一個有 n 個元素的集合，S 的冪集（powerset）是 S 所有可能子集的集合。例如，如果 S = {a,b,c}，則 powerset(S) = {{}, {a}, {b}, {c}, {a,b}, {a,c}, {b,c}, {a,b,c}}。請寫一個遞迴函數來計算這個冪集。

### 解題策略
解法思路：
1.從索引 0 開始，對每個元素：
    不選它（不加入子集合）
    選它（加入子集合）
2.每次選完都遞迴往下一層走。
3.遞迴到底時（已處理所有元素），將子集合輸出。

### 程式實作

```cpp
#include <iostream>
using namespace std;

// 遞迴函數用來生成集合 S 的冪集
void generatePowerSet(int S[], int n, int index, int current[], int currentSize) 
{
  
    if (index == n) 
    {
        cout << "{ ";
        for (int i = 0; i < currentSize; ++i)
          {
            cout << current[i] << " ";
        }
        cout << "}" << endl;
        return;
    }

    // 選擇不包含當前元素的情況
    generatePowerSet(S, n, index + 1, current, currentSize);

    // 選擇包含當前元素的情況
    current[currentSize] = S[index];
    generatePowerSet(S, n, index + 1, current, currentSize + 1);
}

int main() {
    int n;
    cout << "輸入陣列大小: ";
    cin >> n;

    int S[n]; 
    cout << "輸入鎮列內容: ";
    for (int i = 0; i < n; ++i) {
        cin >> S[i];
    }

    int current[n]; // 保存當前子集的陣列
    cout << "The power set is:\n";
    
    // 計算冪集
    generatePowerSet(S, n, 0, current, 0);

    return 0;
}
```

### 效能分析

- 時間複雜度：
對於長度為n的集合，每個元素有兩種選擇（選或不選）：O(2^n)。
- 空間複雜度：O(n)。

### 測試與驗證

**測試案例：S = {a, b, c}**


輸出：`{{}, {c}, {b}, {b,c}, {a}, {a,c}, {a,b}, {a,b,c}}`

### 編譯與執行指令

```shell
$ g++ -std=c++17 -o main2 main2.cpp
$ ./main2.exe
```

## 申論及開發報告

1.遞迴架構設計：將整體解空間視為一棵二元遞迴樹，每層做「選或不選」的分支。
2.回溯技巧讓我能在每次「包含元素」之後，退回並「移除該元素」，以便進入另一條不包含它的遞迴分支
3.這種結構具有清晰的決策樹（decision tree）結構，便於控制與理解。


## 心得

通過這次作業，主要理解了遞迴的核心概念，和陣列的熟悉度，並個別分析其複雜度，對於處理複雜演算法具有重要意義。
