#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <mcp3004.h>
#include "global.h"

//constants
const float kp = 1.1789;
const float ki = 1.0615;
const float kd = 0.8234;
const float IntegralThreshold = 25;

//variables
int fd, flag, error, previousValue = 1000, control;
float p, i = 0, d;

//prototypes
int calculateControl();
int getOutput();
int getSetpoint();
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

int calculateControl(int output, int setPoint){
    error = setPoint - output;
    p = error * kp;
    i = i + error;
    if(i > IntegralThreshold){
        i = IntegralThreshold;
    }
    if(i < -IntegralThreshold){
        i = -IntegralThreshold;
    }
    i = i * ki;
    d = (output - previousValue) * kd;
    previousValue = output;
    printf("p %6.3f\ni %6.3f\nd %6.3f\n", p, i, d);
    if(p + i + d < 0){
        control = 0;
    } else {
        control = 1023;
    }
    return control;
}

int getOutput() {
	return analogRead(BASE);
}

int getSetpoint() {
	return analogRead(BASE + 1);
}

int putResult(int value) {
	return wiringPiI2CWriteReg8(fd, (value >> 8) & 0xFF, value & 0xFF);
}

void interrupt(void){
    flag = TRUE;
}

int main (int argc, char * argv[]) {    // used to characterize the dynamics of the unknown plant
	int result, output, setPoint;
	setup();
	flag = TRUE;    // initialize flag to be true to avoid deadlock between two pi

	for(;;) {
        printf("Waiting for interrupt.. \n");
        while (!flag);       // wait for interrupt to happen
        printf("\ec"); // clear the terminal screen
        printf("interrupted.. \n");
        output = getOutput();
        setPoint = getSetpoint();
        printf("Output: %d  |   Setpoint: %d\n", output, setPoint);
        flag = FALSE;        // reset flag
		result = calculateControl(output, setPoint);
		putResult(result*4);    // to DAC output
        printf("Control-Out: %d\n", result);
        digitalWrite(OUTPUT_PIN, 1); // inform the other pi
        delay(1); // wait a millisecond
		digitalWrite(OUTPUT_PIN, 0); // clear the signal line
	}
	return NO_ERROR;
}
