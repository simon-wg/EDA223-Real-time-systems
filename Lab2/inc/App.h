#ifndef _APP_H
#define _APP_H

#include "TinyTimber.h"

#define INPUT_BUFFER_SIZE 10

typedef struct {
  Object super;
  char buf[INPUT_BUFFER_SIZE];
  unsigned char index;
} App;

#define initApp() {initObject()}

int reader(App *, int);
int receiver(App *, int);
int startApp(App *, int);
int handleSerial(App *, int);
int clearBuffer(App *, int);
int appendBuffer(App *, int);

int getInt(App *);

#endif
