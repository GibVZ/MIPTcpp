#include<iostream>

uint64_t gcd(uint64_t a, uint64_t b){
	while(b != 0){
		a %= b;
		std::swap(a, b);
	}
  	return a;
}

int main(){
	int a, b;
	std::cin >> a >> b;
	std::cout << gcd(a, b);
	return 0;
}




