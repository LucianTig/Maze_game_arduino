#include <TimerOne.h> 
#include <LiquidCrystal_I2C.h>

#define pinStart 2
#define pinStop 3

LiquidCrystal_I2C lcd(0x27,20,4);

volatile int secunde=0;
volatile int minute=0;
int t=0;
volatile bool flagLcd=false;
volatile bool flagWin=false;


void setup() {
  // put your setup code here, to run once:
  Timer1.initialize(1000000); 
  Timer1.attachInterrupt(ShowMessage);
  
  lcd.init();                   
  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print("Nu merge");
  pinMode(pinStart,INPUT_PULLUP);
  pinMode(pinStop,INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(pinStart), resetCron, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinStop), stopCron, CHANGE);

  Serial.begin(9600);
  
}

void loop() {
  
    if(flagLcd){
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print(minute);
      lcd.print(":");
      lcd.print(secunde);
      flagLcd=false;
    }
}

void ShowMessage(void)
{
  if(!flagWin){
    secunde++;
    if(secunde>60){
      minute++;
      secunde=0;
    } 
    flagLcd=true;   
  }
}

void resetCron(){
  minute=0;
  secunde=0;
  flagWin=false;
}

void stopCron(){
  flagWin=true;
}
