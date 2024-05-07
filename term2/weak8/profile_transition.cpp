#include <iostream>
#include <cstdint>
#include <array>

const size_t M = 3;
const size_t S = 1 << M;
const size_t ALLP = S - 1;
using u64 = uint64_t;

using Col = std::array<u64, S>;


int main() {
  u64 N = 4;
  
  
  Col prev, cur;

  for (size_t i = 0; i < S; ++i) {
    prev[i] = 0;
    cur[i] = 0;
  }

  prev[S - 1] = 1;

  for (size_t i = 0; i < N; ++i) {
    // cross-col transition
    for (size_t k = 0; k < S; ++k) {
      cur[ALLP ^ k] += prev[k];
    }

    Col tmp = cur;
    // inside-col transition
    for (size_t K = 0; K < S; ++K) {
      u64 mask = 1 + 2;
      for (size_t i = 0; i < M - 1; ++i) {
        if ((K & mask) == 0) {
          std::cerr << K << " -> " << (K | mask) << "\n";
          tmp[K | mask] += cur[K];
        }
        mask <<= 1;
      }
    }
    cur = tmp;

    std::swap(prev, cur);
    for (size_t i = 0; i < S; ++i) cur[i] = 0;

    for (auto i : prev) std::cerr << i << " ";
    std::cerr << "\n";
  }

  std::cout << prev[S - 1] << "\n";
}
