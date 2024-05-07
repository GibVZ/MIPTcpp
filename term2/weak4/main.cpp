#include <iostream>
#include <vector>
#include <cstdint>
#include <cstddef>
#include <cstdlib>
#include <random>

// What are we doing&
// We explore heap(data structure)
//	We have a operations P: AxA -> bool
//	that have a "compare" feature:
// 		1) P(a, a) == false
//		2) P(a, b) = true => P(b, a) = false
//		3) P(a, b) & P(b, c) => P(a, c)
//	sometimes we have e(a, b) := (not P(a, b)) & (not P(b, a))
//		e(a, b) & e(b, c) => e(a, c)

// heap is the binary tree, for which "parent >= childs"
// in heap we want methods:
//	1) push(add child)	O(log N), where N - amount of elements
//	2) pop head		O(log N)
//	3) heapify*
// so create a (дополнительный) methods:
// 	1) sift up (for push)
//	2) sipt down (for pop head)


// let create two variants - truth tree and some cheat(this is dynamic array(vector))

using ValueType = uint32_t;

struct HeapVec{
	std::vector<ValueType> data;
	size_t size;

	HeapVec(){
		data = {};
		size = 0;
	}
	~HeapVec(){
		data.clear();
	}
	ValueType Top(){
		return data[0];
	}
	void Push(ValueType value){
		data.push_back(value);
		++size;
		SiftUp(size - 1);
	}
	void Swap(size_t a, size_t b){
		std::swap(data[a], data[b]);
	}
	void Pop(){
		Swap(0, size-1);
		data.pop_back();
		--size;
		SiftDown(0);
	}
	void SiftUp(size_t curr){
	    if(curr == 0)
	      return;
	    if(data[curr / 2] < data[curr]){
	      Swap(curr / 2, curr);
	      SiftUp(curr / 2);
	    }
	}
	void SiftDown(size_t curr){
		// curr->left = data[2*curr], curr->right = data[2*curr + 1]
	    if(2*curr + 1 >= size)
	      return;
	    size_t pivot = curr;
	    if((2*curr + 1 < size) && (data[2*curr + 1] > data[pivot]))
	      pivot = 2*curr + 1;
	    if((2*curr < size) && (data[2*curr] > data[pivot]))
	      pivot = 2*curr;
	    if(pivot != curr){
	      Swap(pivot, curr);
	      SiftDown(pivot);
	    }
	}
	void Heapify(){

	}
};





int main(){
  HeapVec heap;

  const size_t N = 100;
  size_t * vals = new size_t[N];

  for (size_t i = 0; i < N; ++i) {
    vals[i] = i;
  }
  std::random_device rd;
  std::mt19937 re{rd()};
  std::uniform_int_distribution<size_t> dist{0, N-1
  };

  for (size_t i = 0; i < N; ++i) {
    size_t i1 = dist(re), i2 = dist(re);
    std::swap(vals[i1], vals[i2]);
  }

  for (size_t i = 0; i < N; ++i) {
    std::cout << vals[i] << ' ';
    heap.Push(vals[i]);
  }
  std::cout << '\n';
  
  for (size_t i = 0; i < N; ++i) {
    vals[i] = heap.Top();
    heap.Pop();
  }


  for (size_t i = 0; i < N; ++i) {
    std::cout << vals[i] << ' ';
  }
  std::cout << '\n';

  delete[] vals;

}
