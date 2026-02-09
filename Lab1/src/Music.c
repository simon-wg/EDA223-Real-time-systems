#include "Music.h"
#include "print.h"

const int MELODY[32] = {0, 2, 4, 0, 0, 2, 4, 0, 4, 5, 7, 4,  5, 7, 7,  9,
                        7, 5, 4, 0, 7, 9, 7, 5, 4, 0, 0, -5, 0, 0, -5, 0};

const int PERIOD[] = {2025, 1911, 1804, 1703, 1607, 1517, 1432, 1351, 1276,
                      1204, 1136, 1073, 1012, 956,  902,  851,  804,  758,
                      716,  676,  638,  602,  568,  536,  506};

int getPeriod(int semitone) {
  if (semitone < -10 || semitone > 14) {
    return 0;
  }
  return PERIOD[semitone + 10];
}

int toggleMute(Music *self, int unused) {
  self->muted ^= 1;
  return 0;
}

int toggleMusicDeadline(Music *self, int unused) {
  self->deadlineEnabled ^= 1;
  print("Toggling background deadline to: %d\n", self->deadlineEnabled);
  return 0;
}

int increaseVolume(Music *self, int unused) {
  if (self->volume < MAX_VOLUME) {
    self->volume++;
  }
  print("Raising volume to: %d\n", self->volume);
  return 0;
}

int decreaseVolume(Music *self, int unused) {
  if (self->volume > MIN_VOLUME) {
    self->volume--;
  }
  print("Decreasing volume to: %d\n", self->volume);
  return 0;
}

int play(Music *self, int period) {
  if (self->deadlineEnabled) {
    SEND(USEC(period), USEC(100), self, play, period);
  } else {
    AFTER(USEC(period), self, play, period);
  }
  if (self->muted) {
    return 0;
  }
  int current = READ_REG(DAC->DHR8R2);
  if (current == 0) {
    WRITE_REG(DAC->DHR8R2, self->volume);
  } else {
    WRITE_REG(DAC->DHR8R2, 0);
  }
  return 0;
}

// BELOW THIS IS ONLY FOR MEASUREMENT PURPOSES
#define MEASUREMENT_RUNS 5000

int playMusic(Music *self){
  Time start = CURRENT_OFFSET();
  if (self->deadlineEnabled) {
  } else {
  }
  if (self->muted) {
  }
  int current = READ_REG(DAC->DHR8R2);
  if (current == 0) {
    WRITE_REG(DAC->DHR8R2, self->volume);
  } else {
    WRITE_REG(DAC->DHR8R2, 0);
  }
  return CURRENT_OFFSET() - start;
}

int measurePlayMusic(Music *self, int unused) {
  Time totalTime = 0;
  Time maxTime = 0;
  for (int i = 0; i < MEASUREMENT_RUNS; i++) {
    Time time = playMusic(self);
    totalTime += time;
    if (time > maxTime) {
      maxTime = time;
    }
  };
  print("Background avg measurement: %d us\n", USEC(totalTime) / MEASUREMENT_RUNS);
  print("Background tot measurement: %d us\n", USEC(totalTime));
  print("Background max measurement: %d us\n", USEC(maxTime));
  return 0;
}
