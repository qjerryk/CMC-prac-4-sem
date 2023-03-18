#include <iostream>
#include <cmath>
//using namespace std;
class Vector_3d {
 private:
  double x, y, z;
 public:
  Vector_3d(double a = 0, double b = 0, double c = 0) {
    x = a;
    y = b;
    z = c;
  }
  void print() {
    std::cout << '(' << x << "," << y << "," << z << ")" << std::endl;
  }
  double euc_norm() {
    return sqrt(x*x+y*y+z*z);
  }
  double max_norm() {
    return std::max(std::abs(x), std::max(std::abs(y), std::abs(z)));
  }
  double get_x(){
    return x;
  }
  double get_y(){
    return y;
  }
  double get_z(){
    return z;
  }
  void set(double a, double b, double c) {
    x = a;
    y = b;
    z = c;
  }
};
/*
int main() {
  Vector_3d v(1.5, 2.4, 3.);
  Vector_3d w, u = 2.;
  v.print();
  w.print();
  u.print();
  cout << "norma euc v = " << v.euc_norm() << endl;
  w.set(1,2,3);
  cout << "norma max w = " << w.max_norm() << endl;
  cout << " u_x = " << u.get_x() << endl;
  cout << " w_y = " << w.get_y() << endl;
  cout << " v_z = " << v.get_z() << endl;
  return 0;
}*/