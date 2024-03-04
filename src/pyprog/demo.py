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
    print("3. Calibration Menu")
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
    print("1. Quick Calibration.")
    print("2. SL(shutterless) T0 Calibration.")
    print("3. SL(shutterless) T1 Calibration.")
    print("0. <-- Go Back to Main Menu")


def get_cal_choice():
    while True:
        try:
            choice = int(input("Enter your choice (1-3): "))
            if choice in [0, 1, 2, 3, 4]:
                return choice
            else:
                print("Invalid choice. Please enter a value from 0 to 3")
        except ValueError:
            print("Invalid input. Please enter a number.")


def calibration_process():
    display_cal_menu()
    choice = get_cal_choice()

    if choice == 0:
        return

    elif choice == 1:
        h = cam.init(fps=cam.DEF_FPS,
                     SL=cam.DEF_SL,
                     BP=0,
                     AGC=0,
                     nuc=0)
        print("Please place cold source in front of lens.")
        input("Hit enter to start:")
        cam.calibrate_camera(h)
        cam.close_camera(h)

    elif choice == 2:
        h = cam.init(fps=cam.DEF_FPS,
                     SL=1,
                     BP=0,
                     AGC=0,
                     nuc=0)
        print("Please place cold source in front of lens.")
        input("Hit enter to start:")
        cam.shutterless_cal_T0(h, 0)

        print("Please place hot source in front of lens.")
        input("Hit enter to start:")
        cam.shutterless_cal_T0(h, 1)

        cam.close_camera(h)

    elif choice == 3:
        h = cam.init(fps=cam.DEF_FPS,
                     SL=cam.DEF_SL,
                     BP=0,
                     AGC=0,
                     nuc=0)
        res = cam.shutterless_cal_T1(h)
        print("Shutterless Calibration results:")
        if res == 0:
            print("Sucess!")
        else:
            print("Error: " + str(res))
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
