#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*
 * main.c
 */
int main(void) {
	
	//500hz sine wave, sampled at 4800Hz, gives 9.6 samples per period
	// they want 2.5 periods which is 24 samples.
	// so 2.5 periods is (2*pi() * 2.5) then divide that into 24....
	double totalRadians = 2 * (22/7) * 2.5;
	double sampleSpacing = totalRadians / 24;
	double output = 0;
	double sampleIncrementer = 0;

	int c = 0;
	FILE *fptr; // thanks to programiz.com/c-programming/c-file-input-output
	fptr = fopen("sinevalues.dat","a");
	if(fptr == NULL)
	{
		printf("Error when opening file!");
		exit(1);
	}
	for(c=0;c<24;c++){
		output = sin(sampleIncrementer);
		fprintf(fptr,"%f\n",output);
		sampleIncrementer = sampleIncrementer + sampleSpacing;
	}

	fclose(fptr);

	return 0;
}
