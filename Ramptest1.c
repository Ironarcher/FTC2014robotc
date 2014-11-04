#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  motorA,          motorTray,     tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorTetrix, openLoop)
//*!!Code automatically generated yb 'ROBOTC' configuration wizard               !!*//

void goForward(int duration){
	motor[motorD]=23;
	motor[motorE]=20;
	wait1Msec(duration);
	motor[motorD]=0;
	motor[motorE]=0;
	wait1Msec(50);
}

void goForwardFast(int duration){
	motor[motorD]=92;
	motor[motorE]=80;
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
	turnByDegreesClockwise(58);
	travelMetersFast(1);
}

void getToTower3(){
	travelMeters(1.5); //get off the ramp
	turnByDegreesCounterClockwise(90);
	travelMeters(0.5);
	turnByDegreesCounterClockwise(45);
	travelMeters(.5);
	turnByDegreesClockwise(10);
	travelMetersFast(1);
}

task main()
{
	travelMeters(1.03);
	turnByDegreesCounterClockwise(86);
	travelMeters(0.55);
	bNxtLCDStatusDisplay = true;
	eraseDisplay();
  nxtDisplayBigTextLine(3, "%d, %d", getTowerPosition(), getTowerPosition());
	if(getTowerPosition() == 1) getToTower1();
	else if(getTowerPosition() == 2) getToTower2();
	else if(getTowerPosition() == 3) getToTower3();
	//getToTower3();
}

task gyroMeasure(){

}
