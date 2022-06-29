#include <Wire.h> // Wire Bibliothek einbinden
#include <LiquidCrystal_I2C.h> // Vorher hinzugefügte LiquidCrystal_I2C Bibliothek einbinden
LiquidCrystal_I2C lcd(0x27, 16, 2); //Hier wird festgelegt um was für einen Display es sich handelt. In diesem Fall eines mit 16 Zeichen in 2 Zeilen und der HEX-Adresse 0x27. Für ein vierzeiliges I2C-LCD verwendet man den Code "LiquidCrystal_I2C lcd(0x27, 20, 4)" 

void setup() 
{
lcd.init(); //Im Setup wird der LCD gestartet 
lcd.backlight(); //Hintergrundbeleuchtung einschalten (lcd.noBacklight(); schaltet die Beleuchtung aus).
pinMode(7, INPUT);
pinMode(4, OUTPUT);
}

void loop() 
{ 
lcd.setCursor(0, 0);//Hier wird die Position des ersten Zeichens festgelegt. In diesem Fall bedeutet (0,0) das erste Zeichen in der ersten Zeile. 
lcd.print("Warten Sie auf"); 
lcd.setCursor(0, 1);// In diesem Fall bedeutet (0,1) das erste Zeichen in der zweiten Zeile. 
lcd.print("den Ton..."); 
delay(random(1000, 5000));
// Ton abstpielen
digitalWrite(4, HIGH);
delay(200);
digitalWrite(4, LOW);

lcd.clear();
lcd.setCursor(0, 0);
lcd.print("DRUECKEN!");

// timer starten
long start = millis();

// button drücken
boolean pressed = false;
while(!pressed) {
  if(digitalRead(7) == HIGH) {
    pressed = true;
  }
}
pressed = false;

//timer stoppen
long ergebnis = millis()-start;

lcd.clear();
lcd.setCursor(0, 0);
lcd.print("SUPER! " + String(ergebnis) + "ms");

lcd.setCursor(0, 1);
lcd.print("Press to play");

delay(1000);

while(!pressed) {
  if(digitalRead(7) == HIGH) {
    pressed = true;
  }
}
pressed = false;
lcd.clear();
} 
