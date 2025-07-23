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
    std::cout << "¿é¤J m n¡G";
    while (std::cin >> m >> n)
    {
        std::cout << "A(" << m << ',' << n << ") = "
                  << Ackermann(m, n) << '\n';
    }
    return 0;
}
