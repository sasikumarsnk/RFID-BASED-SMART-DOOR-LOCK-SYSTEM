
#include<LPC21XX.H>

int delay_s(int);
int delay_ms(int);
int delay_us(int);

int delay_s(int s)
{
 T0PR = 15000000-1;
 T0TCR = 0x01;
 while(T0TC<s);
 T0TCR = 0x03;
 T0TCR = 0x00;
 return 0;
}

int delay_ms(int ms)
{
 T0PR = 15000-1;
 T0TCR = 0x01;
 while(T0TC<ms);
 T0TCR = 0x03;
 T0TCR = 0x00;
 return 0;
}

int delay_us(int us)
{
 T0PR = 15-1;
 T0TCR = 0x01;
 while(T0TC<us);
 T0TCR = 0x03;
 T0TCR = 0x00;
 return 0;
}
