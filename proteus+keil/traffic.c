#include <LPC213X.H>
static int flg=0;
void Delay(int n)
{
	T0TCR = (1<<1);
	T0MR0 = n;
	T0MCR = (3<<0); 
	T0TCR = (1<<0);	
	T0PR = 0x270F;
	while(!(T0IR & (1<<0))); 
	T0IR = (1<<0);	
}

void isr_ext0()__irq
{
	
	IOPIN1=(1<<18)|(1<<20)|(1<<22)|(1<<25);
	Delay(6000);
	flg=1;
	EXTINT = (1<<0);
	VICVectAddr=0x00;
}
void isr_ext1()__irq
{
	
	IOPIN1=(1<<16)|(1<<21)|(1<<23)|(1<<25);
	Delay(6000);
	flg=2;
	EXTINT = (1<<1);
	VICVectAddr=0x00;
}
void isr_ext2()__irq
{
	IOPIN1=(1<<16)|(1<<19)|(1<<24)|(1<<26);
	Delay(6000);
	flg=3;
	EXTINT = (1<<2);
	VICVectAddr=0x00;
}
void isr_ext3()__irq
{
	IOPIN1=(1<<17)|(1<<19)|(1<<22)|(1<<27);
	Delay(6000);
	flg=4;
	EXTINT = (1<<3);
	VICVectAddr=0x00;
}
void intr_init()
{
	PINSEL0=0X000CC0CC;
	VICIntSelect=0x00;
	VICVectAddr0=(unsigned)isr_ext0;
	VICVectCntl0=(1<<5)|(14<<0);
	VICVectAddr1=(unsigned)isr_ext1;
	VICVectCntl1=(1<<5)|(15<<0);
	VICVectAddr2=(unsigned)isr_ext2;
	VICVectCntl2=(1<<5)|(16<<0);
	VICVectAddr3=(unsigned)isr_ext3;
	VICVectCntl3=(1<<5)|(17<<0);
	VICIntEnable=(0x0F<<14);
	VPBDIV=0x00;
	EXTMODE=(0xF<<0);
	EXTPOLAR=(0xF<<0);
}
void initial()
{

	IOPIN1=(1<<18)|(1<<20)|(1<<22)|(1<<25);
	Delay(3000);
	IOPIN1=(1<<16)|(1<<21)|(1<<23)|(1<<25);
	Delay(3000);
	IOPIN1=(1<<16)|(1<<19)|(1<<24)|(1<<26);
	Delay(3000);
	IOPIN1=(1<<17)|(1<<19)|(1<<22)|(1<<27);
	Delay(3000);	
}
int  main()
{
	
	intr_init();
	IODIR1 = ((0XFFF)<<16); 
	while(1)
	{
      if(flg==1)
			{
				IOPIN1=(1<<16)|(1<<21)|(1<<23)|(1<<25);
				Delay(3000);
				IOPIN1=(1<<16)|(1<<19)|(1<<24)|(1<<26);
				Delay(3000);
				IOPIN1=(1<<17)|(1<<19)|(1<<22)|(1<<27);
				Delay(3000);
			}
			else if(flg==2)
			{
				IOPIN1=(1<<16)|(1<<19)|(1<<24)|(1<<26);
				Delay(3000);
				IOPIN1=(1<<17)|(1<<19)|(1<<22)|(1<<27);
				Delay(3000);
				IOPIN1=(1<<18)|(1<<20)|(1<<22)|(1<<25);
				Delay(3000);
			}
			else if(flg==3)
			{
				IOPIN1=(1<<17)|(1<<19)|(1<<22)|(1<<27);
				Delay(3000);
				IOPIN1=(1<<18)|(1<<20)|(1<<22)|(1<<25);
				Delay(3000);
				IOPIN1=(1<<16)|(1<<21)|(1<<23)|(1<<25);
				Delay(3000);
				
			}
			else
			{
				flg=0;
				initial();
			}
		}
}