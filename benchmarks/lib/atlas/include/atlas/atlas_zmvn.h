#ifndef ATLAS_ZMVN_L0_H
#define ATLAS_ZMVN_L0_H

#include "atlas_type.h"

#ifndef ATL_MVKERN_DEF
   #define ATL_MVKERN_DEF
   typedef void (*ATL_mvkern_t)
      (ATL_CINT, ATL_CINT, const double*, ATL_CINT, const double*, double*);

#endif
void ATL_zmvnk__900002(ATL_CINT, ATL_CINT, const double*, ATL_CINT, const double*, double*);
void ATL_zmvnk__900002_b0(ATL_CINT, ATL_CINT, const double*, ATL_CINT, const double*, double*);

static ATL_mvkern_t ATL_GetMVNKern
   (ATL_CINT M, ATL_CINT N, const void *A, ATL_CINT lda,
    ATL_mvkern_t *mvk_b0, int *DOTBASED,
    int *mu, int *nu, int *minM, int *minN, int *alignX, int *ALIGNX2A,
    int *alignY, int *FNU, ATL_INT *CacheElts) 
{
   *minM = 4;   *minN = 6;
   *mu = 4;     *nu = 6;
   *alignX = 16;  *alignY = 16;
   *ALIGNX2A = 0;
   *FNU = 1;
   *CacheElts = 7372;
   *mvk_b0 = ATL_zmvnk__900002_b0;
   *DOTBASED = 0;
   return(ATL_zmvnk__900002);
}

#define ATL_GetPartMVN(A_, lda_, mb_, nb_) { *(mb_) = 524; *(nb_) = 6; }

#endif  /* end protection around header file contents */
