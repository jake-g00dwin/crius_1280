# Author: Jake G
# Date: 2023
# FileName: cam.py
# Description: Calls C interface functions for camera.
import ctypes
from ctypes import CDLL, POINTER
from ctypes import c_uint8, c_int, c_char, c_bool, c_float
from ctypes import c_void_p

import cv2 as cv
import numpy as np
# import matplotlib.pyplot as plt

WIDTH = 1280
HEIGHT = 1024
NUMPIXELS = 1310720
MIRROR_FRAME = True
SHARED_LIB = "./shared/libcamera_handler.so"


def init():
    camlib = CDLL("./shared/libcamera_handler.so")

    # HANDLE init_camera(float fps, bool SL, char BP, uint8_t agc, char nuc);
    camlib.init_camera.argtypes = [c_float, c_bool, c_char, c_uint8, c_char]
    camlib.init_camera.restype = c_void_p
    fps = c_float(60.0)
    handle = camlib.init_camera(fps, True, 1, 2, 1)
    return handle


def num_attached():
    camlib = CDLL("./shared/libcamera_handler.so")

    # int num_attached(void);
    camlib.num_attached.argtypes = []
    camlib.num_attached.restype = c_int
    n = camlib.num_attached()
    return n


def close_camera(h):
    camlib = CDLL("./shared/libcamera_handler.so")

    # int close_camera(void);
    camlib.close_camera.argtypes = [c_void_p]
    camlib.close_camera.restype = c_int
    r = camlib.close_camera(h)
    return r


def load_frame_buffer(h):
    camlib = CDLL("./shared/libcamera_handler.so")

    # int load_frame_buffer(HANDLE camera_handle);
    camlib.load_frame_buffer.argtypes = [c_void_p]
    camlib.load_frame_buffer.restype = c_int
    r = camlib.load_frame_buffer(h)
    return r


def get_paimage():
    arr = np.zeros(NUMPIXELS, dtype=np.uint16)
    c_arr = arr.astype(np.intc)
    camlib = CDLL("./shared/libcamera_handler.so")

    # void get_paimage(int *arr);
    camlib.get_paimage.argtypes = [ctypes.POINTER(ctypes.c_int)]
    camlib.get_paimage.restype = None

    c_array_ptr = ctypes.cast(c_arr.ctypes.data, ctypes.POINTER(ctypes.c_int))

    camlib.get_paimage(c_array_ptr)
    arr = c_arr.view(dtype=np.uint16)
    return c_array_ptr


# Doesn't do anything unless called from C
def print_paimage():
    camlib = CDLL("./shared/libcamera_handler.so")

    # void print_paimage(void);
    camlib.print_paimage.argtypes = []
    camlib.print_paimage.restype = c_int
    camlib.print_paimage()


def load_matrix_buffer(swap_endian):
    camlib = CDLL(SHARED_LIB)

    # void load_matrix_buffer(bool endian_swap);
    camlib.load_matrix_buffer.argtypes = [c_bool]
    camlib.load_matrix_buffer.restype = None
    b = c_bool(swap_endian)
    camlib.load_matrix_buffer(b)


def get_frame_matrix():
    camlib = CDLL(SHARED_LIB)
    # C-type corresponding to numpy array
    ND_POINTER_2 = np.ctypeslib.ndpointer(
            dtype=np.uint16,
            ndim=2,
            flags="C")

    # void get_frame_matrix(uint16_t *mat, size_t n, size_t p);
    camlib.get_frame_matrix.argtypes = [ND_POINTER_2, ctypes.c_size_t]
    camlib.get_frame_matrix.restype = None

    M = np.ones(NUMPIXELS, dtype=np.uint16).reshape(HEIGHT, WIDTH, order="C")
    camlib.get_frame_matrix(M, *M.shape)
    return M


def clear_paimage():
    camlib = CDLL(SHARED_LIB)

    # void clear_paimage(void);
    camlib.clear_paimage.argtypes = []
    camlib.clear_paimage.argtypes = None
    camlib.clear_paimage()


def clear_matrix():
    camlib = CDLL(SHARED_LIB)

    # void clear_matrix(void);
    camlib.clear_matrix.argtypes = []
    camlib.clear_matrix.argtypes = None
    camlib.clear_matrix()


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


def define_c_funcs(camlib):

    # int num_attached(void);
    camlib.num_attached()
    camlib.num_attached.restype = c_uint8

    # int close_camera(HANDLE *camera_handle);
    camlib.close_camera.argtypes = [c_void_p]
    camlib.close_camera.restype = c_int

    # HANDLE init_camera(float fps, bool SL, char BP, uint8_t agc, char nuc);
    camlib.init_camera.argtypes = [c_float, c_bool, c_char, c_uint8, c_char]
    camlib.init_camera.restype = c_void_p

    # int load_frame_buffer(HANDLE camera_handle);
    camlib.load_frame_buffer.argtypes = [c_void_p]
    camlib.load_frame_buffer.restype = c_int

    # void load_matrix_buffer(bool endian_swap);
    camlib.load_matrix_buffer.argtypes = [c_bool]
    camlib.load_matrix_buffer.restype = None

    # void get_frame_matrix(uint16_t *mat)
    ND_POINTER_2 = np.ctypeslib.ndpointer(dtype=np.uint16, ndim=2, flags="C")
    camlib.get_frame_matrix.argtypes = [ND_POINTER_2]
    camlib.get_frame_matrix.restype = None

    # void get_paimage(uint16_t *arr);
    ND_POINTER = np.ctypeslib.ndpointer(dtype=np.uint16, ndim=1, flags="C")
    camlib.get_paimage.argtypes = [ND_POINTER]
    camlib.get_paimage.restype = c_int


def get_frame(camlib, handle, mat):
    res = camlib.load_frame_buffer(handle)
    if res != 0:
        print("Error getting new frame!")
    camlib.load_matrix_buffer(False)
    camlib.get_frame_matrix(mat)
    if MIRROR_FRAME:
        mat = np.rot90(mat)
        mat = np.rot90(mat)


def start_video_loop(camlib, handle, mat):
    # frame = np.zeros((1024, 1280), dtype=np.uint16)
    arr = np.zeros(1024 * 1280, dtype=np.uint16)
    print("Size of the array:", arr.size)
    print("array data" + str(arr))
    while True:
        # get_frame(camlib, handle, mat)
        get_paimage(camlib, handle, arr)
        frame = arr.reshape((1024, 1280))

        # Now we compress dowwn the bitdepth to make it viewable.
        frame = cv.normalize(mat,
                             None,
                             0,
                             255,
                             cv.NORM_MINMAX).astype(np.uint8)

        cv.imshow('Video', frame)
        if cv.waitKey(500) & 0xFF == ord('q'):
            break


def start_image_plot_loop(camlib, handle, mat):
    while True:
        user_input = input("Do you want to continue? (y/n): ")
        if user_input.lower() == 'n':
            print("Exiting...")
            break
        elif user_input.lower() != 'y':
            print("Invalid. Please enter 'y' to continue or 'n' to exit.")
        else:
            print("Continuing...")
            get_frame(camlib, handle, mat)
            # plt.imshow(mat, cmap='gray')
            # plt.axis('off')  # Turn off axis numbers
            # plt.show()


def main():
    # create a empty 2D array for filling.
    mat = np.zeros((HEIGHT, WIDTH), dtype=np.uint16)

    print("Loading shared libs...")
    camlib = CDLL("./shared/libcamera_handler.so")

    print("defining C function params...")
    define_c_funcs(camlib)

    number_modules = camlib.num_attached()
    print("camlib.num_attached(): " + str(number_modules))
    if number_modules == 0:
        return

    # handle = c_void_p()
    handle = camlib.init_camera(60, True, 1, 2, 1)
    print("camlib.init_camera(): " + str(handle))

    # show that we can get camera frames.
    result = camlib.load_frame_buffer(handle)
    print("camlib.load_frame_buffer(handle): " + str(result))

    # tell the shared library to change the 1D array into to big-endian
    # 2D matrix that we can use.
    camlib.load_matrix_buffer(True)

    # Get the matrix info.
    camlib.get_frame_matrix(mat)

    # Now do it in a function call.
    get_frame(camlib, handle, mat)

    print("matrix:" + str(mat))
    # plt.imshow(mat, cmap='gray')
    # plt.axis('off')  # Turn off axis numbers
    # plt.show()

    while True:
        # Showing two diffent ways to display the data.
        display_menu()
        choice = get_choice()
        if choice == 0:
            break
        elif choice == 1:
            start_video_loop(camlib, handle, mat)
        elif choice == 2:
            start_image_plot_loop(camlib, handle, mat)

    # Close the camera, using the SDK wrapper.
    print("camlib.close_camera(): " + str(camlib.close_camera(handle)))


def t():
    # create a empty 2D array for filling.
    mat = np.zeros((HEIGHT, WIDTH), dtype=np.uint16)

    print("Loading shared libs...")
    camlib = CDLL("./shared/libcamera_handler.so")

    print("defining C function params...")
    define_c_funcs(camlib)

    number_modules = camlib.num_attached()
    print("camlib.num_attached(): " + str(number_modules))
    if number_modules == 0:
        return

    h = c_void_p()
    print("py->*handle: " + str(hex(id(h))))
    h = camlib.init_camera(60, True, 1, 2, 1)
    print("py->*handle: " + str(hex(id(h))))
    print("py->handle: " + str(hex(h)))

    res = camlib.load_frame_buffer(h)
    print("load_frame_buffer: " + str(res))

    camlib.load_matrix_buffer(False)

    M = np.ones(1310720, dtype=np.uint16).reshape(1024, 1280, order="C")
    camlib.get_frame_matrix(M)
    print(M)

    cv.imshow('data', mat)
    cv.waitKey(0)
    cv.destroyAllWindows()


# main()
# t()
