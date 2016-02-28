#pragma config(Sensor, S1,     sensorL,        sensorLightActive)
#pragma config(Sensor, S2,     sensorF,        sensorEV3_Color)
#pragma config(Sensor, S4,     sensorD,        sensorEV3_Ultrasonic)
#pragma config(Motor,  motorA,          motorL,        tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          motorSonar,    tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorD,          motorR,        tmotorEV3_Large, PIDControl, driveRight, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

int turningPower = 20;
int turningTime = 1000; // We need to test this time
int moveTime = 2000; // The time of moving forward during turning

bool isBlack(int value){
	return value >= 14 && value <= 16;
}
bool isBlue(int value){
	return value >= 16 && value <= 18;
}
bool isRed(int value){
	return value >= 35 && value <= 39;
}
bool isWhite(int value){
	return value >= 48 && value <= 52;
}

// 1 for turn left, 2 for turn right, 3 for go straight
// 4 for turn onto a circular path, 5 for move on a circular path
int arr[] = {1, 3};

int A_ONE[3] = {1, 1, 1};
int A_THREE[11] = {1, 1, 1, 3, 3, 1, 3, 1, 3, 1, 1};
int A_FOUR[12] = {1, 1, 1, 3, 3, 1, 3, 3, 3, 1, 1, 3};
int A_SIX[9] = {1, 1, 1, 3, 3, 3, 1, 2, 3};
int A_NINE[11] = {1, 1, 1, 3, 3, 3, 3, 3, 3, 1, 3};
int ONE_THREE[9] = {1, 3, 3, 1, 3, 1, 3, 1, 1};
int ONE_FOUR[10] = {1, 3, 3, 1, 3, 3, 3, 1, 1, 3};
int ONE_SIX[7] = {1, 3, 3, 3, 1, 2, 3};
int ONE_NINE[9] = {1, 3, 3, 3, 3, 3, 3, 1, 3};
int ONE_A[10] = {1, 3, 3, 1, 3, 3, 3, 1, 3, 3};
int ONE_B[7] = {1, 3, 3, 3, 3, 3, 3};
int THREE_ONE[10] = {1, 3, 1, 3, 3, 1, 3, 3, 1, 1};
int THREE_FOUR[8] = {1, 3, 1, 3, 3, 1, 1, 3};
int THREE_SIX[5] = {1, 3, 3, 3, 3};
int THREE_NINE[9] = {1, 3, 3, 3, 3, 3, 3, 3, 1};
int THREE_A[8] = {1, 3, 1, 3, 3, 1, 3, 3};
int THREE_B[7] = {1, 2, 1, 3, 3, 3, 3};
int FOUR_ONE[11] = {1, 3, 1, 1, 3, 3, 1, 3, 3, 1, 1};
int FOUR_THREE[4] = {1, 2, 1, 1};
int FOUR_SIX[6] = {1, 3, 1, 3, 3, 3};
int FOUR_NINE[10] = {1, 3, 1, 3, 3, 3, 3, 3, 3, 1};
int FOUR_A[9] = {1, 3, 1, 1, 3, 3, 1, 3, 3};
int FOUR_B[8] = {1, 3, 3, 1, 3, 3, 3, 3};
int SIX_ONE[13] = {1, 1, 1, 3, 4, 2, 2, 3, 1, 3, 3, 1, 1};
int SIX_THREE[10] = {1, 1, 1, 3, 4, 2, 3, 3, 1, 1};
int SIX_FOUR[11] = {1, 1, 1, 3, 4, 2, 2, 3, 1, 1, 3};
int SIX_NINE[5] = {1, 3, 3, 3, 1};
int SIX_A[11] = {1, 1, 1, 3, 4, 2, 2, 3, 1, 3, 3};
int SIX_B[5] = {1, 3, 2, 1, 3};
int NINE_ONE[9] = {1, 1, 3, 3, 3, 3, 3, 1, 1};
int NINE_THREE[10] = {1, 1, 3, 3, 3, 1, 3, 2, 1, 1};
int NINE_FOUR[7] = {1, 1, 3, 3, 3, 1, 3};
int NINE_SIX[7] = {1, 1, 3, 1, 3, 3, 1};
int NINE_A[7] = {1, 1, 3, 3, 3, 3, 3};
int NINE_B[8] = {1, 1, 1, 3, 3, 3, 1, 3};
int B_ONE[11] = {1, 1, 3, 1, 3, 3, 3, 3, 3, 1, 1};
int B_THREE[12] = {1, 1, 3, 1, 3, 3, 3, 1, 3, 2, 1, 1};
int B_FOUR[9] = {1, 1, 3, 1, 3, 3, 3, 1, 3};
int B_SIX[9] = {1, 1, 3, 1, 3, 1, 3, 3, 1};
int B_NINE[3] = {1, 1, 3};

void run();
void moveForward(bool detect, bool isParking);
void turn(char a, bool isParking);
void circularForward();
void turnOntoCircular();
void parking();
task checkCollision();
task adjust();
task begin();

task main(){
	wait1Msec(100);
	startTask(begin);
	while(true){
		wait1Msec(1000);
	}
}

task begin(){
	//arr = A_ONE;
	run();
	//arr = A_ONE;
	//run();
	//arr = A_ONE;
	//run();
	//arr = A_ONE;
	//run();
}

void run(){
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
	wait1Msec(4000);
}

// 'l' for left, other for right
// return true if there is an object
bool detection(char a){
	int power = 10, angle = 70; // The final speed and angle will be about 2/3 of these values due to different radii of gears
	bool flag = false;
	if(a != 'l'){
		power = -power;
		angle = -angle;
	}
	moveMotorTarget(motorSonar, angle, power);
	waitUntilMotorStop(motorSonar);
	wait1Msec(500);
	if(SensorValue[sensorD] < 30){
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
	wait1Msec(moveTime); // wait for the robot to leave the red line
	startTask(adjust);
	if(isParking) return;
	while(!isRed(SensorValue[sensorF])){}
	motor[motorL] = 0;
	motor[motorR] = 0;
	stopTask(adjust);
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
	motor[motorL] = 20; // angle = 45 * width / radius
	motor[motorR] = 20;
	wait1Msec(moveTime); // move a distance (we need to test)

	if(a == 'l'){ // turn
		motor[motorL] = -turningPower;
		motor[motorR] = turningPower;
	} else {
		motor[motorL] = turningPower;
		motor[motorR] = -turningPower;
	}
	wait1Msec(turningTime);
	moveForward(false, isParking);
}

void circularForward(){ // The diameter of the circle is about 1/2"
	motor[motorL] = 20; // we need to test these numbers
	motor[motorR] = 40;
	wait1Msec(500); // wait for the robot to leave the red line
	startTask(adjust);
	while(!isRed(SensorValue[sensorF])){}
	motor[motorL] = 0;
	motor[motorR] = 0;
	stopTask(adjust);
}

void turnOntoCircular(){
	while(detection('l')){
		wait1Msec(2000);
	}
	motor[motorL] = 20;
	motor[motorR] = 20;
	wait1Msec(moveTime); // move a distance (we need to test)

	motor[motorL] = turningPower;
	motor[motorR] = -turningPower;
	wait1Msec(turningTime);

	circularForward();
}

bool parkingDetection(){
	bool flag = false;
	int time = 300;
	motor[motorL] = -20; // Turn left a little
	motor[motorR] = 20;
	wait1Msec(time);
	motor[motorL] = 0;
	motor[motorR] = 0;
	wait1Msec(400);
	if(SensorValue[sensorD] < 10){
		flag = true;
	}
	motor[motorL] = 20; // Turn the robot back
	motor[motorR] = -20;
	wait1Msec(time);
	motor[motorL] = 0;
	motor[motorR] = 0;
	return flag;
}

void parking(){
	//motor[motorL] = 20;
	//motor[motorR] = 20;
	while(!isBlue(SensorValue[sensorL])){}
	wait1Msec(400); // wait for the robot to go a little bit forward
	motor[motorL] = 0;
	motor[motorR] = 0;
	stopTask(checkCollision);
	stopTask(adjust);
	// Turn the sonar sensor and check objects
	// If there is a robot in the parking lot,
	// go to the next one.
	int power = 10;
	int angle = 90;
	moveMotorTarget(motorSonar, angle, power);
	waitUntilMotorStop(motorSonar);
	while(parkingDetection()){
		motor[motorL] = 20; // Move to the next parking lot
		motor[motorR] = 20;
		wait1Msec(2000); // we need to test this time
		motor[motorL] = 0;
		motor[motorR] = 0;
	}
	moveMotorTarget(motorSonar, -angle, -power); // turn the sensor back
	waitUntilMotorStop(motorSonar);
	// Assume the robot itselt is not turned by this time
	motor[motorL] = turningPower;
	motor[motorR] = -turningPower;
	wait1Msec(turningTime); // we need to test this time

	motor[motorL] = -20;
	motor[motorR] = -20;
	wait1Msec(1000);
	while(!isBlue(SensorValue[sensorF])){}
	wait1Msec(200);
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
			suspendTask(begin);
			int l = motor[motorL];
			int r = motor[motorR];
			motor[motorL] = 0;
			motor[motorR] = 0;
			wait1Msec(1000);
			motor[motorL] = l;
			motor[motorR] = r;
			startTask(begin);
		}
	}
}

task adjust(){
	while(true){
		wait1Msec(10);
		if(motor[motorL] == 0 && motor[motorR] == 0){
			continue;
		}
		if(!isWhite(SensorValue[sensorL]) && !isBlue(SensorValue[sensorL])){
			if(!isBlack(SensorValue(sensorL))){
				motor[motorL] += 2;
				wait1Msec(1000);
				motor[motorL] -= 2;
			}
			else { // (isBlack(SensorValue(SensorL)))
				motor[motorL] -= 2;
				wait1Msec(1000);
				motor[motorL] += 2;
			}
		}
	}
}