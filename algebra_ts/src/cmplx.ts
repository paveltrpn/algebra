
export class cmplx {
    data: Float32Array;
    private readonly order: number = 2;

    constructor(r?: number, i?: number) {
        this.data = new Float32Array(2);
        
		this.data[0] = r || 0.0;
		this.data[1] = i || 0.0;
    }
}

export function cmplxSum(a: cmplx, b: cmplx): cmplx {
    let rt = new cmplx;

    rt.data[0] = a.data[0] + b.data[0];
    rt.data[1] = a.data[1] + b.data[1];

    return rt;
 }

 export function cmplxSub(a: cmplx, b: cmplx): cmplx {
    let rt = new cmplx;

    rt.data[0] = a.data[0] - b.data[0];
    rt.data[1] = a.data[1] - b.data[1];

    return rt;
 }

 export function cmplxMult(a: cmplx, b: cmplx): cmplx {
    let rt = new cmplx;

     rt.data[0] = a.data[0]*b.data[0] - a.data[1]*b.data[1];
     rt.data[1] = a.data[0]*b.data[1] + a.data[1]*b.data[0];

     return rt;
 }

 export function cmplxDiv(a: cmplx, b: cmplx): cmplx {
    let rt = new cmplx;

    rt.data[0] = (a.data[0]*b.data[0] + a.data[1]*b.data[1]) / (b.data[0]*b.data[0] + b.data[1]*b.data[1]);
    rt.data[1] = (a.data[1]*b.data[0] - a.data[0]*b.data[1]) / (b.data[0]*b.data[0] + b.data[1]*b.data[1]);

    return rt;
}

export function cmplxScale(a: cmplx, k: number): cmplx {
    let rt = new cmplx;

    rt.data[0] = a.data[0]*k;
    rt.data[1] = a.data[1]*k;

    return rt;
}

