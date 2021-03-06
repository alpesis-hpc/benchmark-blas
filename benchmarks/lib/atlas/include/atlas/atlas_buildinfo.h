#ifndef ATL_INSTINFO_H
   #define ATL_INSTINFO_H

#define ATL_ARCH "Corei364AVXMAC"
#define ATL_INSTFLAGS "-1 0 -a 1 -l 1"
#define ATL_F2CDEFS "-DAdd_ -DF77_INTEGER=int -DStringSunStyle"
#define ATL_ARCHDEFS "-DATL_OS_Linux -DATL_ARCH_Corei3 -DATL_CPUMHZ=3501 -DATL_AVXMAC -DATL_AVX -DATL_SSE3 -DATL_SSE2 -DATL_SSE1 -DATL_USE64BITS -DATL_GAS_x8664"
#define ATL_DKCFLAGS "-fomit-frame-pointer -mfpmath=sse -O2 -mavx2 -mfma -m64"
#define ATL_DKC "/usr/bin/gcc-4.9"
#define ATL_SKCFLAGS "-fomit-frame-pointer -mfpmath=sse -O2 -mavx2 -mfma -m64"
#define ATL_SKC "/usr/bin/gcc-4.9"
#define ATL_DMCFLAGS "-fomit-frame-pointer -mfpmath=sse -O2 -mavx2 -mfma -m64"
#define ATL_DMC "/usr/bin/gcc-4.9"
#define ATL_SMCFLAGS "-fomit-frame-pointer -mfpmath=sse -O2 -mavx2 -mfma -m64"
#define ATL_SMC "/usr/bin/gcc-4.9"
#define ATL_ICCFLAGS "-DL2SIZE=33554432 -I/home/kelly/Studio/kelly/k/blas-benchmarks/_blas/atlas/ATLAS/_build/include -I/home/kelly/Studio/kelly/k/blas-benchmarks/_blas/atlas/ATLAS/_build/..//include -I/home/kelly/Studio/kelly/k/blas-benchmarks/_blas/atlas/ATLAS/_build/..//include/contrib -DAdd_ -DF77_INTEGER=int -DStringSunStyle -DATL_OS_Linux -DATL_ARCH_Corei3 -DATL_CPUMHZ=3501 -DATL_AVXMAC -DATL_AVX -DATL_SSE3 -DATL_SSE2 -DATL_SSE1 -DATL_USE64BITS -DATL_GAS_x8664 -m64 -DATL_NCPU=12 -fomit-frame-pointer -mfpmath=sse -O2 -mavx"
#define ATL_ICC "/usr/bin/gcc-4.9"
#define ATL_F77FLAGS "-O -mavx2 -mfma -m64"
#define ATL_F77 "/usr/bin/gfortran"
#define ATL_DKCVERS "gcc-4.9 (Ubuntu 4.9.4-2ubuntu1 14.04.1) 4.9.4"
#define ATL_SKCVERS "gcc-4.9 (Ubuntu 4.9.4-2ubuntu1 14.04.1) 4.9.4"
#define ATL_DMCVERS "gcc-4.9 (Ubuntu 4.9.4-2ubuntu1 14.04.1) 4.9.4"
#define ATL_SMCVERS "gcc-4.9 (Ubuntu 4.9.4-2ubuntu1 14.04.1) 4.9.4"
#define ATL_ICCVERS "gcc-4.9 (Ubuntu 4.9.4-2ubuntu1 14.04.1) 4.9.4"
#define ATL_F77VERS "GNU Fortran (Ubuntu 4.8.5-2ubuntu1 14.04.1) 4.8.5"
#define ATL_SYSINFO "Linux establishz 4.4.0-47-generic #68 14.04.1-Ubuntu SMP Wed Oct 26 19:42:11 UTC 2016 x86_64 x86_64 x86_64 GNU/Linux"
#define ATL_DATE    "2017    08    12              16:15:37 CST"
#define ATL_UNAM    "kelly"
#define ATL_VERS    "3.10.3"

#endif
