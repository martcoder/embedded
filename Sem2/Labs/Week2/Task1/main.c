#include <stdio.h>

/*
 * main.c
 */
int main(void) {

	int c = 0;
	int holder[10] = {0,0,0,0,0,0,0,0,0,0};
	int counters[10] = {0,0,0,0,0,0,0,0,0,0};
	for(c = 0; c < 10; c++){
		printf("\nPlease enter an integer then press Enter : ");
		scanf("%d",&holder[c]);
		counters[holder[c]] = counters[holder[c]] + 1;
	}

	int e = 0;
	printf("The array now consists of:\n");
	for(e=0;e<10;e++){
		printf(" %d",holder[e]);
	}
	e = 0;
		printf("\nThe count of array now consists of:\n");
		for(e=0;e<10;e++){
			printf(" %d",counters[e]);
		}

	c = 0;
	int d = 0;
	printf("\n\nNumber    Times    histogram\n");
	for(c=0; c<10; c++){
		if(counters[c] > 0){
			printf("\n\n%d         %d          |",c,counters[c]);
			for(d=0;d < counters[c];d++){
				printf("*");
			}
		}
	}

	return 0;
}
