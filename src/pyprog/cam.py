#
# test.py
#
from ctypes import CDLL, POINTER, pointer
from ctypes import c_size_t, c_double, c_uint8, c_int, c_char, c_bool, c_float

import cv2 as cv
import numpy as np


def quicktest():
    # load the library
    # mylib = CDLL("mylib.so")
    mylib = CDLL("./mylib.so")

    # C-type corresponding to numpy array
    ND_POINTER_1 = np.ctypeslib.ndpointer(dtype=np.float64,
                                          ndim=1,
                                          flags="C")

    # define prototypes
    mylib.print_array.argtypes = [ND_POINTER_1, c_size_t]
    mylib.print_array.restype = None

    # create array X = [1 1 1 1 1]
    X = np.ones(5)
    # call function
    mylib.print_array(X, X.size)


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

    cam_handle = POINTER(c_int)

    camlib.close_camera(cam_handle)
    camlib.close_camera.restype = c_int

    camlib.init_camera.argtypes = [c_float, c_bool, c_bool, c_uint8, c_char]
    camlib.init_camera.restype = cam_handle

    # int load_frame_buffer(int *camera_handle)
    camlib.load_frame_buffer(cam_handle)
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
    number_modules = camlib.num_attached()
    print("camlib.num_attached(): " + str(number_modules))

    handle = camlib.init_camera(1, False, False, 0, 0)
    print("camlib.init_camera(): " + str(handle))

    # show that we can get camera frames.
    result = camlib.load_frame_buffer(handle)
    print("camlib.load_frame_buffer(handle): " + str(result))

    # create a empty 2D array for filling.
    mat = np.ones((1280, 1024), dtype=np.uint16)
    camlib.get_frame_matrix(mat)

    print("image data:" + str(mat))

    # Close the camera, using the SDK wrapper.
    print("camlib.close_camera(): " + str(camlib.close_camera(handle)))

    # Now request frame/image from the camera that's formatted.
    # ND_POINTER_1 = np.ctypeslib.ndpointer(dtype=np.uint16, ndim=2, flags="C")

    # define prototypes camlib
    # camlib.get_frame(ND_POINTER_1, c_size_t)
    # camlib.get_fame.restype = None


main()
# check_img()
