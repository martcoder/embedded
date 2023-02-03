#include <stdio.h>
#include <stdlib.h>

int main(){

 float * u;
 u = (float*) malloc( sizeof(float) * 3 );
 u[0] = 2;
 u[1] = 4;
 u[2] = 6;

 printf("first val is %f and 2nd value is %f",u[0],*(u+1));

}
