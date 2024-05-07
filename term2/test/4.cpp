#include <iostream>
#include <vector>


bool search(const std::vector<int> &vec, int to_find) 
{
    for (size_t i = 0; i < vec.size(); ++i)
    {
        if (vec[i] == to_find)
        {
            return true;
        }
    }
    return false;
}

int dp(int *a, size_t N)
{
    // std::cout << "in f \n";
    std::vector<int> sums;
    sums.push_back(0);
    for(size_t i = 0; i < N; ++i)
    {
    	// std::cout << "in for i=" << i << "\n";
    	if (a[i] == 0)
    	    continue;
    	size_t sums_size = sums.size();
    	for(size_t j = 0; j < sums_size; ++j)
    	{
    	    int sum = sums[j];
    	    if (!search(sums, sum + a[i]))
    	    {
    	        sums.push_back(sum + a[i]);
    	    }
    	}
    }
    return sums.size();
}

int main()
{
    size_t N;
    std::cin >> N;
    
    int *a = new int[N];
    for(size_t i = 0; i < N; ++i)
    {
        std::cin >> a[i];
    }
    
    std::cout << dp(a, N);
    
    delete[] a;
    return 0;
}
