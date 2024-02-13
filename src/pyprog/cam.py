#
# test.py
#
from ctypes import CDLL, POINTER
from ctypes import c_size_t, c_double

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


def main():
    print("TESTING!\n")

    camlib = CDLL("./shared/libcamera_handler.so")

    # check it works
    camlib.cam_self_test()
    camlib.cam_self_test.restype = int

    print("cam_self_test(): " + str(camlib.cam_self_test()))

    # Pass in args to the C function to get a camera 'HANDLE' type.
    # camera_handle = camlib.init_camera()

    # Now request frame/image from the camera that's formatted.
    ND_POINTER_1 = np.ctypeslib.ndpointer(dtype=np.uint16, ndim=2, flags="C")

    # define prototypes camlib
    camlib.get_frame(ND_POINTER_1, c_size_t)
    camlib.get_fame.restype = None


main()
# check_img()
