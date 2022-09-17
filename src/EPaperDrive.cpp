#include"EPaperDrive.h"

EPaperDrive::EPaperDrive(
    /* args */
    uint8_t BUSY_Pin,
    uint8_t RES_Pin,
    uint8_t DC_Pin,
    uint8_t CS_Pin,
    uint8_t SCK_Pin,
    uint8_t SDI_Pin)
{
    _BUSY_Pin = BUSY_Pin; 
    _RES_Pin = RES_Pin; 
    _DC_Pin = DC_Pin; 
    _CS_Pin = CS_Pin; 
    _SCK_Pin = SCK_Pin; 
    _SDI_Pin = SDI_Pin;

    pinMode(BUSY_Pin, INPUT); 
    pinMode(RES_Pin, OUTPUT);  
    pinMode(DC_Pin, OUTPUT);    
    pinMode(CS_Pin, OUTPUT);    
    pinMode(SCK_Pin, OUTPUT);    
    pinMode(SDI_Pin, OUTPUT);
}

EPaperDrive::~EPaperDrive()
{
}

void EPaperDrive::driver_delay_us(unsigned int xus)  //1us
{
  for(;xus>1;xus--);
}
void driver_delay_xms(unsigned long xms) //1ms
{  
    unsigned long i = 0 , j=0;

    for(j=0;j<xms;j++)
  {
        for(i=0; i<256; i++);
    }
}

void EPaperDrive::DELAY_S(unsigned int delaytime)     
{
  int i,j,k;
  for(i=0;i<delaytime;i++)
  {
    for(j=0;j<4000;j++)           
    {
      for(k=0;k<222;k++);
                
    }
  }
}

void EPaperDrive::SPI_Delay(uint8_t xrate)
{
  uint8_t i;
  while(xrate)
  {
    for(i=0;i<2;i++);
    xrate--;
  }
}

void EPaperDrive::SPI_Write(uint8_t value)                                    
{                                                           
   uint8_t i;  
   SPI_Delay(1);
    for(i=0; i<8; i++)   
    {
        EPD_CLK_0;
       SPI_Delay(1);
       if(value & 0x80)
          EPD_MOSI_1;
        else
          EPD_MOSI_0;   
        value = (value << 1); 
       SPI_Delay(1);
       driver_delay_us(1);
        EPD_CLK_1; 
        SPI_Delay(1);
    }
}

void EPaperDrive::EPD_WriteCMD(uint8_t command)
{
  SPI_Delay(1);
  EPD_CS_0;                   
  EPD_DC_0;   // command write
  SPI_Write(command);
  EPD_CS_1;
}

void EPaperDrive::EPD_WriteData(uint8_t command)
{
  SPI_Delay(1);
  EPD_CS_0;                   
  EPD_DC_1;   // command write
  SPI_Write(command);
  EPD_CS_1;
}

void EPaperDrive::EPD_Init_Full(void)
{
  EPD_RST_0;  // Module reset      
  delay(10); //At least 10ms delay 
  EPD_RST_1; 
  delay(10); //At least 10ms delay  
    
  EPD_READBUSY();   
  EPD_WriteCMD(0x12);  //SWRESET
  EPD_READBUSY();   
    
  EPD_WriteCMD(0x01); //Driver output control      
  EPD_WriteData(0xF9);
  EPD_WriteData(0x00);
  EPD_WriteData(0x00);

  EPD_WriteCMD(0x11); //data entry mode       
  EPD_WriteData(0x01);

  EPD_WriteCMD(0x44); //set Ram-X address start/end position   
  EPD_WriteData(0x00);
  EPD_WriteData(0x0F);    //0x0F-->(15+1)*8=128

  EPD_WriteCMD(0x45); //set Ram-Y address start/end position          
  EPD_WriteData(0xF9);   //0xF9-->(249+1)=250
  EPD_WriteData(0x00);
  EPD_WriteData(0x00);
  EPD_WriteData(0x00); 

  EPD_WriteCMD(0x3C); //BorderWavefrom
  EPD_WriteData(0x05);  
      
  EPD_WriteCMD(0x18); //Read built-in temperature sensor
  EPD_WriteData(0x80);  
  
  EPD_WriteCMD(0x21); //  Display update control
  EPD_WriteData(0x00);  
  EPD_WriteData(0x80);  

  EPD_WriteCMD(0x4E);   // set RAM x address count to 0;
  EPD_WriteData(0x00);
  EPD_WriteCMD(0x4F);   // set RAM y address count to 0X199;    
  EPD_WriteData(0xF9);
  EPD_WriteData(0x00);
  EPD_READBUSY();
  
}

void EPaperDrive::EPD_WhiteScreen_ALL(const unsigned char *BW_datas,const unsigned char *R_datas)
{
   unsigned int i;  
  EPD_WriteCMD(0x24);   //write RAM for black(0)/white (1)
   for(i=0;i<ALLSCREEN_GRAGHBYTES;i++)
   {               
     EPD_WriteData(pgm_read_byte(&BW_datas[i]));
   }
  EPD_WriteCMD(0x26);   //write RAM for black(0)/white (1)
   for(i=0;i<ALLSCREEN_GRAGHBYTES;i++)
   {               
     EPD_WriteData(~(pgm_read_byte(&R_datas[i])));
   }
   EPD_Update();   
}

void EPaperDrive::EPD_WhiteScreen_ALL_Clean(void)
{
   unsigned int i;  
  EPD_WriteCMD(0x24);   //write RAM for black(0)/white (1)
   for(i=0;i<ALLSCREEN_GRAGHBYTES;i++)
   {               
     EPD_WriteData(0xff);
   }
  EPD_WriteCMD(0x26);   //write RAM for black(0)/white (1)
   for(i=0;i<ALLSCREEN_GRAGHBYTES;i++)
   {               
     EPD_WriteData(0x00);
   }
   EPD_Update();   
}

void EPaperDrive::EPD_Update(void)
{
  EPD_WriteCMD(0x22); //Display Update Control
  EPD_WriteData(0xF7);   
  EPD_WriteCMD(0x20);  //Activate Display Update Sequence
  EPD_READBUSY();   

}

void EPaperDrive::EPD_DeepSleep(void)
{  
  EPD_WriteCMD(0x10); //enter deep sleep
  EPD_WriteData(0x01); 
  delay(100);
}

void EPaperDrive::EPD_READBUSY(void)
{ 
  while(1)
  {   //=1 BUSY
     if(isEPD_BUSY==0) break;
  }  
}