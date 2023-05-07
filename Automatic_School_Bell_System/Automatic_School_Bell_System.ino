#include "Adafruit_GFX.h" // include Adafruit graphix library
#include "Adafruit_PCD8544.h" // include Adafruit PCD8544 (Nokia 3310/5110) library
#include "SPI.h"  // include the SPI library
#include "Wire.h" // include the wire library (required for I2C devices)

// Nokia 5110 LCD module connections (CLK, DIN, D/C, CS, RST)
Adafruit_PCD8544 lcd = Adafruit_PCD8544(13, 12, 11, 10, 9);

// app logo, 48x48px
const unsigned char logo [] PROGMEM = {
	0x01, 0xff, 0xff, 0xff, 0xff, 0x80, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x1e, 0x00, 0x00, 0x00, 
	0x00, 0x78, 0x38, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x70, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x60, 0x00, 
	0x00, 0x00, 0x00, 0x06, 0x60, 0x00, 0x00, 0x00, 0x00, 0x06, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x03, 
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 
	0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 
	0x07, 0x80, 0x00, 0x03, 0xc0, 0x00, 0x0f, 0xc0, 0x00, 0x03, 0xc0, 0x00, 0x0f, 0xc0, 0x00, 0x03, 
	0xc0, 0x00, 0x07, 0x80, 0x00, 0x03, 0xc0, 0x00, 0x01, 0x80, 0x00, 0x03, 0xc0, 0x00, 0x07, 0xc0, 
	0x00, 0x03, 0xc0, 0x00, 0x07, 0xf0, 0x00, 0x03, 0xc0, 0x1f, 0x87, 0xf8, 0x00, 0x03, 0xc0, 0x3f, 
	0xe7, 0xff, 0xc0, 0x03, 0xc0, 0x3f, 0xe7, 0xef, 0xe6, 0x03, 0xc0, 0x00, 0x07, 0xe0, 0xff, 0x03, 
	0xc0, 0x7f, 0x07, 0xe0, 0x7f, 0x83, 0xc0, 0xff, 0x87, 0xf1, 0xff, 0xc3, 0xc0, 0xff, 0x8f, 0xf9, 
	0xff, 0xc3, 0xc0, 0x00, 0x0f, 0x7c, 0xdf, 0x03, 0xc3, 0xfc, 0x1f, 0x3c, 0xfc, 0x03, 0xc3, 0xfe, 
	0x3e, 0x3c, 0x20, 0x03, 0xc3, 0xfc, 0x7c, 0x3c, 0x00, 0x03, 0xc0, 0x01, 0xf8, 0x3c, 0x00, 0x03, 
	0xc0, 0x01, 0xf0, 0x3c, 0x00, 0x03, 0xc0, 0x01, 0xc0, 0x3c, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x08, 
	0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 
	0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x03, 
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x03, 0x60, 0x00, 0x00, 0x00, 0x00, 0x06, 0x60, 0x00, 0x00, 0x00, 
	0x00, 0x06, 0x70, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x38, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x1e, 0x00, 
	0x00, 0x00, 0x00, 0x78, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x01, 0xff, 0xff, 0xff, 0xff, 0x80
};

// constants
const int upButton = 5; // the pin at which the up button is attached to
const int downButton = 6; // the pin at which the down button is attached to
const int selectButton = 7; // the pin at which the select button is attached to
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
int upButtonState = 0;  
int downButtonState = 0; 
int selectButtonState = 0;
int lastUpButtonState = 0;          
int lastDownButtonState = 0;
int lastSelectButtonState = 0;

void setup(){
  // push buttons are connected as inputs 
  // using Arduino's built-in pull-up resistors
  pinMode(upButton, INPUT_PULLUP);
  pinMode(downButton, INPUT_PULLUP);
  pinMode(selectButton, INPUT_PULLUP);
  pinMode(lcdLedPin, OUTPUT);

  // start serial communication
  Serial.begin(9600);
  
  // initialize the lcd
  lcd.begin();      
  lcd.clearDisplay(); // clear the buffer
  lcd.setContrast(contrast); //Set contrast to 50
  lcd.drawBitmap(18, 0,  logo, 48, 48, BLACK); // display the app logo
  lcd.display();   
  delay(3000);
}

void loop(){
  // call the function for displaying the menu
  drawMenu();

  // check the current state of the navigation buttons
  upButtonState =   digitalRead(upButton);
  downButtonState = digitalRead(downButton);
  selectButtonState = digitalRead(selectButton);
  
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
      down = true;
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
    // display the black FontColor on a white BackgroundColor
    lcd.setTextColor(BLACK, WHITE);
    lcd.setCursor(15, 0);
    lcd.print("MAIN MENU");
    lcd.drawFastHLine(0, 10, 83, BLACK);
    lcd.setCursor(0, 15);
  
    if(menuItem == 1){ 
      // display the white FontColor on a black BackgroundColor
      lcd.setTextColor(WHITE, BLACK);
    } else {
      // display the black FontColor on a white BackgroundColor
      lcd.setTextColor(BLACK, WHITE);
    }

    lcd.print(">Contrast");
    lcd.setCursor(0, 25);
  
    if(menuItem == 2){
      // display the white FontColor on a black BackgroundColor
      lcd.setTextColor(WHITE, BLACK);
    } else {
      // display the black FontColor on a white BackgroundColor
      lcd.setTextColor(BLACK, WHITE);
    }  

    lcd.print(">Light: ");
    
    if(backlight){
      lcd.print("ON");
    } else {
      lcd.print("OFF");
    }
    lcd.display();
    
    if(menuItem == 3){ 
      // display the white FontColor on a black BackgroundColor
      lcd.setTextColor(WHITE, BLACK);
    } else {
      // display the black FontColor on a white BackgroundColor
      lcd.setTextColor(BLACK, WHITE);
    } 

    lcd.setCursor(0, 35);
    lcd.print(">Reset");
    lcd.display();

  } else if(page == 2){
    lcd.setTextSize(1);
    lcd.clearDisplay();
    // display the white FontColor on a black BackgroundColor
    lcd.setTextColor(BLACK, WHITE);
    lcd.setCursor(15, 0);
    lcd.print("CONTRAST");
    lcd.drawFastHLine(0, 10, 83,BLACK);
    lcd.setCursor(5, 15);
    lcd.print("Value");
    lcd.setTextSize(2);
    lcd.setCursor(5, 25);
    lcd.print(contrast);
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
  digitalWrite(lcdLedPin, HIGH);
}

void turnBacklightOff(){
  digitalWrite(lcdLedPin, LOW);
}
