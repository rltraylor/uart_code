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
uint16_t brightness[10] = {0xFF, 0xF8, 0xF0, 0xE8, 0xD0, 0xC0, 0xA0, 0x80, 0x10, 0x00};

uint8_t i,level;
char    rx_char; 
extern char uart_tx_buf[40];      //holds string to send to crt


void tcnt2_init(void){                              
  //fast PWM mode, TOP=0xFF, clear on match, clk/128, PWM output on PB7
  TCCR2 =  (1<<WGM21) | (1<<WGM20) | (1<<COM21) | (1<<COM20) | (1<<CS20) | (1<<CS21);
  OCR2  = 0xFF;  //inital value, will be overwritten 
}

int main(){
  DDRB |= 0x80; //PWM at PB7 
  tcnt2_init();
  uart_init();  
  uart_puts("\033[2J\033[;H");  //clear terminal screen
  while(1){
    if(UCSR0A & (1<<RXC0)){ //check for character received
      rx_char = UDR0;       //get character
      switch(rx_char){
        case 'b':  //brighten the LED
          if(level < 9){
            level++; 
            uart_puts("level is now ");
            uart_puts(itoa(level,uart_tx_buf,10));  //print present value of brightness
            uart_puts("\n\r");
            OCR2 = brightness[level];
          }
          else{ 
            uart_puts("At max brightness! \n\r");
          }
          break;
        case 'd':  //dim the LED
          if(level > 0){
            level--; 
            uart_puts("level is now ");
            uart_puts(itoa(level,uart_tx_buf,10));  //print present value of brightness
            uart_puts("\n\r");
            OCR2 = brightness[level];
          }
          else{ 
            uart_puts("At min brightness!\n\r");
          }
          break;
        case 'c':  //current level query
          uart_puts("Current brightness is: ");
          uart_puts(itoa(level,uart_tx_buf,10));  //print present value of brightness
          uart_puts("\n\r");
          break;
        default: 
          break;
      }//switch    
    } //if 
  }//while(1)
}//main
