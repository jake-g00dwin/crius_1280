#
# test.py
#
from ctypes import CDLL, POINTER
from ctypes import c_size_t, c_double
# from ctypes import *
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


def main():
    camlib = CDLL("./camera_handler.so")
    # Pass in args to the C function to get a camera 'HANDLE' type.
    camera_handle = camlib.init_camera()

    # Now request frame/image from the camera that's formatted.
    ND_POINTER_1 = np.ctypeslib.ndpointer(dtype=np.uint16, ndim=2, flags="C")

    #define prototypes camlib
    camlib.get_frame(ND_POINTER_1, c_size_t)
    camlib.get_fame.restype = None

main
