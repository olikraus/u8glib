
#include "LPC11xx.h"
#include <stdio.h>



/*============================================================*/
/* LPC11xx UART */

void UARTInit(void)
{
  LPC_SYSCON->SYSAHBCLKCTRL |= 1<<16;	/* enable IOCON clock */
  LPC_SYSCON->SYSAHBCLKCTRL |= 1<<12;	/* enable UART clock */
  LPC_SYSCON->UARTCLKDIV = 1;			/* PCLK = Master Clock / 1 */
  
  /*
    LPC1114:
      TXD PIO1_7
      RXD PIO1_6
  */
  LPC_IOCON->PIO1_6 = 1;		/* connect UART to RXD pin */
  LPC_IOCON->PIO1_7 = 1;		/* connect UART to TXD pin */
  
  /*
    12MHz/9600				DLM=0,DLL=71,DIVADDVAL=1,MULVAL=10		<===
    50MHz/9600				DLM=0,DLL=217,DIVADDVAL=5,MULVAL=10

    12MHz/38400			DLM=0,DLL=16,DIVADDVAL=2,MULVAL=9
    50MHz/38400			DLM=0,DLL=46,DIVADDVAL=10,MULVAL=13

    12MHz/115200			DLM=0,DLL=4,DIVADDVAL=5,MULVAL=8
    50MHz/115200			DLM=0,DLL=19,DIVADDVAL=3,MULVAL=7
  */
  LPC_UART->LCR = 3 | 128;		/* 8 data bits, one stop bit, enable divider register */
  LPC_UART->DLL = 71 /* dll */;
  LPC_UART->DLM = 0;
  LPC_UART->LCR = 3;			/* 8 data bits, one stop bit, disable divider register */
  LPC_UART->FDR  = (10 /* mulval */ << 4) | 1 /* divaddval */;
  LPC_UART->IER = 0;			/* no interrupts */
  LPC_UART->FCR = 1;			/* FIFO enable */
  LPC_UART->MCR = 0;  
  LPC_UART->TER = 1<<7;			/* enable transmit */
}

int UARTIsDataAvailable(void)
{
  if ( ( LPC_UART->LSR & 1 ) != 0 )
    return 1;
  return 0;
}

int UARTReadData(void)
{
  if ( UARTIsDataAvailable() != 0 )
    return LPC_UART->RBR;
  return -1;
}

void UARTSendData(int data)
{
  while( (LPC_UART->LSR & (1<<5)) == 0 )
    ;
  LPC_UART->THR = data;
}

void UARTSendStr(const char *str)
{
  while( *str != '\0' )
    UARTSendData( (int)(unsigned char)*str++ );
}


/*============================================================*/
/* SystemInit */

uint32_t SystemCoreClock;

void SystemInit(void)
{
  /* SystemInit() is called by the startup code */
  /* according to system_LPC11xx.h it is expected, that the clock freq is set here */
  SystemCoreClock = F_CPU;  
  UARTInit();
}

/*============================================================*/
/* gcc retarget, redirect I/O to UART */

int _write (int fd, char *ptr, int len)
{
  /* Write "len" of char from "ptr" to file id "fd"
   * Return number of char written.
   * Need implementing with UART here. */
  int i;
  for( i = 0; i < len; i++ )
    UARTSendData((int)(unsigned char)ptr[i]);
  return len;
}

int _read (int fd, char *ptr, int len)
{
  /* Read "len" of char to "ptr" from file id "fd"
   * Return number of char read.
   * Need implementing with UART here. */
  if ( UARTIsDataAvailable() == 0 )
    return 0;
  *ptr = UARTReadData();
  return 1;
}

void _ttywrch(int ch) {
  /* Write one char "ch" to the default console
   * Need implementing with UART here. */
  UARTSendData(ch);
}


/*============================================================*/
/* main procedure */


#define LED_GPIO	LPC_GPIO1
#define LED_PIN 8			

void main()
{
  volatile uint32_t count, count_max = 100000;
  int hello = 0;
  LED_GPIO->DIR |= 1 << LED_PIN;		
  LED_GPIO->DATA |= 1 << LED_PIN;

  while (1)
  {
    for (count = 0; count < count_max; count++);	// delay
    LED_GPIO->DATA |= 1 << LED_PIN;
    for (count = 0; count < count_max; count++);	// delay
    LED_GPIO->DATA &= ~(1 << LED_PIN);

    printf("Hello World (%d)!\n\r", hello);
    hello++;
  }
}
