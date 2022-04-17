#ifndef Cockpit_h
#define Cockpit_h
#include "Arduino.h"
class Cockpit {
  public:
    Cockpit();
    void prepare();
    void operate();
  private:
    bool operational;
};
#endif
