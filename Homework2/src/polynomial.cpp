#include <iostream>
#include <cmath>           
using namespace std;

const int MAX = 50;        

struct Term { float c; int e; };

struct Poly {
    Term t[MAX];
    int  n = 0;            // 實際項數
};

/* 讀取：先輸入項數，再依序輸入 (係數 指數) */
void readPoly(Poly& p) {
    cin >> p.n;
    for (int i = 0; i < p.n; ++i)
        cin >> p.t[i].c >> p.t[i].e;
}

/* print：直接照輸入順序輸出 */
void printPoly(const Poly& p) {
    if (p.n == 0) { cout << "0"; return; }
    for (int i = 0; i < p.n; ++i) {
        if (i) cout << " + ";
        cout << p.t[i].c;
        if (p.t[i].e) cout << "x^" << p.t[i].e;
    }
}

/* 加法： */
Poly add(const Poly& a, const Poly& b) {
    Poly c;
    c.n = a.n + b.n;
    for (int i = 0; i < a.n; ++i) c.t[i]       = a.t[i];
    for (int j = 0; j < b.n; ++j) c.t[a.n + j] = b.t[j];
    return c;
}

/* 乘法： */
Poly mult(const Poly& a, const Poly& b) {
    Poly c;
    for (int i = 0; i < a.n; ++i)
        for (int j = 0; j < b.n; ++j) {
            float newC = a.t[i].c * b.t[j].c;
            int   newE = a.t[i].e + b.t[j].e;

            // 檢查 c 內是否已有同次方
            int k = 0;
            while (k < c.n && c.t[k].e != newE) ++k;
            if (k < c.n) c.t[k].c += newC;
            else {
                c.t[c.n++] = {newC, newE};
            }
        }
    return c;
}

/* 求值 */
float eval(const Poly& p, float x) {
    float s = 0;
    for (int i = 0; i < p.n; ++i)
        s += p.t[i].c * pow(x, p.t[i].e);
    return s;
}

int main() {
    Poly p1, p2;
    cout << "輸入第一個多項式：項數 係數 指數...\n";
    readPoly(p1);
    cout << "輸入第二個多項式：\n";
    readPoly(p2);

    cout << "\np1(x) = "; printPoly(p1); cout << '\n';
    cout << "p2(x) = ";   printPoly(p2); cout << "\n\n";

    Poly s = add(p1, p2);
    cout << "p1 + p2 = "; printPoly(s); cout << '\n';

    Poly m = mult(p1, p2);
    cout << "p1 * p2 = "; printPoly(m); cout << '\n';

    float x;
    cout << "\n輸入 x 以計算 p1(x)：";
    cin  >> x;
    cout << "p1(" << x << ") = " << eval(p1, x) << '\n';
    return 0;
}
