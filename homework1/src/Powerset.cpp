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
    std::cout << "�п�J���X�G";
    if (std::cin >> S)                  
    {
        std::cout << "powerset(" << S << ")�G\n";
        PowerSet(S, 0, "");
    }
    return 0;
}