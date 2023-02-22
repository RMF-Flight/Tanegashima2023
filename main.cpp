#include "mbed.h"

#include "DCMotor.h"
#include "PID.h"



/*int Rev1 = 0;
double Angle1=0;
int Pulse1=0;
double rpm1=0;*/

int main() {
    //Saber.baud(115200);
    pc.baud(115200);
    timer.attach(&timer_PID,INT_TIME);
    
    while(1) {  
        motorPID(360);         
    }
}



