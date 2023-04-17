# import evdev
import time

from evdev import InputDevice, categorize, ecodes

# creates object 'gamepad' to store the data
# you can call it whatever you like
gamepad = InputDevice('/dev/input/event2')
#
# # prints out device info at start
# print(gamepad)
#
# # evdev takes care of polling the controller in a loop
# for event in gamepad.read_loop():
#     print(categorize(event))

from evdev import InputDevice, categorize, ecodes

print("ACGAM R1 - pad mapping")

# creates object 'gamepad' to store the data
gamepad = InputDevice('/dev/input/event2')

# button code variables (change to suit your device)
A = 304
B = 305
X = 307
Y = 308

# loop and filter by event code and print the mapped label
x = gamepad.capabilities()
print(x)


while True:
    print("ggg")
    # for event in gamepad.read_loop():
    #     if event.type == ecodes.EV_KEY:
    #         if event.value == 1:
    #             print(event.code)

    x = (gamepad.absinfo(4).value-32768)/32768
    print(x)


    time.sleep(0.1)
