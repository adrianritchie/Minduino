/*
  Scanner.h - Library for controlling Minduino ultrasonic range finder.
  Created by Adrian Ritchie, February 8, 2017.
*/
#include "Scanner.h"
#include "Arduino.h"

#define OBSTACLE_LIMIT  50
#define SCAN_LIMIT      200

#define FORWARD_ANGLE   90
#define LEFT_ANGLE      30
#define RIGHT_ANGLE     140
Scanner::Scanner() {
    _lastForward = 0;
    _lastLeft = _lastRight = SCAN_LIMIT;
}

void Scanner::attachServo(int servoPin){
    _servo.attach(servoPin);
    _angle = FORWARD_ANGLE;
    _servo.write(_angle);
}

void Scanner::attachSonar(int triggerPin, int echoPin){
    _sonar = NewPing(triggerPin, echoPin, SCAN_LIMIT);
}

void Scanner::scan() {
    update();
    delay(100);
    update();
    delay(100);
    update();
}

void Scanner::update(){
    int range = _ping(3);
    
    
    switch(_angle) {
        case FORWARD_ANGLE:
            _lastForward = range;
            _angle = LEFT_ANGLE;
            Serial.print("Forward ");
            break;
        case LEFT_ANGLE:
            _lastLeft = range;
            _angle = RIGHT_ANGLE;
            Serial.print("Left ");
            break;
        case RIGHT_ANGLE:
            _lastRight = range;
            _angle = FORWARD_ANGLE;
            Serial.print("Right ");
            break;
    }
    
    Serial.print("Range: ");
    Serial.println(range);
    
    _servo.write(_angle);
}

bool Scanner::obstacle(){
    return _lastForward < OBSTACLE_LIMIT
        || _lastLeft < OBSTACLE_LIMIT
        || _lastRight < OBSTACLE_LIMIT;
}

int Scanner::bestDirection(){
    if (_lastLeft < _lastRight) {
        return LEFT;
    }
    else {
        return RIGHT;
    }
}

int Scanner::range(){
    return min(_lastForward, min(_lastLeft, _lastRight));
}


int Scanner::_ping(int tries) {
    unsigned long pingTime = _sonar.ping_median(10);
    int distance = _sonar.convert_cm(pingTime);
    
    if (distance < 10 && tries > 0) {
        distance = _ping(tries - 1);
    }
    
    return distance;
}
    