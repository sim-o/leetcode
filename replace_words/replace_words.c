#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int precmp(char *pre, char *str) {
  int i = 0;
  while (pre[i] && pre[i] == str[i]) i++;
  if (!pre[i])
    return 0;
  return pre[i] - str[i];
}

int find(char **dictionary, int dictionarySize, char *key) {
  int left = 0, right = dictionarySize - 1;
  int cmp = -1;
  do {
    int next = (right - left) / 2 + left;
    cmp = precmp(dictionary[next], key);
    if (cmp < 0)
      left = next + 1;
    else if (cmp > 0)
      right = next - 1;
    else {
      if (next) {
        cmp = precmp(dictionary[next - 1], key);
        if (cmp == 0) {
          right = next - 1;
          continue;
        }
      }
      return next;
    }
  } while (left < right);

  if (precmp(dictionary[left], key) == 0) return left;
  return -1;
}

int cmp(const void *av, const void *bv) {
  char* a = *(char**)av;
  char* b = *(char**)bv;
  int i = 0;
  while (a[i] && a[i] == b[i]) i++;
  return a[i] - b[i];
}

void reduceDict(char** dictionary, int* dictionarySize) {
  int skipped = 0;
  for (int i = 1; i < *dictionarySize; i++) {
    if (skipped) {
      dictionary[i - skipped] = dictionary[i];
    }
    if (precmp(dictionary[i - skipped - 1], dictionary[i]) == 0) {
      skipped++;
    }
  }
  *dictionarySize -= skipped;
}

char *replaceWords(char **dictionary, int dictionarySize, char *sentence) {
  qsort(dictionary, dictionarySize, sizeof(char *), &cmp);
  reduceDict(dictionary, &dictionarySize);
  
  int i = 0, replaceTail = 0, wordStart = 0;
  while (1) {
    // printf("%c", sentence[i]);
    char c = sentence[i];

    if (c == ' ' || c == 0) {
      sentence[i] = '\0';
      int loc = find(dictionary, dictionarySize, sentence + wordStart);
      int copylen = loc == -1 ? i - wordStart : strlen(dictionary[loc]);
      for (int i = 0; i < copylen; i++) {
        sentence[replaceTail++] = sentence[wordStart++];
      }
      sentence[replaceTail++] = c;
      wordStart = i + 1;

      if (c == 0) break;
    }
    i++;
  }
  return sentence;
}

int main() {
  setbuf(stdout, NULL);

  const int size = 7;
  char *dictionary[size] = {"cat", "rat", "hat", "spat", "rats", "abc", "aat"};
  qsort(dictionary, size, sizeof(char *), &cmp);
  for (int i = 0; i < size; i++)
    printf("%s ", dictionary[i]);
  printf("\n");

  printf("cmp %d\n", precmp("spat", "spatherly"));
  printf("spatherly=%d\n", find(dictionary, size, "spatherly"));

  char sentence[] = "rats of spatherly cat about the hatter";
  printf("%s\n", replaceWords(dictionary, size, sentence));

  char *dict2[] = {"a", "aa", "aaa", "aaaa"};
  qsort(dict2, 4, sizeof(char*), &cmp);
  for (int i = 0; i < 4; i++)
    printf("%s ", dict2[i]);
  printf("\n");
  char sentence2[] = "a aa a aaaa aaa aaa aaa aaaaaa bbb baba ababa";
  printf("cmp %d\n", precmp("a", "ababa"));
  printf("aaaa=%d\n", find(dict2, 4, (char*)"aaaa"));
  printf("ababa=%d\n", find(dict2, 4, (char*)"ababaa"));
  printf("aa=%d\n", find(dict2, 4, (char*)"aa"));
  printf("%s\n", replaceWords(dict2, 4, sentence2));
}
