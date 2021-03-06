#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S2,     ,               sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S3,     HTGyro,         sensorAnalogInactive)
#pragma config(Sensor, S4,     HTIRS2,         sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  motorA,          motorTray,     tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     motorE,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorCollector, tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     motorD,        tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     motorScissor,  tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    servo1,               tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_3,    servo2,               tServoStandard)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "hitechnic-gyro.h"
#include "hitechnic-sensormux.h"
#include "hitechnic-irseeker-v2.h"
#include "JoystickDriver.c"

float total_distance = 0;
bool flag7 = true;
bool flag8 = true;
bool flag9 = true;
bool flag13 = true;
bool flag14 = true;
char path[220];
int plength = 0;
float prev_rot = 0;
void print(int s){
	NXTDisplayBigTextLine(3, "%d", s);
}
void raiseScissorLift(){
	motor[motorScissor] = 100;
	wait1Msec(2000);
	motor[motorScissor] = 0;
}

void lowerScissorLift(){
	motor[motorScissor] = -100;
	wait1Msec(2000);
	motor[motorScissor] = 0;
}

void raiseGrabber(){
	servo[servo1] = 360;
	servo[servo2] = 20;
}

void lowerGrabber(){
	servo[servo1] = 80;
	servo[servo2] = 270;
}

void releaseBallCollector(){
	motor[motorCollector] = -20;
	wait1Msec(3000);
	motor[motorCollector] = 0;
}

void addToPath(string t) {
	path[plength] = StringGetChar(t, 0);
	path[plength+1] = StringGetChar(t, 1);
	path[plength+2] = StringGetChar(t, 2);
	path[plength+3] = StringGetChar(t, 3);
	plength +=4;
}
void initializeRobot()
{
	//servo[servo1] = 0;  // Gripper opened
	nMotorPIDSpeedCtrl[motorTray] = mtrSpeedReg;
	motor[motorTray] = 0;
	return;
}
void resetEncoders(){
	nMotorEncoder[motorD] = 0;
	nMotorEncoder[motorE] = 0;
}
void turn(int direction) {
	int mul = direction;

	resetEncoders();
	//float degreesToTurn = degrees - (degrees/27);
	motor[motorD] = 15 * mul;
	motor[motorE] = -15 * mul;

	float current_rot = HTGYROreadRot(HTGyro) +14;
	float time = time1[T1];

	float distance = ((prev_rot+current_rot)/2)*time/1000;
	total_distance += distance;
	prev_rot = current_rot;
	clearTimer(T1);
	wait1Msec(10);
	motor[motorD] = 0;
	motor[motorE] = 0;
}

//Encode actions into a readable code
void finishAction(int num) {
	flag7 = true;
	flag8 = true;
	flag9 = true;
	flag13 = true;
	flag14 = true;
	clearTimer(T1);
	total_distance += total_distance/13;
	motor[motorD] = 0;
	motor[motorE] = 0;
	string chare; //Placeholder, used to store which action was taken (ie. "a")
	string chare2 = ""; //Another placeholder, records the action in 3 digits (ie. "000")
	float add; //Used for rounding/data type conversion
	int add2; //Used for rounding/data type conversion
	if(num == 1) { //LEFT
		chare = "c";
		add = round(total_distance);
		add = abs(add);
		add2 = add;
		chare2 = add2;
		if(strlen(chare2) < 3) {
			if(strlen(chare2) == 2) {
				string addon = "0"; //Used to turn "9" into "009"
				strcat(addon, chare2);
				chare2 = addon;
				} else if(strlen(chare2) == 1) {
				string addon = "00";
				strcat(addon, chare2);
				chare2 = addon;
				} else {
				chare2 = "000";
			}
		}
		strcat(chare, chare2);
		addToPath(chare); //Adds the 4 digit action to the path (ie. "c070", which is turn left 70 degrees)
		} else if(num == 3) { //RIGHT
		chare = "d";
		add = round(total_distance);
		add = abs(add);
		add2 = add;
		chare2 = add2;
		if(strlen(chare2) < 3) {
			if(strlen(chare2) == 2) {
				string addon = "0";
				strcat(addon, chare2);
				chare2 = addon;
				} else if(strlen(chare2) == 1) {
				string addon = "00";
				strcat(addon, chare2);
				chare2 = addon;
				} else {
				chare2 = "000";
			}
		}
		strcat(chare, chare2);
		addToPath(chare);
		} else if(num == 2) { //BACK
		chare = "b";
		add = nMotorEncoder[motorE]/56.33
		add = round(add);
		add = abs(add);
		add2 = add;
		chare2 = add2;
		if(strlen(chare2) < 3) {
			if(strlen(chare2) == 2) {
				string addon = "0";
				strcat(addon, chare2);
				chare2 = addon;
				} else if(strlen(chare2) == 1) {
				string addon = "00";
				strcat(addon, chare2);
				chare2 = addon;
				} else {
				chare2 = "000";
			}
		}
		strcat(chare, chare2);
		addToPath(chare);
		} else if(num == 4) { //FORWARDS
		chare = "a";
		add = nMotorEncoder[motorE]/56.33
		add = round(add);
		add = abs(add);
		add2 = add;
		chare2 = add2;
		if(strlen(chare2) < 3) {
			if(strlen(chare2) == 2) {
				string addon = "0";
				strcat(addon, chare2);
				chare2 = addon;
				} else if(strlen(chare2) == 1) {
				string addon = "00";
				strcat(addon, chare2);
				chare2 = addon;
				} else {
				chare2 = "000";
			}
		}
		strcat(chare, chare2);
		addToPath(chare);
	} else if(num == 7) { //LSCISSOR
	 	string s = "e002";
		addToPath(s);
	} else if(num == 8) { //RSCISSOR
	 	string s = "e001";
		addToPath(s);
	} else if(num == 9) { //SWEEp
	 	string s = "e005";
		addToPath(s);
	}else if(num == 13) { //RGRABBER
	 	string s = "e003";
		addToPath(s);
	} else if(num == 14) { //LGRABBER
	 	string s = "e004";
		addToPath(s);
	}
	total_distance = 0;
	prev_rot = 0;
	resetEncoders();
}
task main()
{
	initializeRobot();
	clearTimer(T1);
	bool isLaunching = false;
	bool isDropping = false;
	int mThreshold = 15;      // Sets dead zones to avoid unnecessary movement
	int aThreshold = 30;
	int xVal, yVal;           //Stores left analog stick values
	float scaleFactor = 40.0 / 127;           //Sets max. average motor power and maps range of analog stick to desired range of power

	//waitForStart();   // wait for start of tele-op phase
	int num = 0;
	while (true)
	{
		getJoystickSettings(joystick); // Retrieves data from the joystick

		//4 is forward, 2 is backwards, 7 is left, 8 is right

		if(joy1Btn(4) == 1){
			if(num == 4) {
				motor[motorD] = 20;
				motor[motorE] = 20;
				} else {
				finishAction(num);
				num = 4;
			}
			} else if (joy1Btn(2) == 1){
			if(num == 2) {
				motor[motorD] = -23;
				motor[motorE] = -23;
				} else {
				finishAction(num);
				num = 2;
			}
			} else if (joy1Btn(1) == 1){
			if(num == 1) {
				turn(1);
				} else {
				finishAction(num);
				num = 1;
			}
			}else if (joy1Btn(3) == 1){
			if(num == 3) {
				turn(-1);
				} else {
				finishAction(num);
				num = 3;
			}

			//raise scissor lift (positive motor power)
			/*
			} else if (joy1Btn(9) == 1){
				if(num == 9 && flag9) {
					flag9 = false;
					releaseBallCollector();
				//
				} else {
				finishAction(num);
				num = 9;
				}
				*/
			/*} else if (joy1Btn(6) == 1){
				if(num == 13 && flag13) {
					flag13 = false;
					raiseGrabber();
				//
				} else {
				finishAction(num);
				num = 13;
				}//raise grabber
				} else if (joy1Btn(7) == 1){
				if(num == 14 && flag14) {
					flag14 = false;
					lowerGrabber();
				//
				} else {
				finishAction(num);
				num = 14;
				}
			//lower grabber */

		}else if (joy1Btn(7) == 1){
		clearDebugStream();
		writeDebugStreamLine(path);
		stopAllTasks();
		}else{
		if(num != 0) {
			finishAction(num);
			num = 0;
		}
		//RECORD CURRENT VARIABLES, THEN RESET EVERYTHING
	}

	//Controls launcher
	//if(joy1Btn(1) == 1 && isLaunching == false){
	//isLaunching = true;
	//fireLauncher();
	//isLaunching = false;
	//}
	//wait1Msec(1);
}

}
