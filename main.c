#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// Knuth–Morris–Pratt algorithm
// Taken from:
// https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm#.22Partial_match.22_table_.28also_known_as_.22failure_function.22.29
// https://www.youtube.com/watch?v=5i7oKodCRJo
// https://www.youtube.com/watch?v=2ogqPWJSftE

int kmp(char pattern[], char string[], const int *prefix_table) {
  int n = strlen(string);
  int m = strlen(pattern);

  int i = 0;

  int j;

  int r = -1;
  for(j = 1; j < n; j++) {
    while (i > 0 && pattern[i+1] != string[j]) {
      i = prefix_table[i];
    }
    if(pattern[i+1] == string[j]) {
      i += 1;
    }
    if (i == m - 1) {
      r = j - m - 1;
      break;
    };
  }
  return r;
}

int *kmp_prefix(char pattern[]) {
  int patternLength = strlen(pattern);
  int *prefix = malloc(sizeof(int)*patternLength);
  prefix[0] = 0;
  int a = 0;
  int b;
  for(b = 1; b < patternLength;b++) {
    while(a > 0 && pattern[a] != pattern[b]) {
      a = prefix[a - 1];
    };
    if (pattern[a] == pattern[b]) {
      a = a + 1;
    }
    prefix[b] = a;
  }
  return prefix;
}

int main() {
  char pattern[255], string[255];

  scanf("%s", pattern);
  scanf("%s", string);

  int *prefix_table = kmp_prefix(pattern);

  if (kmp(pattern, string, prefix_table) != -1) {
    printf("match!");
  } else {
    printf("doesnt match!");
  }
}
