#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp(const void *a, const void *b) { return *(int *)a - *(int *)b; }

bool isNStraightHand(int *hand, int handSize, int groupSize) {
  if (handSize % groupSize)
    return false;
  qsort(hand, handSize, sizeof(int), cmp);

  int prev = hand[0];
  hand[0] = -1;
  int firstSkipped = -1;
  int count = 1;
  for (int i = 1; i < handSize; i++) {
    if (hand[i] == -1) continue;
    if (count == groupSize) {
      if (firstSkipped != -1)
        i = firstSkipped;
      count = 0;
      firstSkipped = -1;
    }
    if (count != 0) {
      if (hand[i] == prev) {
        if (firstSkipped == -1)
          firstSkipped = i;
        continue;
      }
      if (hand[i] != prev + 1) {
        return false;
      }
    }
    prev = hand[i];
    hand[i] = -1;
    count++;
  }
  return firstSkipped == -1;
}

int main() {
  printf("123623478@3 = %d\n",
         isNStraightHand((int[]){1, 2, 3, 6, 2, 3, 4, 7, 8}, 9, 3));
  printf("1111@1 = %d\n",
         isNStraightHand((int[]){1, 1, 1, 1}, 4, 1));
  printf("1212@2 = %d\n",
         isNStraightHand((int[]){1, 2, 1, 2}, 4, 2));
  printf("112233@2 = %d\n",
         isNStraightHand((int[]){1,1,2,2,3,3}, 6, 2));
  return 0;
}
