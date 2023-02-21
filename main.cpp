#include "mbed.h"
#include "QEI.h"
#include "DCMotor.h"

#define RESOLUTION 310//なぜかこの値がちょうどいい
#define INT_TIME 0.05//クロックのスパン


DCMotor dcMotorR(D9, D10);
DCMotor dcMotorL(D7,D2);


Ticker timer;
Timer T;

QEI Enc1(A3,D12,NC,RESOLUTION,&T,QEI::X4_ENCODING);
QEI Enc2(A1,A0,NC,RESOLUTION,&T,QEI::X4_ENCODING);
Serial pc(USBTX,USBRX);

int encountRev1 = 0;
double encountAngle1=0;
int encountPulse1=0;

int encountRev2 = 0;
double encountAngle2=0;
int encountPulse2=0;



void timer_warikomi()
{
    
    //static float pre_sp1 = 0;
    
    encountRev1 = Enc1.getAng_rev();//回転数
    encountAngle1 = Enc1.getAngle();//回転角度
    encountPulse1 = Enc1.getPulses();//合計パルス

    encountRev2 = Enc2.getAng_rev();
    encountAngle2 = Enc2.getAngle();
    encountPulse2 = Enc2.getPulses();
    //encount2 = Enc2.getPulses();
    //if (encount1 > encount2) encount_rot = encount1;
   // else encount_rot = encount2;
    
    //float rot_sp1 = encount_rot/multi/ppr*pull_ratio; 
    //spd1 = (rot_sp1 - pre_sp1)/INT_TIME/(48*4);
    pc.printf("rev1=%d,angle1=%f,pulse1=%d  Rev2=%d,angle2=%f,pulse2=%d \n", encountRev1,encountAngle1,encountPulse1,encountRev2,encountAngle2,encountPulse2);
        
}

int main() {
    //Saber.baud(115200);
    pc.baud(115200);
    timer.attach(&timer_warikomi,INT_TIME);
    
    while(1) {  
        // 正転
        dcMotorL.forward(1);
        dcMotorR.forward(1);
        wait(5);    
        
    }
}


