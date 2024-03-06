#define FCY 40000000
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <libpic30.h>

 void strobe(uint16_t freq_inp) { //Функция мигания. Частота делится на два, потому что иначе ожидание будет равно двум заданным временным константам, а не одной
         uint16_t freq = (50+0.09768*freq_inp)/2;
         LATEbits.LATE12 = 1; 
         __delay_ms(freq) 
         LATEbits.LATE12 = 0; 
         __delay_ms(freq)         
 } 

void Adc_init(){
 ADCON1Lbits.ADSIDL = 0;
 ADCON1Hbits.FORM = 0;
 ADCON1Hbits.SHRRES0 = 1;
 ADCON1Hbits.SHRRES1 = 1;
 ADCON1Lbits.ADON = 0x1;
 ADCON5Lbits.SHRPWR = 1; 
 while(ADCON5Lbits.SHRRDY == 0);
 ADCON3Hbits.SHREN = 1; 
 ADTRIG3L = 0x100;
 ADTRIG0H = 0x100;//ADTRIG0H[12:8]
 ADTRIG1L = 0x001;//ADTRIG1L[4:0]
}


uint16_t read_Adc(uint8_t channel){
 uint16_t result;
 
 ADCON3Lbits.SWCTRG = 1;
 __delay_ms(5)
 switch(channel)
 {
 case 0:
 while(!ADSTATLbits.AN3RDY);
 __delay_ms(5)
 result = ADCBUF3;
 break;
 case 1:
 while(!ADSTATLbits.AN4RDY);
 __delay_ms(5)
 result = ADCBUF4;
 break;
 case 2:
 while(!ADSTATLbits.AN13RDY);
 __delay_ms(5)
 result = ADCBUF13;
 break;
 }
 return result;
}

void main(){
    TRISEbits.TRISE12=0; // настройка E12 как цифрового выхода 
    Adc_init();
    while(1){
        uint16_t freq = read_Adc(2);
        strobe(freq);
    }
}
