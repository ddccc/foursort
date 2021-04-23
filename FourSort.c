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

// File: c:/bsd/rigel/sort/FourSort.c
// Date: Thu Jan 07 15:08:48 2010
/* This file has the source of the algorithms that make up FourSort
   headed by foursort
*/
/* compile with: 
   gcc -c FourSort.c
   which produces:
   FourSort.o
   Compile & link with UseFourSort:
   gcc UseFourSort.c FourSort.o
*/
// To adjust restrictions: go to foursort(...) at the end of this file 


#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

// const int cut2Limit = 127;

char* expiration = "*** License for foursort has expired ...\n";

// Here more global entities used throughout
// int (*compareXY)();
// void **A;

// the members of FourSort
// /*
#include "Isort.c"
#include "Hsort.c"
#include "Dsort.c"  // dflgm member
// */

#include "Qusort.c" // quicksort member
// #include "D3sort.c" // dflgm3
#include "C2sort.c" // cut2 member

void foursort(void **AA, int size, 
	int (*compar ) (const void *, const void * ) ) {
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
  // A = AA;
  // compareXY = compar;
  cut2(AA, 0, size-1, compar);
}
/* compile with: 
   gcc -c FourSort.c
   which produces:
   FourSort.o
   Compile & link with UseFourSort:
   gcc UseFourSort.c FourSort.o
*/
