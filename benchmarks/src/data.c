#include "benchmarks/data.h"


void data_constant_init (float * data, const unsigned int count, float value)
{
  int i;
  for (i = 0; i < count; ++i) { data[i] = value; } 
}


void data_copy (float * dest, float * src, const unsigned int count)
{
  int i;
  for (i = 0; i < count; ++i) { dest[i] = src[i]; } 
}
