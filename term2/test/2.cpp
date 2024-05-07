#include <iostream>
#include <cstdint>

using u32 = uint32_t;

void debug(u32 *a, size_t N, size_t ptr_a, size_t ptr_b)
{ 
    for(size_t i = 0; i < N; ++i)
    {
        std::cout << a[i] << " ";
    }
    std::cout << "\n";
    for(size_t i = 0; i < N; ++i)
    {	
    	if((i == ptr_a))
    	{
        	std::cout << "^ ";
        } else
        {
        	std::cout << "  ";
        }
    }
    std::cout << "\n";
    for(size_t i = 0; i < N; ++i)
    {	
    	if((i == ptr_b)) 
    	{
        	std::cout << "^ ";
        } else
        {
        	std::cout << "  ";
        }
    }
    std::cout << "\n";
}

int main()
{
    size_t N;
    std::cin >> N;
    u32 *a = new u32[N];
    for(size_t i = 0; i < N; ++i)
    {
        std::cin >> a[i];
    }
    size_t unique = 0;
    for(size_t i = 0; i < N; ++i) 
    {	
    	if (a[i] == 0)
    	{
    	    continue;
    	}
    	++unique;
    	for(size_t j = i+1; j < N; ++j)
    	{
    	    // debug(a, N, i, j);
    	    if (a[j] == a[i])
    	    {
    	    	a[j] = 0;
    	    }
    	}
    	a[i] = 0;
    }
    std::cout << unique << "\n";
    delete[] a;
}
