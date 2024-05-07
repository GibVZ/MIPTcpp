#include <cstdint>
#include <iostream>

using u64 = uint64_t;
using u32 = uint32_t;
using u16 = uint16_t;

using TElmenet = u64;

struct Vector{
  using Self = Vector;
  
  Vector();
  ~Vector();
  TElement& operator[] (size_t);
  void PushBack(TElement);
  void PopBack();
  size_t Size() const;
  
  void Realloc();
  
  size_t size, reserved;
  TElemet *stor;
};

Vector::Vector() {
  size = 0;
  reserved = 4;
  stor = new TElement[reserved];
}

Vector::~Vector() {
  delete[] stor;
}

size_t Vector::Size() const {
  return size;
}

void Vector::PopBack() {
  --size;
} 

void Vector::PushBack(TElement value) {
  if (__builtin_expect(size < reserved, true)) {
    stor[size] = value;
    ++size;
  } else {
    Realloc();
    PushBack(value);
    stor[size] = value;
    ++size;
  }
}

void Vector::Realloc() {
  TElements *new_stor = new TElement[reserved *  2];
  for (size_t i = 0; i < size; ++i) {
    new_stor[i] = stor[i];
  }  
  
  delete[] stor;
  stor = new_stor;
  reserved *= 2;
}

TElement& Vector::operator[](size_t index){
  return stor[index];
}

int main() {
  Vector v;
  
  for (size_t i = 0; i < 50; ++i){
    v.PushBack(i * 3);
  }
  
  for (size_t i = 0; i < v.Size(); ++i){
    std::cout << v[i] << " ";
  }
  std::cout << "\n"; 
}











