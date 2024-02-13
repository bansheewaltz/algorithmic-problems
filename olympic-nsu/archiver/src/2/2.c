#include <stdio.h>
#include <stdlib.h>
#define DICT_SIZE 256

int main() {
  FILE* fp = NULL;
  int dictionary[DICT_SIZE] = {0};

  fp = fopen("input.bin", "rb");
  if (fp == NULL) {
    exit(1);
  }

  int a;
  while ((a = fgetc(fp)) != EOF) {
    dictionary[(unsigned char)a]++;
  }
  fclose(fp);
  fp = NULL;

  fp = fopen("output.txt", "w");
  if (fp == NULL) {
    exit(1);
  }

  for (int i = 0; i < DICT_SIZE; i++) {
    if (dictionary[i] != 0) {
      fprintf(fp, "%d : %d\n", i, dictionary[i]);
    }
  }
  fclose(fp);
}