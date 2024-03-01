#include<iostream>

unsigned long long digit_sum(unsigned long long a) {
    unsigned long long ret = 0;
    while(a > 0){
        ret += a%10;
        a /= 10;
    }
    return ret;
}

unsigned long long redux(unsigned long long a){
    while(a > 10){
        a = digit_sum(a);
    }
    return a;
}

int main(){
    int a;
    std::cin >> a;
    std::cout << redux(a);
}
