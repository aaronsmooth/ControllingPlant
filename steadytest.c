#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//int plant(int disturbance, int control);

int main (int argc, char * argv[]) {    // used to characterize the dynamics of the unknown plant
	int i, j, result;
	int disturbance = atoi(argv[1]);
	int control = atoi(argv[2]);
	FILE *fp;
	fp = fopen("steadytests.sql", "a");
	if(fp == NULL) exit (-1);
	//fprintf(fp, "Control: %d\n", control);
	//fprintf(fp, "Disturbance: %d\n\n", disturbance);
	//fprintf(fp, "Step	Output\n");
	int plant(int disturbance, int control);
	for(i=0;i<=500;i++) {
		// when you have the ADC and DAC interfaces completed you will get and put values like this:
		// result = plant(getDisturb(), getControl()); // get these signals from respective ADCs
		result = plant(disturbance, control);    // these can be varied from run to run to see how the plant behaves
		// then
		// putResult(result);    // to DAC output
		// printf("Level: %d\n", result);
		if(i%50==0){
			//fprintf(fp, "%d	%d\n", i, result);
			fprintf(fp, "INSERT INTO TEST_DATA VALUES (%d, %d, %d, %d);\n", control, disturbance, i, result);
		}
	}
	//fprintf(fp, "---------------------\n\n");
	fclose(fp);
	return 0;
}
