import {IdRw} from "./common.mjs"
import { vec3Cross } from "./vec3.mjs"
import { vec3Sub } from "./vec3.mjs"

export class mtrx4 {
    constructor() {
        this.data = new Float32Array(16)
    }

    print() {
        console.log("%f %f %f %f", this.data[0], this.data[1], this.data[2], this.data[3])   
        console.log("%f %f %f %f", this.data[4], this.data[5], this.data[6], this.data[7])  
        console.log("%f %f %f %f", this.data[8], this.data[9], this.data[10], this.data[11])  
        console.log("%f %f %f %f", this.data[12], this.data[13], this.data[14], this.data[15])   
    }
}

/**
 * Return a identity matrix 4x4
 *
 * @returns {mtrx4} a identity 4x4 matrix
 */
 export function mtrx4SetIdtt() {
    let rt = new mtrx4();

    let onDiag = (elem) => {
        if ((elem % 5) === 0) {
            return 1.0
        } else return 0.0        
    }

    for (let i = 0; i < 16; i++) {
        rt.data[i] = onDiag(i)
    }

    return rt;
}

/**
 * Matrix 4x4 multiplication
 *
 * @returns {mtrx4} a identity 4x4 matrix
 */
export function mtrx4Mult(a, b) {
    let rt = new mtrx4()

    for (let i = 0; i < 4; i++){ 
        for (let j = 0; j < 4; j++) {
            for (let k = 0; k < 4; k++) {
                rt.data[IdRw(i, j, 4)] = rt.data[IdRw(i, j, 4)]+ a.data[IdRw(k, j, 4)]*b.data[IdRw(i, k, 4)]
            }
        }
    }

    return rt
}

/**
 * Return a matrix 4x4 build from euler angles
 *
 * @param {float}
 * @param {float}
 * @param {float}
 * @returns {mtrx4}
 */
export function mtrx4FromEuler(yaw, pitch, roll) {
    const cosy = Math.cos(yaw)
    const siny = Math.sin(yaw)
    const cosp = Math.cos(pitch)
    const sinp = Math.sin(pitch)
    const cosr = Math.cos(roll)
    const sinr = Math.sin(roll)

    let rt = new mtrx4()

    rt.data[0] = cosy*cosr - siny*cosp*sinr
    rt.data[1] = -cosy*sinr - siny*cosp*cosr
    rt.data[2] = siny * sinp
    rt.data[3] = 0.0

    rt.data[4] = siny*cosr + cosy*cosp*sinr
    rt.data[5] = -siny*sinr + cosy*cosp*cosr
    rt.data[6] = -cosy * sinp
    rt.data[7] = 0.0

    rt.data[8] = sinp * sinr
    rt.data[9] = sinp * cosr
    rt.data[10] = cosp
    rt.data[11] = 0.0

    rt.data[12] = 0.0
    rt.data[13] = 0.0
    rt.data[14] = 0.0
    rt.data[15] = 1.0

    return rt
}

/**
 * Return a matrix 4x4 build from perspective
 *
 * @param {float} field of view
 * @param {float} aspect ratio
 * @param {float} near clip plane distance
 * @param {float} far clip plane distance
 * @returns {mtrx4} 
 */
export function mtrx4FromPerspective(fovy, aspect, near, far) {
    let rt = mtrx4SetIdtt()
    let f = 1.0 / Math.tanh(fovy / Math.sqrt(2))
    let nf
	
    rt.data[0] = f / aspect
    rt.data[1] = 0.0
    rt.data[2] = 0.0
    rt.data[3] = 0.0
    rt.data[4] = 0.0
    rt.data[5] = f
    rt.data[6] = 0.0
    rt.data[7] = 0.0
    rt.data[8] = 0.0
    rt.data[9] = 0.0
    rt.data[11] = -1.0
    rt.data[12] =  0.0
    rt.data[13] =  0.0
    rt.data[15] =  0.0
	
    if (far >= Number.EPSILON) {
        nf = 1.0 / (near - far)
        rt.data[10] = (far + near) * nf
        rt.data[14] = 2.0 * far * near * nf
    } else {
        rt.data[10] = -1.0
        rt.data[14] = -2.0 * near
    }

    return rt
}

function mtrx4FromLookAt(eye, center, up) {
    let out = mtrx4SetIdtt()

    if (Math.fabs(eye[0]-center[0]) < float_info.epsilon &&
        Math.fabs(eye[1]-center[1]) < float_info.epsilon && 
        Math.fabs(eye[2]-center[2]) < float_info.epsilon) {
        return out
    }

    // let z0 = eye[0] - center[0]
    // let z1 = eye[1] - center[1]
    // let z2 = eye[2] - center[2]

    let z = vec3Sub(eye, center)

    len = 1.0 / Math.hypot(z.data[0], z.data[1], z.data[2]); // ??? было просто hypot
    z.data[0] *= len
    z.data[1] *= len
    z.data[2] *= len

    // let x0 = up[1]*z2 - up[2]*z1
    // let x1 = up[2]*z0 - up[0]*z2
    // let x2 = up[0]*z1 - up[1]*z0

    let x = vec3Cross(up, z)

    len = Math.hypot(x.data[0], x.data[1], x.data[2])

    if (len == 0.0) {
	    x.data[0] = 0
	    x.data[1] = 0
	    x.data[2] = 0
    } else {
        len = 1.0 / len
        x.data[0] *= len
        x.data[1] *= len
        x.data[2] *= len
    }

    // let y0 = z1*x2 - z2*x1
    // let y1 = z2*x0 - z0*x2
    // let y2 = z0*x1 - z1*x0

    let y = vec3Cross(z, x)

    len = Math.hypot(y.data[0], y.data[1], y.data[2])

    if (len == 0.0) {
        y.data[0] = 0
        y.data[1] = 0
        y.data[2] = 0
    } else {
        len = 1.0 / len
        y.data[0] *= len
        y.data[1] *= len
        y.data[2] *= len
    }

    out.data[0] = x.data[0]
    out.data[1] = y.data[0]
    out.data[2] = z.data[0]
    out.data[3] = 0.0
    out.data[4] = x.data[1]
    out.data[5] = y.data[1]
    out.data[6] = z.data[1]
    out.data[7] = 0.0
    out.data[8] = x.data[2]
    out.data[9] = y.data[2]
    out.data[10] = z.data[2]
    out.data[11] = 0.0
    out.data[12] = -(x.data[0]*eye[0] + x.data[1]*eye[1] + x.data[2]*eye[2])
    out.data[13] = -(y.data[0]*eye[0] + y.data[1]*eye[1] + y.data[2]*eye[2])
    out.data[14] = -(z.data[0]*eye[0] + z.data[1]*eye[1] + z.data[2]*eye[2])
    out.data[15] = 1.0

    return out
}
