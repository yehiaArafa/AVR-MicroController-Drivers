#include "Types.h"
#include "Util.h"

#include "DIO_Interface.h"

#include "LCD_Interface.h"
#include "LCD_config.h"

#define F_CPU 1000000UL
#include <util/delay.h>



void LCD_INIT(void){
		
	//delay 15 ms//
	_delay_ms(15);
	LCD_writeCommand(0x38); // 2 lines screen
	LCD_cursorON();
	LCD_clearScreen();
}


void LCD_clearScreen(void){
	LCD_writeCommand(0x01);
}

void LCD_displayOff(void){
	LCD_writeCommand(0x08);
}

void LCD_cursorON(){
	LCD_writeCommand(0x0E);
}

void LCD_cursorBlinking(){
	LCD_writeCommand(0x0F);
}

void LCD_cursorAtFirstLine(void){
	LCD_writeCommand(0x80);
}

u8 LCD_cursorAtSecondLine(void){
	#if LCD_rowbiteNumber==2
		LCD_writeCommand(0xc0);
		return OK;
	#elif LCD_rowbiteNumber==1
		return ERROR;
	#endif	
}


void LCD_writeCommand(u8 command){
	
	DIO_writePin(LCD_D0,GET_BIT(command,0));
	DIO_writePin(LCD_D1,GET_BIT(command,1));
	DIO_writePin(LCD_D2,GET_BIT(command,2));
	DIO_writePin(LCD_D3,GET_BIT(command,3));
	DIO_writePin(LCD_D4,GET_BIT(command,4));
	DIO_writePin(LCD_D5,GET_BIT(command,5));
	DIO_writePin(LCD_D6,GET_BIT(command,6));
	DIO_writePin(LCD_D7,GET_BIT(command,7));
	
	DIO_writePin(LCD_RS,LCD_COMMAND); //RS -> LOW
	DIO_writePin(LCD_RW,LCD_WRITE); // RW -> LOW
	
	DIO_writePin(LCD_E,LCD_ENABLE); // E --> HIGH
	_delay_us(1);
	DIO_writePin(LCD_E,LCD_DISABLE); //E --> LOW
	
	if(command==0x01 || command == 0x02)
		//delay 2 ms
		_delay_ms(2);
	else
		//delay 100 us
		_delay_us(100);
}


void LCD_writeChar(u8 data){
	
	
	DIO_writePin(LCD_D0,GET_BIT(data,0));
	DIO_writePin(LCD_D1,GET_BIT(data,1));
	DIO_writePin(LCD_D2,GET_BIT(data,2));
	DIO_writePin(LCD_D3,GET_BIT(data,3));
	DIO_writePin(LCD_D4,GET_BIT(data,4));
	DIO_writePin(LCD_D5,GET_BIT(data,5));
	DIO_writePin(LCD_D6,GET_BIT(data,6));
	DIO_writePin(LCD_D7,GET_BIT(data,7));
	
	DIO_writePin(LCD_RS,LCD_DATA); //RS --> HIGH
	DIO_writePin(LCD_RW,LCD_WRITE); //RW --> HIGH 
	
	DIO_writePin(LCD_E,LCD_ENABLE);//E --> HIGH
	_delay_us(1);
	DIO_writePin(LCD_E,LCD_DISABLE);//E --> LOW
	
	//delay 100 us
	_delay_ms(200);
}




void LCD_writeString(u8 ptrToString[100]){

	u8 counter;
	for(counter=0;ptrToString[counter]!='\0';counter++){
		LCD_writeChar(ptrToString[counter]);
		
	}	
}

