#include "App.h"
#include "Input.h"
#include "Music.h"
#include "TinyTimber.h"
#include "canTinyTimber.h"
#include "print.h"
#include "sciTinyTimber.h"

extern App app;
extern Input input;
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

  ASYNC(&musicPlayer, play, 500);
  // SCI_WRITE(&sci0, "Hello, hello...\n");

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
  return 0;
}

int main() {
  INSTALL(&sci0, sci_interrupt, SCI_IRQ0);
  INSTALL(&can0, can_interrupt, CAN_IRQ0);
  TINYTIMBER(&app, startApp, 0);
  return 0;
}

int handleSerial(App *self, int c) {
  int n;
  print("Rcv: '%c'\n", c);
  switch (c) {
  case 'F':
    ASYNC(&input, clear, 0);
    return 0;
  case 'e':
    ASYNC(&input, appendInt, 0);
    return 0;
  case 'p':
    n = SYNC(&input, getInt, 0);
    print("Key: %d\n", n);
    for (int i = 0; i < 32; ++i) {
      print("%d ", getPeriod(n + MELODY[i]));
    }
    print("\n");
    return 0;
  default:
    ASYNC(&input, appendBuffer, c);
    return 0;
  }
}
