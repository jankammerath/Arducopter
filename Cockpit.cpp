#include "Arduino.h"
#include <Bluepad32.h>
#include "Cockpit.h"

/**
 * Constructs the cockpit and initialises
 * the local variables that define the state
 * of the cockpit
 */
Cockpit::Cockpit(){
  this->operational = false;  
}

/**
 * Prepares the cockpit for operation by
 * connecting all controls (PS4 controller)
 */
void Cockpit::prepare(){
  
}

/**
 * Operates the cockpit reading the information
 * from the flight controller and storing it
 * locally for reading from other objects
 */
void Cockpit::operate(){
  if(this->operational == true){
    /* read the flight controls */
  }
}
