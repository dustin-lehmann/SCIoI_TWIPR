import time

from cm4_core.rc_board import RobotControl_Board


def example_board():
    board = RobotControl_Board()
    board.setStatusLed(0)

    while True:
        time.sleep(1)


if __name__ == '__main__':
    example_board()
