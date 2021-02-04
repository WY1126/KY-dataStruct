#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void loveYou(int n) {
	int i = 1;
	while (i <=n){
		printf("I Love You %d\n",i);
		i++;
	}
	printf("I Love You More Than %d\n", n);
}

int main(int argc, char *argv[]) {
	loveYou(3000);
	return 0;
}
