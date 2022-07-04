#include <Wire.h>                   
#include <LiquidCrystal_I2C.h>      
LiquidCrystal_I2C lcd(0x27, 16, 2); 

int buttonPin = 7;
int tonePin = 4;

void setup()
{
  lcd.init();      
  lcd.backlight(); 
  pinMode(buttonPin, INPUT);
  pinMode(tonePin, OUTPUT);
  startMenue();
  waitForButton(buttonPin);
}

void loop()
{
  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("Wait for");
  lcd.setCursor(0, 1); 
  lcd.print("the tone...");
  delay(random(1000, 5000));

  // start timer
  unsigned long startTime = millis();

  // Tell the user to press the button
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("PRESS NOW!");

  // Play the tone
  startTone(tonePin);

  // press button and play tone when it hasn't playerd for 200ms
  bool button = false;
  while (button == false)
  {
    if (millis() - startTime > 200)
    {
      stopTone(tonePin);
    }
    button = checkButton(buttonPin);
  }

  // stop tone if check button is true before 200ms
  stopTone(tonePin);

  // stop timer
  long ergebnis = millis() - startTime;

  // stop tone
  // stopTone(tonePin);

  // tell the user the result
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SUPER! " + String(ergebnis) + "ms");
  lcd.setCursor(0, 1);
  lcd.print("Press to play");
  delay(1000);
  
  waitForButton(buttonPin);
  lcd.clear();
}

// declare a new function that creates a start menue
void startMenue()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Start Menue");
  lcd.setCursor(0, 1);
  lcd.print("Press to play");
}

// wait for button to be pressed
boolean waitForButton(int readPin)
{
  boolean pressed = false;
  while (!pressed)
  {
    if (digitalRead(readPin) == HIGH)
    {
      pressed = true;
    }
  }
  pressed = false;
  return true;
}

void playTone(int tonePin, int duration)
{
  digitalWrite(tonePin, HIGH);
  delay(duration);
  digitalWrite(tonePin, LOW);
}

// start tone
void startTone(int tonePin)
{
  digitalWrite(tonePin, HIGH);
}

// stop tone
void stopTone(int tonePin)
{
  digitalWrite(tonePin, LOW);
}

// check if button is pressed
boolean checkButton(int readPin)
{
  if (digitalRead(readPin) == HIGH)
  {
    return true;
  }
  return false;
}