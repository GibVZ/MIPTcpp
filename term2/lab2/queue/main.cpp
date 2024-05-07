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
  size_t poll_idx, push_idx;
  size_t reserved;
  
  Queue() : reserved(1) {
    store = new TValue[reserved];
    poll_idx = 0;
    push_idx = 0;
  }
  ~Queue() {
    delete[] store;
  }
  TValue & Poll() { 
    if (poll_idx == push_idx)
      return *store;
    TValue &ret = store[poll_idx];
    if(poll_idx == (reserved - 1)) 
      poll_idx = 0;
    else
      ++poll_idx;
    return ret;
  }
  void Push(TValue element) {
    if(push_idx == (reserved - 1)) 
    {
      if(poll_idx == 0)
      {
        realloc();
        store[push_idx] = element;
        ++push_idx;
      }
      else
      {
        store[push_idx] = element;
        push_idx = 0;
      }
    }
    else if ((push_idx + 1) == poll_idx)
    {
      realloc();
      store[push_idx] = element;
      ++push_idx;
    } 
    else 
    {
      store[push_idx] = element;
      ++push_idx;
    }
  }
 private:
  void realloc() {
    TValue *new_store = new TValue[reserved * 2];
    if (push_idx > poll_idx)
    {
      for (size_t i = poll_idx; i < push_idx; ++i)
      {
        new_store[i - poll_idx] = store[i];
      }
    } else 
    {
      size_t new_store_idx = 0;
      for (size_t i = poll_idx; i < reserved; ++i) 
      {
        new_store[new_store_idx] = store[i];
        ++new_store_idx;
      }
      for (size_t i = 0; i < push_idx; ++i) 
      {
        new_store[new_store_idx] = store[i];
        ++new_store_idx;
      }
    }
    delete[] store;
    store = new_store;
    poll_idx = 0;
    push_idx = reserved - 1;
    reserved *= 2;
  }
};




double selftest(size_t iterations, size_t arrlen){
  Queue* q = new Queue[iterations];
   
  for(size_t i = 0; i < iterations; ++i) {
    for(size_t j = 0; j < arrlen; ++j) {
      q[i].Push(j);
    }
  } 
    
  auto begin =  std::chrono::steady_clock::now();

  for (size_t i = 1; i < iterations; ++i)
  {
    q[i].Poll();
  }
  auto end = std::chrono::steady_clock::now();
  auto time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
  return (double)time_span.count() / iterations;
}

int main(int argc, char **argv){
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






