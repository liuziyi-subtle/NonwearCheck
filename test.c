#include <stdio.h>
int Add(int x, int y) { return x + y; }

typedef int (*func_t)(int, int);

int Calculate(int x, int y, func_t operation) { return operation(x, y); }

int main() {
  Calculate(1, 2, Add);

  int a = b = 1;
  return 0;
}