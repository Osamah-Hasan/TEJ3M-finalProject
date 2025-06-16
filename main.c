/*
Created by: Osamah Hasan
Created on: May 2025
make the lcd display timer and work
*/

// librarys requaierd
#include <LiquidCrystal.h> //gitting the librarys

//LCD pins:(RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //asing the pins to the librarys

// pins for Buzzer and button
const int addButton = 6; 
const int subButton = 7; 
const int starButton = 8; 
const int buzzer = 9; 
const int stopButton = 10;
const int potPin = A0;
const int onemsDelay = 100;
const int speakerDelay = 10000;
const int onesDelay = 1000;
const int timeCul =1000;
const int highVolume = 255;
const int lowVolume = 0;
const int lowTurn = 0;
const int highTurn = 1023;

// time variables
int hours = 0;
int minutes = 0;
int seconds = 0;
int number = 1;
int countdown = 0;

//step counter
int step = 0; //step0: add hours, step1 add minutes, step2 add seconds, step3 start countdown

//setup pins for input and pins for output
void setup() {
  //lcd config
  lcd.begin(16, 2);
  pinMode(addButton, INPUT_PULLUP);
  pinMode(subButton, INPUT_PULLUP);
  pinMode(starButton, INPUT_PULLUP);
  pinMode(stopButton, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  pinMode(potPin, INPUT);
}

// for everything you will see in the screen
void loop() {
  //that shows the hours after 100ms delay
  if (step == 0) {
    delay(onemsDelay);
    lcd.setCursor(0, 0);
    lcd.print("Set Hours");
    lcd.setCursor(0, 1);
    lcd.print(hours);
    
    // that to add 1 to hours if the add button was prssed
    if (digitalRead(addButton) == LOW) {
      delay(onemsDelay);
      hours = hours + number;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Set Hours");
      lcd.setCursor(0, 1);
      lcd.print(hours);
      delay(onemsDelay);
      
    // mines one to hours if the number was bigger then 0  
    } else if(digitalRead(subButton) == LOW) {
      delay(onemsDelay);
      if (hours > 0) hours = hours - number;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Set Hours");
      lcd.setCursor(0, 1);
      lcd.print(hours);
      delay(onemsDelay);
    
    //startbutton when pressed make the step changes from zero to one after clearing the screen and 100ms delay  
    } else if(digitalRead(starButton) == LOW) {
      step = 1;
      lcd.clear();
      delay(onemsDelay);
     
    //that restart the hours, minutes, seconds when press to restart all and return to step zero
    } else if (digitalRead(stopButton) == LOW) {
      hours = 0;
      minutes = 0;
      seconds = 0;
      lcd.clear();
      lcd.print("restarting...");
      delay(onesDelay);
      lcd.clear();
      step = 0;
    }
  
  //that shows the Minutes after 100ms delay  
  } else if (step == 1) {
    delay(onemsDelay);
    lcd.setCursor(0, 0);
    lcd.print("Set Minutes");
    lcd.setCursor(0, 1);
    lcd.print(minutes);
    
    // that to add 1 to minutes if the add button was prssed
    if (digitalRead(addButton) == LOW) {
      delay(onemsDelay);
      
      //make the minutes reach the highest then stop which is 59
      if (minutes < 59) { 
        minutes = minutes + number;
        lcd.clear();
      }
      
    //clear the screen and print setminutes and then print minutes after changing minutes
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Set Minutes");
      lcd.setCursor(0, 1);
      lcd.print(minutes);
      delay(onemsDelay);
    // mines one from minutes    
    } else if(digitalRead(subButton) == LOW) {
      delay(onemsDelay);
      
      // make te max number to go down to zero
      if (minutes > 0) {
      minutes = minutes - number;
      lcd.clear();
    }
      
      // change minutes after update 
      lcd.setCursor(0, 0);
      lcd.print("Set Minutes");
      lcd.setCursor(0, 1);
      lcd.print(minutes);
      delay(onemsDelay);
      
    //startbutton when pressed make the step changes from one to two after clearing the screen and 100ms delay   
    } else if(digitalRead(starButton) == LOW){
      step = 2;
      lcd.clear();
      delay(onemsDelay);
      
    //that restart the hours, minutes, seconds when press to restart all and return to step zero  
    } else if (digitalRead(stopButton) == LOW){
      hours = 0;
      minutes = 0;
      seconds = 0;
      lcd.clear();
      lcd.print("restarting...");
      delay(onesDelay);
      lcd.clear();
      step = 0;
    }
  
  //that shows the Seconds after 100ms delay    
  } else if (step == 2){
    delay(onemsDelay);
    lcd.setCursor(0, 0);
    lcd.print("Set Seconds");
    lcd.setCursor(0, 1);
    lcd.print(seconds);
    
    //make the seconds reach the highest then stop which is 59
    if (digitalRead(addButton) == LOW) {
      delay(onemsDelay);
      if (seconds < 59) { 
        seconds = seconds + number;
        lcd.clear();
      }
      
      //dispay the seconds after the update
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Set Seconds");
      lcd.setCursor(0, 1);
      lcd.print(seconds);
      delay(onemsDelay);
      
    // mines one from seconds      
    } else if(digitalRead(subButton) == LOW) {
      delay(onemsDelay);
      
      // make te max number to go down to zero
      if (seconds > 0) { 
        seconds = seconds - number;
      }
      
      // change minutes after update 
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Set Seconds");
      lcd.setCursor(0, 1);
      lcd.print(seconds);
      delay(onemsDelay);
      
    //startbutton when pressed make the step changes from two to three after clearing the screen and 100ms delay   
    } else if(digitalRead(starButton) == LOW){
      step = 3;
      lcd.clear();
      delay(onemsDelay);
      
    //that restart the hours, minutes, seconds when press to restart all and return to step zero    
    } else if (digitalRead(stopButton) == LOW){
      hours = 0;
      minutes = 0;
      seconds = 0;
      lcd.clear();
      lcd.print("restarting...");
      delay(onesDelay);
      lcd.clear();
      step = 0;
    }
    
  //that shows the time you set ether to start or to resat  
  } else if (step == 3) {
    lcd.setCursor(0, 0);
    lcd.print("Time you set is ");
    lcd.setCursor(0, 1);
    
    //if hours less then two numbers add zero before the number 
    if (hours < 10) {
      lcd.print("0");
    }
  lcd.print(hours);
  lcd.print(":");
    
    //if hours less then two numbers add zero before the number 
    if (minutes < 10) {
      lcd.print("0");
    } 
  lcd.print(minutes);
  lcd.print(":");
    
    //if hours less then two numbers add zero before the number 
    if (seconds < 10) {
      lcd.print("0");
    }
  lcd.print(seconds);
    
    //startbutton when pressed make the step changes from three to four after clearing the screen and 100ms delay   and making the countdown into seconds
    if (digitalRead(starButton) == LOW) {
      countdown = hours * 3600 + minutes * 60 + seconds;
      step = 4;
      lcd.clear();
      delay(onemsDelay);
      
    //that restart the hours, minutes, seconds when press to restart all and return to step zero   
    } else if (digitalRead(stopButton) == LOW) {
      hours = 0;
      minutes = 0;
      seconds = 0;
      lcd.clear();
      lcd.print("restarting...");
      delay(onesDelay);
      lcd.clear();
      step = 0;
    }
    
  //shows the timer in HH:MM:SS after making some calculation and then display the time with the if the number is one number add zero before the number  
  } else if (step == 4) {
    
    //calculation to get info if what the time is in HH:MM:SS
    int cHours = countdown / 3600;
  int cMinutes = (countdown % 3600) / 60;
  int cSeconds = countdown % 60;
  lcd.setCursor(0, 0);
  lcd.print("Time Left:");
  lcd.setCursor(0, 1);
    
    //if hours less then two numbers add zero before the number 
  if (cHours < 10) {
      lcd.print("0");
    }
  lcd.print(cHours);
  lcd.print(":");
    
    //if hours less then two numbers add zero before the number 
    if (cMinutes < 10) {
      lcd.print("0");
    }
    lcd.print(cMinutes);
    lcd.print(":");
    
    //if hours less then two numbers add zero before the number 
  if (cSeconds < 10) {
      lcd.print("0");
    }
    lcd.print(cSeconds);
    
    //that restart the hours, minutes, seconds when press to restart all and return to step zero
    if (digitalRead(stopButton) == LOW) {
      hours = 0;
      minutes = 0;
      seconds = 0;
      lcd.clear();
      lcd.print("restarting...");
      delay(onesDelay);
      lcd.clear();
      step = 0;
      
    // make the countdown do it things with minus one form the number that was changed to seconds and check if the countdown bigger the zero   
    } else if (countdown > 0) {
      countdown = countdown - 1;
      delay(timeCul);
      lcd.setCursor(0, 0);
      lcd.print("wait");
      lcd.setCursor(0, 1);
      lcd.print(countdown);
      lcd.clear();
      
    // check if the code is equal to zero  and turn the buzzer to high after second to low
    } else if (countdown == 0) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Timer is up!");
      unsigned long startTime = millis();
      
      while (millis() - startTime < speakerDelay) {
        int potValue = analogRead(potPin);            // Read potentiometer
        int volume = map(potValue, lowTurn, highTurn, lowVolume, highVolume);   // Map to PWM duty cycle
        analogWrite(buzzer, volume);                  // Set volume
      }
      
      analogWrite(buzzer, 0); // Turn off the buzzer after long beep
      // Reset timer and display
      hours = 0;
      minutes = 0;
      seconds = 0;
      countdown = 0;
      lcd.clear();
      lcd.print("restarting....");
      delay(onesDelay);
      lcd.clear();
      step = 0;
    }
  }
}