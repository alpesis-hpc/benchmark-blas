#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef __APPLE__
  #include <OpenCL/cl.h>
#else
  #include <CL/cl.h>
#endif

#define CL_USE_DEPRECATED_OPENCL_1_2_APIS // to disable deprecation warnings

#include <clblast_c.h>

#include "benchmarks/engine_cl.h"
#include "benchmarks/sgemm.h"


/* --------------------------------------------------------------------------------------------- */
// sgemm_data

void sgemm_data_cpu_init (sgemm_data_cpu * data,
                          const float alpha,
                          const float beta,
                          const size_t m,
                          const size_t n,
                          const size_t k,
                          const size_t lda,
                          const size_t ldb,
                          const size_t ldc)
{
  data->alpha = alpha;
  data->beta = beta;
  data->m = m;
  data->n = n;
  data->k = k;
  data->lda = lda;
  data->ldb = ldb;
  data->ldc = ldc;
  data->host_a = (float*)malloc(sizeof(float)*m*k);
  data->host_b = (float*)malloc(sizeof(float)*n*k);
  data->host_c = (float*)malloc(sizeof(float)*m*n);

  size_t i;
  for (i = 0; i < m*k; ++i) { data->host_a[i] = (float)rand() / (float)RAND_MAX; }; 
  for (i = 0; i < n*k; ++i) { data->host_b[i] = (float)rand() / (float)RAND_MAX; }; 
  for (i = 0; i < m*n; ++i) { data->host_c[i] = 0.0f; }; 
}


void sgemm_data_cpu_del (sgemm_data_cpu * data_cpu)
{
  free (data_cpu->host_a);
  free (data_cpu->host_b);
  free (data_cpu->host_c);
  free (data_cpu);
}


/* --------------------------------------------------------------------------------------------- */
// clblast

void sgemm_clblast_init (engine_cl * t, sgemm_data_cl * data_cl, sgemm_data_cpu * data_cpu)
{
  data_cl->device_a = clCreateBuffer(t->context, 
                                     CL_MEM_READ_WRITE, 
                                     data_cpu->m*data_cpu->k*sizeof(float), 
                                     NULL, 
                                     NULL);

  data_cl->device_b = clCreateBuffer(t->context, 
                                     CL_MEM_READ_WRITE, 
                                     data_cpu->n*data_cpu->k*sizeof(float), 
                                     NULL, 
                                     NULL);

  data_cl->device_c = clCreateBuffer(t->context, 
                                     CL_MEM_READ_WRITE, 
                                     data_cpu->m*data_cpu->n*sizeof(float), 
                                     NULL, 
                                     NULL);

  clEnqueueWriteBuffer(t->queue, 
                       data_cl->device_a, 
                       CL_TRUE, 
                       0, 
                       data_cpu->m*data_cpu->k*sizeof(float), 
                       data_cpu->host_a, 
                       0, 
                       NULL, 
                       NULL);

  clEnqueueWriteBuffer(t->queue, 
                       data_cl->device_b, 
                       CL_TRUE, 
                       0, 
                       data_cpu->n*data_cpu->k*sizeof(float), 
                       data_cpu->host_b, 
                       0, 
                       NULL, 
                       NULL);

  clEnqueueWriteBuffer(t->queue, 
                       data_cl->device_c, 
                       CL_TRUE, 
                       0, 
                       data_cpu->m*data_cpu->n*sizeof(float), 
                       data_cpu->host_c, 
                       0, 
                       NULL, 
                       NULL);
}


void sgemm_clblast_compute (engine_cl * t, sgemm_data_cl * data_cl, sgemm_data_cpu * data_cpu)
{

  // Call the SGEMM routine.
  CLBlastStatusCode status = CLBlastSgemm(CLBlastLayoutRowMajor,
                                          CLBlastTransposeNo, CLBlastTransposeNo,
                                          data_cpu->m, data_cpu->n, data_cpu->k,
                                          data_cpu->alpha,
                                          data_cl->device_a, 0, data_cpu->lda,
                                          data_cl->device_b, 0, data_cpu->ldb,
                                          data_cpu->beta,
                                          data_cl->device_c, 0, data_cpu->ldc,
                                          &t->queue, &t->event);

  // Wait for completion
  if (status == CLBlastSuccess) {
    clWaitForEvents(1, &t->event);
    clReleaseEvent(t->event);
  }

  // Example completed. See "clblast_c.h" for status codes (0 -> success).
  printf("Completed SGEMM with status %d\n", status);
}


void sgemm_data_cl_del (sgemm_data_cl * data_cl)
{
  clReleaseMemObject (data_cl->device_a);
  clReleaseMemObject (data_cl->device_b);
  clReleaseMemObject (data_cl->device_c);

  free (data_cl);
}
