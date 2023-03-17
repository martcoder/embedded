#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
//ref https://stackoverflow.com/questions/5141960/get-the-current-time-in-c
float lp_denominator[17] = {1.0f, -5.3263f, 14.9989f, -28.3719f, 39.7005f, -43.0924f, 37.2584f, -26.0312f, 14.7901f, -6.8332f, 2.5516f, -0.7602f, 0.1768f, -0.0310f, 0.0039f, -0.0003f, 0.0f};
float lp_numerator[17] = { 0.0f, 0.0f, 0.0001f, 0.0003f, 0.0009f, 0.0022f, 0.0041f, 0.0059f, 0.0066f, 0.0059f, 0.0041f, 0.0022f, 0.0009f, 0.0003f, 0.0001f, 0.0f, 0.0f  };

float yMinus[15]; //global
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

void doIIR(float * signalValuesLast16, float * currentOutput, int outputIndex){ //pass in last 16 values of signal

 float result = 0.0f;
 int c = 0;
 for(c=0; c < 16; c++){ 
   currentOutput[outputIndex] += lp_numerator[c] * signalValuesLast16[c]; 
 }
 
 for(c=1; c < 16; c++){
   currentOutput[outputIndex] += lp_denominator[c] * yMinus[ (yMinusOldest + c-1) % 15 ]; // where yMinus[0] is y[n-1]
   yMinus[c-1] = 0.0f; // cheeky initialisation also using this loop
 }
 
 // CIRCULAR BUFFER HOLDING yMinus values
 // Now update the previous y values, overwriting the oldest with latest
  // and update the index holding the oldest
  yMinus[yMinusOldest] = currentOutput[outputIndex]; 
  yMinusOldest++; 
  if( yMinusOldest > 14 ){//yMinus holds 15 elements
    //reset 
    yMinusOldest = 0;
  }
}

int main(){
 currentOutput = 0.0f;
 yMinusOldest = 0; //initialise yMinus oldest index to start at 0 

 //construct signal to have 900 elements
 float filteredOutput[900];
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
   }

   avg = avg / 900.0;
   for(c = 0; c < 900;c++){ 
     constructedSignal[c] -= avg;
   }


  //latestValueInSignal = &(sig[0]); 
  // let's do this!
  int ir = 0;
  for(ir=0; ir< 900-16; ir++){ // call iir for each value of the signal!!! 
    doIIR(constructedSignal,filteredOutput,ir);
  }
  // Let's see if our signal has been low pass filtered!!! 

  char filename[1024];
  time_t mytime = time(NULL);
  char * time_str = ctime(&mytime);
  time_str[strlen(time_str)-1] = '\0';
  strcat(filename,time_str);
  strcat(filename,"iirFilteredData.data");  

 writeDataToFile("constructedSignal", constructedSignal, 900);

 //ref https://stackoverflow.com/questions/308695/how-do-i-concatenate-const-literal-strings-in-c
  writeDataToFile(filename, filteredOutput, 900);


  return 0;
}//end of main
