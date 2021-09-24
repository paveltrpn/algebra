package main

import (
	"fmt"
	"math"
)

type mtrx3_t [9]float32

/* func proto

func mtrx3_idtt() (rt mtrx3_t)
func mtrx3_set(m [9]float32) (rt mtrx3_t)
func mtrx3_set_float(a00, a01, a02,
					 a10, a11, a12,
					 a20, a21, a22 float32) (rt mtrx3_t)
func mtrx3_set_euler(yaw, pitch, roll float32) (rt mtrx3_t)
func mtrx3_set_axisangl(ax vec3_t, phi float32) (rt mtrx3_t)
func mtrx3_show(m mtrx3_t)
func mtrx3_det(m mtrx3_t) (rt float32)
func mtrx3_det_lu(m mtrx3_t) (rt float32)
func mtrx3_mult(a, b mtrx3_t) (rt mtrx3_t)
func mtrx3_mult_vec3(m mtrx3_t, v vec3_t) (rt vec3_t)
func mtrx3_lu(m mtrx3_t) (lm, um mtrx3_t)
func mtrx3_ldlt(m mtrx3_t) (lm mtrx3_t, dv vec3_t)
func mtrx3_transpose(m mtrx3_t) (rt mtrx3_t)
func mtrx3_invert(m mtrx3_t) (rt mtrx3_t)
func mtrx3_solve_gauss(m mtrx3_t, v vec3_t) (rt vec3_t)
func mtrx3_insert_cmn(m mtrx3_t, v vec3_t, cmn int32) (rt mtrx3_t)
func mtrx3_solve_kramer(m mtrx3_t, v vec3_t) (rt vec3_t)

*/

func mtrx3_idtt() (rt mtrx3_t) {
	var (
		i, j   int32
		mrange int32 = 3
	)

	for i = 0; i < mrange; i++ {
		for j = 0; j < mrange; j++ {
			if i == j {
				rt[id_rw(i, j, mrange)] = 1.0
			} else {
				rt[id_rw(i, j, mrange)] = 0.0
			}
		}
	}

	return rt
}

func mtrx3_set(m [9]float32) (rt mtrx3_t) {
	var (
		i, j   int32
		mrange int32 = 3
	)

	for i = 0; i < mrange; i++ {
		for j = 0; j < mrange; j++ {
			rt[id_rw(i, j, mrange)] = m[id_rw(i, j, mrange)]
		}
	}

	return rt
}

func mtrx3_set_float(a00, a01, a02,
	a10, a11, a12,
	a20, a21, a22 float32) (rt mtrx3_t) {

	rt[0] = a00
	rt[1] = a01
	rt[2] = a02

	rt[3] = a10
	rt[4] = a11
	rt[5] = a12

	rt[6] = a20
	rt[7] = a21
	rt[8] = a22

	return rt
}

func mtrx3_set_euler(yaw, pitch, roll float32) (rt mtrx3_t) {
	var (
		cosy, siny, cosp, sinp, cosr, sinr float32
	)

	cosy = cosf(yaw)
	siny = sinf(yaw)
	cosp = cosf(pitch)
	sinp = sinf(pitch)
	cosr = cosf(roll)
	sinr = sinf(roll)

	rt[0] = cosy*cosr - siny*cosp*sinr
	rt[1] = -cosy*sinr - siny*cosp*cosr
	rt[2] = siny * sinp

	rt[3] = siny*cosr + cosy*cosp*sinr
	rt[4] = -siny*sinr + cosy*cosp*cosr
	rt[5] = -cosy * sinp

	rt[6] = sinp * sinr
	rt[7] = sinp * cosr
	rt[8] = cosp

	return rt
}

func mtrx3_set_axisangl(ax vec3_t, phi float32) (rt mtrx3_t) {
	var (
		cosphi, sinphi, vxvy, vxvz, vyvz, vx, vy, vz float32
	)

	cosphi = cosf(phi)
	sinphi = sinf(phi)
	vxvy = ax[_XC] * ax[_YC]
	vxvz = ax[_XC] * ax[_ZC]
	vyvz = ax[_YC] * ax[_ZC]
	vx = ax[_XC]
	vy = ax[_YC]
	vz = ax[_ZC]

	rt[0] = cosphi + (1.0-cosphi)*vx*vx
	rt[1] = (1.0-cosphi)*vxvy - sinphi*vz
	rt[2] = (1.0-cosphi)*vxvz + sinphi*vy

	rt[3] = (1.0-cosphi)*vxvy + sinphi*vz
	rt[4] = cosphi + (1.0-cosphi)*vy*vy
	rt[5] = (1.0-cosphi)*vyvz - sinphi*vz

	rt[6] = (1.0-cosphi)*vxvz - sinphi*vy
	rt[7] = (1.0-cosphi)*vyvz + sinphi*vx
	rt[8] = cosphi + (1.0-cosphi)*vz*vz

	return rt
}

func mtrx3_show(m mtrx3_t) {
	fmt.Printf("%5.2f %5.2f %5.2f\n", m[0], m[1], m[2])
	fmt.Printf("%5.2f %5.2f %5.2f\n", m[3], m[4], m[5])
	fmt.Printf("%5.2f %5.2f %5.2f\n", m[6], m[7], m[8])
}

func mtrx3_det(m mtrx3_t) float32 {
	return m[0]*m[4]*m[8] +
		m[6]*m[1]*m[5] +
		m[2]*m[3]*m[7] -
		m[0]*m[7]*m[5] -
		m[8]*m[3]*m[1]
}

func mtrx3_det_lu(m mtrx3_t) (rt float32) {
	const (
		mrange int32 = 3
	)

	var (
		i            int32
		l, u         mtrx3_t
		l_det, u_det float32
	)

	l, u = mtrx3_lu(m)

	l_det = l[0]
	u_det = u[0]

	for i = 1; i < mrange; i++ {
		l_det *= l[id_rw(i, i, mrange)]
		u_det *= u[id_rw(i, i, mrange)]
	}

	return l_det * u_det
}

func mtrx3_mult(a, b mtrx3_t) (rt mtrx3_t) {
	const (
		mrange int32 = 3
	)

	var (
		i, j, k int32
		tmp     float32
	)

	for i = 0; i < mrange; i++ {
		for j = 0; j < mrange; j++ {
			tmp = 0.0
			for k = 0; k < mrange; k++ {
				tmp = tmp + a[id_rw(k, j, mrange)]*b[id_rw(i, k, mrange)]
			}
			rt[id_rw(i, j, mrange)] = tmp
		}
	}

	return rt
}

func mtrx3_mult_vec(m mtrx3_t, v vec3_t) (rt vec3_t) {
	const (
		mrange int32 = 3
	)

	var (
		i, j int32
		tmp  float32
	)

	for i = 0; i < mrange; i++ {
		tmp = 0
		for j = 0; j < mrange; j++ {
			tmp = tmp + m[id_rw(i, j, mrange)]*v[j]
		}
		rt[i] = tmp
	}

	return rt
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
func mtrx3_lu(m mtrx3_t) (lm, um mtrx3_t) {
	const (
		mrange int32 = 3
	)

	var (
		i, j, k int32
		sum     float32
	)

	for i = 0; i < mrange; i++ {
		for k = i; k < mrange; k++ {
			sum = 0
			for j = 0; j < i; j++ {
				sum += (lm[id_rw(i, j, mrange)] * um[id_rw(j, k, mrange)])
			}
			um[id_rw(i, k, mrange)] = m[id_rw(i, k, mrange)] - sum
		}

		for k = i; k < mrange; k++ {
			if i == k {
				lm[id_rw(i, i, mrange)] = 1.0
			} else {
				sum = 0
				for j = 0; j < i; j++ {
					sum += lm[id_rw(k, j, mrange)] * um[id_rw(j, i, mrange)]
				}
				lm[id_rw(k, i, mrange)] = (m[id_rw(k, i, mrange)] - sum) / um[id_rw(i, i, mrange)]
			}
		}
	}

	return lm, um
}

func mtrx3_ldlt(m mtrx3_t) (lm mtrx3_t, dv vec3_t) {
	const (
		mrange int32 = 3
	)

	var (
		i, j, k int32
		sum     float32
	)

	for i = 0; i < mrange; i++ {
		for j = i; j < mrange; j++ {
			sum = m[id_rw(j, i, mrange)]
			for k = 0; k < i; k++ {
				sum = sum - lm[id_rw(i, k, mrange)]*dv[k]*lm[id_rw(j, k, mrange)]
				if i == j {
					if sum <= 0 {
						fmt.Println("mtrx3_ldlt(): mtrx is not positive deﬁnite")
						return mtrx3_idtt(), vec3_set(0.0, 0.0, 0.0)
					}
					dv[i] = sum
					lm[id_rw(i, i, mrange)] = 1.0
				} else {
					lm[id_rw(j, i, mrange)] = sum / dv[i]
				}
			}
		}
	}

	return lm, dv
}

func mtrx3_transpose(m mtrx3_t) (rt mtrx3_t) {
	const (
		mrange int32 = 3
	)

	var (
		i, j int32
		tmp  float32
	)

	rt = m

	for i = 0; i < mrange; i++ {
		for j = 0; j < i; j++ {
			tmp = rt[id_rw(i, i, mrange)]
			rt[id_rw(i, j, mrange)] = rt[id_rw(j, i, mrange)]
			rt[id_rw(j, i, mrange)] = tmp
		}
	}

	return rt
}

func mtrx3_invert(m mtrx3_t) (rt mtrx3_t) {
	var (
		inverse     mtrx3_t
		det, invDet float32
	)

	inverse[0] = m[4]*m[8] - m[5]*m[7]
	inverse[3] = m[5]*m[6] - m[3]*m[8]
	inverse[6] = m[3]*m[7] - m[4]*m[6]

	det = m[0]*inverse[0] + m[1]*inverse[3] +
		m[2]*inverse[6]

	if fabs(det) < f_eps {
		fmt.Println("mtrx_invert(): determinant is a zero!")
		return mtrx3_idtt()
	}

	invDet = 1.0 / det

	inverse[1] = m[2]*m[7] - m[1]*m[8]
	inverse[2] = m[1]*m[5] - m[2]*m[4]
	inverse[4] = m[0]*m[8] - m[2]*m[6]
	inverse[5] = m[2]*m[3] - m[0]*m[5]
	inverse[7] = m[1]*m[6] - m[0]*m[7]
	inverse[8] = m[0]*m[4] - m[1]*m[3]

	rt[0] = inverse[0] * invDet
	rt[1] = inverse[1] * invDet
	rt[2] = inverse[2] * invDet

	rt[3] = inverse[3] * invDet
	rt[4] = inverse[4] * invDet
	rt[5] = inverse[5] * invDet

	rt[6] = inverse[6] * invDet
	rt[7] = inverse[7] * invDet
	rt[8] = inverse[8] * invDet

	return rt
}

func mtrx3_solve_gauss(m mtrx3_t, v vec3_t) (rt vec3_t) {
	const (
		mrange int32 = 3
	)

	var (
		i, j, k int32
		t       float32
		a       [mrange][mrange + 1]float32
	)

	for i = 0; i < mrange; i++ { //было ++i
		for j = 0; j < mrange; j++ { //было ++j
			a[i][j] = m[id_rw(i, j, mrange)]
			a[i][mrange] = v[i]
		}
	}

	/* Pivotisation */
	for i = 0; i < mrange; i++ {
		for k = i + 1; k < mrange; k++ {
			if math.Abs(float64(a[i][i])) < math.Abs(float64(a[k][i])) {
				for j = 0; j <= mrange; j++ {
					t = a[i][j]
					a[i][j] = a[k][j]
					a[k][j] = t
				}
			}
		}
	}

	/* прямой ход */
	for k = 1; k < mrange; k++ {
		for j = k; j < mrange; j++ {
			t = a[j][k-1] / a[k-1][k-1]
			for i = 0; i < mrange+1; i++ {
				a[j][i] = a[j][i] - t*a[k-1][i]
			}
		}
	}

	/* обратный ход */
	for i = mrange - 1; i >= 0; i-- {
		rt[i] = a[i][mrange] / a[i][i]
		for j = mrange - 1; j > i; j-- {
			rt[i] = rt[i] - a[i][j]*rt[j]/a[i][i]
		}
	}

	return rt
}

func mtrx3_insert_cmn(m mtrx3_t, v vec3_t, cmn int32) (rt mtrx3_t) {
	const (
		mrange int32 = 3
	)

	var (
		i int32
		j int32 = 0
	)

	rt = m

	for i = cmn; i < mrange*mrange; i += mrange {
		rt[i] = v[j]
		j++
	}

	return rt
}

func mtrx3_solve_kramer(m mtrx3_t, v vec3_t) (rt vec3_t) {
	const (
		mrange int32 = 3
	)

	var (
		i       int32
		det     float32
		kr_mtrx mtrx3_t
	)

	det = mtrx3_det(m)

	if fabs(det) < f_eps {
		fmt.Println("mtrx3_solve_kramer(): system has no solve")
		return vec3_set(0.0, 0.0, 0.0)
	}

	for i = 0; i < mrange; i++ {
		kr_mtrx = mtrx3_insert_cmn(m, v, i)
		rt[i] = mtrx3_det(kr_mtrx) / det
	}

	return rt
}