# Author: Jake G
# Date: 2024
# FileName: cam.py
# Description: Calls C interface functions for camera.
import ctypes
from ctypes import CDLL
from ctypes import c_uint8, c_int, c_char, c_bool, c_float
from ctypes import c_void_p
from enum import Enum

import cv2 as cv
import numpy as np
import platform

WIDTH = 1280
HEIGHT = 1024
NUMPIXELS = 1310720
MIRROR_FRAME = True

# Handle the OS specific shared library.
if(platform.system() == "Linux"):
    print("UNIX PLATFORM FOUND!")
    SHARED_LIB = "./shared/libcamera_handler.so"
else:
    print("WIN32 PLATFORM FOUND!")
    SHARED_LIB = "./shared/libcamera_handler.dll"


# Used as an enum to pass into functions
class eAGC(Enum):
    no_agc = 0
    agc_eq_history = 1
    agc_local = 2
    agc_linear = 3
    agc_total = 4


# Moved defaults into global scope for use in demo functions
DEF_FPS = 60.0
DEF_AGC = eAGC.agc_eq_history.value
DEF_SL = 1
DEF_BP = 1
DEF_NUC = 1


def init(fps=60.0, SL=True, BP=1, AGC=2, nuc=1):
    camlib = CDLL(SHARED_LIB)

    # HANDLE init_camera(float fps, bool SL, char BP, uint8_t agc, char nuc);
    camlib.init_camera.argtypes = [c_float, c_bool, c_char, c_uint8, c_char]
    camlib.init_camera.restype = c_void_p
    handle = camlib.init_camera(fps, SL, BP, AGC, nuc)
    return handle


def num_attached():
    camlib = CDLL(SHARED_LIB)

    # int num_attached(void);
    camlib.num_attached.argtypes = []
    camlib.num_attached.restype = c_int
    n = camlib.num_attached()
    return n


def close_camera(h):
    camlib = CDLL(SHARED_LIB)

    # int close_camera(void);
    camlib.close_camera.argtypes = [c_void_p]
    camlib.close_camera.restype = c_int
    r = camlib.close_camera(h)
    return r


def load_frame_buffer(h):
    camlib = CDLL(SHARED_LIB)

    # int load_frame_buffer(HANDLE camera_handle);
    camlib.load_frame_buffer.argtypes = [c_void_p]
    camlib.load_frame_buffer.restype = c_int
    r = camlib.load_frame_buffer(h)
    return r


def get_paimage():
    arr = np.zeros(NUMPIXELS, dtype=np.uint16)
    c_arr = arr.astype(np.intc)
    camlib = CDLL(SHARED_LIB)

    # void get_paimage(int *arr);
    camlib.get_paimage.argtypes = [ctypes.POINTER(ctypes.c_int)]
    camlib.get_paimage.restype = None

    c_array_ptr = ctypes.cast(c_arr.ctypes.data, ctypes.POINTER(ctypes.c_int))

    camlib.get_paimage(c_array_ptr)
    arr = c_arr.view(dtype=np.uint16)
    return c_array_ptr


# Doesn't do anything unless called from C
def print_paimage():
    camlib = CDLL(SHARED_LIB)

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
    camlib.clear_paimage.restype = None
    camlib.clear_paimage()


def clear_matrix():
    camlib = CDLL(SHARED_LIB)

    # void clear_matrix(void);
    camlib.clear_matrix.argtypes = []
    camlib.clear_matrix.restype = None
    camlib.clear_matrix()


def shutter_cal(h):
    camlib = CDLL(SHARED_LIB)

    # int shutter_calibration(HANDLE h);
    camlib.shutter_calibration.argtypes = [c_void_p]
    camlib.shutter_calibration.restype = c_int
    return camlib.shutter_calibration(h)


def two_point_shutter_cal(h, iStage):
    camlib = CDLL(SHARED_LIB)

    # int shutter_2pts_calibration(HANDLE h, int iStage);
    camlib.shutter_2pts_calibration.argtypes = [c_void_p, c_int]
    camlib.shutter_2pts_calibration.restype = c_int
    return camlib.shutter_2pts_calibration(h, iStage)


def shutterless_cal_T0(h, iStage):
    camlib = CDLL(SHARED_LIB)

    # int sl_calibration_t0(HANDLE h, int iStage);
    camlib.sl_calibration_t0.argtypes = [c_void_p, c_int]
    camlib.sl_calibration_t0.restype = c_int
    return camlib.sl_calibration_t0(h, iStage)


def shutterless_cal_T1(h):
    camlib = CDLL(SHARED_LIB)

    # int sl_calibration_t1(HANDLE h);
    camlib.sl_calibration_t1.argtypes = [c_void_p]
    camlib.sl_calibration_t1.restype = c_int
    return camlib.sl_calibration_t1(h)


def fast_cal_save(h):
    camlib = CDLL(SHARED_LIB)

    # int save_calibration(HANDLE h);
    camlib.save_calibration.argtypes = [c_void_p]
    camlib.save_calibration.restype = c_int
    return camlib.save_calibration(h)


def calibrate_camera(h):
    print("CALIBRATION:\nFast calibration --> `shutter_cal()`")
    print("The camera's lense should be covered at this point!")
    shutter_cal(h)
    print("Calibration done...saving...\n")
    res = fast_cal_save(h)
    print("save_calibration() --> " + str(res))
    return res


def demo_video(set_8bit):
    clear_matrix()
    clear_paimage()
    h = init(fps=DEF_FPS, SL=DEF_SL, BP=DEF_BP, AGC=DEF_AGC, nuc=DEF_NUC)

    while(True):
        load_frame_buffer(h)
        load_matrix_buffer(False)
        mat = get_frame_matrix()

        if(set_8bit):
            mat = cv.normalize(
                    mat,
                    None,
                    0,
                    255,
                    cv.NORM_MINMAX).astype(np.uint8)

        mat = (mat/256).astype('uint8')
        newmat = np.ones(NUMPIXELS, dtype=np.uint8).reshape(HEIGHT, WIDTH, order="C")
        cv.equalizeHist(mat, newmat)
        cv.imshow('data', newmat)
        key = cv.waitKey(16)

        if key == ord('q'):
            break

    cv.destroyAllWindows()
    close_camera(h)


def demo_image(set_8bit):
    clear_matrix()
    clear_paimage()
    h = init(fps=DEF_FPS, SL=DEF_SL, BP=DEF_BP, AGC=DEF_AGC, nuc=DEF_NUC)

    load_frame_buffer(h)
    load_matrix_buffer(False)
    mat = get_frame_matrix()

    close_camera(h)

    if(set_8bit):
        mat = cv.normalize(
                mat,
                None,
                0,
                255,
                cv.NORM_MINMAX).astype(np.uint8)

    mat = (mat/256).astype('uint8')
    newmat = np.ones(NUMPIXELS, dtype=np.uint8).reshape(HEIGHT, WIDTH, order="C")
    cv.equalizeHist(mat, newmat)
    cv.imshow('data', mat)
    cv.waitKey(0)
    cv.destroyAllWindows()
