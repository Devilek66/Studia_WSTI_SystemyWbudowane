#include <REGX52.H>
volatile unsigned char data i;
volatile unsigned char data j;
volatile unsigned char data x;

void Wait(void)
{
int g;
for(g=0;g<x*100;g++)
  {
  ;
  }
}


void ISR_INT1(void) interrupt 2
{ 
  j++;
  if(j>=2)
  {
  	P2_5=1;
	x++;
	 Wait();
	 P2_5=0;
	j=0;
	if(x==20)
	{
	  x=0;
	}
  }
  
}
void ISR_INT0(void) interrupt 0
{
  i++;
  if(i==10)
  {
  	P2_1=!P2_1;
  	P2_2=!P2_2;
	i=0;
  }
}

void Init(void)
{
	i=0;
	j=0;
	x=0;

	IT0=1;
	EX0=1;

	IT1=1;
	EX1=1;
			 
	EA=1;
	P2=0x5C;
	P2_6=0;
	P3_4=0;
}

void main(void)
{		
	P2=0;											  
	Init();
	//P3=0x0C;
	//P2_2=1;
	//P2_3=1;

	while(1)
		{
		;
		}
}