#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findPivot(int *nums, int numsSize) {
  int left = 0, right = numsSize - 1;
  while (left < right) {
    int next = (right - left) / 2 + left;
    // printf("l = %d, r = %d, next = %d\n", left, right, next);

    if (nums[next] < nums[left]) {
      right = next;
    } else {
      if (nums[next + 1] >= nums[next])
        left = next + 1;
      else
        return next + 1;
    }
  }
  if (left && nums[left] >= nums[left - 1]) return 0;
  return left;
}

int binarySearch(int* nums, int left, int right, int target) {
  while (left < right) {
    int next = (right - left) / 2 + left;
    // printf("l = %d, r = %d, next = %d\n", left, right, next);
    if (nums[next] < target) {
      if (nums[next + 1] <= target)
        left = next + 1;
      else
        return -1;
    } else if (nums[next] > target) {
      if (next && nums[next - 1] >= target) right = next - 1;
      else return -1;
    } else {
      return next;
    }
  }
  if (nums[left] == target)
    return left;
  return -1;
}

int search(int *nums, int numsSize, int target) {
  int pivot = findPivot(nums, numsSize);
  int left = 0, right = numsSize - 1;
  if (pivot && nums[0] <= target)
    right = pivot - 1;
  else
    left = pivot;
  // printf("left = %d, right = %d\n", left, right);

  return binarySearch(nums, left, right, target);
}

int main() {
  int nums[] = {4, 5, 6, 7, 0, 1, 2};
  printf("search@4 = %d\n", search(nums, 7, 0));
  printf("search@-1 = %d\n", search(nums, 7, 3));

  nums[0] = 1;
  printf("search@-1 = %d\n", search(nums, 1, 0));
  
  nums[0] = 1;
  nums[1] = 3;
  printf("search@1 = %d\n", search(nums, 2, 3));
  printf("search@-1 = %d\n", search(nums, 2, 0));
  printf("pivot@0 = %d\n", findPivot(nums, 2));
  printf("search@-1 = %d \n", search(nums, 2, 2));
}
