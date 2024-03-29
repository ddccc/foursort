/* 
File: c:/bsd/rigel/sort/Licence.txt
Date: Sat Jun 09 22:22:31 2012/ Sat Nov 28 12:44:00 2020

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


// File: c:/bsd/rigel/sort/UseFourSort.c
// Date: Thu Jan 07 15:38:08 2010

/*
   This file is a test bench for excercising foursort and testing 
   it against other algorithms.
   >>Specific objects and a specific comparison function are used throughout<<.
   Feel free to change them as you see fit.
  
   The comparison function given here does NOT work for qsort, because qsort 
   thinks that entities to be sorted reside in the array, while sixsort knows
   that the array contains pointers to objects.  It >is< possible, of course,
   to construct an alternative comparison function for qsort.

   To compile:  $ gcc UseFourSort.c FourSort.o
   It produces the file: a.exe (or the like)


   The main function has many alternative functions.
   Un-comment one to activate.
   Inside such a function are often other choices that can be selected.

   Thu Dec 21 11:20:02 2017
   There is more hybridization. 
   -- quicksort0 has been replaced by a version that is a hybrid also
   -- cut2f has been added and is the main function; it calls cut2 when it
      encounters trouble and delegates to quicksort0 for short arrays

 */

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// To avoid compiler warnings:::

void callCut2(void **AA, int size, 
	      int (*compar ) (const void *, const void * ) );
void callQuicksortm(void **AA, int size, int (*compar ) () );
// void callQsort(void **A, int size, int (*compar ) () );
void callDflgm2(void **AA, int size, int (*compar ) () );
void foursort(void **AA, int size, 
	      int (*compar ) (const void *, const void * ));
void callLQ(void **A, int size, int (*compar ) () ); 
void callBentley(void **A, int size, int (*compar ) () );
void callChensort(void **A, int size, int (*compar ) () ); 
void callMyQS(void **A, int size, int (*compar ) () ); 
void callBlockSort(void **A, int size, int (*compar ) () ); 
void testQsort();
void testQuicksortm();
void testIntroSort();
void testDFLGM();
void testFourSort();
void testBentley();
void testBlockSort();
void validateQsort();
void validateHeapSort();
void validateFourSort();
void validateMyQS();
void validateBentley();
void validateChensort();
void validateFourSortBT();
void validateDFLGM();
void validateIntroSort();
void validateBlockSort();
void timeTest();
void compareQsortAgainstQuicksort0();
void compareQsortAgainstFourSort();
void compareQuicksort0AgainstFourSort();
void compareFourSortAgainstC2LR();
void compareMyQSAgainstFourSort();
void compareLQAgainstFourSort(); // LQ is ako qsort in the Linux C-library
void compareBentleyAgainstFourSort(); 
void compareBentleyAgainstQuicksort0(); 
void compareChenSortAgainstFourSort();
void compareDFLGMAgainstQuicksortm();
void compareDFLGMAgainstFourSort();
void compare00QxAgainstFourSort();
void compare00LQAgainstFourSort();
void compare00BentleyAgainstFourSort();
void compare00ChenAgainstFourSort();
void compareXYZAgainstFourSortBT();  // using the Bentley test bench
// int clock();
void insertionsort(); 
void heapc();
void quicksortmc();
void myqs();
void dflgm();
void introsort();
void blockSort();

void cut2c();
void dflgm3();
// #include "Qusort.c"
#include "C2LR.c"




// Example of objects that can be used to populate an array to be sorted:
  // To obtain the int field from X: ((struct intval *) X)->val
  // To obtain the float field from X: ((struct intval *) X)->valf
  struct intval {
    int val;
    float valf;
  };

// void **A;
// int (*compareXY)();

// Here an exmple comparison function for these objects:
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

// This comparison formula is used for qsort in callQsort and
// for bentley in callBentley 
int compareIntVal2 (const void **a, const void **b)
{
  struct intval *pa = (struct intval *) *a;
  struct intval *pb = (struct intval *) *b;
  return (pa->val - pb->val);
}

int main (int argc, char *argv[]) {
  printf("Running UseFourSort ...\n");
  // Un-comment one of the following to use a specific functionality.
  // Modify the body of these functions as desired

  // To ask for the license expiration date and the host
     // foursort(0, 0, 0);
  // To check that a sorted array is produced
  // testQuicksortm();
  // testFourSort(); 
     // testDFLGM(); 
     // testQsort();
     // testBentley();
  // void introsort(void **A, int N, int M, int (*compare)())
  // testIntroSort();
  // testBlockSort();
  // validateHeapSort();
  // validateFourSort();
  // validateMyQS();
  // validateQsort();
  // validateBentley();
  // validateChensort();
  // validateDFLGM();
  // validateIntroSort();
  // validateBlockSort(); 
  // Measure the sorting time of an algorithm
  // timeTest();
  // Compare the outputs of two sorting algorithms
     // validateXYZ(); // must provide an other algorithm XYZ
     // ... and uncomment validateXYZ ...
  // Compare the speed fraction of two algorithms
  //
  // It looks like that the compare function is not accurate
  // Use instead the timeTest
  // 
     // compareFoursortAgainstXYZ();
     // ... and uncomment also compareFoursortAgainstXYZ ...
  // Whatever here::
     // compareQuicksortmAgainstFourSort();
     // compareMyQSAgainstFourSort();
     // compareQsortAgainstQuicksortm(); 
     // compareQsortAgainstFourSort();
     // compareFourSortAgainstC2LR();
     // compareLQAgainstFourSort(); // LQ is qsort in the Linux C-library
     // compareBentleyAgainstFourSort();
     // compareBentleyAgainstQuicksortm();
     // compareChenSortAgainstFourSort();
     // compareDFLGMAgainstQuicksortm();
     // compareDFLGMAgainstFourSort();
  // using the Bentley test-bench
     // compareXYZAgainstFourSortBT(); 
     // validateFourSortBT(); // against heapsort on Bentley test-bench
     // compare00QxAgainstFourSort();
     // compare00LQAgainstFourSort();
     // compare00BentleyAgainstFourSort();
     // compare00ChenAgainstFourSort();
     return 0;
} // end of main

void *myMalloc(char* location, int size) {
  void *p = malloc(size);
  if ( 0 == p ) {
    fprintf(stderr, "malloc fails for: %s\n", location);
    exit(1);
  }
  return p;
} // end myMalloc

// fillarray assigns random values to the int-field of our objects
void fillarray(void **A, int lng, int startv) {
  int i;
  srand(startv);
  struct intval *pi;
  const int range = 1024*1024*32;
  // /*
  for ( i = 0; i < lng; i++) {
    pi = (struct intval *)A[i];
    pi->val = rand()%range; 
    // pi->val = 0; 
  }
  // */
  /*
  int percentage = 50; // adjust [0,100] to get that percentage on noise
  int v, v2, r, sign = 0;
    for ( i = 1; i < lng; i++) {
      pi = (struct intval *)A[i];
      if ( 0 == percentage ) pi->val = 0; else {
	v = rand()%range;
	sign = v%2;
	v2 = (sign) ? v : -v;
	r = v%100;
	pi->val = (r <= percentage) ? v2 : 0;
      }
  }
  */

  /*
  // for testing dflgm:
  int val = 1000000000;
  pi = (struct intval *)A[(lng-1)/2];
  pi->val = val; 
  int delta = lng/20;
  for ( i = 0; i < lng; i=i+delta) {
    pi = (struct intval *)A[i];
    pi->val = val; 
  }
  */
} // end of fillarray

// Check that adjacent objects in an array are ordered.
// If not, it reports an error 
void check(void **A, int N, int M) {
  printf("Running check N %i M %i \n", N, M);
  int i; int cnt = 0;
  void *x, *y;
  struct intval *pi;
  for (i = N + 1; i <= M; i++) {
    x = A[i-1]; y = A[i];
    if ( compareIntVal(y, x) < 0 ) {
      pi = (struct intval *) y;
      printf("%s %d %s %d %s\n", "Error at: ", i, 
	     " A[i]: ", pi->val, "\n");
      exit(0);
      cnt++;
    }
  }
  printf("check # errors: %d\n", cnt);
} // end check

// void heapSort();
void callHeapsort(void **A, int size, 
	 int (*compar ) (const void *, const void * ) ) {
  // heapSort(A, size, compar);
  heapc(A, 0, size-1, compar);
} // end callHeapsort

// testAlgorithm0 is a generalization of testFoursort;
// another algorithm can be plugged in
void testAlgorithm00(char* label, int siz, void (*alg1)(),
		     int (*compare1)()) {
  printf("%s on size: %d\n", label, siz);
  // create array
  struct intval *pi;
  void **A = myMalloc("testAlgorithm0 1", sizeof(pi) * siz);
  int i;
  for (i = 0; i < siz; i++) {
    pi = myMalloc("testAlgorithm0 2", sizeof (struct intval));
    A[i] = pi;
    // pi->val = i%10;
  };
  // fill its content
  fillarray(A, siz, 100);
  // sort it
  (*alg1)(A, siz, compare1);
  // and check it
  check(A, 0, siz-1);
  // free array
    for (i = 0; i < siz; i++) {
      free(A[i]);
    };
    free(A);
} // end testAlgorithm0

void testAlgorithm0(char* label, int siz, void (*alg1)() ) {
  testAlgorithm00(label, siz, alg1, compareIntVal);
} // end testAlgorithm0

void testAlgorithm2(char* label, int siz, void (*alg1)() ) {
  testAlgorithm00(label, siz, alg1, compareIntVal2);
} // end testAlgorithm1

// like testAlgorithm0 but the size of array is preset inside testAlgorithm
void testAlgorithm(char* label, void (*alg1)() ) {
  //  testAlgorithm0(label, 1024*1024, alg1);
  testAlgorithm0(label, 1024*8, alg1);
} // end testAlgorithm0

// /* Example: use of testAlgorithm
void testFourSort() {
  void foursort();
  testAlgorithm("Running foursort ...", foursort);
}
//  */
void testDFLGM() {
  void callDflgm2();
  testAlgorithm0("Check dflgm()", 1024*1024*2, callDflgm2);
} // end testDFLGM()

void testQuicksortm() {
  void callQuicksortm();
  // testAlgorithm0("Check quicksortm()", 1024*1024, callQuicksortm);
  // testAlgorithm0("Check quicksortm()", 101, callQuicksortm);
  testAlgorithm0("Check quicksortm()", 10000, callQuicksortm);
} // end testQuicksort0() 

void testQsort() {
  void callQsort();
  testAlgorithm2("Check qsort()", 1024*1024, callQsort);
}

void testBentley() {
  void callBentley();
  testAlgorithm2("Check callBentley()", 1024*1024, callBentley);
  // testAlgorithm2("Check callBentley()", 50, callBentley);
}

void testIntroSort() {
  void callIntroSort();
  testAlgorithm0("Check introSort()", 1024*1025*16, callIntroSort);
  // testAlgorithm0("Check introSort()", 1024*128, callIntroSort);
} // end testIntroSort()

void testBlockSort() {
  void callBlockSort();
  testAlgorithm0("Check blockSort()", 1024*1024*16, callBlockSort);
  // testAlgorithm0("Check blockSort()", 1024*1024, callBlockSort); // OK
} // end testIntroSort()


// validateAlgorithm0 is used to check algorithm alg2 against a
// trusted algorithm alg1.
// The check consists of making sure that starting from identical
// inputs they produce identical outputs
// Both input algorithms use compareIntVal for comparisons
void validateAlgorithm0(char* label, int siz, void (*alg1)(), void (*alg2)() ) {
  // siz = 255;
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
  // here alternative ways to fill the array
  // int k;
  // for ( k = 0; k < siz; k++ ) { pi = (struct intval *) A[k]; pi->val = 0; }
  // for ( k = 0; k < siz; k++ ) { pi = (struct intval *) A[k]; pi->val = k%5; }
  // for ( k = 0; k < siz; k++ ) { pi = (struct intval *) A[k]; pi->val = siz-k; }
  // ... sort it
  (*alg1)(A, siz, compareIntVal);

  // create the input for alg2 ...
  void **B = myMalloc("validateAlgorithm0 3", sizeof(pi) * siz);
  // struct intval *pi;
  for (i = 0; i < siz; i++) {
    pi =  myMalloc("validateAlgorithm0 4", sizeof (struct intval));
    B[i] = pi;
  };
  fillarray(B, siz, 100);
  // for ( k = 0; k < siz; k++ ) { pi = (struct intval *) B[k]; pi->val = 0; }
  // for ( k = 0; k < siz; k++ ) { pi = (struct intval *) B[k]; pi->val = k%5; }
  // for ( k = 0; k < siz; k++ ) { pi = (struct intval *) B[k]; pi->val = siz-k; }
  // ... sort it
  (*alg2)(B, siz, compareIntVal);
 
  // check that the two outputs are the same
  int foundError = 0;
  for (i = 0; i < siz; i++)
    // if ( A[i] != B[i] ) {
    if ( compareIntVal(A[i], B[i]) != 0 ) {
      pi = (struct intval *) A[i]; int ai = pi->val;
      pi = (struct intval *) B[i]; int bi = pi->val;
      printf("validate error i: %i ai %i bi %i\n", i, ai, bi);
      foundError = 1;
    }
  if ( !foundError ) 
    printf("NO error found ...\n");
  // free array
    for (i = 0; i < siz; i++) {
      free(A[i]); 
    };
    free(A);
    for (i = 0; i < siz; i++) {
      free(B[i]); 
    };
    free(B);
} // end validateAlgorithm0

// Like validateAlgorithm0 but with fixed array size
void validateAlgorithm(char* label, void (*alg1)(), void (*alg2)() ) {
  validateAlgorithm0(label, 1024 * 1024 * 16, alg1, alg2);
  // validateAlgorithm0(label, 1024*1024, alg1, alg2);
} // end validateAlgorithm

/* Example:: replace XYZ by what you want to validate
void validateXYZ() {
  void foursort(), XYZ();
  validateAlgorithm("Running validate XYZ ...",
		    foursort, XYZ);
}
 */
void validateHeapSort() { // they validate each other :-)
  void callQuicksortm(), callHeapsort();
  validateAlgorithm("Running validate HeapSort ...",
		    callQuicksortm, callHeapsort);
}
void validateFourSort() {
  void callQuicksortm(), foursort();
  validateAlgorithm("Running validate FourSort ...",
		    callQuicksortm, foursort);
}

void validateMyQS() {
  void callQuicksortm(), callMyQS();
  validateAlgorithm("Running validate myqs ...",
		    callQuicksortm, callMyQS);
}

void validateDFLGM() {
  void callQuicksortm(), callDflgm2();
  validateAlgorithm("Running validate DFLGM ...",
		    callQuicksortm, callDflgm2);
}

void validateIntroSort() {
  void callQuicksortm(), callIntroSort();
  validateAlgorithm("Running validate introSort...",
		    callQuicksortm, callIntroSort);
}

void validateBlockSort() {
  void callQuicksortm(), callBloackSort();
  validateAlgorithm("Running validate blockSort...",
		    callQuicksortm, callBlockSort);
}

// Note:
//      alg1 is using the comparison function compareIntVal
//      alg2 is using the comparison function compareIntVal2
void validateAlgorithm1(char* label, int siz, void (*alg1)(), void (*alg2)() ) {
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
  (*alg1)(A, siz, compareIntVal);

  // create the input for alg2 ...
  void **B = myMalloc("validateAlgorithm0 3", sizeof(pi) * siz);
  // struct intval *pi;
  for (i = 0; i < siz; i++) {
    pi =  myMalloc("validateAlgorithm0 4", sizeof (struct intval));
    B[i] = pi;
  };
  fillarray(B, siz, 100);
  // ... sort it
  (*alg2)(B, siz, compareIntVal2);
 
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
  // free array
    for (i = 0; i < siz; i++) {
      free(A[i]); 
    };
    free(A);
    for (i = 0; i < siz; i++) {
      free(B[i]); 
    };
    free(B);
} // end validateAlgorithm1

void validateQsort() {
  void callQuicksortm(), callQsort();
  validateAlgorithm1("Running validate qsort ...", 1024 * 1024 *16,
		    callQuicksortm, callQsort);
}

void validateBentley() {
  void callQuicksortm(), callBentley();
  validateAlgorithm1("Running validate bentley  ...",  1024 * 1024,
		    callQuicksortm, callBentley);
}

void validateChensort() {
  void callQuicksortm(), callChensort();
  validateAlgorithm1("Running validate Chensort ...",  1024 * 1024 *16,
		     callQuicksortm, callChensort);
}

// Run an algorithm and report the time used
void timeTest() {
  printf("timeTest() of XYZ \n");
  double algTime;
  clock_t T;
  int seed;
  // int seedLimit = 10;
  int seedLimit = 5;
  int z;
  int siz = 1024 * 1024 * 16;
  // int siz = 1024 * 1024;
  // construct array
  struct intval *pi;
  void **A = myMalloc("timeTest 1", sizeof(pi) * siz);
  int i;
  for (i = 0; i < siz; i++) {
    pi = myMalloc("timeTest 2", sizeof (struct intval));
    A[i] = pi;
  };
  int repeat = 5;
  // warm up the process
  fillarray(A, siz, 666); 
  double sumTimes = 0;
  for (z = 0; z < repeat; z++) { // repeat to check stability
    // measure the array fill time
    clock_t TFill = clock();
    for (seed = 0; seed < seedLimit; seed++) 
      fillarray(A, siz, seed);
      // here alternative ways to fill the array
      // for ( k = 0; k < siz; k++ ) A[k] = 0;
      // for ( k = 0; k < siz; k++ ) A[k] = k%5;
      // for ( k = 0; k < siz; k++ ) A[k] = siz-k;
    TFill = clock() - TFill;
    // now we know how much time it takes to fill the array
    // measure the time to fill & sort the array
    T = clock();
    for (seed = 0; seed < seedLimit; seed++) { 
      fillarray(A, siz, seed);
      // for ( k = 0; k < siz; k++ ) A[k] = 0;
      // for ( k = 0; k < siz; k++ ) A[k] = k%5;
      // for ( k = 0; k < siz; k++ ) A[k] = siz-k;
      foursort(A, siz, compareIntVal);  
      // callLQ(A, siz, compareIntVal2);
      // callBentley(A, siz, compareIntVal2);
      // callChensort(A, siz, compareIntVal2);
      // callMyQS(A, siz, compareIntVal);  
      // callQuicksortm(A, siz, compareIntVal);
      // callDflgm2(A, siz, compareIntVal);
      // callBlockSort(A, siz, compareIntVal);
    }
    // ... and subtract the fill time to obtain the sort time
    algTime = (clock() - T - TFill)/seedLimit;
    algTime = algTime/ CLOCKS_PER_SEC;
    printf("algTime: %f \n", algTime);
    sumTimes = sumTimes + algTime;
  }
  printf("%s %f %s", "average: ", sumTimes/repeat, "\n");
  // free array
  for (i = 0; i < siz; i++) {
    free(A[i]); 
  };
  free(A);
} // end timeTest()


// Report the speed fraction of two algorithms on a range of array sizes
void compareAlgorithms00(char *label, int siz, int seedLimit, 
		   void (*alg1)(), void (*alg2)(),
			 int (*compare1)(), int (*compare2)() ) {
  seedLimit = seedLimit*3;
  printf("The timings have only comparative relevance.\n");
  printf("%s on size: %d seedLimit: %d\n", label, siz, seedLimit);
  int alg1Time, alg2Time, T;
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
    for (z = 0; z < 3; z++) { // repeat to check stability
      int TFill = clock();
      for (seed = 0; seed < seedLimit; seed++) 
	fillarray(A, siz, seed);
      TFill = clock() - TFill;
      T = clock();
      for (seed = 0; seed < seedLimit; seed++) { 
	fillarray(A, siz, seed);
	(*alg1)(A, siz, compare1); 
      }
      alg1Time = clock() - T - TFill;
      T = clock();
      for (seed = 0; seed < seedLimit; seed++) { 
	fillarray(A, siz, seed);
	(*alg2)(A, siz, compare2);
      }
      alg2Time = clock() - T - TFill;
      printf("%s %d %s", "siz: ", siz, " ");
      printf("%s %d %s", "alg1Time: ", alg1Time, " ");
      printf("%s %d %s", "alg2Time: ", alg2Time, " ");
      float frac = 0;
      if ( alg1Time != 0 ) frac = alg2Time / ( 1.0 * alg1Time );
      printf("%s %f %s", "frac: ", frac, "\n");
    }
    // free array
    for (i = 0; i < siz; i++) {
      free(A[i]);
    };
    free(A);
    siz = siz * 4;
    seedLimit = seedLimit / 4;
    // siz = siz * 2;
    // seedLimit = seedLimit / 2;

  }
} // end compareAlgorithms00

void compareAlgorithms0(char *label, int siz, int seedLimit, 
		   void (*alg1)(), void (*alg2)() ) {
  compareAlgorithms00(label, siz, seedLimit, alg1, alg2, 
		      compareIntVal, compareIntVal);
 } // end compareAlgorithms0

void compareAlgorithms2(char *label, int siz, int seedLimit, 
		   void (*alg1)(), void (*alg2)() ) {
  compareAlgorithms00(label, siz, seedLimit, alg1, alg2, 
		      compareIntVal2, compareIntVal);
 } // end compareAlgorithms2

void compareAlgorithms(char *label, void (*alg1)(), void (*alg2)() ) {
  compareAlgorithms0(label, 1024, 32 * 1024, alg1, alg2);
  // compareAlgorithms0(label, 16 * 1024 * 1024, 2, alg1, alg2);
  // compareAlgorithms0(label, 1024 * 1024, 32, alg1, alg2);
} // end compareAlgorithms


/* Example, replace XYZ by what you want to compare against
void compareFoursortAgainstXYZ() {
  int foursort(), XYZ();
  compareAlgorithms("Compare foursort vs XYZ", foursort, XYZ);
}
*/
void compareQuicksortmAgainstFourSort() {
  void foursort(), callQuicksortm();
  compareAlgorithms("Compare quicksortm vs foursort", callQuicksortm, foursort);
}

void compareFourSortAgainstC2LR() {
  void foursort(), callC2LR();
  compareAlgorithms("Compare foursort vs c2lr", foursort, callC2LR);
}

void callC2LR(void **A, int size, 
	int (*compar ) (const void *, const void * ) ) {
  cut2lr(A, 0, size-1, compar);
} // end  callC2LR


void quicksortm(void **A, int N, int M, int (*compar )());
void callQuicksortm(void **A, int size, 
	int (*compar ) (const void *, const void * ) ) {
  quicksortm(A, 0, size-1, compar);
} // end callQuicksortm

void callIntroSort(void **A, int size, 
	int (*compar ) (const void *, const void * ) ) {
  introsort(A, 0, size-1, compar);
} // end callIntroSort

void compareMyQSAgainstFourSort() {
  void foursort(), callMyQS();
  compareAlgorithms("Compare myqs vs foursort", callMyQS, foursort);
  // compareAlgorithms("Compare myqs vs foursort", foursort, callMyQS);
} // end compareMyQSAgainstFourSort

#define iswap(p, q, A) { void *t3t = A[p]; A[p] = A[q]; A[q] = t3t; }

void callMyQS(void **A, int size, 
	int (*compar ) (const void *, const void * ) ) {
  myqs(A, 0, size-1, compar);
} // end callMyQS

void myqsc();
void myqs(void **A, int N, int M, int (*compar )) {
  int L = M-N;
  if (L <= 0) return;
  int dp = 2.9 * floor(log(L));
  myqsc(A, N, M, dp, compar);
}
// void dflgm();
// void heapc();
// void quicksortmc();
void myqsc(void **A, int N, int M, 
	   int depthLimit, int (*compareXY)()) {
  int L;
 again:
  // printf("myqs N %i M %i\n", N, M);
  L = M - N;
  // if ( L <= 0 ) return;
  if ( L <= 10 ) { 
    insertionsort(A, N, M, compareXY);
    return;
  }
  /*
  if ( L < 127 ) { 
    quicksortmc(A, N, M, depthLimit, compareXY);
    return;
  }
  */

  if ( depthLimit <= 0 ) {
    heapc(A, N, M, compareXY);
    return;
  }
  depthLimit--;

  /*
    // 10 < L
    // grab median of 3 or 9 to get a good pivot
    int pm = N + L/2; // (N+M)/2;
    int pl = N;
    int pn = M;
    if (L > 40) { // do median of 9
      int d = L/8;
      pl = med(A, pl, pl + d, pl + 2 * d, compareXY);
      pm = med(A, pm - d, pm, pm + d, compareXY);
      pn = med(A, pn - 2 * d, pn - d, pn, compareXY);
    }
    pm = med(A, pl, pm, pn, compareXY); // pm is index to 'best' pivot ...
    */
  // /*
        int sixth = (L + 1) / 6;
        int e1 = N  + sixth;
        int e5 = M - sixth;
        int e3 = N + L/2; // (N+M) / 2; // The midpoint
        int e4 = e3 + sixth;
        int e2 = e3 - sixth;

        // Sort these elements using a 5-element sorting network
        // Sort these elements using a 5-element sorting network
        void *ae1 = A[e1], *ae2 = A[e2], *ae3 = A[e3], *ae4 = A[e4], *ae5 = A[e5];
	void *t;
        // if (ae1 > ae2) { t = ae1; ae1 = ae2; ae2 = t; }
	if ( 0 < compareXY(ae1, ae2) ) { t = ae1; ae1 = ae2; ae2 = t; } // 1-2
	if ( 0 < compareXY(ae4, ae5) ) { t = ae4; ae4 = ae5; ae5 = t; } // 4-5
	if ( 0 < compareXY(ae1, ae3) ) { t = ae1; ae1 = ae3; ae3 = t; } // 1-3
	if ( 0 < compareXY(ae2, ae3) ) { t = ae2; ae2 = ae3; ae3 = t; } // 2-3
	if ( 0 < compareXY(ae1, ae4) ) { t = ae1; ae1 = ae4; ae4 = t; } // 1-4
	if ( 0 < compareXY(ae3, ae4) ) { t = ae3; ae3 = ae4; ae4 = t; } // 3-4
	if ( 0 < compareXY(ae2, ae5) ) { t = ae2; ae2 = ae5; ae5 = t; } // 2-5
	if ( 0 < compareXY(ae2, ae3) ) { t = ae2; ae2 = ae3; ae3 = t; } // 2-3
	if ( 0 < compareXY(ae4, ae5) ) { t = ae4; ae4 = ae5; ae5 = t; } // 4-5
	// ... and reassign
	A[e1] = ae1; A[e2] = ae2; A[e3] = ae3; A[e4] = ae4; A[e5] = ae5;

	// Fix end points
	if ( compareXY(ae1, A[N]) < 0 ) iswap(N, e1, A);
	if ( compareXY(A[M], ae5) < 0 ) iswap(M, e5, A);


	register void *pv = ae3; // pivot

	// check Left label invariant
	// if ( pv <= A[N] || A[M] < pv ) {
	if ( compareXY(pv, A[N]) <= 0 || compareXY(A[M], pv) < 0) {
	   // give up because cannot find a good pivot
	   // dflgm is a dutch flag type of algorithm
	  void myqsc();
	  dflgm(A, N, M, e3, myqsc, depthLimit, compareXY);
	  return;
	}

    int i = N; int j = M; // indices

	// The left segment has elements < T
	// The right segment has elements >= T
 loop:
    // while ( pv <= A[j] ) j--;
    while ( compareXY(pv, A[--j]) <= 0 );
    // while ( i < j && A[i] <= pv ) i++;
    while ( compareXY(A[++i], pv) < 0 );
    if ( i < j ) { t = A[i]; A[i] = A[j]; A[j] = t; goto loop; }
    if ( i-N < M-i ) { // order the sub-segments
      myqsc(A, N, j, depthLimit, compareXY); // myqs(A, i+1, M); 
      N = i; goto again;
    } else {
      myqsc(A, i, M, depthLimit, compareXY); // myqs(A, N, i-1); 
      M = j; goto again;
    }
} // end myqsc


void cut2(void **A, int N, int M, int (*compareXY)());
void callCut2(void **A, int size, 
	int (*compar ) (const void *, const void * ) ) {
  cut2(A, 0, size-1, compar);
} // end callCut2

void dflgm2(void **A, int N, int M, int (*compar )());
void callDflgm2(void **A, int size, int (*compar )() ) {
  dflgm2(A, 0, size-1, compar);
} // end callDflgm2


void compareQsortAgainstQuicksortm() {
   void callQsort(), callQuicksortm();
   compareAlgorithms2("Compare qsort vs quicksortm", 1024 * 1024, 32,
		      callQsort, callQuicksortm);
 } // end compareQsortAgainstQuicksortm

void compareQsortAgainstFourSort() {
   void callQsort(), callCut2();
   compareAlgorithms2("Compare qsort vs cut2", 1024 * 1024, 32,
		      callQsort, callCut2);
 } // end compareQsortAgainstCut2

// Wrapper function to invoke qsort
void callQsort(void **A, int size, int (*compar ) () ) {
  struct intval *pi;
  qsort(A, size, sizeof(pi), compar);
} // end callQsort

void compareLQAgainstFourSort() { // LQ is qsort in the Linux C-library
  void callLQ(), callCut2();
  compareAlgorithms2("Compare lq vs cut2", 1024 * 1024, 32,
		     callLQ, callCut2);
} // end compareLqAgainstFourSort

void compareBentleyAgainstFourSort() { 
  void callBentley(), callCut2();
   compareAlgorithms2("Compare bentley vs cut2", 1024, 32 * 1024,
   // compareAlgorithms2("Compare bentley vs cut2", 1024 * 1024, 32,
		      callBentley, callCut2);
} // end compareBentleyAgainstFourSort

void compareBentleyAgainstQuicksortm() { 
  void callBentley(), callQuicksortm();
   compareAlgorithms2("Compare bentley vs quicksortm", 1024, 32 * 1024,
   // compareAlgorithms2("Compare bentley vs quicksortm", 1024 * 1024, 32,
		      callBentley, callQuicksortm);
} // end compareBentleyAgainstQuicksortm

void compareChenSortAgainstFourSort() { 
  void callChensort(), callCut2();
  compareAlgorithms2("Compare chenSort vs cut2", 1024 * 1024, 32,
		     callChensort, callCut2);
} // end compareChenSortAgainstFourSort()

void compareDFLGMAgainstQuicksortm() {
  void callDflgm2(), callQuicksortm();
  compareAlgorithms0("Compare DFLGM vs quicksortm", 1024 * 1024, 32,
		     callDflgm2, callQuicksortm);
} // end compareDFLGMAgainstQuicksortm()

void compareDFLGMAgainstFourSort() {
  void callDflgm2(), callCut2();
  compareAlgorithms0("Compare DFLGM vs cut2", 1024 * 1024, 32,
		     callDflgm2, callCut2);
} // end compareDFLGMAgainstFourSort()


// Infrastructure for the Bentley test-bench; adapted from:
// Bentley, J.L. & M.D. McIlroy, "Engineering a Sort Function", 1993.
/*
void reverse();
void reverseFront();
void reverseBack();
void tweakSort();
void dither();
*/
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

void tweakSort(void **AA, int n) {
  /*
  A = AA;
  compareXY = compareIntVal;
  cut2(0, n-1);
  */
  callCut2(AA, n, compareIntVal);
} // end tweakSort
void dither(void **A, int n) {
  int k;
  struct intval *pi;
  for (k = 0; k < n; k++) {
    // A[k] = A[k] + (k % 5);
    pi = (struct intval *)A[k];
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

void bentley();
// Wrapper function to invoke bentley
void callBentley(void **A, int size, int (*compar ) () ) {
  struct intval *pi;
  bentley(A, size, sizeof(pi), compar);
} // end callBentley


// #include <_ansi.h>
#include <stdlib.h>

#ifndef __GNUC__
#define inline
#endif

// static inline char	*med33 _PARAMS((char *, char *, char *, int (*)()));
// static inline void	 swapfunc _PARAMS((char *, char *, int, int));

#define min(a, b)	(a) < (b) ? a : b

/*
 * Qsort routine from Bentley & McIlroy's "Engineering a Sort Function".
 */
#define swapcode(TYPE, parmi, parmj, n) { 		\
	long i = (n) / sizeof (TYPE); 			\
	register TYPE *pi = (TYPE *) (parmi); 		\
	register TYPE *pj = (TYPE *) (parmj); 		\
	do { 						\
		register TYPE	t = *pi;		\
		*pi++ = *pj;				\
		*pj++ = t;				\
        } while (--i > 0);				\
}

#define SWAPINIT(a, es) swaptype = ((char *)a - (char *)0) % sizeof(long) || \
	es % sizeof(long) ? 2 : es == sizeof(long)? 0 : 1;

static inline void swapfunc(a, b, n, swaptype)
     char *a;
     char *b;
     int n;
     int swaptype;
{
	if (swaptype <= 1) 
		swapcode(long, a, b, n)
	else
		swapcode(char, a, b, n)
}

#define swap(a, b)					\
	if (swaptype == 0) {				\
	  long t = *(long *)(a);			\
		*(long *)(a) = *(long *)(b);		\
		*(long *)(b) = t;			\
	} else						\
		swapfunc(a, b, es, swaptype)

#define vecswap(a, b, n) 	if ((n) > 0) swapfunc(a, b, n, swaptype)

static inline char * med33(a, b, c, cmp)
     char *a;
     char *b;
     char *c;
     int (*cmp)(); 
{
	return cmp(a, b) < 0 ?
	       (cmp(b, c) < 0 ? b : (cmp(a, c) < 0 ? c : a ))
              :(cmp(b, c) > 0 ? b : (cmp(a, c) < 0 ? a : c ));
}

void bentley(a, n, es, cmp)
     void *a;
     size_t n;
     size_t es;
     int (*cmp)();
{
  char *pa, *pb, *pc, *pd, *pl, *pm, *pn;
  int d, r, swaptype; 
  // The use of swap_cnt and the 2nd invocation of insertionsort has been removed
  // int swap_cnt; 

loop:	SWAPINIT(a, es);
  // printf("bentley n: %i es %i\n", n, es);
  // swap_cnt = 0;
	if (n < 7) {
		for (pm = (char *) a + es; pm < (char *) a + n * es; pm += es)
			for (pl = pm; pl > (char *) a && cmp(pl - es, pl) > 0;
			     pl -= es)
				swap(pl, pl - es);
		return;
	}
	pm = (char *) a + (n / 2) * es;
	if (n > 7) {
		pl = a;
		pn = (char *) a + (n - 1) * es;
		if (n > 40) {
			d = (n / 8) * es;
			pl = med33(pl, pl + d, pl + 2 * d, cmp);
			pm = med33(pm - d, pm, pm + d, cmp);
			pn = med33(pn - 2 * d, pn - d, pn, cmp);
		}
		pm = med33(pl, pm, pn, cmp);
	}
	// printf("pivot is at: %i\n", pm - (char *)a);
	swap(a, pm);
	pa = pb = (char *) a + es;

	pc = pd = (char *) a + (n - 1) * es;
	for (;;) {
		while (pb <= pc && (r = cmp(pb, a)) <= 0) {
		  // printf("Inside 1st loop N2 %i I %i\n",
		  //	 (pa- (char *)a)/es, (pb- (char *)a)/es);
			if (r == 0) {
			        // swap_cnt = 1;
				swap(pa, pb);
				pa += es;
			}
			pb += es;
		}
	        // printf("After 1st loop N2 %i I %i\n",
		//       (pa- (char *)a)/es, (pb- (char *)a)/es);
		while (pb <= pc && (r = cmp(pc, a)) >= 0) {
			if (r == 0) {
			        // swap_cnt = 1;
				swap(pc, pd);
				pd -= es;
			}
			pc -= es;
		}
		if (pb > pc)
			break;
		// printf("swap N %i I %i J %i M %i \n", 
		//       0, (pb- (char *)a )/es, (pc- (char *)a)/es, 0);
		swap(pb, pc);
		// swap_cnt = 1;
		pb += es;
		pc -= es;
	}
	/*
	if (swap_cnt == 0) {  // Switch to insertion sort 
		for (pm = (char *) a + es; pm < (char *) a + n * es; pm += es)
			for (pl = pm; pl > (char *) a && cmp(pl - es, pl) > 0; 
			     pl -= es)
				swap(pl, pl - es);
		return;
	}
	*/

	pn = (char *) a + n * es;
	r = min(pa - (char *)a, pb - pa);
	// printf("l %i r %i r %i \n", (pa - (char *)a)/es, (pb - pa)/es, r);
	vecswap(a, pb - r, r);
	r = min(pd - pc, pn - pd - es);
	// printf("l %i r %i r %i\n", (pd - pc)/es, (pn - pd - es)/es, r);
	vecswap(pb, pn - r, r);
	/* Ordering on the recursive calls has been added to obtain at most 
	   log2(N) stack space 
	if ((r = pb - pa) > es)
		bentley(a, r / es, es, cmp);
	if ((r = pd - pc) > es) { 
	        // Iterate rather than recurse to save stack space 
		a = pn - r;
		n = r / es;
		goto loop;
	}
	*/
	
    int left =  pb - pa;
    int right = pd - pc;
    if ( left <= right ) {
       if ( left > es ) bentley(a, left / es, es, cmp);
       if ( right > es ) {
	   // Iterate rather than recurse to save stack space 
	   a = pn - right;
	   n = right / es;
	   goto loop;
       }
    } else {
       if ( right > es ) bentley(pn-right, right / es, es, cmp);
       if ( left > es ) {
	   // Iterate rather than recurse to save stack space 
	   // a = pn - left;
	   n = left / es;
	   goto loop;
       }
    }
} // end bentley


// This function excecutes foursort and heapsort and checks the outputs on the
// 5 * 126 different distributions of the Bentley bench-test / quite time consuming 
// Uncomment the five sets in turn - consistently 5 times, four locs
void validateFourSortBT() {
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
      	for (tweak = 0; tweak <= 5; tweak++ ) {
	  // tweak = 4; {
	  sortcBTime = 0; cut2Time = 0;
	  TFill = clock();
	  for (seed = 0; seed < seedLimit; seed++) 
	    sawtooth(A, siz, m, tweak);
	    // rand2(A, siz, m, tweak, seed);
	    // plateau(A, siz, m, tweak);
	    // shuffle(A, siz, m, tweak, seed);
	    // stagger(A, siz, m, tweak);
	    // slopes(A, siz, m, tweak);
	  TFill = clock() - TFill;
	  T = clock();
	  for (seed = 0; seed < seedLimit; seed++) { 
	    sawtooth(A, siz, m, tweak);
	    // rand2(A, siz, m, tweak, seed);
	    // plateau(A, siz, m, tweak);
	    // shuffle(A, siz, m, tweak, seed);
	    // stagger(A, siz, m, tweak);
	    // slopes(A, siz, m, tweak);
	    callHeapsort(A, siz, compareIntVal);
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
	    // slopes(B, siz, m, tweak);

	    foursort(B, siz, compareIntVal);  
	    // callDflgm2(B, siz, compareIntVal);
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

// fill with random numbers according to percentage, otherwise 0
void fillRandom(void **A, int lng, int startv, int percentage) {
  if ( percentage < 0 || 100 < percentage ) percentage = 50;
  int i, v, r, v2; 
  srand(startv);
  struct intval *pi;
  for ( i = 0; i < lng; i++) {
    pi = (struct intval *)A[i];
    if ( 0 == percentage ) pi->val = 0; else {
      v = rand();
      v2 = (v < 0) ? -v : v;
      r = v2%100;
      pi->val = (r <= percentage) ? v : 0; 
    }
  }
} // end fillRandom

// fill with random numbers according to percentage, otherwise with i
void fillRandom2(void **A, int lng, int startv, int percentage) {
  if ( percentage < 0 || 100 < percentage ) percentage = 50;
  int i, v, r, v2; 
  srand(startv);
  struct intval *pi;
  for ( i = 0; i < lng; i++) {
    pi = (struct intval *)A[i];
    if ( 0 == percentage ) pi->val = i; else {
      v = rand();
      v2 = (v < 0) ? -v : v;
      r = v2%100;
      pi->val = (r <= percentage) ? v : i; 
    }
  }
} // end fillRandom2

void testNonRandom(int p, void **A, int siz, int seedLimit, 
		   void (*alg1)(), void (*alg2)(), 
		   int (*compare1)(), int (*compare2)()  ) {
  int z, alg1Time, alg2Time, T, seed;
  // for (z = 0; z < 3; z++) { // repeat to check stability
  for (z = 0; z < 1; z++) { // repeat to check stability
    alg1Time = 0; alg2Time = 0;
    int TFill = clock();
    for (seed = 0; seed < seedLimit; seed++) 
      fillarray(A, siz, seed);
    TFill = clock() - TFill;
    T = clock();
    for (seed = 0; seed < seedLimit; seed++) { 
      fillRandom(A, siz, seed, p); // zeros + random
      // fillRandom2(A, siz, seed, p); // sorted + random
      (*alg1)(A, siz, compare1); 
    }
    alg1Time = clock() - T - TFill;
    T = clock();
    for (seed = 0; seed < seedLimit; seed++) { 
      fillRandom(A, siz, seed, p); // zeros + random
      // fillRandom2(A, siz, seed, p); // sorted + random
      (*alg2)(A, siz, compare2);
    }
    alg2Time = clock() - T - TFill;
    printf("%s %d %s %i", "siz: ", siz, " p: ", p);
    printf(" %s %d %s", "alg1Time: ", alg1Time, " ");
    printf("%s %d %s", "alg2Time: ", alg2Time, " ");
    float frac = 0;
    if ( alg1Time != 0 ) frac = alg2Time / ( 1.0 * alg1Time );
    printf("%s %f %s", "frac: ", frac, "\n");
  }
} // end testNonRandom


// Generate distributions with a varying percentage of uniform random numbers
// and compare the running times of two algorithms
void compareZeros00(char *label, int siz, int seedLimit, 
		   void (*alg1)(), void (*alg2)(),
		   int (*compare1)(), int (*compare2)() ) {
  printf("%s on size: %d seedLimit: %d\n", label, siz, seedLimit);
  int seed;
  int limit = 1024 * 1024 * 16 + 1;
  // int limit = 1024 * 1024 + 1;
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
    // int p;
    // for (p = 0; p < 101; p = p + 20 )  // percentages of random elements
    //   testNonRandom(p, A, siz, seedLimit, alg1, alg2, compare1, compare2);
    testNonRandom(0, A, siz, seedLimit, alg1, alg2, compare1, compare2);
    testNonRandom(1, A, siz, seedLimit, alg1, alg2, compare1, compare2);
    testNonRandom(2, A, siz, seedLimit, alg1, alg2, compare1, compare2);
    testNonRandom(4, A, siz, seedLimit, alg1, alg2, compare1, compare2);
    testNonRandom(8, A, siz, seedLimit, alg1, alg2, compare1, compare2);
    testNonRandom(16, A, siz, seedLimit, alg1, alg2, compare1, compare2);
    testNonRandom(32, A, siz, seedLimit, alg1, alg2, compare1, compare2);
    testNonRandom(64, A, siz, seedLimit, alg1, alg2, compare1, compare2);

    // testNonRandom(20, A, siz, seedLimit, alg1, alg2, compare1, compare2);
    // testNonRandom(40, A, siz, seedLimit, alg1, alg2, compare1, compare2);
    // testNonRandom(100, A, siz, seedLimit, alg1, alg2, compare1, compare2);

    // free array
    for (i = 0; i < siz; i++) {
      free(A[i]);
    };
    free(A);
    siz = siz * 2;
    seedLimit = seedLimit / 2;
  }
} // end compareZeros00


// used to compare two versions of quicksortm:
// without and the with delegation to dflgm
void compare00QxAgainstFourSort() {
  void callQuicksortm(), foursort();
  compareZeros00("compare00QxAgainstFoursort", 
		 1024*1024, 16, callQuicksortm, foursort, 
		 compareIntVal, compareIntVal);
} // end compare00QxAgainstFourSort

void compare00LQAgainstFourSort() {
  void callLQ(), foursort();
  compareZeros00("compare00LQAgainstFoursort", 
		 1024*1024, 16, callLQ, foursort, 
		 compareIntVal2, compareIntVal);
} // end compare00LQAgainstFourSort

void compare00BentleyAgainstFourSort() {
  void callBentley(), foursort();
  compareZeros00("compare00BentleyAgainstFoursort", 
		 // 1024*1024, 16, 
		 1024*1024*16, 2, 
		 callBentley, foursort, 
		 compareIntVal2, compareIntVal);
} // end compare00BentleyAgainstFourSort

void compare00ChenAgainstFourSort() {
  void callChensort(), foursort();
  compareZeros00("compare00ChenAgainstFoursort", 
		 1024*1024, 16, callChensort, foursort, 
		 compareIntVal2, compareIntVal);
} // end compare00ChenAgainstFourSort



/* Copyright (C) 1991,1992,1996,1997,1999,2004 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Written by Douglas C. Schmidt (schmidt@ics.uci.edu).

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

/* If you consider tuning this algorithm, you should consult first:
   Engineering a sort function; Jon Bentley and M. Douglas McIlroy;
   Software - Practice and Experience; Vol. 23 (11), 1249-1265, 1993.  */

#include <alloca.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

/* Byte-wise swap two items of size SIZE. */
#define SWAP(a, b, size)						      \
  do									      \
    {									      \
      register size_t __size = (size);					      \
      register char *__a = (a), *__b = (b);				      \
      do								      \
	{								      \
	  char __tmp = *__a;						      \
	  *__a++ = *__b;						      \
	  *__b++ = __tmp;						      \
	} while (--__size > 0);						      \
    } while (0)

/* Discontinue quicksort algorithm when partition gets below this size.
   This particular magic number was chosen to work best on a Sun 4/260. */
#define MAX_THRESH 4

/* Stack node declarations used to store unfulfilled partition obligations. */
typedef struct
  {
    char *lo;
    char *hi;
  } stack_node;

/* The next 4 #defines implement a very fast in-line stack abstraction. */
/* The stack needs log (total_elements) entries (we could even subtract
   log(MAX_THRESH)).  Since total_elements has type size_t, we get as
   upper bound for log (total_elements):
   bits per byte (CHAR_BIT) * sizeof(size_t).  */
#define STACK_SIZE	(CHAR_BIT * sizeof(size_t))
#define PUSH(low, high)	((void) ((top->lo = (low)), (top->hi = (high)), ++top))
#define	POP(low, high)	((void) (--top, (low = top->lo), (high = top->hi)))
#define	STACK_NOT_EMPTY	(stack < top)


/* Order size using quicksort.  This implementation incorporates
   four optimizations discussed in Sedgewick:

   1. Non-recursive, using an explicit stack of pointer that store the
      next array partition to sort.  To save time, this maximum amount
      of space required to store an array of SIZE_MAX is allocated on the
      stack.  Assuming a 32-bit (64 bit) integer for size_t, this needs
      only 32 * sizeof(stack_node) == 256 bytes (for 64 bit: 1024 bytes).
      Pretty cheap, actually.

   2. Chose the pivot element using a median-of-three decision tree.
      This reduces the probability of selecting a bad pivot value and
      eliminates certain extraneous comparisons.

   3. Only quicksorts TOTAL_ELEMS / MAX_THRESH partitions, leaving
      insertion sort to order the MAX_THRESH items within each partition.
      This is a big win, since insertion sort is faster for small, mostly
      sorted array segments.

   4. The larger of the two sub-partitions is always pushed onto the
      stack first, with the algorithm then concentrating on the
      smaller partition.  This *guarantees* no more than log (total_elems)
      stack size is needed (actually O(1) in this case)!  */

// This is qsort in the Linux C-library
void
_quicksort (void *const pbase, size_t total_elems, size_t size,
	    //	    __compar_d_fn_t cmp, void *arg)
	    int (*cmp)(), void *arg)
{
  register char *base_ptr = (char *) pbase;

  const size_t max_thresh = MAX_THRESH * size;

  if (total_elems == 0)
    /* Avoid lossage with unsigned arithmetic below.  */
    return;

  if (total_elems > MAX_THRESH)
    {
      char *lo = base_ptr;
      char *hi = &lo[size * (total_elems - 1)];
      stack_node stack[STACK_SIZE];
      stack_node *top = stack;

      PUSH (NULL, NULL);

      while (STACK_NOT_EMPTY)
        {
          char *left_ptr;
          char *right_ptr;

	  /* Select median value from among LO, MID, and HI. Rearrange
	     LO and HI so the three values are sorted. This lowers the
	     probability of picking a pathological pivot value and
	     skips a comparison for both the LEFT_PTR and RIGHT_PTR in
	     the while loops. */

	  char *mid = lo + size * ((hi - lo) / size >> 1);

	  if ((*cmp) ((void *) mid, (void *) lo, arg) < 0)
	    SWAP (mid, lo, size);
	  if ((*cmp) ((void *) hi, (void *) mid, arg) < 0)
	    SWAP (mid, hi, size);
	  else
	    goto jump_over;
	  if ((*cmp) ((void *) mid, (void *) lo, arg) < 0)
	    SWAP (mid, lo, size);
	jump_over:;

	  left_ptr  = lo + size;
	  right_ptr = hi - size;

	  /* Here's the famous ``collapse the walls'' section of quicksort.
	     Gotta like those tight inner loops!  They are the main reason
	     that this algorithm runs much faster than others. */
	  do
	    {
	      while ((*cmp) ((void *) left_ptr, (void *) mid, arg) < 0)
		left_ptr += size;

	      while ((*cmp) ((void *) mid, (void *) right_ptr, arg) < 0)
		right_ptr -= size;

	      if (left_ptr < right_ptr)
		{
		  SWAP (left_ptr, right_ptr, size);
		  if (mid == left_ptr)
		    mid = right_ptr;
		  else if (mid == right_ptr)
		    mid = left_ptr;
		  left_ptr += size;
		  right_ptr -= size;
		}
	      else if (left_ptr == right_ptr)
		{
		  left_ptr += size;
		  right_ptr -= size;
		  break;
		}
	    }
	  while (left_ptr <= right_ptr);

          /* Set up pointers for next iteration.  First determine whether
             left and right partitions are below the threshold size.  If so,
             ignore one or both.  Otherwise, push the larger partition's
             bounds on the stack and continue sorting the smaller one. */

          if ((size_t) (right_ptr - lo) <= max_thresh)
            {
              if ((size_t) (hi - left_ptr) <= max_thresh)
		/* Ignore both small partitions. */
                POP (lo, hi);
              else
		/* Ignore small left partition. */
                lo = left_ptr;
            }
          else if ((size_t) (hi - left_ptr) <= max_thresh)
	    /* Ignore small right partition. */
            hi = right_ptr;
          else if ((right_ptr - lo) > (hi - left_ptr))
            {
	      /* Push larger left partition indices. */
              PUSH (lo, right_ptr);
              lo = left_ptr;
            }
          else
            {
	      /* Push larger right partition indices. */
              PUSH (left_ptr, hi);
              hi = right_ptr;
            }
        }
    }

  /* Once the BASE_PTR array is partially sorted by quicksort the rest
     is completely sorted using insertion sort, since this is efficient
     for partitions below MAX_THRESH size. BASE_PTR points to the beginning
     of the array to sort, and END_PTR points at the very last element in
     the array (*not* one beyond it!). */

  // #define min(x, y) ((x) < (y) ? (x) : (y))

  {
    char *const end_ptr = &base_ptr[size * (total_elems - 1)];
    char *tmp_ptr = base_ptr;
    char *thresh = min(end_ptr, base_ptr + max_thresh);
    register char *run_ptr;

    /* Find smallest element in first threshold and place it at the
       array's beginning.  This is the smallest array element,
       and the operation speeds up insertion sort's inner loop. */

    for (run_ptr = tmp_ptr + size; run_ptr <= thresh; run_ptr += size)
      if ((*cmp) ((void *) run_ptr, (void *) tmp_ptr, arg) < 0)
        tmp_ptr = run_ptr;

    if (tmp_ptr != base_ptr)
      SWAP (tmp_ptr, base_ptr, size);

    /* Insertion sort, running from left-hand-side up to right-hand-side.  */

    run_ptr = base_ptr + size;
    while ((run_ptr += size) <= end_ptr)
      {
	tmp_ptr = run_ptr - size;
	while ((*cmp) ((void *) run_ptr, (void *) tmp_ptr, arg) < 0)
	  tmp_ptr -= size;

	tmp_ptr += size;
        if (tmp_ptr != run_ptr)
          {
            char *trav;

	    trav = run_ptr + size;
	    while (--trav >= run_ptr)
              {
                char c = *trav;
                char *hi, *lo;

                for (hi = lo = trav; (lo -= size) >= tmp_ptr; hi = lo)
                  *hi = *lo;
                *hi = c;
              }
          }
      }
  }
} // end _quicksort 

// LQ is qsort in the Linux C-library
void callLQ(void **A, int size, int (*compar ) () ) { 
  struct intval *pi;
  _quicksort(A, size, sizeof(pi), compar, NULL);
} // end callLQ


/*   This is the C code for Adaptive Symmetry Partition Sort       */     
/*   which sorts the specified sequence into ascending order.      */
/*   This algorithm is Rem-adaptive and offers better performance  */ 
/*   than Psort                                                    */
/*   Date : 2007/01/24, version 1.0                                */
/*   Copyright (C) 2007 Jingchao Chen                              */
/*   Any comment is welcome. For any question, email to            */
/*   chen-jc@dhu.edu.cn or chenjingchao@yahoo.com                  */
// From: http://www.gtoal.com/languages/bcpl/BCPL/bcplprogs/sort/AdoSymmetryPSort.cpp

// #include <conio.h>
#include <stdlib.h>
#include <stdio.h>
// #include <dos.h>
#define SIZE_n 45
#define ItemType int

int  n=SIZE_n;
ItemType key[SIZE_n];


void Adp_SymPSort(void *a, int n, int es, int (*cmp)(const void *, const void *));
void callChensort(void **A, int size, int (*compar ) () ) { 
  struct intval *pi;
  Adp_SymPSort(A, size, sizeof(pi), compar);
}

// void check(const void * a);
/*
main(void)
{   int  i;

    printf("\n Adaptive Symmetry Partition Sort \n",n);
    srand(2007);
    for(i=0;i<n;i++) key[i]=rand()%n; // generate a random integer in [0,32767],
   	Adp_SymPSort((char *)key,n,sizeof(ItemType),cmp);
    check(key); //verify output;
}
*/
 /*
void check(const void * a)
{    int i;
     for (i=0; i< n-1; i++){
          if (*((ItemType *)a+i)>*((ItemType *)a+i+1))
          {
                printf( "\nThe sequence is not ordered");
                return;
          }
     }
     printf( "\nThe sequence is correctly sorted");
}
 */
// the code for the sorting algorithm begins  
  /*
#define swapvector(TYPE,pi,pj,n)            \
	do {                                    \
       TYPE t= *(TYPE *) (pi);              \
       *(TYPE *) (pi) = *(TYPE *) (pj);     \
       *(TYPE *) (pj) = t;                  \
       pi+=sizeof(TYPE); pj+=sizeof(TYPE);  \
       n-=sizeof(TYPE);                     \
  	} while (n > 0);
 
void swapfunc(char *a, char *b, int n, int swaptype)
{    if (swaptype <=1 ) swapvector(long,a,b,n)
     else swapvector(char,a,b,n)
}

#define swap(a,b)                          \
    if (swaptype == 0) {                   \
       long t = * (long *) (a);            \
       * (long *) (a) = * (long *) (b);    \
       * (long *) (b) = t;                 \
	}                                      \
    else swapfunc(a,b,es,swaptype)

#define SWAPINIT(a,es) swaptype =                           \
 (a - (char *) 0) % sizeof(long) || es % sizeof(long) ? 2 : \
 es == sizeof(long) ? 0 : 1
  */


#define pxx 16
#define beta1 256
#define beta2 512
// Symmetry Partition Sort
void SymPartitionSort(char *a, int s, int n, int es, int (*cmp)(const void *,const void *))
{   char *pm,*pb,*pc,*pi,*pj;
    int i,v,vL,m,left,right,swaptype,sp,eq,ineq,rc;
    left=right=0;
    SWAPINIT(a,es);
    while(1){
        if(n < 8){ //Insertion sort on small arrays
             for (s=1; s < n; s++)
                for (pb = a+s*es; cmp(pb-es,pb) > 0; ) {
                        swap(pb,pb-es); pb-=es; 
                        if(pb <= a) break;
                }
             return;
        }
        m= s<0 ? -s:s;
        if(m <= 2){//First,middle,last items are ordered and placed 1st,2nd and last
            v = beta2 > n ? n : 63;
            pc=a+(v-1)*es;
            pm=a+es; 
            swap(pm,a+(v/2)*es);
            if(cmp(a, pm) > 0) {swap(a,pm);}
                if((cmp(pm, pc) > 0)) {
                      swap(pm,pc);
                      if((cmp(a, pm) > 0)) {swap(a,pm);}
                }
                left=right=1; pc-=es;
            }
            else{
               v=m > n/beta1 ? n : pxx*m-1;
               if(s < 0) {  //Move sorted items to left end
                      if(v<n) {left=m; s=-s;}
                      else    {left=(m+1)/2; right=m/2;} 
                      swapfunc(a, a+(n-m)*es, left*es, swaptype);
                      left--;
               }
               if(s>0){
                      pb=a+m*es; pc=a+v*es;  
                      if(v < n){ //Extract sampling items 
                          sp=(n/v)*es; pj=pb; pi=pb;  
                          for(; pi < pc; pi+=es, pj+=sp) swap(pi,pj);
                      }
                      i=right=m/2; //Right move sorted items
                      do{ pb-=es; pc-=es; swap(pb,pc); i--;} while (i);
                      left=(m-1)/2; 
               }
               pm=a+left*es; pc=pm+(v-m)*es;
            }
//Fat partition begins
        pb=pi=pm+es;  
        do {
            while ( (rc=cmp(pb,pm)) < 0 ) pb+=es;
            if(pb >= pc) break;
            if(rc==0){
				if(pi!=pb) {swap(pb,pi);}
                 pi+=es; pb+=es;
                 continue;
            }
            while ((rc=cmp(pc,pm)) > 0 ) pc-=es;
            if(pb >= pc) break;
            swap(pb,pc);
            if(rc==0){
				if(pi!=pb) { swap(pb,pi);}
                pi+=es; 
            }
            pb+=es; pc-=es;
        } while (pb <= pc);
//Move equal-key items
        eq=pi-pm, ineq=pb-pi;
        if( ineq < eq) pi=pm+ineq;
        pc=pb;
        while (pm < pi ) { pc-=es; swap(pc,pm); pm+=es;} 
//Fat partition ends
            vL=(pb-a)/es; 
            if(right < v-vL) SymPartitionSort(pb, -right, v-vL, es, cmp);
            vL=vL-eq/es; 
            if(v < n){
                if(left < vL) SymPartitionSort(a, left,vL,es,cmp);
                s=v;  //Remove tail recursion
            }
            else{
                if(left >= vL) return;
                s=left; n=vL; //Remove tail recursion
            }
    }
} // end SymPartitionSort

// Adaptive Symmetry Partition Sort
void Adp_SymPSort(void *a, int n, int es, int (*cmp)(const void *,const void *))
{   char *pb,*pc,*pi,*pj;
    int swaptype,i,j,ne,rc,D_inv,left,m,Rev=0;
  
    SWAPINIT((char *)a,es);
//Find 1st run
    ne = n * es;
    for (i=es; i < ne; i+=es){
         if((rc=cmp((char *)a+i-es, (char *)a+i)) != 0 ){
             if(Rev==0) Rev= rc < 0 ? 1 : -1;//Rev=1: increasing, -1: decreasing
             else if(rc*Rev > 0) break;
         }
    }
    D_inv= Rev*(i/es);   //D_inv: difference of inversions & orders
    for(j=i+es; j < ne; j+=(97*es)){
         if((rc=cmp((char *)a+j-es, (char *)a+j)) < 0) D_inv++;
         if(rc>0) D_inv--;
    }
    pb=(char *)a+i-es;
    if(abs(D_inv) > n/512 ) {     
         if(Rev*D_inv < 0) {pb=(char *)a; Rev=-Rev;}  //If 1st run is reverse, re-find it
            pc=(char *)a+n*es; pj=pb;
            while(1){
                pj=pj+10*es; pi=pj-es;
                if(pj >= pc) break;
                while (pj < pc && Rev*cmp(pj-es, pj) <=0) pj+=es; //Find next run foreward
                while (pi > pb && Rev*cmp(pi-es, pi) <=0) pi-=es; //Find next run backward
                if(pj-pi < 4*es) continue;
                if(pb!=a) { //Find knots in 1st and 2nd run 
                      j=((pj-pi)/es)/2;
                      m=((pb-(char *)a)/es)/4;
                      if (j > m ) j=m;
                      for(i=0; i<j; i++) if(Rev*cmp(pb-i*es,pi+i*es) <= 0) break;
                      if(i>=j) continue;
                      pb=pb+(1-i)*es; pi=pi+i*es;
                }
                // Merge two runs by moving 2nd knot to 1st knot 
                if(pi!=pb) while(pi < pj ) { swap(pb,pi); pb+=es; pi+=es;}
                else pb=pj;
                pb-=es;
            }
    }   
    left=(pb-(char *)a)/es+1;
    if(Rev==-1){ //if the longest run reverse, reverse it
        pc=(char *)a;
        while(pc < pb ) {swap(pc,pb); pc+=es; pb-=es; }
    }
    if(left < n) SymPartitionSort((char *)a, left, n, es, cmp);
} // end Adp_SymPSort


// This function excecutes XYZ and foursort on the 5 * 126 different 
// distributions of the Bentley bench-test / quite time consuming 
void compareXYZAgainstFourSortBT() {
  printf("Entering compareXYZAgainstFourSortBT Sawtooth ........\n");
  // printf("Entering compareXYZAgainstFourSortBT Rand2 ........\n");
  // printf("Entering compareXYZAgainstFourSortBT Plateau ........\n");
  // printf("Entering compareXYZAgainstFourSortBT Shuffle ........\n");
  // printf("Entering compareXYZAgainstFourSortBT Stagger ........\n");
  int sortcBTime, cut2Time, T;
  int seed =  666;
  int z;
  int siz = 1024*1024;
  // int limit = 1024 * 1024 * 16 + 1;
  // int seedLimit = 32 * 1024;
  int limit = siz + 1;
  // int seedLimit = 32;
  // int seedLimit = 5;
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
    fillarray(B, siz, seed);
    int TFill, m, tweak;
    int sortcBCnt, cut2Cnt; // , sortcBCntx, cut2Cntx;
    int sumQsortB, sumCut2; // , sumQsortBx, sumCut2x;
    // for (z = 0; z < 3; z++) { // repeat to check stability
    for (z = 0; z < 1; z++) { // repeat to check stability
      sortcBCnt = cut2Cnt = sumQsortB = sumCut2 = 0;
      // sortcBCntx = cut2Cntx = sumQsortBx = sumCut2x = 0;
      for (m = 1; m < 2 * siz; m = m * 2) {
      // m = 1024 * 1024; {
      // m = 2; {
      	for (tweak = 0; tweak <= 5; tweak++ ) {
	  if (4 == tweak) continue; // due to bias 
	  sortcBTime = 0; cut2Time = 0;
	  TFill = clock();
	  for (seed = 0; seed < seedLimit; seed++) 
	    // sawtooth(A, siz, m, tweak);
	    // rand2(A, siz, m, tweak, seed);
	    // plateau(A, siz, m, tweak); // not used
	    // shuffle(A, siz, m, tweak, seed); // not used
	    // stagger(A, siz, m, tweak);
	    slopes(A, siz, m, tweak);
	  TFill = clock() - TFill;
	  T = clock();
	  for (seed = 0; seed < seedLimit; seed++) { 
	    // sawtooth(A, siz, m, tweak);
	    // rand2(A, siz, m, tweak, seed);
	    // plateau(A, siz, m, tweak);  // not used
	    // shuffle(A, siz, m, tweak, seed); // not used
	    // stagger(A, siz, m, tweak);
	    slopes(A, siz, m, tweak);

	    // Alternative algorithms to compare against FourSort::
	    // callLQ(A, siz, compareIntVal2);
	    callBentley(A, siz, compareIntVal2);
	    // callChensort(A, siz, compareIntVal2);
            // callMyQS(A, siz, compareIntVal);  
	  }
	  sortcBTime = sortcBTime + clock() - T - TFill;
	  sumQsortB += sortcBTime;
	  // if ( 4 != tweak ) sumQsortBx += sortcBTime;
	  T = clock();
	  for (seed = 0; seed < seedLimit; seed++) { 
	    // sawtooth(B, siz, m, tweak);
	    // rand2(B, siz, m, tweak, seed);
	    // plateau(B, siz, m, tweak);  // not used
	    // shuffle(B, siz, m, tweak, seed);  // not used
	    // stagger(B, siz, m, tweak);
	    slopes(B, siz, m, tweak);

	    foursort(B, siz, compareIntVal); 
	    // callQuicksortm(B, siz, compareIntVal); 
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
	  /* no checking here
	  for (i = 0; i < siz; i++) {
	    if ( compareIntVal(A[i], B[i]) != 0 ) {
	      printf("***** validateFourSortBT m: %i tweak: %i at i: %i\n", 
		     m, tweak, i);
	      exit(0);
	    }
	  }
	  */
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
} // end compareXYZAgainstFourSortBT

void dflgmc(void **A, int N, int M, int depthLimit, int (*compareXY)());
void dflgm2(void **A, int N, int M, int (*compareXY)()) {
  // printf("dflgm2 N %i M %i\n", N, M);
  int L = M - N;
  int depthLimit = 2.9 * floor(log(L));
  dflgmc(A, N, M, depthLimit, compareXY);
} // end dflgm2

void dflgmc(void **A, int N, int M, int depthLimit, int (*compareXY)()) {
  // printf("dflgmc N %i M %i depthLimit %i\n", N, M, depthLimit);
  if ( depthLimit <= 0 ) {
    heapc(A, N, M, compareXY);
    return;
  }
  int L = M - N;
  if ( L < 50 ) { 
    quicksortmc(A, N, M, depthLimit, compareXY);
    return;
  }
  depthLimit--;
  /*
    int pn = N;
    int pm = M;
    int p0 = pn + L/2; // (pn+pm)/2;
    int d = L/8;
    pn = med(A, pn, pn + d, pn + 2 * d, compareXY);
    p0 = med(A, p0 - d, p0, p0 + d, compareXY);
    pm = med(A, pm - 2 * d, pm - d, pm, compareXY);
    p0 = med(A, pn, p0, pm, compareXY); // p0 is index to 'best' pivot ...
    dflgm(N, M, p0, dflgmc, depthLimit);
  */
        int sixth = (L + 1) / 6;
        int e1 = N  + sixth;
        int e5 = M - sixth;
        int e3 = N + (L>>1); // N + L/2; // (N+M) / 2; // The midpoint
        int e4 = e3 + sixth;
        int e2 = e3 - sixth;

        // Sort these elements using a 5-element sorting network ...
        void *ae1 = A[e1], *ae2 = A[e2], *ae3 = A[e3], *ae4 = A[e4], *ae5 = A[e5];
	void *t;
        // if (ae1 > ae2) { t = ae1; ae1 = ae2; ae2 = t; }
	if ( 0 < compareXY(ae1, ae2) ) { t = ae1; ae1 = ae2; ae2 = t; } // 1-2
	if ( 0 < compareXY(ae4, ae5) ) { t = ae4; ae4 = ae5; ae5 = t; } // 4-5
	if ( 0 < compareXY(ae1, ae3) ) { t = ae1; ae1 = ae3; ae3 = t; } // 1-3
	if ( 0 < compareXY(ae2, ae3) ) { t = ae2; ae2 = ae3; ae3 = t; } // 2-3
	if ( 0 < compareXY(ae1, ae4) ) { t = ae1; ae1 = ae4; ae4 = t; } // 1-4
	if ( 0 < compareXY(ae3, ae4) ) { t = ae3; ae3 = ae4; ae4 = t; } // 3-4
	if ( 0 < compareXY(ae2, ae5) ) { t = ae2; ae2 = ae5; ae5 = t; } // 2-5
	if ( 0 < compareXY(ae2, ae3) ) { t = ae2; ae2 = ae3; ae3 = t; } // 2-3
	if ( 0 < compareXY(ae4, ae5) ) { t = ae4; ae4 = ae5; ae5 = t; } // 4-5
	// ... and reassign
	A[e1] = ae1; A[e2] = ae2; A[e3] = ae3; A[e4] = ae4; A[e5] = ae5;

	// Fix end points
	if ( compareXY(ae1, A[N]) < 0 ) iswap(N, e1, A);
	if ( compareXY(A[M], ae5) < 0 ) iswap(M, e5, A);

	dflgm(A, N, M, e3, dflgmc, depthLimit, compareXY);

} // end dflgmc
 
// Terrible implementation of introsort!!!!
void introsort_r();
void insertion();

  // int a[], int n){
void introsort(void **A, int N, int M, int (*compare)()) {
  // introsort_r ( a, 0, n-1, (int(2*log(double(n)))));
  int L = M-N;
  int dp = 2.9 * floor(log(L));
  introsort_r(A, N, M, dp, compare);
  // _insertion(a, n);
  insertion(A, N, M, compare);
} // end introsort

// calculate the median of 3
int medi(void **A, int a, int b, int c,
	int (*compareXY ) (const void *, const void * ) ) {
  return
    compareXY( A[a], A[b] ) < 0 ?
    ( compareXY( A[b], A[c] ) < 0 ? b : compareXY( A[a], A[c] ) < 0 ? c : a)
    : compareXY( A[b], A[c] ) > 0 ? b : compareXY( A[a], A[c] ) > 0 ? c : a;
} // end medi


int partition();
void introsort_r(void **A, int first, int last, int depth, int (*compare)()) {
  while (last - first > 16 ) {
    // printf("introsort_r first %i last %i depth %i\n", first, last, depth);
    if (depth <=0 ) {
      // _heapsort(&a[first], first, last-first+1 );
      printf("HEAPSORT %i last %i depth %i\n", first, last, depth);
      heapc(A, first, last, compare);
      return;
    }
    else {
      depth--;
      int pivot; 
      int middle = 1 + first + (last - first)/2;
      int m = medi(A, first, middle, last, compare);
      pivot = partition(A, first, last, m, compare);
      introsort_r(A, pivot, last, depth, compare);
      last = pivot;
    }
  }
} // end introsort_r

int partition ( void **A, int first, int last, int m, int (*compare)() ) {
  // printf("partition first %i last %i m %i\n", first, last, m);
  int i= first; int j=last;  
  void **pi = A[m];
        while (1)  
        {  
	  // while (a[i].smaller(x)) i++;  
	  while ( compare(A[i], pi) < 0 ) i++;
	  /*
	    The "j--;" causes the last element of the segment to be miss allocated
	    in the partition.
	    Omitting "j--;" causes recursive calls on the same segment with constant 
	    data.  This triggers the invocation of heapsort on that segment
	   */
	  // j--; 
	  // while (x.smaller(a[j])) j=j-1;  
	  while ( compare(pi, A[j]) < 0 ) j--; 
	  if(!(i < j)) return i;  
	  // exchange(i,j);  
	  void **t = A[i]; A[i] = A[j]; A[j] = t;
	  i++;  
        }  
} // end partition

// void insertion ( int a[], int n ) {
void insertion ( void **A, int N, int M, int (*compare)()) {
  // printf("insertion N %i M %i\n", N, M);
  int i;
  //for ( i = 1; i < n; i++ ) {
  for ( i = N+1; i <= M; i++ ) {
    // int j, save = A[i];
    int j; void *save = A[i];
    // for ( j = i; j >= 1 && a[j - 1] > save; j-- )
    for ( j = i; j >= 1+N && compare(A[j-1], save) > 0; j-- )
      // a[j] = a[j - 1];
      A[j] = A[j - 1];
    // a[j] = save;
    A[j] = save;
  }
} // end insertion


/*
From:
    https://arxiv.org/pdf/1604.06697.pdf
    BlockQuicksort: How Branch Mispredictions don't affect Quicksort
    Stefan Edelkamp and Armin Weiss2
Original c++ code ported to C
*/

void callBlockSort(void **A, int size, 
	int (*compar ) (const void *, const void * ) ) {
  blockSort(A, 0, size-1, compar);
} // end callBlockSort

void iswap3(int p, int q, void **A) {
  void *t = A[p];
  A[p] = A[q];
  A[q] = t;
} // end of iswap3

void blockSortc();
const int BLOCKSIZE = 128;
void blockSort(void **A, int N, int M, int (*compar )) {
  int L = M-N;
  if (L <= 0) return;
  int dp = 2.9 * floor(log(L));
  int indexL[BLOCKSIZE], indexR[BLOCKSIZE];
  blockSortc(A, N, M, indexL, indexR, dp, compar);
}

void blockSortc(void **A, int N, int M, int indexL[], int indexR[],
	   int depthLimit, int (*compareXY)()) {
  int L;
 again:
  // printf("blockSortc N %i M %i d %i \n", N, M, depthLimit);
  L = M - N;
  // if ( L <= 0 ) return;
  if ( L <= 10 ) { 
    insertionsort(A, N, M, compareXY);
    return;
  }

  if ( depthLimit <= 0 ) {
    heapc(A, N, M, compareXY);
    return;
  }
  depthLimit--;

    // 10 < L
    // grab median of 3 or 9 to get a good pivot
    int pm = N + L/2; // (N+M)/2;
    int pl = N;
    int pn = M;
    if (L > 40) { // do median of 9
      int d = L/8;
      pl = medi(A, pl, pl + d, pl + 2 * d, compareXY);
      pm = medi(A, pm - d, pm, pm + d, compareXY);
      pn = medi(A, pn - 2 * d, pn - d, pn, compareXY);
    }
    pm = medi(A, pl, pm, pn, compareXY); // pm is index to 'best' pivot ...

    // iter last = end - 1 ;
    int last = M, begin = N;
    // std::iter_swap (pivot_position, last);
    iswap(pm, last, A);
    // const typename std::iterator_traits <iter >::value_type & pivot = *last;
    void *pivot = A[last];
    int pivot_position = last;
    last --;
    
    int num_left = 0;
    int num_right = 0;
    int start_left = 0;
    int start_right = 0;
    int num;
    int j; // for the for-loops 

    // main loop
    while (last - begin + 1 > 2 * BLOCKSIZE)
      { 
	// printf("BB blockSortc begin %i last %i pi %i\n", 
	//	 begin, last, pivot_position);

       //Compare and store in buffers
          if ( num_left == 0 ) {
              start_left = 0;
              for (j = 0; j < BLOCKSIZE; j++) {
                  indexL[num_left] = j;
                  // num_left += ( !( less( begin[j], pivot ) ) );
		  // num_left += ( !( less( A[begin+j], pivot ) ) );
		  // num_left += ( !( compareXY(A[begin+j], pivot) < 0 ) );
		  num_left += ( compareXY(A[begin+j], pivot) >= 0 );
              }
          }
          if ( num_right == 0 ) {
            start_right = 0;
            for (j = 0; j < BLOCKSIZE; j++) {
                indexR [ num_right ] = j;
                // num_right += ! ( less( pivot , *( last - j ) ) );
                // num_right += ! ( less( pivot , A[last-j] ) );
		// num_right += ! ( compareXY(pivot, A[last-j]) < 0 );
		num_right += ( compareXY(pivot, A[last-j]) >= 0 );
	    }
	  }
	  // rearrange elements
	  // num = std::min ( num_left , num_right );
	  int num = ( num_left <= num_right ? num_left : num_right );
	  for (j = 0; j < num; j++)
	    // std::iter_swap ( begin + indexL[start_left + j], 
	    //	                last - indexR[start_right + j] );
	    iswap3(begin + indexL[start_left + j], 
		  last - indexR[start_right + j], A);
  
        num_left -= num;
        num_right -= num;
        start_left += num;
        start_right += num;
        begin += ( num_left == 0 ) ? BLOCKSIZE : 0;
        last -= ( num_right == 0 ) ? BLOCKSIZE : 0;
  
        } // end main l o o p
  
	// printf("AA blockSortc N %i M %i\n", N, M);

        // printf("CC blockSortc begin %i last %i pi %i\n", 
        //        begin, last, pivot_position);


        // Compare and store in buffers final iteration
        int shiftR = 0, shiftL = 0;
        if ( num_right == 0 && num_left == 0 ) { 
            // for small arrays or in the unlikely
            // case that both buffers are empty
            shiftL = ((last - begin) + 1 ) / 2 ;
            shiftR = (last - begin) + 1 - shiftL;
            start_left = 0; start_right = 0;
            for (j = 0; j < shiftL; j++) {
                indexL[ num_left ] = j;
                // num_left += ( ! less( begin[j], pivot ) );
		num_left += ( compareXY(A[begin+j], pivot) >= 0 );
                indexR [ num_right ] = j;
                // num_right += ! less( pivot, *( last - j ) );
		num_right += ( compareXY(pivot, A[last-j]) >= 0 );
            }
            if ( shiftL < shiftR )
            {
                indexR [ num_right ] = shiftR - 1;
                // num_right += ! less( pivot, *( last - shiftR + 1 ) );
		num_right += ( compareXY(pivot, A[last - shiftR + 1]) >= 0 );
            }
         }
         else if ( num_right != 0 ) {
             shiftL = ( last - begin ) - BLOCKSIZE + 1;
             shiftR = BLOCKSIZE;
              start_left = 0;
              for (j = 0; j < shiftL; j++) {
                  indexL [ num_left ] = j;
                  // num_left += ( ! less( begin[ j ] , pivot ) );
		  num_left += ( compareXY(A[begin+j], pivot) >= 0 );
              }
         }
         else {
             shiftL = BLOCKSIZE;
             shiftR = ( last - begin) - BLOCKSIZE + 1;
             start_right = 0;
             for (j = 0; j < shiftR; j++) {
                indexR [ num_right ] = j;
                // num_right += ! ( less( pivot , *( last - j ) ) );
		num_right += ( compareXY(pivot, A[last - j]) >= 0 );
             }
         }
   
         // rearrange final iteration
         // num = std::min ( num_left , num_right );
	 num = ( num_left <= num_right ? num_left : num_right);
         for (j = 0; j < num; j++)
	   // std::iter_swap ( begin + indexL [ start_left + j ], 
	   //                  last - indexR [ start_right + j ] );
	   iswap3(begin + indexL [ start_left + j ],
		 last - indexR [ start_right + j ], A);
   
         num_left -= num;
         num_right -= num;
         start_left += num;
         start_right += num;
         begin += ( num_left == 0 ) ? shiftL : 0;
         last -= ( num_right == 0 ) ? shiftR : 0;
         // end final iteration
   
	 int pivotIndex;
        // rearrange elements remaining in buffer
        if ( num_left != 0 )
        {
            int lowerI = start_left + num_left - 1;
            int upper = last - begin;
            // search first element to be swapped
            while ( lowerI >= start_left && indexL [ lowerI ] == upper ) {
               upper--; lowerI--;
            }
            while ( lowerI >= start_left )
	      // std::iter_swap ( begin + upper--, begin + indexL [ lowerI--]);
	      iswap3(begin + upper--, begin + indexL [ lowerI--], A);
   
            // std::iter_swap ( pivot_position, begin + upper + 1 ); 
	    iswap3(pivot_position, begin + upper + 1, A);
	    // fetch the pivot
            // return begin + upper + 1;
	    pivotIndex = begin + upper + 1;
        }
        else if ( num_right != 0 ) {
	  int lowerI = start_right + num_right - 1 ;
	  int upper = last - begin;
	  // search first element to be swapped
	  while( lowerI >= start_right && indexR[ lowerI ] == upper ) {
	    upper--; lowerI--;
	  }
   
	  while (lowerI >= start_right )
	    // std::iter_swap(last - upper--, last - indexR[lowerI--]);
	    iswap3(last - upper--, last - indexR[lowerI--], A);
   
	  // std::iter_swap (pivot_position, last - upper ); 
	  iswap3(pivot_position, last - upper, A);
	  // fetch the pivot
	  // return last - upper;
	  pivotIndex = last - upper;
	}
        else { // no remaining elements
	  // std::iter_swap(pivot_position, begin); // fetch the pivot
	  iswap(pivot_position, begin, A);
	  // return begin;
	  pivotIndex = begin;
        }

	// Recurse on smallest segment first.
	depthLimit++;

	// printf("DD blockSortc begin %i last %i pi %i\n", 
	//        begin, last, pivotIndex);

	if ( pivotIndex - begin < last - pivotIndex ) {
	  blockSortc(A, N, pivotIndex-1, indexL, indexR, depthLimit, compareXY);
	  N = pivotIndex + 1;
	  goto again;
	}
	blockSortc(A, pivotIndex+1, M, indexL, indexR, depthLimit, compareXY);
	M = pivotIndex-1;
	goto again;

} // end blockSortc
   
