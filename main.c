#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int plant(int disturbance, int control);

int main (void) {    // used to characterize the dynamics of the unknown plant
    int i, j, result;
    int disturbance = 3;
    int control = 10;
    time_t t;
    srand(time(&t));    // seed random number generator with different value each time
    FILE *fp;
    char *str;
    fp = fopen("result1.txt", "w");
    if(fp == NULL) exit (-1);
    for(j=0;j<1024;j++) {
    disturbance = j;
    fprintf(fp, "Control: %d\n", control);
    fprintf(fp, "Disturbance: %d\n\n", disturbance);
    fprintf(fp, "i	Level\n");
    for(i=0;i<500;i++) {
    // when you have the ADC and DAC interfaces completed you will get and put values like this:
    // result = plant(getDisturb(), getControl()); // get these signals from respective ADCs
        result = plant(disturbance, control);    // these can be varied from run to run to see how the plant
                    // behaves
    // then 
    //    putResult(result);    // to DAC output
       // printf("Level: %d\n", result);
	fprintf(fp, "%d	%d\n", i, result);	
    }
    fprintf(fp, "---------------------\n\n");
    }
    fclose(fp);
    return 0;
}
