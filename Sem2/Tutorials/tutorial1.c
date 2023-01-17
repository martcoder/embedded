#include <stdio.h>
#include <stdlib.h>

float mymedian(float * floatArr, int size){
  if( (size % 2) == 0){ // if even number of elements
    return (floatArr[((size/2)-1)] + floatArr[(size/2)] ) / 2.0; // return avg of two middle elements
  }
  else{
    return  floatArr[size/2]; // C rounds down for integer division so this will choose the middle element. 
  }
}

struct Stats{ float minimum; float maximum; float rangeimum; float median; };

struct Stats mystats(float * elementsArr, int size){
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
  printf("To use default array of floats, press d then Enter. To input your own values, press v then Enter : ");
  char c;
  scanf("%c", &c);
  float * fa;
  int size = 0;
  if( c == 'd'){
    fa = malloc(sizeof(float) * 5);
    fa[0] = 0.7; fa[1] = 0.2; fa[2] = 0.9; fa[3] = 1.2; fa[4] = 0.4;
    size = 5;
    printf("\nThe array consists of:  %f %f %f %f %f \n\n",fa[0],fa[1],fa[2],fa[3],fa[4]);
  }
  else{
    // Read in up to 10 float values
    float floatarr[10];
    int counter = 0;
    printf("Enter 10 or less separate float values, to populate an array...\nto finish populating write -1 and Enter\n");
    float toread = 1.0;
    while( (toread != -1.0) && (counter < 10) ){
      printf("Write the next float value for the array, then press Enter : ");
      scanf("%f",&toread);
      floatarr[counter] = toread;
      counter++;
    }
    counter--; // to omit the -1 that got stored...
    fa =  malloc(sizeof(float) * counter);
    size = counter;
    int inc= 0;
    // now populate a float array from the entered values...
    printf("\n\n The array consists of:\n");
    for(inc = 0; inc < counter; inc++){
      fa[inc] = floatarr[inc];
      printf("%f ",fa[inc]);
    }
  }
  //int size = sizeof(fa) / sizeof(fa[0]);
  printf("\nThe size of array is %d\n",size);
  struct Stats stats = mystats(fa,size);
  stats.median = mymedian(fa,size);
  printf("======\nArray stats: \n - minimum value of %f \n - maximum value of %f \n - range of %f\n \n======\n",stats.minimum,stats.maximum,stats.rangeimum);
  mysort(fa,size);
  stats.median = mymedian(fa,size);
  printf("\nThe array has been sorted in descending order:");
  int raise = 0;
  for(raise = 0; raise < size; raise++){
    printf(" %f ",fa[raise]); 
  }
  printf("\n.... and the median is %f\n",stats.median);

  int buffer[5] = {0,0,0,0,0};
  int bufferLength = sizeof(buffer) / sizeof(buffer[0]);
  int newData = 1;
  int location = bufferLength - 1; // starting location inthe circular buffer
  printf("\n---------\nFollowing this a reverse circular buffer will be experimented with\n");
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
