#include <stdio.h>
#include <math.h>

// v.14
float z1(a){
	return ( (cos(a)+sin(a)) / (cos(a)-sin(a)) );
}
float z2(a){
	return ( sin(2*a)/cos(2*a) + 1/cos(2*a) );
}
int main(){
	float a;
	scanf("%f", &a);
	printf("%f\n%f\n", z1(a), z2(a));
}
