#include "DCMotor.h"
#include "mbed.h"
#include "QEI.h"

#define Limit 30.0
#define PI 3.14159265359


#define RESOLUTION 823//180
#define INT_TIME 0.01

Serial pc(USBTX,USBRX);
Ticker timer;
Timer T;
DCMotor dcMotorR(D9, D10);
DCMotor dcMotorL(D7,D2);



QEI Enc1(A3,D12,NC,RESOLUTION,&T,QEI::X4_ENCODING);
QEI Enc2(A1,A0,NC,RESOLUTION,&T,QEI::X4_ENCODING);


int Rev2 = 0;
double Angle2=0;
int Pulse2=0;
double rpm2=0;


float k_p = 0.001;
float k_i = 0.01;
float k_d = 0.0001;
float rev;
float goal;
float rev_back = 0.0;
float power= 0.0;
float erorr;
float erorr_back = 0.0;
float integ=0;
float deriva;

void timer_PID()
{
    
    //static float pre_sp1 = 0;
    
    /*Rev1 = Enc1.getAng_rev();
    Angle1 = Enc1.getAngle();
    Pulse1 = Enc1.getPulses
    ();
    rpm1=Enc1.getRPM();*/

    Rev2 =  -Enc2.getRevolutions();
    Angle2 = -Enc2.getSumangle();
    Pulse2 = -Enc2.getPulses();
    rpm2=-Enc2.getRPM();



    erorr = goal - Angle2;
    //integ += (erorr + erorr_back) * (1/2) * INT_TIME;
    deriva = (erorr - erorr_back) / INT_TIME;
    power = k_p * erorr + k_d * deriva;
    erorr_back = erorr;


    //encount2 = Enc2.getPulses();
    //if (encount1 > encount2) encount_rot = encount1;
   // else encount_rot = encount2;
    
    //float rot_sp1 = encount_rot/multi/ppr*pull_ratio; 
    //spd1 = (rot_sp1 - pre_sp1)/INT_TIME/(48*4);
    
        
}


void motorPID(double kakudo){
    goal=kakudo;
    pc.printf("Rev2=%d,angle2=%f,pulse2=%d,rpm2=%f,power=%f\n", Rev2,Angle2,Pulse2,rpm2,power); 

        if(erorr<2){
            dcMotorL.brake();
            dcMotorR.brake();
            wait(5);
        }  
        else if(power<0){
            if(abs(power)>1){
                power = 1;
            }
            dcMotorL.backward(power);
            dcMotorR.backward(power); 
            pc.printf("minus!,power=%f\n",power);  
        }else{
            if(power>1){
                power=1;
            }
            dcMotorL.forward(power);
            dcMotorR.forward(power);
        }

}
