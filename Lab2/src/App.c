#include "App.h"
#include "MusicPlayer.h"
#include "ToneGenerator.h"
#include "TinyTimber.h"
#include "canTinyTimber.h"
#include "print.h"
#include "sciTinyTimber.h"
#include <stdlib.h>

extern App app;
extern ToneGenerator toneGenerator;
extern MusicPlayer musicPlayer;
extern Can can0;
extern Serial sci0;

int receiver(App *self, int unused) {
  CANMsg msg;
  CAN_RECEIVE(&can0, &msg);
  SCI_WRITE(&sci0, "Can msg received: ");
  SCI_WRITE(&sci0, msg.buff);
  return 0;
}

int reader(App *self, int c) {
  ASYNC(self, handleSerial, c);
  return 0;
}

int startApp(App *self, int arg) {
  // CANMsg msg;

  CAN_INIT(&can0);
  SCI_INIT(&sci0);

  ASYNC(&musicPlayer, playTone, 0);

  // msg.msgId = 1;
  // msg.nodeId = 1;
  // msg.length = 6;
  // msg.buff[0] = 'H';
  // msg.buff[1] = 'e';
  // msg.buff[2] = 'l';
  // msg.buff[3] = 'l';
  // msg.buff[4] = 'o';
  // msg.buff[5] = 0;
  // CAN_SEND(&can0, &msg);
  print("Hello world!\n");
  return 0;
}

int main() {
  INSTALL(&sci0, sci_interrupt, SCI_IRQ0);
  INSTALL(&can0, can_interrupt, CAN_IRQ0);
  TINYTIMBER(&app, startApp, NULL);
  return 0;
}

int handleSerial(App *self, int c) {
  int n;
  uint8_t volume;
  print("Rcv: '%c'\n", c);
  switch (c) {
  case 'F':
    ASYNC(self, clearBuffer, 0);
    return 0;
  case 'm':
    ASYNC(&toneGenerator, toggleMute, NULL);
    return 0;
  case 'i':
    volume = SYNC(&toneGenerator, getVolume, NULL);
    ASYNC(&toneGenerator, setVolume, volume + 1);
    return 0;
  case 'u':
    volume = SYNC(&toneGenerator, getVolume, NULL);
    ASYNC(&toneGenerator, setVolume, volume - 1);
    return 0;
  case 't':
    n = getInt(self);
    ASYNC(&musicPlayer, setTempo, n);
    return 0;
  case 'k':
    n = getInt(self);
    ASYNC(&musicPlayer, setKey, n);
    return 0;
  default:
    ASYNC(self, appendBuffer, c);
    return 0;
  }
}

int clearBuffer(App *self, int unused) {
  self->index = 0;
  return 0;
}

int appendBuffer(App *self, int c) {
  if (self->index >= INPUT_BUFFER_SIZE) {
    self->index = INPUT_BUFFER_SIZE;
    return 0;
  }
  self->buf[self->index++] = c;
  return 0;
}

int getInt(App *self) {
  char strBuf[INPUT_BUFFER_SIZE + 1];
  for (int i = 0; i < self->index; i++) {
    strBuf[i] = (char)self->buf[i];
  }
  strBuf[self->index] = '\0';
  self->index = 0;
  return atoi(strBuf);
}
