#ifndef Cockpit_h
#define Cockpit_h
#include "Arduino.h"
#include <Bluepad32.h>
class Cockpit {
  public:
    /* public methods */
    Cockpit();
    void prepare();
    void operate();
    bool isOperational();

    /* public static methods */
    static void onConnectedGamepad(GamepadPtr gp);
    static void onDisconnectedGamepad(GamepadPtr gp);

    /* public static variables */
    static void* objectPtr;
  private:
    /* private variables of this class */
    bool operational;
    GamepadPtr myGamepads[BP32_MAX_GAMEPADS];
};
#endif
