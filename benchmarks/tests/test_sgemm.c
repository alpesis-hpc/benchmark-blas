#include <stdio.h>
#include <stdlib.h>

#include "benchmarks/engine_cl.h"
#include "benchmarks/timer.h"
#include "benchmarks/sgemm.h"


void test_sgemm_cublas (sgemm_data_cpu * data_cpu)
{
  sgemm_data_cu * data_cu = (sgemm_data_cu*)malloc(sizeof(sgemm_data_cu));
  sgemm_cublas_init (data_cu, data_cpu);

  double tic = wtime();
  sgemm_cublas_compute (data_cu, data_cpu);
  double toc = wtime();
  printf ("(sgemm)(cublas) time collapsed: %f\n", toc - tic);

  sgemm_data_cu_del (data_cu);
}


void test_sgemm_clblast (sgemm_data_cpu * data_cpu)
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


int main(void) 
{
  // init
  const float alpha = 0.7f;
  const float beta = 1.0f;
  const unsigned int m = 128;
  const unsigned int n = 64;
  const unsigned int k = 512;
  const unsigned int lda = k;
  const unsigned int ldb = n;
  const unsigned int ldc = n;
  sgemm_data_cpu * data_cpu = (sgemm_data_cpu*)malloc(sizeof(sgemm_data_cpu));
  sgemm_data_cpu_init (data_cpu, alpha, beta, m, n, k, lda, ldb, ldc);

  // tests
  test_sgemm_cublas (data_cpu);
  test_sgemm_clblast (data_cpu);
  
  // delete
  sgemm_data_cpu_del (data_cpu);

  return 0;
}

