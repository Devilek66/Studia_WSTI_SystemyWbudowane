#include <REGX52.H>

unsigned char bufor;
unsigned char suma;
unsigned char licznik;
unsigned char liczba;
unsigned char buforL;
unsigned char sumaL;
unsigned char licznikL;
unsigned char liczbaL;
unsigned char xdata Prawy _at_ 0xFD00;
unsigned char xdata Lewy _at_ 0xFE00;
unsigned char Set[]={0x00,0x00,0x00,0x00,0x30,0x09,0x06};
unsigned char Set2[]={0x00,0x30,0x09,0x06,0x00,0x00,0x00};
					//0    1    2     3    4    5    6    s  kropka

void magicL(void)
{
int i;
if(liczbaL==0x00){liczbaL=0x01;}
for(i=0;i<1000;i++)
{
	Lewy=sumaL;
}
if(sumaL==0x3F){sumaL=0x00; licznikL=0x20; liczbaL=0x00; buforL=0x00;}
if(liczbaL<=licznikL)
{
  sumaL=sumaL+liczbaL;
  sumaL=sumaL-buforL;
  buforL=liczbaL;
}
else
{
  liczbaL=0x00;
  buforL=0x00;
  licznikL=licznikL/2;
}
liczbaL=liczbaL*2;
}

void magicP(void)
{
int i;
if(liczba==0x00){liczba=0x01;}
for(i=0;i<1000;i++)
{
	Prawy=suma;
	Lewy=sumaL;
}
if(suma==0x3F){suma=0x00; licznik=0x20; liczba=0x00; bufor=0x00; magicL();}
if(liczba<=licznik)
{
  suma=suma+liczba;
  suma=suma-bufor;
  bufor=liczba;
}
else
{
  liczba=0x00;
  bufor=0x00;
  licznik=licznik/2;
}
liczba=liczba*2;
}


void main(void)
{
	unsigned char bol=0x01;
	unsigned char bool=0x00;
	unsigned char index=0x00;
	P3_4=0;
	bufor=0x00;
	licznik=0x20;
	liczba=0x00;
	suma=0x00;
	buforL=0x00;
	licznikL=0x20;
	liczbaL=0x00;
	sumaL=0x00;
  while(1)
  {
    magicP();
  }
}