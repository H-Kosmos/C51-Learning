#include <REGX52.H>
#include "Delay.h"

void main(){
    unsigned char i = 0;
    while(1){
        P0 = ~(0x01 << i);
        Delay(100);
        i++;
        i %= 8;
    }
}