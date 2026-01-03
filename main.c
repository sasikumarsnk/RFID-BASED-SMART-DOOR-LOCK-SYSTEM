#include<lpc21xx.h>
#include<string.h>
#include"uart.h"
#include"lcd.h"
#define m 1<<21
#define buz 1<<22

unsigned char card[3][13];

void card_read(int i)
{
	unsigned char j;
	for(j=0;j<12;j++)
	{
		card[i][j]=UART_RX();
	}
	card[i][12]= 0;
}

void motor(void)
{
	IOSET0 = m;
	delay_ms(1000);
	IOCLR0 = m; 
}

void buzzer(void)
{
	IOCLR0 = buz;
	delay_ms(1000);
	IOSET0 = buz; 
}



int main() 
{
	unsigned char lock=0;
	int sec;
	IODIR0|= m|buz;
	IOSET0|=buz;

	UART_CONFIG();
	lcd_init();
	lcd_cmd(0x80);
	lcd_string("RFID BASED DOOR");
	lcd_cmd(0xc3);
	lcd_string("LOCK SYSTEM");
	delay_ms(2000);
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	lcd_string("READ MODE");
	card_read(0);
	card_read(1);
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	lcd_string("TAP RFID");
	while(1)
	{
		card_read(2);
		if(strcmp(card[0],card[2])==0)
		{
			UART_STR("OK");
			lcd_cmd(0x01);
			lcd_cmd(0x80);
			lcd_string("Welcome");
			motor();
			delay_ms(500);
			lcd_cmd(0x01);
			lcd_cmd(0x80);
			lcd_string("TAP RFID");
			lock=0;
		}
		else if(strcmp(card[1],card[2])==0)
		{
			UART_STR("OK");
			lcd_cmd(0x01);
			lcd_cmd(0x80);
			lcd_string("Welcome");
			motor();
			delay_ms(500);
			lcd_cmd(0x01);
			lcd_cmd(0x80);
			lcd_string("TAP RFID");
			lock = 0;
		
		}
		else
		{
			UART_STR("NO");
			lcd_cmd(0x01);
			lcd_cmd(0x80);
			lcd_string("Incorrect pass");
			buzzer();
			delay_ms(500);
			lcd_cmd(0x01);
			lcd_cmd(0x80);
			lcd_string("TAP RFID");
			lock++;
		}
		if(lock==3)
		{
			lcd_cmd(0x01);
			lcd_cmd(0x80);
			lcd_string("try again later");
			for(sec=9;sec>=0;sec--)
			{
				lcd_cmd(0xc0);
				lcd_data(sec+48);
				delay_ms(1000);
			}
			lock=0;
			lcd_cmd(0x01);
			lcd_cmd(0x80);
			lcd_string("TAP RFID");
		}
  }
}


