#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int longestSubarray(int *nums, int numsSize) {
  if (numsSize <= 1) return 0;
  for (int c = 0; c < numsSize; c++)
    printf("%d ", nums[c]);
  printf("\n");
  
  int i, max = 0, z, lz = -1;
  for (i = 0; i < numsSize && nums[i]; i++);
  if (i == numsSize) return numsSize - 1;
  max = i;

  for (; i < numsSize; i++) {
    if (nums[i]) {
      max = i - z - 1 > max ? i - z - 1: max;
    } else {
      z = lz;
      lz = i;
    }
    printf("%d max=%d z=%d lz=%d i=%d\n", nums[i], max, z, lz, i);
  }
  return max;
}

int main() {
  int arr1[] = {0,1,1,1,0,1,1,0,1};
  printf("longest[5]=%d\n", longestSubarray(arr1, sizeof(arr1)/sizeof(arr1[0])));
  
  int arr2[] = {1,0,1};
  printf("longest[2]=%d\n", longestSubarray(arr2, sizeof(arr2)/sizeof(arr2[0])));

  int arr3[] = {1,0,0,0};
  printf("longest[1]=%d\n", longestSubarray(arr3, sizeof(arr3)/sizeof(arr3[0])));
}
