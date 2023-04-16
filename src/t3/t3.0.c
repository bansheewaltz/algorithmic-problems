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
#define INPUT_FILE "3.txt"
#define ALPHABET_SIZE 256
#define BUFFER_SIZE 4096
#define MAX_TREE_HEIGHT 50

typedef unsigned char uchar;
typedef unsigned int uint;

typedef struct TreeNode TreeNode;
struct TreeNode {
  uchar symbol;
  uint freq;
  TreeNode *left, *right;
};

typedef struct MinHeap MinHeap;
struct MinHeap {
  uint size;
  uint capacity;
  TreeNode **array;
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

bool HeapSizeIsOne(MinHeap *minHeap) {
  return (minHeap->size == 1);
}

void SwapNodes(TreeNode **a, TreeNode **b) {
  TreeNode *t = *a;

  *a = *b;
  *b = t;
}

void DestroyHeap(MinHeap *minHeap) {
  free(minHeap);
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

void InsertHTreeNode(MinHeap *minHeap, TreeNode *heapNode) {
  if (minHeap->size == minHeap->capacity) {
    fprintf(stderr, "Cannot insert %c. Heap is full\n", heapNode->symbol);
    exit(1);
  }

  ++minHeap->size;
  int i = minHeap->size - 1;

  uint parent_idx = GetParentIdx(i);
  while (i && heapNode->freq < minHeap->array[parent_idx]->freq) {
    minHeap->array[i] = minHeap->array[parent_idx];
    i = parent_idx;
    parent_idx = GetParentIdx(i);
  }

  minHeap->array[i] = heapNode;
}

bool NodeIdxIsValid(MinHeap *minHeap, int idx) {
  return idx < (int)minHeap->size;
}

bool NodeFreqIsLesser(MinHeap *minHeap, int idx, int smallest) {
  return minHeap->array[idx]->freq < minHeap->array[smallest]->freq;
}

bool NodeFreqIsGreater(MinHeap *minHeap, int idx, int smallest) {
  return minHeap->array[idx]->freq > minHeap->array[smallest]->freq;
}

bool NodeFreqIsEqual(MinHeap *minHeap, int idx, int smallest) {
  return minHeap->array[idx]->freq == minHeap->array[smallest]->freq;
}

bool NodeAsciiIsGreater(MinHeap *minHeap, int idx, int smallest) {
  return minHeap->array[idx]->symbol > minHeap->array[smallest]->symbol;
}

bool NodeAsciiIsLesser(MinHeap *minHeap, int idx, int smallest) {
  return minHeap->array[idx]->symbol < minHeap->array[smallest]->symbol;
}

bool NodeIsSmaller(MinHeap *minHeap, int idx, int smallest) {
  if (!NodeIdxIsValid(minHeap, idx) ||
      NodeFreqIsGreater(minHeap, idx, smallest)) {
    return false;
  }
  if (NodeFreqIsLesser(minHeap, idx, smallest)) {
    return true;
  }
  if (NodeFreqIsEqual(minHeap, idx, smallest)) {
    return NodeAsciiIsGreater(minHeap, idx, smallest) ||
           !NodeIsLeaf(minHeap->array[smallest]);
  }
  return false;
}

void Heapify(MinHeap *minHeap, int idx) {
  int smallest = idx;
  int left = GetLChildIdx(idx);
  int right = GetRchildIdx(idx);

  if (NodeIsSmaller(minHeap, left, smallest)) {
    smallest = left;
  }

  if (NodeIsSmaller(minHeap, right, smallest)) {
    smallest = right;
  }

  if (smallest != idx) {
    SwapNodes(&minHeap->array[smallest], &minHeap->array[idx]);
    Heapify(minHeap, smallest);
  }
}

TreeNode *ExtractMinTreeNode(MinHeap *minHeap) {
  TreeNode *temp = minHeap->array[0];
  minHeap->array[0] = minHeap->array[minHeap->size - 1];

  --minHeap->size;
  Heapify(minHeap, 0);

  return temp;
}

void BuildMinHeap(MinHeap *minHeap) {
  int n = minHeap->size - 1;

  int i;
  for (i = GetParentIdx(n); i >= 0; --i) {
    Heapify(minHeap, i);
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

MinHeap *CreateMinHeap(uint capacity) {
  MinHeap *minHeap = (MinHeap *)malloc(sizeof(MinHeap));

  minHeap->size = 0;
  minHeap->capacity = capacity;
  minHeap->array = (TreeNode **)malloc(capacity * sizeof(TreeNode *));

  return minHeap;
}

MinHeap *CreateAndBuildMinHeap(uchar alph[], uint freq[], int size) {
  MinHeap *minHeap = CreateMinHeap(size);

  for (int i = 0; i < size; ++i) {
    minHeap->array[i] = MakeNewNode(alph[i], freq[i]);
  }
  minHeap->size = size;
  BuildMinHeap(minHeap);

  return minHeap;
}

TreeNode *BuildHuffmanTree(uchar alph[], uint freq[], int size) {
  TreeNode *left, *right, *top;
  MinHeap *minHeap = CreateAndBuildMinHeap(alph, freq, size);
#ifdef DEBUG
  // DisplayTree(minHeap->array, size);
#endif

  while (!HeapSizeIsOne(minHeap)) {
    right = ExtractMinTreeNode(minHeap);
    left = ExtractMinTreeNode(minHeap);

    top = MakeNewNode('$', left->freq + right->freq);
    top->left = left;
    top->right = right;
    InsertHTreeNode(minHeap, top);
  }

  TreeNode *root = ExtractMinTreeNode(minHeap);
  DestroyHeap(minHeap);

  return root;
}

void PrintArray(int arr[], int n, FILE *output) {
  int i;
  for (i = 0; i < n; ++i) {
    fprintf(output, "%d", arr[i]);
  }

  fprintf(output, "\n");
}

// void PrintHCodesTraverse(TreeNode *root, int arr[], int top) {
//   if (root->left) {
//     arr[top] = 0;
//     PrintHCodesTraverse(root->left, arr, top + 1);
//   }
//   if (root->right) {
//     arr[top] = 1;
//     PrintHCodesTraverse(root->right, arr, top + 1);
//   }
//   if (NodeIsLeaf(root)) {
//     printf("%d : ", root->symbol);
//     PrintArray(arr, top, out);
//   }
// }

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
    PrintArray(arr, top, out);
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

TreeNode *HuffmanCodes(uchar alph[], uint freq[], uint len[], int alph_size,
                       FILE *output) {
  TreeNode *root = BuildHuffmanTree(alph, freq, alph_size);

  // int arr[MAX_TREE_HEIGHT], top = 0;
  PrintHCodesLexicographically(root, alph, len, alph_size, output);

  return root;
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

  FILE *output = NULL;
  output = fopen("output.txt", "w");
  NullPointerGuard(output);
  uint *lens = (uint *)malloc(alph_size * sizeof(uint));
  TreeNode *tree = HuffmanCodes(alph, freq, lens, alph_size, output);
#ifdef DEBUG
  DisplayTree(tree);
#endif
  PrintAdditionalInfo(freq, lens, alph_size, output);
  fclose(output);

  DestroyTree(tree);
  free(alph);
  free(freq);
  free(lens);
  return EXIT_SUCCESS;
}
