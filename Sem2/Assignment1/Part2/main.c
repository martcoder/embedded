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
  
/* int numLoops = 2; // rounds this up
 int whileCounter = 0;
 while(whileCounter < numLoops){
 */ //Results array
  //float * results;
  //results = (float*) malloc(sizeof(float) * resultsLength);
  //initialise where in signal where are looking at
  float * ptrToResult = outputSignal;
  float * ptrToInputSig = inputSignal;
  float * whereInChunk = inputSignal;
  float * endOfChunk = inputSignal + chunkLength;
  float * whereInWeights = weights;
  float * weightEnd = weights + weightslength - 1;

 int numLoops = ceil(siglength / chunkLength); // rounds this up
#ifdef TEST
 printf("num while loops is %d\n",numLoops);
#endif
 int whileCounter = 0;
 while(whileCounter < numLoops){

  int iter = 0;
  int shift = 1;
  int dotprodlength = 0;
  //weightslength + chunkLength - 1 = number of convolution results we need
  for(shift = 1; shift < (weightslength + chunkLength); shift++){
    //initialilse result value to 0.0 
    /*if(whileCounter == 0){
      ptrToResult[shift-1] = 0.0f;
    }*/
    // following if statement adjusts how long the dot product is at start and end of convolution
    if(shift < chunkLength){ //at start of convolution
      dotprodlength = shift;
    }
    else if ( shift > weightslength){//at end of convolution
      dotprodlength = chunkLength - (shift - weightslength); // will want to iterate few times
      whereInChunk = ptrToInputSig + (shift - weightslength); // set signal starting point
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
      ptrToResult[shift-1] += (float) (*whereInWeights) * (*whereInChunk);
#ifdef TEST
      printf("intermediate convolution result value is %f\n",ptrToResult[shift-1]);
#endif
      whereInWeights--; // move to preceding weight
      whereInChunk++; // move to subsequent element in signal chunk
      // need to break out of chunkLength if we are at the beginning or end of the convolution
      
    }
    // reset pointers and move to next shift position
    whereInChunk = ptrToInputSig;
    whereInWeights = weights + shift;
  }
#ifdef TEST
  int c = 0; 
  printf("\nThe %d-long results of convolution of filter with weights %d is:\n",weightslength + chunkLength - 1,weightslength);
  for(c = 0; c < weightslength + (chunkLength*2) - 1; c++){
    printf("\nresult[%d] = %f\n",c,inputSignal[c]);
  }
#endif

  whileCounter++;
  ptrToInputSig = ptrToInputSig + chunkLength; // move to next Overlap-Add section in signal...
  // Move to the section of the results that you want to start overlapping convo results onto
  ptrToResult = ptrToResult + chunkLength;

  whereInWeights = weights;
 }//end of while
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
    float test1[4] = { 1, 4, 6, 3};
    float test2[4] = { 3, 2, 7, 4};
    

    int choice = -1; 
    printf("\n\n==============\nMake a choice then press Enter.....\n");
    printf(" If you would like to use the coursework signals press 0\n");
    printf(" or if you would like to use the test signals press 1 \n");
    printf(" Enter your choice here: ");
    scanf("%d",&choice);
    if(choice == 0){ printf("\nOkay, you selected the coursework signals, doing FIR filtering of them now\n");}
    else if(choice == 1){ printf("\nOkay, you selected the test signals, doing FIR filtering of them now\n");}
    else{
      choice = 0; //default of coursework signals
      printf("\n... thanks for participating, using the default coursework signals then... \n");
    }

    
    int chunksize = 4;
    printf("\n\n======Okay now define chunk size, e.g. how big a chunk of the signal gets processed each time using overlap add\n");
    printf("--------- Enter an integer value between 2 and inifinity.... : ");
    scanf("%d",&chunksize);
    if(chunksize < 2){
      chunksize = 4; 
      printf("\n... so I'll just use the default chunksize of 4 then....\n");
    }
    printf("You chose chunksize of %d\n",chunksize);

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
           signal2[i+nine] = student2[nine]; 
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

   if(choice == 1){    
     printf("The two test signals are: \n");
     printf("Test signal 1: [%f %f %f %f]\n",test1[0],test1[1],test1[2],test1[3]);
     printf("Test signal 2: [%f %f %f %f]\n",test2[0],test2[1],test2[2],test2[3]);
   }
   else{
     printf("The two test signals have been written to two data files containing their values\n");

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
    float * filteredSignal1 = (float*) malloc( sizeof(float) * (signalLength + N_FIR_B1 - 1) );
    float * filteredSignal2 = (float*) malloc( sizeof(float) * (signalLength + N_FIR_B2 - 1) );
    float * filteredTestSignal1 = (float*) malloc( sizeof(float) * (4 + N_FIR_B1 - 1) );
     float * filteredTestSignal2 = (float*) malloc( sizeof(float) * (4 + N_FIR_B2 - 1) );    


    // Initialise final values to zero
    int init = 0;
    for(init = 0; init < (signalLength + N_FIR_B1 - 1); init++){
      filteredSignal1[init] = 0.0f;
      filteredSignal2[init] = 0.0f;
    }
#ifdef TEST
    printf("\nOur weight value is %f and sig1 val is %f \n",b_fir1[0],signal1[0]);
#endif

    if(choice == 1){ // test signals
      doFIR(b_fir1, test1/*signal*/, filteredTestSignal1, 4/*signalLength*/,N_FIR_B1,chunksize/*N_CHUNK*/,N_FIR_B1 + N_CHUNK - 1);
      writeDataToFile("testfiltered1.data",filteredTestSignal1, 4/*signalLength*/ + N_FIR_B1 - 1); // write convolution results

      doFIR(b_fir2, test2/*signal*/, filteredTestSignal2, 4/*signalLength*/,N_FIR_B2,chunksize/*N_CHUNK*/,N_FIR_B2 + N_CHUNK - 1);
      writeDataToFile("testfiltered2.data",filteredTestSignal2, 4/*signalLength*/ + N_FIR_B2 - 1); // write convolution results

      printf("Please find the filtered results in testfilteredx.data\n");
    }
    else{
      // FIR filter signal1
      doFIR(b_fir1, signal1, filteredSignal1, signalLength,N_FIR_B1,N_CHUNK,N_FIR_B1 + chunksize/*N_CHUNK*/ - 1);
      writeDataToFile("filtered1.data",filteredSignal1, signalLength + N_FIR_B1 - 1); // write convolution results

      doFIR(b_fir2, signal2,filteredSignal2,signalLength,N_FIR_B2,N_CHUNK, N_FIR_B2 + chunksize/*N_CHUNK*/ - 1);
 
      writeDataToFile("filtered2.data",filteredSignal2, signalLength + N_FIR_B2 - 1);
  
      printf("Please find the filtered results in filteredx.data\n");
    }

    
	return 0;
}
