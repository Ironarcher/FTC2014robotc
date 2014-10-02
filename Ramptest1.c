#pragma config(Hubs,  S1, HTMotor,  HTServo,  none,     none)
#pragma config(Sensor, S2,     ,               sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  motorA,          motorTray,     tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C2_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)

void goForward(int duration){
	motor[motorD]=23;
	motor[motorE]=20;
	wait1Msec(duration);
	motor[motorD]=0;
	motor[motorE]=0;
	wait1Msec(50);
}

void goForwardFast(int duration){
	motor[motorD]=46;
	motor[motorE]=40;
	wait1Msec(duration);
	motor[motorD]=0;
	motor[motorE]=0;
	wait1Msec(50);
}

void goBackward(int duration){
	motor[motorD]=-23;
	motor[motorE]=-20;
	wait1Msec(duration);
	motor[motorD]=0;
	motor[motorE]=0;
	wait1Msec(50);
}

void turnClockwise(int duration){
	motor[motorD]=15;
	motor[motorE]=-15;
	wait1Msec(duration);
	motor[motorD]=0;
	motor[motorE]=0;
	wait1Msec(50);
}

void turnCounterClockwise(int duration){
	motor[motorD]=-15;
	motor[motorE]=15;
	wait1Msec(duration);
	motor[motorD]=0;
	motor[motorE]=0;
	wait1Msec(50);
}
void turnByDegreesClockwise(int degrees) {
	turnClockwise(degrees*11);
}
void turnByDegreesCounterClockwise(int degrees) {
	turnCounterClockwise(degrees*10);
}

void travelMetersFast(double meters){
	int conversion = (int)(1177 * meters);
	goForwardFast(conversion);
}

void travelMeters(double meters){
	int conversion = (int)(2353 * meters);
	goForward(conversion);
}

int getInfrared(){
	return SensorValue[S2];
}


int getTowerPosition(){
	int position;
	if(getInfrared() == 5){
		//if infrared sensor is straight ahead, position is tower position 1
		position = 1;
	} else if (getInfrared() == 6){
		position = 2;
  } else if (getInfrared() == 7){
  	position = 3;
	}

	return position;
}


void getToTower2(){
	turnByDegreesCounterClockwise(10);
	travelMetersFast(1);
}

void getToTower1(){
	turnByDegreesCounterClockwise(45);
	travelMeters(.6);
	turnByDegreesClockwise(47);
	travelMetersFast(1.2);
}

void getToTower3(){
	travelMeters(1.5); //get off the ramp
	turnByDegreesCounterClockwise(90);
	travelMeters(0.5);
	turnByDegreesCounterClockwise(45);
	travelMeters(0.4);
	turnByDegreesClockwise(45);
	travelMeters(1);
}

task main()
{
	travelMeters(1.03);
	turnByDegreesCounterClockwise(90);
	travelMeters(0.55);
	if(getTowerPosition() == 1) getToTower1();
	else if(getTowerPosition() == 2) getToTower2();
	else if(getTowerPosition() == 3) getToTower3();
	//getToTower3();
}
