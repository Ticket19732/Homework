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

    return -1;                       
}

int main()
{
    int m, n;
    std::cout << "¿é¤J m n (0~3)¡G";
    while (std::cin >> m >> n)
    {
        std::cout << "A(" << m << "," << n << ") = "
                  << AckNR(m, n) << '\n';
    }
    return 0;
}