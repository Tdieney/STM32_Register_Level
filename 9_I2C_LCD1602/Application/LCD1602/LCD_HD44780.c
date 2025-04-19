#include "LCD_HD44780.h"
//extern I2C_HandleTypeDef hi2c1;

#define HAL_Delay(ms)     rcc_msDelay(ms)

const unsigned char LCD_SO_X[11][6] ={
			0,1,2,5,3,4,                   // SO 0
			1,2,32,3,255,3,                // SO 1
			6,6,2,5,3,3,                   // SO 2
			6,6,2,3,3,4,                   // SO 3
			5,3,255,32,32,255,             // SO 4
			255,6,6,3,3,4,                 // SO 5
			0,6,6,5,3,4,                   // SO 6
			1,1,255,32,32,255,             // SO 7
			0,6,2,5,3,4,                   // SO 8
			0,6,2,3,3,4,                   // SO 9
			32,32,32,32,32,32
			};   
const unsigned char LCD_SO_X1[11][12] ={
			0,1,2,255,32,255,255,32,255,5,3,4,       //0   
			1,2,32,32,255,32,32,255,32,3,255,3,      //1  
			1,1,2,3,3,255,255,32,32,5,3,3,           //2           
			0,1,2,32,3,4,32,32,2,5,3,4,              //3
			255,32,255,5,3,255,32,32,255,32,32,255,  //4             
			255,1,1,255,3,7,32,32,255,5,3,4,         //5           
			0,1,2,255,3,7,255,32,255,5,3,4,          //6             
			1,1,255,32,32,4,32,0,32,32,255,32,       //7             
			0,1,2,5,3,4,0,32,2,5,3,4,                //8     
			0,1,2,5,3,255,32,32,255,5,3,4,           //9 
			32,32,32,32,32,32,32,32,32,32,32,32,
			};
const unsigned char LCD_MA_8DOAN[] = {
		 0x07,0x0F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,  
		 0x1F,0x1F,0x1F,0X00,0X00,0X00,0X00,0X00,  
		 0x1C,0x1E,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F, 
		 0X00,0X00,0X00,0X00,0X00,0x1F,0x1F,0x1F,  
		 0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1E,0x1C,  
		 0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x0F,0x07, 
		 0x1F,0x1F,0x1F,0X00,0X00,0X00,0x1F,0x1F,  
		 0x00,0x00,0x00,0x00,0x00,0x1c,0x1e,0x1F}; 
void lcd_command (char cmd)
{
			char data_u, data_l;
			uint8_t data_t[4];
			data_u = (cmd&0xf0);
			data_l = ((cmd<<4)&0xf0);
			data_t[0] = data_u|0x0c;  
			data_t[1] = data_u|0x08;  
			data_t[2] = data_l|0x0c;  
			data_t[3] = data_l|0x08;  
			//HAL_I2C_Master_Transmit (&hi2c1, 0x4e,(uint8_t *) data_t, 4, 100);
			i2c_I2C1_masterTransmit(0x4E, (uint8_t *) data_t, 4, 100);
}

void lcd_data (char data)
{
		char data_u, data_l;
		uint8_t data_t[4];
		data_u = (data&0xf0);
		data_l = ((data<<4)&0xf0);
		data_t[0] = data_u|0x0D;  
		data_t[1] = data_u|0x09;  
		data_t[2] = data_l|0x0D;  
		data_t[3] = data_l|0x09;  
		//HAL_I2C_Master_Transmit (&hi2c1, 0x4e,(uint8_t *) data_t, 4, 100);
		i2c_I2C1_masterTransmit(0x4E, (uint8_t *) data_t, 4, 100);
}

void lcd_init (void)
{
	  HAL_Delay(10);
		lcd_command (0x33); 
		lcd_command (0x32);
		HAL_Delay(5);
		lcd_command (0x2c); 
		HAL_Delay(5);
		lcd_command (0x0c); 
		lcd_command(0x40);
		for (char n=0;n<64;n++) { lcd_data(LCD_MA_8DOAN[n]); }
		lcd_command (0x01); 
		HAL_Delay(2);
}

void lcd_string (char *str)
{
	  while (*str) lcd_data(*str++);
}

void lcd_goto_xy (int row, int col)
{
	  const char add[]={0x80,0xc0,0x94,0xd4};
	  lcd_command(add[row]+col);
}
  
void lcd_16x2_2line_num(unsigned char so, unsigned char x) 
{   
	  char  i;
		lcd_goto_xy(0,x);
		for (i=0;i<6;i++)     
		{                  
			if (i==3)   lcd_goto_xy(1,x);             
			lcd_data(LCD_SO_X[so][i]);     
		 } 
}

void lcd_20x4_2line_num(unsigned char so, unsigned char x,unsigned char y) 
{   
	  char  i;
		lcd_goto_xy(x,y);
		for (i=0;i<6;i++)     
		{                  
			if (i==3)   lcd_goto_xy(x+1,y);             
			lcd_data(LCD_SO_X[so][i]);     
		 } 
}

void lcd_20x4_4line_num(unsigned char  so, unsigned char x)
{
      char  n;
      for(n=0;n<12;n++)
      {
            if(n%3==0)lcd_goto_xy(n/3,x); 
            lcd_data(LCD_SO_X1[so][n]);
      }
}
void lcd_clear()
{
  lcd_command (0x01);
  HAL_Delay(2);
}
