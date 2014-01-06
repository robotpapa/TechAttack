// common.c

const int SERVO_POW_STOP = 128;
const int SERVO_POW_CW = 255;
const int SERVO_POW_CCW = 0;

const int LIFT_POW_STOP = 128;
const int LIFT_POW_UP = 255;
const int LIFT_POW_DOWN = 0;

const int SCOOP_POW_STOP = 0;
const int SCOOP_POW_IN = 100;
const int SCOOP_POW_OUT = -100;

const int MOTOR_POW_FORWARD = 100;
const int MOTOR_POW_BACKWARD = -100;

void blip() {
	PlaySound(soundBlip);
	Sleep(1000);
}

bool isLiftUp() {
	return joy2Btn(8) == 1;
}

bool isLiftDown() {
	return joy2Btn(7) == 1;
}

bool isScoopIn() {
	return joy2Btn(6) == 1;
}

bool isScoopOut() {
	return joy2Btn(5) == 1;
}

void liftUp() {
	servo[barA] = LIFT_POW_UP;
	servo[barB] = LIFT_POW_DOWN;
}

void liftDown() {
	servo[barA] = LIFT_POW_DOWN;
	servo[barB] = LIFT_POW_UP;
}

void liftStop() {
	servo[barA] = LIFT_POW_STOP;
	servo[barB] = LIFT_POW_STOP;
}

void scoopIn() {
	motor[motorA] = SCOOP_POW_OUT;
	motor[motorB] = SCOOP_POW_IN;
}

void scoopOut() {
	motor[motorA] = SCOOP_POW_IN;
	motor[motorB] = SCOOP_POW_OUT;
}

void scoopStop() {
	motor[motorA] = SCOOP_POW_STOP;
	motor[motorB] = SCOOP_POW_STOP;
}

void frontBrushIn() {
	servo[FrontBrush] = SERVO_POW_CW;
}

void frontBrushOut() {
	servo[FrontBrush] = SERVO_POW_CCW;
}

void frontBrushStop() {
	servo[FrontBrush] = SERVO_POW_STOP;
	servoTarget[FrontBrush] = 0;
}

void frontBrushControl() {
	if (joy2Btn(2) == 1) {
		// button "A" sucks cubes in
		frontBrushIn();
		PlaySound(soundLowBuzzShort);
	} else if (joy2Btn(4) == 1) {
		// button "Y" spits cubes out
		frontBrushOut();
		PlaySound(soundShortBlip);
	} else {
		// stop brush
		frontBrushStop();
	}
}

void liftControl() {
	if (isLiftUp())
	{
		liftUp();
		PlaySound(soundUpwardTones);
	}
	else if (isLiftDown())
	{
		liftDown();
		PlaySound(soundDownwardTones);
	}
	else
	{
		liftStop();
		ClearSounds();
	}
}

void scoopControl() {
	if (isScoopIn())
	{
		scoopIn();
	}
	else if (isScoopOut())
	{
		scoopOut();
	}
	else
	{
		scoopStop();
	}
}

void forwardBy14(int multiplier)
{
	motor[motorD] = MOTOR_POW_BACKWARD;
	motor[motorE] = MOTOR_POW_FORWARD;
	wait1Msec(500 * multiplier);
}

void turnBy45Clock(int multiplier)
{
	motor[motorD] = MOTOR_POW_BACKWARD;
	motor[motorE] = MOTOR_POW_BACKWARD;
	wait1Msec(250 * multiplier);
}

void turnBy45CounterClock(int multiplier)
{
	motor[motorD] = MOTOR_POW_FORWARD;
	motor[motorE] = MOTOR_POW_FORWARD;
	wait1Msec(250 * multiplier);
}

void flapUp() {
	motor[motorFlap] = 40;
}

void flapDown() {
	motor[motorFlap] = -40;
}

void flapStop() {
	motor[motorFlap] = 0;
}

void flapControl() {
	if (joystick.joy2_TopHat == 0) {
		flapUp();
	} else if (joystick.joy2_TopHat == 4) {
		flapDown();
	} else {
		flapStop();
	}
}
