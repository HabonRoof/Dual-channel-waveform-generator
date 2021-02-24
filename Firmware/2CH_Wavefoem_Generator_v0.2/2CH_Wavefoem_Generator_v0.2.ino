/*
  This is a dual channel wave form generator firmware
  Use AD9833 DDS signal generator as main function IC
  Hardware schematic please visit @habonroof github

  Author: Chun-Lin Chen (HabonRoof)
  License: CC-BY 3.0

*/

#include <AD9833.h>         //Include AD9833 library from BillWilliams1952 @https://github.com/Billwilliams1952/AD9833-Library-Arduino
#include <RSCG12864B.h>     //Include RSCG12864 LCD module library. If you use another LCD, please modify the library as your LCD display.
#include <RotaryEncoder.h>  //Include awesome rotary encoder library from mathertel @https://github.com/brianlow/Rotary
#include "lcdUI.h"

//------------------ Pin configuration ----------------------

#define FNC_PIN     10      // Function pin of first AD9833 module
#define FNC_PIN2    8       // Function pin of second AD9833 module
#define Enable      4       // Enable output
#define Enter       1       // Rotary encoder button

RotaryEncoder encoder(2, 3);// Rotary encoder connect pin. I converte the pins into "pin change interrupt" mode to responce faster



//------------------- Create an AD9833 object ---------------

// Note, SCK and MOSI must be connected to CLK and DAT pins on the AD9833 for SPI
AD9833 gen(FNC_PIN);        //Declare gen object as first AD9833 module
AD9833 gen2(FNC_PIN2);      //Declare gen2 object as second AD9833 module

//--------------------- Serial Debug ------------------------

#define DEBUG  0    // 1:Enable Serial debugging 0:disable

//---------------------- Useful flags -----------------------

bool switchState = false;
bool lcdNeedUpdate = true;



//----------------------- UI variable ------------------------

int rotaryCtr = 0;
int menuCtr = 0;
byte layer1Item = 0;
byte layer2Item = 0;
byte layer3Item = 0;
byte layer1Temp = 0;
byte layer2Temp = 0;
byte layer3Temp = 0;
bool back = false;


menuPage1 mainMenu;
menuPage2 channel;
menuPage3 waveform;
menuPage4 frequency;
menuPage5 phase;


void lcdShowMenu();
void lcdBootScreen();
void lcdAboutScreen();




//---------------------- Debounce --------------------------
unsigned long lastButtonPress = 0;
bool lastButtonState = true;
bool buttonState = true;

//---------------------- Sub function -----------------------

void ad9833Init();
void lcdBootScreen();   //Indicate the boot screen
void buttonChecker();   //Check the button and the rotary encoder
bool buttonPress();     //If button pressed, return true
void rotaryChecker();   //Check the rotary encoder value
void lcdShowMenu();
//void ad9833Update();    //Update the AD9833 module for new configuration

//------------------------ ISR --------------------------------

ISR(PCINT2_vect) {
  encoder.tick();
}

//------------------------ Setup -----------------------------

void setup() {

#ifdef DEBUG
  Serial.begin(115200);
#endif

  PCICR   |= (1 << PCIE2);    // Enables Pin Change Interrupt 1 that covers the Analog input pins or Port C.
  PCMSK2  |= (1 << PCINT18) | (1 << PCINT19);  // This enables the interrupt for pin 2 and 3 of Port C.

  pinMode(Enable, INPUT_PULLUP);
  pinMode(Enter, INPUT);
  RSCG12864B.begin();
  RSCG12864B.brightness(255);
  RSCG12864B.clear();
  ad9833Init();
  lcdBootScreen();
  lastButtonPress = millis();   //Set last button press time to millis()
}

//----------------------- Main loop --------------------------------

void loop() {
  //switchChecker();    // Enable oputput
  buttonChecker();
  rotaryChecker();
  lcdShowMenu();

  delay(50);
}

void lcdShowMenu() {
  switch (menuCtr) {
    case (0):   //Channel select
      mainMenu.show(lcdNeedUpdate, rotaryCtr, layer1Temp);
      break;
    case (1):   //Channel setting select
      channel.show(lcdNeedUpdate, rotaryCtr, layer2Temp, back);
      break;
    case (2):
      switch (layer2Item) {
        case (0):
          waveform.show(lcdNeedUpdate, rotaryCtr, layer3Temp, back);
          break;
        case (1):
          frequency.show(lcdNeedUpdate, rotaryCtr, layer3Temp, back);
          break;
        case (2):
          phase.show(lcdNeedUpdate, rotaryCtr, layer3Temp, back);
          break;
      }
      break;
  }
}

void rotaryChecker() {
  RotaryEncoder::Direction currentDirection = encoder.getDirection();
  if (currentDirection == RotaryEncoder::Direction::COUNTERCLOCKWISE)
    rotaryCtr--;
  else if (currentDirection == RotaryEncoder::Direction::CLOCKWISE)
    rotaryCtr++;
}


void buttonChecker() {
  if (buttonPress()) {
    buttonState = false;
    layer1Item = layer1Temp;    //Update layer variable when press button
    layer2Item = layer2Temp;
    layer3Item = layer2Temp;
    menuCtr ++;
    if (back) {
      menuCtr = menuCtr - 2;
      back = false;
      lcdNeedUpdate = true;
    }
    if (menuCtr > 2)     //go back to main menu when menu counter > 2
      menuCtr = 0;
  }
}


bool buttonPress() {
  if ((millis() - lastButtonPress) > 150) {
    if (digitalRead(Enter) != lastButtonState) {
      buttonState = digitalRead(Enter);
      lastButtonState = buttonState;
      lastButtonPress = millis();
      if (buttonState == LOW) {
        lcdNeedUpdate = true;
        return true;
      }
    }
  }
  return false;
}

void ad9833Init() {
  gen.Begin();
  gen2.Begin();
  gen.ApplySignal(SINE_WAVE, REG0, 1000);
  gen2.ApplySignal(SINE_WAVE, REG0, 1000);
}
