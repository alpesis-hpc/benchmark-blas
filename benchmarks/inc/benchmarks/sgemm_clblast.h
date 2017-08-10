#ifndef SGEMM_CLBLAST_H
#define SGEMM_CLBLAST_H

#ifdef __APPLE__
  #include <OpenCL/cl.h>
#else
  #include <CL/cl.h>
#endif


typedef struct
{
  cl_mem device_a;
  cl_mem device_b;
  cl_mem device_c;
} sgemm_data;


void sgemm_clblast_init (engine_cl * t, sgemm_data * data,
                         const size_t m,
                         const size_t n,
                         const size_t k,
                         const float * host_a,
                         const float * host_b,
                         float * host_c);

void sgemm_clblast_compute (engine_cl * t, sgemm_data * data,
                            const size_t m,
                            const size_t n,
                            const size_t k,
                            const float alpha,
                            const size_t lda,
                            const size_t ldb,
                            const float beta,
                            const size_t ldc);

void sgemm_data_del (sgemm_data * data);

#endif
