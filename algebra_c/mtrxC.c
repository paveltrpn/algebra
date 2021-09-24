
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "math.h"
#include "algebra.h"

bool mtrxC_assert(const mtrxC_t *m) {
	return 0;
}

bool mtrxC_allocate(int range, mtrxC_t *rt) {
	/*
	if (rt->mtrx != NULL) {
		printf("mtrxC_allocate(): trying allocate not empty matrix!");
		rt->mrange = 0;
		free(rt->mtrx);
	}
	*/

	if (range <= 1) {
		printf("mtrxC_allocate(): trying allocate matrix by zero or negative range!");
		return false;
	}

	rt->mrange = range;

	rt->mtrx = (float *)(malloc(sizeof(float)*range*range));

	return true;
}

void mtrxC_free(mtrxC_t *m) {
	if (m->mtrx == NULL) {
		printf("mtrxC_allocate(): trying delete empty matrix!");
		return;
	}

	m->mrange = 0;

	free(m->mtrx);	

	m->mtrx = NULL;
}

void mtrxC_show(const mtrxC_t m) {
	int32_t i, j;

	for (i = 0; i < m.mrange; i++) {
		for (j = 0; j < m.mrange; j++) {
			printf("%5.2f ",m.mtrx[id_rw(i, j, m.mrange)]);	
		}
		printf("\n");
	}
}

void mtrxC_zero(mtrxC_t m) {
	for (int i = 0; i < m.mrange; i++) {
		m.mtrx[i] = 0.0f;
	}
}

void mtrxC_idtt(mtrxC_t m) {
	int32_t i, j;

	for (i = 0; i < m.mrange; i++) {
		for (j = 0; j < m.mrange; j++) {
			if (i == j) {
				m.mtrx[id_rw(i, j, m.mrange)] = 1.0f;
			} else {
				m.mtrx[id_rw(i, j, m.mrange)] = 0.0f;
			}
		}
	}
}

