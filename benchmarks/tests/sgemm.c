#include <stdio.h>

#include "benchmarks/timer.h"
#include "benchmarks/sgemm_clblast.h"


int main(void) {

  double tic = wtime();
  sgemm_clblast();
  double toc = wtime();
  printf ("(sgemm)(clblast) time collapsed: %f\n", toc - tic);

  return 0;
}

