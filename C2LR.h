// c:/bsd/rigel/sort/C2LR.h
// Date: Sun Aug 29 18:54:23 2021
// (C) OntoOO/ Dennis de Champeaux

#ifndef isort
#define isort 1
#include "Isort.h"
#endif
#ifndef hsort
#define hsort 1
#include "Hsort.h"
#endif
#ifndef dsort
#define dsort 1
#include "Dsort.h"
#endif

static const int cut2LRLimit =  700; 
static const int bufSize = 200;

#define iswap(p, q, A) { void *t3t = A[p]; A[p] = A[q]; A[q] = t3t; }

void cut2lr(void **A, int lo, int hi, int (*compare)()){}
