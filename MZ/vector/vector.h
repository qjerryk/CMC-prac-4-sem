#include <iostream>
#include <string>
#include <cmath>
#include <cstring>


class vector_exception {
 private:
  const char *msg;
  int par_n;
  int par1;
  int par2;
 public:
  vector_exception(const char *msg, int par_n = 0, int par1 = 0, int par2 = 0): msg(msg), par_n(par_n), par1(par1), par2(par2) {}
  vector_exception(const vector_exception &other): msg(other.msg), par_n(other.par_n), par1(other.par1), par2(other.par2) {}

  void what(void) const {
    if (par_n == 0) {
      std::cerr << msg << std::endl;
    }
    if (par_n == 1)
      std::cerr << msg << " " << par1 << std::endl;
    if (par_n == 2)
      std::cerr << msg << " " << par1 << " " << par2 << std::endl;
  }
};

template <typename T>
class Vec {
 private:
  int len;
  T *v;
  T *get_vec() const;
 public:
  Vec(int len, const T *cords);
  Vec (const Vec &v);
  Vec(int len);

  int get_len() const;
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
  T operator^(const Vec<T> &op);
  ~Vec();
};


template <typename T>
T Vec<T>::operator^(const Vec<T> &op) {
  if (len != op.get_len()) {
    throw vector_exception("Exception: multiplication of vectors of different lengths:", 2, len, op.len);
  }
  T res = 0;
  for (int i = 0; i < len; ++i) {
    res += (*this)[i]*op[i];
  }
  return res;
}

template <typename T>
Vec<T>& Vec<T>::operator+=(const Vec<T> &op) {
  *this = *this + op;
  return *this;
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
    throw vector_exception("Exception: incorrect indexing:", 1, ind);
  }
  return v[ind];
}

template <typename T>
const T& Vec<T>::operator[](int ind) const {
  if (ind >= len || ind < 0) {
    throw vector_exception("Exception: incorrect indexing:", 1, ind);
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
    throw vector_exception("Exception: addition of vectors of different lengths:", 2, op1.len, op2.len);
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
    throw vector_exception("Exception: addition of vectors of different lengths:", 2, op1.len, op2.len);
  }
  Vec<T> res = op1;
  for (int i = 0; i < op1.get_len(); ++i) {
    res[i] -= op2[i];
  }
  return res;
}


template <typename T>
Vec<T>::Vec(int len, const T *cords) {
  if (len <= 0) {
    throw vector_exception("Exception: length error", 0);
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
Vec<T>::Vec(int len): len(len) {
  if (len <= 0) {
    throw vector_exception("Exception: length error", 0);
  }
  v = new T[len];
  /*this->len = len;
  this->v = new T[len];
  if (cords != nullptr) {
    for (int i = 0; i < len; i++) {
      v[i] = cords[i];
    }
  } else {
    for (int i = 0; i < len; i++) {
      v[i] = 0;
    }
  }*/
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
    
   throw vector_exception("Exception: coordinate error in set()", 0/*, 1, coord*/);
  }
  v[coord] = arg;
}

template <typename T>
T Vec<T>::get(int coord) const {
  if (coord < 0 || coord >= len) {
    throw vector_exception("Exception: coordinate error in get()", 0/*, 1, coord*/);
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

