#include "stdio.h"
#include "math.h"
#include "string.h"
#include "algebra.h"

void vec2_copy(const vec2_t v, vec2_t rt) {
	memcpy(rt, v, sizeof(float)*2);
}

void vec2_show(const vec2_t v) {
	printf("%5.2f %5.2f\n", v[_XC], v[_YC]);
}

void vec2_zero(vec2_t v) {
	v[0] = 0.0f;
	v[1] = 0.0f;
}

void vec2_set(float x, float y, vec3_t rt) {
	rt[0] = x;
	rt[1] = y;
}

float vec2_lenght(const vec2_t v) {
	return sqrtf(v[_XC]*v[_XC] +
				 v[_YC]*v[_YC]);

}

void vec2_normalize(vec2_t v) {
	float len;
	
	len = vec2_lenght(v);

	if (len > f_eps) {
		v[_ZC] = v[_ZC] / len;
		v[_XC] = v[_XC] / len;
	} else {
		printf("vec2_normalize_self(): vector is too short!");
		return;
	}
}

void vec2_scale(const vec2_t v, const float scale, vec3_t rt) {
	rt[0] *= scale;
	rt[1] *= scale;
}

void vec2_invert(vec2_t v) {
	v[_XC] = -v[_XC];
	v[_YC] = -v[_YC];
}

float vec2_dot(const vec2_t a, const vec2_t b) {
	return a[0]*b[0] + a[1]*b[1];
}

void vec2_sum(const vec2_t a, const vec2_t b, vec2_t rt) {
	rt[0] = a[0] + b[0];
	rt[1] = a[1] + b[1];
}

void vec2_sub(const vec2_t a, const vec2_t b, vec2_t rt) {
	rt[0] = a[0] - b[0];
	rt[1] = a[1] - b[1];
}

