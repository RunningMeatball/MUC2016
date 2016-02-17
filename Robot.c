#pragma config(Sensor, S1,     sensorL,        sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S2,     sensorF,        sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S3,     sensorR,        sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S4,     sensorD,        sensorEV3_Ultrasonic)
#pragma config(Motor,  motorA,          motorL,        tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorB,          motorR,        tmotorEV3_Large, PIDControl, driveRight, encoder)
#pragma config(Motor,  motorC,          motorSonar,    tmotorEV3_Medium, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// 0 is no color, 1 is black, 2 is blue, 3 is green,
// 4 is yellow, 5 is red, 6 is white, and 7 is brown

// 1 for turn left, 2 for turn right, 3 for go straight
// 4 for turn onto a circular path, 5 for move on a circular path
int arr[8] = {3, 1, 3, 4, 5, 2, 1, 3};

void moveForward(bool detect, bool isParking);
void turn(char a, bool isParking);
void circularForward();
void turnOntoCircular();
void parking();
task checkCollision();

task main(){
	wait1Msec(100);

	startTask(checkCollision);
	int index;
	int length = sizeof(arr) / 2; //divide by 2 for int, divide by 20 for string
	for(index = 0; index < length - 1; index++){
		int a = arr[index];
		switch(a){
			case 1:
				turn('l', false);
				break;
			case 2:
				turn('r', false);
				break;
			case 3:
				moveForward(true, false);
				break;
			case 4:
				turnOntoCircular();
				break;
			case 5:
				circularForward();
				break;
		}
	}
	// Last turn and then park
	int b = arr[length - 1];
	switch(b){
		case 1:
			turn('l', true);
			break;
		case 2:
			turn('r', true);
			break;
		case 3:
			moveForward(true, true);
			break;
	}
	parking();
}

// 'l' for left, other for right
// return true if there is an object
bool detection(char a){
	int power = 10, angle = 20; // The final speed and angle will be about 2/3 of these values due to different radii of gears
	bool flag = false;
	if(a != 'l'){
		power = -power;
		angle = -angle;
	}
	moveMotorTarget(motorSonar, angle, power);
	waitUntilMotorStop(motorSonar);
	if(SensorValue[sensorD] < 20){
		flag = true;
	}
	moveMotorTarget(motorSonar, -angle, -power); // turn the sensor back
	waitUntilMotorStop(motorSonar);
	return flag;
}

// put false to skip object detection
void moveForward(bool detect, bool isParking){
	if(detect){
		while(detection('l') || detection('r')){
			wait1Msec(2000);
		}
	}
	motor[motorL] = 20;
	motor[motorR] = 20;
	wait1Msec(500); // wait for the robot to leave the red line

	if(isParking) return;

	while(SensorValue[sensorF] != 5){} // while it is not red
	motor[motorL] = 0;
	motor[motorR] = 0;
}

// 'l' for left, other for right
void turn(char a, bool isParking){
	if(a == 'l'){
		while(detection('r')){
			wait1Msec(2000);
		}
	} else {
		while(detection('l')){
			wait1Msec(2000);
		}
	}
	motor[motorL] = 10; // angle = 45 * width / radius
	motor[motorR] = 10;
	wait1Msec(500); // move a distance (we need to test)

	if(a == 'l'){ // turn
		motor[motorL] = -20;
		motor[motorR] = 20;
	} else {
		motor[motorL] = 20;
		motor[motorR] = -20;
	}
	wait1Msec(500); // we need to test this time

	moveForward(false, isParking);
}

void circularForward(){ // The diameter of the circle is about 1/2"
	motor[motorL] = 20; // we need to test these numbers
	motor[motorR] = 30;
	wait1Msec(500); // wait for the robot to leave the red line

	while(SensorValue[sensorF] != 5){} // while it is not red
	motor[motorL] = 0;
	motor[motorR] = 0;
}

void turnOntoCircular(){
	while(detection('l')){
		wait1Msec(2000);
	}

	motor[motorL] = 10;
	motor[motorR] = 10;
	wait1Msec(500); // move a distance (we need to test)

	motor[motorL] = 20;
	motor[motorR] = -20;
	wait1Msec(500); // we need to test this time

	circularForward();
}

// return 0 if blue is not found, 1 if blue is left, 2 if blue is right
int whereIsBlue(){
	if(SensorValue[sensorL] == 2)
		return 1;
	else if(SensorValue[sensorR] == 2) // may have some issue with parking lot 9 and 10
		return 2;
	else return 0;
}

void parking(){
	int a = 0;
	while(a == 0){
		wait1Msec(10);
		a = whereIsBlue();
	}
	wait1Msec(200); // wait for the robot to go a little bit forward
	motor[motorL] = 0;
	motor[motorR] = 0;
	stopTask(checkCollision);

	// Turn the sonar sensor and check objects
	// If there is a robot in the parking lot,
	// go to the next one.
	int power, angle;
	if(a == 1){
		power = 10;
		angle = 90;
	} else {
		power = -10;
		angle = -90;
	}
	moveMotorTarget(motorSonar, angle, power);
	waitUntilMotorStop(motorSonar);
	while(SensorValue[sensorD] < 10){
		motor[motorL] = 20;
		motor[motorR] = 20;
		wait1Msec(500); // we need to test this time
		motor[motorL] = 0;
		motor[motorR] = 0;
	}
	setMotorTarget(motorSonar, -angle, -power); // turn the sensor back

	// Assume the robot itselt is not turned by this time
	if(a == 1){
		motor[motorL] = 20;
		motor[motorR] = -20;
	} else {
		motor[motorL] = -20;
		motor[motorR] = 20;
	}
	wait1Msec(500); // we need to test this time

	motor[motorL] = -20;
	motor[motorR] = -20;
	wait1Msec(500);
	while(SensorValue[sensorF] != 2){} // while the front is not blue
	motor[motorL] = 0;
	motor[motorR] = 0;
}

task checkCollision(){
	while(true){
		wait1Msec(10);
		if(motor[motorL] == 0 && motor[motorR] == 0){
			continue;
		}

		if(SensorValue[sensorD] < 10){
			suspendTask(main);
			int l = motor[motorL];
			int r = motor[motorR];
			motor[motorL] = 0;
			motor[motorR] = 0;
			wait1Msec(1000);
			motor[motorL] = l;
			motor[motorR] = r;
			startTask(main);
		}
	}
}
