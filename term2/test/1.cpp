#include <iostream>
#include <cstdint>

using u32 = uint32_t;

void debug(size_t N, u32 *a, size_t ptr_a, size_t ptr_b) 
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
    size_t N, L;
    std::cin >> N;
    u32 *a = new u32[N];
    for(size_t i = 0; i < N; ++i) 
    {
    	std::cin >> a[i];
    }
    std::cin >> L;
    
    size_t ptr_a = 0;
    size_t ptr_b = 0;
    u32 cur_len = 0;
    size_t lamps = 1;
    size_t max_lamps = 1;
    while(ptr_b < N-1)
    {
    	u32 new_len = cur_len - a[ptr_b] + a[ptr_b + 1];
    	// debug(N, a, ptr_a, ptr_b);
    	if(new_len <= L)
    	{
    	    ++lamps;
    	    cur_len = new_len;
    	    ++ptr_b;
    	    // std::cout << "new_len(" << new_len << ") <= " << L << "\n";
    	} 
    	else if (ptr_a < ptr_b)
    	{
	    if (lamps > max_lamps)
	    {
	    	max_lamps = lamps;
	    }
    	    --lamps;
    	    cur_len = cur_len + a[ptr_a] - a[ptr_a + 1];
    	    ++ptr_a;
    	    
    	    // std::cout << "new_len(" << new_len << ") > " << L << "\n";
    	}
    	else
    	{
    	    ++ptr_a;
    	    ++ptr_b;
    	    // std::cout << "ptr_a == ptr_b!! \n";
    	}
    	if(ptr_a > ptr_b){std::cout << "WTF?"; return 0;}
    }
    if(lamps > max_lamps)
    	max_lamps = lamps;
    std::cout << max_lamps << "\n";
    delete[] a;
}
