/*
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

// File: c:/bsd/rigel/sort/ParFourSort.c
// Date: Thu Jan 07 15:08:48 2010
/* This file has the source of the algorithms that make up ParFourSort
   headed by foursort
*/
/* compile with: 
   gcc -c ParFourSort.c
   which produces:
   ParFourSort.o
   Compile & link with UseParFourSort:
   gcc UseParFourSort.c ParFourSort.o
*/
// To adjust restrictions: go to foursort(...) at the end of this file 


#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <math.h>

#define errexit(code,str)                          \
  fprintf(stderr,"%s: %s\n",(str),strerror(code)); \
  exit(1);

const int cut2PLimit = 127;

char* expiration = "*** License for foursort has expired ...\n";

// Here more global entities used throughout
int (*compareXY)();
void **A;
int sleepingThreads = 0;
int NUMTHREADS;

// the members of ParFourSort
#include "Isort"
#include "Hsort"
#include "Qusort"
#include "Dsort"


void cut2Pc();
// cut2P is a support function to call up the workhorse cut2Pc
void cut2P(int N, int M) { 
  // printf("cut2P %d %d \n", N, M);
  int L = M - N;
  if ( L < cut2PLimit ) { 
    quicksort0(N, M);
    return;
  }
  int depthLimit = 2 * floor(log(L));
  cut2Pc(N, M, depthLimit);
} // end cut2P

struct stack *ll;
struct task * newTask();
void addTaskSynchronized();

void cut2Pc(int N, int M, int depthLimit) {
  int L;
  Start:
  if ( depthLimit <= 0 ) {
    heapc(A, N, M);
    return;
  }
  L = M - N;
  if ( L < cut2PLimit ) { 
    quicksort0c(N, M, depthLimit);
    return;
  }

  depthLimit--;

  // Check for duplicates
        int sixth = (L + 1) / 6;
        int e1 = N  + sixth;
        int e5 = M - sixth;
        int e3 = (N+M) / 2; // The midpoint
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

	register void *T = ae3; // pivot

	// check Left label invariant
	// if ( T <= A[N] || A[M] < T ) {
	if ( compareXY(T, A[N]) <= 0 || compareXY(A[M], T) < 0) {
	   // give up because cannot find a good pivot
	   // dflgm is a dutch flag type of algorithm
	   void cut2Pc();
	   dflgm(N, M, e3, cut2Pc, depthLimit);
	   return;
	 }

	register int I, J; // indices
	register void *AI, *AJ; // array values


	// initialize running indices
	I= N;
	J= M;

	// The left segment has elements < T
	// The right segment has elements >= T
  Left:
	// I = I + 1;
	// AI = A[I];
	// if (AI < T) goto Left;
	// if ( compareXY(AI,  T) < 0 ) goto Left;
	while ( compareXY(A[++I],  T) < 0 ); AI = A[I];
  Right:
	// J = J - 1;
	// AJ = A[J];
	// if ( T <= AJ ) goto Right;
	// if ( compareXY(T, AJ) <= 0 ) goto Right;
	while ( compareXY(T, A[--J]) <= 0 ); AJ = A[J];
	if ( I < J ) {
	  A[I] = AJ; A[J] = AI;
	  goto Left;
	}
	// Tail iteration  
  	 if ( (I - N) < (M - J) ) { // smallest one first
	   // cut2Pc(N, J, depthLimit);
	   // N = I; 
	   addTaskSynchronized(ll, newTask(I, M, depthLimit));
	   M = J;
	   goto Start;
	 }
	 // cut2Pc(I, M, depthLimit);
	 // M = J;
	 addTaskSynchronized(ll, newTask(N, J, depthLimit));
	 N = I;
	 goto Start;
} // (*  OF cut2P; *) ... the brackets reminds that this was Pascal code


void *myMallocSS(char* location, int size) {
  void *p = malloc(size);
  if ( 0 == p ) {
    fprintf(stderr, "malloc fails for: %s\n", location);
    // printf("Cannot allocate memory in: %s\n", location);
    exit(1);
  }
  return p;
} // end of myMalloc

/* Infrastructure for the parallel equipment:
  To obtain the int n field from X: ((struct task *) X)->n
  To obtain the int m field from X: ((struct task *) X)->m
  To obtain the task next field from X: ((struct task *) X)->next
  */
struct task {
  int n;
  int m;
  int dl;
  struct task *next;
};
int getN(struct task *t) { return ((struct task *) t)->n; }
int getM(struct task *t) { return ((struct task *) t)->m; }
int getDL(struct task *t) { return ((struct task *) t)->dl; }
struct task *getNext(struct task *t) { return ((struct task *) t)->next; }

void setN(struct task *t, int n) { ((struct task *) t)->n = n; }
void setM(struct task *t, int m) { ((struct task *) t)->m = m; }
void setDL(struct task *t, int dl) { ((struct task *) t)->dl = dl; }
void setNext(struct task *t, struct task* tn) { 
  ((struct task *) t)->next = tn; }
struct task *newTask(int N, int M, int depthLimit) {
  struct task *t = (struct task *) 
    myMallocSS("ParFourSort/ newTask()", sizeof (struct task));
  setN(t, N); setM(t, M); setDL(t, depthLimit); setNext(t, NULL);
  return t;
} // end newTask

struct stack {
  struct task *first;
  int size;
};
struct task *getFirst(struct stack *ll) { 
  return ((struct stack *) ll)->first; }
int getSize(struct stack *ll) { 
  return ((struct stack *) ll)->size; }
void setFirst(struct stack *ll, struct task *t) { 
  ((struct stack *) ll)->first = t; }
void setSize(struct stack *ll, int s) { 
  ((struct stack *) ll)->size = s; }
void incrementSize(struct stack *ll) { 
  setSize(ll, getSize(ll) + 1); }
void decrementSize(struct stack *ll) { 
  setSize(ll, getSize(ll) - 1); }
struct stack *newStack() {
  struct stack *ll = (struct stack *)
    myMallocSS("ParFourSort/ newStack()", sizeof (struct stack));
  setFirst(ll, NULL); setSize(ll, 0);
  return ll;
} // end newStack
int isEmpty(struct stack *ll) { 
  return ( NULL == getFirst(ll) ); 
} // end isEmpty
struct task *pop(struct stack *ll) {
  struct task *t = getFirst(ll);
  if ( NULL == t ) return NULL;
  setFirst(ll, getNext(t));
  decrementSize(ll);
  return t;
} // end pop
void push(struct stack *ll, struct task *t) {
  if ( !isEmpty(ll) ) setNext(t, getFirst(ll)); 
  setFirst(ll, t);
  incrementSize(ll);
} // end push


pthread_mutex_t condition_mutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  condition_cond2  = PTHREAD_COND_INITIALIZER;


void addTaskSynchronized(struct stack *ll, struct task *t) {
  /*
  printf("Thread#: %ld ", pthread_self());
  printf("addTask N: %d M: %d sleepingThreads: %d\n", 
	 getN(t), getM(t), sleepingThreads);
  */
  pthread_mutex_lock( &condition_mutex2 );
  push(ll, t);
  pthread_cond_signal( &condition_cond2 );
  pthread_mutex_unlock( &condition_mutex2 );
} // end addTaskSynchronized

// threads execute sortThread
void *sortThread(void *A) { // A-argument is NOT used
  // int taskCnt = 0;
  //  printf("Thread number: %ld #sleepers %d\n", 
  //         pthread_self(), sleepingThreads);
  struct task *t = NULL;
  for (;;) {
    pthread_mutex_lock( &condition_mutex2 );
       sleepingThreads++;
       while ( NULL == ( t = pop(ll) ) && 
	       sleepingThreads < NUMTHREADS ) {
	 pthread_cond_wait( &condition_cond2, &condition_mutex2 );
       }
       if ( NULL != t ) sleepingThreads--;
    pthread_mutex_unlock( &condition_mutex2 );
    if ( NULL == t ) { 
      pthread_mutex_lock( &condition_mutex2 );
      pthread_cond_signal( &condition_cond2 );
      pthread_mutex_unlock( &condition_mutex2 );
      break;
    }
    int n = getN(t);
    int m = getM(t);
    int depthLimit = getDL(t);
    free(t);
    // taskCnt++;
    cut2Pc(n, m, depthLimit);
  }

  //  printf("Exit of Thread number: %ld taskCnt: %d\n", pthread_self(), taskCnt);
  return NULL;
} // end sortThread

int cut2S2Limit = 2000;
void foursort(void **AA, int size, 
	int (*compar ) (const void *, const void * ),
	int numberOfThreads) {
  /*
  // Set host & licence expiration date
  char* myHost = "ddc2";
  int year = 2010;
  int month = 11; // December = 11
  int day = 31;
  // show allowed host and licence expiration date
  if ( 0 == AA ) {
    printf("Licence expires: %d / %d / %d\n", year, month+1, day);
    printf("Host: %s\n", myHost);
    exit(0);
  }
  // Check whether licence expired
  time_t now = time(NULL);
  struct tm *laterx = localtime(&now);
  laterx->tm_year = year-1900; // = 2010
  laterx->tm_mon = month;
  laterx->tm_mday = day;
  time_t endTime = mktime(laterx);
  if ( endTime < now ) {
     printf(expiration);
     exit(1);
  }
  // Check whether this host is allowed
  int nameLng = 100;
  char hostName[nameLng];
  int out = gethostname(hostName, nameLng);
  if ( 0 != out ) {
    printf("*** Error: cannot get: Host name\n");
    exit(1);
  }
  out = strcmp(myHost, hostName);
  if ( 0 != out ) {
    printf("*** Error: not allowed host\n");
    exit(1);
  }
  */
  // Proceed !
  A = AA;
  compareXY = compar;
  if ( size <= cut2S2Limit || numberOfThreads <= 0) {
    quicksort0(0, size-1);
    return;
  }
  sleepingThreads = 0;
  NUMTHREADS = numberOfThreads;
  // printf("Entering sortArray\n");
  ll = newStack();
  int depthLimit = 2 * floor(log(size));
  struct task *t = newTask(0, size-1, depthLimit);
  addTaskSynchronized(ll, t);

  pthread_t thread_id[NUMTHREADS];
  int i;
  int errcode;
  for ( i = 0; i < NUMTHREADS; i++ ) {
    if ( errcode=pthread_create(&thread_id[i], NULL, 
				sortThread, (void*) A) ) {
      errexit(errcode,"ParSort/ sortArray()/pthread_create");
    }
  }

  for ( i = 0; i < NUMTHREADS; i++ ) {
    if ( errcode=pthread_join(thread_id[i], NULL) ) {
      errexit(errcode,"ParSort/ sortArray()/pthread_join");
    }
  }
  free(ll);
  // printf("Exiting sortArray\n");

} // end foursort
/* compile with: 
   gcc -c ParFourSort.c
   which produces:
   ParFourSort.o
   Compile & link with UseParFourSort:
   gcc UseParFourSort.c ParFourSort.o
*/
