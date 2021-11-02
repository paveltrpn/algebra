
import {vec3} from "./vec3.js"
import {vec2} from "./vec2.js"
import {cmplx} from "./cmplx.js"

function main() {
    let bar_vec3 = new vec3(0.4, 0.1, 0.3);
    let bar_cmplx = new cmplx(0, 1);
    let bar_vec2 = new vec2(3, 5);

    console.log(bar_vec3.data);
    console.log(bar_vec2.data);
    console.log(bar_cmplx.data);
}

main()