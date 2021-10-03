package algebra_go

type Vec3 [3]float32

func Vec3Copy(v Vec3) (rt Vec3) {
	rt[0] = v[0]
	rt[1] = v[1]
	rt[2] = v[2]

	return rt
}

func Vec3Set(x float32, y float32, z float32) (rt Vec3) {
	rt[0] = x
	rt[1] = y
	rt[2] = z

	return rt
}

func Vec3Lenght(v Vec3) float32 {
	return Sqrtf(v[_XC]*v[_XC] +
		v[_YC]*v[_YC] +
		v[_ZC]*v[_ZC])

}

func Vec3Normalize(v Vec3) (rt Vec3) {
	len := Vec3Lenght(v)

	if len != 0.0 {
		rt[_ZC] = v[_ZC] / len
		rt[_XC] = v[_XC] / len
		rt[_YC] = v[_YC] / len
	}

	return rt
}

func Vec3Scale(v Vec3, scale float32) (rt Vec3) {
	v[0] *= scale
	v[1] *= scale
	v[2] *= scale

	return rt
}

func Vec3Invert(v Vec3) (rt Vec3) {
	rt[_XC] = -v[_XC]
	rt[_YC] = -v[_YC]
	rt[_ZC] = -v[_ZC]

	return rt
}

func Vec3Dot(a Vec3, b Vec3) float32 {
	return a[0]*b[0] + a[1]*b[1] + a[2]*b[2]
}

func Vec3Sum(a, b Vec3) (rt Vec3) {
	rt[0] = a[0] + b[0]
	rt[1] = a[1] + b[1]
	rt[2] = a[2] + b[2]

	return rt
}

func Vec3Sub(a, b Vec3) (rt Vec3) {
	rt[0] = a[0] - b[0]
	rt[1] = a[1] - b[1]
	rt[2] = a[2] - b[2]

	return rt
}

func Vec3Cross(a, b Vec3) (rt Vec3) {
	rt[0] = a[_YC]*b[_ZC] - a[_ZC]*b[_YC]
	rt[0] = a[_ZC]*b[_XC] - a[_XC]*b[_ZC]
	rt[0] = a[_XC]*b[_YC] - a[_YC]*b[_XC]

	return rt
}
