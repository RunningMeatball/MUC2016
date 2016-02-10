#pragma config(Sensor, S1,     colorSensorA,   sensorColorNxtFULL)
#pragma config(Sensor, S2,     colorSensorB,   sensorNone)
#pragma config(Sensor, S3,     sonarSensor,    sensorSONAR)
#pragma config(Motor,  motorA,          motorL,        tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          motorR,        tmotorNXT, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// void leftparking()// did all this assuming motorA is left, motorB is right, colorSensorA is left, colorSensorB is right
task sonarFunction()
	{
		while(true)
		{
			setMotorTarget(motorC, 90, 50);
			waitUntilMotorStop(motorC);
			setMotorTarget(motorC, -90, -50);
			waitUntilMotorStop(motorC);
			motor[motorC] = 0;
		}

	}
task leftparking()
	{
		if (SensorValue(sonarSensor) <= 75)
			{
				motor[motorL] = 75;                                          // lego group x*y x=diamter, y=width
				motor[motorR] = 75;
		 	}
		else
			{
				motor[motorL] = 0;
				motor[motorR] = 90;
				wait1Msec(100);
				setMotorTarget(motorL, 2122, 75);
				setMotorTarget(motorR, 2122, 75);
				waitUntilMotorStop(motorR);
				motor[motorL] = 0;
				motor[motorR] = 0;
			}
	}
task rightparking()
	{
		if(SensorValue(sonarSensor) <= 75)
			{
				motor[motorL] = 75; // lego group x*y x=diamter, y=width
				motor[motorR] = 75;
		 	}
		else
			{
				motor[motorL] = 90;
				motor[motorR] = 0;
				wait1Msec(100);
				setMotorTarget(motorL, 2122, 75);
				setMotorTarget(motorR, 2122, 75);
				waitUntilMotorStop(motorR);
				motor[motorL] = 0;
				motor[motorR] = 0;
			}
	}
task main()
	{
		startTask (sonarFunction);
		if (SensorValue(colorSensorA)>60 && SensorValue(colorSensorA) <65) // Don't know what color blue is. 60 I think?
		{
			motor[motorL] = 0;
			motor[motorR] = 0;
			startTask (leftparking);
		}
		else if (SensorValue(colorSensorB) > 55 && SensorValue(colorSensorB) <65)
		{
			motor[motorL] = 0;
			motor[motorR] = 0;
			startTask (rightparking);
		}
		else
		{
			motor[motorL] = 75; // I don't know normal speed of robot
			motor[motorR] = 75;
		}
	}
