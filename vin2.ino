// C++ code
//

#include <Wire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup()
{
  Wire.begin(4);
  Wire.onReceive(show);
  lcd.begin(16, 2);
  
}

void loop()
{
}

void show(int n)
{
  int x = Wire.read();
  if (x == 1) {
    lcd.print("Correct!");
  } else if (x == 2) {
  	lcd.clear();
  } else {
  	lcd.print("Incorrect!");
  }
}