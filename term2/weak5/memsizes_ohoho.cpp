#include <cstdint>
#include <iostream>

using u64 = uint64_t;
using u32 = uint32_t;
using u16 = uint16_t;

struct A{
  u16 a1;
  u64 a2; 
  u16 a3;
  u64 a4;
};

int main() {
  std::cout << "Size of A: " << sizeof(A) << "\n"; // 32 (хотя казалось бы, 2 + 8 + 2 + 8 = 20, но тут дело в выравнивании)
}
