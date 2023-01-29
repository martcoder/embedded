#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "weights_filter1.h"
#include "weights_filter2.h"

#define signalLength 900
#define idMultiplier 100
#define idLength 9

float * filteredSignal1;
float * filteredSignal2;

float doFIR(float * weights, float * inputSignal, float * outputSignal){
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
    signal1 = (float*) malloc( sizeof(float) * signalLength );
    signal2 = (float*) malloc( sizeof(float) * signalLength );

    
    FILE * fp1; // file pointer
    FILE * fp2; // file pointer
    fp1 = fopen("signal1.data","w"); //open file to write to
    fp2 = fopen("signal2.data","w"); //open file to write to
    
    // Construct full 900 length signal1 and signal2
    int c = 0;
    int nine = 0;
    printf("before signal construction");
    int i = 0;
    while(c < idMultiplier){ //100 times
        for(nine = 0; nine < idLength; nine++){
           signal1[i+nine] = student1[nine];
           fprintf(fp1,"%f\n",signal1[i+nine]); //print signal1 value to file
           signal2[i+nine] = student2[nine]; 
           fprintf(fp2,"%f\n",signal2[i+nine]); //print signal2 value to file
        }
        c++;
        i = i + 9;
    }
    
    printf("after signal construction");

    fclose(fp1);
    fclose(fp2);
    i = 0;
    for(i = 0; i < 10; i++){
      printf("sig1 and sig2 first 10 vals %f %f",signal1[i],signal2[i]);
    }
    //
    filteredSignal1 = (float*) malloc(sizeof(float) * signalLength);
    filteredSignal2 = (float*) malloc(sizeof(float) * signalLength);
    
    int delay = 0;
    printf("Our weight value is %f and sig1 val is %f ",b_fir1[0],signal1[0]);

    
    /*
    doFIR(b_fir1, signal1,filteredSignal1);
    
    writeDataToFile("filtered1.data",filteredSignal1, signalLength);
    
    doFIR(b_fir2, signal2,filteredSignal2);
    
    writeDataToFile("filtered2.data",filteredSignal2, signalLength);
    */
	return 0;
}
