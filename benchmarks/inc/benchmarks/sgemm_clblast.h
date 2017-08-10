#ifndef SGEMM_CLBLAST_H
#define SGEMM_CLBLAST_H

int sgemm_clblast (engine_cl * t,
                   const size_t m,
                   const size_t n,
                   const size_t k,
                   const float alpha,
                   const float * host_a, const size_t lda,
                   const float * host_b, const size_t ldb,
                   const float beta,
                   float * host_c, const size_t ldc);

#endif
