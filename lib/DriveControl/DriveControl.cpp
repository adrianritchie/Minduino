/*
  DriveControl.cpp - Library for controlling Minduino drive.
  Created by Adrian Ritchie, February 8, 2017.
*/

#include "DriveControl.h"

DriveControl::DriveControl(int leftA, int leftB, int rightA, int rightB, int enable) {
    pinMode(leftA, OUTPUT);
    pinMode(leftB, OUTPUT);
    pinMode(rightA, OUTPUT);
    pinMode(rightB, OUTPUT);
    pinMode(enable, OUTPUT);
    
    _leftA = leftA;
    _leftB = leftB;
    _rightA = rightA;
    _rightB = rightB;
    _enable = enable;
}

void DriveControl::forward(int speed) {
    digitalWrite(_enable, HIGH);
    digitalWrite(_leftA, LOW);
    digitalWrite(_leftB, HIGH);
    digitalWrite(_rightA, LOW);
    digitalWrite(_rightB, HIGH);
}

void DriveControl::backward() {
    digitalWrite(_enable, HIGH);
    digitalWrite(_leftA, HIGH);
    digitalWrite(_leftB, LOW);
    digitalWrite(_rightA, HIGH);
    digitalWrite(_rightB, LOW);
}

void DriveControl::left() {
    digitalWrite(_enable, HIGH);
    digitalWrite(_leftA, HIGH);
    digitalWrite(_leftB, LOW);
    digitalWrite(_rightA, LOW);
    digitalWrite(_rightB, HIGH);  
    
}

void DriveControl::right() {
    digitalWrite(_enable, HIGH);
    digitalWrite(_leftA, LOW);
    digitalWrite(_leftB, HIGH);  
    digitalWrite(_rightA, HIGH);
    digitalWrite(_rightB, LOW);
}

void DriveControl::halt() {
    digitalWrite(_enable, LOW);
    digitalWrite(_leftA, LOW);
    digitalWrite(_leftB, LOW);
    digitalWrite(_rightA, LOW);
    digitalWrite(_rightB, LOW);  
}