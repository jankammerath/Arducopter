#ifndef Aircraft_h
#define Aircraft_h
#include "Arduino.h"
#include "Cockpit.h"
class Aircraft {
  public:
    Aircraft();
    void prepare();
    void operate();
  private:
    Cockpit cockpit;
    bool operational;
    float rotationZ;
    float rotationX;
    float rotationY;
    float verticalSpeed;
    float horizontalSpeedX;
    float horizontalSpeedY;
};
#endif
