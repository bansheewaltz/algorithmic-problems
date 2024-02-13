#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define COMPACT

typedef unsigned char uchar;
typedef unsigned int uint;

typedef struct TreeNode TreeNode;
struct TreeNode {
  uchar symbol;
  uint freq;
  TreeNode *left, *right;
};

int _DisplayTree(TreeNode *tree, int is_left, int offset, int depth,
                 char s[20][2000]) {
  char b[20];
  int width = 5;

  if (!tree)
    return 0;

  sprintf(b, "(%03d)", tree->symbol);

  int left = _DisplayTree(tree->left, 1, offset, depth + 1, s);
  int right = _DisplayTree(tree->right, 0, offset + left + width, depth + 1, s);

#ifdef COMPACT
  for (int i = 0; i < width; i++) s[depth][offset + left + i] = b[i];

  if (depth && is_left) {
    for (int i = 0; i < width + right; i++)
      s[depth - 1][offset + left + width / 2 + i] = '-';

    s[depth - 1][offset + left + width / 2] = '.';

  } else if (depth && !is_left) {
    for (int i = 0; i < left + width; i++)
      s[depth - 1][offset - width / 2 + i] = '-';

    s[depth - 1][offset + left + width / 2] = '.';
  }
#else
  for (int i = 0; i < width; i++) s[2 * depth][offset + left + i] = b[i];

  if (depth && is_left) {
    for (int i = 0; i < width + right; i++)
      s[2 * depth - 1][offset + left + width / 2 + i] = '-';

    s[2 * depth - 1][offset + left + width / 2] = '+';
    s[2 * depth - 1][offset + left + width + right + width / 2] = '+';

  } else if (depth && !is_left) {
    for (int i = 0; i < left + width; i++)
      s[2 * depth - 1][offset - width / 2 + i] = '-';

    s[2 * depth - 1][offset + left + width / 2] = '+';
    s[2 * depth - 1][offset - width / 2 - 1] = '+';
  }
#endif

  return left + width + right;
}

void DisplayTree(TreeNode *tree) {
  char s[20][2000];
  for (int i = 0; i < 20; i++) sprintf(s[i], "%80s", " ");

  _DisplayTree(tree, 0, 0, 0, s);

  for (int i = 0; i < 20; i++) printf("%s\n", s[i]);
}