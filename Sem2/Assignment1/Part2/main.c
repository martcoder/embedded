#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "weights_filter1.h"
#include "weights_filter2.h"

#define signalLength 900
#define idMultiplier 100
#define idLength 9
#define N_CHUNK 4

//#define TEST


float doFIR(float * weights, float * inputSignal, float * outputSignal, int siglength, int weightslength, int chunkLength, int resultsLength){
   // signal will be split into chunks
  //weights will be swept across the signal chunk
  // Signal will be chunked into length of 8, therefore convolution result = weightsLength+8 - 1;
  // If signal chunk is less than 8, then just do that too. 
  
  //Results array
  //float * results;
  //results = (float*) malloc(sizeof(float) * resultsLength);
  //initialise where in signal where are looking at
  float * whereInChunk = inputSignal;
  float * endOfChunk = inputSignal + chunkLength;
  float * whereInWeights = weights;
  float * weightEnd = weights + weightslength - 1;
  int iter = 0;
  int shift = 1;
  int dotprodlength = 0;
  //weightslength + chunkLength - 1 = number of convolution results we need
  for(shift = 1; shift < (weightslength + chunkLength); shift++){
    outputSignal[shift-1] = 0.0f;
    
    // following if statement adjusts how long the dot product is at start and end of convolution
    if(shift < chunkLength){ //at start of convolution
      dotprodlength = shift;
    }
    else if ( shift > weightslength){//at end of convolution
      dotprodlength = chunkLength - (shift - weightslength); // will want to iterate few times
      whereInChunk = inputSignal + (shift - weightslength); // set signal starting point
      whereInWeights  = weightEnd; // we are at the end of our convolution so always counting bakcware from weights end 
    }
    else{
      dotprodlength = chunkLength;
    }
#ifdef TEST
    printf("\nStarting a new convo result MAC\n");
#endif
    for(iter = 0; iter < dotprodlength; iter++){
#ifdef TEST
      printf("...\nweight is %f and sig is %f and \n",*whereInWeights,*whereInChunk);
#endif
      outputSignal[shift-1] += (float) (*whereInWeights) * (*whereInChunk);
#ifdef TEST
      printf("intermediate convolution result value is %f\n",outputSignal[shift-1]);
#endif
      whereInWeights--; // move to preceding weight
      whereInChunk++; // move to subsequent element in signal chunk
      // need to break out of chunkLength if we are at the beginning or end of the convolution
      
    }
    // reset pointers and move to next shift position
    whereInChunk = inputSignal;
    whereInWeights = weights + shift;
  }
#ifdef TEST
  int c = 0; 
  printf("\nThe %d-long results of convolution of filter with weights %d is:\n",weightslength + chunkLength - 1,weightslength);
  for(c = 0; c < weightslength + chunkLength - 1; c++){
    printf("\nresult[%d] = %f\n",c,outputSignal[c]);
  }
#endif

  //outputSignal = results; //Finally set the outputSignal ptr to the results ptr for access outside of this function
}


void writeDataToFile(char * filename, float * data, int lengthOfArray){
    FILE * fptr;
    fptr = fopen(filename,"w");
    int c = 0;
#ifdef TEST
    printf("\nUp to just before for loop in writeDataToFile func\n");
#endif

    for(c = 0; c < lengthOfArray; c++){
#ifdef TEST
        printf("value is %f",data[c]);
#endif
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
#ifdef TEST
    printf("\nbefore signal construction\n");
#endif
    int i = 0;
    while(c < idMultiplier){ //100 times
        for(nine = 0; nine < idLength; nine++){
           signal1[i+nine] = student1[nine];
           //fprintf(fp1,"%f\n",signal1[i+nine]); //print signal1 value to file
           signal2[i+nine] = student2[nine]; 
           //fprintf(fp2,"%f\n",signal2[i+nine]); //print signal2 value to file
        }
        c++;
        i = i + 9;
    }
#ifdef TEST
    printf("\nafter signal construction\n");
#endif
    //=================CALCULATE AVG, THEN SUBTRACT AVG LEAVING MEAN-ZERO SIGNALS====
    float average1 = 0.0;
    float average2 = 0.0;
    int n900 = 900;
    for(n900 = 0; n900 < 900; n900++){
      average1 = average1 + signal1[n900];
      average2 = average2 + signal2[n900];
    }

    average1 = average1 / 900.0f;
    average2 = average2 / 900.0f;

    //========Create zero-mean signals and also print to file. 
    for(n900 = 0; n900 < 900; n900++){ 
      signal1[n900] -= average1;
      fprintf(fp1,"%f\n",signal1[n900]); //print signal1 value to file
      signal2[n900] -= average2;
      fprintf(fp2,"%f\n",signal2[n900]); //print signal2 value to file
    }

    // Close file handles. 
    fclose(fp1);
    fclose(fp2);
#ifdef TEST
    printf("\nThe mean valueS for signal1 and signal2 are %f and %f\n",average1,average2);

    i = 0;
    for(i = 0; i < 10; i++){
      printf("\nsig1 and sig2 first 10 vals %f %f\n",signal1[i],signal2[i]);
    }
#endif
    //
    float * filteredSignal1 = (float*) malloc( sizeof(float) * (N_CHUNK + N_FIR_B1 - 1) );
    float * filteredSignal2 = (float*) malloc( sizeof(float) * (N_CHUNK + N_FIR_B2 - 1) );
    
#ifdef TEST
    printf("\nOur weight value is %f and sig1 val is %f \n",b_fir1[0],signal1[0]);
#endif

    
    doFIR(b_fir1, signal1, filteredSignal1, signalLength,N_FIR_B1,N_CHUNK,N_FIR_B1 + N_CHUNK - 1);

#ifdef TEST
    printf("\nJust did a FIR filtering\n");
#endif    
    writeDataToFile("filtered1.data",filteredSignal1, N_CHUNK + N_FIR_B1 - 1); // write convolution results
    
    doFIR(b_fir2, signal2,filteredSignal2,signalLength,N_FIR_B2,N_CHUNK, N_FIR_B2 + N_CHUNK - 1);
    
    writeDataToFile("filtered2.data",filteredSignal2, N_CHUNK + N_FIR_B2 - 1);
    
	return 0;
}
