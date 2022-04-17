/**
 * Arducopter aircraft application that
 * operates the helicopter and manages
 * both avionics as well as communication
 */

/* include the main aicraft class */
#include "Aircraft.h"

/* instanciate the aircraft class */
Aircraft helicopter;

/**
 * Setup the helicopter aircraft for
 * flight operations and ensure it is
 * operational
 */
void setup() {
  helicopter.prepare();
}

/**
 * Handle the aircraft operation and manage
 * all sensors and flight controls
 */
void loop() {
  helicopter.operate();
}
