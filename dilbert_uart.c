//UART Functions 
//Roger Traylor 11.l6.11
//For controlling the UART and sending debug data to a terminal
//as an aid in debugging.

/*
To use this program:
  OSX:
       -Install FTDI driver
       -In terminal app: kextstat -l | grep FTDI
        this should return something like:
         116    0 0xffffff7f81a5c000 0x8000     0x8000     com.FTDI.driver.FTDIUSBSerialDriver (2.2.18) <109 12 5 4 3 1>
        if the FTDI driver installed successfully
       -Then in terminal app:  ls /dev/cu.*
        Look for a string similar to:  /dev/cu.usbserial-A800fh27
       -Use i/o file name as follows in terminal: screen /dev/cu.usbserial-A800fh27  57600 8N1
       -To exit screen, type ctrl-A then /
*/

#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include "uart_functions.h"
#include <util/delay.h>
#include <avr/pgmspace.h>

char first_string  [13]  = "first_string";
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

uint8_t i;
char    ch;

int main(){
  uart_init();  

  while(1){
    uart_puts("\033[2J\033[;H");  //clear terminal screen
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
    
    for(i=0;i<=9;i++){_delay_ms(100);}
    }//while
}//main
