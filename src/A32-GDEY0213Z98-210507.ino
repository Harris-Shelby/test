#include<Arduino.h>
#include<SPI.h>
#include"Ap_29demo.h"
#include"EPaperDrive.h"

//IO settings
int BUSY_Pin = 17; 
int RES_Pin = 16; 
int DC_Pin = 4; 
int CS_Pin = 15; 
int SCK_Pin = 14; 
int SDI_Pin = 13; 

EPaperDrive EPD(BUSY_Pin, RES_Pin, DC_Pin, CS_Pin);

#define MONOMSB_MODE 1
#define MONOLSB_MODE 2 
#define RED_MODE     3

#define MAX_LINE_BYTES 16// =128/8
#define MAX_COLUMN_BYTES  250

// #define ALLSCREEN_GRAGHBYTES  4000

void setup() {
  //  pinMode(BUSY_Pin, INPUT); 
  //  pinMode(RES_Pin, OUTPUT);  
  //  pinMode(DC_Pin, OUTPUT);    
  //  pinMode(CS_Pin, OUTPUT);    
  //  pinMode(SCK_Pin, OUTPUT);    
  //  pinMode(SDI_Pin, OUTPUT);
       //Full screen refresh
    EPD.EPD_Init_Full(); //Electronic paper initialization
    EPD.EPD_WhiteScreen_ALL(gImage_BW,gImage_R); //Refresh the picture in full screen
    EPD.EPD_DeepSleep(); //Enter deep sleep,Sleep instruction is necessary, please do not delete!!! 
    
}

//Tips//
/*When the electronic paper is refreshed in full screen, the picture flicker is a normal phenomenon, and the main function is to clear the display afterimage in the previous picture.
  When the local refresh is performed, the screen does not flash.*/
/*When you need to transplant the driver, you only need to change the corresponding IO. The BUSY pin is the input mode and the others are the output mode. */
  
void loop() {

    
    // //Clean
    // EPD_Init_Full(); //Electronic paper initialization
    // EPD_WhiteScreen_ALL_Clean();
    // EPD_DeepSleep(); //Enter deep sleep,Sleep instruction is necessary, please do not delete!!!
    // delay(2000); 
    // while(1);
}











