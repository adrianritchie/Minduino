/*
  DriveControl.h - Library for controlling Minduino drive.
  Created by Adrian Ritchie, February 8, 2017.
*/

#ifndef Scanner_h
#define Scanner_h

#include <Arduino.h>
#include <NewPing.h>
#include <Servo.h>

#define FORWARD 0
#define LEFT 1
#define RIGHT 2

class Scanner
{
  public:
    Scanner();
    void attachServo(int pin);
    void attachSonar(int trigger, int echo);
    void scan();
    void update();
    bool obstacle();
    int bestDirection();
    int range();
    
  private:
    Servo _servo;
    NewPing _sonar = NewPing(0,0,0);
    bool _obstacle;
    int _lastForward;
    int _lastLeft;
    int _lastRight;
    int _angle;
    int _ping(int tries);
};

#endif