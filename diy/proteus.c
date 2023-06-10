#include <LiquidCrystal.h>
#include <TimerOne.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

int HBSensor = 4;
int HBCount = 0;
int HBCheck = 0;
int TimeinSec = 0;
int HBperMin = 0;
int HBStart = 2;
int HBStartCheck = 0;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(20, 4);
  pinMode(HBSensor, INPUT);
  pinMode(HBStart, INPUT_PULLUP);
  Timer1.initialize(800000); 
  Timer1.attachInterrupt( timerIsr );
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Current HB  : ");
  lcd.setCursor(0,1);
  lcd.print("Time in Sec : ");
  lcd.setCursor(0,2);
  lcd.print("HB per Min  : 0.0");
}

void loop() {
  if(digitalRead(HBStart) == LOW){lcd.setCursor(0,3);lcd.print("HB Counting ..");HBStartCheck = 1;}
  if(HBStartCheck == 1)
  {
      if((digitalRead(HBSensor) == HIGH) && (HBCheck == 0))
      {
        HBCount = HBCount + 1;
        HBCheck = 1;
        lcd.setCursor(14,0);
        lcd.print(HBCount);
        lcd.print(" ");
      }
      if((digitalRead(HBSensor) == LOW) && (HBCheck == 1))
      {
        HBCheck = 0;   
      }
      if(TimeinSec == 10)
      {
          HBperMin = HBCount * 6;
          HBStartCheck = 0;
          lcd.setCursor(14,2);
          lcd.print(HBperMin);
          lcd.print(" ");
          lcd.setCursor(0,3);
          lcd.print("Press Button again.");
          HBCount = 0;
          TimeinSec = 0;      
      }
  }
}

void timerIsr()
{
  if(HBStartCheck == 1)
  {
      TimeinSec = TimeinSec + 1;
      lcd.setCursor(14,1);
      lcd.print(TimeinSec);
      lcd.print(" ");
  }
}
