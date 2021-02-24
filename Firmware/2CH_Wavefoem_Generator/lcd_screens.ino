

//------------------------ BOOT SCREEN ------------------
void lcd_boot_screen() {
  RSCG12864B.clear();
  RSCG12864B.print_string_16_xy(24, 0, "AD9833 2CH");
  RSCG12864B.print_string_16_xy(32, 16, "Waveform");
  RSCG12864B.print_string_16_xy(24, 32, "Generator");
  RSCG12864B.print_string_16_xy(24, 48, "Ver. 1.0.0");
  delay(1000);
}

//------------------------ MAIN MENU ------------------
void lcd_main_menu() {
  RSCG12864B.clear();
  RSCG12864B.draw_rectangle(0, 0, 127, 63);
  RSCG12864B.print_string_5x7_xy(35, 2, "CH1");
  RSCG12864B.print_string_5x7_xy(80, 2, "CH2");
  RSCG12864B.print_string_5x7_xy(8, 10, "Wave");
  RSCG12864B.print_string_5x7_xy(35, 10, "Sine");
  RSCG12864B.print_string_5x7_xy(80, 10, "Trig");
  RSCG12864B.print_string_5x7_xy(8, 18, "Freq");
  RSCG12864B.print_string_5x7_xy(35, 18, "100k");
  RSCG12864B.print_string_5x7_xy(80, 18, "10M");
  RSCG12864B.print_string_5x7_xy(8, 26, "Phas");
  RSCG12864B.print_string_5x7_xy(35, 26, "30");
  RSCG12864B.print_string_5x7_xy(80, 26, "0");
  RSCG12864B.print_string_5x7_xy(8, 34, "About");
  lcd_need_refresh = false;         // reset refresh flas
  esc = 0;                          // refresh escape flag
}

//------------------------ CH1 waveform SCREEN ------------------
void lcd_CH1_wave_screen() {

#if DEBUG > 0
  Serial.print("lastpos = ");
  Serial.println(lastpos);
#endif
  int lastpos = pos;
  int delta = 0;
  delta = lastpos - pos;
  switch (delta) {
    case 0:
      RSCG12864B.print_string_5x7_xy(35, 10, "Sine");
      break;
    case 1:
      RSCG12864B.print_string_5x7_xy(35, 10, "Trig");
      break;
    case 2:
      RSCG12864B.print_string_5x7_xy(35, 10, "Squr");
      break;
    default:
      RSCG12864B.print_string_5x7_xy(35, 10, "dflt");
      break;
  }
  if (into == 1)
    L1_Ctr = 0;
  lcd_need_refresh = false;         // reset refresh flas
  esc = 0;                          // refresh escape flag
}

//------------------------ ABOUT SCREEN ------------------
void lcd_about_screen() {
  lcd_need_refresh = true;
  RSCG12864B.clear();
  RSCG12864B.print_string_5x7_xy(3, 8, "AD9833 Waveform");
  RSCG12864B.print_string_5x7_xy(3, 16, "Generator");
  RSCG12864B.print_string_5x7_xy(3, 24, "Author: HabonRoof");
  RSCG12864B.print_string_5x7_xy(3, 32, "https//:habonroof/");
  RSCG12864B.print_string_5x7_xy(3, 40, "2CHWaveformGenerator");
  into   = 0;
  esc    = 1;
  delay(5000);
}
