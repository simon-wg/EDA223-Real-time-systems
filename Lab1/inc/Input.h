#ifndef _INPUT_H
#define _INPUT_H

#include "TinyTimber.h"
#include <stdint.h>
#define INPUT_BUFFER_SIZE 10

typedef struct {
  Object super;
  char buf[INPUT_BUFFER_SIZE];
  unsigned char index;
  int history[3];
  int historyIndex;
} Input;

#define initInput() {initObject(), {}, 0, {0, 0, 0}, 0}

int clear(Input *, int);
int clearHistory(Input *, int);
int clearBuffer(Input *, int);
int appendBuffer(Input *, int);
int appendInt(Input *, int);
int getInt(Input *, int);
int getHistorySum(Input *, int);
int getHistoryMedian(Input *, int);

#endif
