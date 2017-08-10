#include <stdio.h>
#include <stdlib.h>

#include "benchmarks/engine_cl.h"
#include "benchmarks/timer.h"
#include "benchmarks/sgemm_clblast.h"


int main(void) {

  devices_cl * nvidia = (devices_cl*)malloc(sizeof(devices_cl));
  devices_cl_init (nvidia);
  
  engine_cl * nvidia_engine = (engine_cl*)malloc(sizeof(engine_cl));
  engine_cl_init (nvidia_engine, nvidia);

  const size_t m = 128;
  const size_t n = 64;
  const size_t k = 512;
  const float alpha = 0.7f;
  const float beta = 1.0f;
  const size_t lda = k;
  const size_t ldb = n;
  const size_t ldc = n;

  float* host_a = (float*)malloc(sizeof(float)*m*k);
  float* host_b = (float*)malloc(sizeof(float)*n*k);
  float* host_c = (float*)malloc(sizeof(float)*m*n);
  for (size_t i=0; i<m*k; ++i) { host_a[i] = 12.193f; }
  for (size_t i=0; i<n*k; ++i) { host_b[i] = -8.199f; }
  for (size_t i=0; i<m*n; ++i) { host_c[i] = 0.0f; }

  sgemm_data * data = (sgemm_data*)malloc(sizeof(sgemm_data));
  sgemm_clblast_init (nvidia_engine, data, m, n, k, host_a, host_b, host_c);

  double tic = wtime();
  sgemm_clblast_compute (nvidia_engine, data,
                m, n, k,
                alpha,
                lda,
                ldb,
                beta,
                ldc);

  double toc = wtime();
  printf ("(sgemm)(clblast) time collapsed: %f\n", toc - tic);

  // clean up
  sgemm_data_del (data);
  engine_cl_del (nvidia_engine);
  devices_cl_del (nvidia);
  free (host_a);
  free (host_b);
  free (host_c);

  return 0;
}

