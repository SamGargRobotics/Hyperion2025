#pragma config(Sensor, S2,     irFront,         sensorI2CCustom)
#pragma config(Sensor, S1,     irBack,        sensorI2CCustom)
#pragma config(Sensor, S3,     compass,        sensorEV3_GenericI2C)
#pragma config(Motor,  motorA,          frontleft,     tmotorEV3_Medium, openLoop, encoder)
#pragma config(Motor,  motorB,          frontright,    tmotorEV3_Medium, openLoop, encoder)
#pragma config(Motor,  motorC,          backright,      tmotorEV3_Medium, openLoop, reversed, encoder)
#pragma config(Motor,  motorD,          backleft,     tmotorEV3_Medium, openLoop, reversed, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "hitechnic-irseeker-v2.h"
#include "PF_Motors.c"

int irFrontDir, irFrontStr;
int irBackDir, irBackStr;

tHTIRS2 irSeeker1;
tHTIRS2 irSeeker2;

int comp;
int minus = SensorValue(S3);
int speed = 100;

bool compcorrection(){
	comp = SensorValue(S3) - minus;
	if(comp < 0){
		comp = 180 + comp;
	}
	if(comp < 5 || comp > 175){
		return true;
	}
	else if(comp > 90){
		motorIn.structure.A = -1*(comp-180);
		motorIn.structure.B= -(comp-180);
		motorIn.structure.C=(comp-180);
		motorIn.structure.D=(comp-180);
	}
	else{
		motorIn.structure.A=-comp;
		motorIn.structure.B=-comp;
		motorIn.structure.C=comp;
		motorIn.structure.D=comp;
	}
	return false;
}

void front(){
	motorIn.structure.A=speed;
	motorIn.structure.B=speed;
	motorIn.structure.C=speed;
	motorIn.structure.D=speed;
}

void back(){
	motorIn.structure.A=-speed;
	motorIn.structure.B=-speed;
	motorIn.structure.C=-speed;
	motorIn.structure.D=-speed;
}

void left(){
	motorIn.structure.A=-speed;
	motorIn.structure.B=speed;
	motorIn.structure.C=-speed;
	motorIn.structure.D=speed;
}

void right(){
	motorIn.structure.A=speed;
	motorIn.structure.B=-speed;
	motorIn.structure.C=speed;
	motorIn.structure.D=-speed;
}

void leftfront(){
	motorIn.structure.A=0;
	motorIn.structure.B=speed;
	motorIn.structure.C=0;
	motorIn.structure.D=speed;
}

void rightfront(){
	motorIn.structure.A=speed;
	motorIn.structure.B=0;
	motorIn.structure.C=speed;
	motorIn.structure.D=0;
}

void leftback(){
	motorIn.structure.A=-speed;
	motorIn.structure.B=0;
	motorIn.structure.C=-speed;
	motorIn.structure.D=0;
}
void still() {
	motorIn.structure.A=0;
	motorIn.structure.B=0;
	motorIn.structure.C=0;
	motorIn.structure.D=0;
}
void rightback(){
	motorIn.structure.A=speed;
	motorIn.structure.B=0;
	motorIn.structure.C=speed;
	motorIn.structure.D=0;
}

void goalie(){
	irFrontDir = irSeeker1.acDirection;
	irFrontStr = irSeeker1.enhStrength;
	irBackDir = irSeeker2.acDirection;
	irBackStr = irSeeker2.enhStrength;
	if(SensorValue(S2)<10){
		front();
	}
	else if(SensorValue(S1)>30){
		left();
	}
	else if(SensorValue(S1)<25){
		right();
	}
	else if(SensorValue(S2)>15){
		back();
	}
	else if(irFrontStr < 20){
		motorIn.structure.A=0;
		motorIn.structure.B=0;
		motorIn.structure.C=0;
		motorIn.structure.D=0;
	}
	if(irFrontStr >= irBackStr) {
		switch(irFrontDir) {
		case 1:
			leftfront();
			break;
		case 2:
			leftfront();
			break;

		case 3:
			leftfront();
			break;

		case 4:
			front();
			break;

		case 5:
			front();
			break;

		case 6:
			front();
			break;
		case 7:
			rightfront();
			break;
		case 8:
			right();
			break;
		case 9:
			right();
			break;
		default:
			still();
			break;
		}
	}
	else
	{
		switch(irBackDir) {
		case 1:
			right();
			break;
		case 2:
			rightback();
			break;
		case 3:
			rightback();
			break;
		case 4:
			back();
			break;
		case 5:
			back();
			break;
		case 6:
			back();
			break;
		case 7:
			leftback();
			break;
		case 8:
			leftback();
			break;
		case 9:
			left();
			break;
		default:
			still();
			break;
		}
	}
}



task main {
	initPFMotors();
	startMotorTask();
	initSensor(&irSeeker1, irBack);
	initSensor(&irSeeker2, irFront);
	while(true){
		readSensor(&irSeeker1);
		readSensor(&irSeeker2);
		int ir1 = SensorValue[S1];
		writeDebugStream("irvalue %4d/n", ir1);
		irFrontDir = irSeeker1.acDirection;
		irFrontStr = irSeeker1.enhStrength;
		irBackDir = irSeeker2.acDirection;
		irBackStr = irSeeker2.enhStrength;
			if(SensorValue(S2)<10){
		 	front();
			}
			if(SensorValue(S1)>30){
				left();
			}
			else if(SensorValue(S1)<25){
				right();
			}
			else if(SensorValue(S2)>15){
				back();
			}
			else if(irFrontStr < 20){
				motorIn.structure.A=0;
				motorIn.structure.B=0;
				motorIn.structure.C=0;
				motorIn.structure.D=0;
			}
		if(irFrontStr >= irBackStr) {
			switch(irFrontDir) {
			case 1:
				leftfront();
				break;

			case 2:
				leftfront();
				break;

			case 3:
				leftfront();
				break;

			case 4:
				front();
				break;

			case 5:
				front();
				break;

			case 6:
				front();
				break;

			case 7:
				rightfront();
				break;

			case 8:
				right();
				break;

			case 9:
				right();
				break;
			default:
				still();
				break;
			}
		}
		else
		{
			switch(irBackDir) {
			case 1:
				right();
				break;
			case 2:
				rightback();
				break;
			case 3:
				rightback();
				break;
			case 4:
				back();
				break;
			case 5:
				back();
				break;
			case 6:
				back();
				break;
			case 7:
				leftback();
				break;
			case 8:
				leftback();
				break;
			case 9:
				left();
				break;
			}
		}
	}
}
