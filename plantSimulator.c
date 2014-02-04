#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "main.h"

//variables
int fd;

//prototypes
int plant(int disturbance, int control);
int getControl();
int getDisturb();
int putResult();
int setup();

int setup() {
	fd = wiringPiI2CSetup(DEVICE_ID);
	mcp3004Setup(BASE, CHANNEL);
	wiringPiSetupSys();
	return NO_ERROR;
}

int getControl() {
	return analogRead(BASE);
}
int getDisturb() {
	return analogRead(BASE + 1);
}

int putResult(int value) {
	return wiringPiI2CWriteReg8(fd, (value >> 8) & 0xFF, 
value & 0xFF);
}
int main (int argc, char * argv[]) {    // used to characterize the dynamics of the unknown plant
	int i, j, result;
	setup();

	for(;;) {
		// when you have the ADC and DAC interfaces completed you will get and put values like this:
		result = plant(getDisturb(), getControl()); // get these signals from respective ADCs
		putResult(result);    // to DAC output
		// printf("Level: %d\n", result);
	}
	return NO_ERROR;
}
