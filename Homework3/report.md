# 41142132

�@�~�T

## ���D����

���D�ݥH �`���쵲��C�]�����Y�`�I�^ �Ӫ�F���ܼƾ�ƫY�Ʀh�����A�ù�@�G

Ū�J�~����� n, c1 e1, c2 e2, �K, cn en�]���ƻ���^

��X�~����ܻP�iŪ���N�Ʀ�

�h�����[�k add(A,B)�]�u�ʨ֨��^

�h�������k multiply(A,B)�]�v���ۭ��ϦP���X�֡^

�ϥ� �i�ΪŶ���C�]available list�^ �i��`�I�^��/����

### ���D����

1.��Ƶ��c�G

�`�I coef, exp, link�F���Y�`�I exp = -1 �@����L�C

��C���`���A�ú��@ rear �@�������СA���J���ݬ� O(1)�C

�]�p���� Avail �@���i�ΪŶ���C�AGetNode ������ Avail�ARetNode �^���`�I�� Avail�C

2.��J/��X�G

��J�ɰ��]���Ƥw����A�����H attachBack ������ݡC

���ѡu�~����ܡv�P�u�iŪ�N�Ʀ��v��ؿ�X�C

3.�[�k�G

����нu�ʨ֨��A���Ƭ۵��ɦX�֫Y�ơB�� 0 �Y�R���F�_�h�N���j���ƪ������[�쵲�G�C

4.���k�G

�� A �C���P B �C���ۭ��A�N (coef �ۭ�, exp �ۥ[) �H insertCombine �̫��ƻ���J�æP���X�֡A�X�֫�Y�Ƭ� 0 �h�R���C

5.�O����޲z�G

����h�����ɤ� delete�A��I�s RetNode �^���`�I�A�H�ŦX�u�i�ΪŶ��v�n�D�C
## �{����@

�H�U���D�n�{���X�G

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

## �į���R

1.�[�k�G���C�u�ʨ֨��A�ɶ� O(m+n)�]m�Bn ���O����h�������ơ^�F�Ŷ� O(1) �B�~�]���G��C�����^�C

2.���k�G�����j��v���ۭ��A���a O(m�Pn)�F���J�ϥ� insertCombine�A�������p���� m�Pn �D�ɡC���G���Ƴ��a�i�F m�Pn�A�]����X�Ŷ����a O(m+n+m�Pn)�C

3.�`�I�޲z�G�إ�/�^���z�L available list�A�`�I���o�P�k�٬Ҭ� O(1)

## ���ջP����

### ���ծר�

���դ@
3  5 7   3 2  -6 0 <br>
2  1 3  -2 0

### �sĶ�P������O

```shell
$ ./polynomial.exe
$ 3  5 7   3 2  -6 0
$ 2  1 3  -2 0
A: 3 5 7 3 2 -6 0    // 5*x^7 + 3*x^2 - 6
B: 2 1 3 -2 0    // x^3 - 2
A+B: 4 5 7 1 3 3 2 -8 0    // 5*x^7 + x^3 + 3*x^2 - 8
A*B: 6 5 10 -10 7 3 5 -6 3 -6 2 12 0    // 5*x^10 - 10*x^7 + 3*x^5 - 6*x^3 - 6*x^2 + 12
```

### ����

���@�~�H�`���쵲�Ϫ��Y�ϧ����й�@�h�����A�t�X�i�ΪŶ���C�F�� O(1) �`�I�t�m/�^�����ĪG�F�[�k�� O(m+n)�B���k�� O(m�Pn)�A�ŦX�Ұ��v����h�����[�k�������׻����ç������w����J/��X�P�B��ݨD�C

## �ӽפζ}�o���i

����δ`���쵲�ϧ����СH
��K�b���� O(1) ���[�`�I�A�B��L�]���Y�^���޿�²��A�֯S�P�Ū�C

����ݭn�i�ΪŶ���C�H
�j�q�`�I�إ�/�R���ɥi���ƨϥθ`�I�A���C�t�m�����F�]��b�w�������`�I�� O(1) �R����q�C

�P�Ұ�����פ@�P��
�[�k�Ľu�ʦX�֡A������ O(m+n) �P��v���@�P�F���k�ݥ��M�����ۭ��A���a O(m�Pn)

3. **���j���y�N�M��**  
   �b�{�����A�C�����j�I�s���N��@�ӡu�l���D���ѡv�A�ӳ̲׻��j����^���G�|�v�h�ۥ[�A����������D���D�ѡC  
   �o�س]�p²�ƤF�޿�A���ݭn�B�~�ܼƨӺ��@�������A�C
