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

float doFIR(float * weights, float * inputSignal, float * outputSignal, int siglength, int weightslength){
    int f = 0;
    int s = 0;
    // Weights will remain 'stationary' and the signal will 'flow' through from right to left
    // (think convolution but backwards direction from how you normally slide across)
    // the following float pointers will be for representing which parts in the signal are 
    // below the end points of the weights
    //sigcircular is for which item in the sig is 
    float * left; float * right; float * wcircular; float * sigcircular;
    float * startcase; float * endcase;
    *left = -1.0; *right = -1.0; // minus denotes not started yet
    int iterations = siglength + weightslength - 1; // convolution # of expected results
    right = &inputSignal[0]; // special starting case, first sig element is at the rightmost weight
    int i = 0;
    sigcircular = right; // sigcircular for intial transient and marks 
    int wIndex;
    for(i = 0; i < iterations; i++){
      outputSignal[i] = 0.0;
      int conv = 0;
      //starting logic
      if(left == startcase){ // while signal still reaching other end of weights, multiply everything from signal[0] to right
         wIndex = 0;
         while(sigcircular != &inputSignal[0]){
           outputSignal[i] += *sigcircular * weights[wIndex];
           sigcircular--; // move left down the array toward the 0th element 
           wIndex++; // move to next weight element, weights are symmetric so -- or ++ works
         }
         // Finally sigcircular reaches 0th element of signal
         outputSignal[i] += *sigcircular * weights[wIndex]; 
         // Now for next iteration move right ptr along one. 
         right++;
         if(wIndex > weightslength){
           left = &inputSignal[0]; // leftmost weight has now got the sig element0 under it
         }
      }
      else if (right == endcase){ // sig has moved beyond being beneath all weights
        wIndex = 0; 
        sigcircular = left; 
        while(sigcircular != &inputSignal[siglength-1]){
          outputSignal[i] += *sigcircular * weights[wIndex];
          wIndex++;
          sigcircular++;
        }
        // Finally sigcircular reaches rightmost element of signal
         outputSignal[i] += *sigcircular * weights[wIndex]; 
         left++; 
         right++;
      }
      else{
        // main body
        sigcircular = right;
        if(right == &weights[weightslength-1]){//if we have reached the point where sig starts leaving the weights
         right = endcase;// set the condition for the endgame. 
        }
        wIndex = 0; 
        while(sigcircular != &inputSignal[0]){
          outputSignal[i] += *sigcircular * weights[wIndex];
          sigcircular--; // move to next sig element
          wIndex++; // move to next weight element
        }
        // Finally sigcircular reaches 0th element of signal
        outputSignal[i] += *sigcircular * weights[wIndex];
        right++;
        left++; // keep on moving which sig element has the leftmost weight above it
        
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

    
    
    doFIR(b_fir1, signal1,filteredSignal1,signalLength,N_FIR_B1);
    
    writeDataToFile("filtered1.data",filteredSignal1, signalLength);
    
    doFIR(b_fir2, signal2,filteredSignal2,signalLength,N_FIR_B2);
    
    writeDataToFile("filtered2.data",filteredSignal2, signalLength);
    
	return 0;
}
