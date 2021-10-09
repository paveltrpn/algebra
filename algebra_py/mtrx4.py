
from array import array
from math import sin, cos

from typing import Callable

from common import IdRw

class mtrx4(object):
    def __init__(self) -> None:
        self.data = array("f", [x-x for x in range(16)])

    def __repr__(self) -> str:
        return """
{:.4f} {:.4f} {:.4f} {:.4f}
{:.4f} {:.4f} {:.4f} {:.4f}
{:.4f} {:.4f} {:.4f} {:.4f}
{:.4f} {:.4f} {:.4f} {:.4f}
""".format(self.data[0],  self.data[1],  self.data[2],  self.data[3],
           self.data[4],  self.data[5],  self.data[6],  self.data[7],
           self.data[8],  self.data[9],  self.data[10], self.data[11],
           self.data[12], self.data[13], self.data[14], self.data[15])

    def __setitem__(self, key: int, value: float):
        self.data[key] = value

    def __getitem__(self, key: int) -> float:
        return self.data[key]

def mtrx4SetIdtt() -> mtrx4:
    rt = mtrx4()

    onDiag: Callable[[int], float] = lambda elem: 1.0 if (elem % 5) == 0 else 0.0
    for i, _ in enumerate(rt.data):
        rt[i] = onDiag(i)

    return rt

def mtrx4SetIdttLoop() -> mtrx4:
    rt = mtrx4()

    for i in range(4):
        for j in range(4): 
            if i == j: 
                rt[IdRw(i, j, 4)] = 1.0
            else:
                rt[IdRw(i, j, 4)] = 0.0

    return rt

def mtrx4SetEuler(yaw: float, pitch: float, roll: float) -> mtrx4:
    cosy = cos(yaw)
    siny = sin(yaw)
    cosp = cos(pitch)
    sinp = sin(pitch)
    cosr = cos(roll)
    sinr = sin(roll)

    rt = mtrx4()

    rt[0] = cosy*cosr - siny*cosp*sinr
    rt[1] = -cosy*sinr - siny*cosp*cosr
    rt[2] = siny * sinp
    rt[3] = 0.0

    rt[4] = siny*cosr + cosy*cosp*sinr
    rt[5] = -siny*sinr + cosy*cosp*cosr
    rt[6] = -cosy * sinp
    rt[7] = 0.0

    rt[8] = sinp * sinr
    rt[9] = sinp * cosr
    rt[10] = cosp
    rt[11] = 0.0

    rt[12] = 0.0
    rt[13] = 0.0
    rt[14] = 0.0
    rt[15] = 1.0

    return rt
