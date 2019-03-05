/*
File: c:/bsd/rigel/sort/Licence.txt
Date: Sat Jun 09 22:22:31 2012

Copyright (c) 2012, Dennis de Champeaux.  All rights reserved.

The copyright holders hereby grant to any person obtaining a copy of
this software (the "Software") and/or its associated documentation
files (the Documentation), the irrevocable (except in the case of
breach of this license) no-cost, royalty free, rights to use the
Software for non-commercial evaluation/test purposes only, while
subject to the following conditions:

. Redistributions of the Software in source code must retain the above
copyright notice, this list of conditions and the following
disclaimers.

. Redistributions of the Software in binary form must reproduce the
above copyright notice, this list of conditions and the following
disclaimers in the documentation and/or other materials provided with
the distribution.

. Redistributions of the Documentation must retain the above copyright
notice, this list of conditions and the following disclaimers.

The name of the copyright holder, may not be used to endorse or
promote products derived from this Software or the Documentation
without specific prior written permission of the copyright holder.
 
THE SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS", WITHOUT WARRANTY
OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE CONTRIBUTORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
IN CONNECTION WITH THE SOFTWARE OR DOCUMENTATION OR THE USE OF OR
OTHER DEALINGS WITH THE SOFTWARE OR DOCUMENTATION.
*/

// File: c:/bsd/rigel/sort/UseParFourSort.c
// Date: Thu Jan 07 15:38:08 2010

/*
   This file is a test bench for excercising parallel foursort and testing 
   it against other (parallel) algorithms.
   >>Specific objects and a specific comparison function are used throughout<<.
   Feel free to change them as you see fit.
  
   The comparison function given here does NOT work for qsort, because qsort 
   thinks that entities to be sorted reside in the array, while sixsort knows
   that the array contains pointers to objects.  It >is< possible, of course,
   to construct an alternative comparison function for qsort.

   To compile:  $ gcc UseParFourSort.c ParFourSort.o
   It produces the file: a.exe (or the like)


   The main function has many alternative functions.
   Un-comment one to activate.
   Inside such a function are often other choices that can be selected.
 */


#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <math.h>

int NUMTHREADS = 2; // # threads used by parallel foursort

// Example of objects that can be used to populate an array to be sorted:
  // To obtain the int field from X: ((struct intval *) X)->val
  // To obtain the float field from X: ((struct intval *) X)->valf
  struct intval {
    int val;
    float valf;
  };

// Here an example comparison function for these objects:
// **** NOTE, again **** 
//      All the examples below use ::::
//          the intval objects, and 
//          the compareIntVal comparison function
int compareIntVal (const void *a, const void *b)
{
  struct intval *pa = (struct intval *) a;
  struct intval *pb = (struct intval *) b;
  return (pa->val - pb->val);
}

// This comparison formula is used for qsort in qsortx and
// for bentley in bentleyx 
int compareIntVal2 (const void **a, const void **b)
{
  struct intval *pa = (struct intval *) *a;
  struct intval *pb = (struct intval *) *b;
  return (pa->val - pb->val);
}

// To avoid compiler warnings::
void foursort(void **AA, int size, int (*compar )(), int numberOfThreads);
void testCut2();
void validateXYZ();
void testFourSort();
void testFourSort2();
void timeTest();
void dflgm(void **A, int N, int M, int pivotx, void (*cut)(), 
	   int depthLimit, int (*compar ) ());
void compareFoursortAgainstCut2();
void callCut2(void **AA, int siz, int (*compar ) () );
void validateFourSortBT(); // validation on the Bentley bench test against heapsort
void compareFoursortAgainstLQ(); // against Linux qsort on Linux i3, i5, ...


int main (int argc, char *argv[]) {
  printf("Running UseParFourSort ...\n");
  // Un-comment one of the following to use a specific functionality.
  // Modify the body of these functions as desired

  // To ask for the license expiration date and the host
     // foursort(0, 0, 0, 0);
  // To check that cut2 produces a sorted array
     // testCut2();
  // To check that foursort produces a sorted array
  // testFourSort();
  // Ditto but using the general function testAlgorithm
     // ... and uncomment also testFourSort2 ...
     // testFourSort2();
  // Compare the outputs of two sorting algorithms
  validateXYZ(); // must provide an other algorithm XYZ
     // ... and uncomment validateXYZ ...
  // Measure the sorting time of an algorithm
     // timeTest();
  // Compare the speed fraction of two algorithms
     // compareFoursortAgainstXYZ();
     // ... and uncomment also compareFoursortAgainstXYZ ...
  // Whatever here:::
     // compareFoursortAgainstCut2();  
     // compareFoursortAgainstLQ(); // against Linux qsort on Linux i3, i5, ...
     // validateFourSortBT(); // against heapsort on Bentley test-bench
     return 0;
} // end of main

void *myMalloc(char* location, int size) {
  void *p = malloc(size);
  if ( 0 == p ) {
    // printf("Cannot allocate memory in: %s\n", location);
    fprintf(stderr, "malloc fails for: %s\n", location);
    exit(1);
  }
  return p;
} // end myMalloc

// fillarray assigns random values to the int-field of our objects
void fillarray(void **A, int lng, int startv) {
  const int range = 1024*1024*32;
  int i;
  srand(startv);
  struct intval *pi;
  for ( i = 0; i < lng; i++) {
    pi = (struct intval *)A[i];
    pi->val = rand()%range; 
  }
} // end of fillarray

// Check that adjacent objects in an array are ordered.
// If not, it reports an error 
void check(void **A, int N, int M) {
  int i;
  void *x, *y;
  struct intval *pi;
  for (i = N + 1; i <= M; i++) {
    x = A[i-1]; y = A[i];
    if ( compareIntVal(y, x) < 0 ) {
      pi = (struct intval *) y;
      printf("%s %d %s %d %s", "Error at: ", i, 
	     " A[i]: ", pi->val, "\n");
    }
  }
} // end check

// initializing an array, sort it and check it
void testFourSort() {
  printf("Running testFourSort ...\n");
  int siz = 1024 * 1024 * 8;
  // int siz = 1024 * 1024;
  // int siz = 15;
  // create array
  struct intval *pi;
  void **A = myMalloc("testFourSort 1", sizeof(pi) * siz);
  int i;
  for (i = 0; i < siz; i++) {
    pi = myMalloc("testFourSort 2", sizeof (struct intval));
    A[i] = pi;
  };
  // fill its content
  fillarray(A, siz, 100);
  // sort it
  // int t0 = clock();
    struct timeval tim;
    gettimeofday(&tim, NULL);
    double t0=tim.tv_sec+(tim.tv_usec/1000000.0);
  int compareIntVal();
  foursort(A, siz, compareIntVal, NUMTHREADS);
  // int t1 = clock();
  gettimeofday(&tim, NULL);
  double t1=tim.tv_sec+(tim.tv_usec/1000000.0);
  // and check it
  check(A, 0, siz-1);
  // printf("Sorting size: %d time: %d\n", siz, t1-t0);
  printf("Sorting time: siz: %d duration: %.2f\n", siz, t1-t0);
} // end testFourSort()


// testAlgorithm0 is a generalization of testFoursort;
// another algorithm can be plugged in
// alg1 is a parallel algorithm
void testAlgorithm0(char* label, int siz, void (*alg1)() ) {
  printf("%s on size: %d\n", label, siz);
  // create array
  struct intval *pi;
  void **A = myMalloc("testAlgorithm0 1", sizeof(pi) * siz);
  int i;
  for (i = 0; i < siz; i++) {
    pi = myMalloc("testAlgorithm0 2", sizeof (struct intval));
    A[i] = pi;
  };
  // fill its content
  fillarray(A, siz, 100);
  // sort it
  int compareIntVal();
  (*alg1)(A, siz, compareIntVal, NUMTHREADS);
  // and check it
  check(A, 0, siz-1);
} // end testAlgorithm0

// like testAlgorithm0 but the size of array is preset inside testAlgorithm
void testAlgorithm(char* label, void (*alg1)() ) {
  // testAlgorithm0(label, 1024 * 1024, alg1);
  testAlgorithm0(label, 1024, alg1);
  // testAlgorithm0(label, 15, alg1);
} // end testAlgorithm

// Example: use of testAlgorithm
void testFourSort2() {
  void foursort();
  testAlgorithm("Running foursort ...", foursort);
} // end testFourSort2

// alg1 is a sequential algorithm
void testAlgorithm0S(char* label, int siz, void (*alg1)() ) {
  printf("%s on size: %d\n", label, siz);
  // create array
  struct intval *pi;
  void **A = myMalloc("testAlgorithm0 1", sizeof(pi) * siz);
  int i;
  for (i = 0; i < siz; i++) {
    pi = myMalloc("testAlgorithm0 2", sizeof (struct intval));
    A[i] = pi;
  };
  // fill its content
  fillarray(A, siz, 100);
  // sort it
  int compareIntVal();
  (*alg1)(A, siz, compareIntVal);
  // and check it
  check(A, 0, siz-1);
} // end testAlgorithm0S

// like testAlgorithm0 but the size of array is preset inside testAlgorithm
void testAlgorithmS(char* label, void (*alg1)() ) {
  // testAlgorithm0S(label, 1024 * 1024, alg1);
  testAlgorithm0S(label, 1024 * 1024 *2, alg1);
} // end testAlgorithmS

// Example: use of testAlgorithmS
void testCut2() {
  void callCut2();
  testAlgorithmS("Running cut2 ...", callCut2);
} // end testCut2

/*
  validateAlgorithm0 is used to check algorithm alg1 against a
  trusted algorithm alg2.
  The check consists of making sure that starting from identical
  inputs they produce identical outputs.
  alg1 is a parallel one, alg2 is sequential */
void validateAlgorithm0(char* label, int siz, void (*alg1)(), void (*alg2)() ) {
  printf("%s on size: %d\n", label, siz);
  // create the input for alg1 ...
  struct intval *pi;
  void **A = myMalloc("validateAlgorithm0 1", sizeof(pi) * siz);
  int i;
  for (i = 0; i < siz; i++) {
    pi = myMalloc("validateAlgorithm0 2", sizeof (struct intval));
    A[i] = pi;
  };
  fillarray(A, siz, 100);
  // ... sort it
  int compareIntVal();
  (*alg1)(A, siz, compareIntVal, NUMTHREADS);

  // create the input for alg2 ...
  void **B = myMalloc("validateAlgorithm0 3", sizeof(pi) * siz);
  // int i;
  // struct intval *pi;
  for (i = 0; i < siz; i++) {
    pi =  myMalloc("validateAlgorithm0 4", sizeof (struct intval));
    B[i] = pi;
  };
  fillarray(B, siz, 100);
  // ... sort it
  // int compareIntVal();
  (*alg2)(B, siz, compareIntVal);
 
  // check that the two outputs are the same
  int foundError = 0;
  for (i = 0; i < siz; i++)
    // if ( A[i] != B[i] ) {
    if ( compareIntVal(A[i], B[i]) != 0 ) {
      printf("validate error i: %d\n", i);
      foundError = 1;
    }
  if ( !foundError ) 
    printf("NO error found ...\n");
} // end validateAlgorithm0

// Like validateAlgorithm0 but with fixed array size
// alg1 is a parallel one, alg2 is sequential
void validateAlgorithm(char* label, void (*alg1)(), void (*alg2)() ) {
  validateAlgorithm0(label, 1024 * 1024 * 16, alg1, alg2);
} // end validateAlgorithm

/* Example:: replace XYZ by what you want to validate
validateXYZ() {
  void foursort(), XYZ();
  validateAlgorithm("Running validate XYZ ...",
		    foursort, XYZ);
}
*/

void validateXYZ() {
  void foursort(), callCut2();
  validateAlgorithm("Running validate foursort ...",
		    foursort, callCut2);
} // end validateXYZ

// Run an algorithm and report the time used
void timeTest() {
  double algTime, T;
  int seed;
  int seedLimit = 3;
  int z;
  // int siz = 1024 * 1024 * 16;
  int siz = 1024 * 1024 * 4;
  printf("timeTest() on size: %d \n", siz);
  // construct array
  struct intval *pi;
  void **A = myMalloc("timeTest 1", sizeof(pi) * siz);
  int i;
  for (i = 0; i < siz; i++) {
    pi = myMalloc("timeTest 2", sizeof (struct intval));
    A[i] = pi;
  };

  // warm up the process
  fillarray(A, siz, 666); 
  float sumTimes = 0;
  for (z = 0; z < 3; z++) { // repeat to check stability
    algTime = 0;
    // measure the array fill time
    // int TFill = clock();
      struct timeval tim;
      gettimeofday(&tim, NULL);
      double TFILL=tim.tv_sec+(tim.tv_usec/1000000.0);
    for (seed = 0; seed < seedLimit; seed++) 
      fillarray(A, siz, seed);
      // here alternative ways to fill the array
      // int k;
      // for ( k = 0; k < siz; k++ ) A[k] = 0;
      // for ( k = 0; k < siz; k++ ) A[k] = k%5;
      // for ( k = 0; k < siz; k++ ) A[k] = siz-k;
    // TFill = clock() - TFill;
    gettimeofday(&tim, NULL);
    TFILL=tim.tv_sec+(tim.tv_usec/1000000.0) - TFILL;
    // now we know how much time it takes to fill the array
    // measure the time to fill & sort the array
    // T = clock();
    gettimeofday(&tim, NULL);
    T=tim.tv_sec+(tim.tv_usec/1000000.0);
    for (seed = 0; seed < seedLimit; seed++) { 
      fillarray(A, siz, seed);
      // for ( k = 0; k < siz; k++ ) A[k] = 0;
      // for ( k = 0; k < siz; k++ ) A[k] = k%5;
      // for ( k = 0; k < siz; k++ ) A[k] = siz-k;
      // foursort(A, siz, compareIntVal, NUMTHREADS);
      callCut2(A, siz, compareIntVal);
    }
    // ... and subtract the fill time to obtain the sort time
    // algTime = clock() - T - TFill;
    gettimeofday(&tim, NULL);
    algTime=tim.tv_sec+(tim.tv_usec/1000000.0) - T - TFILL;
    printf("algTime: %f \n", algTime);
    sumTimes = sumTimes + algTime;
  }
  printf("%s %f %s", "sumTimes: ", sumTimes, "\n");
} // end timeTest()

// Report the speed fraction of two algorithms on a range of array sizes
// alg1 is parallel, alg2 is sequential
void compareAlgorithms0(char *label, int siz, int seedLimit, void (*alg1)(), void (*alg2)() ) {
  printf("%s on size: %d seedLimit: %d #threads: %d\n", label, siz, seedLimit, NUMTHREADS);
  double alg1Time, alg2Time, T;
  int seed;
  int z;
  int limit = 1024 * 1024 * 16 + 1;
  while (siz <= limit) {
    printf("%s %d %s %d %s", "siz: ", siz, " seedLimit: ", seedLimit, "\n");
    struct intval *pi;
    void **A = myMalloc("compareAlgorithms0 1", sizeof(pi) * siz); 
    // construct array
    int i;
    for (i = 0; i < siz; i++) {
      pi = myMalloc("compareAlgorithms0 2", sizeof (struct intval));
      A[i] = pi;
    };
    // warm up the process
    for (seed = 0; seed < seedLimit; seed++) 
      fillarray(A, siz, seed);
    for (z = 0; z < 4; z++) { // repeat to check stability
    // for (z = 0; z < 1; z++) { // repeat to check stability
      alg1Time = 0; alg2Time = 0;
      // int TFill = clock();
        struct timeval tim;
        gettimeofday(&tim, NULL);
        double TFILL=tim.tv_sec+(tim.tv_usec/1000000.0);
      for (seed = 0; seed < seedLimit; seed++) 
	fillarray(A, siz, seed);
      // TFill = clock() - TFill;
      gettimeofday(&tim, NULL);
      TFILL=tim.tv_sec+(tim.tv_usec/1000000.0) - TFILL;
      // T = clock();
      gettimeofday(&tim, NULL);
      T=tim.tv_sec+(tim.tv_usec/1000000.0);
      for (seed = 0; seed < seedLimit; seed++) { 
	fillarray(A, siz, seed);
	(*alg1)(A, siz, compareIntVal, NUMTHREADS); 
      }
      // alg1Time = clock() - T - TFill;
      gettimeofday(&tim, NULL);
      alg1Time=tim.tv_sec+(tim.tv_usec/1000000.0) - T - TFILL;
      // T = clock();
      gettimeofday(&tim, NULL);
      T=tim.tv_sec+(tim.tv_usec/1000000.0);
      for (seed = 0; seed < seedLimit; seed++) { 
	fillarray(A, siz, seed);
	(*alg2)(A, siz, compareIntVal);
      }
      // alg2Time = clock() - T - TFill;
      gettimeofday(&tim, NULL);
      alg2Time=tim.tv_sec+(tim.tv_usec/1000000.0) - T - TFILL;

      printf("%s %d %s", "siz: ", siz, " ");
      printf("%s %f %s", "alg1Time: ", alg1Time, " ");
      printf("%s %f %s", "alg2Time: ", alg2Time, " ");
      float frac = 0; float frac2 = 0;
      if ( alg1Time != 0 &&  alg2Time != 0) { 
	frac = alg2Time / ( 1.0 * alg1Time ); frac2 = 1.0/frac;
      }
      printf("%s %f %s %f %s", "frac: ", frac, "frac2: ", frac2, "\n");
    }
    // free array
    for (i = 0; i < siz; i++) {
      free(A[i]);
    };
    free(A);
    siz = siz * 2;
    seedLimit = seedLimit / 2;
  }
} // end compareAlgorithms0

// alg1 is parallel, alg2 is sequential
void compareAlgorithms(char *label, void (*alg1)(), void (*alg2)() ) {
  // compareAlgorithms0(label, 1024, 32 * 1024, alg1, alg2);
  compareAlgorithms0(label, 1024 * 1024, 32, alg1, alg2);
  // compareAlgorithms0(label, 1024 * 1024, 4, alg1, alg2);
} // end compareAlgorithms

/* Example, replace XYZ by what you want to compare against
void compareFoursortAgainstXYZ() {
  void foursort(), XYZ();
  compareAlgorithms("Compare foursort vs XYZ", foursort, XYZ);
}
*/

void compareFoursortAgainstCut2() {
  void  foursort(), callCut2();
  compareAlgorithms("Compare foursort vs cut2", foursort, callCut2);
} // end compareFoursortAgainstCut2


// Here are the global entities used throughout
// int (*compareXY)();
// void **A;

// The next lines up to the include makes the inclusion of cut2 obsolete
// const int cut2Limit = 127;
void quicksort0(void **A, int N, int M, int (*compare)());
void quicksort0c(void **A, int N, int M, int depthLimit, int (*compare)());
void iswap(int p, int q, void **A);
void heapc(void **A, int N, int M, int (*compare)());
void cut2();
// #include "C2sort.c"


// invoking 3-layered quicksort
// void cut2f();
void callCut2(void **A, int siz, 
	  int (*compar ) (const void *, const void * ) ) {
  // A = AA;
  // compareXY = compar;
  cut2(A, 0, siz-1, compar);
} // end callCut2

// Here infrastructure for the Bentley test-bench
// It has been adapted for this setting

void reverse2();
void reverse(void **A, int n) {
  reverse2(A, 0, n-1);
} // end reverse
void reverse2(void **A, int start, int end) {
  void *x;
  while ( start < end ) {
    x = A[start]; A[start++] = A[end]; A[end--] = x;
  }    
} // end reverse2
void reverseFront(void **A, int n) {
  reverse2(A, 0, n/2);
} // end reverseFront
void reverseBack(void **A, int n) {
  reverse2(A, n/2, n-1);
} // end reverseBack

// void **A;
int (*compareXY)();
void tweakSort(void **AA, int n) {
  /*
  A = AA;
  compareXY = compareIntVal;
  cut2(0, n-1);  // specific for this setting !!
  */
  callCut2(AA, n, compareIntVal);
} // end tweakSort
void dither(void **A, int n) {
  int k;
  struct intval *pi;
  for (k = 0; k < n; k++) {
    // A[k] = A[k] + (k % 5);
    pi = (struct intval *)A[k]; // specific for this setting !!
    pi->val = pi->val + (k % 5);
  }
} // end dither

void sawtooth(void **A, int n, int m, int tweak) {
  // int *A = malloc (sizeof(int) * n);
  struct intval *pi;
  int k;
  for (k = 0; k < n; k++) {
    pi = (struct intval *)A[k];
    pi->val = k % m; 
  }
  if ( tweak <= 0 ) return;
  if ( tweak == 1 ) { reverse(A, n); return; }
  if ( tweak == 2 ) { reverseFront(A, n); return; }
  if ( tweak == 3 ) { reverseBack(A, n); return; }
  if ( tweak == 4 ) { tweakSort(A, n); return; }
  dither(A, n);
} // end sawtooth

void rand2(void **A, int n, int m, int tweak, int seed) {
  srand(seed);
  int k;
  struct intval *pi;
  for (k = 0; k < n; k++) {
    // A[k] = rand() % m;
    pi = (struct intval *)A[k];
    pi->val = rand() % m;
  }
  if ( tweak <= 0 ) return;
  if ( tweak == 1 ) { reverse(A, n); return; }
  if ( tweak == 2 ) { reverseFront(A, n); return; }
  if ( tweak == 3 ) { reverseBack(A, n); return; }
  if ( tweak == 4 ) { tweakSort(A, n); return; }
  dither(A, n);
} // end rand2

void stagger(void **A, int n, int m, int tweak) {
  int k;
  struct intval *pi;
  for (k = 0; k < n; k++) {
    // A[k] = (k*m+k) % n;
    pi = (struct intval *)A[k];
    pi->val = (k*m+k) % n;
  }
  if ( tweak <= 0 ) return;
  if ( tweak == 1 ) { reverse(A, n); return; }
  if ( tweak == 2 ) { reverseFront(A, n); return; }
  if ( tweak == 3 ) { reverseBack(A, n); return; }
  if ( tweak == 4 ) { tweakSort(A, n); return; }
  dither(A, n);
} // end stagger

void plateau(void **A, int n, int m, int tweak) {
  int k;
  struct intval *pi;
  for (k = 0; k < n; k++) {
    // A[k] = ( k <= m ? k : m );
    pi = (struct intval *)A[k];
    pi->val = ( k <= m ? k : m );
  }
  if ( tweak <= 0 ) return;
  if ( tweak == 1 ) { reverse(A, n); return; }
  if ( tweak == 2 ) { reverseFront(A, n); return; }
  if ( tweak == 3 ) { reverseBack(A, n); return; }
  if ( tweak == 4 ) { tweakSort(A, n); return; }
  dither(A, n);
} // end plateau

void shuffle(void **A, int n, int m, int tweak, int seed) {
  srand(seed);
  int k, i, j;
  i = j = 0;
  struct intval *pi;
  for (k = 0; k < n; k++) {
    pi = (struct intval *)A[k];
    if ( 0 == ( rand() %m ) ) { 
      // j = j+2; A[k] = j;
      j = j+2;  pi->val = j;
    } else {
      // i = i+2; A[k] = i;
      i = i+2;  pi->val = i;
    }
  }
  if ( tweak <= 0 ) return;
  if ( tweak == 1 ) { reverse(A, n); return; }
  if ( tweak == 2 ) { reverseFront(A, n); return; }
  if ( tweak == 3 ) { reverseBack(A, n); return; }
  if ( tweak == 4 ) { tweakSort(A, n); return; }
  dither(A, n);
} // end shuffle

void slopes(void **A, int n, int m, int tweak) {
  int k, i, b, ak;
  i = k = b = 0; ak = 1;
  struct intval *pi;
  while ( k < n ) {
    if (1000000 < ak) ak = k; else
    if (ak < -1000000) ak = -k;
    // A[k] = -(ak + b); ak = A[k];
    pi = (struct intval *)A[k];
    ak = -(ak + b);
    pi->val = ak;
    k++; i++; b++;
    if ( 11 == b ) { b = 0; }
    if ( m == i ) { ak = ak*2; i = 0; }
  }
  if ( tweak <= 0 ) return;
  if ( tweak == 1 ) { reverse(A, n); return; }
  if ( tweak == 2 ) { reverseFront(A, n); return; }
  if ( tweak == 3 ) { reverseBack(A, n); return; }
  if ( tweak == 4 ) { tweakSort(A, n); return; }
  dither(A, n);
} // end slopes


void heapSort();
void callHeapSort(void **A, int size, 
	 int (*compar ) (const void *, const void * ) ) {
  heapSort(A, size, compar);
} // end callHeapSort

void validateFourSortBT() {  // validation on the Bentley bench test against heapsort
  printf("Entering validateFourSortBT Sawtooth ........\n");
  // printf("Entering validateFourSortBT Rand2 ........\n");
  // printf("Entering validateFourSortBT Plateau ........\n");
  // printf("Entering validateFourSortBT Shuffle ........\n");
  // printf("Entering validateFourSortBT Stagger ........\n");
  int sortcBTime, cut2Time, T;
  int seed =  666;
  int z;
  int siz = 1024*1024;
  // int limit = 1024 * 1024 * 16 + 1;
  // int seedLimit = 32 * 1024;
  int limit = siz + 1;
  // int seedLimit = 32;
  int seedLimit = 1;
  float frac;
  while (siz <= limit) {
    printf("%s %d %s %d %s", "siz: ", siz, " seedLimit: ", seedLimit, "\n");
    // int A[siz];
    struct intval *pi;
    void **A = myMalloc("compareAlgorithms0 1", sizeof(pi) * siz);
    void **B = myMalloc("compareAlgorithms0 3", sizeof(pi) * siz);
    // construct array
    int i;
    for (i = 0; i < siz; i++) {
      pi = myMalloc("compareAlgorithms0 2", sizeof (struct intval));
      A[i] = pi;
      pi = myMalloc("compareAlgorithms0 4", sizeof (struct intval));
      B[i] = pi;
    };
    // warm up the process
    fillarray(A, siz, seed);
    int TFill, m, tweak;
    int sortcBCnt, cut2Cnt; // , sortcBCntx, cut2Cntx;
    int sumQsortB, sumCut2; // , sumQsortBx, sumCut2x;
    // for (z = 0; z < 3; z++) { // repeat to check stability
    for (z = 0; z < 1; z++) { // repeat to check stability
      sortcBCnt = cut2Cnt = sumQsortB = sumCut2 = 0;
      // sortcBCntx = cut2Cntx = sumQsortBx = sumCut2x = 0;
      for (m = 1; m < 2 * siz; m = m * 2) {
      // m = 1024 * 1024; {
      // m = 1; {
      	for (tweak = 0; tweak <= 5; tweak++ ) {
	// tweak = 5; {
	  sortcBTime = 0; cut2Time = 0;
	  TFill = clock();
	  for (seed = 0; seed < seedLimit; seed++) 
	    sawtooth(A, siz, m, tweak);
	    // rand2(A, siz, m, tweak, seed);
	    // plateau(A, siz, m, tweak);
	    // shuffle(A, siz, m, tweak, seed);
	    // stagger(A, siz, m, tweak);
	  TFill = clock() - TFill;
	  T = clock();
	  for (seed = 0; seed < seedLimit; seed++) { 
	    sawtooth(A, siz, m, tweak);
	    // rand2(A, siz, m, tweak, seed);
	    // plateau(A, siz, m, tweak);
	    // shuffle(A, siz, m, tweak, seed);
	    // stagger(A, siz, m, tweak);
	    callHeapSort(A, siz, compareIntVal);
	  }
	  sortcBTime = sortcBTime + clock() - T - TFill;
	  sumQsortB += sortcBTime;
	  // if ( 4 != tweak ) sumQsortBx += sortcBTime;
	  T = clock();
	  for (seed = 0; seed < seedLimit; seed++) { 
	    sawtooth(B, siz, m, tweak);
	    // rand2(B, siz, m, tweak, seed);
	    // plateau(B, siz, m, tweak);
	    // shuffle(B, siz, m, tweak, seed);
	    // stagger(B, siz, m, tweak);
	    foursort(B, siz, compareIntVal, NUMTHREADS);  
	  }
	  cut2Time = cut2Time + clock() - T - TFill;
	  sumCut2 += cut2Time;
	  // if ( 4 != tweak ) sumCut2x += cut2Time;
	  printf("Size: %d m: %d tweak: %d ", siz, m, tweak);
	  printf("sortcBTime: %d ", sortcBTime);
	  printf("Cut2Time: %d ", cut2Time);
	  frac = 0;
	  if ( sortcBTime != 0 ) frac = cut2Time / ( 1.0 * sortcBTime );
	  printf("frac: %f \n", frac);
	  if ( sortcBTime < cut2Time ) sortcBCnt++;
	  else cut2Cnt++;
	  for (i = 0; i < siz; i++) {
	    if ( compareIntVal(A[i], B[i]) != 0 ) {
	      printf("***** validateFourSortBT m: %i tweak: %i at i: %i\n", 
		     m, tweak, i);
	      exit(0);
	    }
	  }
	}
	printf("sumQsortB:   %i sumCut2:  %i frac: %f", 
	       sumQsortB, sumCut2, (sumCut2/(1.0 * sumQsortB)));
	printf(" sortcBCnt:  %i cut2Cnt:  %i\n", sortcBCnt, cut2Cnt);
      }
      frac = 0;
      if ( sumQsortB != 0 ) frac = sumCut2 / ( 1.0 * sumQsortB );
      printf("Measurements:\n");
      printf("sumQsortB:   %i sumCut2:  %i frac: %f", 
	     sumQsortB, sumCut2, (sumCut2/(1.0 * sumQsortB)));
      printf(" sortcBCnt:  %i cut2Cnt:  %i\n", sortcBCnt, cut2Cnt);
      // printf("sumQsortBx:  %i sumCut2x: %i", sumQsortBx, sumCut2x);
      // printf(" sortcBCntx: %i cut2Cntx: %i\n", sortcBCntx, cut2Cntx);

    }
    // free array
    for (i = 0; i < siz; i++) {
      free(A[i]); free(B[i]);
    };
    free(A); free(B);
    siz = siz * 2;
    seedLimit = seedLimit / 2;
  }
} // end validateFourSortBT


// Report the speed fraction of two algorithms on a range of array sizes
// alg1 is parallel FourSort, alg2 is the qsort of Linux 
// (which I suspect has a wrapper that can check for parallel opportunity)
void compareAlgorithmsQ(char *label, int siz, int seedLimit, void (*alg1)(), void (*alg2)(),
			int (*comp1)(), int (*comp2)()  ) {
  printf("%s on size: %d seedLimit: %d #treads: %d\n", label, siz, seedLimit, NUMTHREADS);
  double alg1Time, alg2Time, T;
  int seed;
  int z;
  int limit = 1024 * 1024 * 16 + 1;
  while (siz <= limit) {
    printf("%s %d %s %d %s", "siz: ", siz, " seedLimit: ", seedLimit, "\n");
    struct intval *pi;
    void **A = myMalloc("compareAlgorithms0 1", sizeof(pi) * siz); 
    // construct array
    int i;
    for (i = 0; i < siz; i++) {
      pi = myMalloc("compareAlgorithms0 2", sizeof (struct intval));
      A[i] = pi;
    };
    // warm up the process
    for (seed = 0; seed < seedLimit; seed++) 
      fillarray(A, siz, seed);
    for (z = 0; z < 4; z++) { // repeat to check stability
      alg1Time = 0; alg2Time = 0;
      // int TFill = clock();
	struct timeval tim;
	gettimeofday(&tim, NULL);
	double TFILL=tim.tv_sec+(tim.tv_usec/1000000.0);
      for (seed = 0; seed < seedLimit; seed++) 
	fillarray(A, siz, seed);
      // TFill = clock() - TFill;
      gettimeofday(&tim, NULL);
      TFILL=tim.tv_sec+(tim.tv_usec/1000000.0) - TFILL;
      // T = clock();
      gettimeofday(&tim, NULL);
      T=tim.tv_sec+(tim.tv_usec/1000000.0);
      for (seed = 0; seed < seedLimit; seed++) { 
	fillarray(A, siz, seed);
	(*alg1)(A, siz, comp1, NUMTHREADS); 
      }
      // alg1Time = clock() - T - TFill;
      gettimeofday(&tim, NULL);
      alg1Time=tim.tv_sec+(tim.tv_usec/1000000.0) - T - TFILL;
      // T = clock();
      gettimeofday(&tim, NULL);
      T=tim.tv_sec+(tim.tv_usec/1000000.0);
      for (seed = 0; seed < seedLimit; seed++) { 
	fillarray(A, siz, seed);
	(*alg2)(A, siz, comp2);
      }
      // alg2Time = clock() - T - TFill;
      gettimeofday(&tim, NULL);
      alg2Time=tim.tv_sec+(tim.tv_usec/1000000.0) - T - TFILL;

      printf("%s %d %s", "siz: ", siz, " ");
      printf("%s %f %s", "alg1Time: ", alg1Time, " ");
      printf("%s %f %s", "alg2Time: ", alg2Time, " ");
      float frac = 0; float frac2 = 0;
      if ( alg1Time != 0 &&  alg2Time != 0) { 
	frac = alg2Time / ( 1.0 * alg1Time ); frac2 = 1.0/frac;
      }
      printf("%s %f %s %f %s", "frac: ", frac, "frac2: ", frac2, "\n");
    }
    // free array
    for (i = 0; i < siz; i++) {
      free(A[i]);
    };
    free(A);
    siz = siz * 2;
    seedLimit = seedLimit / 2;
  }
} // end compareAlgorithmsQ

// Wrapper function to invoke qsort
void qsortx(void **A, int size, int (*compar ) () ) {
  struct intval *pi;
  qsort(A, size, sizeof(pi), compar);
} // end qsortx


void compareFoursortAgainstLQ() { // against Linux qsort on Linux i3, i5, ...
  void foursort(), qsortx(); int compareIntVal(), compareIntVal2();
  compareAlgorithmsQ("Compare foursort vs Linux qsort", 
		     1024 * 1024, 32, foursort, qsortx, compareIntVal, compareIntVal2);
} // end compareFoursortAgainstLQ
