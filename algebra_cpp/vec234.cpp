#include <iostream>
#include <tuple>
#include <cmath>
#include "algebra.h"

using namespace std;

template <typename vecT_t, int range>
void 	vec_show(const vecT_t &v) {
	for (int i = 0; i < range; i++) {
		printf(" %5.2f", v[i]);
	}
	cout << "\n";
}
template void vec_show<vec2_t, 2>(const vec2_t &v);
template void vec_show<vec3_t, 3>(const vec3_t &v);
template void vec_show<vec4_t, 4>(const vec4_t &v);

template <typename vecT_t, int range>
float vec_lenght(const vecT_t &v) {
	float rt = 0;

	for (int i = 0; i < range; i++) {
		rt = rt + v[i]*v[i];
	}

	return sqrt(rt);
}
template float vec_lenght<vec2_t, 2>(const vec2_t &v);
template float vec_lenght<vec3_t, 3>(const vec3_t &v);
template float vec_lenght<vec4_t, 4>(const vec4_t &v);


template <typename vecT_t, int range>
vecT_t vec_normalize(const vecT_t &v) {
	vecT_t rt;
	float len;

	len = vec_lenght<vecT_t, range>(v);

	if (len != 0.0) {
		for (int i = 0; i < range; i++) {
			rt[i] = v[i] / len;
		}
	}

	return rt;
}
template vec2_t vec_normalize<vec2_t, 2>(const vec2_t &v);
template vec3_t vec_normalize<vec3_t, 2>(const vec3_t &v);
template vec4_t vec_normalize<vec4_t, 2>(const vec4_t &v);

template <typename vecT_t, int range>
vecT_t	vec_scale(const vecT_t &v,const float scale) {
	vecT_t rt;

	for (int i = 0; i < range; i++) {
		rt[i] = v[i] * scale;
	}
	
	return rt;
}
template vec2_t	vec_scale<vec2_t, 2>(const vec2_t &v,const float scale);
template vec3_t	vec_scale<vec3_t, 3>(const vec3_t &v,const float scale);
template vec4_t	vec_scale<vec4_t, 4>(const vec4_t &v,const float scale);

template <typename vecT_t, int range>
vecT_t vec_invert(const vecT_t &v) {
	vecT_t rt;

	for (int i = 0; i < range; i++) {
		rt[i] = -v[i];
	}
	
	return rt;
}
template vec2_t	vec_invert<vec2_t, 2>(const vec2_t &v);
template vec3_t	vec_invert<vec3_t, 3>(const vec3_t &v);
template vec4_t	vec_invert<vec4_t, 4>(const vec4_t &v);

template <typename vecT_t, int range>
float vec_dot(const vecT_t &a, const vecT_t &b) {
	float rt = 0;

	for (int i = 0; i < range; i++) {
		rt = rt + a[i] * b[i];
	}

	return rt;
}
template float vec_dot<vec2_t, 2>(const vec2_t &a, const vec2_t &b);
template float vec_dot<vec3_t, 3>(const vec3_t &a, const vec3_t &b);
template float vec_dot<vec4_t, 4>(const vec4_t &a, const vec4_t &b);

template <typename vecT_t, int range>
vecT_t vec_sum(const vecT_t &a, const vecT_t &b) {
	vecT_t rt;

	for (int i = 0; i < range; i++) {
		rt[i] = a[i] + b[i];
	}

	return rt;
}
template vec2_t vec_sum<vec2_t, 2>(const vec2_t &a, const vec2_t &b);
template vec3_t vec_sum<vec3_t, 3>(const vec3_t &a, const vec3_t &b);
template vec4_t vec_sum<vec4_t, 4>(const vec4_t &a, const vec4_t &b);

template <typename vecT_t, int range>
vecT_t vec_sub(const vecT_t &a, const vecT_t &b) {
	vecT_t rt;

	for (int i = 0; i < range; i++) {
		rt[i] = a[i] - b[i];
	}

	return rt;
}
template vec2_t vec_sub<vec2_t, 2>(const vec2_t &a, const vec2_t &b);
template vec3_t vec_sub<vec3_t, 3>(const vec3_t &a, const vec3_t &b);
template vec4_t vec_sub<vec4_t, 4>(const vec4_t &a, const vec4_t &b);

vec3_t vec_cross(vec3_t &a, vec3_t &b) {
	vec3_t rt;
	
	rt[0] = a[_YC]*b[_ZC] - a[_ZC]*b[_YC];
	rt[1] = a[_ZC]*b[_XC] - a[_XC]*b[_ZC];
	rt[2] = a[_XC]*b[_YC] - a[_YC]*b[_XC];

	return rt;
}
