//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
char data;
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
void setup()
{
  lcd.init();                      // initialize the lcd 
  lcd.init();
  Serial.begin(9600);
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  // Configure la broche 12 sur laquelle est reliée notre LED  en sortie
  pinMode(12,OUTPUT);
//La LED reliée à la broche 12 est intialisé à l'état LOW
  digitalWrite(12,LOW);
    pinMode(11,OUTPUT);
//La LED reliée à la broche 12 est intialisé à l'état LOW
  digitalWrite(11,LOW);
}


void loop()
{
if (Serial.available()){
  data=Serial.read();
  if(data=='1')
  {
    lcd.init();
    digitalWrite(12,HIGH);
    lcd.print("   Welcome to  ");
    lcd.setCursor(0,1);
    lcd.print(" Smart Aeroport");
    delay(2000);
    digitalWrite(12,LOW);
    lcd.init();

  }else if(data=='0')
  {
    lcd.init();
    digitalWrite(11,HIGH);
    lcd.print("   Error!!!!");
    lcd.setCursor(0,1);
    lcd.print("   Try Again ");
    delay(2000);
    digitalWrite(11,LOW);
    lcd.init();
  }
}
}
