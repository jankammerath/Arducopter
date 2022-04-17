#include "Arduino.h"
#include "Cockpit.h"
#include <Bluepad32.h>

/* define the static ptr to the instance */
void* Cockpit::objectPtr;

/**
 * Constructs the cockpit and initialises
 * the local variables that define the state
 * of the cockpit
 */
Cockpit::Cockpit(){
  this->operational = false;
  Cockpit::objectPtr = this;
}

/**
 * Returns true when the cockpit is operational
 * and false if it is not yet operational
 */
bool Cockpit::isOperational(){
  return this->operational;  
}

/**
 * Handles the connected event of the
 * gamepad and configured the cockpit
 * to be operational
 * 
 * @param {GamepadPtr} gp
 * pointer to the gamepad instance
 */
void Cockpit::onConnectedGamepad(GamepadPtr gp) {
  Serial.println("Gamepad connect event.");
  
  bool foundEmptySlot = false;
  for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
    if (((Cockpit*)Cockpit::objectPtr)->myGamepads[i] == nullptr) {
      Serial.print("Gamepad is connected, index#");
      Serial.println(i);

      /* set the gamepad ptr locally */
      ((Cockpit*)Cockpit::objectPtr)->myGamepads[i] = gp;
      foundEmptySlot = true;

      /* set the cockpit to operational */
      ((Cockpit*)Cockpit::objectPtr)->operational = true;
      break;
    }
  }

  /* log an error when no empty slot was found */
  if (!foundEmptySlot) {
      Serial.println("Gamepad connected, unable to find empty slot.");
  }
  
}

/**
 * Handles the disconnected event of the
 * gamepad and resets the cockpit operations
 * status to not operational
 * 
 * @param {GamepadPtr} gp
 * pointer to the gamepad instance
 */
void Cockpit::onDisconnectedGamepad(GamepadPtr gp) {
  Serial.println("Gamepad disconnect event.");
  
  bool foundGamepad = false;
  for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
    if (((Cockpit*)Cockpit::objectPtr)->myGamepads[i] == gp) {
      /* log the disconnect event */
      Serial.print("Gamepad is disconnected, index#");
      Serial.println(i);
      ((Cockpit*)Cockpit::objectPtr)->myGamepads[i] = nullptr;
      foundGamepad = true;
      ((Cockpit*)Cockpit::objectPtr)->operational = false;
      break;
    }
  }
  
  if (!foundGamepad) {
    Serial.println("Gamepad disconnected, but not found in myGamepads");
  }
}

/**
 * Prepares the cockpit for operation by
 * connecting all controls (PS4 controller)
 */
void Cockpit::prepare(){
  /* log the firmware version of BP32 */
  String fv = BP32.firmwareVersion();
  Serial.print("BP32/Gamepad-Firmware: ");
  Serial.println(fv);

  /* setup the callbacks for the gamepad events */
  BP32.setup(Cockpit::onConnectedGamepad,Cockpit::onDisconnectedGamepad);
}

/**
 * Operates the cockpit reading the information
 * from the flight controller and storing it
 * locally for reading from other objects
 */
void Cockpit::operate(){
  if(this->operational == true){
    /* read the flight controls by fetching the
        gamepad information from the NINA module */
    BP32.update();

    /* iterate through the gamepads and read them */
    for(int i=0; i<BP32_MAX_GAMEPADS; i++) {
      GamepadPtr myGamepad = this->myGamepads[i];
      if(myGamepad && myGamepad->isConnected()){
        if (myGamepad->a()){
          /* set the color of the gamepad to red */
          myGamepad->setColorLED(255, 0, 0);
        }    

        /* log the button and joystick positions */
        char buffer[120];
        snprintf(buffer, sizeof(buffer) - 1,
          "idx=%d, dpad: 0x%02x, buttons: 0x%04x, axis L: %4d, %4d, axis R: %4d, "
          "%4d, brake: %4d, throttle: %4d, misc: 0x%02x",
          i,                        // Gamepad Index
          myGamepad->dpad(),        // DPAD
          myGamepad->buttons(),     // bitmask of pressed buttons
          myGamepad->axisX(),       // (-511 - 512) left X Axis
          myGamepad->axisY(),       // (-511 - 512) left Y axis
          myGamepad->axisRX(),      // (-511 - 512) right X axis
          myGamepad->axisRY(),      // (-511 - 512) right Y axis
          myGamepad->brake(),       // (0 - 1023): brake button
          myGamepad->throttle(),    // (0 - 1023): throttle (AKA gas) button
          myGamepad->miscButtons()  // bitmak of pressed "misc" buttons
        );
        Serial.println(buffer);
      }
    }
  }
}
