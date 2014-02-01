#include <wiringPiI2C.h>
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

int main(int argc, char *argv[]) {
	int fd;
	fd = wiringPiI2CSetup(0x63); // 0x63 is the devId for the MCP4725 DAC

	printf("fd is: %d \n", fd);

	int value = atoi(argv[1]);

	int output = wiringPiI2CWriteReg8(fd, (value >> 8) & 0xFF, value & 0xFF);

	printf("output is: %d \n", output);

	return 0;
}
