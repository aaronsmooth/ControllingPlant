#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "global.h"

//variables
int fd, flag;

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
    pinMode(OUTPUT_PIN, OUTPUT);
	wiringPiISR(INPUT_PIN, INT_EDGE_RISING, &interrupt);
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

void interrupt(){
   flag = TRUE;
}

int main (int argc, char * argv[]) {    // used to characterize the dynamics of the unknown plant
	int i, j, result, disturb, control;
	setup();
    flag = FALSE;   // wait for plant controller to signal

	for(;;) {
        printf("Waiting for interrupt.. \n");
        while (!flag);       // wait for interrupt to happen
        printf("interrupted.. \n");
        disturb = getDisturb();
        printf("Disturb: %d     |   Control: %d\n", disturb, control);
        digitalWrite(INPUT_PIN, FALSE); // reset pin value
        flag = FALSE;        // reset flag
		result = plant(disturb, control); // get these signals from respective ADCs
		printf("Output to Controller: %d\n", result);
		putResult(result);    // to DAC output
        digitalWrite(OUTPUT_PIN, TRUE); // inform the other pi
	}
	return NO_ERROR;
}
