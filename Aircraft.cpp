#include "Arduino.h"
#include <Arduino_LSM6DSOX.h>
#include "Aircraft.h"

/**
 * Constructs the aircraft object
 * and performs any basic initialisation
 */
Aircraft::Aircraft(){
  this->operational = false;
  this->rotationZ = 0;
  this->rotationY = 0;
  this->rotationX = 0;
  this->verticalSpeed = 0;
  this->horizontalSpeedX = 0;
  this->horizontalSpeedY = 0;
}

/**
 * Performs the flight preparation
 * for the aircraft and sets it up
 */
void Aircraft::prepare(){
  /* set up the serial connection */
  Serial.begin(9600);
  while(!Serial);

  /* prepare gyroscope and accelerometer */
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
  }else{
    /* Prepare the cockpit for flight operation */
    this->cockpit.prepare();
    while(!this->cockpit.isOperational());
    
    /* print out the operational status */
    Serial.println("Aircraft operational.");
    this->operational = true;  
  }
}

/**
 * Operates the aircraft and monitors
 * the flight operation as well as the
 * pilot input
 */
void Aircraft::operate(){  
  if (IMU.accelerationAvailable()) {
    /* update the speed information by reading
      the data from the accelerometer */
    IMU.readAcceleration(this->horizontalSpeedX, 
        this->horizontalSpeedY, this->verticalSpeed);
  }if (IMU.gyroscopeAvailable()) {
    /* update the rotation status information
      by reading the data from the gyroscope*/
    IMU.readGyroscope(this->rotationX, 
        this->rotationY, this->rotationZ);
  }

  /* operate the cockpit */
  this->cockpit.operate();
}
