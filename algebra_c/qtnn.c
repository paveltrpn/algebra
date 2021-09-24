
#include "stdio.h"
#include "math.h"
#include "string.h"
#include "algebra.h"

void qtnn_zero(qtnn_t q) {
	q[0] = 0.0f;
	q[1] = 0.0f;
	q[2] = 0.0f;
	q[3] = 0.0f;
}

void qtnn_copy(const qtnn_t q, qtnn_t rt) {
	memcpy(rt, q, sizeof(float)*4);
}

void qtnn_show(const qtnn_t q) {
	printf("%5.2f %5.2f %5.2f %5.2f\n", q[_XC], q[_YC], q[_ZC], q[_WC]);
}

float qtnn_lenght(const qtnn_t q) {
	return sqrtf(q[_XC]*q[_XC] +
				 q[_YC]*q[_YC] +
				 q[_ZC]*q[_ZC] +
				 q[_WC]*q[_WC]);
}

void qtnn_normalize_self(qtnn_t q) {
	float len;

	len = qtnn_lenght(q);

	if (len > f_eps) {
		q[_WC] = q[_WC] / len;
		q[_XC] = q[_XC] / len;
		q[_YC] = q[_YC] / len;
		q[_ZC] = q[_ZC] / len;
	} else {
		printf("qtnn_normalize_self(): quaternion is too short!");
		return;
	}
}

void qtnn_get_normalize(const qtnn_t q, qtnn_t rt) {
	qtnn_copy(q, rt);

	qtnn_normalize_self(rt);
}

void qtnn_invert_self(qtnn_t q) {
	q[_WC] =  q[_WC];
	q[_XC] = -q[_XC];
	q[_YC] = -q[_YC];
	q[_ZC] = -q[_ZC];

	qtnn_normalize_self(q);
}

void qtnn_get_invert(const qtnn_t q, qtnn_t rt) {
	qtnn_copy(q, rt);

	qtnn_invert_self(rt);
}

void qtnn_scale(const qtnn_t q, float scale, qtnn_t rt) {
	rt[_WC] = q[_WC] * scale;
	rt[_XC] = q[_XC] * scale;
	rt[_YC] = q[_YC] * scale;
	rt[_ZC] = q[_ZC] * scale;
}

void qtnn_sum(const qtnn_t a, const qtnn_t b, qtnn_t rt) {
	rt[0] = a[0] + b[0];
	rt[1] = a[1] + b[1];
	rt[2] = a[2] + b[2];
	rt[3] = a[3] + b[3];
}

void qtnn_sub(const qtnn_t a, const qtnn_t b, qtnn_t rt) {
	rt[0] = a[0] - b[0];
	rt[1] = a[1] - b[1];
	rt[2] = a[2] - b[2];
	rt[3] = a[3] - b[3];
}

float qtnn_dot(const qtnn_t a, const qtnn_t b) {
	return a[0]*b[0] + a[1]*b[1] + a[2]*b[2] + a[3]*b[3];
}

void qtnn_mult(const qtnn_t a, const qtnn_t b, qtnn_t rt) {
	rt[_WC] = a[_WC]*b[_WC] - a[_XC]*b[_XC] - a[_YC]*b[_YC] - a[_ZC]*b[_ZC];
	rt[_XC] = a[_WC]*b[_XC] + a[_XC]*b[_WC] + a[_YC]*b[_ZC] - a[_ZC]*b[_YC];
	rt[_YC] = a[_WC]*b[_YC] - a[_XC]*b[_ZC] + a[_YC]*b[_WC] + a[_ZC]*b[_XC];
	rt[_ZC] = a[_WC]*b[_ZC] + a[_XC]*b[_YC] - a[_YC]*b[_XC] + a[_ZC]*b[_WC];
}

/* function is broken */
void qtnn_mult_vec3(const qtnn_t a, const vec3_t b, qtnn_t rt) {
	rt[_WC] = -a[_WC]*b[_XC] - a[_YC]*b[_YC] - a[_ZC]*b[_ZC];
	rt[_XC] = a[_WC]*b[_XC] + a[_YC]*b[_ZC] - a[_ZC]*b[_YC];
	rt[_YC] = a[_WC]*b[_YC] - a[_XC]*b[_ZC] + a[_ZC]*b[_XC];
	rt[_ZC] = a[_WC]*b[_ZC] + a[_XC]*b[_YC] - a[_YC]*b[_XC];
}

void qtnn_from_vec3(const vec3_t v, qtnn_t rt) {
	rt[_XC] = v[_XC];
	rt[_YC] = v[_YC];
	rt[_ZC] = v[_ZC];
	rt[_WC] = 0.0;
}

void qtnn_from_axisangl(const vec3_t a, float phi, qtnn_t rt) {
	float sinhalfphi;

	sinhalfphi = sinf(phi * 0.5);

	rt[_WC] = cosf(phi * 0.5);
	rt[_XC] = a[_XC] * sinhalfphi;
	rt[_YC] = a[_YC] * sinhalfphi;
	rt[_ZC] = a[_ZC] * sinhalfphi;
}

void qtnn_from_euler(float yaw, float pitch, float roll, qtnn_t rt) {
	qtnn_t	qyaw, qpitch, qroll;
	vec3_t  vyaw, vpitch, vroll;

	vec3_set(1.0, 0.0, 0.0, vyaw);
	vec3_set(0.0, 1.0, 0.0, vpitch);
	vec3_set(0.0, 0.0, 1.0, vroll);

	qtnn_from_axisangl(vyaw, yaw, qyaw);
	qtnn_from_axisangl(vpitch, pitch, qpitch);
	qtnn_from_axisangl(vroll, roll, qroll);

	qtnn_mult(qyaw, qpitch, rt);

	qtnn_mult(rt, qroll, rt);
}

void qtnn_to_vec3(const qtnn_t q, vec3_t rt) {
	vec3_set(q[_XC], q[_YC], q[_ZC], rt);
}

void qtnn_transform_vec3(const qtnn_t a, const vec3_t b, vec3_t rt) {
	qtnn_t	vq, tmp, ia;

	qtnn_from_vec3(b, vq);
    qtnn_mult(a, vq, tmp);
	qtnn_get_invert(a, ia);
	qtnn_mult(tmp, ia, rt);
}
