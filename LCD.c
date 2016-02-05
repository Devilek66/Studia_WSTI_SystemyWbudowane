#include <REGX52.H>
unsigned char Set[9];
extern void LcdInit();
extern void LcdWelcome();
extern void Lcd_Cursor (char row, char column);
extern void Lcd_DisplayCharacter (char a_char);
unsigned char rand=0;
unsigned char rand2=10;
bit gowno=1;
bit czyPC=0;
unsigned char buffor=0x00;
unsigned char buffor2=0x00;
unsigned char symbol='X';
unsigned char data Var1;
unsigned char data Var2;
unsigned char data Var3;

unsigned char Value = 0;




void Reset(void)
{
 ;
}
void Stop(unsigned char bufor)
{
   Odswiez();
   Lcd_Cursor(3,6);
   Lcd_DisplayCharacter(symbol);
   if(bufor=='*'||bufor=='#'||bufor=='0')
   {
   	Reset();
   }
}
void resymb(void)
{
 if(symbol=='X')
 {
  symbol='O';
 }
 else
 {
  symbol='X';
 }
 Lcd_Cursor(2,2);
 Lcd_DisplayCharacter(symbol);
}

 bit CzyWin(void)
{
 if(gowno)
 {
 if((Set[0]==Set[1])&&(Set[1]==Set[2])&&(Set[1]!='-')){resymb();gowno=0;return 1;}
 if((Set[0]==Set[4])&&(Set[4]==Set[8])&&(Set[1]!='-')){resymb();gowno=0;return 1;}
 if((Set[0]==Set[3])&&(Set[3]==Set[6])&&(Set[1]!='-')){resymb();gowno=0;return 1;}
 if((Set[2]==Set[4])&&(Set[4]==Set[6])&&(Set[1]!='-')){resymb();gowno=0;return 1;}
 if((Set[1]==Set[4])&&(Set[4]==Set[7])&&(Set[1]!='-')){resymb();gowno=0;return 1;}
 if((Set[2]==Set[5])&&(Set[5]==Set[8])&&(Set[1]!='-')){resymb();gowno=0;return 1;}
 if((Set[3]==Set[4])&&(Set[4]==Set[5])&&(Set[1]!='-')){resymb();gowno=0;return 1;}
 if((Set[6]==Set[7])&&(Set[7]==Set[8])&&(Set[1]!='-')){resymb();gowno=0;return 1;}
 return 0;
 }
 else
 {
  return 1;
 }
}

 void PC(void)
{
 bit flaga=0;
 int kupa;
 kupa=0;
 while(flaga==0)
 {
  if(Set[rand%9]=='-')
  {
   Set[rand%9]=symbol;
   flaga=1;
  }
  else
  {
   kupa++;
   rand++;
   if(kupa==20)
    flaga=1;
  }
 }
 resymb();
}

bit spr(x)
{
  if(Set[x]=='-')
  {
   Set[x]=symbol;
   return 1;
  }
  else
  {	
   return 0;
  }
}

void Odswiez(void)
{
	int i,j,z;
	z=0;
   for(i=0;i<3;i++)
   {
   	for(j=0;j<3;j++)
	{

	 Lcd_Cursor(i+1,j+10);
	 Lcd_DisplayCharacter(Set[z]);
	 	 z++;
	}
   }
}

void Start(void)
{
	int i,j,z;
	z=0;
   for(i=0;i<3;i++)
   {
   	for(j=0;j<3;j++)
	{

	 Lcd_Cursor(i+1,j+10);
	 Lcd_DisplayCharacter(Set[z]);
	 	 z++;
	}
   }
}
/*void ox(char znak)
{
 

}
	 */

void paternshit(unsigned char znak)
{
if(znak=='1'){if(spr(0)){Set[0]=symbol;resymb();czyPC=1;}}
if(znak=='2'){if(spr(1)){Set[1]=symbol;resymb();czyPC=1;}}
if(znak=='3'){if(spr(2)){Set[2]=symbol;resymb();czyPC=1;}}
if(znak=='4'){if(spr(3)){Set[3]=symbol;resymb();czyPC=1;}}
if(znak=='5'){if(spr(4)){Set[4]=symbol;resymb();czyPC=1;}}
if(znak=='6'){if(spr(5)){Set[5]=symbol;resymb();czyPC=1;}}
if(znak=='7'){if(spr(6)){Set[6]=symbol;resymb();czyPC=1;}}
if(znak=='8'){if(spr(7)){Set[7]=symbol;resymb();czyPC=1;}}
if(znak=='9'){if(spr(8)){Set[8]=symbol;resymb();czyPC=1;}}
}


void ISR_Serial(void) interrupt 4
  {
    if (RI == 1)
  {
     RI = 0;
	 buffor=SBUF;
	  Lcd_DisplayCharacter(buffor);
	   if(!CzyWin())
	  {
	   paternshit(buffor);
	   

	   if(czyPC)
	   {
	    PC();
	    czyPC=0;
	   }
	   	   Odswiez();
	  }
	  else
	  {
	   Odswiez();
	   Stop(buffor);
	  }
   Odswiez();
  }
  }

void SerialInit(void)
  {
   P3_4 = 0;  // Ustawienie na odbiornik
   SCON = 0x50;
   RCAP2L = TL2 = 0xDC;
   RCAP2H = TH2 = 0xFF;
   T2CON = 0x30;
   ES = 1; 
   TR2 = 1; 
   EA = 1;
  }

void TabInit(void)
{
	int i;
	for(i=0;i<9;i++)
	{
	  Set[i]='-';
	}

}

void main(void){
  LcdInit();       // Zainicjowanie rejestrów uP
  LcdWelcome();
  SerialInit();
  TabInit();
  Start();
  while(1) {rand++;}
}