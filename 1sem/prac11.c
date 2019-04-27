#include <stdio.h>
#include <math.h>

struct figure
{
	int x1, y1, x2, y2, x3, y3;
};

float sq(struct figure f)
{
	int nx1 = f.x1 - f.x2;
	int ny1 = f.y1 - f.y2;
	int nx3 = f.x3 - f.x2;
	int ny3 = f.y3 - f.y2;
	float l1 = sqrt(nx1*nx1 + ny1*ny1);
	float l2 = sqrt(nx3*nx3 + ny3*ny3);
	return (l1 * sqrt(l2*l2 - nx3*nx3));
}
float per(struct figure f)
{
	int nx1 = f.x1 - f.x2;
	int ny1 = f.y1 - f.y2;
	int nx3 = f.x3 - f.x2;
	int ny3 = f.y3 - f.y2;
	float l1 = sqrt(nx1*nx1 + ny1*ny1);
	float l2 = sqrt(nx3*nx3 + ny3*ny3);
	return (2*(l1+l2));
}
