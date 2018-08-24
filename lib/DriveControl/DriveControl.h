/*
  DriveControl.h - Library for controlling Minduino drive.
  Created by Adrian Ritchie, February 8, 2017.
*/

#ifndef DriveControl_h
#define DriveControl_h

#include "Arduino.h"

class DriveControl
{
  public:
    DriveControl(int leftA, int leftB, int rightA, int rightB, int enable);
    void update(int distance);
    void forward(int speed);
    void backward();
    void left();
    void right();
    void halt();
  private:
    int _leftA;
    int _leftB;
    int _rightA;
    int _rightB;
    int _enable;
};

#endif