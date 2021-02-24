/*
   This file declaer the UI calss and some variables

                        |  layer1 menu  |  layer2 menu    |  layer3 menu    |
                        ____________________________________________________
                        |- Channel 1 ---|- Waveform Type -|- sine
                        |               |                 |- triangle
                        |               |                 |- square
                        |               |                 |- Back
                        |               |
                        |               |- Frequency ------- number setting (12.5M Hz)
                        |               |                 |- Back
                        |               |
                        |               |- Phase     ------- number setting (360 degree)
                        |               |                 |- Back
                        |               |- Back
                        |
                        |- Channel 2 ---|- Waveform Type -|- sine
                        |               |                 |- triangle
                        |               |                 |- square
                        |               |                 |- Back
                        |               |
                        |               |- Frequency ------- number setting (12.5M Hz)
                        |               |                 |- Back
                        |               |
                        |               |- Phase     ------- number setting (360 degree)
                        |               |                 |- Back
                        |               |- Back
*/


//------------------------------- Channel select menu -----------------------------

class menuPage1 {
  public:
    void show(bool &updateLcd, int &rotary, byte &temp);
  private:
};

void menuPage1::show(bool &updateLcd, int &rotary, byte &temp) {

  if (updateLcd) {
    RSCG12864B.clear();
    rotary = 0;
    RSCG12864B.draw_rectangle(0, 0, 127, 63);    //Draw outline rectangle
    RSCG12864B.print_string_5x7_xy(9, 2, "Select Channel");
    RSCG12864B.print_string_5x7_xy(9, 10, "Channel 1");
    RSCG12864B.print_string_5x7_xy(9, 18, "Channel 2");
    updateLcd = false;
  }

  if (rotary > 1)
    rotary = 0;
  else if (rotary < 0)
    rotary = 1;

  switch (rotary) {
    case (0):   //Select channel 1
      RSCG12864B.print_string_5x7_xy(3, 10, ">");
      RSCG12864B.print_string_5x7_xy(3, 18, " ");
      temp = 0;

      break;
    case (1):   //Select channel 2
      RSCG12864B.print_string_5x7_xy(3, 10, " ");
      RSCG12864B.print_string_5x7_xy(3, 18, ">");
      temp = 1;
      break;
  }
}

//------------------------------- Channel setting menu ---------------------

class menuPage2 {
  public:
    void show(bool &updateLcd, int &rotary, byte &temp, bool &back);
  private:
};

void menuPage2::show(bool &updateLcd, int &rotary, byte &temp, bool &back) {
  if (updateLcd) {
    RSCG12864B.clear();
    rotary = 0;
    RSCG12864B.draw_rectangle(0, 0, 127, 63);    //Draw outline rectangle
    RSCG12864B.print_string_5x7_xy(9, 2, "Settings");
    RSCG12864B.print_string_5x7_xy(9, 10, "Waveform Type");
    RSCG12864B.print_string_5x7_xy(9, 18, "Frequency");
    RSCG12864B.print_string_5x7_xy(9, 26, "Phase");
    RSCG12864B.print_string_5x7_xy(9, 34, "Back");
    updateLcd = false;
  }

  if (rotary > 3)
    rotary = 0;
  else if (rotary < 0)
    rotary = 3;

  switch (rotary) {
    case (0):   //Wavwform type setting
      RSCG12864B.print_string_5x7_xy(3, 34, " ");
      RSCG12864B.print_string_5x7_xy(3, 10, ">");
      RSCG12864B.print_string_5x7_xy(3, 18, " ");
      temp = 0;
      break;
    case (1):   //Frequency setting
      RSCG12864B.print_string_5x7_xy(3, 10, " ");
      RSCG12864B.print_string_5x7_xy(3, 18, ">");
      RSCG12864B.print_string_5x7_xy(3, 26, " ");
      temp = 1;
      break;
    case (2):   //Phase setting
      RSCG12864B.print_string_5x7_xy(3, 18, " ");
      RSCG12864B.print_string_5x7_xy(3, 26, ">");
      RSCG12864B.print_string_5x7_xy(3, 34, " ");
      temp = 2;
      break;
    case (3):   //go back
      RSCG12864B.print_string_5x7_xy(3, 26, " ");
      RSCG12864B.print_string_5x7_xy(3, 34, ">");
      RSCG12864B.print_string_5x7_xy(3, 10, " ");
      back = true;
      break;
  }
}

//------------------------------- Waveform setting menu --------------------------------

class menuPage3 {
  public:
    void show(bool &updateLcd, int &rotary, byte &temp, bool &back);
  private:
};

void menuPage3::show(bool &updateLcd, int &rotary, byte &temp, bool &back) {

  if (updateLcd) {
    RSCG12864B.clear();
    rotary = 0;
    RSCG12864B.draw_rectangle(0, 0, 127, 63);    //Draw outline rectangle
    RSCG12864B.print_string_5x7_xy(9, 2, "Waveform Type:");
    RSCG12864B.print_string_5x7_xy(9, 10, "Sine wave");
    RSCG12864B.print_string_5x7_xy(9, 18, "Triangle wave");
    RSCG12864B.print_string_5x7_xy(9, 26, "Square wave");
    RSCG12864B.print_string_5x7_xy(9, 34, "Back");
    updateLcd = false;
  }

  if (rotary > 3)
    rotary = 0;
  else if (rotary < 0)
    rotary = 3;

  switch (rotary) {
    case (0):   //Wavwform type setting
      RSCG12864B.print_string_5x7_xy(3, 34, " ");
      RSCG12864B.print_string_5x7_xy(3, 10, ">");
      RSCG12864B.print_string_5x7_xy(3, 18, " ");
      temp = 0;
      break;
    case (1):   //Frequency setting
      RSCG12864B.print_string_5x7_xy(3, 10, " ");
      RSCG12864B.print_string_5x7_xy(3, 18, ">");
      RSCG12864B.print_string_5x7_xy(3, 26, " ");
      temp = 1;
      break;
    case (2):   //Phase setting
      RSCG12864B.print_string_5x7_xy(3, 18, " ");
      RSCG12864B.print_string_5x7_xy(3, 26, ">");
      RSCG12864B.print_string_5x7_xy(3, 34, " ");
      temp = 2;
      break;
    case (3):   //go back
      RSCG12864B.print_string_5x7_xy(3, 26, " ");
      RSCG12864B.print_string_5x7_xy(3, 34, ">");
      RSCG12864B.print_string_5x7_xy(3, 10, " ");
      back = true;
      break;
  }
}

//------------------------------- Frequency setting menu -----------------------------------

class menuPage4 {
  public:
    void show(bool &updateLcd, int &rotary, byte &temp, bool &back, byte &channel, uint32_t &freq1, uint32_t &freq2, bool &setFreq);
  private:
};

void menuPage4::show(bool &updateLcd, int &rotary, byte &temp, bool &back, byte &channel, uint32_t &freq1, uint32_t &freq2, bool &setFreq) {

  if (updateLcd) {
    RSCG12864B.clear();
    rotary = 0;
    RSCG12864B.draw_rectangle(0, 0, 127, 63);    //Draw outline rectangle
    RSCG12864B.print_string_5x7_xy(9, 2, "Set frequency");
    RSCG12864B.print_string_5x7_xy(60, 10, "Hz");
    if (channel == 0)
      RSCG12864B.print_U32_5x7_xy(9, 10, freq1);
    else if (channel == 1)
      RSCG12864B.print_U32_5x7_xy(9, 10, freq2);
    RSCG12864B.print_string_5x7_xy(9, 18, "Back");
    updateLcd = false;
  }

  if (rotary > 1)
    rotary = 0;
  else if (rotary < 0)
    rotary = 1;

  switch (rotary) {
    case (0):   //Setting frequency
      RSCG12864B.print_string_5x7_xy(3, 10, ">");
      RSCG12864B.print_string_5x7_xy(3, 18, " ");
      temp = 0;

      break;
    case (1):   //go back
      RSCG12864B.print_string_5x7_xy(3, 10, " ");
      RSCG12864B.print_string_5x7_xy(3, 18, ">");
      back = true;
      break;
  }
}

//------------------------------- Phase select menu --------------------------

class menuPage5 {
  public:
    void show(bool &updateLcd, int &rotary, byte &temp, bool &back);
  private:
};

void menuPage5::show(bool &updateLcd, int &rotary, byte &temp, bool &back) {

  if (updateLcd) {
    RSCG12864B.clear();
    rotary = 0;
    RSCG12864B.draw_rectangle(0, 0, 127, 63);    //Draw outline rectangle
    RSCG12864B.print_string_5x7_xy(9, 2, "Setting phase:");
    RSCG12864B.print_string_5x7_xy(9, 10, "  0 degree");
    RSCG12864B.print_string_5x7_xy(9, 18, "Back");
    updateLcd = false;
  }

  if (rotary > 1)
    rotary = 0;
  else if (rotary < 0)
    rotary = 1;

  switch (rotary) {
    case (0):   //Setting phase
      RSCG12864B.print_string_5x7_xy(3, 10, ">");
      RSCG12864B.print_string_5x7_xy(3, 18, " ");
      temp = 0;

      break;
    case (1):   //go back
      RSCG12864B.print_string_5x7_xy(3, 18, ">");
      RSCG12864B.print_string_5x7_xy(3, 10, " ");
      back = true;
      break;
  }
}
