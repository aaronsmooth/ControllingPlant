#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <mcp3004.h>
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
    return 11;
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
	int result, output, setPoint;
	setup();
    flag = TRUE;    // initialize flag to be true to avoid deadlock between two pi

	for(;;) {
        printf("Waiting for interrupt.. \n");
        while (!flag);       // wait for interrupt to happen
        printf("interrupted.. \n");
        output = getOutput();
        setPoint = getSetpoint();
        printf("Output: %d  |   Setpoint: %d\n", output, setpoint);
        digitalWrite(INPUT_PIN, TRUE); // reset pin
        flag = FALSE;        // reset flag
		result = calculateControl(output, setpoint);
		putResult(result);    // to DAC output
        printf("Control-Out: %d\n", result);
        digitalWrite(OUTPUT_PIN, TRUE); // inform the other pi
	}
	return NO_ERROR;
}
