#include <stdio.h>
#include <stdlib.h>

#include "benchmarks/engine_cl.h"
#include "benchmarks/timer.h"
#include "benchmarks/sgemm.h"


void test_clblast (sgemm_data_cpu * data_cpu)
{
  devices_cl * nvidia = (devices_cl*)malloc(sizeof(devices_cl));
  devices_cl_init (nvidia);
  
  engine_cl * nvidia_engine = (engine_cl*)malloc(sizeof(engine_cl));
  engine_cl_init (nvidia_engine, nvidia);
  
  // clblast
  sgemm_data_cl * data_cl = (sgemm_data_cl*)malloc(sizeof(sgemm_data_cl));
  sgemm_clblast_init (nvidia_engine, data_cl, data_cpu);
  double tic = wtime();
  sgemm_clblast_compute (nvidia_engine, data_cl, data_cpu);
  double toc = wtime();
  printf ("(sgemm)(clblast) time collapsed: %f\n", toc - tic);

  // clean up
  sgemm_data_cl_del (data_cl);
  engine_cl_del (nvidia_engine);
  devices_cl_del (nvidia);
}


int main(void) {
  const float alpha = 0.7f;
  const float beta = 1.0f;
  const size_t m = 128;
  const size_t n = 64;
  const size_t k = 512;
  const size_t lda = k;
  const size_t ldb = n;
  const size_t ldc = n;
  sgemm_data_cpu * data_cpu = (sgemm_data_cpu*)malloc(sizeof(sgemm_data_cpu));
  sgemm_data_cpu_init (data_cpu, alpha, beta, m, n, k, lda, ldb, ldc);

  test_clblast (data_cpu);
  
  sgemm_data_cpu_del (data_cpu);

  return 0;
}

