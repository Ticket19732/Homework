# 41142132

作業三

## 解題說明

本題需以 循環鏈結串列（有表頭節點） 來表達單變數整數係數多項式，並實作：

讀入外部表示 n, c1 e1, c2 e2, …, cn en（指數遞減）

輸出外部表示與可讀的代數式

多項式加法 add(A,B)（線性併走）

多項式乘法 multiply(A,B)（逐項相乘＋同次合併）

使用 可用空間串列（available list） 進行節點回收/重用

### 解題策略

1.資料結構：

節點 coef, exp, link；表頭節點 exp = -1 作為哨兵。

串列為循環，並維護 rear 作為尾指標，插入尾端為 O(1)。

設計全域 Avail 作為可用空間串列，GetNode 先取自 Avail，RetNode 回收節點到 Avail。

2.輸入/輸出：

輸入時假設指數已遞減，直接以 attachBack 掛到尾端。

提供「外部表示」與「可讀代數式」兩種輸出。

3.加法：

兩指標線性併走，指數相等時合併係數、為 0 即刪除；否則將較大指數的項附加到結果。

4.乘法：

對 A 每項與 B 每項相乘，將 (coef 相乘, exp 相加) 以 insertCombine 依指數遞減插入並同次合併，合併後係數為 0 則刪除。

5.記憶體管理：

釋放多項式時不 delete，改呼叫 RetNode 回收節點，以符合「可用空間」要求。
## 程式實作

以下為主要程式碼：

```cpp
#include <iostream>
#include <cstdio>
using namespace std;

struct TermNode {
    int coef, exp;
    TermNode* link;
    TermNode(int c=0, int e=0, TermNode* L=nullptr): coef(c), exp(e), link(L) {}
};

static TermNode* Avail = nullptr;

TermNode* GetNode() {
    if (Avail) {
        TermNode* p = Avail;
        Avail = Avail->link;
        p->link = nullptr;
        return p;
    }
    return new TermNode();
}

void RetNode(TermNode* p) {
    if (!p) return;
    p->link = Avail;
    Avail = p;
}

class Polynomial {
public:
    Polynomial() {
        head = GetNode();  
        head->coef = 0; head->exp = -1;
        head->link = head;   
        rear = head;         
    }

    Polynomial(const Polynomial& rhs) : Polynomial() { copyFrom(rhs); }

    Polynomial& operator=(const Polynomial& rhs) {
        if (this != &rhs) { clear(); copyFrom(rhs); }
        return *this;
    }

    ~Polynomial() { clear(); RetNode(head); head=nullptr; rear=nullptr; }

    bool empty() const { return head->link == head; }


    void attachBack(int c, int e) {
        if (c == 0) return;
        TermNode* node = GetNode();
        node->coef = c; node->exp = e;
        node->link = head;       
        rear->link = node;        
        rear = node;              
    }

    void insertCombine(int c, int e) {
        if (c == 0) return;
        TermNode* prev = head;
        TermNode* curr = head->link;
        while (curr != head && curr->exp > e) {
            prev = curr; curr = curr->link;
        }
        if (curr != head && curr->exp == e) {
            curr->coef += c;
            if (curr->coef == 0) { 
                prev->link = curr->link;
                if (curr == rear) rear = prev;
                RetNode(curr);
            }
        } else {
            TermNode* node = GetNode();
            node->coef = c; node->exp = e;
            node->link = curr;
            prev->link = node;
            if (prev == rear) rear = node; 
        }
    }

    bool read(istream& in=cin) {
        clear();
        int n;
        if (!(in >> n)) return false;
        for (int i=0;i<n;i++) {
            int c,e; in >> c >> e;
            attachBack(c,e);
        }
        return true;
    }


    void writeRaw(ostream& out=cout) const {
        int n = countTerms();
        out << n;
        for (TermNode* p=head->link; p!=head; p=p->link)
            out << ' ' << p->coef << ' ' << p->exp;
    }


    void writePretty(ostream& out=cout) const {
        if (empty()) { out << "0"; return; }
        bool first = true;
        for (TermNode* p=head->link; p!=head; p=p->link) {
            int c=p->coef, e=p->exp;
            if (!first) out << (c>=0? " + " : " - ");
            else { if (c<0) out << "-"; first=false; }
            int ac = c>=0? c : -c;
            if (e==0) out << ac;
            else {
                if (ac!=1) out << ac << "*";
                out << "x";
                if (e!=1) out << "^" << e;
            }
        }
    }

    // A + B
    static Polynomial add(const Polynomial& A, const Polynomial& B) {
        Polynomial C;
        TermNode *pa = A.head->link, *pb = B.head->link;
        while (pa != A.head && pb != B.head) {
            if (pa->exp == pb->exp) {
                int sum = pa->coef + pb->coef;
                if (sum != 0) C.attachBack(sum, pa->exp);
                pa = pa->link; pb = pb->link;
            } else if (pa->exp > pb->exp) {
                C.attachBack(pa->coef, pa->exp);
                pa = pa->link;
            } else {
                C.attachBack(pb->coef, pb->exp);
                pb = pb->link;
            }
        }
        while (pa != A.head) { C.attachBack(pa->coef, pa->exp); pa = pa->link; }
        while (pb != B.head) { C.attachBack(pb->coef, pb->exp); pb = pb->link; }
        return C;
    }

    // A * B
    static Polynomial multiply(const Polynomial& A, const Polynomial& B) {
        Polynomial C;
        if (A.empty() || B.empty()) return C;
        for (TermNode* pa=A.head->link; pa!=A.head; pa=pa->link) {
            for (TermNode* pb=B.head->link; pb!=B.head; pb=pb->link) {
                C.insertCombine(pa->coef * pb->coef, pa->exp + pb->exp);
            }
        }
        return C;
    }

private:
    TermNode* head; 
    TermNode* rear;

    void clear() {

        TermNode* p = head->link;
        while (p != head) {
            TermNode* next = p->link;
            RetNode(p);
            p = next;
        }
        head->link = head;
        rear = head;
    }

    void copyFrom(const Polynomial& rhs) {
        for (TermNode* p=rhs.head->link; p!=rhs.head; p=p->link)
            attachBack(p->coef, p->exp);
    }

    int countTerms() const {
        int cnt=0;
        for (TermNode* p=head->link; p!=head; p=p->link) ++cnt;
        return cnt;
    }
};

ostream& operator<<(ostream& os, const Polynomial& P) {
    P.writeRaw(os);
    os << "    // ";
    P.writePretty(os);
    return os;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Polynomial A, B;

    if (!A.read(cin)) return 0;
    if (!B.read(cin)) return 0;

    Polynomial S = Polynomial::add(A,B);
    Polynomial M = Polynomial::multiply(A,B);

    cout << "A: " << A << "\n";
    cout << "B: " << B << "\n";
    cout << "A+B: " << S << "\n";
    cout << "A*B: " << M << "\n";
    return 0;
}

```

## 效能分析

1.加法：兩串列線性併走，時間 O(m+n)（m、n 分別為兩多項式項數）；空間 O(1) 額外（結果串列忽略）。

2.乘法：雙重迴圈逐項相乘，最壞 O(m·n)；插入使用 insertCombine，平均情況仍受 m·n 主導。結果項數最壞可達 m·n，因此輸出空間最壞 O(m+n+m·n)。

3.節點管理：建立/回收透過 available list，節點取得與歸還皆為 O(1)

## 測試與驗證

### 測試案例

測試一
3  5 7   3 2  -6 0 <br>
2  1 3  -2 0

### 編譯與執行指令

```shell
$ ./polynomial.exe
$ 3  5 7   3 2  -6 0
$ 2  1 3  -2 0
A: 3 5 7 3 2 -6 0    // 5*x^7 + 3*x^2 - 6
B: 2 1 3 -2 0    // x^3 - 2
A+B: 4 5 7 1 3 3 2 -8 0    // 5*x^7 + x^3 + 3*x^2 - 8
A*B: 6 5 10 -10 7 3 5 -6 3 -6 2 12 0    // 5*x^10 - 10*x^7 + 3*x^5 - 6*x^3 - 6*x^2 + 12
```

### 結論

本作業以循環鏈結＋表頭＋尾指標實作多項式，配合可用空間串列達到 O(1) 節點配置/回收的效果；加法為 O(m+n)、乘法為 O(m·n)，符合課堂投影片對多項式加法的複雜度說明並完成指定的輸入/輸出與運算需求。

## 申論及開發報告

為何用循環鏈結＋尾指標？
方便在尾端 O(1) 附加節點，且哨兵（表頭）讓邏輯簡潔，少特判空表。

為何需要可用空間串列？
大量節點建立/刪除時可重複使用節點，降低配置成本；也能在已知首尾節點時 O(1) 刪除整段。

與課堂複雜度一致性
加法採線性合併，複雜度 O(m+n) 與投影片一致；乘法屬必然的兩兩相乘，最壞 O(m·n)

3. **遞迴的語意清楚**  
   在程式中，每次遞迴呼叫都代表一個「子問題的解」，而最終遞迴的返回結果會逐層相加，完成整體問題的求解。  
   這種設計簡化了邏輯，不需要額外變數來維護中間狀態。
