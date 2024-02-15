#define FCY 4000000UL 
#include "xc.h" 
#include <libpic30.h> 
 
int main(void) { 
  
 TRISEbits.TRISE12=0; // настройка E12 как цифрового выхода 
 TRISEbits.TRISE14=0; // настройка E14 как цифрового выхода 
 TRISEbits.TRISE15=0; // настройка E15 как цифрового выхода 
 TRISEbits.TRISE13=1; // настройка E13 как цифрового входа 
 CNPUEbits.CNPUE13=1;// подтяжка E13 к питанию 
 TRISDbits.TRISD6=1; // настройка D6 как цифрового входа 
 CNPUDbits.CNPUD6=1;// подтяжка D6 к питанию 
  
 void strobe(int freq_inp) { //Функция мигания. Частота делится на два, потому что иначе ожидание будет равно двум заданным временным константам, а не одной
         freq = freq_inp/2;
         LATEbits.LATE12 = 1; 
         __delay_ms(freq) 
         LATEbits.LATE12 = 0; 
         __delay_ms(freq)         
 } 
  
 
  
 while (1) /*организация бесконечного цикла*/ 
 { 
     if (PORTDbits.RD6 == 0){ 
         strobe(100); //При замыкании D6 - частота мигания - 100 мс
     } 
      
     if (PORTEbits.RE13 == 0){ 
         strobe(500); //При замыкании E13 - частота мигания - 500 мс
     } 
 } 
 return 0; 
} 
                 
