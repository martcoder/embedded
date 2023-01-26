#include <stdio.h>
/*
 * main.c
 */

void factorial(int * input){
	int returner = 1;
	while((*input) > 0){
		returner = returner * (*input);
		(*input)--;
	}
	(*input) = returner; // Finally set the passed into variable to the correct return value
}

int main(void) {
	
	int value;
	printf("Write an integer then press Enter: ");
	scanf("%d",&value);

	printf("Factorial of %d ",value);
	factorial(&value);
	printf(" is %d",value);

	return 0;
}
