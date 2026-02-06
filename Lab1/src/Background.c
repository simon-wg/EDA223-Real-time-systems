#include "Background.h"
#include "print.h"

#define LOAD_INCREMENT 500
#define BACKGROUND_PERIOD USEC(1300)

int loop(Background *self, int unused) {
  if (self->deadlineEnabled) {
    SEND(BACKGROUND_PERIOD, BACKGROUND_PERIOD, self, loop, NULL);
  } else {
    AFTER(BACKGROUND_PERIOD, self, loop, NULL);
  }
  for (int i = 0; i < self->background_loop_range; i++) {
  };
  return 0;
}

int toggleBackgroundDeadline(Background *self, int unused) {
  self->deadlineEnabled ^= 1;
  print("Toggling background deadline to: %d\n", self->deadlineEnabled);
  return 0;
}

int increaseLoad(Background *self, int unused) {
  self->background_loop_range += LOAD_INCREMENT;
  print("Increasing background load to: %d\n", self->background_loop_range);
  return 0;
}

int decreaseLoad(Background *self, int unused) {
  self->background_loop_range -= LOAD_INCREMENT;
  print("Decreasing background load to: %d\n", self->background_loop_range);
  return 0;
}
