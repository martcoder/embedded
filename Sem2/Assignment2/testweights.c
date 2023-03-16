#include <stdio.h>
#include <stdlib.h>

float lp_denominator[17] = {1.0f, -5.3263f, 14.9989f, -28.3719f, 39.7005f, -43.0924f, 37.2584f, -26.0312f, 14.7901f, -6.8332f, 2.5516f, -0.7602f, 0.1768f, -0.0310f, 0.0039f, -0.0003f, 0.0f};
float lp_numerator[17] = { 0.0f, 0.0f, 0.0001f, 0.0003f, 0.0009f, 0.0022f, 0.0041f, 0.0059f, 0.0066f, 0.0059f, 0.0041f, 0.0022f, 0.0009f, 0.0003f, 0.0001f, 0.0f, 0.0f  };

float yMinus[15]; //global
float * yMinusOldest; // global pointer to oldest position in yMinus array
float * yMinusBeginning; // global pointer to keep track of start of yMinus
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

void doIIR(float * signalValuesLast16, float * currentOutput){ //pass in last 16 values of signal

 float result = 0.0f;
 int c = 0;
 for(c=0; c < 16; c++){ 
   result += lp_numerator[c] * signalValuesLast16[c]; 
 }
 for(c=1; c < 16; c++){
   (*currentOutput) += lp_denominator[c] * yMinus[c-1]; // where yMinus[1] is y[n-1]
   yMinus[c-1] = 0.0f; // cheeky initialisation also using this loop
 }

 // CIRCULAR BUFFER HOLDING yMinus values
 // Now update the previous y values, overwriting the oldest with latest
  // by updating the pointer that points to the oldest
  *yMinusOldest = (*currentOutput); 
  yMinusOldest++; 
  if( ( (float) (yMinusOldest - yMinusBeginning) ) > 16.0f ){
    //reset 
    yMinusOldest = yMinusBeginning;
  }
}

int main(){
 currentOutput = 0.0f;
 yMinusOldest = &(yMinus[0]); //initialise the yMinus pointer to point to yMinus beginning
 yMinusBeginning = &(yMinus[0]); // initialise this pointer to point to the start of yMinus
 //construct signal to have 900 elements
 float filteredOutput[900];
 float sig[9] = {1.0f, 5.0f, 4.0f, 1.0f, 6.0f, 7.0f, 8.0f, 3.0f, 4.0f};
 int i = 0;
 int idLength = 9;
 int c = 0;
 int nine = 0;
    	while(c < 100){ //100 times
        	for(nine = 0; nine < idLength; nine++){
           	 sig[i+nine] = sig[nine];
        	}
        	c++;
        	i = i + 9;
	}

  latestValueInSignal = &(sig[0]); 
  // let's do this!
  int ir = 0;
  for(ir=0; ir< 900/16; ir+=16){ // call iir for each value of the signal!!! 
    doIIR(latestValueInSignal,&currentOutput);
  }
  // Let's see if our signal has been low pass filtered!!! 

  writeDataToFile("iirFiltered.data", &(filteredOutput[0]), 900);


  return 0;
}//end of main
