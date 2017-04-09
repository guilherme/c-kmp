#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// Knuth–Morris–Pratt algorithm
// Taken from:
// https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm#.22Partial_match.22_table_.28also_known_as_.22failure_function.22.29
// https://www.youtube.com/watch?v=5i7oKodCRJo
// https://www.youtube.com/watch?v=2ogqPWJSftE

int kmp(char pattern[], char string[], const int *prefix_table) {
  int string_length = strlen(string);
  int pattern_length = strlen(pattern);
  int q = 0;
  int i, r = -1;
  for(i = 0; i <= string_length; i++) {
    // if it started to match
    // and then stopped.
    // tries to jump by using the prefix table.
    while ((q > 0) && (pattern[q] != string[i])) {
      q = prefix_table[q];
    }
    // matches
    if (pattern[q] == string[i]) {
      q = q + 1;
    }
    // if all the letters of the pattern match.
    if (q == pattern_length) {
      r = q;
      break;
    }
  }
  return r;
}

int *kmp_prefix(char pattern[]) {
  int pattern_length = strlen(pattern);
  int *prefix_table = malloc(sizeof(int)*pattern_length);
  prefix_table[0] = 0;
  int q = 0; // index of last letter of current pattern substring.
  int k = 0; // max length of a substring that is both proper prefix and suffix of the pattern substring pattern[0..q];
  for(q = 1; q < pattern_length; q++) {
    // from the substring pattern[k..q] if we find a substring that does nt have the first letter equal to the last
    // it means that we dont have a proper prefix that has the proper suffix. so we backtrack the substring[k..q]
    while(k > 0 && pattern[k] != pattern[q]) {
      k = prefix_table[k-1];
    }
    // logic:
    // if the first character is equal to the last. means that we have, in the substring, at least:
    //  a proper suffix that is equal to the propper prefix.
    if(pattern[k] == pattern[q]) {
      k = k + 1;
    };
    prefix_table[q] = k;
  };
  return prefix_table;
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
