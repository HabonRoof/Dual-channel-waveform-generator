/*
  This is a dual channel wave form generator firmware
  Use AD9833 DDS signal generator as main function IC
  Hardware schematic please visit @habonroof github

  Author: Chun-Lin Chen (HabonRoof)
  License: CC-BY 3.0

*/

//---------------- Object declear -------------------------

#include <AD9833.h>         //Include AD9833 library from BillWilliams1952 @https://github.com/Billwilliams1952/AD9833-Library-Arduino
#include <RSCG12864B.h>     //Include RSCG12864 LCD module library. If you use another LCD, please modify the library as your LCD display.
#include <RotaryEncoder.h>  //Include awesome rotary encoder library from mathertel @https://github.com/brianlow/Rotary

#define FNC_PIN     10      // Function pin of first AD9833 module
#define FNC_PIN2    8       // Function pin of second AD9833 module

#define Enable      4       // Enable output
#define Enter       1       // Rotary encoder button

RotaryEncoder encoder(2, 3);// Rotary encoder connect pin. I converte the pins into "pin change interrupt" mode to responce faster


//--------------- Create an AD9833 object ----------------

// Note, SCK and MOSI must be connected to CLK and DAT pins on the AD9833 for SPI
AD9833 gen(FNC_PIN);        //Declare gen object as first AD9833 module
AD9833 gen2(FNC_PIN2);      //Declare gen2 object as second AD9833 module
WaveformType ch1_waveform;  //Declare "ch1_waveform"and "ch2_waveform" as a WaveformType variable (from AD9833.h)
WaveformType ch2_waveform;  //SINE_WAVE = 0x2000, TRIANGLE_WAVE = 0x2002,
//SQUARE_WAVE = 0x2028, HALF_SQUARE_WAVE = 0x2020
//---------------- LCD variable ---------------------------

#define LCD_Width 128      //LCD width
#define LCD_high 64        //LCD high

#define DEBUG_EN    0    // 1:Enable Serial debugging 0:disable

//----------------- Useful flags ---------------------------

bool SW_state = false;
bool lcd_need_refresh = true;

//-------------- Button debounce ----------------------------

//  Reference: https://www.arduino.cc/en/Tutorial/BuiltInExamples/Debounce

int btn_press = 0;
int buttonState;
int lastButtonState = 0;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
int pos = 0;                       // position of rotary encoder
unsigned long systemtick = 50;
unsigned long lastmillis = 0;

//---------------- UI variable --------------------------------



//    Define the specific int as the switch case
#define CH1_Wave    1
#define CH1_Freq    2
#define CH1_Phase   3
#define CH2_Wave    4
#define CH2_Freq    5
#define CH2_Phase   6
#define about       7


byte menu_state = 0;
byte L1_Ctr = 1;    //Level 1 menu counter
byte L2_Ctr = 1;    //Level 2 menu counter
byte L3_Ctr = 1;    //Level 3 menu counter
byte L4_Ctr = 1;    //Level 4 menu counter
byte L5_Ctr = 1;    //Level 5 menu counter
byte L6_Ctr = 1;    //Level 6 menu counter
byte esc    = 0;    //escape to main menu
byte into   = 0;    //go into next UI level



//---------------- Sub function declare ---------------

void Output_EN();
void read_btn();
void lcd_main_menu();
void lcd_boot_screen();
void lcd_about_screen();
void AD9833_init();


//---------------- Main loop --------------------------

void setup() {
#if DEBUG_EN > 0
  Serial.begin(115200);
#endif
  pinMode(Enable, INPUT_PULLUP);
  pinMode(Enter, INPUT_PULLUP);
  RSCG12864B.begin();
  RSCG12864B.brightness(255);

  // You may have to modify the next 2 lines if using other pins than A2 and A3
  PCICR   |= (1 << PCIE2);    // This enables Pin Change Interrupt 1 that covers the Analog input pins or Port C.
  PCMSK2  |= (1 << PCINT18) | (1 << PCINT19);  // This enables the interrupt for pin 2 and 3 of Port C.

  RSCG12864B.clear();
  AD9833_init();


#if DEBUG_EN > 0
  Serial.println("Boot Done");
#endif

  lcd_boot_screen();
}

// The Interrupt Service Routine for Pin Change Interrupt 1
// This routine will only be called on any signal change on A2 and A3: exactly where we need to check.
ISR(PCINT2_vect) {
  encoder.tick(); // just call tick() to check the state.
}

void loop() {


#if DEBUG_EN >0
  Serial.print("pos = ");
  Serial.println(pos);
  Serial.print("btn_press = ");
  Serial.println(btn_press);
#endif
  //Read the button state is pressed or not
  read_btn();
  //refresh the lcd if needed
  if (lcd_need_refresh || esc == 1) {
    lcd_main_menu();
    lcd_need_refresh = false;
  }

  RotaryEncoder::Direction currentDirection = encoder.getDirection();    //Check the rotary direction variable are from Rotary library .cpp file
  //Remember check the enum variable
  if (currentDirection == RotaryEncoder::Direction::COUNTERCLOCKWISE )
    pos--;
  else if (currentDirection == RotaryEncoder::Direction::CLOCKWISE)
    pos++;

  if (pos < 0)
    pos = 7;
  else if (pos > 7)
    pos = 0;

  if (millis() - lastmillis > systemtick) {         //Use this statement to replace delay() function
    switch (pos) {
      case CH1_Wave:
        RSCG12864B.print_string_5x7_xy(2, 34, " ");
        RSCG12864B.print_string_5x7_xy(2, 10, ">");
        RSCG12864B.print_string_5x7_xy(2, 18, " ");
        if (into == 1 || L1_Ctr == 1) {
          L1_Ctr++;
          into = 0;
          lcd_CH1_wave_screen();
        }
        break;

      case CH1_Freq:
        RSCG12864B.print_string_5x7_xy(2, 10, " ");
        RSCG12864B.print_string_5x7_xy(2, 18, ">");
        RSCG12864B.print_string_5x7_xy(2, 26, " ");
        break;

      case CH1_Phase:
        RSCG12864B.print_string_5x7_xy(2, 18, " ");
        RSCG12864B.print_string_5x7_xy(2, 26, ">");
        RSCG12864B.print_string_5x7_xy(74, 10, " ");
        break;

      case CH2_Wave:
        RSCG12864B.print_string_5x7_xy(2, 26, " ");
        RSCG12864B.print_string_5x7_xy(74, 10, ">");
        RSCG12864B.print_string_5x7_xy(74, 18, " ");
        break;

      case CH2_Freq:
        RSCG12864B.print_string_5x7_xy(74, 10, " ");
        RSCG12864B.print_string_5x7_xy(74, 18, ">");
        RSCG12864B.print_string_5x7_xy(74, 26, " ");
        break;

      case CH2_Phase:
        RSCG12864B.print_string_5x7_xy(74, 18, " ");
        RSCG12864B.print_string_5x7_xy(74, 26, ">");
        RSCG12864B.print_string_5x7_xy(2, 34, " ");
        break;
      case about:
        RSCG12864B.print_string_5x7_xy(74, 26, " ");
        RSCG12864B.print_string_5x7_xy(2, 34, ">");
        RSCG12864B.print_string_5x7_xy(2, 18, " ");
        if (into == 1) {
          into = 0;
          lcd_about_screen();
        }
        break;
      default:
        RSCG12864B.print_string_5x7_xy(2, 34, " ");
        RSCG12864B.print_string_5x7_xy(2, 10, " ");
        RSCG12864B.print_string_5x7_xy(2, 18, " ");
        break;
    }



    Output_EN();
    lastmillis = millis();

  }
}


//---------------- Initialize AD9833 module --------------------------

void AD9833_init() {
  // This MUST be the first command after declaring the AD9833 object
  gen.Begin();
  gen2.Begin();

  // Apply a 1000 Hz sine wave using REG0 (register set 0). There are two register sets,
  // REG0 and REG1.
  // Each one can be programmed for:
  //   Signal type - SINE_WAVE, TRIANGLE_WAVE, SQUARE_WAVE, and HALF_SQUARE_WAVE
  //   Frequency - 0 to 12.5 MHz
  //   Phase - 0 to 360 degress (this is only useful if it is 'relative' to some other signal
  //           such as the phase difference between REG0 and REG1).
  // In ApplySignal, if Phase is not given, it defaults to 0.
  gen.ApplySignal(SINE_WAVE, REG0, 10000000);
  gen2.ApplySignal(SINE_WAVE, REG0, 5000000);
  // There should be a 1000 Hz sine wave on the output of the AD9833
}

//------------------ Enable the output waveform -------------------------

void Output_EN() {
  if (!digitalRead(Enable)) {
    gen.EnableOutput(true);   // Turn ON the output - it defaults to OFF
    gen2.EnableOutput(true);
    RSCG12864B.draw_fill_circle(60, 5, 2);
    RSCG12864B.draw_fill_circle(105, 5, 2);
  }
  else {
    gen.EnableOutput(false);   // Turn OFF the output
    gen2.EnableOutput(false);
    RSCG12864B.delete_fill_circle(60, 5, 2);
    RSCG12864B.delete_fill_circle(105, 5, 2);
  }
}

//------------------- read the button is pressed or not --------------------

void read_btn() {


  // set the LCD:
  if (into == 1)
    RSCG12864B.draw_fill_circle(119, 57, 2);
  else if (into == 0)
    RSCG12864B.delete_fill_circle(119, 57, 2);
  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}
