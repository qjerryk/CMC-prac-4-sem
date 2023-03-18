#include <iostream>

class BitString {
 private:
  unsigned int first, second; // first -  старшая часть числа, second - младшая
 public:
  BitString(const unsigned second = 0) {
    this->first = 0;
    this->second = second;
  }
  BitString(const unsigned first, const unsigned second) {
    this->first = first;
    this->second = second;
  }
  unsigned get_first() const {
    return this->first;
  }
  unsigned get_second() const {
    return this->second;
  }
  void Print() {
    unsigned long long tmp = ((unsigned long long)this->first << sizeof(unsigned)*8) | this->second;
    std::cout << tmp << std::endl;
  }
  void ShiftLeft(const unsigned &offset) {
    unsigned mask = 1u << (sizeof(unsigned)*8 - 1);
    if (offset >= 64) {
      this->first = 0;
      this->second = 0;
      return;
    }
    for (int i = 0; i < offset; i++) {
      unsigned tmp = (this->second & mask) != 0u; // tmp равен 1, если последняя цифра двоичного представления младшой части равна 1
      this->second <<= 1;
      this->first <<= 1;
      this->first |= tmp;
    }
  }
  void ShiftRight(const unsigned &offset) {
    if (offset >= 64) {
      this->first = 0;
      this->second = 0;
      return;
    }
    for (int i = 0; i < offset; i++) {
      unsigned tmp = this->first & 1u; // tmp равен 1, если первая цифра двоичного представления старшей части равна 1
      this->second >>= 1;
      this->first >>= 1;
      unsigned mask = tmp << (sizeof(unsigned)*8 - 1);
      this->second |= mask;
    }
  }
  void NOT() {
    this->first = ~this->first;
    this->second = ~this->second;
  }
  void AND(const BitString &a) {
    this->first = this->first & a.get_first();
    this->second &= a.get_second();
  }
  void OR(const BitString &a) {
    this->first |= a.get_first();
    this->second |= a.get_second();
  }
  void XOR(const BitString &a) {
    this->first ^= a.get_first();
    this->second ^= a.get_second();
  }

};
/*
int main() {
  BitString b1(127,255);
  b1.Print();
  b1.ShiftLeft(3);
  b1.Print();
  BitString b2(511,1025), b3(2045);
  b2.Print();
  b1.AND(b2);
  b1.Print();
  b3.Print();
  b1.OR(b3);
  b1.Print();
  b2.Print();
  b2.XOR(b1);
  b2.Print();
  b3.NOT();
  b3.Print();
  return 0;
  //std::cout << (1u << (sizeof(unsigned)*8 - 1)) << std::endl;
  return 0;
}
 */