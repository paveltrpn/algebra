
#include "stdio.h"
#include "math.h"
#include "algebra.h"

#define mrange 3

/*	multidimensional array mapping, array[i][j]
	row-wise (C, C++):
	(0	1)
	(2	3)

	column-wise (Fortran, Matlab):
	(0	2)
	(1	3)
*/

int32_t id_rw(int32_t i, int32_t j, int32_t n) {
	return (i*n + j);
}

int32_t id_cw(int32_t i, int32_t j, int32_t n) {
	return (j*n + i);
}

void mtrx3_copy(const mtrx3_t m, mtrx3_t rt) {
	int32_t i, j;

	for (i = 0; i < mrange; i++) {
		for (j = 0; j < mrange; j++) {
			rt[id_rw(i, j, mrange)] = m[id_rw(i, j, mrange)];
		}
	}
}

void    mtrx3_set(float a00, float a01, float a02,
                  float a10, float a11, float a12,
                  float a20, float a21, float a22,
                  mtrx3_t rt) {
	rt[0] = a00;
	rt[1] = a01;
	rt[2] = a02;

	rt[3] = a10;
	rt[4] = a11;
	rt[5] = a12;

	rt[6] = a20;
	rt[7] = a21;
	rt[8] = a22;
}

void mtrx3_zero(mtrx3_t m) {
	for (int i = 0; i < (mrange*mrange); i++) {
		m[i] = 0.0f;
	}
}

void mtrx3_set_euler(float yaw, float pitch, float roll, mtrx3_t rt) {
	float cosy, siny, cosp, sinp, cosr, sinr;
	
	cosy = cosf(yaw);
	siny = sinf(yaw);
	cosp = cosf(pitch);
	sinp = sinf(pitch);
	cosr = cosf(roll);
	sinr = sinf(roll);

	rt[0] = cosy*cosr - siny*cosp*sinr;
	rt[1] = -cosy*sinr - siny*cosp*cosr;
	rt[2] = siny * sinp;

	rt[3] = siny*cosr + cosy*cosp*sinr;
	rt[4] = -siny*sinr + cosy*cosp*cosr;
	rt[5] = -cosy * sinp;

	rt[6] = sinp * sinr;
	rt[7] = sinp * cosr;
	rt[8] = cosp;
}

void mtrx3_set_axisangl(const vec3_t ax, float phi, mtrx3_t rt) {
	float cosphi, sinphi, vxvy, vxvz, vyvz, vx, vy, vz;

	cosphi = cosf(phi);
	sinphi = sinf(phi);
	vxvy = ax[_XC] * ax[_YC];
	vxvz = ax[_XC] * ax[_ZC];
	vyvz = ax[_YC] * ax[_ZC];
	vx = ax[_XC];
	vy = ax[_YC];
	vz = ax[_ZC];

	rt[0] = cosphi + (1.0-cosphi)*vx*vx;
	rt[1] = (1.0-cosphi)*vxvy - sinphi*vz;
	rt[2] = (1.0-cosphi)*vxvz + sinphi*vy;

	rt[3] = (1.0-cosphi)*vxvy + sinphi*vz;
	rt[4] = cosphi + (1.0-cosphi)*vy*vy;
	rt[5] = (1.0-cosphi)*vyvz - sinphi*vz;

	rt[6] = (1.0-cosphi)*vxvz - sinphi*vy;
	rt[7] = (1.0-cosphi)*vyvz + sinphi*vx;
	rt[8] = cosphi + (1.0-cosphi)*vz*vz;
}

void mtrx3_show(const mtrx3_t m) {
	printf("%5.2f %5.2f %5.2f\n", m[0], m[1], m[2]);
	printf("%5.2f %5.2f %5.2f\n", m[3], m[4], m[5]);
	printf("%5.2f %5.2f %5.2f\n", m[6], m[7], m[8]);
}

void mtrx3_idtt(mtrx3_t rt) {
	int32_t i, j;

	for (i = 0; i < mrange; i++) {
		for (j = 0; j < mrange; j++) {
			if (i == j) {
				rt[id_rw(i, j, mrange)] = 1.0f;
			} else {
				rt[id_rw(i, j, mrange)] = 0.0f;
			}
		}
	}
}

float mtrx3_det(const mtrx3_t m) {
	return m[0]*m[4]*m[8] +
		   m[6]*m[1]*m[5] +
		   m[2]*m[3]*m[7] -
		   m[0]*m[7]*m[5] -
		   m[8]*m[3]*m[1];
}

void mtrx3_mult(const mtrx3_t a, const mtrx3_t b, mtrx3_t rt) {
	int32_t i, j;
	
	for (i = 0; i < mrange; i++) {
		for (j = 0; j < mrange; j++) {
			rt[id_rw(i, j, mrange)] =
				a[id_rw(0, j, mrange)]*b[id_rw(i, 0, mrange)] +
					a[id_rw(1, j, mrange)]*b[id_rw(i, 1, mrange)] +
					a[id_rw(2, j, mrange)]*b[id_rw(i, 2, mrange)];
		}
	}
}

void mtrx3_mult_vec3(const mtrx3_t m, const vec3_t v, vec3_t rt) {
	rt[_XC] = m[0]*v[_XC] + m[1]*v[_YC] + m[2]*v[_ZC];
	rt[_YC] = m[3]*v[_XC] + m[4]*v[_YC] + m[5]*v[_ZC];
	rt[_ZC] = m[6]*v[_XC] + m[7]*v[_YC] + m[8]*v[_ZC];
}

/*
	Где-то здесь ошибка, долго искал
	ничего не вышло и взял код из сети
*/
/*
func mtrx3_lu(m mtrx3_t) (l, u mtrx3_t) {
	var (
		i, j, k int32
		lm, um  mtrx3_t
		sum     float32
	)

	for j = 0; j < 3; j++ {
		um[id_rw(0, j, 3)] = m[id_rw(0, j, 3)]
	}

	for j = 0; j < 3; j++ {
		lm[id_rw(j, 0, 3)] = m[id_rw(j, 0, 3)] / um[id_rw(0, 0, 3)]
	}

	for i = 1; i < 3; i++ {
		for j = i; j < 3; j++ {
			sum = 0.0
			for k = 0; k < i; k++ {
				sum = sum + lm[id_rw(i, k, 3)]*um[id_rw(k, j, 3)]
			}
			um[id_rw(i, j, 3)] = m[id_rw(i, j, 3)] - sum
		}
	}

	for i = 1; i < 3; i++ {
		for j = i; j < 3; j++ {
			if i > j {
				lm[id_rw(j, i, 3)] = 0.0
			} else {
				sum = 0.0
				for k = 0; k < i; k++ {
					sum = sum + lm[id_rw(j, k, 3)]*um[id_rw(k, i, 3)]
				}
				lm[id_rw(j, i, 3)] = (1.0 / um[id_rw(i, i, 3)]) * (m[id_rw(j, i, 3)] - sum)
			}
		}
	}

	return lm, um
}
*/

/*
	Нижнетреугольная (L, lm) матрица имеет единицы по диагонали
*/
void mtrx3_lu(const mtrx3_t m, mtrx3_t lm, mtrx3_t um) {
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

 void mtrx3_ldlt(const mtrx3_t m, mtrx3_t lm, vec3_t dv) {
	int32_t	i, j, k; 
	float sum;

	for (i = 0; i < mrange; i++) {
		for (j = i; j < mrange; j++) {
			sum = m[id_rw(j, i, mrange)];
			for (k = 0; k < i; k++) {
				sum = sum - lm[id_rw(i, k, mrange)]*dv[k]*lm[id_rw(j, k, mrange)];
				if (i == j) {
					if (sum <= 0) {
						printf("mtrx3_ldlt(): matrix is not positive definite \n");
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

void mtrx3_get_transpose(const mtrx3_t m, mtrx3_t rt) {
	int32_t i, j;
	float tmp;

	mtrx3_copy(m, rt);

	for (i = 0; i < mrange; i++) {
		for (j = 0; j < i; j++) {
			tmp = rt[id_rw(i, i, mrange)];
			rt[id_rw(i, j, mrange)] = rt[id_rw(j, i, mrange)];
			rt[id_rw(j, i, mrange)] = tmp;
		}
	}
}

void mtrx3_tranpose_self(mtrx3_t m) {
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

void mtrx3_get_inv(const mtrx3_t m, mtrx3_t rt) {
	mtrx3_t inverse;
	float det, invDet;

	inverse[id_rw(0, 0, 3)] = m[id_rw(1, 1, 3)] * m[id_rw(2, 2, 3)] - m[id_rw(1, 2, 3)] * m[id_rw(2, 1, 3)];
	inverse[id_rw(1, 0, 3)] = m[id_rw(1, 2, 3)] * m[id_rw(2, 0, 3)] - m[id_rw(1, 0, 3)] * m[id_rw(2, 2, 3)];
	inverse[id_rw(2, 0, 3)] = m[id_rw(1, 0, 3)] * m[id_rw(2, 1, 3)] - m[id_rw(1, 1, 3)] * m[id_rw(2, 0, 3)];

	det = m[id_rw(0, 0, 3)] * inverse[id_rw(0, 0, 3)] + m[id_rw(0, 1, 3)] * inverse[id_rw(1, 0, 3)] + 
		  m[id_rw(0, 2, 3)] * inverse[id_rw(2, 0, 3)];

	if (fabs(det) < f_eps) {
		return;
	}

	invDet = 1.0f / det;

	inverse[id_rw(0, 1, 3)] = m[id_rw(0, 2, 3)] * m[id_rw(2, 1, 3)] - m[id_rw(0, 1, 3)] * m[id_rw(2, 2, 3)];
	inverse[id_rw(0, 2, 3)] = m[id_rw(0, 1, 3)] * m[id_rw(1, 2, 3)] - m[id_rw(0, 2, 3)] * m[id_rw(1, 1, 3)];
	inverse[id_rw(1, 1, 3)] = m[id_rw(0, 0, 3)] * m[id_rw(2, 2, 3)] - m[id_rw(0, 2, 3)] * m[id_rw(2, 0, 3)];
	inverse[id_rw(1, 2, 3)] = m[id_rw(0, 2, 3)] * m[id_rw(1, 0, 3)] - m[id_rw(0, 0, 3)] * m[id_rw(1, 2, 3)];
	inverse[id_rw(2, 1, 3)] = m[id_rw(0, 1, 3)] * m[id_rw(2, 0, 3)] - m[id_rw(0, 0, 3)] * m[id_rw(2, 1, 3)];
	inverse[id_rw(2, 2, 3)] = m[id_rw(0, 0, 3)] * m[id_rw(1, 1, 3)] - m[id_rw(0, 1, 3)] * m[id_rw(1, 0, 3)];

	rt[id_rw(0, 0, 3)] = inverse[id_rw(0, 0, 3)] * invDet;
	rt[id_rw(0, 1, 3)] = inverse[id_rw(0, 1, 3)] * invDet;
	rt[id_rw(0, 2, 3)] = inverse[id_rw(0, 2, 3)] * invDet;

	rt[id_rw(1, 0, 3)] = inverse[id_rw(1, 0, 3)] * invDet;
	rt[id_rw(1, 1, 3)] = inverse[id_rw(1, 1, 3)] * invDet;
	rt[id_rw(1, 2, 3)] = inverse[id_rw(1, 2, 3)] * invDet;

	rt[id_rw(2, 0, 3)] = inverse[id_rw(2, 0, 3)] * invDet;
	rt[id_rw(2, 1, 3)] = inverse[id_rw(2, 1, 3)] * invDet;
	rt[id_rw(2, 2, 3)] = inverse[id_rw(2, 2, 3)] * invDet;
}
