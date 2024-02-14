# Author: Jake G
# Date: 2023
# FileName: cam.py
# Description: Calls C interface functions for camera.

from ctypes import CDLL, POINTER, pointer
from ctypes import c_size_t, c_uint8, c_int, c_char, c_bool, c_float, c_long
from ctypes import byref

import cv2 as cv
import numpy as np


# Displays the image in a window
def check_img():
    img = cv.imread("./image.pgm")
    cv.imshow("IR CAM", img)
    k = cv.waitKey(0)
    return k


def define_c_funcs(camlib):
    # check it works
    camlib.cam_self_test()
    camlib.cam_self_test.restype = c_int

    camlib.num_attached()
    camlib.num_attached.restype = c_uint8

    camlib.close_camera.argtypes = [POINTER(c_long)]
    camlib.close_camera.restype = c_int

    # HANDLE init_camera(float fps, bool SL, char BP, uint8_t agc, char nuc);
    camlib.init_camera.argtypes = [c_float, c_bool, c_char, c_uint8, c_char]
    camlib.init_camera.restype = POINTER(c_long)

    # int load_frame_buffer(HANDLE camera_handle);
    camlib.load_frame_buffer.argtypes = [POINTER(c_long)]
    camlib.load_frame_buffer.restype = c_int

    # void get_frame_matrix(uint16_t *mat)
    ND_POINTER = np.ctypeslib.ndpointer(dtype=np.uint16, ndim=2, flags="C")
    camlib.get_frame_matrix.argtypes = [ND_POINTER]


def main():
    print("Loading shared libs...")
    camlib = CDLL("./shared/libcamera_handler.so")

    print("defining C function params...")
    define_c_funcs(camlib)

    print("cam_self_test(): " + str(camlib.cam_self_test()))

    # number_modules = camlib.num_attached()
    # print("camlib.num_attached(): " + str(number_modules))

    handle = c_long()
    handle = camlib.init_camera(1, False, False, 0, 0)
    print("camlib.init_camera(): " + str(handle))

    # show that we can get camera frames.
    # result = camlib.load_frame_buffer(handle)
    # print("camlib.load_frame_buffer(handle): " + str(result))

    # create a empty 2D array for filling.
    mat = np.ones((1280, 1024), dtype=np.uint16)
    camlib.get_frame_matrix(byref(mat))

    print("image data:" + str(mat))

    # Close the camera, using the SDK wrapper.
    print("camlib.close_camera(): " + str(camlib.close_camera(handle)))


main()
# check_img()
