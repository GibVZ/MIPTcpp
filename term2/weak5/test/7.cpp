#include <cassert>



struct Stack {
    size_t size, reserved;
    int * store;
};

Stack stack_new() {
    Stack ret{0, 0, nullptr};
}

bool stack_is_empty(Stack const &s) {
    return (s.size == 0);
}

bool stack_is_full(Stack const &s) {
    return (s.size == 100);
}

Stack& stack_push(Stack &s, int val) {
    if(s.size >= s.reserved)
    {
    	int * new_store = new int[2 * s.reserved];
    	for (size_t i = 0; i < s.size; ++i)
    	{
    		new_store[i] = store[i];
    	}
    	
    } else {
    	
    }
}

int stack_pop(Stack &s) {
    // Code
}



int main() {
    Stack s = stack_new();
    assert(true == stack_is_empty(s));
    stack_push(s, -1);
    assert(false == stack_is_empty(s));
    assert(expected == stack_pop(s));
    assert(true == stack_is_empty(s));
    return 0;
}
