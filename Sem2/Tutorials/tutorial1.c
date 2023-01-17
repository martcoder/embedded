#include <stdio.h>

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
  printf("array starts as  %f %f %f %f %f \n\n",fa[0],fa[1],fa[2],fa[3],fa[4]);
  mysort(fa,5);
  printf("array is sorted to become: %f %f %f %f %f\n",fa[0],fa[1],fa[2],fa[3],fa[4]);

  int buffer[5] = {0,0,0,0,0};
  int bufferLength = sizeof(buffer) / sizeof(buffer[0]);
  int newData = 1;
  int location = bufferLength - 1; // starting location inthe circular buffer
  while(newData != 0){
    scanf("%d", &newData);
    location = reverseCircBuffer(newData, buffer, bufferLength, location);
    printf("Circular buffer is now %d %d %d %d %d\n\n",buffer[0],buffer[1],buffer[2],buffer[3],buffer[4]);
  }

  printf("Goodbye\n");

return 0;
}
