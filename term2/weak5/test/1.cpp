#include <iostream>
#include <cstdint>

using u32 = uint32_t;


int main() 
{
  size_t N;
  std::cin >> N;
  u32 * arr = new u32[N];
  
  for (size_t i = 0; i < N; i++)
  {
    std::cin >> arr[i];
  }
  
  for (size_t i = 0; i < N; i++)
  {
    std::cout << arr[N-1 - i] << " ";
  }
  std::cout << "\n";
  
  delete[] arr;
  
  return 0;
  
}
