#include <Servo.h>

Servo servoX;
Servo servoY;
float x=90;
float y=90;

String number="";
bool numberComplete=false;

int secunde=0;
int minute=0;

void setup()
{  
  Serial.begin(9600); // Interfata Serial 0, pentru PC
  servoX.attach(10);
  servoY.attach(11);
  number.reserve(10);
}
void loop()
{
  if (Serial.available()){ // Citire de pe Bluetooth, trimite la PC
    char car=Serial.read();
    if(car!='*')
      number+=car;
    else{
      numberComplete=true;
      //Serial.println(number);
    }
  }

  if(numberComplete==true){
    Serial.println(number);
    numberComplete=false;

    if(number[0]=='A' && number[1]=='-'){
      x=-number.substring(1,5).toFloat();
      x=x*10+90;

      if(number[7]=='-'){
        y=number.substring(7,11).toFloat();
        y=y*10+90;
      }
      else{
        y=number.substring(7,10).toFloat();
        y=y*10+90;
      }
    }

    if(number[0]=='A' && number[1]!='-'){
      x=-number.substring(1,4).toFloat();
      x=x*10+90;

      if(number[6]=='-'){
        y=number.substring(6,10).toFloat();
        y=y*10+90;
      }
      else{
        y=number.substring(6,9).toFloat();
        y=y*10+90;
      }
    }
    servoX.write(x);
    servoY.write(y);
        
    number="";
  } 
}
