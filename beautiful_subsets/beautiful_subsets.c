#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int beautiful(int *nums, int k, int perm) {
  int curr = 0, next = 1;
  while ((1 << next) <= perm) {
    int currExists = (1 << curr) & perm;
    int nextExists = (1 << next) & perm;
    if (currExists && nextExists) {
      if (nums[curr] + k == nums[next]) {
        return 0;
      } else if (nums[curr] + k < nums[next]) {
        curr++;
      } else {
        next++;
      }
    } else {
      if (!currExists) curr++;
      if (!nextExists) next++;
    }
    if (next <= curr) next++;
  }
  return 1;
}

int cmpfunc(const void *a, const void *b) { return (*(int *)a - *(int *)b); }

int beautifulSubsets(int *nums, int numsSize, int k) {
  qsort(nums, numsSize, sizeof(int), cmpfunc);

  int count = 0;
  int max = (1 << numsSize) - 1;
  for (int i = 1; i <= max; i++) {
    if (beautiful(nums, k, i)) {
      count++;
    }
  }

  return count;
}

int main() {
  printf("[2,4,6] = %d\n", beautifulSubsets((int[]){2, 4, 6}, 3, 2));
  printf("[1] = %d\n", beautifulSubsets((int[]){1}, 1, 1));
  printf("[1,1,1,1] = %d\n", beautifulSubsets((int[]){1,1,1,1}, 4, 0));
  return 0;
}
