#include <stdio.h>
#include <stdlib.h>
#define DICT_SIZE 256
#define BUFF_SIZE 4096

typedef struct HTreeNode HTreeNode;
struct HTreeNode {
  char symbol;
  unsigned freq;
  HTreeNode *left, *right;
};

typedef struct MinHeap MinHeap;
struct MinHeap {
  unsigned size;
  unsigned capacity;
  HTreeNode **array;
};

void swap_nodes(HTreeNode **a, HTreeNode **b) {
  HTreeNode *t = *a;

  *a = *b;
  *b = t;
}

HTreeNode *create_new_node(char symbol, unsigned freq) {
  HTreeNode *temp = (HTreeNode *)malloc(sizeof(HTreeNode));
  if (temp == NULL) {
    exit(1);
  }

  temp->left = temp->right = NULL;
  temp->symbol = symbol;
  temp->freq = freq;

  return temp;
}

MinHeap *create_min_heap(unsigned capacity) {
  MinHeap *minHeap = (MinHeap *)malloc(sizeof(MinHeap));

  minHeap->size = 0;
  minHeap->capacity = capacity;
  minHeap->array = (HTreeNode **)malloc(capacity * sizeof(HTreeNode *));

  return minHeap;
}

MinHeap *insert_node(MinHeap *heap, int element) {
  if (heap->size == heap->capacity) {
    fprintf(stderr, "Cannot insert %d. Heap is full\n", element);
    exit(1);
  }

  heap->size++;
  heap->array[heap->size - 1] = element;

  int curr = heap->size - 1;
  while (curr > 0 && heap->array[parent(curr)] > heap->array[curr]) {
    int temp = heap->array[parent(curr)];
    heap->array[parent(curr)] = heap->array[curr];
    heap->array[curr] = temp;
    curr = parent(curr);
  }
  return heap;
}

int main() {
  FILE *in = NULL;
  unsigned int dictionary[DICT_SIZE] = {0};

  in = fopen("input.txt", "r");
  if (in == NULL) {
    exit(1);
  }

  char buffer[BUFF_SIZE];
  int chars_read;
  while ((chars_read = fread(buffer, sizeof(char), BUFF_SIZE, in)) > 0) {
    for (int i = 0; i < chars_read; ++i) {
      dictionary[(unsigned char)buffer[i]]++;
    }
  }
  fclose(in);

  FILE *out = NULL;
  out = fopen("output.txt", "w");
  if (out == NULL) {
    exit(1);
  }

  for (int i = 0; i < DICT_SIZE; i++) {
    if (dictionary[i] != 0) {
      fprintf(out, "%d : %d\n", i, dictionary[i]);
    }
  }
  fclose(out);
}
