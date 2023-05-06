#include "Adafruit_GFX.h" // include Adafruit graphix library
#include "Adafruit_PCD8544.h" // include Adafruit PCD8544 (Nokia 3310/5110) library
#include "SPI.h"  // include the SPI library
#include "Wire.h" // include the wire library (required for I2C devices)

// NOkia 5110 LCD module connections (CLK, DIN, D/C, CS, RST)
Adafruit_PCD8544 lcd = Adafruit_PCD8544(13, 12, 11, 10, 9);

// constants
const int upBtn = 5; // the pin at which the up button is attached to
const int downBtn = 6; // the pin at which the down button is attached to
const int selectBtn = 7; // the pin at which the select button is attached to
const int lcdLedPin = 8; // the pin where the led pin of the lcd is attached to

/* Variables */
// set the lcd backlight as on by default
boolean backlight = true;
// set contrast to the default value
int contrast = 50;
// set the menu on the first menu item
int menuItem = 1;
// set the default page to the first page
int page = 1;

// set all button options to not pressed by default
volatile boolean up = false;
volatile boolean down = false;
volatile boolean middle = false;

// set button states to 0 
int downButtonState = 0;
int upButtonState = 0;  
int selectButtonState = 0;          
int lastDownButtonState = 0;
int lastSelectButtonState = 0;
int lastUpButtonState = 0;

void setup(){
  // push buttons are connected as inputs 
  // using Arduino's built-in pull-up resistors
  pinMode(upBtn, INPUT_PULLUP);
  pinMode(downBtn, INPUT_PULLUP);
  pinMode(selectBtn, INPUT_PULLUP);

  // initialize the lcd led pin as output
  pinMode(lcdLedPin, OUTPUT);
  digitalWrite(lcdLedPin, LOW); // turn backlight Off

  // start serial communication
  Serial.begin(9600);
  
  // initialize the lcd
  lcd.begin();      
  lcd.setContrast(contrast); //Set contrast to 50
  lcd.clearDisplay(); 
  lcd.display();   
}

void loop(){
  // call the function for displaying the menu
  drawMenu();

  // check the current state of the navigation buttons
  upButtonState =   digitalRead(upBtn);
  downButtonState = digitalRead(downBtn);
  selectButtonState = digitalRead(selectBtn);
  
  // check if any of the navigation buttons has been pressed
  checkIfUpButtonIsPressed();
  checkIfDownButtonIsPressed();
  checkIfSelectButtonIsPressed();

  // check if the menu is currently on page 1 
  // and if the up button is pressed
  if(up && page == 1 ){
    up = false;
    menuItem--;
    if(menuItem == 0){
      menuItem = 3;
    }      
  } else if(up && page == 2 ){
    up = false;
    contrast--;
    setContrast();
  }

  if(down && page == 1){
    down = false;
    menuItem++;
    if(menuItem == 4) 
    {
      menuItem = 1;
    }      
  } else if(down && page == 2){
    down = false;
    contrast++;
    setContrast();
  }

  if(middle){
    middle = false;
    
    if(page == 1 && menuItem == 2){
      if(backlight){
        backlight = false;
        turnBacklightOff();
      } else {
        backlight = true; 
        turnBacklightOn();
      }
    }
    if(page == 1 && menuItem == 3){
      resetDefaults();
    } else if(page == 1 && menuItem == 1){
      page = 2;
    } else if(page == 2){
      page = 1;
    }
  }
}

void checkIfDownButtonIsPressed(){
  if(downButtonState != lastDownButtonState){
    if(downButtonState == 0){
      down=true;
    }
    delay(50);
  }
  lastDownButtonState = downButtonState;
}

void checkIfUpButtonIsPressed(){
  if(upButtonState != lastUpButtonState){
    if(upButtonState == 0){
      up=true;
    }
    delay(50);
  }
  lastUpButtonState = upButtonState;
}

void checkIfSelectButtonIsPressed(){
  if(selectButtonState != lastSelectButtonState){
    if(selectButtonState == 0){
      middle=true;
    }
    delay(50);
  }
  lastSelectButtonState = selectButtonState;
}

void drawMenu(){ 
  if(page == 1){    
    lcd.setTextSize(1);
    lcd.clearDisplay();
    lcd.setTextColor(BLACK, WHITE);
    lcd.setCursor(15, 0);
    lcd.print("MAIN MENU");
    lcd.drawFastHLine(0, 10, 83, BLACK);
    lcd.setCursor(0, 15);
  
    if(menuItem == 1){ 
      lcd.setTextColor(WHITE, BLACK);
    } else {
      lcd.setTextColor(BLACK, WHITE);
    }

    lcd.print(">Contrast");
    lcd.setCursor(0, 25);
  
    if(menuItem == 2) 
    {
      lcd.setTextColor(WHITE, BLACK);
    } else {
      lcd.setTextColor(BLACK, WHITE);
    }  

    lcd.print(">Light: ");
    
    if(backlight){
      lcd.print("ON");
    } else {
      lcd.print("OFF");
    }
    lcd.display();
    
    if(menuItem==3){ 
      lcd.setTextColor(WHITE, BLACK);
    } else {
      lcd.setTextColor(BLACK, WHITE);
    } 

    lcd.setCursor(0, 35);
    lcd.print(">Reset");
    lcd.display();
  } else if(page == 2){
    lcd.setTextSize(1);
    lcd.clearDisplay();
    lcd.setTextColor(BLACK, WHITE);
    lcd.setCursor(15, 0);
    lcd.print("CONTRAST");
    lcd.drawFastHLine(0, 10, 83,BLACK);
    lcd.setCursor(5, 15);
    lcd.print("Value");
    lcd.setTextSize(2);
    lcd.setCursor(5, 25);
    lcd.print(contrast);
    lcd.setTextSize(2);
    lcd.display();
  }
}

void resetDefaults(){
  contrast = 50;
  setContrast();
  backlight = true;
  turnBacklightOn();
}

void setContrast(){
  lcd.setContrast(contrast);
  lcd.display();
}

void turnBacklightOn(){
  digitalWrite(lcdLedPin, LOW);
}

void turnBacklightOff(){
  digitalWrite(lcdLedPin, HIGH);
}
