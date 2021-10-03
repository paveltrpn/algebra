package algebra_go

import (
	"fmt"
	"math"
)

type Mtrx4 [16]float32

func Mtrx4Idtt() (rt Mtrx4) {
	var (
		i, j int32
		n    int32 = 4
	)

	for i = 0; i < n; i++ {
		for j = 0; j < n; j++ {
			if i == j {
				rt[IdRw(i, j, n)] = 1.0
			} else {
				rt[IdRw(i, j, n)] = 0.0
			}
		}
	}

	return rt
}

func Mtrx4Set(m [16]float32) (rt Mtrx4) {
	var (
		i, j int32
		n    int32 = 4
	)

	for i = 0; i < n; i++ {
		for j = 0; j < n; j++ {
			rt[IdRw(i, j, n)] = m[IdRw(i, j, n)]
		}
	}
	return rt
}

func Mtrx4SetFloat(a00, a01, a02, a03,
	a10, a11, a12, a13,
	a20, a21, a22, a23,
	a30, a31, a32, a33 float32) (rt Mtrx4) {

	rt[0] = a00
	rt[1] = a01
	rt[2] = a02
	rt[3] = a03

	rt[4] = a10
	rt[5] = a11
	rt[6] = a12
	rt[7] = a13

	rt[8] = a20
	rt[9] = a21
	rt[10] = a22
	rt[11] = a23

	rt[12] = a30
	rt[13] = a31
	rt[14] = a32
	rt[15] = a33

	return rt
}

func Mtrx4SetEuler(yaw, pitch, roll float32) (rt Mtrx4) {
	var (
		cosy, siny, cosp, sinp, cosr, sinr float32
	)

	cosy = Cosf(yaw)
	siny = Sinf(yaw)
	cosp = Cosf(pitch)
	sinp = Sinf(pitch)
	cosr = Cosf(roll)
	sinr = Sinf(roll)

	rt[0] = cosy*cosr - siny*cosp*sinr
	rt[1] = -cosy*sinr - siny*cosp*cosr
	rt[2] = siny * sinp
	rt[3] = 0.0

	rt[4] = siny*cosr + cosy*cosp*sinr
	rt[5] = -siny*sinr + cosy*cosp*cosr
	rt[6] = -cosy * sinp
	rt[7] = 0.0

	rt[8] = sinp * sinr
	rt[9] = sinp * cosr
	rt[10] = cosp
	rt[11] = 0.0

	rt[12] = 0.0
	rt[13] = 0.0
	rt[14] = 0.0
	rt[15] = 1.0

	return rt
}

func Mtrx4SetAxisAngl(ax Vec3, phi float32) (rt Mtrx4) {
	var (
		cosphi, sinphi, vxvy, vxvz, vyvz, vx, vy, vz float32
	)

	cosphi = Cosf(phi)
	sinphi = Sinf(phi)
	vxvy = ax[_XC] * ax[_YC]
	vxvz = ax[_XC] * ax[_ZC]
	vyvz = ax[_YC] * ax[_ZC]
	vx = ax[_XC]
	vy = ax[_YC]
	vz = ax[_ZC]

	rt[0] = cosphi + (1.0-cosphi)*vx*vx
	rt[1] = (1.0-cosphi)*vxvy - sinphi*vz
	rt[2] = (1.0-cosphi)*vxvz + sinphi*vy
	rt[3] = 0.0

	rt[4] = (1.0-cosphi)*vxvy + sinphi*vz
	rt[5] = cosphi + (1.0-cosphi)*vy*vy
	rt[6] = (1.0-cosphi)*vyvz - sinphi*vz
	rt[7] = 0.0

	rt[8] = (1.0-cosphi)*vxvz - sinphi*vy
	rt[9] = (1.0-cosphi)*vyvz + sinphi*vx
	rt[10] = cosphi + (1.0-cosphi)*vz*vz
	rt[11] = 0.0

	rt[12] = 0.0
	rt[13] = 0.0
	rt[14] = 0.0
	rt[15] = 1.0

	return rt
}

func Mtrx4det(m Mtrx4) float32 {
	return 0.0
}

func Mtrx4det_lu(m Mtrx4) (rt float32) {
	const (
		mrange int32 = 4
	)

	var (
		i            int32
		l, u         Mtrx4
		l_det, u_det float32
	)

	l, u = Mtrx4LU(m)

	l_det = l[0]
	u_det = u[0]

	for i = 1; i < mrange; i++ {
		l_det *= l[IdRw(i, i, mrange)]
		u_det *= u[IdRw(i, i, mrange)]
	}

	return l_det * u_det
}

func Mtrx4mult(a, b Mtrx4) (rt Mtrx4) {
	const (
		mrange int32 = 4
	)

	var (
		i, j, k int32
		tmp     float32
	)

	for i = 0; i < mrange; i++ {
		for j = 0; j < mrange; j++ {
			tmp = 0.0
			for k = 0; k < mrange; k++ {
				tmp = tmp + a[IdRw(k, j, mrange)]*b[IdRw(i, k, mrange)]
			}
			rt[IdRw(i, j, mrange)] = tmp
		}
	}

	return rt
}

func Mtrx4MultVec(m Mtrx4, v Vec4) (rt Vec4) {
	const (
		mrange int32 = 4
	)

	var (
		i, j int32
		tmp  float32
	)

	for i = 0; i < mrange; i++ {
		tmp = 0
		for j = 0; j < mrange; j++ {
			tmp = tmp + m[IdRw(i, j, mrange)]*v[j]
		}
		rt[i] = tmp
	}

	return rt
}

func Mtrx4LU(m Mtrx4) (lm, um Mtrx4) {
	const (
		mrange int32 = 4
	)

	var (
		i, j, k int32
		sum     float32
	)

	for i = 0; i < mrange; i++ {
		for k = i; k < mrange; k++ {
			sum = 0
			for j = 0; j < i; j++ {
				sum += (lm[IdRw(i, j, mrange)] * um[IdRw(j, k, mrange)])
			}
			um[IdRw(i, k, mrange)] = m[IdRw(i, k, mrange)] - sum
		}

		for k = i; k < mrange; k++ {
			if i == k {
				lm[IdRw(i, i, mrange)] = 1.0
			} else {
				sum = 0
				for j = 0; j < i; j++ {
					sum += lm[IdRw(k, j, mrange)] * um[IdRw(j, i, mrange)]
				}
				lm[IdRw(k, i, mrange)] = (m[IdRw(k, i, mrange)] - sum) / um[IdRw(i, i, mrange)]
			}
		}
	}

	return lm, um
}

func Mtrx4LDLT(m Mtrx4) (lm Mtrx4, dv Vec4) {
	const (
		mrange int32 = 4
	)

	var (
		i, j, k int32
		sum     float32
	)

	for i = 0; i < mrange; i++ {
		for j = i; j < mrange; j++ {
			sum = m[IdRw(j, i, mrange)]
			for k = 0; k < i; k++ {
				sum = sum - lm[IdRw(i, k, mrange)]*dv[k]*lm[IdRw(j, k, mrange)]
				if i == j {
					if sum <= 0 {
						fmt.Println("Mtrx4LDLT(): mtrx is not positive deﬁnite")
						return Mtrx4Idtt(), Vec4Set(0.0, 0.0, 0.0, 0.0)
					}
					dv[i] = sum
					lm[IdRw(i, i, mrange)] = 1.0
				} else {
					lm[IdRw(j, i, mrange)] = sum / dv[i]
				}
			}
		}
	}

	return lm, dv
}

func Mtrx4Invert(m Mtrx4) (rt Mtrx4) {
	return Mtrx4Idtt()
}

func Mtrx4SolveGauss(m Mtrx4, v Vec4) (rt Vec4) {
	const (
		mrange int32 = 4
	)

	var (
		i, j, k int32
		t       float32
		a       [mrange][mrange + 1]float32
	)

	for i = 0; i < mrange; i++ { //было ++i
		for j = 0; j < mrange; j++ { //было ++j
			a[i][j] = m[IdRw(i, j, mrange)]
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

func Mtrx4InsertCmn(m Mtrx4, v Vec4, cmn int32) (rt Mtrx4) {
	const (
		mrange int32 = 4
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

func Mtrx4SolveKramer(m Mtrx4, v Vec4) (rt Vec4) {
	const (
		mrange int32 = 4
	)

	var (
		i       int32
		det     float32
		kr_mtrx Mtrx4
	)

	det = Mtrx4det_lu(m)

	if Fabs(det) < f_eps {
		fmt.Println("Mtrx4SolveKramer(): system has no solve")
		return Vec4Set(0.0, 0.0, 0.0, 0.0)
	}

	for i = 0; i < mrange; i++ {
		kr_mtrx = Mtrx4InsertCmn(m, v, i)
		rt[i] = Mtrx4det_lu(kr_mtrx) / det
	}

	return rt
}
