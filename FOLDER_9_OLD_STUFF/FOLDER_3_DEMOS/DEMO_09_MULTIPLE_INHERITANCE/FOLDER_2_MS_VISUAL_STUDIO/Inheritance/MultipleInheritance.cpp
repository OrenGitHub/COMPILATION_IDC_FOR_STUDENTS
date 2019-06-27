/*****************/
/* INCLUDE FILES */
/*****************/
#include <stdio.h>

class Mother { public:
	int x; int y; Mother() { x = 1; y = 2; }
	virtual void WORK(void)	{ printf("WORK(%d) Mother\n", x); }
	virtual void READ(void) { printf("READ(%d) Mother\n", x); }
	virtual void SWIM(void) { printf("SWIM(%d) Mother\n", x); }
};
class Father { public:
	int u; int v; Father() { u = 3; v = 4;  }
	virtual void DRIVE(void){ printf("DRIVE(%d) Father\n", u); }
	virtual void REST(void)	{ printf("REST(%d)  Father\n", u); }
};
class Son : public Father, public Mother { public:
	int s;	int t; Son()	{ s = 5; t = 6; }
	virtual void REST(void)	{ printf("REST(%d) Son\n",s); }
	virtual void SWIM(void)	{ printf("REST(%d) Son\n",s); }
};
void GO(Mother *m1, Mother *m2,Mother *m3)
{m1->SWIM();m2->SWIM();m3->SWIM();}

void MultipleInheritance(void) {
	Son    *a = new Son;
	Mother *b = new Son;
	Mother *c = new Mother;

	GO(a,b,c);
}


