
#include <iostream>
#include <tuple>
#include <cmath>
#include "algebra.h"

using namespace std;

mtrx2_t::mtrx2_t(float phi) {
	float sinphi = sinf(deg_to_rad(phi));
	float cosphi = cosf(deg_to_rad(phi));

	data[0] = cosphi;
	data[1] = -sinphi;
	data[2] = -sinphi;
	data[3] = cosphi;
}

/* DEBUG !!!! */
mtrx3_t::mtrx3_t(float yaw, float pitch, float roll) {
	float cosy, siny, cosp, sinp, cosr, sinr;
	
	cosy = cosf(deg_to_rad(yaw));
	siny = sinf(deg_to_rad(yaw));
	cosp = cosf(deg_to_rad(pitch));
	sinp = sinf(deg_to_rad(pitch));
	cosr = cosf(deg_to_rad(roll));
	sinr = sinf(deg_to_rad(roll));

	data[0] = cosy*cosr - siny*cosp*sinr;
	data[1] = -cosy*sinr - siny*cosp*cosr;
	data[2] = siny * sinp;

	data[3] = siny*cosr + cosy*cosp*sinr;
	data[4] = -siny*sinr + cosy*cosp*cosr;
	data[5] = -cosy * sinp;

	data[6] = sinp * sinr;
	data[7] = sinp * cosr;
	data[8] = cosp;
}

/* DEBUG !!!! */
mtrx3_t::mtrx3_t(const vec3_t &ax, float phi) {
	float cosphi, sinphi, vxvy, vxvz, vyvz, vx, vy, vz;

	cosphi = cosf(deg_to_rad(phi));
	sinphi = sinf(deg_to_rad(phi));
	vxvy = ax[_XC] * ax[_YC];
	vxvz = ax[_XC] * ax[_ZC];
	vyvz = ax[_YC] * ax[_ZC];
	vx = ax[_XC];
	vy = ax[_YC];
	vz = ax[_ZC];

	data[0] = cosphi + (1.0f-cosphi)*vx*vx;
	data[1] = (1.0f-cosphi)*vxvy - sinphi*vz;
	data[2] = (1.0f-cosphi)*vxvz + sinphi*vy;

	data[3] = (1.0f-cosphi)*vxvy + sinphi*vz;
	data[4] = cosphi + (1.0f-cosphi)*vy*vy;
	data[5] = (1.0f-cosphi)*vyvz - sinphi*vz;

	data[6] = (1.0f-cosphi)*vxvz - sinphi*vy;
	data[7] = (1.0f-cosphi)*vyvz + sinphi*vx;
	data[8] = cosphi + (1.0f-cosphi)*vz*vz;
}

mtrx4_t::mtrx4_t(float yaw, float pitch, float roll) {
	float cosy, siny, cosp, sinp, cosr, sinr;
	
	cosy = cosf(deg_to_rad(yaw));
	siny = sinf(deg_to_rad(yaw));
	cosp = cosf(deg_to_rad(pitch));
	sinp = sinf(deg_to_rad(pitch));
	cosr = cosf(deg_to_rad(roll));
	sinr = sinf(deg_to_rad(roll));

	data[0]  = cosy*cosr - siny*cosp*sinr;
	data[1]  = -cosy*sinr - siny*cosp*cosr;
	data[2]  = siny * sinp;
	data[3]  = 0.0f;
	
	data[4]  = siny*cosr + cosy*cosp*sinr;
	data[5]  = -siny*sinr + cosy*cosp*cosr;
	data[6]  = -cosy * sinp;
	data[7]  = 0.0f;
	
	data[8]  = sinp * sinr;
	data[9]  = sinp * cosr;
	data[10] = cosp;
	data[11] = 0.0f;

	data[12] = 0.0f;
	data[13] = 0.0f;
	data[14] = 0.0f;
	data[15] = 1.0f;
}

mtrx4_t::mtrx4_t(const vec3_t &ax, float phi) {
	float cosphi, sinphi, vxvy, vxvz, vyvz, vx, vy, vz;

	cosphi = cosf(deg_to_rad(phi));
	sinphi = sinf(deg_to_rad(phi));
	vxvy = ax[_XC] * ax[_YC];
	vxvz = ax[_XC] * ax[_ZC];
	vyvz = ax[_YC] * ax[_ZC];
	vx = ax[_XC];
	vy = ax[_YC];
	vz = ax[_ZC];

	data[0]  = cosphi + (1.0-cosphi)*vx*vx;
	data[1]  = (1.0-cosphi)*vxvy - sinphi*vz;
	data[2]  = (1.0-cosphi)*vxvz + sinphi*vy;
	data[3]  = 0.0f;

	data[4]  = (1.0-cosphi)*vxvy + sinphi*vz;
	data[5]  = cosphi + (1.0-cosphi)*vy*vy;
	data[6]  = (1.0-cosphi)*vyvz - sinphi*vz;
	data[7]  = 0.0f;

	data[8]  = (1.0-cosphi)*vxvz - sinphi*vy;
	data[9]  = (1.0-cosphi)*vyvz + sinphi*vx;
	data[10] = cosphi + (1.0-cosphi)*vz*vz;
	data[11] = 0.0f;

	data[12] = 0.0f;
	data[13] = 0.0f;
	data[14] = 0.0f;
	data[15] = 1.0f;
}
		
template <typename mtrxT_t, int mrange>
void mtrx_show(const mtrxT_t &m) {
	for (int i = 0; i < mrange; i++) {
		for (int j = 0; j < mrange; j++) {
			printf(" %5.2f", m[id_rw(i,j,mrange)]);
		}
		cout << "\n";
	}
}
template void mtrx_show<mtrx2_t, 2>(const mtrx2_t &m);
template void mtrx_show<mtrx3_t, 3>(const mtrx3_t &m);
template void mtrx_show<mtrx4_t, 4>(const mtrx4_t &m);

mtrx3_t mtrx_set_yaw(float angl) {
	float sa, ca;
	mtrx3_t rt;

	sa = sinf(deg_to_rad(angl));
	ca = cosf(deg_to_rad(angl));

	rt[0] = ca;   rt[1] = -sa;  rt[2] = 0.0f;
	rt[3] = sa;   rt[4] =  ca;  rt[5] = 0.0f;
	rt[6] = 0.0f; rt[7] = 0.0f; rt[8] = 1.0f;

	return rt;
}

mtrx3_t mtrx_set_pitch(float angl) {
	float sa, ca;
	mtrx3_t rt;

	sa = sinf(deg_to_rad(angl));
	ca = cosf(deg_to_rad(angl));

	rt[0] = 1.0f; rt[1] = 0.0f; rt[2] = 0.0f;
	rt[3] = 0.0f; rt[4] = ca;   rt[5] = -sa;
	rt[6] = 0.0f; rt[7] = sa;   rt[8] = ca;

	return rt;
}

mtrx3_t mtrx_set_roll(float angl)
{
	float sa, ca;
	mtrx3_t rt;

	sa = sinf(deg_to_rad(angl));
	ca = cosf(deg_to_rad(angl));

	rt[0] = ca;   rt[1] = 0.0f; rt[2] = sa;
	rt[3] = 0.0f; rt[4] = 1.0f; rt[5] = 0.0f;
	rt[6] = -sa;  rt[7] = 0.0f; rt[8] = ca;

	return rt;
}

float mtrx_det(const mtrx2_t &m) {
	return m[0]*m[3] - m[1]*m[2];
}

float mtrx_det(const mtrx3_t &m) {
	return m[0]*m[4]*m[8] +
		   m[6]*m[1]*m[5] +
		   m[2]*m[3]*m[7] -
		   m[0]*m[7]*m[5] -
		   m[8]*m[3]*m[1];
}

float mtrx_det(const mtrx4_t &m) {
	return 1;
}

template <typename mtrxT_t, int mrange>
float	mtrx_det_lu(const mtrxT_t &m) {
	int i;
	tuple<mtrxT_t, mtrxT_t> lu;
	float l_det, u_det;

	lu = mtrx_lu<mtrxT_t, mrange>(m);

	l_det = get<0>(lu)[0];
	u_det = get<1>(lu)[0];

	for (i = 1; i < mrange; i++) {
		l_det *= get<0>(lu)[id_rw(i, i, mrange)];
		u_det *= get<1>(lu)[id_rw(i, i, mrange)];
	}

	return l_det*u_det;
}
template float mtrx_det_lu<mtrx2_t, 2>(const mtrx2_t &m);
template float mtrx_det_lu<mtrx3_t, 3>(const mtrx3_t &m);
template float mtrx_det_lu<mtrx4_t, 4>(const mtrx4_t &m);

template <typename mtrxT_t, int mrange>
mtrxT_t mtrx_mult(const mtrxT_t &a, const mtrxT_t &b) {
	mtrxT_t rt;
	int32_t i, j, k;
	float tmp;
	
	for (i = 0; i < mrange; i++) {
		for (j = 0; j < mrange; j++) {
			tmp = 0;
			for (k = 0; k < mrange; k++) {
				tmp = tmp + a[id_rw(k, j, mrange)]*b[id_rw(i, k, mrange)];
			}
			rt[id_rw(i, j, mrange)] = tmp;	
		}
	}

	return rt;
}
template mtrx2_t mtrx_mult<mtrx2_t, 2>(const mtrx2_t &a, const mtrx2_t &b);
template mtrx3_t mtrx_mult<mtrx3_t, 3>(const mtrx3_t &a, const mtrx3_t &b);
template mtrx4_t mtrx_mult<mtrx4_t, 4>(const mtrx4_t &a, const mtrx4_t &b);

template <typename mtrxT_t, typename vecT_t, int range>
vecT_t	mtrx_mult_vec(const mtrxT_t &m, const vecT_t &v) {
	vecT_t rt;
	int32_t i, j;
	float tmp;
	
	for (i = 0; i < range; i++) {
		tmp = 0;
		for (j = 0; j < range; j++) {
			tmp = tmp + m[id_rw(i, j, range)]*v[j];	
		}
		rt[i] = tmp;
	}

	return rt;
}
template vec2_t mtrx_mult_vec<mtrx2_t, vec2_t, 2>(const mtrx2_t &m, const vec2_t &v);
template vec3_t mtrx_mult_vec<mtrx3_t, vec3_t, 3>(const mtrx3_t &m, const vec3_t &v);
template vec4_t mtrx_mult_vec<mtrx4_t, vec4_t, 4>(const mtrx4_t &m, const vec4_t &v);

vec3_t mtrx_mult_vec(const mtrx4_t &m, const vec3_t &v) {
	vec3_t rt;

	rt[_XC] = m[0]*v[_XC] + m[1]*v[_YC] + m[2]* v[_ZC] + m[3];
	rt[_YC] = m[4]*v[_XC] + m[5]*v[_YC] + m[6]* v[_ZC] + m[7];
	rt[_ZC] = m[8]*v[_XC] + m[9]*v[_YC] + m[10]*v[_ZC] + m[11];

	return rt;
}

/*
	Где-то здесь ошибка, долго искал
	ничего не нашел и взял код из сети
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

template <typename mtrxT_t, int mrange>
tuple<mtrxT_t, mtrxT_t> mtrx_lu(const mtrxT_t &m) {
	mtrxT_t lm, um;
	int32_t	i, j, k; 
	float sum;
	
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

	return {lm, um};
}
template tuple<mtrx2_t, mtrx2_t> mtrx_lu<mtrx2_t, 2>(const mtrx2_t &m);
template tuple<mtrx3_t, mtrx3_t> mtrx_lu<mtrx3_t, 3>(const mtrx3_t &m);
template tuple<mtrx4_t, mtrx4_t> mtrx_lu<mtrx4_t, 4>(const mtrx4_t &m);


template <typename mtrxT_t, typename vecT_t, int mrange>
tuple<mtrxT_t, vecT_t> mtrx_ldlt(const mtrxT_t &m) {
	mtrxT_t lm;
	vecT_t dv;
	int32_t	i, j, k; 
	float sum;
	
	for (i = 0; i < mrange; i++) {
		for (j = i; j < mrange; j++) {
			sum = m[id_rw(j, i, mrange)];
			for (k = 0; k < i; k++) {
				sum = sum - lm[id_rw(i, k, mrange)]*dv[k]*lm[id_rw(j, k, mrange)];
				if (i == j) {
					if (sum <= 0) {
						cout << "mtrx_ldlt(): matrix is not positive definite \n" ;
						return {mtrxT_t(), vecT_t()};
					}
					dv[i] = sum;
					lm[id_rw(i, i, mrange)] = 1.0;
				} else {
					lm[id_rw(j, i, mrange)] = sum / dv[i];
				}
			}
		}
	}

	return {lm, dv};
}
template tuple<mtrx2_t, vec2_t> mtrx_ldlt<mtrx2_t, vec2_t, 2>(const mtrx2_t &m);
template tuple<mtrx3_t, vec3_t> mtrx_ldlt<mtrx3_t, vec3_t, 3>(const mtrx3_t &m);
template tuple<mtrx4_t, vec4_t> mtrx_ldlt<mtrx4_t, vec4_t, 4>(const mtrx4_t &m);

template <typename mtrxT_t, int mrange>
mtrxT_t	mtrx_transpose(const mtrxT_t &m) {
	mtrxT_t rt;
	int32_t i, j;
	float tmp;
	
	rt = m;

	for (i = 0; i < mrange; i++) {
		for (j = 0; j < i; j++) {
			tmp = rt[id_rw(i, i, mrange)];
			rt[id_rw(i, j, mrange)] = rt[id_rw(j, i, mrange)];
			rt[id_rw(j, i, mrange)] = tmp;
		}
	}

	return rt;
}
template mtrx2_t mtrx_transpose<mtrx2_t, 2>(const mtrx2_t &m);
template mtrx3_t mtrx_transpose<mtrx3_t, 3>(const mtrx3_t &m);
template mtrx4_t mtrx_transpose<mtrx4_t, 4>(const mtrx4_t &m);

mtrx2_t	mtrx_invert(const mtrx2_t &m) {
	float det = mtrx_det(m);

	if (fabs(det) < f_eps) {
		cout << "mtrx_invert(): determinant is a zero!" << "\n";
		return mtrx2_t();
	}

	return mtrx2_t(m[3], -m[1]/det, -m[2]/det, m[0]/det);
}

mtrx3_t	mtrx_invert(const mtrx3_t &m) {
	mtrx3_t inverse, rt;
	float det, invDet;

	inverse[0] = m[4] * m[8] - m[5] * m[7];
	inverse[3] = m[5] * m[6] - m[3] * m[8];
	inverse[6] = m[3] * m[7] - m[4] * m[6];

	det = m[0] * inverse[0] + m[1] * inverse[3] + 
		  m[2] * inverse[6];

	if (fabs(det) < f_eps) {
		cout << "mtrx_invert(): determinant is a zero!" << "\n";
		return mtrx3_t();
	}

	invDet = 1.0f / det;

	inverse[1] = m[2] * m[7] - m[1] * m[8];
	inverse[2] = m[1] * m[5] - m[2] * m[4];
	inverse[4] = m[0] * m[8] - m[2] * m[6];
	inverse[5] = m[2] * m[3] - m[0] * m[5];
	inverse[7] = m[1] * m[6] - m[0] * m[7];
	inverse[8] = m[0] * m[4] - m[1] * m[3];

	rt[0] = inverse[0] * invDet;
	rt[1] = inverse[1] * invDet;
	rt[2] = inverse[2] * invDet;

	rt[3] = inverse[3] * invDet;
	rt[4] = inverse[4] * invDet;
	rt[5] = inverse[5] * invDet;

	rt[6] = inverse[6] * invDet;
	rt[7] = inverse[7] * invDet;
	rt[8] = inverse[8] * invDet;

	return rt;
}

mtrx4_t mtrx_invert(const mtrx4_t &m) {
	mtrx4_t rt;
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

    rt[9] = -m[0]  * m[9]  * m[15] + 
             m[0]  * m[11] * m[13] + 
             m[8]  * m[1]  * m[15] - 
             m[8]  * m[3]  * m[13] - 
             m[12] * m[1]  * m[11] + 
             m[12] * m[3]  * m[9];

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
		cout << "mtrx_inverse(): determinant of inv matrix is zero\n";
		return mtrx4_t();
	}
      
    det = 1.0f / det;

    for (i = 0; i < 16; i++) {
        rt[i] = rt[i] * det;
	}

	return rt;
}

template <typename mtrxT_t, typename vecT_t, int mrange>
vecT_t mtrx_solve_gauss(const mtrxT_t &m, const vecT_t &v) {
	int i, j, k;
	float t;
    float a[mrange][mrange+1];
    vecT_t rt;
     
    for (i = 0; i < mrange; ++i) {
        for (j = 0; j < mrange; ++j) {
            a[i][j] = m[id_rw(i, j, mrange)];
        	a[i][mrange] = v[i];
		}
    }
    
	/* Pivotisation */
	for (i = 0; i < mrange; i++) {                    
        for (k = i + 1; k < mrange; k++) {
            if (abs(a[i][i]) < abs(a[k][i])) {
                for (j = 0; j <= mrange; j++) {
                    t = a[i][j];
                    a[i][j] = a[k][j];
                    a[k][j] = t;
                }
			}
		}
	}
	
	/* прямой ход */
    for (k = 1; k < mrange; k++) {        
        for (j = k; j < mrange; j++) {
            t = a[j][k-1] / a[k-1][k-1];
            for (i = 0; i < mrange+1; i++) {
                a[j][i] = a[j][i] - t*a[k-1][i];
            }
		}
	}
    
	/* обратный ход */
    for (i = mrange - 1; i >= 0; i--) {                            
        rt[i] = a[i][mrange] / a[i][i];                
        for (j = mrange - 1; j > i; j--) {
            rt[i] = rt[i] - a[i][j] * rt[j] / a[i][i];
		}            
    }

	return rt;
}
template vec2_t mtrx_solve_gauss<mtrx2_t, vec2_t, 2>(const mtrx2_t &m, const vec2_t &v);
template vec3_t mtrx_solve_gauss<mtrx3_t, vec3_t, 3>(const mtrx3_t &m, const vec3_t &v);
template vec4_t mtrx_solve_gauss<mtrx4_t, vec4_t, 4>(const mtrx4_t &m, const vec4_t &v);

template <typename mtrxT_t, typename vecT_t, int mrange>
mtrxT_t mtrx_insert_cmn(const mtrxT_t &m, const vecT_t &v, int cmn) {
	int i, j = 0;
	mtrxT_t rt;
	/*
	for (i = 0; i < mrange; i++) {
		for (j = 0; j < mrange; j++) {
			rt[id_rw(i, j, mrange)] = m[id_rw(i, j, mrange)];

			if (j == cmn) {
				rt[id_rw(i, j, mrange)] = v[i];
			}
		}
	}
	*/
	rt = m;

	for (i = cmn; i < mrange*mrange; i += mrange) {
		rt[i] = v[j++];
	}

	return rt;
}
template mtrx2_t mtrx_insert_cmn<mtrx2_t, vec2_t, 2>(const mtrx2_t &m, const vec2_t &v, int row);
template mtrx3_t mtrx_insert_cmn<mtrx3_t, vec3_t, 3>(const mtrx3_t &m, const vec3_t &v, int row);
template mtrx4_t mtrx_insert_cmn<mtrx4_t, vec4_t, 4>(const mtrx4_t &m, const vec4_t &v, int row);

template <typename mtrxT_t, typename vecT_t, int mrange>
vecT_t 	mtrx_solve_kramer(const mtrxT_t &m, const vecT_t &v) {
	int i;
	float det;
	mtrxT_t kr_mtrx;
	vecT_t rt;

	det = mtrx_det_lu<mtrxT_t, mrange>(m);

	if (abs(det) < f_eps) {
		cout << "mtrx_solve_kramer(): system has no solve\n";
		return vecT_t();
	}

	for (i = 0; i < mrange; i++) {
		kr_mtrx = mtrx_insert_cmn<mtrxT_t, vecT_t, mrange>(m, v, i);
		rt[i] = mtrx_det_lu<mtrxT_t, mrange>(kr_mtrx) / det;
	}
	
	return rt;
}
template vec2_t mtrx_solve_kramer<mtrx2_t, vec2_t, 2>(const mtrx2_t &m, const vec2_t &v);
template vec3_t mtrx_solve_kramer<mtrx3_t, vec3_t, 3>(const mtrx3_t &m, const vec3_t &v);
template vec4_t mtrx_solve_kramer<mtrx4_t, vec4_t, 4>(const mtrx4_t &m, const vec4_t &v);