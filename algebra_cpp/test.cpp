
#include <iostream>
#include <string>
#include <algorithm>
#include <tuple>

#include "algebra.h"

int main(int argc, char *argv[]) {
	mtrx4_t m, lm, um, mm, m1;
	vec4_t b, X;

	m = mtrx4_t(-14.0f, 1.0f, 5.0f, 1.0f,
				  2.0f, 7.0f, 4.0f, 1.0f,
			     -8.0f, 4.0f, 1.0f, 1.0f,
				  3.0f, 4.0f, 5.0f, 6.0f);

	b = vec4_t(4.7f, 6.1f, 23.1f, 9.0f);

	printf("\n");
	mtrx_show<mtrx4_t, 4>(m);
	printf("\n");

	printf("mtrx_solve_kramer():\n");
	X = mtrx_solve_kramer<mtrx4_t, vec4_t, 4>(m, b);
	vec_show<vec4_t, 4>(X);
	printf("\n");

	printf("mtrx_solve_gauss():\n");
	X = mtrx_solve_gauss<mtrx4_t, vec4_t, 4>(m, b);
	vec_show<vec4_t, 4>(X);
	printf("\n");

	printf("mtrx_det_lu():\n");
	printf("  %.f \n\n", mtrx_det_lu<mtrx4_t, 4>(m));
	
	printf("mtrx_insert_cmn():\n");
	m = mtrx_insert_cmn<mtrx4_t, vec4_t, 4>(m, X, 2);
	mtrx_show<mtrx4_t, 4>(m);
	printf("\n");
/*
	auto ret = mtrx_lu<mtrx4_t, 4>(m);

	lm = std::get<0>(ret);
	mtrx_show<mtrx4_t, 4>(lm);
	printf("\n");

	um = std::get<1>(ret);
	mtrx_show<mtrx4_t, 4>(um);
	printf("\n");

	mm = mtrx_mult<mtrx4_t, 4>(um, lm);

	mtrx_show<mtrx4_t, 4>(mm);
	printf("\n");
*/


	return 0;
}
