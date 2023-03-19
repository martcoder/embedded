#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
//ref https://stackoverflow.com/questions/5141960/get-the-current-time-in-c
float lp_denominator[17] = {1.0f, -5.3263f, 14.9989f, -28.3719f, 39.7005f, -43.0924f, 37.2584f, -26.0312f, 14.7901f, -6.8332f, 2.5516f, -0.7602f, 0.1768f, -0.0310f, 0.0039f, -0.0003f, 0.0f};
float lp_numerator[17] = { 0.0f, 0.0f, 0.0001f, 0.0003f, 0.0009f, 0.0022f, 0.0041f, 0.0059f, 0.0066f, 0.0059f, 0.0041f, 0.0022f, 0.0009f, 0.0003f, 0.0001f, 0.0f, 0.0f  };
float bp_denominator[17] = {1.0f, -0.0005f, 2.6528f, -0.0012f, 3.9151f, -0.0016f, 3.6092f, -0.0012f, 2.2599f, -0.0006f, 0.9571f, -0.0002f, 0.2664f, -0.0f, 0.044f, 0.0f, 0.0033f};
float bp_numerator[17] = {0.0007f, 0.0f, -0.005f, 0.0f, 0.0199f, 0.0f, -0.0397f, 0.0f, 0.0496f, 0.0f, -0.0397f, 0.0f, 0.0199f, 0.0f, -0.0057f, 0.0f, 0.0007f};
float hp_numerator[17] = {0.0000, -0.0000, 0.0001, -0.0003, 0.0009, -0.0022, 0.0041, -0.0059, 0.0066, -0.0059, 0.0041, -0.0022, 0.0009, -0.0003, 0.0001, -0.0000, 0.0000};
float hp_denominator[17] = {1.0000,  5.3257, 14.9962, 28.3650, 39.6887, 43.0774, 37.2438, 26.0200, 14.7832, 6.8298, 2.5502, 0.7598, 0.1767, 0.0310, 0.0038, 0.0003, 0.0000 };

float yMinus[16]; //global
float yMinus2[16]; //global
float yMinus3[16];
int yMinusOldest; // global pointer to oldest position in yMinus array
float currentOutput;
float * latestValueInSignal;

void writeDataToFile(char * filename, float * data, int lengthOfArray){
    FILE * fptr;
    fptr = fopen(filename,"w");
    int c = 0;

    for(c = 0; c < lengthOfArray; c++){
        fprintf(fptr,"%f\n",data[c]); //print value to file
    }

    fclose(fptr);
}

void doIIR(float * signalValuesLast17, float * currentOutput, int outputIndex, float * numerator, float * denominator, float * yPrevious){ //pass in last 16 values of signal

 float result = 0.0f;
 int c = 0;
 for(c=0; c < 17; c++){ 
   //printf("Currentoutput is %f\n",currentOutput[outputIndex]);
   //printf("about to multiply %f with %f\n",numerator[c], signalValuesLast17[c+outputIndex]);
   currentOutput[outputIndex] += numerator[c] * signalValuesLast17[c+outputIndex]; 
 }
 //printf("Now about to start denominator\n"); 
 int yIndex = 0;
 for(c=1; c < 17; c++){
   //printf("Currentoutput is %f\n",currentOutput[outputIndex]);
   yIndex = yMinusOldest - c;
   if( yIndex < 0 ){
     yIndex += 16;
   }
   //printf("about to multiply %f with %f\n",denominator[c], yMinus[ yIndex ]);

   currentOutput[outputIndex] -= denominator[c] * yPrevious[ yIndex ]; // where yMinus[0] is y[n-1]
   //yMinus[c-1] = 0.0f; // cheeky initialisation also using this loop
 }

 //printf("Final output for this round is %f\n",currentOutput[outputIndex]);
 // CIRCULAR BUFFER HOLDING yMinus values
 // Now update the previous y values, overwriting the oldest with latest
 // and update the index holding the oldest
 yPrevious[yMinusOldest] = currentOutput[outputIndex]; 
 yMinusOldest++; 
 if( yMinusOldest > 15 ){//yMinus holds 16 elements
    //reset 
    yMinusOldest = 0;
 }
 //for(c =0; c < 16; c++){
 //  printf("yMinus at index %d is %f\n",c,yMinus[c]);
 //}

}

int main(){
 currentOutput = 0.0f;
 yMinusOldest = 0; //initialise yMinus oldest index to start at 0 

 //construct signal to have 900 elements
 float filteredOutput[900];
 float filteredOutput2[900];
 float filteredOutput3[900];
 float sig[9] = {1.0f, 5.0f, 4.0f, 1.0f, 6.0f, 7.0f, 8.0f, 3.0f, 4.0f};
 float constructedSignal[900];
 int i = 0;
 int idLength = 9;
 int c = 0;
 int nine = 0;
    	while(c < 100){ //100 times
        	for(nine = 0; nine < idLength; nine++){
           	 constructedSignal[i+nine] = sig[nine];
        	}
        	c++;
        	i = i + 9;
	}

   // make signal zero-mean, while also initialising output elements to zero
   float avg = 0;
   for(c = 0; c < 900;c++){
     avg += constructedSignal[c];
     filteredOutput[c] = 0.0f; // also initialise output array elements to zero
     filteredOutput2[c] = 0.0f;
     filteredOutput3[c] = 0.0f;
   }

   avg = avg / 900.0;
   for(c = 0; c < 900;c++){ 
     constructedSignal[c] -= avg;
   }

   writeDataToFile("constructedSignal.data", constructedSignal, 900);

  // initialise yMinus to zeros
  for(c = 0; c < 16; c++){
    yMinus[c] = 0.0f;
    yMinus2[c] = 0.0f;
    yMinus3[c] = 0.0f;
  }

  //latestValueInSignal = &(sig[0]); 
  // let's do this!
  int ir = 0;
  for(ir=0; ir< 880; ir++){ // call iir for each value of the signal!!! 
    // lowpass iir filtering
    doIIR(constructedSignal,filteredOutput,ir, lp_numerator, lp_denominator,yMinus);
  }

  /*for(ir= 0; ir < 880; ir++){
    // bandpass iir filtering
    doIIR(constructedSignal,filteredOutput2,ir, bp_numerator, bp_denominator, yMinus2);
  }*/

  for(ir= 0; ir < 880; ir++){
    // highpass iir filtering
    doIIR(constructedSignal,filteredOutput3,ir, hp_numerator, hp_denominator, yMinus3);
  }

  // Combine low pass and bandpass filtered signal by adding together
  int combine;
  for(combine=0;combine<900;combine++){
    filteredOutput[combine] = filteredOutput[combine] + filteredOutput2[combine] + filteredOutput3[combine];
  }

  char filename[1024];
  time_t mytime = time(NULL);
  char * time_str = ctime(&mytime);
  time_str[strlen(time_str)-1] = '\0';
  strcat(filename,time_str);
  strcat(filename,"iirFilteredData.data");  

 //writeDataToFile("constructedSignal", constructedSignal, 900);

 //ref https://stackoverflow.com/questions/308695/how-do-i-concatenate-const-literal-strings-in-c
  writeDataToFile(filename, filteredOutput, 900);

  return 0;
}//end of main
