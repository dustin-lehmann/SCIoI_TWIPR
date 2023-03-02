from cm4_core.interface.interface import Interface
from cm4_core.interface.data_link import DataLink, Command
from cm4_core.utils.debug import debug_print
from cm4_core.hardware.sx1508 import SX1508, SX1508_GPIO_MODE

SX1508_PIN_LED = 3


class RobotControl_Board:
    interface: Interface

    # === INIT =========================================================================================================
    def __init__(self):
        self.interface = Interface('wifi', device_class='board', device_type='rc', id='board_rc_c4-02', name='c4-02')

        # TODO: This should be defined somewhere else
        self.interface.commands['print'] = Command(identifier='print',
                                                   callback=debug_print,
                                                   arguments=['text'],
                                                   description='Prints any given text')

        self.interface.data['led'] = {

        }

        # This too
        self.portExpander = SX1508()
        self.portExpander.configureGPIO(gpio=SX1508_PIN_LED, mode=SX1508_GPIO_MODE.OUTPUT, pullup=False, pulldown=True)

        self.interface.registerCallback('connected', self.setStatusLed, parameters={'state': True}, discard_inputs=True)

        self.interface.start()

    # === METHODS ======================================================================================================
    def setStatusLed(self, state, *args, **kwargs):
        self.portExpander.writeGPIO(gpio=SX1508_PIN_LED, state=state)

    # ------------------------------------------------------------------------------------------------------------------
    def setRGBLed(self, color):
        ...

    # ------------------------------------------------------------------------------------------------------------------
    def handle_exit(self, *args, **kwargs):
        self.setStatusLed(0)
