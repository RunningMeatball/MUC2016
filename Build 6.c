#pragma config(Sensor, S1,     SensorL,        sensorColorNxtFULL)
#pragma config(Sensor, S2,     SensorM,        sensorColorNxtFULL)
#pragma config(Sensor, S3,     SensorR,        sensorColorNxtFULL)
#pragma config(Sensor, S4,     SensorSonar,    sensorSONAR)
#pragma config(Motor,  motorA,          motorL,        tmotorNXT, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorB,          motorR,        tmotorNXT, PIDControl, driveRight, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//sensor reading estimation
int whiteA()
{
	return SensorValue(SensorL) % 70;
}
int whiteC()
{
	return SensorValue(SensorR) % 70;
}
int redB()
{
	return SensorValue(SensorM) % 55;
}
int blackA()
{
	return SensorValue(SensorL);	//Need a formula for estimation
}
int blackC()
{
	return SensorValue(SensorR);
}
bool sensorOff = false;


//Movement Parts

task moveForward()
{
	while(redB() <= 10){
		if (whiteA() <=10 && whiteC() <=10)	//Might become a rough estimation around a certain range
		{
			moveMotorTarget(motorL,360,50);
		  moveMotorTarget(motorR,360,50);
		}
		else if (whiteA() >= 10 && blackA() == 7)			//This section needs revist, possible backing up before adjusting
		{
		 	moveMotorTarget(motorL,2,25);
		 	motor[motorR] = 0;
		}
		else (whiteC() >=10 && blackC() == 7);			// So is this
		{
		 	motor[motorL] = 0;
		 	moveMotorTarget(motorR,3,25);
		}
	}
}

	//Forward Circular Path 1
task moveForwardLoop ()
{
	while(redB() <= 10){
		if (whiteA() <=10 && whiteC() <=10)
		{
			moveMotorTarget(motorL,360,50);		//Distance requires offset for turning
			moveMotorTarget(motorR,360,50);
		}
		else if (whiteA() >= 10 && blackA() == 7)			//This section needs revist, possible backing up before adjusting
		{
		 	moveMotorTarget(motorL,2,25);
		 	motor[motorR] = 0;
		}
		else (whiteC() >= 10 && blackC() == 7);			// So is this
		{
		 	motor[motorL] = 0;
		 	moveMotorTarget(motorR,3,25);
		}
	}
}

	//Forward Circular Path 2
task moveForwardSemi ()
{
	while(redB() <= 10){
		if (whiteA() <=10 && whiteC() <=10)
		{
			moveMotorTarget(motorL,360,50);		//Distance requires offset for turning
			moveMotorTarget(motorR,360,50);
		}
		else if (whiteA() >= 10 && blackA() == 7)			//This section needs revist, possible backing up before adjusting
		{
		 	moveMotorTarget(motorL,2,25);
		 	motor[motorR] = 0;
		}
		else (whiteC() >= 10 && blackC() == 7);			// So is this
		{
		 	motor[motorL] = 0;
		 	moveMotorTarget(motorR,3,25);
		}
	}
}

task leftTurn() //Distance require calculation
{
	moveMotorTarget(motorL,30,25);
	moveMotorTarget(motorR,90,25);
}

task rightTurn() //Distance require calculation
{
	moveMotorTarget(motorL,90,25);
	moveMotorTarget(motorR,60,25);
}


			//Distance sensing module
task sensor()
{
	if (sensorOff == false)
	{
		while (SensorValue(SensorSonar) <= 20) //possible change in distance
			{
				suspendTask(leftTurn);
				suspendTask(rightTurn);
				suspendTask(moveForwardLoop);
				suspendTask(moveForwardSemi);
				suspendTask(moveForward);	//Add more along the way
				sensorOff = true;
			}
	}
	else
	{
	startTask (sensor);
	sensorOff = false;
	}
}


task main()
{
	startTask (moveForward);			//Input "startTask();"
	startTask (moveForwardLoop);
	startTask (leftTurn);
	startTask (rightTurn);
	startTask (moveForwardSemi);
	startTask (sensor);
}
