
import sys
import os
sys.path.append(os.getcwd()+"/algebra_py")

import algebra_py as alg

def main() -> None:
    foo_mtrx4 = alg.mtrx4()
    foo_mtrx4 = alg.mtrx4SetIdtt()
    print(foo_mtrx4)

    bar = alg.mtrx4SetEuler(20.0, 45.0, 64.0)
    print(bar)

    fooA_vec4 = alg.vec4(1.0)
    fooB_vec4 = alg.vec4()

    bar_vec4 = alg.vec4Sub(fooA_vec4, fooB_vec4)
    print("bar_vec4 - {}".format(bar_vec4))

if __name__ == "__main__":
    main()