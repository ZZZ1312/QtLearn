#include <iostream>
#include <vector>

int main()
{
    using IntVector = std::vector<int>;
    IntVector vector{1,2,3,4,5,6,7};
    IntVector::iterator i = vector.begin();
    while(i != vector.end())
    {
        if ((*i) % 2 == 0)
        {
            ++i;
        }
        else
        {
            i = vector.erase(i);
        }
    }

    IntVector::const_iterator ci = vector.cbegin();
    while (ci != vector.cend())
    {
        std::cout << *ci << "\t";
        ++ci;
    }
    std::cout << std::endl;
    IntVector::reverse_iterator ri = vector.rbegin();
    while (ri != vector.rend())
    {
        std::cout << *ri << "\t";
        ++ri;
    }
    std::cout << std::endl;
    return 0;
}