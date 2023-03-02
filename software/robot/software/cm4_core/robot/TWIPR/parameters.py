import enum








# STM32 Modules
class TWIPR_LL_MODULE(enum.IntEnum):
    TWIPR_LL_MODULE_DEFAULT = 0x00
    TWIPR_LL_MODULE_DEBUG = 0xFF
    TWIPR_LL_MODULE_CONTROL = 0x01


# Board Parameters
TWIPR_PARAMS_BOARD_STM32_UART = '/dev/ttyAMA1'
TWIPR_PARAMS_BOARD_STM32_UART_BAUD = 115200
TWIPR_PARAMS_BOARD_STM32_UART_BAUD = 2000000