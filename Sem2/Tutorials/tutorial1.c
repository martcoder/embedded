#include <stdio.h>

struct Stats{ float minimum; float maximum; float rangeimum; };

struct Stats mystats(float * elementsArr){
  int size = sizeof(elementsArr) / sizeof(elementsArr[0]);
  float min, max, range;
  // Initialise min to an actual element in the array because otherwise it will
  // ...be initialised to 0 which may be smaller than any element
  min = elementsArr[0]; 
  max = min; // Similarly initialise max to an actual element in the array. 
  int c;
  for(c = 0; c < size; c++){
    if( elementsArr[c] < min){
      min = elementsArr[c];
    }
    if( elementsArr[c] > max){
      max = elementsArr[c];
    }
  }//end of for loop

  range = max - min;

  struct Stats returner = { .minimum = min, .maximum = max, .rangeimum = range };
  return returner; 
}

int reverseCircBuffer(int newData, int* buffer, int bufferLength, int location){

  buffer[location] = newData;
  location++;
  location = (location + (bufferLength-2)) % bufferLength;
  return location;
}

float* mysort(float* farray, int L){

 float temp = 0;
 int c = 0;
 int sorted = 0;
 while(!sorted){
   sorted = 1;
   for(c = 0; c < (L-1);c++){
     if(farray[c] < farray[c+1]){
       sorted = 0;
       temp = farray[c];
       farray[c] = farray[c+1];
       farray[c+1] = temp;
     }
   }
 }
}

int main(){
  float fa[5] = {0.7,0.2,0.9,1.2,0.4};
  struct Stats stats = mystats(fa);
  printf("\nThe array consists of:  %f %f %f %f %f \n\n",fa[0],fa[1],fa[2],fa[3],fa[4]);
  printf("======\nArray stats: \n - minimum value of %f \n - maximum value of %f \n - range of %f\n======\n",stats.minimum,stats.maximum,stats.rangeimum);
  mysort(fa,5);
  printf("\nThe array has been sorted in descending order: %f %f %f %f %f\n",fa[0],fa[1],fa[2],fa[3],fa[4]);

  int buffer[5] = {0,0,0,0,0};
  int bufferLength = sizeof(buffer) / sizeof(buffer[0]);
  int newData = 1;
  int location = bufferLength - 1; // starting location inthe circular buffer
  printf("\n----------\n\nTo exit, write 0 and press Enter...\n");

  while(newData != 0){
    printf("Please write an integer number and press Enter: ");
    scanf("%d", &newData);
    location = reverseCircBuffer(newData, buffer, bufferLength, location);
    printf("Circular buffer is now %d %d %d %d %d\n",buffer[0],buffer[1],buffer[2],buffer[3],buffer[4]);
  }

  printf("\n\n*******************\nGoodbye\n*****************\n\n\n");

return 0;
}
