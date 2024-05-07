#include <iostream>

int main() {
  int x;
  std::cin >> x;
  
  switch(x) {
  case 0: std::cout << "0!\n";  [[fallthrough]];
  case 1: std::cout << "1!\n";  [[fallthrough]];
  case 3: std::cout << "3!\n";  [[fallthrough]];
  default: std::cout << "Unexpected!\n"; 
  }

  
}
