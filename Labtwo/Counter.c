#pragma config ALTI2C1 = ON

#define FCY 40000000
#include <xc.h>
#include <libpic30.h>
#include <stdlib.h>

#define PIN_EN (1 << 2)
#define BACKLIGHT (1 << 3)
#define RET_STRING 0b10000000
#define LCD_CLEAR 0b00000001
#define LCD_ADRESS 0x4E





typedef enum
{
 COMMAND=0,
 DATA=1 
}
LDCType_t;

void initI2C(void)
{
 I2C1BRG = 0xC3; 
 I2C1CONLbits.I2CEN = 1; 
 I2C1CONLbits.I2CSIDL=1;
}

void I2CWrite(uint8_t adr,uint8_t data)
{
 while(I2C1CONLbits.PEN);
 I2C1CONLbits.SEN = 1;
 while (I2C1CONLbits.SEN != 0);
 I2C1TRN = adr;
 while (I2C1STATbits.TRSTAT == 1);
 I2C1TRN = data;
 while (I2C1STATbits.TRSTAT == 1);
 I2C1CONLbits.PEN = 1;
}

void I2CWriteBuff(uint8_t adr,uint8_t* data,uint16_t len)
{
 uint16_t i;
 while(I2C1CONLbits.PEN);
 I2C1CONLbits.SEN = 1;
 while (I2C1CONLbits.SEN != 0);
 I2C1TRN = adr;
 for(i=0;i<len;i++)
 {
 while (I2C1STATbits.TRSTAT == 1);
 I2C1TRN=data[i];
 } 
 while (I2C1STATbits.TRSTAT == 1);
 I2C1CONLbits.PEN = 1;
}
void LCDSend(uint8_t lcd_addr, uint8_t data, LDCType_t flags)
{
 uint8_t high = data & 0xF0;
 uint8_t low = (data << 4) & 0xF0;
 uint8_t data_arr[6];
 data_arr[0] = high|flags|BACKLIGHT;
 data_arr[1] = high|flags|BACKLIGHT|PIN_EN;
 data_arr[2] = high|flags|BACKLIGHT;
 data_arr[3] = low|flags|BACKLIGHT;
 data_arr[4] = low|flags|BACKLIGHT|PIN_EN;
 data_arr[5] = low|flags|BACKLIGHT;
 I2CWriteBuff(lcd_addr,&data_arr,6);
}

void LCDInit(void)
{
 LCDSend(LCD_ADRESS, 0b00110000,COMMAND);
 LCDSend(LCD_ADRESS, 0b00000010,COMMAND);
 LCDSend(LCD_ADRESS, 0b00001100,COMMAND);
 LCDSend(LCD_ADRESS, LCD_CLEAR,COMMAND); 
}
void LCDPritStr(uint8_t* str, uint16_t len)
{
    uint16_t i;
    for(i=0;i<len;i++)
    {
        LCDSend(LCD_ADRESS, str[i],DATA);
    } 
}


void main(){
    initI2C();
    LCDInit();
    TRISEbits.TRISE13=1;
    CNPUEbits.CNPUE13=1;
    uint8_t aString[4];
    uint8_t counter = 1;
    uint8_t mode = 1;
    uint8_t screenmode = 0;
    while(1){
        while (PORTEbits.RE13) {
            if (!mode) {    
                counter++;
                mode = 1;
                screenmode = 1;
            }
        }
        mode = 0;
    aString[3] = counter % 10 + '0';
    aString[2] = ((counter % 100) / 10) + '0';  
    aString[1] = ((counter % 1000) / 100) + '0'; 
    aString[0] = (counter / 1000) + '0';
        LCDSend(LCD_ADRESS, RET_STRING,COMMAND);   
        LCDPritStr(aString, 4);
        __delay_ms(5)
    }
}
