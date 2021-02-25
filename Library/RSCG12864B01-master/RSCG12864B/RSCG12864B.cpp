extern "C" {
	#include <stdlib.h>
	#include <string.h>
	#include <inttypes.h>
	#include "utility/I2C.h"
}

#include "RSCG12864B.h"

RAYLIDLCD::RAYLIDLCD()
{
	
}

void RAYLIDLCD::RAYLIDLCD::begin()
{
	I2C_init();
}

/***********************************************************************
*函数原型:clear()
*清屏
***********************************************************************/
void RAYLIDLCD::clear()
{
	I2C_start();
	I2C_to_write();
	I2C_send(0x10);
	I2C_stop();
}

/***********************************************************************
*函数原型:display_on()
*打开显示，开机默认状态
***********************************************************************/
void RAYLIDLCD::display_on()
{
	I2C_start();
	I2C_to_write();
	I2C_send(0x11);
	I2C_stop();
}

/***********************************************************************
*函数原型:display_off()
*关闭显示
***********************************************************************/
void RAYLIDLCD::display_off()
{
	I2C_start();
	I2C_to_write();
	I2C_send(0x12);
	I2C_stop();
}

/***********************************************************************
*函数原型:brightness(U8 n)
*亮度设置
***********************************************************************/
void RAYLIDLCD::brightness(U8 n)
{
	I2C_start();
	I2C_to_write();
	I2C_send(0x13);
	I2C_send(n);
	I2C_stop();
}

/***********************************************************************
*函数原型:draw_pixel(U8 x,U8 y)
*绘制一个点
***********************************************************************/
void RAYLIDLCD::draw_pixel(U8 x,U8 y)
{
	I2C_start();
	I2C_to_write();
	I2C_send(0x30);
	I2C_send(x);
	I2C_send(y);
	I2C_stop();
}

/***********************************************************************
*函数原型:delete_pixel(U8 x,U8 y)
*删除点
***********************************************************************/
void RAYLIDLCD::delete_pixel(U8 x,U8 y)
{
	I2C_start();
	I2C_to_write();
	I2C_send(0x31);
	I2C_send(x);
	I2C_send(y);
	I2C_stop();
}

/***********************************************************************
*函数原型:draw_line(U8 x1,U8 y1,U8 x2,U8 y2)
*绘制直线
***********************************************************************/
void RAYLIDLCD::draw_line(U8 x1,U8 y1,U8 x2,U8 y2)
{
	I2C_start();
	I2C_to_write();
	I2C_send(0x32);
	I2C_send(x1);
	I2C_send(y1);
	I2C_send(x2);
	I2C_send(y2);
	I2C_stop();
}

/***********************************************************************
*函数原型:delete_line(U8 x1,U8 y1,U8 x2,U8 y2)
*删除一条直线
***********************************************************************/
void RAYLIDLCD::delete_line(U8 x1,U8 y1,U8 x2,U8 y2)
{
	I2C_start();
	I2C_to_write();
	I2C_send(0x33);
	I2C_send(x1);
	I2C_send(y1);
	I2C_send(x2);
	I2C_send(y2);
	I2C_stop();
}

/***********************************************************************
*函数原型:draw_rectangle(U8 x1,U8 y1,U8 x2,U8 y2)
*绘制矩形
***********************************************************************/
void RAYLIDLCD::draw_rectangle(U8 x1,U8 y1,U8 x2,U8 y2)
{
	I2C_start();
	I2C_to_write();
	I2C_send(0x34);
	I2C_send(x1);
	I2C_send(y1);
	I2C_send(x2);
	I2C_send(y2);
	I2C_stop();
}

/***********************************************************************
*函数原型:delete_rectangle(U8 x1,U8 y1,U8 x2,U8 y2)
*删除矩形
***********************************************************************/
void RAYLIDLCD::delete_rectangle(U8 x1,U8 y1,U8 x2,U8 y2)
{
	I2C_start();
	I2C_to_write();
	I2C_send(0x35);
	I2C_send(x1);
	I2C_send(y1);
	I2C_send(x2);
	I2C_send(y2);
	I2C_stop();
}

/***********************************************************************
*函数原型:draw_fill_rectangle(U8 x1,U8 y1,U8 x2,U8 y2)
*绘制填充矩形
***********************************************************************/
void RAYLIDLCD::draw_fill_rectangle(U8 x1,U8 y1,U8 x2,U8 y2)
{
	I2C_start();
	I2C_to_write();
	I2C_send(0x36);
	I2C_send(x1);
	I2C_send(y1);
	I2C_send(x2);
	I2C_send(y2);
	I2C_stop();
}

/***********************************************************************
*函数原型:delete_fill_rectangle(U8 x1,U8 y1,U8 x2,U8 y2)
*删除填充矩形
***********************************************************************/
void RAYLIDLCD::delete_fill_rectangle(U8 x1,U8 y1,U8 x2,U8 y2)
{
	I2C_start();
	I2C_to_write();
	I2C_send(0x37);
	I2C_send(x1);
	I2C_send(y1);
	I2C_send(x2);
	I2C_send(y2);
	I2C_stop();
}

/***********************************************************************
*函数原型:draw_circle(U8 x,U8 y,U8 r)
*在制定位置绘制一个圆?
***********************************************************************/
void RAYLIDLCD::draw_circle(U8 x,U8 y,U8 r)
{
	I2C_start();
	I2C_to_write();
	I2C_send(0x38);
	I2C_send(x);
	I2C_send(y);
	I2C_send(r);
	I2C_stop();
}

/***********************************************************************
*函数原型:delete_circle(U8 x,U8 y,U8 r)
*删除圆
***********************************************************************/
void RAYLIDLCD::delete_circle(U8 x,U8 y,U8 r)
{
	I2C_start();
	I2C_to_write();
	I2C_send(0x39);
	I2C_send(x);
	I2C_send(y);
	I2C_send(r);
	I2C_stop();
}

/***********************************************************************
*函数原型:draw_fill_rectangle(U8 x1,U8 y1,U8 x2,U8 y2)
*在制定位置绘制一个填充圆?
***********************************************************************/
void RAYLIDLCD::draw_fill_circle(U8 x,U8 y,U8 r)
{
	I2C_start();
	I2C_to_write();
	I2C_send(0x3A);
	I2C_send(x);
	I2C_send(y);
	I2C_send(r);
	I2C_stop();
}

/***********************************************************************
*函数原型:delete_fill_circle(U8 x,U8 y,U8 r)
*在制定位置删除一个填充圆
***********************************************************************/
void RAYLIDLCD::delete_fill_circle(U8 x,U8 y,U8 r)
{
	I2C_start();
	I2C_to_write();
	I2C_send(0x3B);
	I2C_send(x);
	I2C_send(y);
	I2C_send(r);
	I2C_stop();
}

/***********************************************************************
*函数原型:inversely_area(U8 x1,U8 y1,U8 x2,U8 y2)
*指定区域反白显示
***********************************************************************/
void RAYLIDLCD::inversely_area(U8 x1,U8 y1,U8 x2,U8 y2)
{
	I2C_start();
	I2C_to_write();
	I2C_send(0x38);
	I2C_send(x1);
	I2C_send(y1);
	I2C_send(x2);
	I2C_send(y2);
	I2C_stop();
}

/***********************************************************************
*函数原型:display_bmp(U16 n)
*整张显示预存图片
***********************************************************************/
void RAYLIDLCD::display_bmp(U16 n)
{
	I2C_start();
	I2C_to_write();
	I2C_send(0x3D);
	I2C_send(n>>8);
	I2C_send(n);
	I2C_stop();
}

/***********************************************************************
*函数原型:display_bmp_block(U16 n,U8 px,U8 py,U8 xU8 y,U8 w,U8 h)
*块显示预存图片
***********************************************************************/
void RAYLIDLCD::display_bmp_block(U16 n,U8 px,U8 py,U8 x,U8 y,U8 w,U8 h)
{
	I2C_start();
	I2C_to_write();
	I2C_send(0x3E);
	I2C_send(n>>8);
	I2C_send(n);
	I2C_send(x);
	I2C_send(y);
	I2C_send(px);
	I2C_send(py);
	I2C_send(w);
	I2C_send(h);
	I2C_stop();
}
/***********************************************************************
*函数原型:cursor(U8 x,U8 y)
*设置字符显示位置
参数：x:0~127  y:0~63
***********************************************************************/
void RAYLIDLCD::cursor(U8 x,U8 y)
{
	I2C_start();
	I2C_to_write();
	I2C_send(0x20);
	I2C_send(x);
	I2C_send(y);
	I2C_stop();
}

/***********************************************************************
*函数原型:spacing(U8 xs,U8 ys)
*设置字符间距
参数：xs:0~127  ys:0~63
***********************************************************************/
void RAYLIDLCD::spacing(U8 xs,U8 ys)
{
	I2C_start();
	I2C_to_write();
	I2C_send(0x21);
	I2C_send(xs);
	I2C_send(ys);
	I2C_stop();
}

/***********************************************************************
*函数原型:font_revers_on()
*字符反显模式开启
***********************************************************************/
void  RAYLIDLCD::font_revers_on()
{
	I2C_start();
	I2C_to_write();
	I2C_send(0x23);
	I2C_stop();
}
/***********************************************************************
*函数原型:font_revers_ff()
*字符反显模式关闭
***********************************************************************/
void  RAYLIDLCD::font_revers_off()
{
	I2C_start();
	I2C_to_write();
	I2C_send(0x22);
	I2C_stop();
}
/***********************************************************************
*函数原型:print_U32_5x7(U32 n)
*在当前位置显示长整型变量n
***********************************************************************/
void RAYLIDLCD::print_U32_5x7(U32 n)
{
	U32 i,temp;
	U8 t=0;
	I2C_start();
	I2C_to_write();
	I2C_send(0x24);
	if(n==0)
	{
		I2C_send(0x30);
	}
	else
	{
		for(i=1000000000;i>=1;i=i/10)
		{
			temp=n/i;
			if(t==0&&temp)
			{
				I2C_send(temp%10+0x30);
				t=1;
			}
			else if(t==1)
			{
				I2C_send(temp%10+0x30);
			}
		}
	}
	I2C_send(0x00);
	I2C_stop();
}

/***********************************************************************
*函数原型:print_U32_6x12(U32 n)
*在当前位置显示长整型变量n
***********************************************************************/

void RAYLIDLCD::print_U32_6x12(U32 n)
{
	U32 i,temp;
	U8 t=0;
	I2C_start();
	I2C_to_write();
	I2C_send(0x25);
	if(n==0)
	{
		I2C_send(0x30);
	}
	else
	{
		for(i=1000000000;i>=1;i=i/10)
		{
			temp=n/i;
			if(t==0&&temp)
			{
				I2C_send(temp%10+0x30);
				t=1;
			}
			else if(t==1)
			{
				I2C_send(temp%10+0x30);
			}
		}
	}
	I2C_send(0x00);
	I2C_stop();
}

/***********************************************************************
*函数原型:print_U32_8x16(U32 n)
*在当前位置显示长整型变量n
***********************************************************************/
void RAYLIDLCD::print_U32_8x16(U32 n)
{
	U32 i,temp;
	U8 t=0;
	I2C_start();
	I2C_to_write();
	I2C_send(0x26);
	if(n==0)
	{
		I2C_send(0x30);
	}
	else
	{
		for(i=1000000000;i>=1;i=i/10)
		{
			temp=n/i;
			if(t==0&&temp)
			{
				I2C_send(temp%10+0x30);
				t=1;
			}
			else if(t==1)
			{
				I2C_send(temp%10+0x30);
			}
		}
	}
	I2C_send(0x00);
	I2C_stop();
}

/***********************************************************************
*函数原型:print_U32_5x7_xy(U8 x,U8 y,U32 n)
*在指定位置显示长整型变量n
***********************************************************************/
void RAYLIDLCD::print_U32_5x7_xy(U8 x,U8 y,U32 n)
{
	U32 i,temp;
	U8 t=0;
	I2C_start();
	I2C_to_write();
	I2C_send(0x20);
	I2C_send(x);
	I2C_send(y);
	I2C_send(0x24);
	if(n==0)
	{
		I2C_send(0x30);
	}
	else
	{
		for(i=1000000000;i>=1;i=i/10)
		{
			temp=n/i;
			if(t==0&&temp)
			{
				I2C_send(temp%10+0x30);
				t=1;
			}
			else if(t==1)
			{
				I2C_send(temp%10+0x30);
			}
		}
	}
	I2C_send(0x00);
	I2C_stop();
}

/***********************************************************************
*函数原型:print_U32_6x12_xy(U8 x,U8 y,U32 n)
*在指定位置显示长整型变量n
***********************************************************************/
void RAYLIDLCD::print_U32_6x12_xy(U8 x,U8 y,U32 n)
{
	U32 i,temp;
	U8 t=0;
	I2C_start();
	I2C_to_write();
	I2C_send(0x20);
	I2C_send(x);
	I2C_send(y);
	I2C_send(0x25);
	if(n==0)
	{
		I2C_send(0x30);
	}
	else
	{
		for(i=1000000000;i>=1;i=i/10)
		{
			temp=n/i;
			if(t==0&&temp)
			{
				I2C_send(temp%10+0x30);
				t=1;
			}
			else if(t==1)
			{
				I2C_send(temp%10+0x30);
			}
		}
	}
	I2C_send(0x00);
	I2C_stop();
}

/***********************************************************************
*函数原型:print_U32_8x16_xy(U8 x,U8 y,U32 n)
*在指定位置显示长整型变量n
***********************************************************************/
void RAYLIDLCD::print_U32_8x16_xy(U8 x,U8 y,U32 n)
{
	U32 i,temp;
	U8 t=0;
	I2C_start();
	I2C_to_write();
	I2C_send(0x20);
	I2C_send(x);
	I2C_send(y);
	I2C_send(0x26);
	if(n==0)
	{
		I2C_send(0x30);
	}
	else
	{
		for(i=1000000000;i>=1;i=i/10)
		{
			temp=n/i;
			if(t==0&&temp)
			{
				I2C_send(temp%10+0x30);
				t=1;
			}
			else if(t==1)
			{
				I2C_send(temp%10+0x30);
			}
		}
	}
	I2C_send(0x00);
	I2C_stop();
}

/***********************************************************************
*函数原型:print_string_12(CCHAR *ptr)
*在当前位置显示字符串*ptr,支持全角和半角混合显示
***********************************************************************/
void RAYLIDLCD::print_string_12(CCHAR *ptr)
{
	I2C_start();
	I2C_to_write();
	I2C_send(0x27);
	while(*ptr!='\0')
	{
		I2C_send(*ptr++);
	}
	I2C_send(0x00);
	I2C_stop();
}
/***********************************************************************
*函数原型:print_string_16(CCHAR *ptr)
*在当前位置显示字符串*ptr,支持全角和半角混合显示
***********************************************************************/
void RAYLIDLCD::print_string_16(CCHAR *ptr)
{
	I2C_start();
	I2C_to_write();
	I2C_send(0x28);
	while(*ptr!='\0')
	{
		I2C_send(*ptr++);
	}
	I2C_send(0x00);
	I2C_stop();
}

/***********************************************************************
*函数原型:print_string_12_xy(U8 x,U8 y,CCHAR *ptr)
*在指定位置显示字符串*ptr,支持全角和半角混合显示
***********************************************************************/
void RAYLIDLCD::print_string_12_xy(U8 x,U8 y,CCHAR *ptr)
{
	I2C_start();
	I2C_to_write();
	I2C_send(0x20);
	I2C_send(x);
	I2C_send(y);
	I2C_send(0x27);
	while(*ptr!='\0')
	{
		I2C_send(*ptr++);
	}
	I2C_send(0x00);
	I2C_stop();
}
/***********************************************************************
*函数原型:print_string_16_xy(U8 x,U8 y,CCHAR *ptr)
*在指定位置显示字符串*ptr,支持全角和半角混合显示
***********************************************************************/
void RAYLIDLCD::print_string_16_xy(U8 x,U8 y,CCHAR *ptr)
{
	I2C_start();
	I2C_to_write();
	I2C_send(0x20);
	I2C_send(x);
	I2C_send(y);
	I2C_send(0x28);
	while(*ptr!='\0')
	{
		I2C_send(*ptr++);
	}
	I2C_send(0x00);
	I2C_stop();
}

/***********************************************************************
*函数原型:print_string_5x7(CCHAR *ptr)
*在当前位置显示字符串*ptr,支持5*7ASCII
***********************************************************************/
void RAYLIDLCD::print_string_5x7(CCHAR *ptr)
{
	I2C_start();
	I2C_to_write();
	I2C_send(0x24);
	while(*ptr!='\0')
	{
		I2C_send(*ptr++);
	}
	I2C_send(0x00);
	I2C_stop();
}

/***********************************************************************
*函数原型:print_string_6x12(CCHAR *ptr)
*在当前位置显示字符串*ptr,支持6*12ASCII
***********************************************************************/
void RAYLIDLCD::print_string_6x12(CCHAR *ptr)
{
	I2C_start();
	I2C_to_write();
	I2C_send(0x25);
	while(*ptr!='\0')
	{
		I2C_send(*ptr++);
	}
	I2C_send(0x00);
	I2C_stop();
}

/***********************************************************************
*函数原型:print_string_8x16(CCHAR *ptr)
*在当前位置显示字符串*ptr,支持8*16ASCII
***********************************************************************/
void RAYLIDLCD::print_string_8x16(CCHAR *ptr)
{
	I2C_start();
	I2C_to_write();
	I2C_send(0x26);
	while(*ptr!='\0')
	{
		I2C_send(*ptr++);
	}
	I2C_send(0x00);
	I2C_stop();
}

/***********************************************************************
*函数原型:print_string_5x7_xy(U8 x,U8 y,CCHAR *ptr)
*在指定位置显示字符串*ptr,支持5*7ASCII
***********************************************************************/
void RAYLIDLCD::print_string_5x7_xy(U8 x,U8 y,CCHAR *ptr)
{
	I2C_start();
	I2C_to_write();
	I2C_send(0x20);
	I2C_send(x);
	I2C_send(y);
	I2C_send(0x24);
	while(*ptr!='\0')
	{
		I2C_send(*ptr++);
	}
	I2C_send(0x00);
	I2C_stop();
}

/***********************************************************************
*函数原型:print_string_6x12_xy(U8 x,U8 y,CCHAR *ptr)
*在指定位置显示字符串*ptr,支持6*12ASCII
***********************************************************************/
void RAYLIDLCD::print_string_6x12_xy(U8 x,U8 y,CCHAR *ptr)
{
	I2C_start();
	I2C_to_write();
	I2C_send(0x20);
	I2C_send(x);
	I2C_send(y);
	I2C_send(0x25);
	while(*ptr!='\0')
	{
		I2C_send(*ptr++);
	}
	I2C_send(0x00);
	I2C_stop();
}

/***********************************************************************
*函数原型:print_string_8x16_xy(U8 x,U8 y,CCHAR *ptr)
*在指定位置显示字符串*ptr,支持8*16ASCII
***********************************************************************/
void RAYLIDLCD::print_string_8x16_xy(U8 x,U8 y,CCHAR *ptr)
{
	I2C_start();
	I2C_to_write();
	I2C_send(0x20);
	I2C_send(x);
	I2C_send(y);
	I2C_send(0x26);
	while(*ptr!='\0')
	{
		I2C_send(*ptr++);
	}
	I2C_send(0x00);
	I2C_stop();
}


RAYLIDLCD RSCG12864B=RAYLIDLCD();