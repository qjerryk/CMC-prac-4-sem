#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
using namespace std;

class vector_exception {
 private:
  const char *msg;
  int len1, len2;
 public:
  vector_exception(int len1, int len2): msg("Exception: addition of vectors of different lengths: "), len1(len1), len2(len2) {}
  vector_exception(int len): msg("Exception: incorrect indexing: "), len1(len), len2(-1) {}
  vector_exception(): msg("Exception: unknown exception"), len1(-1), len2(-1) {}
  vector_exception(const vector_exception &other): msg(other.msg), len1(other.len1), len2(other.len2) {}
  const char *get_msg() const {
    return msg;
  }
  int get_first() const {
    return len1;
  }
  int get_second() const {
    return len2;
  }
};
template <typename T>
class Vec {
 private:
  int len;
  T *v;
  T *get_vec() const;
 public:
  Vec(int len, T *cords);
  int get_len() const;
  Vec (const Vec &v);
  void set(T arg, int coord);
  T get(int coord) const;
  T euc_norm() const;
  T max_norm() const ;
  void print() const;

  template <typename A>
  friend const Vec<A> operator+(const Vec<A> &op1, const Vec<A> &op2);

  template<typename  A>
  friend const Vec<A> operator-(const Vec<A> &op1, const Vec<A> &op2);

  Vec<T>& operator=(const Vec<T> &op);
  bool operator==(const Vec<T> &op) const;

  T& operator[](int ind);
  const T& operator[](int ind) const;

  template<typename A>
  friend const Vec<A> operator*(const Vec<A> &op, A lambda);

  template<typename A>
  friend const Vec<T> operator*(T lambda, const Vec<T> &op);

  template<typename A>
  friend std::ostream& operator<<(std::ostream &os, const Vec<A> &op);

  Vec<T>& operator+=(const Vec<T> &op);
  int operator^(const Vec<T> &op);
  ~Vec();
};


template <typename T>
int Vec<T>::operator^(const Vec<T> &op) {
  if (len != op.get_len()) {
    //
  }
  int res = 0;
  for (int i = 0; i < len; ++i) {
    res += (*this)[i]*op[i];
  }
  return res;
}

template <typename T>
Vec<T>& Vec<T>::operator+=(const Vec<T> &op) {
  *this = *this + op;
  return this;
}

template <typename T>
std::ostream& operator<<(std::ostream &os, const Vec<T> &op) {
  os << "(";
  for (int i = 0; i < op.get_len(); i++) {
    if (i != op.get_len()-1)
      os << op.v[i] << ",";
    else
      os << op.v[i] << ")";
  }
  return os;
}

template<typename T>
const Vec<T> operator*(T lambda, const Vec<T> &op) {
  return op*lambda;
}

template <typename T>
const Vec<T> operator*(const Vec<T> &op, T lambda) {
  Vec<T> v = op;
  for (int i = 0; i < op.get_len(); i++) {
    v[i]*=lambda;
  }
  return v;
}

template <typename T>
T& Vec<T>::operator[](int ind) {
  if (ind >= len || ind < 0) {
    throw vector_exception(ind);
  }
  return v[ind];
}

template <typename T>
const T& Vec<T>::operator[](int ind) const {
  if (ind >= len || ind < 0) {
    throw vector_exception(ind);
  }
  return v[ind];
}

template <typename T>
bool Vec<T>::operator==(const Vec<T> &op) const {
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

template <typename T>
Vec<T>& Vec<T>::operator=(const Vec<T> &op) {
  if (len != op.len) {
    delete [] v;
    len = op.len;
    v = new T[len];
  }
 // memcpy(v, op.v, len);
  for (int i = 0; i < len; i++) {
    v[i] = op.v[i];
  }
  return *this;
}

template <typename T>
const Vec<T> operator+(const Vec<T> &op1, const Vec<T> &op2) {
  if (op1.len != op2.len) {
    throw vector_exception(op1.len, op2.len);
  }
  Vec<T> res = op1;
  for (int i = 0; i < op1.get_len(); ++i) {
    res[i] += op2[i];
  }
  return res;
}

template <typename T>
const Vec<T> operator-(const Vec<T> &op1, const Vec<T> &op2) {
  if (op1.len != op2.len) {
    throw vector_exception(op1.len, op2.len);
  }
  Vec<T> res = op1;
  for (int i = 0; i < op1.get_len(); ++i) {
    res[i] -= op2[i];
  }
  return res;
}


template <typename T>
Vec<T>::Vec(int len, T *cords) {
  if (len <= 0) {
    throw "Exception: length error";
  }
  this->len = len;
  this->v = new T[len];
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

template <typename T>
int Vec<T>::get_len() const{
  return this->len;
}

template <typename T>
T *Vec<T>::get_vec() const{
  return this->v;
}

template <typename T>
Vec<T>::Vec (const Vec<T> &v) {
  this->len = v.get_len();
  this->v = new T[this->len];
  T *tmp = v.get_vec();
  for (int i = 0; i < this->len; i++) {
    (this->v)[i] = tmp[i];
  }
}

template <typename T>
void Vec<T>::set(T arg, int coord) {
  if (coord < 0 || coord >= len){
   throw "Exception: coordinate error in set()";
  }
  v[coord] = arg;
}

template <typename T>
T Vec<T>::get(int coord) const {
  if (coord < 0 || coord >= len) {
    throw "Exception: coordinate error in get()";
  }
  return (this->v)[coord];
}

template <typename  T>
T Vec<T>::euc_norm() const {
  T res = 0;
  for (int i = 0; i < this->len; ++i) {
    res+= get(i)* get(i);
  }
  return sqrt(res);
}

template <typename T>
T Vec<T>::max_norm() const {
  T res = abs((this->v)[0]);
  for (int i = 0; i < len; ++i) {
    res = std::max(res, abs(v[i]));
  }
  return res;
}

template <typename T>
void Vec<T>::print() const {
  std::cout << "(";
  for (int i = 0; i < len; i++) {
    if (i != len-1)
      std::cout << v[i] << ",";
    else
      std::cout << v[i] << ")";
  }
  std::cout << std::endl;
}
template <typename T>
Vec<T>::~Vec() {
  delete [] this->v;
}

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


void Vector()
{
  using namespace std;
  double wd[3] = {1.5,2.3,-1.7};
  double wd2[4] = {1.1,2.3,4.5,6.7};
  Vec<double>  vd1(3, wd), vd2(4, wd2);
  d2 += vd1;
  cout << "vd1 = " << vd1 << endl;
  cout << "vd2 = " << vd2 << endl;
  //double prd = vd1^vd2;
  //cout << "vd1^vd2 = " << prd << endl;
  vd2 = vd1 = vd1;
  cout << "vd2 = " << vd2 << endl;
}

int main() {
  try {
    Vector();
  }
  catch(const vector_exception &ex) {
    if (ex.get_first() == -1) {
      std::cerr << ex.get_msg() << std::endl;
    } else if (ex.get_second() == -1) {
      std::cerr << ex.get_msg() << ex.get_first() << std::endl;
    } else {
      std::cerr << ex.get_msg() << ex.get_first() << " " << ex.get_second() << std::endl;
    }
  }
  catch(const char *msg) {
    std::cerr << msg << std::endl;
  }
  catch(...) {
    std::cerr << "Exception: unknown error" << std::endl;
  }
  return 0;
}
