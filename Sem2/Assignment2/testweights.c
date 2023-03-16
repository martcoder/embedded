



struct section{
 float * numerator;
 float * denominator;
 float gain;
 float output;
};


float lp_sections[2,2];
lp_sections[0][0] = 1.0f; //b0
lp_sections[0][1] = 1.0f; // b1
lp_sections[0][2] = 0.0f; //b2
lp_sections[0][3] = 1.f;  //a0
lp_sections[0][4] = 0.0000000000005f; //a1
lp_sections[0][5] = 0.0f;

float lp_denominator[17] = {1.0f, -5.3263f, 14.9989f, -28.3719f, 39.7005f, -43.0924f, 37.2584f, -26.0312f, 14.7901f, -6.8332f, 2.5516f, -0.7602f, 0.1768f, -0.0310f, 0.0039f, -0.0003f, 0.0f};
float lp_numerator[3] = { 0.0f, 0.0f, 0.0001f, 0.0003f, 0.0009f, 0.0022f, 0.0041f, 0.0059f, 0.0066f, 0.0059f, 0.0041f, 0.0022f, 0.0009f, 0.0003f, 0.0001f, 0.0f, 0.0f  };


float yMinus[15]; //global
float * yMinusOldest; // global pointer to oldest position in yMinus array
float * yMinusBeginning; // global pointer to keep track of start of yMinus
float currentOutput;

void doIIR(float * signalValues, float * currentOutput){ //pass in last 16 values of signal

 float result = 0.0f;
 int c = 0;
 for(c=0; c < 16; c++){ 
   result += lp_numerator[c] * signalValues[c]; 
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
  if( (yMinusBeginning + yMinusOldest) > 16 ){
    //reset 
    yMinusOldest = yMinusBeginning;
  }
}

int main(){
 currentOutput = 0.0f;
 yMinusOldest = &yMinus; //initialise the yMinus pointer to point to yMinus beginning
 yMinusBeginning = &yMinus; // initialise this pointer to point to the start of yMinus
 //construct signal to have 900 elements
 float sig[9] = {1.0f, 5.0f, 4.0f, 1.0f, 6.0f, 7.0f, 8.0f, 3.0f, 4.0f};
 int i = 0;
 int idLength = 9;
 int nine = 0;
    	while(c < 100){ //100 times
        	for(nine = 0; nine < idLength; nine++){
           	 sig[i+nine] = sig[nine];
        	}
        	c++;
        	i = i + 9;
    		}
	}

  // let's do this!
  doIIR(&sig,&currentOutput);

  // Let's see if our signal has been low pass filtered!!! 

  


  return 0;
}//end of main
