import ctypes

def main():
    # noinspection PyTypeChecker
    x = bytes(ctypes.c_uint16(400))



    x = test_struct(a=3, b=4.2)

    b = bytes(x)

    pass


if __name__ == '__main__':
    main()