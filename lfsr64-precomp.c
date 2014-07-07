/*
 * Pre-compute the feedback inputs for a byte's worth of output
 */

#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>

// Stahnke's primitive 64-bit tap positions as used by the inner loop from
// http://users.ece.cmu.edu/~koopman/lfsr/index.html
#define FEEDBACK 0x800000000000000D

int main(int argc, char *argv[])
{
  uint64_t lfsr;
  int seed;

  printf("uint64_t byte_feedback[256] = {");

  for (seed = 0; seed <= 255; seed++) {
    lfsr = seed;

    lfsr = (lfsr & 1) ? (lfsr >> 1) ^ FEEDBACK : (lfsr >> 1);
    lfsr = (lfsr & 1) ? (lfsr >> 1) ^ FEEDBACK : (lfsr >> 1);
    lfsr = (lfsr & 1) ? (lfsr >> 1) ^ FEEDBACK : (lfsr >> 1);
    lfsr = (lfsr & 1) ? (lfsr >> 1) ^ FEEDBACK : (lfsr >> 1);
    lfsr = (lfsr & 1) ? (lfsr >> 1) ^ FEEDBACK : (lfsr >> 1);
    lfsr = (lfsr & 1) ? (lfsr >> 1) ^ FEEDBACK : (lfsr >> 1);
    lfsr = (lfsr & 1) ? (lfsr >> 1) ^ FEEDBACK : (lfsr >> 1);
    lfsr = (lfsr & 1) ? (lfsr >> 1) ^ FEEDBACK : (lfsr >> 1);

    if ((seed & 3) == 0) {
      printf("\n ");
    }

    printf(" 0x%.16lx,", lfsr);

  }

  printf("\n};\n");

}
