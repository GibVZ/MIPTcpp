#include <cstdint>
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>

using u32 = uint32_t;

struct SDBMHash {
  u32 operator() (const char* buf, size_t len) const {
    u32 h = 0;

    for (size_t i = 0; i < len; ++i) {
      h = buf[i] + (h << 6) + (h << 16) - h;
    }

    return h;
  }
};

struct FNVHash32 {
  static const u32 h0 = 0x811c9dc5;
  static const u32 b = 16777619;

  u32 operator() (const char* buf, size_t len) const {
    u32 h = h0;

    for (size_t i = len; i > 0; --i) {
      h = (h ^ buf[i - 1]) * b;
    }

    return h;
  }
};

struct HT{
  struct Bucket {

    Bucket(): state(kFree), key(), value() {}

    enum State{kFree, kFilled, kErased} ;
    std::string key;
    std::string value;
    State state;
  };

  struct Iterator {
    Iterator(HT* ht_, u32 ix_)
      : bucket(&(ht_->table[ix_])), ht(ht_)
    {}

    Iterator() : ht(nullptr), bucket(nullptr) {}

    Bucket * bucket;
    HT * ht;

    bool operator! () const {
      return bucket != nullptr;
    }

    operator bool() const {
      return bucket != nullptr;
    }

    Bucket& operator* () {
      return * bucket;
    }

    Bucket* operator-> () {
      return bucket;
    }
  };
  HT() : size(0), length_of_table(7), table(7) {}

  using TKey = std::string;
  using TValue = std::string;

  Iterator FindInternal_(const TKey& k);
  u32 Hash(std::string const &c) const {
    return 0; //hash(c.c_str(), c.length()) % length_of_table ; 
  }

  u32 Next(u32 ix) const {
    return (ix + 1) % length_of_table;
  }

  void ReportLoop() const {
    throw std::runtime_error("Br0ther, loops!");
  }

  void Add(std::string const &a, std::string const &b);

  void Erase(std::string const &a);

  bool Find(std::string const &a);

  std::string& Get(std::string const &a);


  SDBMHash hash;
  u32 length_of_table;
  u32 size;
  std::vector<Bucket> table ;
};

HT::Iterator HT::FindInternal_(const TKey& k) {
  auto ix = Hash(k);
  u32 counter = 0;

  while (true) {
    auto& cur = table[ix];

    if (cur.state == Bucket::kFree) {
      return {};
    }

    if (cur.state == Bucket::kFilled) {
      if (cur.key == k) {
        return Iterator(this, ix);
      }
    }

    if (cur.state == Bucket::kErased) {
      // We could maybe just return null-iter here
      // bc it probably means that we did have our value,
      // and then erased it, but whatever
    }

    ++counter;
    if (counter >= length_of_table) {
      ReportLoop();
    }

    ix = Next(ix);
  }
}

void HT::Add(std::string const &k_, std::string const &v_){
  auto it = FindInternal_(k_);

  if (it) {
    it->value = v_;
    return;
  }
  
  auto ix = Hash(k_);

  u32 counter = 0;

  while (true) {
    auto& cur = table[ix];
    if (cur.state == Bucket::kFilled) {
      ++counter;

      if (counter >= length_of_table) {
        ReportLoop();
      }
      
      ix = Next(ix);
      continue;
    }

    cur.state = Bucket::kFilled;
    cur.key = k_;
    cur.value = v_;
    ++ size;
    return;
  }
}

void HT::Erase(const TKey &k_) {
  auto ix = Hash(k_);
  
  u32 counter = 0;

  while (true) {
    auto& cur = table[ix];
    if (cur.state == Bucket::kFilled) {
      if (cur.key == k_) {
        cur.state = Bucket::kErased;
        -- size;
        return;
      }
    }
    if (cur.state == Bucket::kFree) {
      return;
    }

    ++counter;

    if (counter >= length_of_table) {
      ReportLoop();
    }
    
    ix = Next(ix);
  }
}

bool HT::Find(const TKey &k_) {
  return FindInternal_(k_);
}

HT::TValue& HT::Get(const TKey& k_) {
  return FindInternal_(k_)->value;
}

void pick(HT &ht, std::string const &key) {
  if(ht.Find(key)) {
    std::cout << key << ": " << ht.Get(key) << '\n';
    return;
  }
  std::cout << key << ": None\n";
}


int main() {

  HT hashtable;

  hashtable.Add("Apple", "37 rubles");
  hashtable.Add("Pineapple", "338 rubles");
  hashtable.Add("Buddy", "300 bucks");


  pick(hashtable, "Apple");
  pick(hashtable, "Pineapple");
  pick(hashtable, "Buddy");
  pick(hashtable, "Nill Kiggers");

  hashtable.Erase("Pineapple");
  std::cout << "\nAfter erasing:\n";
  
  pick(hashtable, "Apple");
  pick(hashtable, "Pineapple");
  pick(hashtable, "Buddy");
  pick(hashtable, "Nill Kiggers");


  /*
  std::string s;
  std::hash<std::string> st;
  SDBMHash sd;
  FNVHash32 fn;
  while (true) {
    std::cin >> s;
    std::cout << "std: " << std::hex << std::setw(8) << std::setfill('0') << st(s) <<
      "\tsdbm: " << std::hex << std::setw(8) << std::setfill('0') << sd(s.c_str(), s.length()) <<
      "\tfnv: " << std::hex << std::setw(8) << std::setfill('0') << fn(s.c_str(), s.length()) << '\n';
  } */
}
