// File: c:/bsd/rigel/sort/Isort
// Date: Thu Jan 30 21:54:12 2014
// (C) OntoOO/ Dennis de Champeaux



// int compareXY (const void *a, const void *b);
// if (a<b) then -1 else if a=b then 0 else 1 

// insertionsort for small segments where the loop has been unrolled
void insertionsort(void **A, int N, int M, int (*compareXY)()) {
  if ( M <= N ) return;
  // M <= N + 10 
  register int i, s;
  // put minimum element at index N
  int minimumPosition;
  void *minimum, *next, *ai;
  minimumPosition = N;
  minimum = A[N];
  for ( i = N+1; i <= M; i++ ) {
    ai = A[i];
    // if ( ai < minimum ) {
    if ( compareXY(ai, minimum) < 0 ) {
      minimum = ai;
      minimumPosition = i;
    }
  }
  if ( N != minimumPosition ) {
    A[minimumPosition] = A[N];
    A[N] = minimum;
  }
  // now push elements back to their proper location
  s = N+1;
  while ( s < M ) { // if ( M == s ) return;
    s=s+1;
    next=A[s];
    ai = A[s-1];
    // if ( ai <= next ) continue;
    if ( compareXY(ai, next) <= 0 ) continue;
    A[s] = ai;
    ai = A[s-2];
    if ( compareXY(ai, next) <= 0 ) { A[s-1] = next; continue; }
    A[s-1] = ai;
    ai = A[s-3];
    if ( compareXY(ai, next) <= 0 ) { A[s-2] = next; continue; }
    A[s-2] = ai;
    ai = A[s-4];
    if ( compareXY(ai, next) <= 0 ) { A[s-3] = next; continue; }
    A[s-3] = ai;
    ai = A[s-5];
    if ( compareXY(ai, next) <= 0 ) { A[s-4] = next; continue; }
    A[s-4] = ai;
    ai = A[s-6];
    if ( compareXY(ai, next) <= 0 ) { A[s-5] = next; continue; }
    A[s-5] = ai;
    ai = A[s-7];
    if ( compareXY(ai, next) <= 0 ) { A[s-6] = next; continue; }
    A[s-6] = ai;
    ai = A[s-8];
    if ( compareXY(ai, next) <= 0 ) { A[s-7] = next; continue; }
    A[s-7] = ai;
    ai = A[s-9];
    if ( compareXY(ai, next) <= 0 ) { A[s-8] = next; continue; }
    A[s-8] = ai;
    ai = A[s-10];
    if ( compareXY(ai, next) <= 0 ) { A[s-9] = next; continue; }
    A[s-9] = ai;
    ai = A[s-11];
    if ( compareXY(ai, next) <= 0 ) { A[s-10] = next; continue; }
    A[s-10] = ai;
    ai = A[s-12];
    if ( compareXY(ai, next) <= 0 ) { A[s-11] = next; continue; }
    fprintf(stderr, "SixSort/ insertionsort() ");
    fprintf(stderr, "N: %d M %d s: %i\n", N, M, s);
    exit(1);
  }
  return;
} // end insertionsort