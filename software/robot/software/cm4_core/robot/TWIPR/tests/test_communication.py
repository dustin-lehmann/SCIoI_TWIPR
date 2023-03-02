import ctypes
import logging
import time

# import numpy as np

from robot.TWIPR.parameters import *
from robot.TWIPR.communication.twipr_comm_stm import TWIPR_Communication_STM32, UART_CMD, test_struct
import cm4_core.utils as utils

logging.Formatter(
    fmt='%(asctime)s.%(msecs)03d',
    datefmt='%Y-%m-%d,%H:%M:%S'
)

logging.basicConfig(
    format='%(asctime)s.%(msecs)03d %(levelname)-8s %(name)-8s %(message)s',
    level=logging.INFO,
    datefmt='%H:%M:%S'
)


def example_serial_communication():
    def rx_callback(message, *args, **kwargs):
        x = utils.ctypes.struct_to_dict(test_struct.from_buffer_copy(message.data))
        print(x)
        pass

    comm = TWIPR_Communication_STM32()
    # comm.registerCallback('rx', rx_callback)
    comm.start()

    # x = test_struct(a=99, b = -88888)
    # comm.echo(address=0x0102,value=x, type=test_struct, flag=3)

    time.sleep(60)

    comm.close()


def example_read():
    comm = TWIPR_Communication_STM32()
    comm.start()

    x = comm.read(address=0x0102)

    print("Answer")
    time.sleep(10)

    comm.close()


if __name__ == '__main__':
    # example_serial_communication()
    example_read()
