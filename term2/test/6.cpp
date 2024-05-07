#include <iostream>
#include <stack>

bool is_valid_pattern(char const *p) {
    std::stack<char> s;
    for(char const *sym = p; *sym != 0; ++sym)
    {
    	if ((s.top() == '(') && (s.top()) )
    }
}


int main(int argc, char **argv) 
{
    std::cout << is_valid_pattern(argv[0]);
}
