import threading

from cm4_core.interface.interface import Interface
from cm4_core.interface.data_link import DataLink, Command
from cm4_core.utils.debug import debug_print
from cm4_core.rc_board import RobotControl_Board


class TankRobot:
    interface: Interface
    board: RobotControl_Board
    _thread: threading.Thread

    # === INIT =========================================================================================================
    def __init__(self):
        ...

        # TODO: This should done different and is only for KISS for David's defence
        self.motors = {
            'left': 0,
            'right': 0
        }

        self.interface.data['motors'] = {

            'left': DataLink(identifier='left',
                             description='Percentage of left motor speed',
                             limits=[-1, 1],
                             datatype=float,
                             obj=self.motors,
                             name='left'),

            'right': DataLink(identifier='right',
                              description='Percentage of right motor speed',
                              limits=[-1, 1],
                              datatype=float,
                              obj=self.motors,
                              name='right'),
        }

    # === METHODS ======================================================================================================
    def setSpeed(self, left, right):
        ...

    # === PRIVATE METHODS ==============================================================================================
    def _robot_thread(self):
        ...
