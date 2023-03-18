#include <iostream>

class Rect {
 private:
  int x, y;
  unsigned wd, hd;
  double get_x() const{
    return x;
  }
  double get_y() const{
    return y;
  }
  unsigned get_wd() const{
    return wd;
  }
  unsigned get_hd() const{
    return hd;
  }
 public:
  Rect(int x, int y, unsigned int wd, unsigned int hd) {
    this->x = x;
    this->y = y;
    this->wd = wd;
    this->hd = hd;
  }
  Rect (int a) {
    this->x = 0;
    this->y = 0;
    this->wd = a;
    this->hd = a;
  }
  Rect() {
    this->x = 0;
    this->y = 0;
    this->wd = 1;
    this->hd = 1;
  }
  void print_corner() const {
    std::cout << "(" << x << "," << y << ")" << std::endl;
  }
  void print_sz() const {
    std::cout << "wd=" << wd << " " << "hd=" << hd << std::endl;
  }
  int area() const {
    return (long)wd*hd;
  }
  int perimeter() const {
    return 2l*((long)wd+hd);
  }
  bool intersect(const Rect &r) const {
      long max_x = x+wd;
      long max_y = y+hd;
      long min_x = x;
      long min_y = y;

      long max_x1 = (long)r.get_x() + r.get_wd();
      long max_y1 = (long)r.get_y() +  r.get_hd();
      long min_x1 = r.get_x();
      long min_y1 = r.get_y();
      //std::cout << min_x1 << " " << max_x << " " << min_x << " " << max_x1 << "\n";
      if (min_x1 > max_x || min_x > max_x1) {
        return false;
      }
      if (min_y1 > max_y || min_y > max_y1) {
        return false;
      }
      return true;
  }

};
/*
int main() {
  Rect r1(-2, -3, 4, 5);
  Rect r2;
  Rect r3(7);
  r1.print_corner();
  r1.print_sz();

  int a2 = r2.area();
  int p2 = r2.perimeter();
  std::cout << a2 << " " << p2 << std::endl;

  if (r1.intersect(r3))
    std::cout << "YES";
  else
    std::cout << "NO";

  return 0;
}*/