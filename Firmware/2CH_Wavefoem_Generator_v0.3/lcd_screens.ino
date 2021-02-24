/*LCD screen code for 2CH waveform generator

*/

//------------------------ Boot ------------------------

void lcdBootScreen() {
  RSCG12864B.clear();
  RSCG12864B.print_string_16_xy(24, 0, "AD9833 2CH");
  RSCG12864B.print_string_16_xy(32, 16, "Waveform");
  RSCG12864B.print_string_16_xy(24, 32, "Generator");
  RSCG12864B.print_string_16_xy(24, 48, "Ver. 1.0.0");
  delay(1000);
  RSCG12864B.draw_rectangle(0, 0, 127, 63);
}

//------------------------ About ------------------------

void lcdAboutScreen() {
  if (lcdNeedUpdate) {
    lcdNeedUpdate = false;
    RSCG12864B.clear();
    RSCG12864B.print_string_5x7_xy(3, 8, "AD9833 Waveform");
    RSCG12864B.print_string_5x7_xy(3, 16, "Generator");
    RSCG12864B.print_string_5x7_xy(3, 24, "Author: HabonRoof");
    RSCG12864B.print_string_5x7_xy(3, 32, "https//:habonroof/");
    RSCG12864B.print_string_5x7_xy(3, 40, "2CHWaveformGenerator");
  }
}
