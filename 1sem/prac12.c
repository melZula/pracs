#include <stdio.h>
#include <stdlib.h>
 //./prac12 6 3 > prac12.out
 
void main(int argc, char **argv) 
{	
	  FILE *fout;

  fout = fopen("prac12.out", "w");
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    fprintf(fout, "%d", a + b);
    
}

