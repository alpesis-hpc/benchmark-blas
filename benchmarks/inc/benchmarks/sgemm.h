#ifndef SGEMM_CLBLAST_H
#define SGEMM_CLBLAST_H

#ifdef __APPLE__
  #include <OpenCL/cl.h>
#else
  #include <CL/cl.h>
#endif


typedef struct
{
  float alpha;
  float beta;

  unsigned int m;
  unsigned int n;
  unsigned int k;

  unsigned int lda;
  unsigned int ldb;
  unsigned int ldc;

  float * host_a;
  float * host_b;
  float * host_c;
  float * host_c_base;

} sgemm_data_cpu;


typedef struct
{
  float * device_a;
  float * device_b;
  float * device_c;
} sgemm_data_cu;


typedef struct
{
  cl_mem device_a;
  cl_mem device_b;
  cl_mem device_c;
} sgemm_data_cl;

/* --------------------------------------------------------------------------------------------- */
// sgemm_data_cpu

void sgemm_data_cpu_init (sgemm_data_cpu * data_cpu,
                          const float alpha,
                          const float beta,
                          const size_t m,
                          const size_t n,
                          const size_t k,
                          const size_t lda,
                          const size_t ldb,
                          const size_t ldc)
;
void sgemm_data_cpu_del (sgemm_data_cpu * data_cpu);

/* --------------------------------------------------------------------------------------------- */
// cublas

void sgemm_cublas_init (sgemm_data_cu * data_cu, sgemm_data_cpu * data_cpu);
void sgemm_cublas_compute (sgemm_data_cu * data_cu, sgemm_data_cpu * data_cpu);
void sgemm_data_cu_del (sgemm_data_cu * data_cu);

/* --------------------------------------------------------------------------------------------- */
// clblast

void sgemm_clblast_init (engine_cl * t, sgemm_data_cl * data_cl, sgemm_data_cpu * data_cpu);
void sgemm_clblast_compute (engine_cl * t, sgemm_data_cl * data_cl, sgemm_data_cpu * data_cpu);
void sgemm_data_cl_del (sgemm_data_cl * data_cl);

#endif
