# 41142132

作業一

## 解題說明

Ackermann函數 A(m,n)

$$
A(m,n) = \begin{cases}
n + 1 & \text{if } m = 0 \\
A(m-1, 1) & \text{if } n = 0 \\
A(m-1, A(m, n-1)) & \text{otherwise}
\end{cases}
$$

1.問題描述
就算當 m 與 n 的值都很小時，這個函式的成長速度還是非常快
寫出遞迴版本的程式碼計算
再寫出非遞迴的演算法計算

2.解題策略
當 m=0 時，返回 n+1
當n=0 時，遞迴呼叫 A(m-1, 1)
不然，先計算 A(m,𝑛−1)，再以結果作為第二個參數，繼續計算 A(m−1,...)


## 程式實作

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


## 效能分析


遞迴版本：

時間複雜度：O(A(m, n))
空間複雜度：O(A(m, n))

非遞迴版本：

時間複雜度：O(A(m, n))
空間複雜度：O(A(m, n))

## 測試與驗證

| 測試案例 | 輸入 (m,n) | 預期輸出 | 實際輸出 |
|----------|------------|----------|----------|
| 測試一   | 1 1      | 3        | 3        |
| 測試二   | 0 1      | 2        | 2        |
| 測試三   | 1 1      | 3        | 3        |
| 測試四   | 3,3      | 61       | 61       |

## 編譯與執行指令

```shell
$ g++ -std=c++17 -o ackermann_recursive ackermann_recursive.cpp
$ ./ackermann_recursive.exe
Enter m and n: Ackermann(2, 3) = 9
```

```shell
$ g++ -std=c++17 -o AckNR AckNR.cpp
$ ./AckNR.exe
Enter m and n: Ackermann(2, 3) = 9
```


## 申論及開發報告

**選擇遞迴的原因**

函數定義本身為遞迴形式 程式結構簡潔直觀 使用遞迴讓程式碼對應到數學公式，增加可讀性

實做時的錯誤

實做時忘了設定if (n == 0) 無線的遞迴 導致Stack overflow 益位 程式崩潰

 

### 作業二:

## 解題說明

本題要求撰寫一個遞迴函式，計算一個集合的「冪集合（powerset）」。
冪集合指的是：一個集合的所有子集合的集合。
例如：若集合 S = {a, b, c}，則 powerset(S) 包含
{ {}, {a}, {b}, {c}, {a,b}, {a,c}, {b,c}, {a,b,c} } 

## 解題策略
使用遞迴方式來實作冪集合的計算。

對於集合中的每個元素，有包含或不包含兩種選擇。

採用遞迴方式，從第 0 個元素開始決定是否納入子集合，最終組合出所有可能子集合。

   
## 程式實作

```cpp
// powerset.cpp
#include <iostream>
#include <string>

void powerset(const std::string& S, int index, std::string current)
{
    if (index == static_cast<int>(S.size()))
    {
        std::cout << '(' << current << ")\n";
        return;
    }

    powerset(S, index + 1, current);

    powerset(S, index + 1, current + S[index]);
}

int main()
{
    std::string S;                 //  "abc" 代表 {a,b,c}
    std::cout << "Input set : ";
    std::cin  >> S;

    std::cout << "P(S) =\n";
    powerset(S, 0, "");            
    return 0;
}

```

## 效能分析

時間複雜度：O(2ⁿ)
空間複雜度：O(2ⁿ)


    
## 測試與驗證

輸入：

abc

輸出：
P(S) =
()
(c)
(b)
(bc)
(a)
(ac)
(ab)
(abc)


### 編譯與執行指令

```shell
$ g++ powerset.cpp -std=c++17 -o powerset.cpp       
$ ./powerset                                    
P(S) =
()
(c)
(b)
(bc)
(a)
(ac)
(ab)
(abc)

```

## 申論及開發報告

實做時的錯誤

使用遞迴，程式邏輯能自然、直接對應到問題的數學式

實做時易發生的錯誤
遞迴程式層次多，括號易漏；少一個 ;


