#include <stdio.h>

#include <cublas.h>

#include "benchmarks/engine_cu.h"


void engine_cu_init (void)
{
  cublasStatus status = cublasInit ();
  if (status != CUBLAS_STATUS_SUCCESS)
    fprintf (stderr, "(NVIDIA CUDA) cublas init error.\n");
}


void engine_cu_del (void)
{
  cublasStatus status = cublasShutdown ();
  if (status != CUBLAS_STATUS_SUCCESS)  
    fprintf (stderr, "(NVIDIA CUDA) cublas shutdown error.\n");
}
