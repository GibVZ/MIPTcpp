#include <cstdint>
#include <iostream>

using u64 = uint64_t;

struct Vis{
  Vis() {
    std::cout << "0-arg ctor\n";
  }

  Vis(u64 a) {
    std::cout << "1-arg ctor\n";
  }

  Vis(u64 a, u64 b) {
    std::cout << "1-arg ctor\n";
  }
};

int main() {
  Vis *v1 = new Vis();
  Vis *v2 = new Vis(42);
  Vis *v3 = new Vis{42};
  Vis *v4 = new Vis{42, 64};
  int *arr = new int[3]{0, 10, 20};
  for(size_t i = 0; i < 3; ++i)
    std::cout << arr[i] << ' ';
  std::cout << '\n';
  delete[] arr;
  new(arr) int[3]{1, 2, 3};
  for(size_t i = 0; i < 3; ++i)
    std::cout << arr[i] << ' ';
  std::cout << '\n';
   
  delete[] arr;
}
