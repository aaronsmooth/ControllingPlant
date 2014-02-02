#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <mcp3004.h>

int main(int argc, char * argv[]) {
	mcp3004Setup(123, 0); // Setup SPI BASE = 123, CHANNEL = 0
	wiringPiSetupSys(); // Setup wiringPi

	for(;;) {
		printf("ADC: %d\n", analogRead(123)); // BASE = 123
	}
}
