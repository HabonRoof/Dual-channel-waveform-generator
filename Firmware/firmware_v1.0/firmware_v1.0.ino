/*
  This is a dual channel wave form generator firmware
  Use AD9833 DDS signal generator as main function IC
  Hardware schematic please visit @habonroof github

  Author: Chun-Lin Chen (HabonRoof)
  License: CC-BY 3.0

  Update: 2021/02/28
  Feature:Add channel status page at main menu
  Fix the accurate of frequency issue
  Add channel indicator on each setting screen to ensure user know which channel is he setting
  Issue:
  Phase function not avaliable
  The USB-TTL cable will interference the module signal, but not effect at output.
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
AD9833 gen(FNC_PIN, 24000000);       //Declare gen object as first AD9833 module
AD9833 gen2(FNC_PIN2, 24000000);     //Declare gen2 object as second AD9833 module

float ch1Freq = 1000.0;
float ch1Phase = 0;

float ch2Freq = 1000.0;
float ch2Phase = 0;
bool ad9833Update = false;

//--------------------- Serial Debug ------------------------

#define DEBUG  1    // 1:Enable Serial debugging 0:disable

//---------------------- Useful flags -----------------------

bool switchState = false;
bool lcdNeedUpdate = true;


//----------------------- UI variable ------------------------

int rotaryCtr = 0;
int buttonCtr = 0;
int oldButtonCtr = 0;
byte layer1Item = 0;
byte layer2Item = 0;
byte layer3Item = 0;
byte layer1Temp = 0;
byte layer2Temp = 0;
byte layer3Temp = 0;
bool back = false;
bool resetFlag = false;
bool setFreq = false;
bool setPhase = false;
float newFreq = 0.0;
byte ch1Waveform = 0;   //0 = sine, 1 = triangle, 2 = square
byte ch2Waveform = 0;

menuPage1 mainMenu;
menuPage2 channel;
menuPage3 waveform;
menuPage4 frequency;
menuPage5 phase;


void lcdShowMenu();
void lcdBootScreen();
void lcdAboutScreen();
void lcdSetFrequency();


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
void ad9833Run();    //Update the AD9833 module for new configuration
void outputChecker();   //Check the output switch
void resetMenuItem();
unsigned long power();  //instead using pow()function because there is an error instead accurate value

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
  outputChecker();    // Enable oputput
  buttonChecker();
  rotaryChecker();
  lcdShowMenu();
  ad9833Run();
  resetMenuItem();
#ifdef DEBUG
  Serial.print("setFreq:");
  Serial.println(setFreq);
  Serial.print("oldButtonCtr:");
  Serial.println(oldButtonCtr);
  Serial.print("newFreq:");
  Serial.println(newFreq);
  Serial.print("buttonCtr:");
  Serial.println(buttonCtr);
  Serial.print("layer1Item:");
  Serial.println(layer1Item);
  Serial.print("layer2Item:");
  Serial.println(layer2Item);
  Serial.print("layer3Item:");
  Serial.println(layer3Item);
  Serial.println();
#endif
  delay(50);
}

void resetMenuItem() {
  if (resetFlag) {
    resetFlag = false;
    layer1Temp = 0;
    layer2Temp = 0;
    layer3Temp = 0;
    layer1Item = 0;
    layer2Item = 0;
    layer3Item = 0;
#ifdef DEBUG
    Serial.println("Reset menu item");
#endif
  }
}

void ad9833Run() {
  if (ad9833Update) {
    Serial.println("ad9833 update!!!");
    ad9833Update = false;
    if (layer1Item == 0) {
      if (layer2Item == 0) {
        //setting CH1 waveform type
        if (layer3Item == 0) {
          //CH1 sinewave
          gen.SetWaveform(REG0, SINE_WAVE);
          ch1Waveform = 0;
          resetFlag = true;
        }
        else if (layer3Item == 1) {
          //CH1 triangle wave
          gen.SetWaveform(REG0, TRIANGLE_WAVE);
          ch1Waveform = 1;
          resetFlag = true;
        }
        else {
          //CH1 square wave
          gen.SetWaveform(REG0, SQUARE_WAVE);
          ch1Waveform = 2;
          resetFlag = true;
        }
      }
      else if (layer2Item == 1) {
        //setting CH1 frequency
        if (layer3Item == 0) {
          gen.SetFrequency(REG0, ch1Freq);
          resetFlag = true;
        }
      }
      else {
        //setting CH1 phase
        gen.SetPhase(REG0, ch1Phase);
        //setPhase = true;
        resetFlag = true;
      }
    }
    else {
      if (layer2Item == 0) {
        //setting CH2 waveform type
        if (layer3Item == 0) {
          //CH2 sinewave
          gen2.SetWaveform(REG0, SINE_WAVE);
          ch2Waveform = 0;
          resetFlag = true;
        }
        else if (layer3Item == 1) {
          //CH2 triangle wave
          gen2.SetWaveform(REG0, TRIANGLE_WAVE);
          ch2Waveform = 1;
          resetFlag = true;
        }
        else {
          //CH2 square wave
          gen2.SetWaveform(REG0, SQUARE_WAVE);
          ch2Waveform = 2;
          resetFlag = true;
        }
      }
      else if (layer2Item == 1) {
        //setting CH2 frequency
        if (layer3Item == 0) {
          gen2.SetFrequency(REG0, ch2Freq);
          resetFlag = true;
        }
      }
      else {
        //setting CH2 phase
        gen2.SetPhase(REG0, ch2Phase);
        resetFlag = true;
      }
    }
  }
}

void lcdShowMenu() {
  if (buttonCtr == 0) //Channel select
    mainMenu.show(lcdNeedUpdate, rotaryCtr, layer1Temp, ch1Freq, ch2Freq, ch1Waveform, ch2Waveform);
  else if (buttonCtr == 1)  //Setting select
    channel.show(lcdNeedUpdate, rotaryCtr, layer2Temp, back, layer1Item);
  else if (buttonCtr == 2)  //channel waveform setting
    switch (layer2Item) {
      case (0):   //Waveform select
        waveform.show(lcdNeedUpdate, rotaryCtr, layer3Temp, back, layer1Item);
        break;
      case (1):   //Frequency setting
        frequency.show(lcdNeedUpdate, rotaryCtr, layer3Temp, back, layer1Item, ch1Freq, ch2Freq, setFreq, layer1Item);
        break;
      case (2):   //Phase setting
        phase.show(lcdNeedUpdate, rotaryCtr, layer3Temp, back);
        break;
    }
  else if (buttonCtr > 2) { //only frequency setting and phase setting can go into this case
    if (layer2Item == 1) {
      Serial.println("frequency hertz");
      lcdSetFrequency();

      if (buttonCtr > 11) { //reset buttonCtr when done freq setting
        buttonCtr = 0;
        ad9833Update = true;
      }
    }
    else if (layer2Item == 2) {
      Serial.println("phase degree");

      if (buttonCtr > 5) { //reset buttonCtr when done phase setting
        buttonCtr = 0;
        ad9833Update = true;
      }
    }
    else {
      buttonCtr = 0;
      ad9833Update = true;
    }
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
    layer1Item = layer1Temp;    //Update layerItem to layerTemp when press button
    layer2Item = layer2Temp;
    layer3Item = layer3Temp;
    buttonCtr ++;
    if (back) {
      buttonCtr = buttonCtr - 2;
      back = false;
      lcdNeedUpdate = true;
    }
  }
}



void lcdSetFrequency() {
  float oldFreq = 0.0;
  byte xPos = 9;

  if (lcdNeedUpdate && !setFreq) {
    RSCG12864B.clear();
    rotaryCtr = 0;
    RSCG12864B.draw_rectangle(0, 0, 127, 63);    //Draw outline rectangle
    RSCG12864B.print_string_5x7_xy(9, 2, "New frequency:");
    if (layer1Item == 0)
      oldFreq = ch1Freq;
    else if (layer1Item == 1)
      oldFreq = ch2Freq;
    RSCG12864B.print_string_5x7_xy(9, 10, "00000000"); 	//clear oldFreq screen
    RSCG12864B.print_string_5x7_xy(60, 10, "Hz");
    setFreq = true;
    lcdNeedUpdate = false;
  }

  if (rotaryCtr > 9)
    rotaryCtr = 0;
  else if (rotaryCtr < 0)
    rotaryCtr = 9;

  if ((buttonCtr < 11) && setFreq) {
    xPos = xPos + ((buttonCtr - 3) * 6);
    RSCG12864B.cursor(xPos, 10);
    RSCG12864B.print_U32_5x7(rotaryCtr);
    if (buttonCtr != oldButtonCtr) { //When buttonCtr change, update newFreq once
      oldButtonCtr = buttonCtr;  //Update oldButtonCtr
      newFreq = newFreq + rotaryCtr * power(10, (11 - buttonCtr));
      Serial.print("New Frequemcy:");
      Serial.println(newFreq);
    }
  }
  if (buttonCtr == 11) {
    if (lcdNeedUpdate) {
      RSCG12864B.clear();
      lcdNeedUpdate = false;
      newFreq = newFreq + rotaryCtr * power(10, (11 - buttonCtr));
      RSCG12864B.draw_rectangle(0, 0, 127, 63);    //Draw outline rectangle
      if (layer1Item == 0)
        RSCG12864B.print_string_5x7_xy(9, 2, "Set CH1 freq to");
      else if (layer1Item == 1)
        RSCG12864B.print_string_5x7_xy(9, 2, "Set CH2 freq to");
      RSCG12864B.print_U32_5x7_xy(9, 10, newFreq);  //clear oldFreq screen
      RSCG12864B.print_string_5x7_xy(60, 10, "Hz");
    }
  }
  if (buttonCtr > 11) {
    if (layer1Item == 0)
      ch1Freq = newFreq;
    else if (layer1Item == 1)
      ch2Freq = newFreq;
    oldButtonCtr = 0;
    newFreq = 0;
    ad9833Update = true;
    resetFlag = true;
    setFreq = false;
  }
}

bool buttonPress() {
  if ((millis() - lastButtonPress) > 100) {
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

void outputChecker() {
  if (!digitalRead(Enable)) {
    gen.EnableOutput(true);   // Turn ON the output
    gen2.EnableOutput(true);
    RSCG12864B.draw_fill_circle(122, 5, 2);
  }
  else {
    gen.EnableOutput(false);   // Turn OFF the output
    gen2.EnableOutput(false);
    RSCG12864B.delete_fill_circle(122, 5, 2);
  }
}

unsigned long power(int base, int exponent) {
  unsigned long result;
  if (exponent == 0) {
    result = 1;
  } else {
    result = base;
    for (int i = 0; i < (exponent - 1); i++) {
      result *= base;
    }
  }
  return result;
}
