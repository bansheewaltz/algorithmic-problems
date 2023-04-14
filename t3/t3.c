#include <errno.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef DEBUG
#include "print_tree.h"
#endif

#define FILE_ACCESS_MODE "r"
#define INPUT_FILE "2.txt"
#define ALPHABET_SIZE 256
#define BUFFER_SIZE 4096
#define MAX_TREE_HEIGHT 50
#define COUNTING_SORT_BASE 10

typedef unsigned char uchar;
typedef unsigned int uint;

typedef struct TreeNode TreeNode;
struct TreeNode {
  uchar symbol;
  uint freq;
  TreeNode *left, *right;
};

int GetParentIdx(int i) {
  return (i - 1) / 2;
}

int GetLChildIdx(int i) {
  return (2 * i + 1);
}

int GetRchildIdx(int i) {
  return (2 * i + 2);
}

bool NodeIsLeaf(TreeNode *node) {
  return !(node->left) && !(node->right);
}

void DestroyTree(struct TreeNode *root) {
  if (root == NULL) {
    return;
  }

  DestroyTree(root->left);
  DestroyTree(root->right);

  free(root);
  return;
}

void BuildDictionary(uint *dictionary, FILE *input) {
  uchar buffer[BUFFER_SIZE];
  int chars_read;

  while ((chars_read = fread(buffer, sizeof(uchar), BUFFER_SIZE, input)) > 0) {
    for (int i = 0; i < chars_read; ++i) {
      dictionary[buffer[i]]++;
    }
  }
}

void NullPointerGuard(void *p) {
  if (p == NULL) {
    fprintf(stderr, "Archiver error: %s\n", strerror(errno));
    exit(1);
  }
}

uint GetAlphabetSize(uint *dictionary) {
  uint alph_size = 0;

  for (int i = 0; i < ALPHABET_SIZE; ++i) {
    if (dictionary[i] != 0) {
      ++alph_size;
    }
  }

  return alph_size;
}

void BuildAlphAndFreqArrays(uint *dictionary, uchar *symbols, uint *freq) {
  uint i = 0;

  for (int j = 0; j < ALPHABET_SIZE; ++j) {
    if (dictionary[j] != 0) {
      symbols[i] = j;
      freq[i] = dictionary[j];
      ++i;
    }
  }
}

void PrintAlphFreqArraysLexicographically(uchar *symbols, uint *freq) {
  for (int i = 0; symbols[i]; ++i) {
    printf("%d : %d\n", symbols[i], freq[i]);
  }
}

TreeNode *MakeNewNode(char symbol, uint freq) {
  TreeNode *temp = (TreeNode *)malloc(sizeof(TreeNode));
  NullPointerGuard(temp);

  temp->left = temp->right = NULL;
  temp->symbol = symbol;
  temp->freq = freq;

  return temp;
}

void PrintHCodeArray(int arr[], int n, FILE *output) {
  for (int i = 0; i < n; ++i) {
    fprintf(output, "%d", arr[i]);
  }
  fprintf(output, "\n");
}

void SearchSymbolOnTree(TreeNode *root, int arr[], int top, uint goal,
                        uint *len, FILE *out) {
  if (root->left) {
    arr[top] = 0;
    SearchSymbolOnTree(root->left, arr, top + 1, goal, len, out);
  }
  if (root->right) {
    arr[top] = 1;
    SearchSymbolOnTree(root->right, arr, top + 1, goal, len, out);
  }
  if (NodeIsLeaf(root) && root->symbol == goal) {
    fprintf(out, "%d : ", root->symbol);
    PrintHCodeArray(arr, top, out);
    *len = top;
  }
}

void PrintHCodesLexicographically(TreeNode *root, uchar alph[], uint lens[],
                                  uint size, FILE *out) {
  int arr[MAX_TREE_HEIGHT], top = 0;

  for (uint i = 0; i < size; ++i) {
    uint len = 0;
    SearchSymbolOnTree(root, arr, top, alph[i], &len, out);
    lens[i] = len;
  }
}

void PrintAdditionalInfo(uint freq[], uint len[], int size, FILE *output) {
  uint file_size = 0;
  uint code_length = 0;
  double information_capacity = 0;

  for (int i = 0; i < size; ++i) {
    file_size += freq[i];
    code_length += len[i] * freq[i];
  }
  for (int i = 0; i < size; ++i) {
    information_capacity +=
        (double)freq[i] / file_size * log2((double)file_size / freq[i]);
  }
  double redundancy =
      1.0 - (double)file_size / code_length * information_capacity;

  fprintf(output, "Information capacity = %.6f\n", information_capacity);
  fprintf(output, "Input file size = %d\n", file_size);
  fprintf(output, "Code length = %d\n", code_length);
  fprintf(output, "Redundancy = %.6f\n", redundancy);
}

int GetMax(uint array[], uint n) {
  uint max = array[0];

  for (uint i = 1; i < n; ++i) {
    if (array[i] > max) {
      max = array[i];
    }
  }

  return max;
}

void CountingSortPaired(uchar alph[], uint freq[], int size, int place) {
  int max = COUNTING_SORT_BASE - 1;

  // Initialize counting freq
  int count[COUNTING_SORT_BASE];
  for (int i = 0; i < max; ++i) {
    count[i] = 0;
  }
  // Calculate count of elements
  for (int i = 0; i < size; ++i) {
    count[(freq[i] / place) % 10]++;
  }
  // Calculate cumulative count
  for (int i = 1; i < 10; ++i) {
    count[i] += count[i - 1];
  }
  // Place the elements in sorted order
  int alph_output[size + 1];
  int freq_output[size + 1];
  for (int i = size - 1; i >= 0; i--) {
    alph_output[count[(freq[i] / place) % 10] - 1] = alph[i];
    freq_output[count[(freq[i] / place) % 10] - 1] = freq[i];
    count[(freq[i] / place) % 10]--;
  }
  // Copy the sorted elements into original freq
  for (int i = 0; i < size; ++i) {
    alph[i] = alph_output[i];
    freq[i] = freq_output[i];
  }
}

void RadixSortPaired(uchar alph[], uint freq[], int size) {
  int max = GetMax(freq, size);

  for (int place = 1; max / place > 0; place *= 10) {
    CountingSortPaired(alph, freq, size, place);
  }
}

void PrintSortedAsciiArray(uchar alph[], int alph_size) {
  for (int i = 0; i < alph_size; ++i) {
    printf("%d ", alph[i]);
  }
  putchar('\n');
}

int main() {
  FILE *input = NULL;
  uint dictionary[ALPHABET_SIZE] = {0};

  input = fopen(INPUT_FILE, FILE_ACCESS_MODE);
  NullPointerGuard(input);
  BuildDictionary(dictionary, input);
  fclose(input);

  uint alph_size = GetAlphabetSize(dictionary);
  uchar *alph = (uchar *)malloc(alph_size * sizeof(uchar));
  uint *freq = (uint *)malloc(alph_size * sizeof(uint));
  BuildAlphAndFreqArrays(dictionary, alph, freq);
#ifdef DEBUG
  PrintAlphFreqArraysLexicographically(alph, freq);
#endif
  RadixSortPaired(alph, freq, alph_size);
#ifdef DEBUG
  PrintSortedAsciiArray(alph, alph_size);
#endif

  //   FILE *output = NULL;
  //   output = fopen("output.txt", "w");
  //   NullPointerGuard(output);
  //   uint *lens = (uint *)malloc(alph_size * sizeof(uint));
  //   TreeNode *tree = HuffmanCodes(alph, freq, lens, alph_size, output);
  // #ifdef DEBUG
  //   DisplayTree(tree);
  // #endif
  //   PrintAdditionalInfo(freq, lens, alph_size, output);
  //   fclose(output);

  //   DestroyTree(tree);
  //   free(alph);
  //   free(freq);
  //   free(lens);
  return EXIT_SUCCESS;
}
