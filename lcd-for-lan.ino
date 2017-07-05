#include <Button.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11 , 12);

// set pin numbers:
const int buttonPinCIV = 2;     // the number of the civ-button pin
const int buttonPinOW = 3;     // the number of the civ-button pin

// variables will change:
int buttonStateCIV = 0;         // variable for reading the pushbutton status
int buttonStateCIVLast = LOW;
int buttonStateCIVCurrent = 0; 
int buttonStateOW = 0;         // variable for reading the pushbutton status
int buttonStateOWLast = LOW;
int buttonStateOWCurrent = 0;

// the following variables are unsigned long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTimeCIV = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTimeOW = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

//Button buttonCIV = Button(2, PULLUP);
//Button buttonOW = Button(3, PULLUP);


// DEBOUNCE: https://www.arduino.cc/en/Tutorial/Debounce

const int numberOfCivs = 23;
const String civs[] = {"America", "Arabia", "Australia", "Aztec", "Brazilia", "Chinese", "Egypt", "England", "France", 
"Germany", "Greece", "India", "Japan", "Kongo", "Macedonia", "Norway", "Persia", "Polen", "Rome", "Russia", "Scythia", 
"Spain", "Sumeria"};

const int numberOfOwChars = 24;
const String owChars[] = {"Genji", "McCree", "Pharah", "Reaper", "Soldier: 76", "Sombra", "Tracer", "Bastion", "Hanzo", 
"Junkrat", "Mei", "Torbjörn", "Widowmaker", "D.Va", "Orisa", "Reinhardt", "Roadhog", "Winston", "Zarya", "Ana", "Lucio", 
"Mercy", "Symmetra", "Zenyatta"};


void setup() {
  // put your setup code here, to run once:
//Serial.begin(9600);
  
  // initialize LCD
  lcd.begin(16, 2);
  clearled();

  // initialize buttons
  // initialize the pushbutton pins as an input:
  pinMode(buttonPinCIV, INPUT);
  pinMode(buttonPinOW, INPUT);
}

void clearled()
{
  lcd.setCursor(0, 0);
  lcd.write("Randomize!");
  lcd.setCursor(0,1);
  lcd.write("                ");
}

void writeled(String msg)
{
    lcd.setCursor(0,1);
  lcd.write("                ");
  lcd.setCursor(0, 1);
  lcd.print(msg);
}

void loop() {;

// read the state of the pushbutton value:
  buttonStateCIV = digitalRead(buttonPinCIV);
  buttonStateOW = digitalRead(buttonPinOW);

//------------ CIV
  // If the switch changed, due to noise or pressing:
  if (buttonStateCIV != buttonStateCIVLast) {
    //Serial.print("CIV = Change\n");
    lastDebounceTimeCIV = millis();
  }

  if ((millis() - lastDebounceTimeCIV) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:
    // randomize
    // if the button state has changed:
    if (buttonStateCIV != buttonStateCIVCurrent) {
      buttonStateCIVCurrent = buttonStateCIV;
    }
    // only randomize if the new button state is HIGH
      if (buttonStateCIVCurrent == HIGH) {
        writeled(randomizeCIV());
      }
  } 
  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  buttonStateCIVLast = buttonStateCIV;


//------------ Overwatch

// If the switch changed, due to noise or pressing:
  if (buttonStateOW != buttonStateOWLast) {
    //Serial.print("OW = Change\n");
    lastDebounceTimeOW = millis();
  }

  if ((millis() - lastDebounceTimeOW) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:
    // randomize
    // if the button state has changed:
    if (buttonStateOW != buttonStateOWCurrent) {
      buttonStateOWCurrent = buttonStateOW;
    }
    // only randomize if the new button state is HIGH
      if (buttonStateOWCurrent == HIGH) {
        writeled(randomizeOW());
      }
  }
   
  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  buttonStateOWLast = buttonStateOW;

}

String randomizeOW()
{
  //Serial.print("RandomizeOW\n");
  int rndOW = random(numberOfOwChars);
  //Serial.print("rndOW="+rndOW);
  return owChars[rndOW];
}

String randomizeCIV()
{
    //Serial.print("randomizeCIV\n");
  int rndCIV = random(numberOfCivs);
    //Serial.print("rndCIV="+rndCIV);
  return civs[rndCIV];
}


