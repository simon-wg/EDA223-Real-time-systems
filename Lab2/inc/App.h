#ifndef _APP_H
#define _APP_H

#include "TinyTimber.h"

typedef struct {
  Object super;
} App;

#define initApp() {initObject()}

int reader(App *, int);
int receiver(App *, int);
int startApp(App *, int);
int handleSerial(App *, int);

#endif
