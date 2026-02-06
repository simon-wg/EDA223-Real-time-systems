#ifndef _BACKGROUND_H
#define _BACKGROUND_H
#include "TinyTimber.h"

typedef struct {
  Object super;
  int background_loop_range; // This is not voluntarily named using snake case
  unsigned char deadlineEnabled;
} Background;

#define initBackground() {initObject(), 1000, 1};

int loop(Background *, int);
int toggleBackgroundDeadline(Background *, int);
int increaseLoad(Background *, int);
int decreaseLoad(Background *, int);

#endif
