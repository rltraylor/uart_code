//UART Functions 
//Roger Traylor 11.l6.11
//For controlling the UART and sending debug data to a terminal
//as an aid in debugging.

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

#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include "uart_functions.h"
#include "lcd_functions.h"
#include <util/delay.h>
#include <avr/pgmspace.h>

char first_string [13]  = "first_string";
char second_string [13]  = "second_string";

char char_ptr[20];

const char Dilbert0  [] PROGMEM = "                    \n\r";
const char Dilbert1  [] PROGMEM = "                    \n\r";
const char Dilbert2  [] PROGMEM = "    /\\/\\/\\/\\/\\/\\    \n\r";  
const char Dilbert3  [] PROGMEM = "   <            >   \n\r";
const char Dilbert4  [] PROGMEM = "    |          |    \n\r";
const char Dilbert5  [] PROGMEM = "    |          |    \n\r";
const char Dilbert6  [] PROGMEM = "    |   _  _   |    \n\r";
const char Dilbert7  [] PROGMEM = "   -|_ / \\/ \\_ |-   \n\r";
const char Dilbert8  [] PROGMEM = "  |I|  \\_/\\_/  |I|  \n\r";
const char Dilbert9  [] PROGMEM = "   -|   /  \\   |-   \n\r";
const char Dilbert10 [] PROGMEM = "    |   \\__/   |    \n\r";
const char Dilbert11 [] PROGMEM = "    |          |    \n\r";
const char Dilbert12 [] PROGMEM = "    |          |    \n\r";
const char Dilbert13 [] PROGMEM = "    |__________|    \n\r";
const char Dilbert14 [] PROGMEM = "   /___/\\__/\\___\\   \n\r";
const char Dilbert15 [] PROGMEM = "  /     | \\|     \\  \n\r";
const char Dilbert16 [] PROGMEM = "    /\\  |\\ | _@|#_  \n\r";
const char Dilbert17 [] PROGMEM = "   / /\\ | \\| |   |  \n\r";
const char Dilbert18 [] PROGMEM = "   \\/  / \\ / |   |  \n\r";
const char Dilbert19 [] PROGMEM = "    \\_/___/   \\_/   \n\r";
const char Dilbert20 [] PROGMEM = "                    \n\r";

extern char uart_tx_buf[40];      //holds string to send to crt
extern char uart_rx_buf[40];      //holds string that recieves data from uart

uint8_t strength=1;
uint8_t i;
char    ch;

//this is in lcd_functions....right???
void spi_init(void){                              
  DDRB   = DDRB | 0x07;           //Turn on SS, MO
  SPCR  |= (1<<SPE) | (1<<MSTR);  //set up SPI mod
  SPSR  |= (1<<SPI2X);            // double speed 
 }//spi_init     


int main(){
  uart_init();  
  DDRF = 0x08; //lcd port twiddle pin
  spi_init();
  lcd_init();
  clear_display();
  cursor_home();

  uart_puts("\033[2J\033[;H");  //clear terminal screen

  while(1){
//  uart_puts("*****************\n\r");
//  uart_puts("This is a test\n\r");
//  uart_puts("The value is:");
//  itoa((int)strength, uart_tx_buf, 10);
//  uart_puts(uart_tx_buf);
//  uart_puts("\n\r");


  uart_puts("\033[2J\033[;H");  //clear terminal screen

/*
  for(i=0;i<=9;i++){_delay_ms(100);}

  uart_puts_p(Dilbert0);
  uart_puts_p(Dilbert1);
  uart_puts_p(Dilbert2);
  uart_puts_p(Dilbert3);
  uart_puts_p(Dilbert4);
  uart_puts_p(Dilbert5);
  uart_puts_p(Dilbert6);
  uart_puts_p(Dilbert7);
  uart_puts_p(Dilbert8);
  uart_puts_p(Dilbert9);
  uart_puts_p(Dilbert10);
  uart_puts_p(Dilbert11);
  uart_puts_p(Dilbert12);
  uart_puts_p(Dilbert13);
  uart_puts_p(Dilbert14);
  uart_puts_p(Dilbert15);
  uart_puts_p(Dilbert16);
  uart_puts_p(Dilbert17);
  uart_puts_p(Dilbert18);
  uart_puts_p(Dilbert19);
  uart_puts_p(Dilbert20);

  uart_puts("\n\r");
  uart_puts("Hi! My name is Dilbert\n\r");

*/


/*
  if (UCSR0A & (1<<RXC0)) {
    char2lcd(UDR0); 
    PORTB ^= 0x01;
  }
*/


if (UCSR0A & (1<<RXC0)){ //check for character received
    ch = UDR0;  //get character
    switch(ch){
      case 'a':
        string2lcd(first_string); 
        break;
      case 'b':
        string2lcd(second_string); 
        break;
      case 'c':
        string2lcd(itoa(strength,char_ptr,10));  //print present value of strentgh
        uart_puts(itoa(strength,uart_tx_buf,10));  //print present value of strentgh
        uart_puts("\n\r");
        break;
      default:
        char2lcd('a');
        break;
    }//switch    
  } //get character and print if one came in


 strength++;
  for(i=0;i<=9;i++){_delay_ms(50);}
  }//while
}//main
