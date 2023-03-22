#include "vector.h"
#include <iostream>

void Vector()
{
      using namespace std;
      double wd[3] = {1.5,2.3,-1.7};
      double wd2[4] = {1.1,2.3,4.5,6.7};
      Vec<double>  vd1(3, wd), vd2(4, wd2);
      vd2.get(-1);
}

int main() {
    try {
        Vector();
    }
    catch(const vector_exception &e) {
        e.what();
    }
    catch(...) {
        std::cerr << "Exception: unknown error" << std::endl;
    }
    return 0;
}