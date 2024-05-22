#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int is_palindrome(char* s, int begin, int end) {
  while (begin < end) {
    if (s[begin++] != s[end--]) return 0;
  }
  return 1;
}

int ctz16(unsigned int v) {
  int c = 16;
  v &= -(int)(v);
  if (v) c--;
  if (v & 0x00FF) c -= 8;
  if (v & 0x0F0F) c -= 4;
  if (v & 0x3333) c -= 2;
  if (v & 0x5555) c -= 1;
  return c;
}

#define popcount(n) __builtin_popcount(n)

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char*** partition(char* s, int* returnSize, int** returnColumnSizes) {
  *returnSize = 0;
  int maxSolutions = (1 << (strlen(s) - 1));
  *returnColumnSizes = malloc(sizeof(int *) * (maxSolutions + 1));
  char*** returns = malloc(sizeof(char**) * maxSolutions + 1);
  memset(*returnColumnSizes, 0, sizeof(int*) * (maxSolutions + 1));
  
  unsigned int max = (1 << strlen(s)) - 1;
  unsigned int start = max ^ (max >> 1);

  for (unsigned int i = start; i <= max; i++) {
    unsigned int t = i, bc = 0, failed = 0;
    while (t > 0 && !failed) {
      unsigned int a = ctz16(t);
      unsigned int pal = is_palindrome(s, bc, bc + a);
      if (!pal) { failed = 1; break; }
      t >>= a + 1;
      bc += a + 1;
    }

    if (!failed) {
  //     printf("found %d\n", i);
      int n = (*returnSize)++;
      int pop = popcount(i);
      (*returnColumnSizes)[n] = pop;
      returns[n] = malloc(pop * sizeof(char*));

      t = i, bc = 0;
      for (int m = 0; m < pop; m++) {
        unsigned int a = ctz16(t);
        returns[n][m] = malloc(sizeof(char) * (a + 2));
        strncpy(returns[n][m], s + bc, a + 1);
        returns[n][m][a + 1] = 0;
  //       printf("%s ", returns[n][m]);
        t >>= a + 1;
        bc += a + 1;
      }
  //     printf("\n");
    }
  }
  // printf("out %d\n", *returnSize);
  return returns;
}

void print(char* s) {
  printf("%s = ", s);

  int returnSize;
  int* returnColumnSizes;
  char*** partitions = partition(s, &returnSize, &returnColumnSizes);
  printf("(%d) ", returnSize);
  for (int i = 0; i < returnSize; i++) {
    printf("[");
    for (int j = 0; j < returnColumnSizes[i]; j++) {
      if (j != 0) printf(" ");
      printf("{%s}", partitions[i][j]);
      free(partitions[i][j]);
    }
    free(partitions[i]);
    printf("] ");
  }
  free(partitions);
  free(returnColumnSizes);
  printf("\n");
}

int main() {
  int returnSize;
  int* returnColumnSizes;
  print("aab");
  // partition("aaaaaaaaaaaaaaaa", &returnSize, &returnColumnSizes);
  return 0;
}
