#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "weights_filter1.h"
#include "weights_filter2.h"

#define signalLength 900
#define idMultiplier 100

float * filteredSignal1;
float * filteredSignal2;

float FIR(float * weights, float * inputSignal, float * outputSignal){
    int f = 0;
    int s = 0;
    for(f = 0; f < signalLength; f++){ // for every y value output
        for(s = 0; s < signalLength; s++){ // Accumulate the product of inputSignal element and corresponding weight element
            //printf("weight value is %f and sig val is %f",weights[s],inputSignal[s]);
            int delay;
            //scanf("%d",&delay);
            outputSignal[f] += weights[s] * inputSignal[s]; // Here the product and accumulate happens
        }
    }
}

void writeDataToFile(char * filename, float * data, int lengthOfArray){
    FILE * fptr;
    fptr = fopen(filename,"w");
    int c = 0;
    for(c = 0; c < lengthOfArray; c++){
        printf("value is %f",data[c]);
        fprintf(fptr,"%f\n",data[c]); //print value to file
    }
    
    fclose(fptr);
}

int main(void) {
    
    float student1[9] = {2.0f,0.0f,2.0f,2.0f,9.0f,1.0f,0.0f,6.0f,0.0f};
    float student2[9] = {2.0f,0.0f,2.0f,2.0f,6.0f,7.0f,3.0f,4.0f,8.0f};
    float * signal1;
    float * signal2;
    signal1 = (float*) malloc( sizeof(float) * (signalLength + N_FIR_B1) );
    signal2 = (float*) malloc( sizeof(float) * (signalLength + N_FIR_B2) );
    
    FILE * fp1; // file pointer
    FILE * fp2; // file pointer
    fp1 = fopen("signal1.data","w"); //open file to write to
    fp2 = fopen("signal2.data","w"); //open file to write to
    
    int c = 0;
    int nine = 0;
    for(c=0;c<idMultiplier;c++){
        for(nine = 0; nine < 9; nine++){
           signal1[c] = student1[nine];
           fprintf(fp1,"%f\n",signal1[c]); //print signal1 value to file
           signal2[c] = student2[nine]; 
           fprintf(fp2,"%f\n",signal2[c]); //print signal2 value to file
        }
    }
    
    int m = 0;
    //append zeros
    for(m = signalLength; m < (signalLength+N_FIR_B1); m++){
        signal1[m] = 0.0f;
    }
    for(m = signalLength; m < (signalLength+N_FIR_B2); m++){
        signal2[m] = 0.0f;
    }
    
    //
    filteredSignal1 = (float*) malloc(sizeof(float) * signalLength);
    filteredSignal2 = (float*) malloc(sizeof(float) * signalLength);
    
    int delay = 0;
    //printf("Our weight value is %f and sig val is %f",b_fir1[0],signal1[1]);

    //        scanf("%d",&delay);
    
    FIR(b_fir1, signal1,filteredSignal1);
    
    writeDataToFile("filtered1.data",filteredSignal1, signalLength);
    
    FIR(b_fir2, signal2,filteredSignal2);
    
    writeDataToFile("filtered2.data",filteredSignal2, signalLength);
    
	return 0;
}