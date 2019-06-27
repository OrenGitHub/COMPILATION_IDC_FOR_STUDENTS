/*****************/
/* INCLUDE FILES */
/*****************/
#include <stdio.h>

class Grandfather { public:
	int x;	int y; Grandfather() { x = y = 7; }
	virtual void WALK(void) { printf("WALK(%d) Grandfather\n", x); }
	virtual void RUN(void)	{ printf("RUN(%d)  Grandfather\n", x); }
	virtual void SWIM(void) { printf("SWIM(%d) Grandfather\n", x); }
};
class Father : public Grandfather { public:
	int z; Father() { z = 6; }
	virtual void RUN(void)	{ printf("RUN(%d)  Father\n", z); }
	virtual void WALK(void) { printf("WALK(%d) Father\n", z); }
};
class Son : public Father { public:
	int s; int t; Son() { s = t = 5; }
	virtual void RUN(void) { printf("RUN(%d) Son\n", t); }
};
void SimpleInheritance(void)
{		
	Grandfather *a = new Son;
}


