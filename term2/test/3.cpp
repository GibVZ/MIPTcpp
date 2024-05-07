#include <iostream>
#include <cstdint>
#include <cmath>

using u32 = uint32_t;
using u64 = uint64_t;


int main()
{
    size_t N;
    u64 packed_beans;
    u32 free_beans, max_beans = 0;
    std::cin >> N;
    for(size_t i = 0; i < N; ++i) 
    {
        u32 beans;
        std::cin >> beans;
        if(beans > max_beans)
        {
            max_beans = beans;
        }
        packed_beans += beans;
    }
    std::cin >> free_beans;
    // std::cout << "some debug:" << max_beans << " " << free_beans + packed_beans - N * max_beans << " " << std::ceil(static_cast<float>(free_beans + packed_beans - N * max_beans) / N) << "\n";
    
    
    if (free_beans < (N * max_beans - packed_beans)) 
    {
    	std::cout << max_beans << "\n";
    } else {
    	std::cout << max_beans + std::ceil(static_cast<float>(free_beans + packed_beans - N * max_beans) / N) << "\n";
    }
}
