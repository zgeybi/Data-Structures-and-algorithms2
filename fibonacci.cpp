//
// Created by tim on 25.09.23.
//

#include <iostream>
#include <cstdio>

unsigned long long Mod(unsigned long long n) {
  return n % 1000003;
}

void Multiply(unsigned long long arr1[2][2], unsigned long long arr2[2][2]){
  unsigned long long a, b, c, d;
  a = arr1[0][0] * arr2[0][0] + arr1[0][1] * arr2[1][0];
  b = arr1[0][0] * arr2[0][1] + arr1[0][1] * arr2[1][1];
  c = arr1[1][0] * arr2[0][0] + arr1[1][1] * arr2[1][0];
  d = arr1[1][0] * arr2[0][1] + arr1[1][1] * arr2[1][1];

  arr1[0][0] = Mod(a);
  arr1[0][1] = Mod(b);
  arr1[1][0] = Mod(c);
  arr1[1][1] = Mod(d);
}

void Power(unsigned long long arr1[2][2], unsigned long long n) {
  if (n == 0 || n == 1) {
    return;
  }
  unsigned long long arr2[2][2] = {{1, 1}, {1, 0}};
  Power(arr1, n / 2);
  Multiply(arr1, arr1);
  if (n % 2 != 0){
    Multiply(arr1, arr2);
  }
}

unsigned long long Fib(unsigned long long n) {
  unsigned long long arr[2][2] = {{1, 1}, {1, 0}};
  if(n == 0) {
    return 0;
  } else if (n == 1 || n == 2) {
    return 1;
  }
  Power(arr, n - 1);
  return arr[0][0];
}

int main(){
  unsigned long long n;
  std::cin >> n;
  std::cout << Fib(n - 1) << '\n';
  return 0;
}
