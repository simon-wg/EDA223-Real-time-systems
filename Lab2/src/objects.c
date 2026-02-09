#include "App.h"
#include "Background.h"
#include "Input.h"
#include "Music.h"
#include "canTinyTimber.h"
#include "sciTinyTimber.h"

App app = initApp();
Background background = initBackground();
Input input = initInput();
Music music = initMusic(5);
Can can0 = initCan(CAN_PORT0, &app, receiver);
Serial sci0 = initSerial(SCI_PORT0, &app, reader);
