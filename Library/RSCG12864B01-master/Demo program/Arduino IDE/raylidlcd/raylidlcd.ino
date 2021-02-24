#include <RSCG12864B.h>

void setup() {
  // put your setup code here, to run once:
  RSCG12864B.begin();
  RSCG12864B.brightness(255);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned char i;
  char chn[]={0XC9,0XEE,0XDB,0XDA,0XCA,0XD0,0XC8,0XF0,0XC1,0XA2,0XB5,0XC2,0XB5,0XE7,0XD7,0XD3,0x00,};
  char f1[]={0X49,0X32,0X43,0XBD,0XD3,0XBF,0XDA,0X2C,0XC4,0XDA,0XBD,0XA8,0XD7,0XD6,0XBF,0XE2,0,};
  char f2[]={0XD6,0XD0,0XCE,0XC4,0X2C,0XBA,0XAB,0XCE,0XC4,0X2C,0XC8,0XD5,0XCE,0XC4,0,};
  char f3[]={0XD6,0XA7,0XB3,0XD6,0X32,0X44,0XBB,0XE6,0XCD,0XBC,0};
  RSCG12864B.display_bmp(0);
  delay(800);
  RSCG12864B.display_bmp(1);
  delay(800);
  RSCG12864B.display_bmp(2);
  delay(800);
  RSCG12864B.display_bmp(3);
  delay(800);
  RSCG12864B.display_bmp(4);
  delay(800);
  RSCG12864B.display_bmp(5);
  delay(800);
  RSCG12864B.clear();
  RSCG12864B.print_string_16_xy(0,15,chn);
  RSCG12864B.print_string_16_xy(8,35,"www.raylid.com");
  delay(3000);
  RSCG12864B.clear();
  RSCG12864B.print_string_12_xy(16,15,chn);
  RSCG12864B.print_string_12_xy(20,35,"www.raylid.com");
  delay(3000);
  RSCG12864B.clear();
  RSCG12864B.font_revers_on();
  RSCG12864B.print_string_12_xy(25,0,"Built-in font");
  RSCG12864B.font_revers_off();
  RSCG12864B.print_string_5x7_xy(3,15,"5*7 ASCII 0123456789");
  RSCG12864B.print_string_5x7_xy(3,25,"5*7 ASCII ABCDEabcde");
  RSCG12864B.print_string_12_xy(20,35,"6*12/12*12 FONT");
  RSCG12864B.print_string_16_xy(5,48,"8*16/16*16 FONT");
  delay(3000);
  RSCG12864B.clear();
  RSCG12864B.print_string_16_xy(0,0,f1);
  RSCG12864B.print_string_16_xy(0,16,f2);
  RSCG12864B.print_string_16_xy(0,32,f3);
  RSCG12864B.draw_rectangle(0,50,127,63);
  for(i=2;i<=125;i++)
  {
    RSCG12864B.draw_fill_rectangle(2,52,i,61);
    delay(100);
  }
  delay(3000);
}
