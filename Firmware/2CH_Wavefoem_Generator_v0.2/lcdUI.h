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
    RSCG12864B.print_string_5x7_xy(9, 10, "channel 1");
    RSCG12864B.print_string_5x7_xy(9, 18, "channel 2");
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
      RSCG12864B.print_string_5x7_xy(3, 18, ">");
      RSCG12864B.print_string_5x7_xy(3, 10, " ");
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
    void show(bool &updateLcd, int &rotary, byte &temp, bool &back);
  private:
};

void menuPage4::show(bool &updateLcd, int &rotary, byte &temp, bool &back) {

  if (updateLcd) {
    RSCG12864B.clear();
    rotary = 0;
    RSCG12864B.draw_rectangle(0, 0, 127, 63);    //Draw outline rectangle
    RSCG12864B.print_string_5x7_xy(9, 2, "Setting frequency");
    //這裡要依照頻率digit選擇 總共7位數 所以要有8個case(?
    RSCG12864B.print_string_5x7_xy(9, 10, "1000 Hz");
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
    RSCG12864B.print_string_5x7_xy(9, 2, "Setting phase");
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
