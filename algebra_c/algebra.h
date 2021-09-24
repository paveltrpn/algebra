
#ifndef __algebra_h_
#define __algebra_h_

#include "stdint.h"
#include "stdbool.h"

enum {_XC, _YC, _ZC, _WC};

typedef float vec2_t[2];
typedef float vec3_t[3];
typedef float vec4_t[4];
typedef float mtrx2_t[4];
typedef float mtrx3_t[9];
typedef float mtrx4_t[16];
typedef float qtnn_t[4];

typedef struct {
    int mrange;
    float *mtrx;
} mtrxC_t;

#define f_eps 0.000001f

void    vec2_copy(const vec2_t v, vec2_t rt);
void    vec3_copy(const vec3_t v, vec3_t rt);
void    vec4_copy(const vec4_t v, vec4_t rt);

void    vec2_show(const vec2_t v);
void 	vec3_show(const vec3_t v);
void    vec4_show(const vec4_t v);

void    vec2_zero(vec2_t v);
void    vec3_zero(vec3_t v);
void    vec4_zero(vec4_t v);

void    vec2_set(float x, float y, vec3_t rt);
void 	vec3_set(float x, float y, float z, vec3_t rt);
void    vec4_set(float x, float y, float z, float w, vec3_t rt);

float 	vec2_lenght(const vec2_t v);
float 	vec3_lenght(const vec3_t v);
float 	vec4_lenght(const vec4_t v);

void 	vec2_normalize(vec2_t v);
void 	vec3_normalize(vec3_t v);
void 	vec4_normalize(vec4_t v);

void	vec2_scale(const vec2_t v,const float scale, vec2_t rt);
void	vec3_scale(const vec3_t v,const float scale, vec3_t rt);
void	vec4_scale(const vec4_t v,const float scale, vec4_t rt);

void	vec2_invert(vec2_t v);
void	vec3_invert(vec3_t v);
void	vec4_invert(vec4_t v);

float	vec2_dot(const vec2_t a, const vec2_t b);
float	vec3_dot(const vec3_t a, const vec3_t b);
float	vec4_dot(const vec4_t a, const vec4_t b);

void	vec2_sum(const vec2_t a, const vec2_t b, vec2_t rt);
void	vec3_sum(const vec3_t a, const vec3_t b, vec3_t rt);
void	vec4_sum(const vec4_t a, const vec4_t b, vec4_t rt);

void	vec2_sub(const vec2_t a, const vec2_t b, vec2_t rt);
void	vec3_sub(const vec3_t a, const vec3_t b, vec3_t rt);
void	vec4_sub(const vec4_t a, const vec4_t b, vec4_t rt);

void	vec3_cross(const vec3_t a, const vec3_t b, vec3_t rt);
	
int32_t id_rw(int32_t i, int32_t j, int32_t n);
int32_t id_cw(int32_t i, int32_t j, int32_t n);


void 	mtrx3_copy(const mtrx3_t m, mtrx3_t rt);
void    mtrx3_zero(mtrx3_t m);
void    mtrx3_set(float a00, float a01, float a02,
                  float a10, float a11, float a12,
                  float a20, float a21, float a22,
                  mtrx3_t rt);
void 	mtrx3_set_euler(const float yaw, const float pitch, const float roll, mtrx3_t rt);
void 	mtrx3_set_axisangl(const vec3_t ax, const float phi, mtrx3_t rt);
void	mtrx3_show(const mtrx3_t m);
void	mtrx3_idtt(mtrx3_t rt);
float	mtrx3_det(const mtrx3_t m);
void	mtrx3_mult(const mtrx3_t a, const mtrx3_t b, mtrx3_t rt);
void	mtrx3_mult_vec3(const mtrx3_t m, const vec3_t v, vec3_t rt);
void	mtrx3_lu(const mtrx3_t m, mtrx3_t lm, mtrx3_t um);
void	mtrx3_ldlt(const mtrx3_t m, mtrx3_t lm, vec3_t dv);
void	mtrx3_get_transpose(const mtrx3_t m, mtrx3_t rt);
void	mtrx3_tranpose_self(mtrx3_t m);
void    mtrx3_get_inv(const mtrx3_t m, mtrx3_t rt);

void    qtnn_zero(qtnn_t q);
void    qtnn_copy(const qtnn_t q, qtnn_t rt);    
void 	qtnn_show(const qtnn_t q); 
float	qtnn_lenght(const qtnn_t q);
void	qtnn_normalize_self(qtnn_t q);
void	qtnn_get_normalize(const qtnn_t q, qtnn_t rt);
void	qtnn_invert_self(qtnn_t q);
void	qtnn_get_invert(const qtnn_t q, qtnn_t rt); 
void	qtnn_scale(const qtnn_t q, float scale, qtnn_t rt);
void	qtnn_sum(const qtnn_t a, const qtnn_t b, qtnn_t rt);
void 	qtnn_sub(const qtnn_t a, const qtnn_t b, qtnn_t rt);
float   qtnn_dot(const qtnn_t a, const qtnn_t b);
void    qtnn_mult(const qtnn_t a, const qtnn_t b, qtnn_t rt); 
void    qtnn_mult_vec3(const qtnn_t a, const qtnn_t b, vec3_t rt);
void	qtnn_from_vec3(const vec3_t, qtnn_t rt);
void    qtnn_from_axisangl(const vec3_t a, float phi, qtnn_t rt); 
void	qtnn_from_euler(float yaw, float pitch, float roll, qtnn_t rt); 
void    qtnn_to_vec3(const qtnn_t q, vec3_t rt);
void    qtnn_transform_vec3(const qtnn_t a, const vec3_t b, vec3_t rt);

void 	mtrx4_copy(const mtrx4_t m, mtrx4_t rt);
void    mtrx4_zero(mtrx4_t m);
void    mtrx4_set(float a00, float a01, float a02, float a03,
                  float a10, float a11, float a12, float a13,
                  float a20, float a21, float a22, float a23,
                  float a30, float a31, float a32, float a33,
                  mtrx3_t rt);
void	mtrx4_show(const mtrx4_t m);
void	mtrx4_idtt(mtrx4_t rt);
void	mtrx4_lu(const mtrx4_t m, mtrx4_t lm, mtrx4_t um);
void	mtrx4_ldlt(const mtrx4_t m, mtrx4_t lm, vec4_t dv);
void	mtrx4_get_transpose(const mtrx4_t m, mtrx4_t rt);
void	mtrx4_tranpose_self(mtrx4_t m);
void    mtrx4_get_inv(const mtrx4_t m, mtrx4_t rt);
void    mtrx4_get_inv_gauss(const mtrx4_t m, mtrx4_t rt); //empty

bool    mtrxC_assert(const mtrxC_t *m); //empty
bool    mtrxC_allocate(int range, mtrxC_t *rt);
void    mtrxC_free(mtrxC_t *m);
void    mtrxC_show(const mtrxC_t m);
void    mtrxC_zero(mtrxC_t m);
void    mtrxC_idtt(mtrxC_t m);

#endif