#pragma config(Hubs,  S1, HTMotor,  HTServo,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C2_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

void goForward(int duration){
	motor[motorD]=20;
	motor[motorE]=21;
	wait1Msec(duration);
	motor[motorD]=0;
	motor[motorE]=0;
	wait1Msec(200);
}

void goBackward(int duration){
	motor[motorD]=-20;
	motor[motorE]=-20;
	wait1Msec(duration);
	motor[motorD]=0;
	motor[motorE]=0;
	wait1Msec(200);
}

void turnClockwise(int duration){
	motor[motorD]=15;
	motor[motorE]=-15;
	wait1Msec(duration);
	motor[motorD]=0;
	motor[motorE]=0;
	wait1Msec(200);
}

void turnCounterClockwise(int duration){
	motor[motorD]=-15;
	motor[motorE]=15;
	wait1Msec(duration);
	motor[motorD]=0;
	motor[motorE]=0;
	wait1Msec(200);
}
void turnByDegreesClockwise(int degrees) {
	turnClockwise(degrees*11);
}
void turnByDegreesCounterClockwise(int degrees) {
	turnCounterClockwise(degrees*11);
}

void travelMeters(double meters){
	int conversion = (int)(2353 * meters);
	goForward(conversion);
}


//ratio of 1m to seconds:
//990 : 90 degree turn
task main()
{
	travelMeters(1);
	//turnCounterClockwise(990);
	turnByDegreesCounterClockwise(90);
	travelMeters(2.2);
	turnByDegreesClockwise(90);
	travelMeters(2.6);
	turnByDegreesClockwise(92);
	travelMeters(2.4);
	turnByDegreesClockwise(90);
	travelMeters(3);
	//goBackward(2000);

	/*
  //go forward for 2 seconds
  motor[motorD]=15;
  motor[motorE]=15;
  wait1Msec(2000);

  //stop for 1 second
  motor[motorD]=0;
  motor[motorE]=0;
  wait1Msec(1000);

  //turn around
  motor[motorD]=-15;
  motor[motorE]=15;
  wait1Msec(1000);

  //stop for 1 second
  motor[motorD] = 0;
  motor[motorE] = 0;
  wait1Msec(1000);

  //go forward for 2 seconds
  motor[motorD]=15;
  motor[motorE]=15;
  wait1Msec(2000);

  //stop
  motor[motorD] = 0;
  motor[motorE] = 0;
  */
}
