#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
  // put your setup code here, to run once:
  lcd.begin();
  lcd.setBacklight(HIGH);
  lcd.print("hi cutie :3");

}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0,3);
  lcd.print("Maelys is a nerd :)");
}
