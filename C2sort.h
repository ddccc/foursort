// c:/bsd/rigel/sort/C2sort.h
// Date: Sun Aug 29 20:47:55 2021
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

// This version combines isort + dflgm + ( pivot sample + (fast loops | dflgm ) )

static const int dflgmLimit2 = 250;
static const int iLimit2 = 9;

void cut2(void **A, int lo, int hi, int (*compare)()) {}
