#ifndef DMM_H
   #define DMM_H

   #define ATL_mmNOMULADD
   #define ATL_mmLAT 5
   #define ATL_mmMU  4
   #define ATL_mmNU  3
   #define ATL_mmKU  56
   #define MB 36
   #define NB 36
   #define KB 36
   #define NBNB 1296
   #define MBNB 1296
   #define MBKB 1296
   #define NBKB 1296
   #define NB2 72
   #define NBNB2 2592

   #define ATL_MulByNB(N_) ((N_) * 36)
   #define ATL_DivByNB(N_) ((N_) / 36)
   #define ATL_MulByNBNB(N_) ((N_) * 1296)

#endif
