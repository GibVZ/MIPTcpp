#include<iostream>
#include<memory>
#include<cstdint>
#include<cstddef>
#include<vector>
#include"catchdemo.hpp"

using u32 = uint32_t;
using TElement = u32;


// Несколько вариантов очереди
// 	1. LinkedList
//	2. two Vectors(hea dand tail)
// 	3. Ringbuffer(????)





class TwoStacksQueue{
public:
  TwoStacksQueue();
  const TElement& Top() const ;
  void Push(const TElement & element);
  void Pop();
  size_t Size();
private:
  size_t size_;
  std::vector<TElement> head, tail;
  void MoveTailToHead();
  std::vector<TElement> head_, tail_;
};

TwoStacksQueue::TwoStacksQueue()
  : size_(0), head(), tail() {}
  
size_t TwoStacksQueue::Size() {
  return size_;
}  

void TwoStacksQueue::Push(const TElement & element) {
  tail.emplace_back(element);
  ++size_;
}

void TwoStacksQueue::Pop() {
  if(head.empty()){
    MoveTailToHead();
  }
  head.pop_back();
  --size_;
}

const TElement& TwoStacksQueue::Top() const {
  if(head.empty())
    return tail[0];
  return head.back();
}

void TwoStacksQueue::MoveTailToHead() {
  size_t cur_size = tail.size();
  head.reserve(cur_size);
  for(size_t i = 0; i < cur_size; ++i){
    head.emplace_back(tail.back());
    tail.pop_back();
  }
}

using Queue = TwoStacksQueue;


TEST_CASE("empty queue"){
  Queue q;
  REQUIRE(q.Size() == 0);
}

TEST_CASE("single queue"){
  Queue q;
  REQUIRE(q.Size() == 0)
  q.Push(42);
  REQUIRE();
}







int main(){
  Queue q;
  
  for(size_t i = 0; i < 10; ++i){
    q.Push(i);
  }
  REQUIRE(q.Size() == 10);
//  std::cout << q.Top() << " ";
  for(size_t i = 0; i < 10; ++i){
    std::cout << q.Top() << " ";
    q.Pop();
    REQUIRE(q.Size() == 9 - i);
  }
  std::cout << "\n";
  REQUIRE(2 + 2 == 5);

}











