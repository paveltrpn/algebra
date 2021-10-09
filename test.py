
import sys
import os
sys.path.append(os.getcwd()+"/algebra_py")

import algebra_py as alg

def main() -> None:
    foo = alg.mtrx4()
    foo = alg.mtrx4SetIdtt()
    print(foo)

    bar = alg.mtrx4SetEuler(20.0, 45.0, 64.0)
    print(bar)

if __name__ == "__main__":
    main()