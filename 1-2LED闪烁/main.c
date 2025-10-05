#include <REGX52.H>
#include "Delay.h"

sbit LED = P0^0;

void main(){
    while(1){
        LED = 0;
        Delay(1000);
        LED = 1;
        Delay(1000);
    }
}