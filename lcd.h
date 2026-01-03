 #include "delay.h"
 #define lcd_dp 0xf<<4
 #define lcd_rs 1<<8
 #define lcd_en 1<<9

 void lcd_init(void);
 void lcd_cmd(unsigned char);
 void lcd_data(unsigned char);
 void lcd_string(char *);
 void lcd_int(int);
 void lcd_float(float,int);

 void lcd_init(void)
 {
  IODIR0 |= lcd_dp | lcd_rs | lcd_en;
  //delay_ms(20);
  lcd_cmd(0x03); 
  lcd_cmd(0x02); 
  lcd_cmd(0x28); 
  lcd_cmd(0x0C); 
  lcd_cmd(0x01); 
  lcd_cmd(0x06); 
 }

 void lcd_cmd(unsigned char cmd)
 {
  IOCLR0 = lcd_dp | lcd_rs;
  IOSET0 = (cmd >> 4 & 0x0f)<< 4;
  IOSET0 = lcd_en;
   delay_ms(2);
  IOCLR0 = lcd_en;

  IOCLR0 = lcd_dp | lcd_rs;
  IOSET0 = (cmd & 0x0f)<< 4;
  IOSET0 = lcd_en;
   delay_ms(2);
  IOCLR0 = lcd_en;
 }
 void lcd_data(unsigned char data)
 {
  IOCLR0 = lcd_dp;
  IOSET0 = lcd_rs;
  IOSET0 = (data >> 4 & 0x0f) << 4;
  IOSET0 = lcd_en; 
  delay_ms(2);
  IOCLR0 = lcd_en;
  IOCLR0 = lcd_dp;
  IOSET0 = lcd_rs;
  IOSET0 = (data & 0x0f) << 4;
  IOSET0 = lcd_en;
   delay_ms(2);
  IOCLR0 = lcd_en;
 }

 void lcd_string(char *s)
 {
  while(*s)
  {
   lcd_data(*s++);
  }
 }

 void lcd_int(int n)
 {
  unsigned char a[10];
  signed char i=0;
  if(n==0) lcd_data('0');
  else if(n<0) lcd_data('-'),n=-n;
  while(n>0)
  {
   a[i++] = n%10;
   n=n/10;
  }
  for(--i;i>=0;i--) lcd_data(a[i]+48);
 }

 void lcd_float(float f, int n)
 {
  int x = f;
  lcd_int(x);
  lcd_data('.');
  f = (f-x) * n;
  lcd_int(f);
 }
