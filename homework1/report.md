# 41142132

作業一

## 解題說明

就算在 m 和 n 是很小的值時，它也會超快速地成長。請寫一個遞迴函式來計算此函數，再撰寫一個非遞迴演算法以計算阿克曼函數。

### 解題策略

函數定義

A(0,n) = n+1 <br>
A(m,0) = A(m-1,1) <br>
A(m,n) = A(m-1, A(m,n-1))   (m,n > 0)


由於 m > 4 會變得就算是電腦跑也很難計算，所以只考慮小於等於3的情況

遞迴版本 <br>

直接按照數學定義編寫，可讀性高、利於後續效能與空間分析。<br>

非遞迴版本

在 m ≤ 3 時，可以推導出公式
| m | 封閉公式      |
| - | --------------------- |
| 0 | A(0,n) = n + 1       |
| 1 | A(1,n) = n + 2       |
| 2 | A(2,n) = 2n + 3      |
| 3 | A(3,n) = 2^(n+3) − 3 |


## 程式實作

遞迴版本
```cpp
#include <iostream>

int Ackermann(int m, int n)
{
    if (m == 0)
        return n + 1;                              
    else if (n == 0)
        return Ackermann(m - 1, 1);              
    else
        return Ackermann(m - 1, Ackermann(m, n - 1)); 
}

int main()
{
    int m, n;
    std::cout << "輸入 m n：";
    while (std::cin >> m >> n)
    {
        std::cout << "A(" << m << ',' << n << ") = "
                  << Ackermann(m, n) << '\n';
    }
    return 0;
}

```

非遞迴

```cpp
#include <iostream>

long long AckNR(int m, int n)
{
    if (m == 0) return n + 1;       
    if (m == 1) return n + 2;        
    if (m == 2) return 2 * n + 3;   

    if (m == 3)                      
    {
        long long res = 1;
        for (int i = 0; i < n + 3; ++i) res <<= 1;
        return res - 3;
    }

    return 0;                       
}

int main()
{
    int m, n;
    std::cout << "輸入 m n (0~3)：";
    while (std::cin >> m >> n)
    {
        std::cout << "A(" << m << "," << n << ") = "
                  << AckNR(m, n) << '\n';
    }
    return 0;
}
```


## 效能分析


遞迴版本：

時間複雜度：O(1)
空間複雜度：O(1)

非遞迴版本：

時間複雜度：O(1)
空間複雜度：O(1)

## 測試與驗證

| 測試案例 | 輸入 (m,n) | 預期輸出 | 實際輸出 |
|----------|------------|----------|----------|
| 測試一   | 1 1      | 3        | 3        |
| 測試二   | 0 1      | 2        | 2        |
| 測試三   | 1 1      | 3        | 3        |
| 測試四   | 3,3      | 61       | 61       |

## 編譯與執行指令

```shell
$ ./ackermann_recursive
輸入 m n：1 1
A(1,1) = 3

$ ./homework1/src/AckNR~.exe
輸入 m n (0~3)：1 1
A(1,1) = 3

```

### 結論


當 m 跟 n 小於等於 3 時 能正常執行，若大於 3 會執行失敗


## 申論及開發報告

由於 m 限定輸入小於等於 3 的數字 所以空間與時間複雜度是O(1)

**遞迴版本**

把三條規則對照到

if <br> els if <br> else 

就可以解出但我一開始實做時忘記加了這條規則 else if (n == 0) 導致Stack Overflow

**非遞迴版本**

計算 m 跟 n 使用了快速計算的公式，如程式碼所示
 

### 作業二:

## 解題說明

本題要求撰寫一個遞迴函式，計算一個集合的「冪集合（powerset）」。
冪集合指的是：一個集合的所有子集合的集合。
例如：若集合 S = {a, b, c}，則 powerset(S) 包含
{ {}, {a}, {b}, {c}, {a,b}, {a,c}, {b,c}, {a,b,c} } 


### 解題策略

每個字元代表一個元素，例如 "abc" = { a, b, c }
if (std::cin >> S)，程式讀取一次輸入便遞迴列舉所有子集合，完成後即結束
遞迴兩分支選或不選元素

## 程式實作


```cpp
#include <iostream>
#include <string>

void PowerSet(const std::string& S, int idx, const std::string& current)
{
    int n = S.length();

    if (idx == n)               
    {
        std::cout << '(' << current << ")\n";
        return;
    }

    PowerSet(S, idx + 1, current);      
    PowerSet(S, idx + 1, current + S[idx]); 
}

int main()
{
    std::string S;
    std::cout << "請輸入集合：";
    if (std::cin >> S)                  
    {
        std::cout << "powerset(" << S << ")：\n";
        PowerSet(S, 0, "");
    }
    return 0;
}
```


## 效能分析


時間複雜度：O(2ⁿ)  <BR>
空間複雜度：O(n)


## 測試與驗證

| 測試案例 | 輸入 (字母) | 預期輸出 | 實際輸出 |
|----------|------------|------------------------------------|----------|
| 測試一   | abc      |      ()(c)(b)(bc)(a)(ac)(ab)(abc)   | ()(c)(b)(bc)(a)(ac)(ab)(abc)        |


## 編譯與執行指令

```shell
$ ./homework1/src/Powerset
$ 請輸入集合：abc
powerset(abc)：
()
(c)
(b)
(bc)
(a)
(ac)
(ab)
(abc)
```

### 結論

程式採用遞迴列舉冪集，邏輯清晰。時間複雜度為 O(2^n)，空間複雜度 O(n)。<br>在 n≤20 的範圍內，執行效能良好，記憶體使用低


## 申論及開發報告
本程式以遞迴產生冪集，分支列舉「取」與「不取」，達長度即輸出。足以應付 n≤20。<br>
開發時的錯誤：在呼叫 PowerSet() 前後各有 cout current，導致相同遞迴路徑會輸出兩次
