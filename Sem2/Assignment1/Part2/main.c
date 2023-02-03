#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "weights_filter1.h"
#include "weights_filter2.h"

#define signalLength 900
#define idMultiplier 100
#define idLength 9
#define N_CHUNK 8

float * filteredSignal1;
float * filteredSignal2;

float doFIR(float * weights, float * inputSignal, float * outputSignal, int siglength, int weightslength, int chunkLength, int resultsLength){
   // signal will be split into chunks
  //weights will be swept across the signal chunk
  // Signal will be chunked into length of 8, therefore convolution result = weightsLength+8 - 1;
  // If signal chunk is less than 8, then just do that too. 
  
  //Results array
  float * results;
  results = (float*) malloc(sizeof(float) * resultsLength);
  //initialise where in signal where are looking at
  float * whereInChunk = inputSignal;
  float * endOfChunk = inputSignal + chunkLength;
  float * whereInWeights = weights;
  float * weightEnd = weights + weightslength;
  int iter = 0;
  int shift = 1;
  int dotprodlength = 0;
  //weightslength + chunkLength - 1 = number of convolution results we need
  for(shift = 1; shift < (weightslength + chunkLength); shift++){
    results[shift] = 0.0f;
    
    // following if statement adjusts how long the dot product is at start and end of convolution
    if(shift < chunkLength){ //at start of convolution
      dotprodlength = shift;
    }
    else if ( (weightslength - shift) < chunkLength){//at end of convolution
      dotprodlength = weightslength - shift;
      whereInChunk = inputSignal + chunkLength - (weightslength - shift);
    }
    else{
      dotprodlength = chunkLength;
    }
    for(iter = 0; iter < dotprodlength; iter++){
      results[shift] += (*whereInWeights) * (*whereInChunk);
      whereInWeights--; // move to next weight
      whereInChunk++; // move to next element in signal chunk
      // need to break out of chunkLength if we are at the beginning or end of the convolution
      
    }
    // reset pointers and move to next shift position
    whereInChunk = inputSignal;
    whereInWeights = weights + shift;
  }
  int c = 0; 
  printf("\nThe %d-long results of convolution of filter with weights %d is:\n",weightslength + chunkLength - 1,weightslength);
  for(c = 0; c < weightslength + chunkLength - 1; c++){
    printf("\nresult[%d] = %f\n",c,results[c]);
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


    
    doFIR(b_fir1, signal1,filteredSignal1,signalLength,N_FIR_B1,N_CHUNK,N_FIR_B1 + N_CHUNK - 1);
    
    //writeDataToFile("filtered1.data",filteredSignal1, signalLength);
    
    //doFIR(b_fir2, signal2,filteredSignal2,signalLength,N_FIR_B2,N_CHUNK, N_FIR_B2 + N_CHUNK - 1);
    
    //writeDataToFile("filtered2.data",filteredSignal2, signalLength);
    
	return 0;
}
