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
  
 int increment (int counter) { //функция инкремента. Позволяет изменять число в нужном количестве режимов, в данном случае, в трёх
     counter += 1; 
     return counter%3; 
 } 
 
 int mode = 0; 
  
 while (1) /*организация бесконечного цикла*/ 
 { 
     if (PORTEbits.RE13 == 0){ //Проверка на нажатие кнопки, изменение режима с небольшим ожиданием для увеличения чувствительности к нажатию
         while(PORTEbits.RE13 == 0);  
             mode = increment(mode); 
             __delay_us(10); 
     } else { 
                          //При режиме 0 - светодиод выключен
        if (mode == 1){ 
             strobe(500); //При режиме 1 - частота мигания - 500 мс
        } 
        if (mode == 2){ 
             strobe(100); //При режиме 2 - частота мигания - 100 мс
        } 
        } 
 } 
 return 0; 
} 
