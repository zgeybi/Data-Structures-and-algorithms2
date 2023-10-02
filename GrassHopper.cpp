//
// Created by tim on 02.10.23.
//

#include<cstdio>

const int N = 1000003;

unsigned long long MultiplyDifferentDimensions(unsigned long long arr[5][5], int arr2[5]) {
  unsigned long long res[5] = {0, 0, 0, 0, 0};
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      res[i] += (arr[i][j] * arr2[j]) % N;
    }
  }
  return res[0] % N;
}

void Multiply(unsigned long long arr[5][5], unsigned long long arr2[5][5]) {
  unsigned long long res[5][5] = {0};
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      for (int k = 0; k < 5; k++) {
        res[i][j] += (arr[i][k] * arr2[k][j]) % N;
      }
    }
  }
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      arr[i][j] = res[i][j];
    }
  }
}

void Pow(unsigned long long arr[5][5], unsigned long long n) {
  if (n == 1 || n == 0) {
    return;
  }
  unsigned long long arr2[5][5] = {{1, 1, 1, 1, 1},
                                   {1, 0, 0, 0, 0},
                                   {0, 1, 0, 0, 0},
                                   {0, 0, 1, 0, 0},
                                   {0, 0, 0, 1, 0}};
  Pow(arr, n / 2);
  Multiply(arr, arr);
  if (n & 1) {
    Multiply(arr, arr2);
  }
}

unsigned long long Step(unsigned long long n) {
  if (n == 0) {
    return 0;
  }
  if (n == 1 || n == 2) {
    return 1;
  } else if (n == 3){
    return 2;
  } else if (n == 4){
    return 4;
  } else if (n == 5){
    return 8;
  }
  unsigned long long arr[5][5] = {{1, 1, 1, 1, 1},
                                  {1, 0, 0, 0, 0},
                                  {0, 1, 0, 0, 0},
                                  {0, 0, 1, 0, 0},
                                  {0, 0, 0, 1, 0}};

  int base[5] = {8, 4, 2, 1, 1};
  Pow(arr, n - 5);
  unsigned long long res = MultiplyDifferentDimensions(arr, base);
  return res;
}
int main(){
  unsigned long long n;
  scanf("%llu", &n);
  printf("%llu", Step(n));
  return 0;
}
