#include "xc.h" 
int main(void) { 
  
 TRISEbits.TRISE12=0; // настройка E12 как цифрового выхода 
 TRISEbits.TRISE13=1; // настройка E13 как цифрового входа 
 CNPUEbits.CNPUE13=1;// подтяжка E13 к питанию 
  
 while (1) /*организация бесконечного цикла*/ 
 { 
 LATEbits.LATE12=!PORTEbits.RE13; // Приравниваем значениe на E12 к обратному значению E13. Результат - светодиод светится зеленым светом
 } 
 return 0; 
} 
