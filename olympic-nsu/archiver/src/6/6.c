#include <assert.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef DEBUG
#include "print_tree.h"
#endif

// input/output specification
#define INPUT_FILE "input.bin"
#define INPUT_READ_MODE "rb"
#define OUTPUT_FILE "output.bin"
#define OUTPUT_WRITE_MODE "wb"
// memory limits
#define ALPHABET_SIZE 256
#define BUFFER_SIZE 4096
// radix sort options
#define COUNTING_SORT_BASE 10
#define REVERSE true
#define STRAIGHT false
// huffman tree implementation features
#define MAX_TREE_HEIGHT ALPHABET_SIZE
#define INTERNAL_NODE_SYMBOL 'x'
// huffman tree prefix code symbols
#define LEFT_CHILD 0
#define RIGHT_CHILD 1
// huffman tree serialization symbols
#define CHILD_NODE 0
#define LEAF_NODE 1
// bit-wise writing options
#define FLUSH_BYTE true
#define CONTINUE false
// bit-wise printing options
#define NEW_LINE true
#define SAME_LINE false

typedef unsigned char uchar;

typedef struct TreeNode TreeNode;
struct TreeNode {
  uchar symbol;
  int freq;
  TreeNode *left, *right;
};

typedef struct Queue Queue;
struct Queue {
  int front, rear;
  int capacity;
  TreeNode **array;
};

void check_null_pointer(void *p) {
  if (p == NULL) {
    perror("archiver error");
    exit(1);
  }
}

TreeNode *create_tree_node(uchar symbol, int freq) {
  TreeNode *temp = (TreeNode *)malloc(sizeof(TreeNode));
  check_null_pointer(temp);

  temp->left = temp->right = NULL;
  temp->symbol = symbol;
  temp->freq = freq;

  return temp;
}

Queue *create_queue(int capacity) {
  Queue *queue = (Queue *)malloc(sizeof(Queue));
  check_null_pointer(queue);

  queue->front = queue->rear = -1;
  queue->capacity = capacity;
  queue->array = (TreeNode **)malloc(queue->capacity * sizeof(TreeNode *));

  return queue;
}

bool is_queue_size_one(Queue *queue) {
  return queue->front == queue->rear && queue->front != -1;
}

bool is_queue_empty(Queue *queue) {
  return queue->front == -1;
}

bool is_queue_full(Queue *queue) {
  return queue->rear == queue->capacity - 1;
}

void enqueue(Queue *queue, TreeNode *item) {
  assert(!is_queue_full(queue));

  queue->array[++queue->rear] = item;
  if (queue->front == -1) {
    ++queue->front;
  }
}

TreeNode *dequeue(Queue *queue) {
  if (is_queue_empty(queue)) {
    return NULL;
  }

  TreeNode *temp = queue->array[queue->front];
  if (queue->front == queue->rear) {
    queue->front = queue->rear = -1;
  } else {
    ++queue->front;
  }

  return temp;
}

void reverse_queue(Queue *queue) {
  if (queue->front == -1) {
    return;
  }

  TreeNode *item = dequeue(queue);
  reverse_queue(queue);
  enqueue(queue, item);
}

TreeNode *get_queue_front(Queue *queue) {
  if (is_queue_empty(queue)) {
    return NULL;
  }

  return queue->array[queue->front];
}

TreeNode *find_queue_min(Queue *firstQueue, Queue *secondQueue) {
  if (is_queue_empty(firstQueue)) {
    return dequeue(secondQueue);
  }
  if (is_queue_empty(secondQueue)) {
    return dequeue(firstQueue);
  }

  if (get_queue_front(firstQueue)->freq < get_queue_front(secondQueue)->freq) {
    return dequeue(firstQueue);
  }
  if (get_queue_front(firstQueue)->freq == get_queue_front(secondQueue)->freq) {
    return dequeue(firstQueue);
  }
  return dequeue(secondQueue);
}

#ifdef DEBUG
void display_queue(Queue *queue) {
  if (queue->rear == -1) {
    puts("Queue is empty");
    return;
  }

  for (int i = queue->front; i <= queue->rear; i++) {
    printf("%d ", queue->array[i]->symbol);
  }

  printf("\n");
}
#endif

void destroy_queue(Queue *queue) {
  free(queue->array);
  free(queue);
}

TreeNode *build_huffman_tree(uchar alph[], int freq[], int alph_size) {
  if (alph_size == 1) {
    return create_tree_node(alph[0], freq[0]);
  }

  TreeNode *left, *right, *top;
  Queue *firstQueue = create_queue(alph_size);
  Queue *secondQueue = create_queue(alph_size);

  for (int i = 0; i < alph_size; ++i) {
    enqueue(firstQueue, create_tree_node(alph[i], freq[i]));
  }

#ifdef DEBUG
  puts("original queue:");
  display_queue(firstQueue);
#endif
  reverse_queue(firstQueue);
#ifdef DEBUG
  puts("reversed queue:");
  display_queue(firstQueue);
#endif

  while (!(is_queue_empty(firstQueue) && is_queue_size_one(secondQueue))) {
    right = find_queue_min(firstQueue, secondQueue);
    left = find_queue_min(firstQueue, secondQueue);

    top = create_tree_node(INTERNAL_NODE_SYMBOL, left->freq + right->freq);
    top->left = left;
    top->right = right;
    enqueue(secondQueue, top);
  }

  TreeNode *huffman_tree = dequeue(secondQueue);
  destroy_queue(firstQueue);
  destroy_queue(secondQueue);

  return huffman_tree;
}

bool is_node_leaf(TreeNode *node) {
  return !(node->left) && !(node->right);
}

void destroy_tree(struct TreeNode *root) {
  if (root == NULL) {
    return;
  }

  destroy_tree(root->left);
  destroy_tree(root->right);

  free(root);
  return;
}

void build_dictionary(int *dictionary, FILE *input) {
  uchar buffer[BUFFER_SIZE];
  int chars_read;

  while ((chars_read = fread(buffer, sizeof(uchar), BUFFER_SIZE, input)) > 0) {
    for (int i = 0; i < chars_read; ++i) {
      dictionary[buffer[i]]++;
    }
  }
}

int get_alphabet_size(int *dictionary) {
  int alph_size = 0;

  for (int i = 0; i < ALPHABET_SIZE; ++i) {
    if (dictionary[i] != 0) {
      ++alph_size;
    }
  }

  return alph_size;
}

void build_alph_and_freq_arrays(int *dictionary, uchar *symbols, int *freq) {
  for (int j = 0, i = 0; j < ALPHABET_SIZE; ++j) {
    if (dictionary[j] != 0) {
      symbols[i] = j;
      freq[i] = dictionary[j];
      dictionary[j] = i;  // now the dictionary keeps indeces of the elements
                          // in the new array
      ++i;
    }
  }
}

void print_freq_info(uchar symbols[], int freq[], int alph_size, FILE *output) {
  for (int i = 0; i < alph_size; ++i) {
    fprintf(output, "%d : %d\n", symbols[i], freq[i]);
  }
}

TreeNode *make_new_queue_node(char symbol, int freq) {
  TreeNode *temp = (TreeNode *)malloc(sizeof(TreeNode));
  check_null_pointer(temp);

  temp->left = temp->right = NULL;
  temp->symbol = symbol;
  temp->freq = freq;

  return temp;
}

void counting_sort_paired(uchar alph[], int freq[], int size, int place,
                          bool reverse) {
  assert(size > 0);
  int max_digit = COUNTING_SORT_BASE - 1;
  int count[COUNTING_SORT_BASE] = {0};
  int *freq_output = (int *)malloc(sizeof(int) * size);
  uchar *alph_output = (uchar *)malloc(sizeof(uchar) * size);

  // Calculate count of elements
  for (int i = 0; i < size; ++i) {
    count[(freq[i] / place) % 10]++;
  }
  // Calculate cumulative count
  if (reverse) {
    for (int i = max_digit; i > 0; --i) {
      count[i - 1] += count[i];
    }
  } else {
    for (int i = 1; i < max_digit + 1; ++i) {
      count[i] += count[i - 1];
    }
  }
  // Place the elements in sorted order
  for (int i = size - 1; i >= 0; --i) {
    alph_output[--count[(freq[i] / place) % 10]] = alph[i];
    freq_output[count[(freq[i] / place) % 10]] = freq[i];
  }
  // Copy the sorted elements into original freq
  for (int i = 0; i < size; ++i) {
    alph[i] = alph_output[i];
    freq[i] = freq_output[i];
  }
}

int get_max_int(int array[], int n) {
  int max = array[0];

  for (int i = 1; i < n; ++i) {
    if (array[i] > max) {
      max = array[i];
    }
  }

  return max;
}

void radix_sort_paired(uchar alph[], int freq[], int size, bool reverse) {
  int max = get_max_int(freq, size);

  for (int place = 1; max / place > 0; place *= 10) {
    counting_sort_paired(alph, freq, size, place, reverse);
  }
}

#ifdef DEBUG
void print_sorted_ascii_array(uchar alph[], int alph_size) {
  puts("sorted array of symbols:");
  for (int i = 0; i < alph_size; ++i) {
    printf("%3d ", alph[i]);
  }
  putchar('\n');
}
#endif

#ifdef DEBUG
void print_sorted_freq_array(int freq[], int alph_size) {
  for (int i = 0; i < alph_size; ++i) {
    printf("%3d ", freq[i]);
  }
  putchar('\n');
}
#endif

int *array_int_duplicate_with_shift(int src[], int len, int shift) {
  int array_size = len + shift;
  int *dst = (int *)malloc(sizeof(int) * array_size);

  for (int i = shift; i < array_size; ++i) {
    dst[i] = src[i - shift];
  }

  return dst;
}

int *array_int_duplicate(int src[], int len) {
  int *dst = (int *)malloc(sizeof(int) * len);

  for (int i = 0; i < len; ++i) {
    dst[i] = src[i];
  }

  return dst;
}

uchar *array_char_duplicate(uchar src[], int len) {
  uchar *dst = (uchar *)malloc(sizeof(uchar) * len);

  for (int i = 0; i < len; ++i) {
    dst[i] = src[i];
  }

  return dst;
}

int *copy_code_array(int src[], int code_len) {
  int *dst = array_int_duplicate_with_shift(src, code_len, 1);

  dst[0] = code_len;

  return dst;
}

void scan_codes(TreeNode *root, int code[], int depth, int *codes[],
                int dictionary[]) {
  if (root->left) {
    code[depth] = LEFT_CHILD;
    scan_codes(root->left, code, depth + 1, codes, dictionary);
  }
  if (root->right) {
    code[depth] = RIGHT_CHILD;
    scan_codes(root->right, code, depth + 1, codes, dictionary);
  }

  if (is_node_leaf(root)) {
    codes[dictionary[root->symbol]] = copy_code_array(code, depth);
  }
}

int **build_codes_array(TreeNode *tree, int dictionary[], int alph_size) {
  int **codes = (int **)malloc(alph_size * sizeof(int *));
  for (int i = 0; i < alph_size; ++i) {
    codes[i] = NULL;
  }

  int code[MAX_TREE_HEIGHT];
  int depth = 0;

  scan_codes(tree, code, depth, codes, dictionary);

  return codes;
}

int get_code_len(int *code) {
  assert(code != NULL);
  return code[0];
}

void print_code(uchar symbol, int code[], int code_len, FILE *output) {
  fprintf(output, "%d : ", symbol);
  for (int i = 1; i <= code_len; ++i) {
    fprintf(output, "%d", code[i]);
  }
  fprintf(output, "\n");
}

void print_codes_lexicographically(uchar alph[], int *codes[], int alph_size,
                                   FILE *output) {
  for (int i = 0; i < alph_size; ++i) {
    print_code(alph[i], codes[i], get_code_len(codes[i]), output);
  }
}

void print_coding_stats(int freq[], int *codes[], int size, FILE *output) {
  int file_size = 0;
  int code_length = 0;
  double information_capacity = 0;

  for (int i = 0; i < size; ++i) {
    file_size += freq[i];
    code_length += get_code_len(codes[i]) * freq[i];
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

void open_file_descriptors(FILE **input, FILE **output) {
  *input = fopen(INPUT_FILE, INPUT_READ_MODE);
  *output = fopen(OUTPUT_FILE, OUTPUT_WRITE_MODE);

  check_null_pointer(*input);
  check_null_pointer(*output);
}

void print_coding_info(TreeNode *tree, int dictionary[], uchar alph[],
                       int freq[], int alph_size, FILE *output) {
  int **codes = build_codes_array(tree, dictionary, alph_size);
  print_codes_lexicographically(alph, codes, alph_size, output);
  print_coding_stats(freq, codes, alph_size, output);

#ifdef DEBUG
  print_codes_lexicographically(alph, codes, alph_size, stdout);
#endif

  for (int i = 0; i < alph_size; ++i) {
    free(codes[i]);
  }
  free(codes);
}

void print_byte_in_binary(uchar byte, bool formatting, FILE *output) {
  for (int i = CHAR_BIT - 1; i >= 0; --i) {
    fprintf(output, "%d", (byte >> i) & 1 ? 1 : 0);
  }
  if (formatting == NEW_LINE) {
    fprintf(output, "\n");
  }
}

void print_char_in_binary(uchar symbol, bool formatting, FILE *output) {
  print_byte_in_binary(symbol, formatting, output);
}

void array_int_print(int array[], int len, FILE *output) {
  for (int i = 0; i < len; ++i) {
    fprintf(output, "%d", array[i]);
  }
}

uchar bit_to_char(int bit) {
  if (bit == 0) {
    return '0';
  }
  return '1';
}

void preorder_traversal_printing(TreeNode *root, FILE *output) {
  if (root == NULL) {
    return;
  }

  if (!is_node_leaf(root)) {
    putc(bit_to_char(CHILD_NODE), output);
    preorder_traversal_printing(root->left, output);
    preorder_traversal_printing(root->right, output);
  }
  if (is_node_leaf(root)) {
    putc(bit_to_char(LEAF_NODE), output);
    print_char_in_binary(root->symbol, SAME_LINE, output);
  }
}

void print_huffman_tree_to_text(TreeNode *tree, FILE *output) {
  if (tree == NULL) {
    return;
  }

  preorder_traversal_printing(tree, output);
#ifdef DEBUG
  fprintf(output, "\n");
#endif
}

void set_bit(uchar *byte, int bit, int position) {
  *byte |= bit << (CHAR_BIT - position);
}

void reset_byte(uchar *byte, int *bit_position) {
  *byte = 0b00000000;
  *bit_position = 1;
}

void writebit_buffered(int bit, bool flush_flag, FILE *output) {
  static int bit_position = 1;  // in byte, from left
  static uchar byte = 0b00000000;

  if (flush_flag == FLUSH_BYTE) {
    if (bit_position == 1) {
      return;
    }
    for (; bit_position < CHAR_BIT; ++bit_position) {
      set_bit(&byte, bit, bit_position);
#ifdef DEBUG
      print_byte_in_binary(byte, NEW_LINE, stdout);
      if (bit_position == 8) {
        printf("flush\n");
      }
#endif
    }
    fwrite(&byte, sizeof(uchar), 1, output);
    reset_byte(&byte, &bit_position);
  }

  if (flush_flag == CONTINUE) {
    set_bit(&byte, bit, bit_position);
#ifdef DEBUG
    print_byte_in_binary(byte, NEW_LINE, stdout);
    if (bit_position == 8) {
      printf("flush\n");
    }
#endif
    if (bit_position % CHAR_BIT == 0) {
      fwrite(&byte, sizeof(uchar), 1, output);
      reset_byte(&byte, &bit_position);
    } else {
      ++bit_position;
    }
  }
}

void serialize_char(uchar symbol, FILE *output) {
  for (int i = CHAR_BIT - 1; i >= 0; --i) {
    writebit_buffered((symbol >> i) & 1 ? 1 : 0, CONTINUE, output);
  }
}

void preorder_traversal_serialization(TreeNode *root, FILE *output) {
  if (root == NULL) {
    return;
  }

  if (!is_node_leaf(root)) {
    writebit_buffered(CHILD_NODE, CONTINUE, output);
    preorder_traversal_serialization(root->left, output);
    preorder_traversal_serialization(root->right, output);
  }
  if (is_node_leaf(root)) {
    writebit_buffered(LEAF_NODE, CONTINUE, output);
    serialize_char(root->symbol, output);
  }
}

void serialize_huffman_tree(TreeNode *tree, int alph_size, FILE *output) {
  if (tree == NULL) {
    return;
  }

  uchar alph_size_as_byte = (uchar)alph_size;
  fwrite(&alph_size_as_byte, sizeof(uchar), 1, output);
  preorder_traversal_serialization(tree, output);
  writebit_buffered(0, FLUSH_BYTE, output);
}

int main() {
  FILE *input = NULL;
  FILE *output = NULL;
  open_file_descriptors(&input, &output);
  int dictionary[ALPHABET_SIZE] = {0};
  int alph_size;
#ifdef DEBUG
  setbuf(stdout, NULL);
#endif

  build_dictionary(dictionary, input);
  alph_size = get_alphabet_size(dictionary);
  assert(alph_size > 0);
  uchar *alph = (uchar *)malloc(alph_size * sizeof(uchar));
  int *freq = (int *)malloc(alph_size * sizeof(int));
  build_alph_and_freq_arrays(dictionary, alph, freq);
#ifdef DEBUG
  print_freq_info(alph, freq, alph_size, stdout);
#endif
  uchar *alph_sorted = array_char_duplicate(alph, alph_size);
  int *freq_sorted = array_int_duplicate(freq, alph_size);
  radix_sort_paired(alph_sorted, freq_sorted, alph_size, REVERSE);
#ifdef DEBUG
  print_sorted_ascii_array(alph_sorted, alph_size);
  print_sorted_freq_array(freq_sorted, alph_size);
#endif
  TreeNode *tree = build_huffman_tree(alph_sorted, freq_sorted, alph_size);
#ifdef DEBUG
  print_coding_info(tree, dictionary, alph, freq, alph_size, stdout);
  print_huffman_tree_to_text(tree, stdout);
#endif
  serialize_huffman_tree(tree, alph_size, output);

  destroy_tree(tree);
  free(alph);
  free(freq);
  free(alph_sorted);
  free(freq_sorted);
  fclose(input);
  fclose(output);

  return EXIT_SUCCESS;
}
