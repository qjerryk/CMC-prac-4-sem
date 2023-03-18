#include <iostream>
#include <cstring>


const int buff = 100;


class str_exception {
 private:
  const char *msg;
  int par_n;
  int par1;
  int par2;
 public:
  str_exception(const char *msg, int par_n = 0, int par1 = 0, int par2 = 0): msg(msg), par_n(par_n), par1(par1), par2(par2) {}
  str_exception(const str_exception &other): msg(other.msg), par1(other.par1), par2(other.par2), par_n(other.par_n) {}

  void what(void) const {
    if (par_n == 1)
      std::cerr << "Exception: " << msg << par1 << std::endl;
    if (par_n == 2)
      std::cerr << "Exception: " << msg << par1 << " " << par2 << std::endl;
  }
};



class mstring {
 private:
  size_t len;
  char *str;
 public:
  mstring(const char *str);
  mstring(const mstring &other);
  size_t length() const;
  void add(const char *str);
  void add(const char &c);
  void insert(const char *str, const int offset);
  void insert(const char c, const int offset);
  void del(const int i, const int j);
  void del(const int i);
  int search(const char *str) const;
  void replace(const char *sub_str, const char *new_str);
  void print() const;
  bool isempty();
  ~mstring();


  friend mstring operator+(const mstring &op1, const mstring &op2);
  friend mstring operator+(const char *str, const mstring &op);
  friend mstring operator+(const mstring &op, const char *str);
  friend mstring operator*(const mstring &op, const int &n);
  friend mstring operator*(const int &n, const mstring &op);
  mstring& operator=(const mstring &other);
  bool operator<(const mstring &other) const;
  bool operator>=(const mstring &other) const;
  bool operator>(const mstring &other) const;
  bool operator<=(const mstring &other) const;
  bool operator==(const mstring &other) const;

  char &operator[](const int ind) const;
  friend std::ostream &operator<<(std::ostream &os, const mstring &str);
  friend std::istream &operator>>(std::istream &is, mstring &str);

};

mstring::mstring(const char *str = nullptr): len(str == nullptr? 0: strlen(str)), str(new char[len]) {
  memcpy(this->str, str, len);
}
mstring::mstring(const mstring &other): len(other.len), str(new char[len]) {
  memcpy(str, other.str, len);
}

size_t mstring::length() const {
  return this->len;
}

void mstring::add(const char *str) {
  mstring copy = *this;
  size_t old_len = len;
  delete [] this->str;
  len += (str == nullptr? 0: strlen(str));
  this->str = new char [len];
  memcpy(this->str, copy.str, old_len);
  memcpy(this->str+old_len, str, len-old_len);
}

void mstring::add(const char &c) {
  char *tmp = new char[2];
  tmp[0] = c;
  tmp[1] = '\0';
  this->add(tmp);
  delete [] tmp;
}

void mstring::insert(const char *str, const int offset) {
  if (offset < 0 || (size_t)offset > len) {
    throw str_exception("problem in insert incorrect parameter:", 1, offset);
  }
  if ((size_t)offset == len) {
    this->add(str);
    return;
  }
  if (offset == 0) {
    mstring tmp(str);
    tmp.add(this->str);
    *this = tmp;
    return;
  }
  // the result string = first + str + second
  char *first = new char [offset + 1];
  char *second = new char [len - offset + 1];
  memcpy(first, this->str, offset);
  first[offset] = '\0';
  second[len - offset] = '\0';
  memcpy(second, this->str + offset, len-offset);

  mstring ans(first);
  delete [] first;
  ans.add(str);
  ans.add(second);
  delete [] second;
  *this = ans;
}

void mstring::insert(const char c, const int offset) {
  if (offset < 0 || (size_t)offset > len) {
    throw str_exception("problem in insert incorrect parameter:", 1, offset);
  }
  char *tmp = new char[2];
  tmp[0] = c;
  tmp[1] = '\0';
  this->insert(tmp, offset);
  delete [] tmp;
}

void mstring::del(const int i, const int j) {
  if (i < 0 || (size_t)i >= len || i > j || j < 0 || (size_t)j >= len) {
    throw str_exception("problem in del incorrect parameter:", 2, i, j);
  }
  char *first = new char[i+1];
  char *second = new char[len - j];
  first[i] = '\0';
  second[len - j - 1] = '\0';
  memcpy(first, str, i);
  memcpy(second, str+j+1, len - j - 1);

  mstring ans(first);
  ans.add(second);
  *this = ans;
}

void mstring::del(const int i) {
  if (i < 0 || (size_t)i >= len) {
    throw str_exception("problem in del incorrect parameter:", 1, i);
  }
  this->del(i, i);
}

int mstring::search(const char *str) const {
  if (str == nullptr || strlen(str) > len) {
    return -1;
  }
  size_t substr_len = strlen(str);
  for (size_t i = 0; i < len; ++i) {
    bool is_substr = true;
    for (size_t j = 0; j < substr_len; ++j) {
      if (this->str[i+j] != str[j]) {
        is_substr = false;
        break;
      }
    }
    if (is_substr) {
      return i;
    }
  }
  return -1;
}

void mstring::replace(const char *sub_str, const char *new_str) {
  int i = this->search(sub_str);
  if (i == -1) {
    return;
  }
  this->del(i, i + strlen(sub_str)-1);
  this->insert(new_str, i);
}

void mstring::print() const {
  for (size_t i = 0; i < len; ++i)
    std::cout << this->str[i];
  std::cout << std::endl;
}


bool mstring::isempty() {
  return this->len == 0;
}
mstring::~mstring() {
  delete [] this->str;
}

mstring operator+(const mstring &op1, const mstring &op2) {
  if (op1.len == 0) {
    return  op2;
  } else if (op2.len == 0) {
    return op1;
  }
  mstring res(op1);
  //res.add(op1.str);
  res.add(op2.str);
  return res;
}

mstring operator+(const mstring &op, const char *str) {
  mstring res = op;
  res.add(str);
  return res;
}

mstring operator+(const char *str, const mstring &op) {
  mstring res(str);
  res.add(op.str);
  return res;
}

mstring operator*(const mstring &str, const int &n) {
  if (n < 0) {
    throw str_exception("problem in operator* incorrect parameter:", 1, n);
  }
  mstring res(nullptr);
  for (int i = 0; i < n; ++i) {
    res.add(str.str);
  }
  return res;
}

mstring operator*(const int &n, const mstring &str) {
  if (n < 0) {
    throw str_exception("problem in operator* incorrect parameter:", 1, n);
  }
  return str*n;
}

mstring& mstring::operator=(const mstring &other) {
  if (len != other.len) {
    delete[] str;
    len = other.len;
    str = new char[len + 1];
  }
  memcpy(str, other.str, len);
  str[len] = '\0';
  return *this;
}

bool mstring::operator<(const mstring &other) const {
  return strcmp(str, other.str) < 0;
}
bool mstring::operator>=(const mstring &other) const {
  return !(*this < other);
}
bool mstring::operator>(const mstring &other) const {
  return (other < *this);
}
bool mstring::operator<=(const mstring &other) const {
  return !(*this > other);
}
bool mstring::operator==(const mstring &other) const {
  return (*this <= other) && (other <= *this);
}
char& mstring::operator[](const int ind) const {
  if (ind < 0 || (size_t)ind >= len) {
    throw str_exception("problem in operator[] incorrect parameter:", 1, ind);
  }
  return str[ind];
}

std::ostream &operator<<(std::ostream &os, const mstring &str) {
  for (size_t i = 0; i < str.len; ++i)
    os << str[i];
  return os;
}

std::istream &operator>>(std::istream &in, mstring &str) {
  int ind = 0;
  int buf_size = buff;
  char *buf = new char[buff];
  while (!in.eof()) {
    in.get(buf[ind]);
    if (buf[ind] == '\n') {
      break;
    }
    ind++;
    if (ind == buf_size) {
      buf_size += buff;
      char *buf_cpy = new char [buf_size];
      memcpy(buf_cpy, buf, ind);
      delete [] buf;
      buf = buf_cpy;
    }
  }
  buf[ind] = '\0';
  mstring tmp(buf);
  delete [] buf;
  str = tmp;
  return in;
}



int main() {
  try {
    error();
  }
  catch(const str_exception &e) {
    e.what();
  }
  catch(const std::exception &ex) {
    std::cerr << "Exception: " << ex.what() << std::endl;
  }
  return 0;
}



/*
using namespace  std;
int main()
{
  mstring u("Hello"), v("world!"), w(v), z;
  char q = 'c';
  cout << "u+v = " << u+" "+ v << endl;
  if (u == w)
    w = 2*u + w;
  else
    w = u + v*2;
  cout << "w = " << w << endl;
  w[10] = '?';
  cout << "w = " << w << endl;
  cin >> z;
  cout << "z = " << z << endl;
  z = z * 0;
  mstring p(nullptr);
  p.add(q);
  cout << "z = " << p << " len = " << p.length() << endl;
  return 0;
}
*/
/*
int main() {
  mstring a("aac");
  mstring b("aaa");
  std::cout << a[2] << std::endl;
  std::cout << a << " " << b <<std::endl;
  std::cin >> a >> b;
  std::cout << a * 3 + b << std::endl;
}
*/
/*
int main() {
  mstring a("DADASDA");
  std::cout << a.length() << std::endl;
  mstring b(a);
  b.add("!!!");
  b.print();
  b.insert(">>", 1);
  b.print();
  b.del(9);
  b.add(nullptr);
  b.print();
  std::cout << b.length() << std::endl;
  b.del(0);
  b.print();
  b.replace("A", "??");
  b.print();
  //std::cout << b.search("ASDASDADASDASDADASDADADAD") << std::endl;
  a.add("!");
  a.add("!");
  a.insert("bab", 1);
  a.add('d');
  a.insert('?', 0);
  a.print();
  std::cout << a.length() << std::endl;
  return 0;
}
*/