#ifndef ATLAS_ZR1_L1_H
#define ATLAS_ZR1_L1_H

#include "atlas_type.h"

typedef void (*ATL_r1kern_t)
   (ATL_CINT, ATL_CINT, const double*, const double*, double*, ATL_CINT);
void ATL_zgerk__3
   (ATL_CINT, ATL_CINT, const double*, const double*, double*, ATL_CINT);

static ATL_r1kern_t ATL_GetR1Kern
   (ATL_CINT M, ATL_CINT N, const void *A, ATL_CINT lda,
    int *mu, int *nu, int *minM, int *minN, int *alignX, int *ALIGNX2A,
    int *alignY, int *FNU, ATL_INT *CacheElts) 
{
   *minM = 0;   *minN = 0;
   *mu = 1;     *nu = 4;
   *alignX = 8;  *alignY = 8;
   *ALIGNX2A = 1;
   *FNU = 0;
   *CacheElts = 6225;
   return(ATL_zgerk__3);
}

#define ATL_GetPartR1(A_, lda_, mb_, nb_) { (mb_) = 621; (nb_) = 4; }

#endif  /* end protection around header file contents */
