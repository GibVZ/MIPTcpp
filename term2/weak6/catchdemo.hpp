#include <iostream>
#include <string>
#include <vector>

using DType = int;

class Decomposer {
public:
  Decomposer(): initialized(false) {}
  
  Decomposer(const Decomposer&) = delete; // запрещает инициализацию копированием
  Decomposer& operator=(const Decomposer&) = delete; // запрещает присвоение копированием
  Decomposer& operator=(const Decomposer&&) = delete; // запрещает присвоение копированием(чета короче тоде запрещает)
  Decomposer(const Decomposer&&) = delete; // запрещает (вроде бы тоже инициализацию копированием --\_(0-0)_/-- ) 
  
  Decomposer& operator <= (const DType x){
    if(!initialized) {
      initialized = true;
      cur_value = x;
      return *this;
    }
    Remember("<=", x);
    cur_value = (cur_value <= x);
    return *this;
  }
  
  Decomposer& operator == (const DType x){
    Remember("==", x);
    cur_value = (cur_value == x);
    return *this;
  }
  
  Decomposer& operator >= (const DType x){
    Remember(">=", x);
    cur_value = (cur_value >= x);
    return *this;
  }
  Decomposer& operator < (const DType x){
    Remember("<", x);
    cur_value = (cur_value < x);
    return *this;
  }
  Decomposer& operator > (const DType x){
    Remember(">", x);
    cur_value = (cur_value > x);
    return *this;
  }
  
  Decomposer& operator + (const DType x){
    Remember("+", x);
    cur_value = (cur_value + x);
    return *this;
  }
  Decomposer& operator - (const DType x){
    Remember("-", x);
    cur_value = (cur_value - x);
    return *this;
  }
  Decomposer& operator * (const DType x){
    Remember("*", x);
    cur_value = (cur_value * x);
    return *this;
  }
  Decomposer& operator / (const DType x){
    Remember("/", x);
    cur_value = (cur_value / x);
    return *this;
  }
  void PrintTo(std::ostream& os){
    os << lhs << " " << cmp << " " << rhs;
  }
  bool ToBool(){
    return static_cast<bool>(cur_value);
  }
private:
  void Remember(const char * ccmp, DType rhs_r){
    lhs = cur_value;
    cmp = ccmp;
    rhs = rhs_r;
  }
  DType cur_value;
  std::string cmp;
  DType lhs, rhs;
  bool initialized;
};

#define REQUIRE(expr) 					\
do{                   					\
  Decomposer d;       					\
  d <= expr;          					\
  if(! RequireInternal(d, #expr, __FILE__, __LINE__))	\
   return false;					\
}while(false)



bool RequireInternal(Decomposer& result, const char * expr, const char * file, const int line){
  if(result.ToBool()){
    return true;
  }
  std::cerr << "Assertion failed!\n";
  std::cerr << "\tIn file " << file << ':' << line << "\n";
  std::cerr << "\tExpression: " << expr << "\n";
  std::cerr << "\tExpands to: ";
  result.PrintTo(std::cerr);
  std::cerr << "\n";
  
  return false;
  // std::exit(1);
}

#define CONCAT_HELPER(a, b) a##b
#define CONCAT(a, b) CONCAT_HELPER(a, b)
#define UNIQUE_NAME(base) CONCAT(base, __COUNTER__)

#define TEST_CASE_INTERNAL(M_NAME, description) \
  struct M_NAME {				\
    static const char * test_name = description;\
    static void Run();				\
  };						\
  static void M_NAME::Run()

#define TEST_CASE(description) TEST_CASE_INTERNAL(UNIQUE_NAME(Test), descroption)

struct TestManager {
  using TTestFunction = bool (*) ();
  // TestManager()
  void Register(TTestFunction func) {
    functions.emplace_back(func);
  }
  
  std::vector<TTestFunction> functions;
};



