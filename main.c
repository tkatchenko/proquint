#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char *consonants = "bdfghjklmnprstvz";
const char *vowels = "aiou";

void int_to_proquint(unsigned int n, char *proquint) {
  proquint[0] = consonants[(n >> 12) & 0x0f];
  proquint[1] = vowels[(n >> 10) & 0x03];
  proquint[2] = consonants[(n >> 6) & 0x0f];
  proquint[3] = vowels[(n >> 4) & 0x03];
  proquint[4] = consonants[n & 0x0f];
  proquint[5] = '\0';
}

void string_to_proquint(const char *str, char *output) {
  size_t len = strlen(str);
  char proquint[6];
  unsigned int unit;
  int i, j, bitpos;

  output[0] = '\0'; // Start with an empty string
  for (i = 0; i < len; i += 2) {
    unit = 0;
    for (j = 0; j < 2; ++j) {
      bitpos = (1 - j) * 8;
      if (i + j < len) {
        unit |= (unsigned char)str[i + j] << bitpos;
      }
    }
    int_to_proquint(unit, proquint);
    strcat(output, proquint);
    if (i + 2 < len) {
      strcat(output, "-");
    }
  }
}

int main() {
  char input[1024];
  char output[2048];

  // Read from stdin
  if (fgets(input, sizeof(input), stdin) == NULL) {
    fprintf(stderr, "Error reading input\n");
    return 1;
  }

  // Remove newline character if present
  input[strcspn(input, "\n")] = 0;

  // Convert and output to stdout
  string_to_proquint(input, output);
  printf("%s\n", output);

  return 0;
}
