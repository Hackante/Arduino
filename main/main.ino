#include <Wire.h>                   // Wire Bibliothek einbinden
#include <LiquidCrystal_I2C.h>      // Vorher hinzugefügte LiquidCrystal_I2C Bibliothek einbinden
LiquidCrystal_I2C lcd(0x27, 16, 2); // Hier wird festgelegt um was für einen Display es sich handelt. In diesem Fall eines mit 16 Zeichen in 2 Zeilen und der HEX-Adresse 0x27. Für ein vierzeiliges I2C-LCD verwendet man den Code "LiquidCrystal_I2C lcd(0x27, 20, 4)"

int buttonPin = 7;
int tonePin = 4;

void setup()
{
  lcd.init();      // Im Setup wird der LCD gestartet
  lcd.backlight(); // Hintergrundbeleuchtung einschalten (lcd.noBacklight(); schaltet die Beleuchtung aus).
  pinMode(buttonPin, INPUT);
  pinMode(tonePin, OUTPUT);
  startMenue();
  waitForButton(buttonPin);
}

void loop()
{
  lcd.clear();
  lcd.setCursor(0, 0); // Hier wird die Position des ersten Zeichens festgelegt. In diesem Fall bedeutet (0,0) das erste Zeichen in der ersten Zeile.
  lcd.print("Wait for");
  lcd.setCursor(0, 1); // In diesem Fall bedeutet (0,1) das erste Zeichen in der zweiten Zeile.
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

  // press button
  waitForButton(buttonPin);

  // stop timer
  long ergebnis = millis() - startTime;

  // stop tone
  stopTone(tonePin);

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
