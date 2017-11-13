#include <stdio.h>

int main(void) {
	int i;

	for(i = 1; i<= 100; i++) {

		if((i%3 == 0) && (i%5 == 0)){
			printf("I'm a multiple of 3 && 5!");
		}
	
		if(i%3 == 0) {
			printf("I'm a multiple of 3!");
		}

        else if(i%5 == 0) {
			printf("I'm a multiple of 5!");
		}

		else {
			 printf("%d", i);
		}
	   
	}

	return 0;
}
