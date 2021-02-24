/*
  RSCG12864B.h - 12864LCD library for Arduino & Wiring
  Copyright (c) 2015 Raylid Electronics Co.,Ltd (www.raylid.com).  All right reserved.
*/


/*--------Arduino Uno connection to LCD-----------------------------------------------

          LCD Module                  Arduino Uno
		  
		     GND-------------------------GND
			 VDD-------------------------5.0V
			 RST(Floating)
			 SCL-------------------------A5(PC5)
			 SDA-------------------------A4(PC4)
			 BUSY------------------------A3(PC3)
			 A1(Floating)
			 A0(Floating)
			 
-------------------------------------------------------------------------------------*/

#ifndef RSCG12864B_h
#define RSCG12864B_h


typedef unsigned char U8;
typedef unsigned int U16;
typedef unsigned long U32;
typedef const char  CCHAR;

class RAYLIDLCD 
{
	private:
	
	public:
	RAYLIDLCD();
	void begin();
	void clear();
	void display_on();
	void display_off();
	void brightness(U8 n);
	void draw_pixel(U8 x,U8 y);
	void delete_pixel(U8 x,U8 y);
	void draw_line(U8 x1,U8 y1,U8 x2,U8 y2);
	void delete_line(U8 x1,U8 y1,U8 x2,U8 y2);
	void draw_rectangle(U8 x1,U8 y1,U8 x2,U8 y2);
	void delete_rectangle(U8 x1,U8 y1,U8 x2,U8 y2);
	void draw_fill_rectangle(U8 x1,U8 y1,U8 x2,U8 y2);
	void delete_fill_rectangle(U8 x1,U8 y1,U8 x2,U8 y2);
	void draw_circle(U8 x,U8 y,U8 r);
	void delete_circle(U8 x,U8 y,U8 r);
	void draw_fill_circle(U8 x,U8 y,U8 r);
	void delete_fill_circle(U8 x,U8 y,U8 r);
	void inversely_area(U8 x1,U8 y1,U8 x2,U8 y2);
	void display_bmp(U16 n);
	void display_bmp_block(U16 n,U8 px,U8 py,U8 x,U8 y,U8 w,U8 h);
	void cursor(U8 x,U8 y);
    void spacing(U8 xs,U8 ys);
	void font_revers_on();
	void font_revers_off();
    void print_U32_5x7(U32 n);
	void print_U32_6x12(U32 n);
	void print_U32_8x16(U32 n);
	void print_U32_5x7_xy(U8 x,U8 y,U32 n);
	void print_U32_6x12_xy(U8 x,U8 y,U32 n);
	void print_U32_8x16_xy(U8 x,U8 y,U32 n);
	void print_string_12(CCHAR *ptr);
	void print_string_16(CCHAR *ptr);
	void print_string_12_xy(U8 x,U8 y,CCHAR *ptr);
	void print_string_16_xy(U8 x,U8 y,CCHAR *ptr);
	void print_string_5x7(CCHAR *ptr);
	void print_string_6x12(CCHAR *ptr);
	void print_string_8x16(CCHAR *ptr);
	void print_string_5x7_xy(U8 x,U8 y,CCHAR *ptr);
	void print_string_6x12_xy(U8 x,U8 y,CCHAR *ptr);
	void print_string_8x16_xy(U8 x,U8 y,CCHAR *ptr);	
};

extern RAYLIDLCD RSCG12864B;

#endif
