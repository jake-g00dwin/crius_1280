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
    print("0. Quit")


def get_choice():
    while True:
        try:
            choice = int(input("Enter your choice (0-3): "))
            if choice in [0, 1, 2, 3]:
                return choice
            else:
                print("Invalid choice. Please enter a value from 0 to 3")
        except ValueError:
            print("Invalid input. Please enter a number.")


def main():
    # Change this to false to attempt displaying 16bit grayscale
    # Most monitors can't actually display 65,536 shades of gray however.
    set_8bit = False

    num = cam.num_attached()
    if(num < 1):
        print("ERROR: Please check the camera's connection")
        exit(-1)

    while True:
        display_menu()
        choice = get_choice()

        if choice == 0:
            break
        elif choice == 1:
            # Run the camera demo
            cam.demo_video(set_8bit)
        elif choice == 2:
            # Run the Image demo
            cam.demo_image(set_8bit)
        elif choice == 3:
            h = cam.init(fps=30.0, SL=True, BP=1, AGC=0, nuc=1)
            cam.calibrate_camera(h)
            cam.close_camera(h)


main()
