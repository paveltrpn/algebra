package algebra_go

import (
	"math"
)

type qtnn [4]float32

func QtnnLenght(q qtnn) float32 {
	return float32(math.Sqrt(float64(
		q[_XC]*q[_XC] +
			q[_YC]*q[_YC] +
			q[_ZC]*q[_ZC] +
			q[_WC]*q[_WC])))
}

func QtnnNormalize_self(q qtnn) {
	len := QtnnLenght(q)

	if len != 0.0 {
		q[_WC] = q[_WC] / len
		q[_XC] = q[_XC] / len
		q[_YC] = q[_YC] / len
		q[_ZC] = q[_ZC] / len
	}
}

func QtnnScale(q qtnn, scale float32) (rt qtnn) {
	rt[_WC] = q[_WC] * scale
	rt[_XC] = q[_XC] * scale
	rt[_YC] = q[_YC] * scale
	rt[_ZC] = q[_ZC] * scale
	return rt
}

func QtnnSum(a, b qtnn) (rt qtnn) {
	rt[0] = a[0] + b[0]
	rt[1] = a[1] + b[1]
	rt[2] = a[2] + b[2]
	rt[3] = a[3] + b[3]

	return rt
}

func QtnnSub(a, b qtnn) (rt qtnn) {
	rt[0] = a[0] - b[0]
	rt[1] = a[1] - b[1]
	rt[2] = a[2] - b[2]
	rt[3] = a[3] - b[3]

	return rt
}

func QtnnDot(a, b qtnn) float32 {
	return a[0]*b[0] + a[1]*b[1] + a[2]*b[2] + a[3]*b[3]
}

func QtnnMult(a, b qtnn) (rt qtnn) {
	rt[_WC] = a[_WC]*b[_WC] - a[_XC]*b[_XC] - a[_YC]*b[_YC] - a[_ZC]*b[_ZC]
	rt[_XC] = a[_WC]*b[_XC] + a[_XC]*b[_WC] + a[_YC]*b[_ZC] - a[_ZC]*b[_YC]
	rt[_YC] = a[_WC]*b[_YC] - a[_XC]*b[_ZC] + a[_YC]*b[_WC] + a[_ZC]*b[_XC]
	rt[_ZC] = a[_WC]*b[_ZC] + a[_XC]*b[_YC] - a[_YC]*b[_XC] + a[_ZC]*b[_WC]

	return rt
}

/* function is broken */
func QtnnMultVec3(a qtnn, b Vec3) (rt qtnn) {
	rt[_WC] = -a[_WC]*b[_XC] - a[_YC]*b[_YC] - a[_ZC]*b[_ZC]
	rt[_XC] = a[_WC]*b[_XC] + a[_YC]*b[_ZC] - a[_ZC]*b[_YC]
	rt[_YC] = a[_WC]*b[_YC] - a[_XC]*b[_ZC] + a[_ZC]*b[_XC]
	rt[_ZC] = a[_WC]*b[_ZC] + a[_XC]*b[_YC] - a[_YC]*b[_XC]

	return rt
}

func QtnnFromVec3(v Vec3) (rt qtnn) {
	rt[_XC] = v[_XC]
	rt[_YC] = v[_YC]
	rt[_ZC] = v[_ZC]
	rt[_WC] = 0.0

	return rt
}

func QtnnFromAxisAngl(a Vec3, phi float64) (rt qtnn) {
	sinhalfphi := float32(math.Sin(phi * 0.5))

	rt[_WC] = float32(math.Cos(phi * 0.5))
	rt[_XC] = a[_XC] * sinhalfphi
	rt[_YC] = a[_YC] * sinhalfphi
	rt[_ZC] = a[_ZC] * sinhalfphi

	return rt
}

func Qtnnfrom_euler(yaw, pitch, roll float64) (rt qtnn) {
	var (
		qyaw, qpitch, qroll qtnn
	)

	qyaw = QtnnFromAxisAngl(Vec3Set(1.0, 0.0, 0.0), yaw)
	qpitch = QtnnFromAxisAngl(Vec3Set(0.0, 1.0, 0.0), pitch)
	qroll = QtnnFromAxisAngl(Vec3Set(0.0, 0.0, 1.0), roll)

	rt = QtnnMult(qyaw, qpitch)

	rt = QtnnMult(rt, qroll)

	return rt
}

func QtnnToVec3(q qtnn) (rt Vec3) {
	return Vec3Set(q[_XC], q[_YC], q[_ZC])
}

// func QtnnTransformVec3(a qtnn, b Vec3) (rt Vec3) {
// var (
// vq, tmp qtnn
// )
//
// vq = QtnnFromVec3(b)
//
// tmp = QtnnMult(a, vq)
// tmp = QtnnMult(tmp, QtnnGetInvert(a))
//
// return qtnno_Vec3(tmp)
// }
