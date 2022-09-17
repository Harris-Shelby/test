#pragma once

#include<Arduino.h>
#include<SPI.h>

#define EPD_MOSI_0  digitalWrite(_SDI_Pin,LOW)
#define EPD_MOSI_1  digitalWrite(_SDI_Pin,HIGH) 

#define EPD_CLK_0 digitalWrite(_SCK_Pin,LOW)
#define EPD_CLK_1 digitalWrite(_SCK_Pin,HIGH)

#define EPD_CS_0 digitalWrite(_CS_Pin,LOW)
#define EPD_CS_1 digitalWrite(_CS_Pin,HIGH)

#define EPD_DC_0  digitalWrite(_DC_Pin,LOW)
#define EPD_DC_1  digitalWrite(_DC_Pin,HIGH)
#define EPD_RST_0 digitalWrite(_RES_Pin,LOW)
#define EPD_RST_1 digitalWrite(_RES_Pin,HIGH)
#define isEPD_BUSY digitalRead(_BUSY_Pin)

#define ALLSCREEN_GRAGHBYTES  4000
class EPaperDrive
{
private:
    /* data */
    uint8_t _BUSY_Pin;
    uint8_t _RES_Pin;
    uint8_t _DC_Pin;
    uint8_t _CS_Pin;
    uint8_t _SCK_Pin;
    uint8_t _SDI_Pin;

    void driver_delay_us(unsigned int xus);
    void driver_delay_xms(unsigned long xms);
    void DELAY_S(unsigned int delaytime);   

    /**
     * @brief 
     * 
     * @param xrate 
     */
    void SPI_Delay(uint8_t xrate);
    /**
     * @brief 
     * 
     * @param value 
     */
    void SPI_Write(uint8_t value);

public:
    EPaperDrive(
        /* args */
    uint8_t BUSY_Pin,
    uint8_t RES_Pin,
    uint8_t DC_Pin,
    uint8_t CS_Pin,
    uint8_t SCK_Pin = 14,
    uint8_t SDI_Pin = 13);

    ~EPaperDrive();

    /**
     * @brief 睡眠，节省功耗
     * 
     * @return ** void 
     */
    void EPD_DeepSleep(void);
    
    /**
     * @brief 全刷初始化
     * 
     */
    void EPD_Init_Full(void);

    /**
     * @brief 全刷更新
     * 
     */

    void EPD_Update(void);
    /**
     * @brief 等待BUSY信号变空闲（最大200ms超时）
     * 
     * @return Bool 1 代表成功，0代表超时
     */

    void EPD_READBUSY(void);
    /**
     * @brief 向墨水屏驱动芯片写入命令
     * 
     * @param command 命令的值
     */
    void EPD_WriteCMD(uint8_t command);
    /**
     * @brief 向墨水屏驱动芯片写入数据
     * 
     * @param data 数据的值
     */
    void EPD_WriteData(uint8_t data);

    //Display 
    void EPD_WhiteScreen_ALL(const unsigned char *BW_datas,const unsigned char *R_datas);
    void EPD_WhiteScreen_ALL_Clean(void);
};


