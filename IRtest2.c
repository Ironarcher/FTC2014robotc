#pragma config(Hubs,  S1, HTMotor,  HTServo,  none,     none)
#pragma config(Sensor, S2,     ,               sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorNormal, openLoop)
#pragma config(Servo,  srvo_S1_C2_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//#include "hitechnic-sensormux.h"

int getIrReading(tSensors irReceiverPin)
{
  // IRLED 38 kHz for at least 2 ms
  wait1Msec(1);                              // Wait 1 ms
  int ir = SensorValue[irReceiverPin];      // IR receiver -> ir variable
  wait1Msec(1);                              // Down time before recheck
  return ir;
}

task main()
{
  while (true)
  {
    if (getIrReading(leftIR) == 0 || getIrReading(rightIR) == 0) {
      //there is something within the threshold range
      motor[leftServo] = -15;
      motor[rightServo] = 15;
      wait1Msec(400);
    } else {
      //nothing in the threshold range
      motor[leftServo] = 15;
      motor[rightServo] = 15;
    }
  }
}
