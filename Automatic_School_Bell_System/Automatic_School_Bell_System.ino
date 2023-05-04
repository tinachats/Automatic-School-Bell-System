/**
  Automatic-School-Bell
  Version 1.0

  Copyright (C) 2023, Tinashe Marshall Chaterera.
  Released under the MIT License.
*/
#include "EEPROM.h"
#include "LiquidCrystal.h"
#include "Keypad.h"

// Create an lcd object
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

// constants
 int timetableAddress = 0;
const int buzzer = A0; // this is the pin the buzzer is connected to
const int warningLed = A1; // this blinks if there's an error in the code
const byte rows = 4; // the number of rows on the keypad
const byte cols = 3; // the numbers of columns on the keypad

char keys[rows][cols] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPins[rows] = {1, 2, 3, 4}; // the pins of the keypdad from the top
byte colPins[cols] = {5, 6, 7}; // the pins of the keypdad from the left

char daysOfTheWeek[7][12] = {
  "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
};

// variables
int timetableType;

// create a keypad object 
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

// company info
void companyInfo(){
  lcd.setCursor(0, 1);
  lcd.print("Visionaries Systems");
  lcd.setCursor(0, 2);
  lcd.print("All Rights Reserved.");
  delay(2000);
  lcd.clear();
}

// configure function
void registerSettings(){
  lcd.clear();
  lcd.home();
  lcd.print("SELECT TIMETABLE");
  lcd.setCursor(0, 1);
  lcd.print("DAYS OR CYCLES?");
  lcd.setCursor(0, 3);
  lcd.print("*[DAYS]");
  lcd.setCursor(10, 3);
  lcd.print("#[CYCLES]");
}

// get the timetable type from timetableAddress
void getTimetableType(int timetableAddress){
  lcd.clear();
  lcd.home();
  // read if there is a value in the memory address
  const int timetableType = EEPROM.read(timetableAddress);
  if(timetableType == NULL){
    registerSettings();
  } else if(timetableType == 0){
    lcd.print("DAYS TIMETABLE SET");
  } else {
     lcd.print("CYCLES TIMETABLE SET");
  }
}

// this makes the user enter their timetable type
void chooseTimetable(int timetableAddress, char key){
  // clear the screen
  lcd.clear();
  // set the cursor to the top left
  lcd.home();
  if(isDigit(key)){
    lcd.print("Invalid input!");
    lcd.setCursor(0, 2);
    lcd.print("Try again!");
    registerSettings();
  } else {
    if(key == "*"){
      timetableType = 0;
    } else {
      timetableType = 1;
    }

    // save the timetable type to EEPROM
    EEPROM.update(timetableAddress, timetableType);
  }
}

// clear all memory
void memoryReset(){
  for(int i = 0; i < EEPROM.length(); i++){
    EEPROM.write(i, 0);
  }
}

void setup() {
  // initialise the lcd
  lcd.begin(20, 4);

  // initialize the buzzer as an output
  pinMode(buzzer, OUTPUT);

  // set warningLed as output
  pinMode(warningLed, OUTPUT);

  // display the company info
  companyInfo();

  // check if there is any data in memory
  getTimetableType(timetableAddress);
}

void loop() {
  // check if there is any keypad key that has been pressed 
  char key = keypad.getKey();

  // if there's been a keypress, do something
  if(key){
    chooseTimetable(timetableAddress, key);
  }
}
