#include <stdio.h>
#include <stdlib.h>

int plant(int disturbance, int control);

int main (void) {    // used to characterize the dynamics of the unknown plant
    int i;
    int result;
    time_t t;
    srand(time(&t));    // seed random number generator with different value each time

    for(i=0;i<500;i++) {
    // when you have the ADC and DAC interfaces completed you will get and put values like this:
    // result = plant(getDisturb(), getControl()); // get these signals from respective ADCs
        result = plant(3,10);    // these can be varied from run to run to see how the plant
                    // behaves
    // then 
    //    putResult(result);    // to DAC output
        printf("Level: %d\n", result);
    }
}
