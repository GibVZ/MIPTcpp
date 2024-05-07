#include <iostream>
#include <cstdint>
#include <array>

enum struct Fruit {
	APPLE,
	ORANGE,
	PINEAPPLE,
	
	ENUM_COUNT
};






// using TValue = size_t;
// using TEnum = Fruit;
template <class TEnum, class TValue>
class EnumArray {
public:
  using TReal = std::underlying_type<Fruit>::type;
  EnumArray(std::initializer_list<std::pair<Fruit, TValue>> values_): values() {
    for(auto& pair : values_){
      values[static_cast<TReal>(pair.first)] = pair.second;
    } 
  }
  // EnumArray(std::initializer_list<TValue> values_): values(values_) {}
  
  TValue& operator[] (Fruit index){ 
    return values[static_cast<TReal>(index)];
  }

  TValue& operator[] (size_t index){ 
    return values[index];
  }
  auto begin(){
    return values.begin();
  }
  auto end(){
    return values.end();
  }
  
private:
  std::array<TValue, static_cast<size_t>(Fruit::ENUM_COUNT)> values;
};


static EnumArray<Fruit, size_t> FruitPrices {
  {Fruit::APPLE, 1},
  {Fruit::ORANGE, 100},
  {Fruit::PINEAPPLE, 1000}
};

static EnumArray<Fruit, std::string> FruitNames {
  {Fruit::APPLE, "Apple"},
  {Fruit::ORANGE, "Orange"},
  {Fruit::PINEAPPLE, "Pineapple"}
};



int main() {
  std::cout << FruitPrices[Fruit::ORANGE] << "\n";
  for (auto fruit_name : FruitNames)
    std::cout << fruit_name << " ";
}
