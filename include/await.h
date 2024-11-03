#ifndef AWAIT_H
#define AWAIT_H
// The one and only self titled AWAIT aka COROUTINES that I sailed the waves to find
// Found from some legend at reddit
// Credit to u/jwzumwalt

#include <stdio.h>
#include <time.h>

void delaySec(unsigned int iNumSecs) {   // pass number of seconds to delay
  // Convert time to iMilliSecs
  int iMilliSecs = 1000 * iNumSecs;
  
  // store start time
  clock_t start_time = clock();
  
  // loop until required time
  while (clock() < start_time + iMilliSecs);
  return;
}

void delayMilli(unsigned int iMilliSecs) {   // pass num of milli-secs to delay
  // store start time
  clock_t start_time = clock();
  
  // loop until required time
  while (clock() < start_time + iMilliSecs);
  return;
}

void delay(unsigned int iMilliSecs) {      // default delay
  delayMilli(iMilliSecs);
  return;
}

void sleep(unsigned int iMilliSecs) {      // default delay
  delayMilli(iMilliSecs);
  return;
}
#endif // AWAIT_H