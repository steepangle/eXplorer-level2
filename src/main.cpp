#include <Arduino.h>

void setup()
{
  Serial.begin(9600);
  Serial.println("Booting ...");

  delay(500);

  // S1, S2
  pinMode(2, INPUT);
  pinMode(4, INPUT);

  // OUT Pins 5 - 8
  for (int i = 5; i <= 8; i++)
  {
    pinMode(i, OUTPUT);
  }

  // LED Pin
  pinMode(13, OUTPUT);
  
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
    } else if (i == 99) {
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
    for (int i = 0; i < 100; i++)
    {
      digitalWrite(5, HIGH);
      delay(20);
      digitalWrite(5, LOW);
    }
  }

  if (choice == 'r')
  {
    delay(500);
  }
}
