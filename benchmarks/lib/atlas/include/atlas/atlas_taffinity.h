/* Generated by /home/kelly/Studio/kelly/k/blas-benchmarks/_blas/atlas/ATLAS/_build/..//CONFIG/src/probe_aff.c */
#ifndef ATL_TAFFINITY_H
   #define ATL_TAFFINITY_H

#define _GNU_SOURCE 1 /* what manpage says you need to get CPU_SET */
#define __USE_GNU   1 /* what actually works on linuxes I've seen */
#include <sched.h>    /* must be included with above defs before pthread.h */

#define ATL_HAS_AFFINITY 1
#define ATL_PAFF_SETAFFNP 1
#define ATL_PAFF_LAUNCH 1  /* affinity can be set during thread launch */
#define ATL_AFF_NUMID 12
static int ATL_affinityIDs[12]
   = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
#define ATL_IDSTRIDE 1

#endif /* end multiple inclusion guard */