//UART Example for inclass coding
//Roger Traylor 12.4.12
//Setting up the UART and sending data to and from a dumb terminal

/*
install FTDI driver then restart computer
traylor1$ kextstat -l | grep FTDI
116    0 0xffffff7f81a5c000 0x8000     0x8000     com.FTDI.driver.FTDIUSBSerialDriver (2.2.18) <109 12 5 4 3 1>
traylor1$ ls /dev/cu.*
/dev/cu.Bluetooth-Modem    /dev/cu.Bluetooth-Serial-1 /dev/cu.usbserial-A800fh27
/dev/cu.Bluetooth-PDA-Sync /dev/cu.Bluetooth-Serial-2

screen /dev/cu.usbserial-A800fh27  57600 8N1

 to exit ctrl-A then /
*/

/* LINUX instructions...
ls /dev/tty*
look for /dev/ttyUSB0 which is the FTDI chip

screen /dev/ttyUSB0  57600 8N1
*/


#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include "uart_functions.h"
#include <avr/interrupt.h>
#include <util/delay.h>

//                         dimmest                                          brightest

uint8_t i,level;
char    rx_char; 
extern char uart_tx_buf[40];      //holds string to send to crt


int main(){
  DDRB |= 0xFF; //All port B bits on as outputs
  uart_init();  
  uart_puts("\033[2J\033[;H");  //clear terminal screen
  while(1){
    if(UCSR0A & (1<<RXC0)){ //check for character received
      rx_char = UDR0;       //get character
      switch(rx_char){
        case '0': 
          PORTB = 0x01;
          uart_puts("LED ");
          uart_puts(&rx_char);  //print present value of brightness
          uart_puts(" is on now.\n\r");
        break;
        case '1': 
          PORTB = 0x02;
          uart_puts("LED ");
          uart_puts(&rx_char);  //print present value of brightness
          uart_puts(" is on now.\n\r");
        break;
        case '2': 
          PORTB = 0x04;
          uart_puts("LED ");
          uart_puts(&rx_char);  //print present value of brightness
          uart_puts(" is on now.\n\r");
        break;
        case '3': 
          PORTB = 0x08;
          uart_puts("LED ");
          uart_puts(&rx_char);  //print present value of brightness
          uart_puts(" is on now.\n\r");
          break;
        case '9': 
          PORTB = 0x00;
          uart_puts("All LEDs are off.");
          //uart_puts(&rx_char);  //print present value of brightness
          //uart_puts(" is on now.\n\r");
          break;
        default: 
          break;
      }//switch    
    } //if 
  }//while(1)
}//main
