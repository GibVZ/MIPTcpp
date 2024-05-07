#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>


/*

\ | a b c d
a | p -> in
b |  \
c |   not in
d |

*/
void PrintMat(std::vector<std::vector<int>> &mat)
{
    for(size_t i = 0; i < mat.size(); ++i)
    {
    	for(size_t j = 0; j < mat[0].size(); ++j)
    	{
    	    if(j < i)
    	    {
    	        std::cout << "  ";
    	    }
    	    else
    	    {
    	        std::cout << mat[i][j] << " ";
    	    }
    	}
    	std::cout << "\n";
    }

}

int main()
{
    size_t N;
    int P;
    std::cin >> P >> N;
    int *a = new int[N];
    std::vector<std::vector<int>> p(N+1, std::vector<int>(N+1, 0));
    for(size_t i = 0; i < N; ++i)
    {
        std::cin >> a[i];
        if ((i >= 2))
        {
            p[0][i] = std::max(std::abs(a[i-1] - a[i-2]), p[0][i-1]);
        }
    }
    // std::cout << "it's OK(33)\n";
    p[0][N] = std::max(p[0][N-1], std::abs(a[N-1] - a[N-2]));
    int max_len = 0;
    for (size_t i = 1; i <= N; ++i)
    {
    	p[i][i] = 0;
    	for(size_t j = i+1; j <= N; ++j)
    	{
            // std::cout << "it's OK" << i << " " << j <<  "\n";
    	    p[i][j] = std::min(p[i-1][j-1], std::max(p[i][j-1], a[j-1] - a[j-2]));
    	}
    	if (p[i][N] == P) 
    	{
    	    max_len = N - i;
    	    break;	
    	}
    	//PrintMat(p);
    }
    std::cout << max_len - 1 << "\n";
    delete[] a;
    
    
}
