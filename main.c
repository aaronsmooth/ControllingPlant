#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <mcp3004.h>
#include "main.h"


int main(int argc, char * argv[]) {
	mcp3004Setup(BASE, CHANNEL); 
	wiringPiSetupSys(); // Setup wiringPi

	for(;;) {
		//printf("ADC: %d\n", temp); // BASE = 123
	//	printf("ADC: %d\n", analogRead(124)); // BASE = 123
	}
	return NO_ERROR;
}








