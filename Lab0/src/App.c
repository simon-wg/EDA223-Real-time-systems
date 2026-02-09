#include "App.h"
#include "TinyTimber.h"
#include "canTinyTimber.h"
#include "music.h"
#include "print.h"
#include "sciTinyTimber.h"
#include <stdlib.h>
#include <sys/param.h>

extern App app;
extern Can can0;
extern Serial sci0;

void receiver(App *self, int unused) {
  CANMsg msg;
  CAN_RECEIVE(&can0, &msg);
  SCI_WRITE(&sci0, "Can msg received: ");
  SCI_WRITE(&sci0, msg.buff);
}

void reader(App *self, int c) {
  SCI_WRITE(&sci0, "Rcv: \'");
  SCI_WRITECHAR(&sci0, c);
  SCI_WRITE(&sci0, "\'\n");
  handleSerial(self, c);
}

void startApp(App *self, int arg) {
  CANMsg msg;

  CAN_INIT(&can0);
  SCI_INIT(&sci0);
  SCI_WRITE(&sci0, "Hello, hello...\n");

  msg.msgId = 1;
  msg.nodeId = 1;
  msg.length = 6;
  msg.buff[0] = 'H';
  msg.buff[1] = 'e';
  msg.buff[2] = 'l';
  msg.buff[3] = 'l';
  msg.buff[4] = 'o';
  msg.buff[5] = 0;
  CAN_SEND(&can0, &msg);
}

int main() {
  INSTALL(&sci0, sci_interrupt, SCI_IRQ0);
  INSTALL(&can0, can_interrupt, CAN_IRQ0);
  TINYTIMBER(&app, startApp, 0);
  return 0;
}

void handleSerial(App *self, int c) {
  int n;
  switch (c) {
  case 'F':
    self->bufIndex = 0;
    self->historyIndex = 0;
    print("History and buffer cleared.\n");
    break;
  case 'e':
    n = getInt(self);
    self->history[2] = self->history[1];
    self->history[1] = self->history[0];
    self->history[0] = n;
    self->historyIndex = MIN(self->historyIndex + 1, 3);
    print("Entered integer %d: sum = %d, median = %d\n", self->history[0],
          getHistorySum(self), getHistoryMedian(self));
    break;
  case 'p':
    n = getInt(self);
    print("Key: %d\n", n);
    for (int i = 0; i < 32; ++i) {
      print("%d ", getPeriod(n + MELODY[i]));
    }
    print("\n");
    break;
  default:
    self->buf[self->bufIndex++] = (char)c;
    break;
  }
}

int getInt(App *self) {
  self->buf[self->bufIndex] = '\0';
  self->bufIndex = 0;
  return atoi(self->buf);
}

int getHistorySum(App *self) {
  int sum = 0;
  for (int i = 0; i < self->historyIndex; ++i) {
    sum += self->history[i];
  }
  return sum;
}

int compareInt(const void *a, const void *b) { return (*(int *)a - *(int *)b); }

int getHistoryMedian(App *self) {
  int tmp[3] = {self->history[0], self->history[1], self->history[2]};
  qsort(tmp, self->historyIndex, sizeof(int), compareInt);
  if (self->historyIndex == 2) {
    return (tmp[0] + tmp[1]) / 2;
  }
  return tmp[self->historyIndex / 2];
}
