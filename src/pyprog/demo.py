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
    print("0. Quit")


def get_choice():
    while True:
        try:
            choice = int(input("Enter your choice (0/1/2): "))
            if choice in [0, 1, 2]:
                return choice
            else:
                print("Invalid choice. Please enter 0, 1 or 2.")
        except ValueError:
            print("Invalid input. Please enter a number.")


def main():
    # Change this to false to attempt displaying 16bit grayscale
    # Most monitors can't actually display 65,536 shades of gray however.
    set_8bit = True

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


main()
