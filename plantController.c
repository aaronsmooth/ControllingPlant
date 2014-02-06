#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "global.h"

//variables
int fd, flag;

//prototypes
int calculateControl();
int getOutput();
int getSetpoint();
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

int calculateControl(int output, int setPoint){
    // using transfer function calculate the control
}

int getOutput() {
	return analogRead(BASE);
}

int getSetpoint() {
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
	int i, j, result;
	setup();
    flag = TRUE;    // initialize flag to be true to avoid deadlock between two pi
    
	for(;;) {
        printf("Waiting for interrupt.. ");
        while (!flag);       // wait for interrupt to happen
        printf("interrupted.. ")
        flag = FALSE;        // reset flag
		result = calculateControl(getOutput(), getSetPoint());
		putResult(result);    // to DAC output
        digitalWrite(OUTPUT_PIN, TRUE); // inform the other pi
	}
	return NO_ERROR;
}
