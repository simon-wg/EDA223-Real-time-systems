#ifndef _APP_H
#define _APP_H

#include "TinyTimber.h"

typedef struct {
  Object super;
  int history[3];
  char historyIndex;
  char buf[10];
  char bufIndex;
} App;

#define initApp() {initObject(), initHistory(), 0, initBuf(), 0}
#define initHistory() {0, 0, 0}
#define initBuf() {0}

void reader(App *, int);
void receiver(App *, int);
void startApp(App *, int);
void handleSerial(App *self, int);
void toggleDac(App *self, int);
int getHistorySum(App *self);
int getHistoryMedian(App *self);
int getInt(App *self);

#endif
