#include <Arduino.h>
#include <FastLED.h>

#define PIN_LED_L 7
#define PIN_LED_R 8
#define PIN_LED_C 6

#define PIN_DIST_L A1
#define PIN_DIST_R A0
#define PIN_SENS_C A5
#define PIN_SENS_D A4

#define PIN_M1_F 3
#define PIN_M1_R 11
#define PIN_M2_F 9
#define PIN_M2_R 10

#define PIN_SPKR 5
#define PIN_S1 4
#define PIN_S2 2
#define PIN_RGB 13

#define PIN_RX 2
#define PIN_TX 3

#define NUM_RGB_LEDS 2
CRGB leds[NUM_RGB_LEDS];

void beep(int pitchDelay, int duration)
{
  for (int i = 0; i < duration; i++)
  {
    digitalWrite(PIN_SPKR, HIGH);
    delayMicroseconds(pitchDelay);
    digitalWrite(PIN_SPKR, LOW);
    delayMicroseconds(pitchDelay);
  }
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
}

void loop()
{
  Serial.println("X | awaiting command");

  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);

  char choice = 'l';

  for (int i = 0; i < 100; i++)
  {
    if (digitalRead(4))
    {
      choice = 's';
      Serial.println("s | loudspeaker activated");
      break;
    }
    else if (!digitalRead(2))
    {
      choice = 'r';
      Serial.println("r | rgb LEDs activated");
      break;
    }
    else if (i == 99)
    {
      Serial.println("a | timeout... auto blink initiated");
    }
    delay(30);
  }

  if (choice == 'l')
  {
    for (int i = 0; i < 3; i++)
    {
      digitalWrite(6, LOW);
      digitalWrite(7, LOW);
      digitalWrite(8, HIGH);
      delay(500);
      digitalWrite(6, HIGH);
      digitalWrite(7, HIGH);
      digitalWrite(8, LOW);
      delay(500);
    }
  }

  if (choice == 's')
  {
    beep(4200, 20);
    delay(50);

    beep(4200, 20);
    delay(50);

    for (int i = 0; i < 1000; i++)
    {
      digitalWrite(PIN_SPKR, random(0, 2));
      delayMicroseconds(60);
    }
    digitalWrite(PIN_SPKR, LOW);
  }

  if (choice == 'r')
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
    leds[0] = CRGB::Green;
    leds[1] = CRGB::Purple;
    FastLED.show();
    delay(500);
    leds[0] = CRGB::Black;
    leds[1] = CRGB::Black;
    FastLED.show();
    delay(500);
  }
}