# Author: Jake G
# Date: 2024
# Description: Simple demo
# Filename: demo.py


# Import the python camera interface
import cam


def display_menu():
    print("Menu:")
    print("1. Show Video")
    print("2. Show Image")
    print("3. Fast Calibration")
    print("4. Change Color Map")
    print("0. Quit")


def get_choice():
    while True:
        try:
            choice = int(input("Enter your choice (0-4): "))
            if choice in [0, 1, 2, 3, 4]:
                return choice
            else:
                print("Invalid choice. Please enter a value from 0 to 4")
        except ValueError:
            print("Invalid input. Please enter a number.")


def display_colormap_menu():
    info = "Default Color Map: " + str(cam.DEF_COLORMAP)
    info += "\n Available: none, jet, inferno, viridis\n"
    print(info)
    cam.DEF_COLORMAP = input("Enter Color Map name:")
    print("cam.DEF_COLORMAP " + str(cam.DEF_COLORMAP))


def display_cal_menu():
    help = "INFO: Place the black body(radiative/hot) source front of lens.\n"
    help += "This calibration is a single point process to generate new \n"
    help += "offset values\n"
    print(help)
    print("Calibration Menu:")
    print("1. Yes I want to run fast calibration.")
    print("2. No I don't want to run fast calibration.")


def get_cal_choice():
    while True:
        try:
            choice = int(input("Enter your choice (1-2): "))
            if choice in [1, 2]:
                return choice
            else:
                print("Invalid choice. Please enter a value from 1 to 2")
        except ValueError:
            print("Invalid input. Please enter a number.")


def calibration_process():
    display_cal_menu()
    choice = get_cal_choice()

    if choice == 2:
        return

    h = cam.init(fps=cam.DEF_FPS,
                 SL=cam.DEF_SL,
                 BP=cam.DEF_BP,
                 AGC=cam.DEF_AGC,
                 nuc=cam.DEF_NUC)

    cam.calibrate_camera(h)
    cam.close_camera(h)


def main():

    num = cam.num_attached()
    if num < 1:
        print("ERROR: Please check the camera's connection")
        exit(-1)

    while True:
        display_menu()
        choice = get_choice()

        if choice == 0:
            break
        elif choice == 1:
            # Run the camera demo
            cam.demo_video()
        elif choice == 2:
            # Run the Image demo
            cam.demo_image()
        elif choice == 3:
            calibration_process()
        elif choice == 4:
            display_colormap_menu()


def test():
    cam.load_image()
    cam.test_image()


main()
