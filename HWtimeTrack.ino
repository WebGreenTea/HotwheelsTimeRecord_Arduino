#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>
LiquidCrystal_PCF8574 lcd(0x27);
Servo myservo;
extern volatile unsigned long timer0_millis;

int swStart = 2;//Start Switch
int swReset = 3;//Reset Switch
int servo = 4;//servo
int sensor = 8;//sensor
int state = 0;//0 is Idle, 1 is Recording,2 is end recording
unsigned long TimeRec = 0;

void setup() {
  lcd.setBacklight(255);
  lcd.begin(16,2);
  lcd.display();
  IdleDisply();
  pinMode(swStart,INPUT_PULLUP);
  pinMode(swReset,INPUT_PULLUP);
  myservo.attach(servo);
  myservo.write(0);
}

void loop() {
  if(state){//run when recording time 
    if(!digitalRead(sensor) && state == 1){
      TimeRec = millis();
      lcd.setCursor(3,0);
      lcd.print("Your Time:");
      lcd.setCursor(5,1);
      lcd.print(TimeRec/(float)1000,3);
      state = 2;
    }
    else if(state < 2){
      TimeRec = millis();
      lcd.setCursor(5,1);
      lcd.print(TimeRec/(float)1000,3);  
    }

    if(!digitalRead(swReset)){//when the reset button is pressed
      myservo.write(0);
      state = 0;
      IdleDisply();
    }
    
    
  }
  else{//when not recording time
    if(!digitalRead(swStart)){//when the start button is pressed
      lcd.clear();
      lcd.setCursor(3,0);
      lcd.print("Let's Go!!");
      myservo.write(90);
      timer0_millis = 0;
      state = 1;
    }
  }
}
void IdleDisply(){
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("HOTWHEELS!");
  lcd.setCursor(2,1);
  lcd.print("TIME RECORD.");
}
