#include <REGX52.H>
/*
 0111 1111 0x7F
 1011 1111 0xBF
 1101 1111 0xDF
 1110 1111 0xEF 
#######################################
0 - 0x7B, 1 - 0xE7, 2 - 0xEB, 3 - 0xED
4 - 0xD7, 5 - 0xDB, 6 - 0xDD, 7 - 0xB7
8 - 0xBB, 9 - 0xBD, * - 0x77, # - 0x7D
#######################################
*/
unsigned char code Tab[]={0x7F,0xBF,0xDF,0xEF};

bit flag,flag2;
unsigned char data i;
unsigned char bdata Key;
sbit K1 = Key^1;
sbit K2 = Key^2;
sbit K3 = Key^3;

void Init(void)
{
 i=0;
 flag=0;
 P3_4   = 1;  // ustawienie na nadawanie
 SCON   = 0x50;
 RCAP2L = TL2 = 0xDC;
 RCAP2H = TH2 = 0xFF;
 T2CON  = 0x30;
 ES     = 1; 
 TR2    = 1;  
}

bit SendChar(unsigned char Znak)
{
 if(flag2)
 {
  P0_0=1;
 }
 else
 {
  P0_0=0;
 }
 TI = 0;
 SBUF = Znak;
 while(TI == 0) {;}
    TI = 0;
 return 1; 
}
 
 
void main(void)
{
 Init(); 
 while(1)
 {
     P2 = Tab[i];
    Key = P2;
    if ((K1 & K2 & K3) == 0)
      {
      if (flag == 0)
        {
         // Obsluga przycisków dla LCD i 7segCC
         P1 = Key;
         if (Key == 0xE7) {SendChar('1');}  // 
         if (Key == 0xEB) {SendChar('2');}  // 
         if (Key == 0xED) {SendChar('3');} // 
         if (Key == 0xD7) {SendChar('4');} // 
         if (Key == 0xDB) {SendChar('5');} // 
         if (Key == 0xDD) {SendChar('6');} //  kody do wyslania 
         if (Key == 0xB7) {SendChar('7');} // 
         if (Key == 0xBB) {SendChar('8');} // 
         if (Key == 0xBD) {SendChar('9');} // 
         if (Key == 0x7B) {SendChar('0');} // 
         if (Key == 0x77) {SendChar('*');} // 
         if (Key == 0x7D) {SendChar('#');} // 
         flag2=!flag2;

        flag = 1;
       }  
     }
    else
      {
        if (i == 3) {i = 0;} else {i++;}
      flag = 0;
     }
 }
}