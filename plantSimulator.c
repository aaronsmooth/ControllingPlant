#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <wiringPi.h>
#include <mcp3004.h>
#include <wiringPiI2C.h>
#include "global.h"

//variables
int fd, flag;

//prototypes
int plant(int disturbance, int control);
int getControl();
int getDisturb();
int putResult();
int setup();
void interrupt(void);

int setup() {
	fd = wiringPiI2CSetup(DEVICE_ID);
	mcp3004Setup(BASE, CHANNEL);
	wiringPiSetup();
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
	return wiringPiI2CWriteReg8(fd, (value >> 8) & 0xFF, value & 0xFF);
}

void interrupt(void){
   flag = TRUE;
}

int main (int argc, char * argv[]) {    // used to characterize the dynamics of the unknown plant
	int result, disturb, control;
	setup();
	flag = FALSE;   // wait for plant controller to signal

	for(;;) {
        printf("Waiting for interrupt.. \n");
        while (!flag);       // wait for interrupt to happen
        printf("\ec"); // clear the terminal screen
        printf("interrupted.. \n");
        disturb = getDisturb();
        control = getControl();
        printf("Disturb: %d     |   Control: %d\n", disturb, control);
        flag = FALSE;        // reset flag
		result = plant(disturb, control); // get these signals from respective ADCs
		printf("Output to Controller: %d\n", result);
		putResult(result*4);    // to DAC output
		digitalWrite(OUTPUT_PIN, 1); // signal the other pi
		//delay(1000); // wait a millisecond
		digitalWrite(OUTPUT_PIN, 0); // clear the signal line
	}
	return NO_ERROR;
}
