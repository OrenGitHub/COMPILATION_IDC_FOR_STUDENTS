/*****************/
/* INCLUDE FILES */
/*****************/
#include <stdio.h>

class Son { public:
	        void WALK(void){ printf("WALKING\n"); }
	virtual void RUN(void) { printf("RUNNING\n"); }
};
void SimpleInheritance(void)
{
	Son *a = NULL;

	a->WALK();
	a->RUN();
}


