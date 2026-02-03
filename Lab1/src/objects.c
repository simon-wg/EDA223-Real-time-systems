#include "App.h"
#include "Input.h"
#include "Music.h"
#include "canTinyTimber.h"
#include "sciTinyTimber.h"

#define UNUSED 0

App app = initApp();
Input input = initInput();
MusicPlayer musicPlayer = initMusicPlayer(5);
Can can0 = initCan(CAN_PORT0, &app, receiver);
Serial sci0 = initSerial(SCI_PORT0, &app, reader);
