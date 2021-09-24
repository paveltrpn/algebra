
#include "stdio.h"
#include "math.h"
#include "algebra.h"

#define mrange 4

void mtrx4_copy(const mtrx4_t m, mtrx4_t rt) {
    int32_t i, j;
	int32_t n = 4;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			rt[id_rw(i, j, n)] = m[id_rw(i, j, n)];
		}
	}
}

void mtrx4_zero(mtrx4_t m) {
    for (int i = 0; i < 15; i++) {
		m[i] = 0.0f;
	}
}

void mtrx4_set(float a00, float a01, float a02, float a03,
               float a10, float a11, float a12, float a13,
               float a20, float a21, float a22, float a23,
               float a30, float a31, float a32, float a33,
               mtrx3_t rt) {
    rt[0] = a00;
	rt[1] = a01;
	rt[2] = a02;
    rt[3] = a03;
	
    rt[4] = a10;
	rt[5] = a11;
	rt[6] = a12;
	rt[7] = a13;
	
    rt[8] = a20;
    rt[9] = a21;
    rt[10] = a22;
    rt[11] = a23;

    rt[11] = a30;
    rt[12] = a31;
    rt[14] = a32;
    rt[15] = a33;
}

void mtrx4_show(const mtrx3_t m) {
    printf("%5.2f %5.2f %5.2f %5.2f\n", m[0],  m[1],  m[2],  m[3]);
	printf("%5.2f %5.2f %5.2f %5.2f\n", m[4],  m[5],  m[6],  m[7]);
	printf("%5.2f %5.2f %5.2f %5.2f\n", m[8],  m[9],  m[10], m[11]);
    printf("%5.2f %5.2f %5.2f %5.2f\n", m[11], m[12], m[13], m[15]);
}

void mtrx4_idtt(mtrx3_t rt) {
    int32_t i, j;
	int32_t n = 4;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (i == j) {
				rt[id_rw(i, j, n)] = 1.0f;
			} else {
				rt[id_rw(i, j, n)] = 0.0f;
			}
		}
	}
}

void mtrx4_lu(const mtrx4_t m, mtrx4_t lm, mtrx4_t um) {
    int32_t	i, j, k; 
	float sum = 0;

	for (i = 0; i < mrange; i++) {
		for (k = i; k < mrange; k++) {
			sum = 0;
			for (j = 0; j < i; j++) {
				sum += (lm[id_rw(i, j, mrange)] * um[id_rw(j, k, mrange)]);
			}
			um[id_rw(i, k, mrange)] = m[id_rw(i, k, mrange)] - sum;
		}

		for (k = i; k < mrange; k++) {
			if (i == k) {
				lm[id_rw(i, i, mrange)] = 1.0;
			} else {
				sum = 0;
				for (j = 0; j < i; j++) {
					sum += lm[id_rw(k, j, mrange)] * um[id_rw(j, i, mrange)];
				}
				lm[id_rw(k, i, mrange)] = (m[id_rw(k, i, mrange)] - sum) / um[id_rw(i, i, mrange)];
			}
		}
	}
}

void mtrx4_ldlt(const mtrx4_t m, mtrx4_t lm, vec4_t dv) {
    int32_t	i, j, k; 
	float sum;

	for (i = 0; i < mrange; i++) {
		for (j = i; j < mrange; j++) {
			sum = m[id_rw(j, i, mrange)];
			for (k = 0; k < i; k++) {
				sum = sum - lm[id_rw(i, k, mrange)]*dv[k]*lm[id_rw(j, k, mrange)];
				if (i == j) {
					if (sum <= 0) {
						printf("mtrx4_ldlt(): matrix is not positive definite \n");
						mtrx3_idtt(lm);
						vec3_zero(dv);
						return;
					}
					dv[i] = sum;
					lm[id_rw(i, i, mrange)] = 1.0;
				} else {
					lm[id_rw(j, i, mrange)] = sum / dv[i];
				}
			}
		}
	}
}

void mtrx4_get_transpose(const mtrx4_t m, mtrx4_t rt) {
    int32_t i, j;
	float tmp;

	mtrx4_copy(m, rt);

	for (i = 0; i < mrange; i++) {
		for (j = 0; j < i; j++) {
			tmp = rt[id_rw(i, i, mrange)];
			rt[id_rw(i, j, mrange)] = rt[id_rw(j, i, mrange)];
			rt[id_rw(j, i, mrange)] = tmp;
		}
	}
}

void mtrx4_tranpose_self(mtrx4_t m) {
    int32_t i, j;
	float tmp;

	for (i = 0; i < mrange; i++) {
		for (j = 0; j < i; j++) {
			tmp = m[id_rw(i, i, mrange)];
			m[id_rw(i, j, mrange)] = m[id_rw(j, i, mrange)];
			m[id_rw(j, i, mrange)] = tmp;
		}
	}
}

void mtrx4_get_inv(const mtrx4_t m, mtrx4_t rt){
 	float det;
    int i;

    rt[0] = m[5]  * m[10] * m[15] - 
             m[5]  * m[11] * m[14] - 
             m[9]  * m[6]  * m[15] + 
             m[9]  * m[7]  * m[14] +
             m[13] * m[6]  * m[11] - 
             m[13] * m[7]  * m[10];

    rt[4] = -m[4]  * m[10] * m[15] + 
              m[4]  * m[11] * m[14] + 
              m[8]  * m[6]  * m[15] - 
              m[8]  * m[7]  * m[14] - 
              m[12] * m[6]  * m[11] + 
              m[12] * m[7]  * m[10];

    rt[8] = m[4]  * m[9] * m[15] - 
             m[4]  * m[11] * m[13] - 
             m[8]  * m[5] * m[15] + 
             m[8]  * m[7] * m[13] + 
             m[12] * m[5] * m[11] - 
             m[12] * m[7] * m[9];

    rt[12] = -m[4]  * m[9] * m[14] + 
               m[4]  * m[10] * m[13] +
               m[8]  * m[5] * m[14] - 
               m[8]  * m[6] * m[13] - 
               m[12] * m[5] * m[10] + 
               m[12] * m[6] * m[9];

    rt[1] = -m[1]  * m[10] * m[15] + 
              m[1]  * m[11] * m[14] + 
              m[9]  * m[2] * m[15] - 
              m[9]  * m[3] * m[14] - 
              m[13] * m[2] * m[11] + 
              m[13] * m[3] * m[10];

    rt[5] = m[0]  * m[10] * m[15] - 
             m[0]  * m[11] * m[14] - 
             m[8]  * m[2] * m[15] + 
             m[8]  * m[3] * m[14] + 
             m[12] * m[2] * m[11] - 
             m[12] * m[3] * m[10];

    rt[9] = -m[0]  * m[9] * m[15] + 
              m[0]  * m[11] * m[13] + 
              m[8]  * m[1] * m[15] - 
              m[8]  * m[3] * m[13] - 
              m[12] * m[1] * m[11] + 
              m[12] * m[3] * m[9];

    rt[13] = m[0]  * m[9] * m[14] - 
              m[0]  * m[10] * m[13] - 
              m[8]  * m[1] * m[14] + 
              m[8]  * m[2] * m[13] + 
              m[12] * m[1] * m[10] - 
              m[12] * m[2] * m[9];

    rt[2] = m[1]  * m[6] * m[15] - 
             m[1]  * m[7] * m[14] - 
             m[5]  * m[2] * m[15] + 
             m[5]  * m[3] * m[14] + 
             m[13] * m[2] * m[7] - 
             m[13] * m[3] * m[6];

    rt[6] = -m[0]  * m[6] * m[15] + 
              m[0]  * m[7] * m[14] + 
              m[4]  * m[2] * m[15] - 
              m[4]  * m[3] * m[14] - 
              m[12] * m[2] * m[7] + 
              m[12] * m[3] * m[6];

    rt[10] = m[0]  * m[5] * m[15] - 
              m[0]  * m[7] * m[13] - 
              m[4]  * m[1] * m[15] + 
              m[4]  * m[3] * m[13] + 
              m[12] * m[1] * m[7] - 
              m[12] * m[3] * m[5];

    rt[14] = -m[0]  * m[5] * m[14] + 
               m[0]  * m[6] * m[13] + 
               m[4]  * m[1] * m[14] - 
               m[4]  * m[2] * m[13] - 
               m[12] * m[1] * m[6] + 
               m[12] * m[2] * m[5];

    rt[3] = -m[1] * m[6] * m[11] + 
              m[1] * m[7] * m[10] + 
              m[5] * m[2] * m[11] - 
              m[5] * m[3] * m[10] - 
              m[9] * m[2] * m[7] + 
              m[9] * m[3] * m[6];

    rt[7] = m[0] * m[6] * m[11] - 
             m[0] * m[7] * m[10] - 
             m[4] * m[2] * m[11] + 
             m[4] * m[3] * m[10] + 
             m[8] * m[2] * m[7] - 
             m[8] * m[3] * m[6];

    rt[11] = -m[0] * m[5] * m[11] + 
               m[0] * m[7] * m[9] + 
               m[4] * m[1] * m[11] - 
               m[4] * m[3] * m[9] - 
               m[8] * m[1] * m[7] + 
               m[8] * m[3] * m[5];

    rt[15] = m[0] * m[5] * m[10] - 
              m[0] * m[6] * m[9] - 
              m[4] * m[1] * m[10] + 
              m[4] * m[2] * m[9] + 
              m[8] * m[1] * m[6] - 
              m[8] * m[2] * m[5];

    det = m[0] * rt[0] + m[1] * rt[4] + m[2] * rt[8] + m[3] * rt[12];

    if (det == 0) {
		printf("mtrx4_get_inv(): determinant of inv matrix is zero\n");
		return;
	}
        

    det = 1.0 / det;

    for (i = 0; i < 16; i++)
        rt[i] = rt[i] * det;
}

void mtrx4_get_inv_gauss(const mtrx4_t m, mtrx4_t rt) {
	
}