/* { dg-do run { target powerpc*-*-* } } */
/* { dg-do run { target i?86-*-* x86_64-*-* } } */
/* { dg-options "-O2 -ftree-vectorize -fdump-tree-vect-stats -maltivec" { target powerpc*-*-* } } */
/* { dg-options "-O2 -ftree-vectorize -fdump-tree-vect-stats -msse2" { target i?86-*-* x86_64-*-* } } */

#include <stdarg.h>
#include "tree-vect.h"

#define N 32

struct t{
  int k[N];
  int l; 
};
  
struct s{
  char a;	/* aligned */
  char b[N-1];  /* unaligned (offset 1B) */
  char c[N];    /* aligned (offset NB) */
  struct t d;   /* aligned (offset 2NB) */
  struct t e;   /* unaligned (offset 2N+4N+4 B) */
};
 
int main1 ()
{  
  int i;
  struct s tmp;

  /* unaligned */
  for (i = 0; i < N/2; i++)
    {
      tmp.b[i] = 5;
    }

  /* check results:  */
  for (i = 0; i <N/2; i++)
    {
      if (tmp.b[i] != 5)
        abort ();
    }

  /* aligned */
  for (i = 0; i < N/2; i++)
    {
      tmp.c[i] = 6;
    }

  /* check results:  */
  for (i = 0; i <N/2; i++)
    {
      if (tmp.c[i] != 6)
        abort ();
    }

  /* aligned */
  for (i = 0; i < N/2; i++)
    {
      tmp.d.k[i] = 7;
    }

  /* check results:  */
  for (i = 0; i <N/2; i++)
    {
      if (tmp.d.k[i] != 7)
        abort ();
    }

  /* unaligned */
  for (i = 0; i < N/2; i++)
    {
      tmp.e.k[i] = 8;
    }

  /* check results:  */
  for (i = 0; i <N/2; i++)
    {
      if (tmp.e.k[i] != 8)
        abort ();
    }

  return 0;
}

int main (void)
{ 
  check_vect ();
  
  return main1 ();
} 

/* xfail: local arrays can't be aligned on a boundary greater than STACK_BOUNDARY */
/* { dg-final { scan-tree-dump-times "vectorized 2 loops" 1 "vect" {xfail i?86-*-* x86_64-*-*} } } */
