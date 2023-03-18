#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;
class Vec {
 private:
  int len;
  double *v;
  double *get_vec() const;
 public:
  Vec(int len, double *cords);
  int get_len() const;
  Vec (const Vec &v);
  void set(double arg, int coord);
  double get(int coord);
  double euc_norm();
  double max_norm();
  void print();

  friend Vec operator+(const Vec &op1, const Vec &op2);
  friend Vec operator-(const Vec &op1, const Vec &op2);

  Vec& operator=(const Vec &op);
  bool operator==(const Vec &op) const;

  double& operator[](size_t ind);
  const double& operator[](size_t ind) const;

  friend Vec operator*(const Vec &op, double lambda);
  friend Vec operator*(double lambda, const Vec &op);

  friend std::ostream& operator<<(std::ostream &os, const Vec &op);

  ~Vec();
};


std::ostream& operator<<(std::ostream &os, const Vec &op) {
  os << "(";
  for (int i = 0; i < op.get_len(); i++) {
    if (i != op.get_len()-1)
      os << op.v[i] << ",";
    else
      os << op.v[i] << ")";
  }
  return os;
}

Vec operator*(double lambda, const Vec &op) {
  return op*lambda;
}

Vec operator*(const Vec &op, double lambda) {
  Vec v = op;
  for (int i = 0; i < op.get_len(); i++) {
    v[i]*=lambda;
  }
  return v;
}

double& Vec::operator[](size_t ind) {
  return v[ind];
}
const double& Vec::operator[](size_t ind) const {
  return v[ind];
}


bool Vec::operator==(const Vec &op) const {
  if (this->len != op.len) {
    return false;
  }
  bool flag = true;
  for (int i = 0; i < len; i++) {
    if (v[i] != op.v[i]) {
      flag = false;
      break;
    }
  }
  return flag;
}

Vec& Vec::operator=(const Vec &op) {
  if (len != op.len) {
    delete [] v;
    len = op.len;
    v = new double[len];
  }
 // memcpy(v, op.v, len);
  for (int i = 0; i < len; i++) {
    v[i] = op.v[i];
  }
  return *this;
}

Vec operator+(const Vec &op1, const Vec &op2) {
  Vec res = op1;
  for (int i = 0; i < op1.get_len(); ++i) {
    res[i] += op2[i];
  }
  return res;
}

Vec operator-(const Vec &op1, const Vec &op2) {
  Vec res = op1;
  for (int i = 0; i < op1.get_len(); ++i) {
    res[i] -= op2[i];
  }
  return res;
};



Vec::Vec(int len, double *cords = nullptr) {
  this->len = len;
  this->v = new double[len];
  if (cords != nullptr) {
    for (int i = 0; i < len; i++) {
      v[i] = cords[i];
    }
  } else {
    for (int i = 0; i < len; i++) {
      v[i] = 0;
    }
  }
}
int Vec::get_len() const{
  return this->len;
}
double *Vec::get_vec() const{
  return this->v;
}
Vec::Vec (const Vec &v) {
  this->len = v.get_len();
  this->v = new double[this->len];
  double *tmp = v.get_vec();
  for (int i = 0; i < this->len; i++) {
    (this->v)[i] = tmp[i];
  }
}
void Vec::set(double arg, int coord) {
  if (coord < 0 || coord >= len)
    return;
  v[coord] = arg;
}
double Vec::get(int coord) {
  if (coord < 0 || coord >= len)
    return 0.0;
  return (this->v)[coord];
}
double Vec::euc_norm() {
  double res = 0;
  for (int i = 0; i < this->len; ++i) {
    res+= get(i)* get(i);
  }
  return sqrt(res);
}
double Vec::max_norm() {
  double res = abs((this->v)[0]);
  for (int i = 0; i < len; ++i) {
    res = std::max(res, abs(v[i]));
  }
  return res;
}
void Vec::print() {
  std::cout << "(";
  for (int i = 0; i < len; i++) {
    if (i != len-1)
      std::cout << v[i] << ",";
    else
      std::cout << v[i] << ")";
  }
  std::cout << std::endl;
}
Vec::~Vec() {
  delete [] this->v;
}
/*
int main(void)
{
  double y1[3] = {1,2,3};
  double y2[5] = {2,1,0,5,7};
  Vec x(3, y1), y(5, y2), z(4);
  Vec u = x;

  y.print();
  x.print();
  z.print();
  u.print();

  x.set(23, 2);  u.set(34, 1);  z.set(-3, 3);
  z.print();
  cout << "x[2] = " << x.get(2) << endl;
  cout << "u[1] = " << u.get(1) << endl;
  cout << "euc_norma y: " << y.euc_norm() << endl;
  cout << "max_norma z: " << z.max_norm() << endl;
  return 0;
}
*/

/*
int main()
{
  double y1[4] = {1,2,3,4};
  double y2[4] = {-2,1,3,-3};

  Vec u(4, y1), v(4, y2);
  Vec w(4);

  cout << "u = " << u << endl;
  cout << "v = " << v << endl;
  w = u = u;
  cout << "w = u = " << w << endl;
  w = 4.*u   + v*3;
  cout << "w = 4.*u + v*3 = " << w << endl;
  cout << "u = " << u << endl;
  w[2] = 3;
  w[0] = -1;
  cout << "w = " << w << endl;
  cout << 2*2*u*2 * 2 << endl;
  cout << u << endl;
  double y3[] = {4, 8, 12, 16};
  const Vec z(4, y3);
  u = 2*u*2;
  cout << "u = " << u << endl;
  u = u - u - u;
  cout << "u = " << u << endl;
  std::cout << z[0] << endl;
  std::cout << (u == z) << std::endl;
  //z[0] = 1;
  std::cout << z << endl;
  return 0;
}
*/
/*
int main() {
  double par[] = {1, 2, 3};
  double par1[] = {3, 2, 1};
  Vec v(3, par);
  Vec v1(3, par1);
  Vec v2(3);
  v2 = v-v1;
  v = v1+v2+v;
  std::cout << v;
  v = 3*v*3;
  std::cout << v;
  std::cout << std::endl;
  //std::cout <<
  std::cout << (v1.get_vec())[0];
  return 0;
}*/