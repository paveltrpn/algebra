
#include "stdio.h"
#include "math.h"
#include "string.h"
#include "algebra.h"

void vec4_copy(const vec4_t v, vec4_t rt) {
	memcpy(rt, v, sizeof(float)*4);
}

void vec4_show(const vec4_t v) {
	printf("%5.2f %5.2f %5.2f %5.2f\n", v[_XC], v[_YC], v[_ZC], v[_WC]);
}

void vec4_zero(vec4_t v) {
	v[0] = 0.0f;
	v[1] = 0.0f;
	v[2] = 0.0f;
	v[3] = 0.0f;
}

void vec4_set(float x, float y, float z, float w, vec4_t rt) {
	rt[0] = x;
	rt[1] = y;
	rt[2] = z;
	rt[3] = w;
}

float vec4_lenght(const vec4_t v) {
	return sqrtf(v[_XC]*v[_XC] +
				 v[_YC]*v[_YC] +
				 v[_ZC]*v[_ZC] +
				 v[_WC]*v[_WC]);

}

void vec4_normalize(vec4_t v) {
	float len;
	
	len = vec4_lenght(v);

	if (len > f_eps) {
		v[_ZC] = v[_ZC] / len;
		v[_XC] = v[_XC] / len;
		v[_YC] = v[_YC] / len;
		v[_WC] = v[_WC] / len;
	} else {
		printf("vec4_normalize_self(): vector is too short!");
		return;
	}
}

void vec4_scale(const vec4_t v, const float scale, vec4_t rt) {
	rt[0] *= scale;
	rt[1] *= scale;
	rt[2] *= scale;
	rt[3] *= scale;
}

void vec4_invert(vec4_t v) {
	v[_XC] = -v[_XC];
	v[_YC] = -v[_YC];
	v[_ZC] = -v[_ZC];
	v[_WC] = -v[_WC];
}

float vec4_dot(const vec4_t a, const vec4_t b) {
	return a[0]*b[0] + a[1]*b[1] + a[2]*b[2] + a[3]*b[3];
}

void vec4_sum(const vec4_t a, const vec4_t b, vec4_t rt) {
	rt[0] = a[0] + b[0];
	rt[1] = a[1] + b[1];
	rt[2] = a[2] + b[2];
	rt[3] = a[3] + b[3];
}

void vec4_sub(const vec4_t a, const vec4_t b, vec4_t rt) {
	rt[0] = a[0] - b[0];
	rt[1] = a[1] - b[1];
	rt[2] = a[2] - b[2];
	rt[3] = a[3] - b[3];
}
