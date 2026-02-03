#include "Input.h"
#include "TinyTimber.h"
#include "print.h"
#include <stdlib.h>
#include <sys/param.h>

int clear(Input *self, int unused) {
  ASYNC(self, clearBuffer, 0);
  ASYNC(self, clearHistory, 0);
  print("History and buffer cleared.\n");
  return 0;
}
int clearBuffer(Input *self, int unused) {
  self->index = 0;
  return 0;
}
int clearHistory(Input *self, int unused) {
  self->historyIndex = 0;
  return 0;
}

int appendBuffer(Input *self, int c) {
  if (self->index >= INPUT_BUFFER_SIZE) {
    self->index = INPUT_BUFFER_SIZE;
    return 0;
  }
  self->buf[self->index++] = c;
  return 0;
}

int appendInt(Input *self, int unused) {
  int n = getInt(self, 0);
  self->history[2] = self->history[1];
  self->history[1] = self->history[0];
  self->history[0] = n;
  self->historyIndex = MIN(self->historyIndex + 1, 3);
  // TODO: Make sure this works on baremetal
  print("Entered integer %d: sum = %d, median = %d\n", n,
        getHistorySum(self, 0), getHistoryMedian(self, 0));
  return 0;
}

int getInt(Input *self, int unused) {
  char strBuf[INPUT_BUFFER_SIZE + 1];
  for (int i = 0; i < self->index; i++) {
    strBuf[i] = (char)self->buf[i];
  }
  strBuf[self->index] = '\0';
  self->index = 0;
  return atoi(strBuf);
}

int getHistorySum(Input *self, int unused) {
  int sum = 0;
  for (int i = 0; i < self->historyIndex; ++i) {
    sum += self->history[i];
  }
  return sum;
}

int compareInt(const void *a, const void *b) { return (*(int *)a - *(int *)b); }

int getHistoryMedian(Input *self, int unused) {
  int tmp[3] = {self->history[0], self->history[1], self->history[2]};
  qsort(tmp, self->historyIndex, sizeof(int), compareInt);
  return tmp[self->historyIndex / 2];
}
