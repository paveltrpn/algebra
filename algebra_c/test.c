
#include "stdio.h"
#include "algebra.h"

int main(int argc, char *argv[]) {
	mtrx3_t m, lm, um, mm;
    mtrxC_t cm = {0};

	mtrx3_zero(lm);
	mtrx3_zero(um);

	mtrx3_set(-10.0, 1.0, 5.0,
				2.0, 7.0, 4.0,
			   -8.0, 4.0, 1.0, m);

	mtrx3_show(m);
	printf("\n");

	mtrx3_lu(m, lm, um);

	mtrx3_show(lm);
	printf("\n");

	mtrx3_show(um);
	printf("\n");

	mtrx3_mult(um, lm, mm);

	mtrx3_show(mm);
	printf("\n");

	mtrxC_allocate(8,&cm);
	mtrxC_idtt(cm);
	mtrxC_show(cm);
	mtrxC_free(&cm);
	return 0;
}