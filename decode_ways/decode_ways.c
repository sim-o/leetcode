#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* cache;

#define UNDEFINED -1

int _numDecodings(char* s, int i) {
    if (cache[i] != UNDEFINED) return cache[i];
    if (s[i] == 0) {
       cache[i] = 1;
       return 1;
    } 
    if (s[i] == '0') {
       cache[i] = 0; 
       return 0;
    }
    char c0 = s[i], c1 = s[i + 1];
    int two = (c1 && (c0 == '2' && c1 <= '6' || c0 == '1')) ?
        _numDecodings(s, i + 2) : 0;

    cache[i] = two + _numDecodings(s, i + 1);
    return cache[i];
}

int numDecodings(char* s) {
    int len = strlen(s);
    cache = malloc((len + 1) * sizeof(int));
    for (int i = 0; i <= len; i++) cache[i] = UNDEFINED;
    int sln =  _numDecodings(s, 0);
    free(cache);
    return sln < 0 ? 0 : sln;
}

int main() {
    // printf("\n");
    // printf("12 = %d\n", numDecodings("12"));
    // printf("06 = %d\n", numDecodings("06"));
    // printf("11111111 = %d\n", numDecodings("111111111111111111111111111111"));
    printf("1201234 = %d (expect 3)\n", numDecodings("1201234"));
    return 0;
}
