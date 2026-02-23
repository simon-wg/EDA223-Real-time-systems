#ifndef _APP_H
#define _APP_H

#include "TinyTimber.h"

#define INPUT_BUFFER_SIZE 10

typedef struct {
  Object super;
  char buf[INPUT_BUFFER_SIZE];
  unsigned char index;
  unsigned char conductor;
} App;

#define initApp() {initObject(), {0}, 0, 1}

int reader(App *, int);
int receiver(App *, int);
int startApp(App *, int);
int handleSerial(App *, int);
int handleCan(App *, int);
int handleKey(App *, int);
int sendCan(App *, int);
int clearBuffer(App *, int);
int appendBuffer(App *, int);

int getInt(App *);

#endif
