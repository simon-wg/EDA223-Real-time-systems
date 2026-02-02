#include "App.h"
#include "TinyTimber.h"
#include "print.h"
#include "sciTinyTimber.h"
#include <stdlib.h>

extern App app;
extern Serial sci0;

void reader(App *self, int c) {
  switch (c) {
  case 'e':
    self->buffer[self->index] = '\0';
    print("Integer is %d", atoi(self->buffer));
  }
  SCI_WRITE(&sci0, "Rcv: \'");
  SCI_WRITECHAR(&sci0, c);
  SCI_WRITE(&sci0, "\'\n");
}

void startApp(App *self, int arg) {
  SCI_INIT(&sci0);
  SCI_WRITE(&sci0, "Hello, hello...\n");
}

int main() {
  INSTALL(&sci0, sci_interrupt, SCI_IRQ0);
  TINYTIMBER(&app, startApp, 0);
  return 0;
}
