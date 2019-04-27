#include <stdio.h>

int main(){
	int n;
	int input;
	scanf("%d",&n);
	printf("OCT=%o\n", n );
	printf("HEX=%X\n", n );
	printf("HEX_2=%X\n", n>>2 );
	printf("OCT_neg=%d\n", ~oct(n) );
	printf("HEX_neg=%X\n", ~n );
	printf("AND_hex=%X\n", n&(n>>2) );
}
