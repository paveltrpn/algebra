import { mtrx4FromPerspective } from "./mtrx4.mjs"
import { mtrx4Mult, mtrx4SetIdtt, mtrx4, mtrx4FromEuler } from "./mtrx4.mjs"

function main() {
    let foo = mtrx4SetIdtt()
    let bar = mtrx4FromEuler(34, 12, 155)
    let pesp = mtrx4FromPerspective(45, 4/3, 0.01, 100)

    let res = mtrx4Mult(pesp, bar)

    res.print()
}

main()