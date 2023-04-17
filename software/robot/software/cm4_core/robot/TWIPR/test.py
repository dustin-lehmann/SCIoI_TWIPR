import ctypes
import cm4_core.utils.ctypes as ctypes_utils

from robot.TWIPR.experiments.experiments_simple_twipr import twipr_sample


def main():
    x = twipr_sample()

    z = ctypes_utils.struct_to_dict(x)
    print(z)

if __name__ == '__main__':
    main()
