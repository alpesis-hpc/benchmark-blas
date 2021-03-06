#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cublas.h"

#define N  (512)

/* Host implementation of a simple version of sgemm */
static void simple_sgemm(int n, float alpha, const float *A, const float *B,
                         float beta, float *C)
{
    int i;
    int j;
    int k;
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            float prod = 0;
            for (k = 0; k < n; ++k) {
                prod += A[k * n + i] * B[j * n + k];
            }
            C[j * n + i] = alpha * prod + beta * C[j * n + i];
        }
    }
}

/* Host implementation of a simple version of strsm */
static void simple_strsm(int n, float alpha, const float *A, const float *B, float *B_out)
{

    int i;
    int j;
    int k;

    for (j = 0; j < n; ++j)
      for (i = 0; i < n; ++i) {
        if (alpha == 0.0f) B_out[j*n+i] = 0;
        else B_out[j*n+i] = B[j*n+i];
    }
      

      for (j = 0; j < n; ++j) {
        for (k = 0; k < n; ++k) {
	  if (B_out[j*n+k] != 0.0f) { 
             for (i = k+1; i < n; ++i) {
                B_out[j*n+i] -= A[k * n + i] * B_out[j * n + k];
            }
          }
        }
    }
}

/* Main */
int main(int argc, char** argv)
{    
    cublasStatus status;
    float* h_A;
    float* h_B;
    float* h_B_out;
    float* h_B_ref;
    float* h_C;
    float* h_C_ref;
    float* d_A = 0;
    float* d_B = 0;
    float* d_C = 0;
    float alpha = 1.0f;
    float beta = 0.0f;
    int n2 = N * N;
    int i;
    float error_norm;
    float ref_norm;
    float diff;

    /* Initialize CUBLAS */
    printf("simpleCUBLAS test running..\n");

    status = cublasInit();
    if (status != CUBLAS_STATUS_SUCCESS) {
        fprintf (stderr, "!!!! CUBLAS initialization error\n");
        return EXIT_FAILURE;
    }

    /* Allocate host memory for the matrices */
    h_A = (float*)malloc(n2 * sizeof(h_A[0]));
    if (h_A == 0) {
        fprintf (stderr, "!!!! host memory allocation error (A)\n");
        return EXIT_FAILURE;
    }
    h_B = (float*)malloc(n2 * sizeof(h_B[0]));
    if (h_B == 0) {
        fprintf (stderr, "!!!! host memory allocation error (B)\n");
        return EXIT_FAILURE;
    }
    h_B_out = (float*)malloc(n2 * sizeof(h_B_out[0]));
    if (h_B_out == 0) {
        fprintf (stderr, "!!!! host memory allocation error (B_out)\n");
        return EXIT_FAILURE;
    }
    h_C = (float*)malloc(n2 * sizeof(h_C[0]));
    if (h_C == 0) {
        fprintf (stderr, "!!!! host memory allocation error (C)\n");
        return EXIT_FAILURE;
    }

    /* Fill the matrices with test data */
    for (i = 0; i < n2; i++) {
        h_A[i] = rand() / (float)RAND_MAX; h_A[i] = 0.5 * h_A[i] - 0.25f;
        h_B[i] = rand() / (float)RAND_MAX; h_B[i] = 0.5 * h_B[i] - 0.25f;
        h_C[i] = rand() / (float)RAND_MAX;
    }

    /* Allocate device memory for the matrices */
    status = cublasAlloc(n2, sizeof(d_A[0]), (void**)&d_A);
    if (status != CUBLAS_STATUS_SUCCESS) {
        fprintf (stderr, "!!!! device memory allocation error (A)\n");
        return EXIT_FAILURE;
    }
    status = cublasAlloc(n2, sizeof(d_B[0]), (void**)&d_B);
    if (status != CUBLAS_STATUS_SUCCESS) {
        fprintf (stderr, "!!!! device memory allocation error (B)\n");
        return EXIT_FAILURE;
    }
    status = cublasAlloc(n2, sizeof(d_C[0]), (void**)&d_C);
    if (status != CUBLAS_STATUS_SUCCESS) {
        fprintf (stderr, "!!!! device memory allocation error (C)\n");
        return EXIT_FAILURE;
    }

    /* Initialize the device matrices with the host matrices */
    status = cublasSetVector(n2, sizeof(h_A[0]), h_A, 1, d_A, 1);
    if (status != CUBLAS_STATUS_SUCCESS) {
        fprintf (stderr, "!!!! device access error (write A)\n");
        return EXIT_FAILURE;
    }
    status = cublasSetVector(n2, sizeof(h_B[0]), h_B, 1, d_B, 1);
    if (status != CUBLAS_STATUS_SUCCESS) {
        fprintf (stderr, "!!!! device access error (write B)\n");
        return EXIT_FAILURE;
    }
    status = cublasSetVector(n2, sizeof(h_C[0]), h_C, 1, d_C, 1);
    if (status != CUBLAS_STATUS_SUCCESS) {
        fprintf (stderr, "!!!! device access error (write C)\n");
        return EXIT_FAILURE;
    }
    
    /* Performs operation using plain C code */
    simple_sgemm(N, alpha, h_A, h_B, beta, h_C);
    h_C_ref = h_C;

    /* Clear last error */
    cublasGetError();

    /* Performs operation using cublas */
    cublasSgemm('n', 'n', N, N, N, alpha, d_A, N, d_B, N, beta, d_C, N);
    status = cublasGetError();
    if (status != CUBLAS_STATUS_SUCCESS) {
        fprintf (stderr, "!!!! kernel execution error.\n");
        return EXIT_FAILURE;
    }
    
    /* Allocate host memory for reading back the result from device memory */
    h_C = (float*)malloc(n2 * sizeof(h_C[0]));
    if (h_C == 0) {
        fprintf (stderr, "!!!! host memory allocation error (C)\n");
        return EXIT_FAILURE;
    }

    /* Read the result back */
    status = cublasGetVector(n2, sizeof(h_C[0]), d_C, 1, h_C, 1);
    if (status != CUBLAS_STATUS_SUCCESS) {
        fprintf (stderr, "!!!! device access error (read C)\n");
        return EXIT_FAILURE;
    }

    /* Check result against reference */
    error_norm = 0;
    ref_norm = 0;
    for (i = 0; i < n2; ++i) {
        diff = h_C_ref[i] - h_C[i];
        error_norm += diff * diff;
        ref_norm += h_C_ref[i] * h_C_ref[i];
    }
    error_norm = (float)sqrt((double)error_norm);
    ref_norm = (float)sqrt((double)ref_norm);
    if (fabs(ref_norm) < 1e-7) {
        fprintf (stderr, "!!!! reference norm is 0\n");
        return EXIT_FAILURE;
    }
    printf( "SGEMM Test %s\n", (error_norm / ref_norm < 1e-6f) ? "PASSED" : "FAILED");

    simple_strsm(N, alpha, h_A, h_B, h_B_out);
    h_B_ref = h_B_out;

    cublasStrsm('l' /* left operator */, 'l' /* lower triangular */, 'N' /* not transposed */, 'u' /* unit triangular? */, N, N, alpha, d_A, N, d_B, N);
    /* Allocate host memory for reading back the result from device memory */
    h_B = (float*)malloc(n2 * sizeof(h_B[0]));
    if (h_B == 0) {
        fprintf (stderr, "!!!! host memory allocation error (B)\n");
        return EXIT_FAILURE;
    }

    /* Read the result back */
    status = cublasGetVector(n2, sizeof(h_B[0]), d_B, 1, h_B, 1);
    if (status != CUBLAS_STATUS_SUCCESS) {
        fprintf (stderr, "!!!! device access error (read B)\n");
        return EXIT_FAILURE;
    }

    /* Check result against reference */
    error_norm = 0;
    ref_norm = 0;
    for (i = 0; i < n2; i++) {
        diff = h_B_ref[i] - h_B[i];
        error_norm += diff * diff;
        ref_norm += h_B_ref[i] * h_B_ref[i];
	//	fprintf(stderr, "diff %d = %f\n", i, diff); 
    } 
    error_norm = (float)sqrt((double)error_norm);
    ref_norm = (float)sqrt((double)ref_norm);
    //	fprintf(stderr, "error_norm = %f, ref_norm = %f\n", error_norm, ref_norm); 
    if (fabs(ref_norm) < 1e-7) {
        fprintf (stderr, "!!!! reference norm is 0\n");
        return EXIT_FAILURE;
    }
   printf( "STRSM Test %s\n", (error_norm / ref_norm < 1e-4f) ? "PASSED" : "FAILED");

    /* Memory clean up */
    free(h_A);
    free(h_B);
    free(h_C);
    free(h_C_ref);
    status = cublasFree(d_A);
    if (status != CUBLAS_STATUS_SUCCESS) {
        fprintf (stderr, "!!!! memory free error (A)\n");
        return EXIT_FAILURE;
    }
    status = cublasFree(d_B);
    if (status != CUBLAS_STATUS_SUCCESS) {
        fprintf (stderr, "!!!! memory free error (B)\n");
        return EXIT_FAILURE;
    }
    status = cublasFree(d_C);
    if (status != CUBLAS_STATUS_SUCCESS) {
        fprintf (stderr, "!!!! memory free error (C)\n");
        return EXIT_FAILURE;
    }

    /* Shutdown */
    status = cublasShutdown();
    if (status != CUBLAS_STATUS_SUCCESS) {
        fprintf (stderr, "!!!! shutdown error (A)\n");
        return EXIT_FAILURE;
    }

    if (argc > 1) {
        if (!strcmp(argv[1], "-noprompt") ||
            !strcmp(argv[1], "-qatest") ) 
        {
            return EXIT_SUCCESS;
        }
    } 
    else
    {
    }

    return EXIT_SUCCESS;
}
