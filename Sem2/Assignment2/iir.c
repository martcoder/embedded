#include <stdio.h>
#include <stdlib.h>

float signal[1024];
float filteredSig[1024];

float sectionPointers[8];

float numerator[3];
float denominator[3];
float gain;

float y, yMinusOne, yMinusTwo, x, xMinusOne, xMinusTwo;

struct section{
 float numerator[3];
 float denominator[3];
 float gain;
 float output;
};

void initialiseSection(section * givenSection, float * numerator, float * denominator, float * gain){
 int c = 0;
 for(c=0;c<3;c++){
  givenSection->numerator[c] = numerator[c];
  givenSection->denominator[c] = denominator[c];
  givenSection->gain = *gain;
 }
}

float differenceEquation(float y, float yMinusOne, float yMinusTwo, float x, float xMinusOne, float xMinusTwo){
 return 
}

void iir_filter( float * sectionPointers, int numSections, float * signal  ){
 int c = 0;
 int sigInd = 2;
 yMinusOne = 0;
 yMinusTwo = 0;
 for(c = 0; c < numSections; c++){
  (*sectionPointers)[c]->output += (*sectionPointers)[c]->numerator[0] * signal[sigInd];
  (*sectionPointers)[c]->output += (*sectionPointers)[c]->numerator[1] * signal[sigInd-1];
  (*sectionPointers)[c]->output += (*sectionPointers)[c]->numerator[2] * signal[sigInd-2];
  (*sectionPointers)[c]->output -= (*sectionPointers)[c]->denominator[1] * yMinusOne;
  (*sectionPointers)[c]->output -= (*sectionPointers)[c]->denominator[2] * yMinusTwo;
  (*sectionPointers)[c]->output /= (*sectionPointers)[c]->denominator[0];
  (*sectionPointers)[c]->output *= (*sectionPointers)[c]->gain;
 }

 yMinusOne = 

}



int main(){

 section section1;
 numerator[0] = 1; numerator[1] = 2; numerator[2] = 1; 
 denominator[0] = 0.5; denominator[1] = 0.12; denominator[2] = 0.35; 
 gain = 0.8;
 initialiseSection(&section1, numerator, denominator, &gain);
 sectionPointers[0] = &section1;
 section section2;
 denominator[0] = 0.2; denominator[1] = 0.16; denominator[2] = 1.6;
 initialiseSection(&section2, numerator, denonminator); 
 sectionPointers[1] = &section2;

 // etc etc do for all sections....

 int c = 0;
 for(c = 0; c < 1024; c++){
  signal[c] = c % 10;
 }

 iir_filter(&sectionPointers,8,&signal);

 printf("Signal just got filtered.....\n");

 return 0;
}
