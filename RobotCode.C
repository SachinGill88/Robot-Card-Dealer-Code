void configureAllSensors()
{
	SensorType[S1] = sensorEV3_Touch;
	SensorType[S2] = sensorEV3_Ultrasonic;
	SensorType[S3] = sensorEV3_Color;
	wait1Msec(50);
	SensorMode[S3] = modeEV3Color_Color;
	wait1Msec(50);
	SensorType[S4] = sensorEV3_Gyro;
	wait1Msec(50);
	SensorMode[S4] = modeEV3Gyro_Calibration;
	wait1Msec(100);
	SensorMode[S4] = modeEV3Gyro_RateAndAngle;
	wait1Msec(50);
}

task EmergencyStop()
{
	while(SensorValue[S1]!=1)
	{}
	stopAllTasks();
}

void drive(int motor_power)//powers both drive motors with the same power
{
	motor[motorA] = motor[motorD] = motor_power;
}

void driveall(int motor_power_A, int motor_power_D, int motor_power_c)//powers both motors independently
{
	motor[motorA] = motor_power_A;
	motor[motorD] = motor_power_D;
	motor[motorC] = motor_power_c;
}

void Test_Function()
{
	while(!getButtonPress(buttonEnter))
	{}
	drive(30);
	wait1Msec(2000);
	drive(0);
	wait1Msec(1000);
	drive(-30);
	wait1Msec(2000);
	drive(0);

	resetGyro(S4);
	driveall(-20,20,0);
	while (abs(getGyroDegrees(S4))<360)
	{}
	drive(0);
	resetGyro(S4);
}

int Number_of_players()
{
	int pressCount = 0;
	while(!getButtonPress(buttonEnter))
	{
		displayBigTextLine(2,"Enter # of ");
		displayBigTextLine(6,"players: %d",pressCount);
		if(getButtonPress(buttonRight))
		{
			pressCount+=1;

			wait1Msec(5);
			while(getButtonPress(buttonRight))
			{	}
		}
		if(getButtonPress(buttonLeft))
		{
			pressCount-=1;

			wait1Msec(5);
			while(getButtonPress(buttonLeft))
			{	}
		}
	}
	return pressCount;
}

int input_error()
{
	int player_count = 0;

	while(player_count < 1 || player_count > 12)
	{
		eraseDisplay();
		player_count = Number_of_players();

		wait1Msec(500);
		eraseDisplay();

		if(player_count < 1 || player_count > 12)
		{
			displayBigTextLine(2,"invalid input");
			wait1Msec(3000);
			eraseDisplay();
		}
	}

	return player_count;
}

int Number_of_cards()
{
	int pressCount = 0;
	while(!getButtonPress(buttonEnter))
	{
		displayBigTextLine(2,"Enter # of");
		displayBigTextLine(6, "cards: %d",pressCount);
		if(getButtonPress(buttonRight))
		{
			pressCount+=1;

			wait1Msec(5);
			while(getButtonPress(buttonRight))
			{	}
		}
		if(getButtonPress(buttonLeft))
		{
			pressCount-=1;

			wait1Msec(5);
			while(getButtonPress(buttonLeft))
			{	}
		}
	}
	return pressCount;
}
int cards_error(int players)
{
	int cards_count = 0;

	while(cards_count < 1 || cards_count*players > 52)
	{
		eraseDisplay();
		cards_count = Number_of_cards();

		wait1Msec(500);
		eraseDisplay();

		if(cards_count < 1 || cards_count*players > 52)
		{
			displayBigTextLine(2,"invalid input");
			wait1Msec(3000);
			eraseDisplay();
		}
	}

	return cards_count;
}


float drive_to_colour(int colour)
{
	nMotorEncoder(motorA)=0;
	float distance = 0;
	drive(30);

	while(SensorValue[S3] != colour)
	{}

	drive(0);
	distance = nMotorEncoder(motorA);
	nMotorEncoder(motorA) = 0;
	return distance;

}

float angle_to_rotate(int players)
{
	return 360.0/players;
}

void rotatedealer(int players)
{
	float angle = angle_to_rotate(players);
	resetGyro(S4);
	driveall(-30,30,0);
	while (abs(getGyroDegrees(S4))<abs(angle))
	{}
	drive(0);
}

void dispense_cards(int players)
{
	for(int count = 1; count<=players; count++)
	{
		driveall(0,0,-18);
		wait1Msec(340);
		driveall(0,0,15);
		wait1Msec(800);
		rotatedealer(players);
		wait1Msec(2000);
	}
}

int RemainderDispense(int players, int cards)
{
	nMotorEncoder(motorA)=0;
	int remainder = 52-players*cards;
	int count = 0;
	while(count<(players*cards))
	{
		dispense_cards(players);
		count+=players;
	}

	return remainder;

}

void Exit_Code (int players, float distance, int remainder )

{
	int time = 300*remainder;

	if (players %2 == 0) //means even number of players
	{

		rotatedealer(players*2);

		wait1Msec(500);

		nMotorEncoder(motorA) = 0;
		drive (-25);
		while (abs(nMotorEncoder[motorA])<distance)
		{}
		drive (0);
		wait1Msec (500);
		driveall (0,0,-15);
		wait1Msec(time);
		driveall (0,0,0);


		displayBigTextLine(2, "%d cards were dealt", 52-remainder);

		wait1Msec(10000);
	}

	else
	{

		nMotorEncoder(motorA) = 0;
		drive (-25);
		while (abs(nMotorEncoder[motorA])<distance)
		{}
		drive (0);
		wait1Msec (500);
		driveall (0,0,-15);
		wait1Msec(time);
		driveall (0,0,0);


		displayString(2, "%d cards were dealt", 52-remainder);
		wait1Msec(10000);
	}

	eraseDisplay();
	stopAllTasks();


}





task main()
{
	startTask(EmergencyStop);
	configureAllSensors();

	Test_Function();

	int player_count = input_error();
	wait1Msec(1000);
	int cards_count = cards_error(player_count);

	wait1Msec(1000);

	float radius = drive_to_colour((int)colorRed);
	wait1Msec(2000);

	int remainder = RemainderDispense(player_count,cards_count);
	eraseDisplay();

	Exit_Code(player_count,radius,remainder);






}



