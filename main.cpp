#include "mbed.h"
#include "QEI.h"
#include "DCMotor.h"

#define RESOLUTION 100
#define INT_TIME 0.005


DCMotor dcMotorR(D9, D10);
DCMotor dcMotorL(D7,D2);


Ticker timer;
Timer T;

QEI Enc1(D12,A3,NC,RESOLUTION,&T,QEI::X4_ENCODING);
//QEI Enc2(p5,p6,NC,RESOLUTION,&T,QEI::X4_ENCODING);
Serial pc(USBTX,USBRX);

int encountRev = 0;
double encountAngle=0;
int encountPulse=0;


float spd1 = 0;

void timer_warikomi()
{
    
    //static float pre_sp1 = 0;
    
    encountRev = Enc1.getAng_rev();
    encountAngle = Enc1.getAngle();
    encountPulse = Enc1.getPulses();
    //encount2 = Enc2.getPulses();
    //if (encount1 > encount2) encount_rot = encount1;
   // else encount_rot = encount2;
    
    //float rot_sp1 = encount_rot/multi/ppr*pull_ratio; 
    //spd1 = (rot_sp1 - pre_sp1)/INT_TIME/(48*4);
    pc.printf("rev=%d,angle=%f,pulse=%d\n", encountRev,encountAngle,encountPulse);
        
}

int main() {
    //Saber.baud(115200);
    pc.baud(115200);
    timer.attach(&timer_warikomi,INT_TIME);
    
    while(1) {  
        // 正転
        dcMotorL.forward(0.5);
        dcMotorR.forward(0.5);
        wait(5);    
    }
}
