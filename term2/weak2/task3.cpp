#include<iostream>

unsigned long long collatz_conjecture_count(unsigned long long a) {
    unsigned long long n = 0;
    while(a != 1){
	++n;
        if(a%2 == 0)
		a /= 2;
	else
		a = 3*a + 1;
    }
    return n;
}

int main(){
    int a;
    std::cin >> a;
    std::cout << collatz_conjecture_count(a);
}
