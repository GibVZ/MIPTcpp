#include <cstdint>
#include <iostream>

using u64 = uint64_t;
using u32 = uint32_t;
using u16 = uint16_t;

using element_t = u64;

struct Matrix { 
  element_t *stor;
  size_t w, h, offrow, offcol;
  
  Matrix(size_t, size_t);
  Matrix(const Matrix&);
  ~Matrix();
  
  Matrix& Transpose();
  
  Matrix& operator+=(const Matrix& other);
  Matrix& operator+(const Matrix& other);
  
  Matrix& operator-=(const Matrix& other);
  Matrix& operator-(const Matrix& other);
  
  Matrix& operator*=(const Matrix& other);
  Matrix& operator*(const Matrix& other);
  
  Matirx& operator=(const Matrix& other);
  
  size_t Ind(size_t, size_t);
};

Matrix::Matrix(size_t width, size_t height) {
  w = width; h = height;
  offrow = 1; offcol = w;
  stor = new element_t[w * h];
}

Matrix::Matrix(const Matrix& other){
  w = other.w;
  h = other.h;
  stor = new element_t[w * h];
  
  offcol = 1;
  offcol = w;
  
  for(size_t i = 0; i < h; ++i){
    for(size_t j = 0; j < h; ++j){
      stor[Ind(i, j)] = other.stor[Ind(i, j)];
    }
  }
}

Matrix::~Matrix() {
  delete[] stor;
}

size_t Matrix::Ind(size_t x, size_t y){
  return x * offrow + y * offcol;
}

Matrix& Matrix::operator=(const Matrix& other){
  if ((other.w == w) || (other.h == h)){
    CopyInPlace(other);
    return *this;
  }
  // continue
}

Matrix& Matrix::operator+=(const Matrix& other) {
  Matrix copy(*this);
  copy += other
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











