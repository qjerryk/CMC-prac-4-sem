#include <iostream>
#include <string>
#include <string.h>

char* right(char *str, int N) {
	int len = strlen(str);
    if (len < N) {
      return str;
    }
    return str + len - N;
}
unsigned  long right(unsigned long num, int N) {
  unsigned long tmp = 1;
  for (int i = 0; i < N; i++) {
    tmp*=10;
  }
  if (tmp > num) {
    return num;
  }
  return num % tmp;
}

int main(){
	unsigned long num;
    int N;
	char str[100];
	std::cin.getline(str, 7);

	//std::cout << str << std::endl;
	if (!strcmp(str, "string")) {
		std::cin.getline(str, 101);
		//std::cout << str << std::endl;
        std::cin >> N;
        std::cout << right(str, N);
        return 0;
	}
    std::cin >> num;
    std::cin >> N;
    std::cout << right(num, N);
//	std::cin >> n;
//	std::cout << str;
	return 0;
}
