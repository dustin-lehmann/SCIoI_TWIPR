import ctypes
import math
import time
import numpy as np

from cm4_core.utils.json import readJSON, writeJSON
from robot.TWIPR.communication.twipr_comm_stm import TWIPR_Communication_STM32
from robot.TWIPR.communication.twipr_comm_utils import reset_uart

from robot.TWIPR.experiments.experiments_simple_twipr import SimpleTWIPR
from robot.TWIPR.utils.trajectory import transform_input_2d_3d, getSignal

import cm4_core.utils.joystick.rpi_joystick as rpi_joystick

import matplotlib.pyplot as plt
import json

Ts = 0.01


def test():
    twipr = SimpleTWIPR()

    joystick = rpi_joystick.RpiJoystick()
    joystick.set_callback(event=rpi_joystick.A, callback=twipr.startBalancing)
    joystick.set_callback(event=rpi_joystick.B, callback=twipr.stopBalancing)

    while True:
        val1 = joystick.axes[1]*(-0.05)
        val2 = joystick.axes[2]*(0.15)
        twipr.setInput([val1+val2, val1-val2])
        time.sleep(0.1)

pass


def balance():
    twipr = SimpleTWIPR()
    twipr.startBalancing()
    time.sleep(1)


def run_step():
    twipr = SimpleTWIPR()

    trajectory_input = []
    for i in range(0, 100):
        trajectory_input.append([-0.02, -0.02])
    for i in range(0, 400):
        trajectory_input.append([0, 0])

    twipr.sendTrajectory(trajectory_input)
    time.sleep(1)
    twipr.startBalancing()
    time.sleep(10)
    twipr.startTrajectory(length=300, id=5)
    time.sleep(20)
    twipr.stopBalancing()

    traj_id = [sample.control.trajectory_id for sample in twipr.samples]
    theta = [sample.estimation.state.theta for sample in twipr.samples]

    indexes = [idx for idx, val in enumerate(traj_id) if val != 0]
    index_first = min(indexes)
    index_last = max(indexes)

    theta_experiment = theta[index_first:index_last + 1]

    with open('./step_output.json', 'w') as f:
        json.dump(theta_experiment, f)

    plt.plot(theta_experiment)
    plt.grid()
    plt.show()

    time.sleep(1)


def run_estimation():
    twipr = SimpleTWIPR()
    data = readJSON('./estimation/estimation.json')
    u_est = transform_input_2d_3d(data['u_est'])

    samples_experiment = twipr.runTrajectoryExperiment(u_est, id=1)

    theta = getSignal(samples_experiment, 'estimation', 'state', 'theta')
    data['samples_experiment'] = samples_experiment
    data['samples_all'] = twipr.getSampleData()
    data['y_est'] = theta

    writeJSON('./estimation/estimation.json', data)

    input_plot = np.asarray(data['u_est'])
    plt.plot(10 * input_plot)
    plt.plot(theta)
    plt.show()


def run_ref_1():
    twipr = SimpleTWIPR()

    with open('./ref1/ref1.json') as f:
        ref1_data = json.load(f)

    ref1_input = ref1_data['input']

    trajectory_input = []
    for u in ref1_input:
        trajectory_input.append([u / 2, u / 2])
    twipr.sendTrajectory(trajectory_input)
    time.sleep(1)
    twipr.startBalancing()
    time.sleep(10)
    twipr.startTrajectory(length=len(ref1_input), id=5)
    time.sleep(20)
    twipr.stopBalancing()
    theta = [sample.estimation.state.theta for sample in twipr.samples]
    traj_id = [sample.control.trajectory_id for sample in twipr.samples]

    indexes = [idx for idx, val in enumerate(traj_id) if val != 0]
    index_first = min(indexes)
    index_last = max(indexes)

    theta_experiment = theta[index_first:index_last + 1]

    with open('./ref1/ref1_output.json', 'w') as f:
        json.dump(theta_experiment, f)

    plt.plot(theta_experiment)
    plt.grid()
    plt.show()


if __name__ == '__main__':
    # run_estimation()
    # run_ref_1()
    # run_step()
    # balance()
    test()
