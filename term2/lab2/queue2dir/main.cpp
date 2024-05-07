#include <iostream>
#include <cstdint>
#include<chrono>
#include<bits/stdc++.h>
#include<fstream>


#define ASSERT(expr) 					\
do{                   					\
  if(!expr)	                                        \
    break;      					\
  std::cerr << "Assertion failed!\n";                   \
  std::cerr << "\tIn file " << __FILE__ << ':' << __LINE__ << "\n";\
  std::cerr << "\tExpression: " << #expr << "\n";        \
}while(false)                                           


using u32 = uint32_t;

using TValue = u32;

class Queue 
{
 public:
  TValue *store;
  // size_t poll_idx, push_idx;
  size_t    head_idx, tail_idx;
  size_t reserved;
  
  Queue() : reserved(1) {
    store = new TValue[reserved];
    head_idx = 0;
    tail_idx = 0;
  }
  ~Queue() {
    delete[] store;
  }
  TValue & PollFront() { 
    if (head_idx == tail_idx)
      return *store;
    TValue &ret = store[head_idx];
    if(head_idx == (reserved - 1)) 
      head_idx = 0;
    else
      ++head_idx;
    return ret;
  }
  TValue & PollBack() { 
    if (head_idx == tail_idx)
      return *store;
    if(tail_idx == 0){
      tail_idx = reserved - 1;
    } else {
      --tail_idx;
    }
    TValue &ret = store[tail_idx];  
    return ret;
  }
  void PushBack(TValue element) {
    if(tail_idx == (reserved - 1)) 
    {
      if(head_idx == 0)
      {
        realloc();
        store[tail_idx] = element;
        ++tail_idx;
      }
      else
      {
        store[tail_idx] = element;
        tail_idx = 0;
      }
    }
    else if ((tail_idx + 1) == head_idx)
    {
      realloc();
      store[tail_idx] = element;
      ++tail_idx;
    } 
    else 
    {
      store[tail_idx] = element;
      ++tail_idx;
    }
  }
  void PushFront(TValue element) {
    if(head_idx == 0) 
    {
      if(tail_idx == (reserved - 1))
      {
        realloc();
      }
      head_idx = reserved-1;
      store[head_idx] = element;
    }
    else if ((head_idx - 1) == tail_idx)
    {
      realloc();
      head_idx = reserved-1;
      store[head_idx] = element;
    } 
    else 
    {
      --head_idx;
      store[head_idx] = element;
    }
  }
 private:
  void realloc() {
    TValue *new_store = new TValue[reserved * 2];
    if (tail_idx > head_idx)
    {
      for (size_t i = head_idx; i < tail_idx; ++i)
      {
        new_store[i - head_idx] = store[i];
      }
    } else 
    {
      size_t new_store_idx = 0;
      for (size_t i = head_idx; i < reserved; ++i) 
      {
        new_store[new_store_idx] = store[i];
        ++new_store_idx;
      }
      for (size_t i = 0; i < tail_idx; ++i) 
      {
        new_store[new_store_idx] = store[i];
        ++new_store_idx;
      }
    }
    delete[] store;
    store = new_store;
    head_idx = 0;
    tail_idx = reserved - 1;
    reserved *= 2;
  }
};




double selftest(size_t iterations, size_t arrlen){
  Queue* q = new Queue[iterations];
   
  for(size_t i = 0; i < iterations; ++i) {
    for(size_t j = 0; j < arrlen; ++j) {
      q[i].PushBack(j);
    }
  } 
    
  auto begin =  std::chrono::steady_clock::now();

  for (size_t i = 1; i < iterations; ++i)
  {
    q[i].PollFront();
  }
  auto end = std::chrono::steady_clock::now();
  auto time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
  return (double)time_span.count() / iterations;
}

int main() {
  Queue q;
  for (size_t i = 1; i < 21; ++i) {
    q.PushBack(2*i);
    q.PushFront(2*i - 1);
  }
  
  for (size_t i = 0; i < q.reserved; ++i) {
    std::cout << q.store[i] << " ";
  }
  std::cout << "\n";
  
  for (size_t i = 0; i < 20; ++i) {
    std::cout << q.PollBack() << " ";
  }
  std::cout << "\n";
}

/*int main(int argc, char **argv){
	if(argc != 4){
		std::cerr << "Brut_search expect 3 arguments(steps amount, iterations, output file) but you are giving" << argc - 1;
		return -1;
	}
	size_t steps = atoi(argv[1]);
	size_t iterations = atoi(argv[2]);
	size_t maxlen = 100000;
	size_t minlen = 100;
	std::ofstream os(argv[3]);
	for(size_t arrlen = minlen; arrlen < maxlen; arrlen+=(maxlen - minlen)/steps){
		os << selftest(iterations, arrlen) << " " << arrlen << "\n";
	}
	os.close();
	return 0;
}
*/





