#ifndef ATLAS_DMVT_L1_H
#define ATLAS_DMVT_L1_H

#include "atlas_type.h"

#ifndef ATL_MVKERN_DEF
   #define ATL_MVKERN_DEF
   typedef void (*ATL_mvkern_t)
      (ATL_CINT, ATL_CINT, const double*, ATL_CINT, const double*, double*);

#endif
void ATL_dmvtk__2(ATL_CINT, ATL_CINT, const double*, ATL_CINT, const double*, double*);
void ATL_dmvtk__2_b0(ATL_CINT, ATL_CINT, const double*, ATL_CINT, const double*, double*);
void ATL_dmvtk__900002(ATL_CINT, ATL_CINT, const double*, ATL_CINT, const double*, double*);
void ATL_dmvtk__900002_b0(ATL_CINT, ATL_CINT, const double*, ATL_CINT, const double*, double*);

static ATL_mvkern_t ATL_GetMVTKern
   (ATL_CINT M, ATL_CINT N, const void *A, ATL_CINT lda,
    ATL_mvkern_t *mvk_b0, 
    int *mu, int *nu, int *minM, int *minN, int *alignX, int *ALIGNX2A,
    int *alignY, int *FNU, ATL_INT *CacheElts) 
{
   if ((((((ATL_MulBySize(lda)) >> 4)) << 4)) == ATL_MulBySize(lda))
   {
      if (N >= 8)
      {
         *minM = 0;   *minN = 8;
         *mu = 2;     *nu = 8;
         *alignX = 8;  *alignY = 16;
         *ALIGNX2A = 1;
         *FNU = 0;
         *CacheElts = 15400;
         *mvk_b0 = ATL_dmvtk__2_b0;
         return(ATL_dmvtk__2);
      } /* end if on minimal M guard */
   } /* end if on lda multiple restriction */
   *minM = 8;   *minN = 12;
   *mu = 8;     *nu = 12;
   *alignX = 16;  *alignY = 16;
   *ALIGNX2A = 0;
   *FNU = 1;
   *CacheElts = 15400;
   *mvk_b0 = ATL_dmvtk__900002_b0;
   return(ATL_dmvtk__900002);
}

#define ATL_GetPartMVT(A_, lda_, mb_, nb_) { *(mb_) = 584; *(nb_) = 12; }

#endif  /* end protection around header file contents */
