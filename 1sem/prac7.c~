#include <stdio.h>

enum typeofAuto
{
	 CAR = 1, TRUCK, BUS, SPORTCAR
};

struct triangle
{
	int x1, y1, x2, y2, x3, y3;
};


struct fax
{	
	union status
	{
		char st_1[3];
		unsigned int st_2: 1; 
	} ready, lowlevel, damage, nopaper;
};
int main()
{
	enum typeofAuto example;
	example = BUS;
	printf("%d\n", example);

	struct triangle exmp = {1, 1, 2, 5, 5, 3};
	float square = abs((exmp.x1-exmp.x3)*(exmp.y2-exmp.y3)-(exmp.y1-exmp.y3)*(exmp.x2-exmp.x3)) / 2;
	printf("%f\n", square);
	
	struct fax prt;
	int flags;
	scanf("%x", &flags);
	prt.ready.st_2 = flags % 2;
	prt.lowlevel.st_2 = (flags>>1) % 2;
	prt.damage.st_2 = (flags>>2) % 2;
	prt.nopaper.st_2 = (flags>>3) % 2;
	printf("%d %d %d %d\n", prt.nopaper.st_2, prt.damage.st_2, prt.lowlevel.st_2, prt.ready.st_2);
}
