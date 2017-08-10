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
#include "benchmarks/sgemm_clblast.h"


void sgemm_clblast_init (engine_cl * t, sgemm_data * data,
                         const size_t m,
                         const size_t n,
                         const size_t k,
                         const float * host_a,
                         const float * host_b,
                         float * host_c)
{
  data->device_a = clCreateBuffer(t->context, CL_MEM_READ_WRITE, m*k*sizeof(float), NULL, NULL);
  data->device_b = clCreateBuffer(t->context, CL_MEM_READ_WRITE, n*k*sizeof(float), NULL, NULL);
  data->device_c = clCreateBuffer(t->context, CL_MEM_READ_WRITE, m*n*sizeof(float), NULL, NULL);
  clEnqueueWriteBuffer(t->queue, data->device_a, CL_TRUE, 0, m*k*sizeof(float), host_a, 0, NULL, NULL);
  clEnqueueWriteBuffer(t->queue, data->device_b, CL_TRUE, 0, n*k*sizeof(float), host_b, 0, NULL, NULL);
  clEnqueueWriteBuffer(t->queue, data->device_c, CL_TRUE, 0, m*n*sizeof(float), host_c, 0, NULL, NULL);
}


void sgemm_clblast_compute (engine_cl * t, sgemm_data * data,
                            const size_t m,
                            const size_t n,
                            const size_t k,
                            const float alpha,
                            const size_t lda,
                            const size_t ldb,
                            const float beta,
                            const size_t ldc) 
{

  // Call the SGEMM routine.
  CLBlastStatusCode status = CLBlastSgemm(CLBlastLayoutRowMajor,
                                          CLBlastTransposeNo, CLBlastTransposeNo,
                                          m, n, k,
                                          alpha,
                                          data->device_a, 0, lda,
                                          data->device_b, 0, ldb,
                                          beta,
                                          data->device_c, 0, ldc,
                                          &t->queue, &t->event);

  // Wait for completion
  if (status == CLBlastSuccess) {
    clWaitForEvents(1, &t->event);
    clReleaseEvent(t->event);
  }

  // Example completed. See "clblast_c.h" for status codes (0 -> success).
  printf("Completed SGEMM with status %d\n", status);
}


void sgemm_data_del (sgemm_data * data)
{
  clReleaseMemObject (data->device_a);
  clReleaseMemObject (data->device_b);
  clReleaseMemObject (data->device_c);

  free (data);
}
