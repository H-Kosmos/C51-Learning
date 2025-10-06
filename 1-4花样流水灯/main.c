#include <REGX52.H>
#include "Delay.h"

unsigned char run = 0, mode = 0;                // run->运行标识符  mode->花样模式标识符
unsigned char P1_0State = 0, P1_1State = 0;     //P1.0,P1.1两个按钮的状态

bit Key_P1_0(void){                             //按键1的消抖函数
    if(P1_0 == 0) {
        Delay(5);
        if(P1_0 == 0) {
            while(P1_0 == 0);
            return 1;
        }
    }
    return 0;
}

bit Key_P1_1(void){                             //按键2的消抖函数
    if(P1_1 == 0) {
        Delay(5);
        if(P1_1 == 0) {
            while(P1_1 == 0);
            return 1;
        }
    }
    return 0;
}

void mode_0(){                       //花样1(流水灯)
    static unsigned char state = 0x01;      //state->LED状态,只初始化一次
    P0 = ~state;
    Delay(100);
    state <<= 1;
    if(state == 0)
        state = 0x01;
}

void mode_1(){                       //花样2(相隔的灯亮)
    static unsigned char pattern = 0x55;
    P0 = pattern;
    Delay(200);
    if(pattern == 0x55)    //0101 0101
        pattern = 0xAA;
    else                   //1010 1010
        pattern = 0x55;
}

void mode_2(){                       //花样3(双向流水灯)
    unsigned char arr[] = {0x7E, 0xBD, 0xDB, 0xE7, 0xDB, 0xBD, 0x7E};
    unsigned char i;
    for(i = 0; i <= 6; i++){
        P0 = arr[i];
        Delay(100);
    }
}

void main(){
    P0 = 0xFF;                  //上电时，让所有LED熄灭

    while(1){
        if(Key_P1_0())      //按下P1.0控制LED灯的启停
            run = !run;

        if(Key_P1_1()){    //按下P1.1控制流水灯的花样
            mode++;
            mode %= 3;          //mode到3时归零
        }

        if(run){                //LED启动
            switch(mode){
                case 0:
                    mode_0();
                    break;
                case 1:
                    mode_1();
                    break;
                case 2:
                    mode_2();
                    break;
            }
        }
        else{                   //LED停止
            P0 = 0xFF;
        }
    }
}