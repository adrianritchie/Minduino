#include "Arduino.h"
// AsyncDelay - Version: Latest 
#include <AsyncDelay.h>

// FastLED -3.1.3 - Version: Latest 
#include <FastLED.h>

#include "Scanner.h"
#include "DriveControl.h"

//NeoPixels setup
#define DATA_PIN        7
#define NUM_LEDS        8
#define BRIGHTNESS      10
CRGB leds[NUM_LEDS];


#define SERVO_PIN       3
#define TRIGGER_PIN     A4
#define ECHO_PIN        A5
Scanner myScanner;

DriveControl myDriver(5, 6, 9, 10, 4);
bool halting = false;

#define DELAY_SCANNER   100
#define DELAY_DRIVER    100
#define DELAY_HALT      100
AsyncDelay delay_scanner;
AsyncDelay delay_driver;
AsyncDelay delay_halt;

void setup() {
    
    Serial.begin(9600);

    myDriver.halt();
    
    myScanner.attachServo(SERVO_PIN);
    myScanner.attachSonar(TRIGGER_PIN, ECHO_PIN);
    
    randomSeed(analogRead(0));
    
    
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
    FastLED.setBrightness(  BRIGHTNESS );
    
    
    delay_scanner.start(DELAY_SCANNER, AsyncDelay::MILLIS);
    delay_driver.start(DELAY_DRIVER, AsyncDelay::MILLIS);
    delay_driver.expire();
    
}

void loop() {
    
    // myScanner.scan();

    // if (myScanner.obstacle()) {
    //     Serial.println("OBSTACLE!!!");

    //     switch (myScanner.bestDirection()) {
    //         case LEFT:
    //             Serial.println("Go left");
    //             break;
    //         case RIGHT:
    //             Serial.println("Go right");
    //             break;
    //         default:
    //             break;
    //     }
    // }
    // else {
    //     Serial.println("Go forward");
    // }
    // delay(1000);

    if (delay_scanner.isExpired()) {
        myScanner.scan();
        
        int numLedsToLight = map(myScanner.range(), 0, 200, 0, NUM_LEDS);
        FastLED.clear();
        for(int led = 0; led < numLedsToLight; led++) { 
             leds[led] = CRGB::Purple; 
        }
        FastLED.show();  
        
        Serial.println("scanner delay");
        delay_scanner.repeat();
    }
    
    if (delay_driver.isExpired() && !halting) {
        if (myScanner.obstacle()) {
            Serial.println("OBSTACLE!!!");

            if (myScanner.bestDirection() == LEFT) {
                Serial.println("Turn Left");
                myDriver.left();
            } else {
                Serial.println("Turn Right");
                myDriver.right();
            }
            halting = true;
            delay_halt.start(DELAY_HALT, AsyncDelay::MILLIS);
        }
        else {
            Serial.println("Forward");
            myDriver.forward(myScanner.range());
            delay_driver.repeat();
        }
    }
    
    if (delay_halt.isExpired() && halting) {
        Serial.println("Halting");
        halting = false;
        myDriver.halt();
        delay_driver.start(DELAY_DRIVER, AsyncDelay::MILLIS);
    }
}
