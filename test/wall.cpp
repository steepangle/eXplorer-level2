#include <Arduino.h>
#include <FastLED.h>

#define PIN_LED_L 7
#define PIN_LED_R 8
#define PIN_LED_C 6

#define PIN_DIST_L A1
#define PIN_DIST_R A0
#define PIN_SENS_F A4
#define PIN_SENS_D A5

#define PIN_M1_F 3
#define PIN_M1_R 11
#define PIN_M2_F 10
#define PIN_M2_R 9

#define PIN_SPKR 5
#define PIN_S1 4
#define PIN_S2 2
#define PIN_RGB 13

#define PIN_RX 2
#define PIN_TX 3

#define NUM_RGB_LEDS 2
CRGB leds[NUM_RGB_LEDS];

bool run = false;
int speed = 50; // 0...255

int sensRefLeft;
int sensRefRight;
int sensRefFront;

void rgb()
{
    leds[0] = CRGB::Red;
    leds[1] = CRGB::BlueViolet;
    FastLED.show();
    delay(500);
    leds[0] = CRGB::Green;
    leds[1] = CRGB::Turquoise;
    FastLED.show();
    delay(500);
    leds[0] = CRGB::Blue;
    leds[1] = CRGB::Orange;
    FastLED.show();
    delay(500);
    leds[0] = CRGB::Black;
    leds[1] = CRGB::Black;
    FastLED.show();
    delay(500);
}

void setup()
{
    Serial.begin(9600);
    Serial.println("Booting ...");

    FastLED.addLeds<NEOPIXEL, PIN_RGB>(leds, NUM_RGB_LEDS);

    delay(500);

    // S1, S2
    pinMode(2, INPUT);
    pinMode(4, INPUT);

    // OUT Pins 5 - 8
    for (int i = 5; i <= 8; i++)
    {
        pinMode(i, OUTPUT);
    }

    pinMode(A0, INPUT); // sens right
    pinMode(A1, INPUT); // sens left
    pinMode(A4, INPUT); // sens front

    // turn all lights off
    digitalWrite(PIN_LED_C, LOW);
    digitalWrite(PIN_LED_L, HIGH);
    digitalWrite(PIN_LED_R, LOW);

    // read 'default' values with lights out
    sensRefLeft = analogRead(PIN_DIST_L);
    sensRefRight = analogRead(PIN_DIST_R);
    sensRefFront = analogRead(PIN_SENS_F);

    // turn all lights on
    digitalWrite(PIN_LED_C, HIGH);
    digitalWrite(PIN_LED_L, LOW);
    digitalWrite(PIN_LED_R, HIGH);
}

int readSensL()
{
    int sens = analogRead(PIN_DIST_L);
    return sens;
}

int readSensR()
{
    int sens = analogRead(PIN_DIST_R);
    return sens;
}

int readSensF()
{
    int sens = analogRead(PIN_SENS_F);
    return sens;
}

void turnLft(int speedLo, int speedHi)
{
    analogWrite(PIN_M1_F, speedHi); // left
    analogWrite(PIN_M2_F, 0);       // right
    analogWrite(PIN_M1_R, 0);
    analogWrite(PIN_M2_R, speedLo);
    delay(400);
}

void loop()
{
    if (digitalRead(PIN_S1) == HIGH) {
        run = true;
    }
    /*
    int distFront = sensRefFront - readSensF() + 100;
    int distRight = sensRefRight - readSensR();
    int distLeft = sensRefLeft - readSensL();

    int speedL = 300 - distLeft;
    int speedR = 300 - distRight;

    speedL = speedL - 50;
    speedR = speedR - 50;

    if (speedL < 1) speedL = 20;
    if (speedR < 1) speedR = 20;


    //analogWrite(PIN_M1_F, speedL);
    //analogWrite(PIN_M2_F, speedR);

    // Serial.println("Left: " + (String)distLeft + " | Right: " + (String)distRight + " | Center: " + (String)distFront);
    Serial.println("Left: " + (String)speedL + " | Right: " + (String)speedR);
    */

    while (run)
    {
        /*
        if (digitalRead(PIN_S1) == HIGH)
        {
            run = true;
        }
        */

        if (digitalRead(PIN_S2) == LOW)
        {
            run = false;
        }

        int distFront = readSensF();
        int distRight = readSensR();
        // int distLeft = readSensL();

        int speedHi = 70;
        int speedLo = 40;

        // int tripValue = 50;
        // int delta = distLeft - distRight + 60;

        // Serial.println("Delta: " + (String)delta);

        // delta = 10;

        Serial.println((String)distFront + "  |  " + (String)distRight);

        // dist right
        int max = 650;
        int min = 550;

        // dist
        int fmax = 700;

        if (distFront < fmax)
        {
            leds[0] = CRGB::Blue;
            leds[1] = CRGB::Blue;
            FastLED.show();

            turnLft(speedLo, speedHi);
        }
        if (distRight < max && distRight > min)
        {
            analogWrite(PIN_M1_R, 0);
            analogWrite(PIN_M2_R, 0);
            analogWrite(PIN_M1_F, speedHi); // left
            analogWrite(PIN_M2_F, speedHi); // right

            leds[0] = CRGB::Green;
            leds[1] = CRGB::Green;
            FastLED.show();
        }
        if (distRight > max)
        {
            analogWrite(PIN_M1_F, speedLo);       // left
            analogWrite(PIN_M2_F, speedHi); // right
            analogWrite(PIN_M1_R, 0);
            analogWrite(PIN_M2_R, 0);
            // Serial.println("left obs");
            leds[0] = CRGB::Yellow;
            leds[1] = CRGB::Yellow;
            FastLED.show();
        }
        if (distRight < min)
        {
            analogWrite(PIN_M1_F, speedHi); // left
            analogWrite(PIN_M2_F, speedLo);       // right
            analogWrite(PIN_M1_R, 0);
            analogWrite(PIN_M2_R, 0);
            // Serial.println("right obs");
            leds[0] = CRGB::Red;
            leds[1] = CRGB::Red;
            FastLED.show();
        }
    }

    /*
    if (delta < (-tripValue))
    {
        analogWrite(PIN_M1_F, 0);  //left
        analogWrite(PIN_M2_F, speedHi);  //right
        analogWrite(PIN_M1_R, speedLo);
        analogWrite(PIN_M2_R, 0);
        Serial.println("left");
    }
    if (delta > tripValue) {
        analogWrite(PIN_M1_F, speedHi);  //left
        analogWrite(PIN_M2_F, 0);  //right
        analogWrite(PIN_M1_R, 0);
        analogWrite(PIN_M2_R, speedLo);
        Serial.println("right");
    }
    if ((delta < tripValue) && (delta > (-tripValue))) {
        analogWrite(PIN_M1_R, 0);
        analogWrite(PIN_M2_R, 0);
        analogWrite(PIN_M1_F, speedHi);  //left
        analogWrite(PIN_M2_F, speedHi);  //right

        Serial.println("straight");
    }

    if (distLeft < distRight)
    {
        analogWrite(PIN_M1_F, speedLo);  //left
        analogWrite(PIN_M2_F, speedHi);  //right
    }

    if (distLeft > distRight)
    {
        analogWrite(PIN_M1_F, speedHi);  //left
        analogWrite(PIN_M2_F, speedLo);  //right
    }
    */
}
