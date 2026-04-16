// Remote Control

#include <Arduino.h>
#include <FastLED.h>

#define PIN_RGB 13
#define NUM_RGB_LEDS 2
CRGB leds[NUM_RGB_LEDS];
bool positionLight = true;

#define PIN_M1_F 3
#define PIN_M1_R 11
#define PIN_M2_F 10
#define PIN_M2_R 9

const int buzPin = 5;  // Buzzer pin
const int ledPin = 6;  // LED pin
int speed = 130;       // speed

void setup() {
    Serial.begin(9600);
    FastLED.addLeds<NEOPIXEL, PIN_RGB>(leds, NUM_RGB_LEDS);

    pinMode(PIN_RGB, OUTPUT);

    pinMode(buzPin, OUTPUT);
    pinMode(ledPin, OUTPUT);

    pinMode(PIN_M1_F, OUTPUT);
    pinMode(PIN_M1_R, OUTPUT);
    pinMode(PIN_M2_F, OUTPUT);
    pinMode(PIN_M2_R, OUTPUT);

    // Stop all motors at the beginning
    digitalWrite(PIN_M1_F, LOW);
    digitalWrite(PIN_M1_R, LOW);
    digitalWrite(PIN_M2_F, LOW);
    digitalWrite(PIN_M2_R, LOW);

    leds[0] = CRGB::Green;
    leds[1] = CRGB::Red;
    FastLED.show();
}

void loop() {
    while (Serial.available() > 0) {
        char command = Serial.read(); // Read command from serial
        //Serial.println("BAT:75,SPEED:25"); // Set Battery and speed

        switch(command) {
            case 'F':   // Move forward
                analogWrite(PIN_M1_F, speed);
                analogWrite(PIN_M1_R, 0);
                analogWrite(PIN_M2_F, speed);
                analogWrite(PIN_M2_R, 0);
                break;

            case 'B':   // Move backward
                analogWrite(PIN_M1_F, 0);
                analogWrite(PIN_M1_R, speed);
                analogWrite(PIN_M2_F, 0);
                analogWrite(PIN_M2_R, speed);
                break;

            case 'R':   // Turn right
                analogWrite(PIN_M1_F, 0);
                analogWrite(PIN_M1_R, speed * 0.5);
                analogWrite(PIN_M2_F, speed);
                analogWrite(PIN_M2_R, 0);
                break;

            case 'L':   // Turn left
                analogWrite(PIN_M1_F, speed);
                analogWrite(PIN_M1_R, 0);
                analogWrite(PIN_M2_F, 0);
                analogWrite(PIN_M2_R, speed * 0.5);
                break;

            case 'G':   // Forward left
                analogWrite(PIN_M1_F, speed);
                analogWrite(PIN_M1_R, 0);
                analogWrite(PIN_M2_F, speed * 0.5);
                analogWrite(PIN_M2_R, 0);
                break;

            case 'H':   // Forward right
                analogWrite(PIN_M1_F, speed * 0.5);
                analogWrite(PIN_M1_R, 0);
                analogWrite(PIN_M2_F, speed);
                analogWrite(PIN_M2_R, 0);
                break;

            case 'I':   // Backward left
                analogWrite(PIN_M1_F, 0);
                analogWrite(PIN_M1_R, speed);
                analogWrite(PIN_M2_F, 0);
                analogWrite(PIN_M2_R, speed * 0.5);
                break;

            case 'J':   // Backward right
                analogWrite(PIN_M1_F, 0);
                analogWrite(PIN_M1_R, speed * 0.5);
                analogWrite(PIN_M2_F, 0);
                analogWrite(PIN_M2_R, speed);
                break;

            case 'S':   // Stop all motors
                analogWrite(PIN_M1_F, 0);
                analogWrite(PIN_M1_R, 0);
                analogWrite(PIN_M2_F, 0);
                analogWrite(PIN_M2_R, 0);
                break;

            case 'Y':   // position Lights
                if (!positionLight)
                {
                    leds[0] = CRGB::Green;
                    leds[1] = CRGB::Red;
                    FastLED.show();
                    positionLight = true;
                } else {
                    leds[0] = CRGB::Black;
                    leds[1] = CRGB::Black;
                    FastLED.show();
                    positionLight = false;
                }
                break;

            case 'X':   // Turn headlight ON
                digitalWrite(ledPin, HIGH);
                break;

            case 'x':   // Turn headlight OFF
                digitalWrite(ledPin, LOW);
                break;

            // Setting motor speed using function buttons you can do anything you want (1-4)
            case '0': speed = 0; break;
            case '1': speed = 50; break;
            case '2': speed = 75; break;
            case '3': speed = 100; break;
            case '4': speed = 125; break;
            case '5': speed = 150; break;
            case '6': speed = 175; break;
            case '7': speed = 200; break;
            case '8': speed = 225; break;
            case '9': speed = 250; break;
        }
    }
}
