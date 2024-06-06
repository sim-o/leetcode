#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define swap(nums, i, j) {{int t = (nums)[i]; (nums)[i] = (nums)[j]; (nums[j]) = t;}}

void reverse(int* nums, int numsSize) {
    for (int i = 0, j = numsSize - 1; i < j;) {
        swap(nums, i, j);
        i++; j--;
    }
}

void nextPermutation(int* nums, int numsSize) {
    int i = numsSize - 2;
    while (i >= 0 && nums[i + 1] <= nums[i]) i--;
    if (i >= 0) {
        int j = numsSize - 1;
        while (nums[j] <= nums[i]) j--;
        swap(nums, i, j);
    }
    reverse(nums + i + 1, numsSize - i - 1);
}

int main() {
  int x[] = {3,2,1};
  nextPermutation(x, 3);
  for (int i = 0; i < 3; i++) printf("%d, ", x[i]);
  printf("\n");
}
