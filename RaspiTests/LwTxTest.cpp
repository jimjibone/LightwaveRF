#include <stdio.h>
#include <wiringPi.h>
#include "../libraries/LwTx/LwTx.h"

void loop();
void turnOn();
void turnDim();
void turnOff();

uint8_t on[]  = {0x9,0xf,0x3,0x1,0x5,0x9,0x3,0x0,0x1,0x2};
uint8_t off[] = {0x4,0x0,0x3,0x0,0x5,0x9,0x3,0x0,0x1,0x2};
int time = 0;

int main(int argc, char const *argv[])
{
    printf("lwtx starting\n");
    wiringPiSetup();
    int err = piHiPri(99);

    if (err < 0)
        return err;

    //Transmit on pin 3, 10 repeats,no invert, 140uSec tick)
    lwtx_setup(3, 10, 0, 140);

    while (1) {
        loop();
    }

    return 0;
}

void loop() {

    printf("time: %d", (time * 5));

    if (time % 3 == 0) turnOn();
    else if (time % 2 == 0) turnDim();
    else turnOff();

    lw_timer_exec();

    time++;

    delay(2000); // 5 secs
}

void turnOn() {
    printf("\tturning on\n");
    // lwtx_sendCmd(0x80 + 31,     // level
    //              6,             // byte channel
    //              Lightwave_On,  // byte command
    //              id);           // byte* id
    lwtx_send(on);
}

void turnDim() {
    printf("\tNOT turning dim\n");
    // lwtx_sendCmdDim(12,     // dim value
    //                 6,      // byte channel
    //                 id);    // byte* id
}

void turnOff() {
    printf("\tturning off\n");
    //lwtx_sendMsg(off);
    lwtx_send(off);
}
