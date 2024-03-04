# Author: Jake G
# Date: 2024
# FileName: cam.py
# Description: Calls C interface functions for camera.

import ctypes
from ctypes import CDLL
from ctypes import c_uint8, c_int, c_char, c_bool, c_float
from ctypes import c_void_p, c_char_p
from enum import Enum

import cv2 as cv
import numpy as np
import platform
import os
import os.path


WIDTH = 1280
HEIGHT = 1024
NUMPIXELS = 1310720
MIRROR_FRAME = True

clahe = cv.createCLAHE(5, (5, 5))
img = np.ones(NUMPIXELS, dtype=np.uint16).reshape(HEIGHT, WIDTH, order="C")

# Handle the OS specific shared library.
if platform.system() == "Linux":
    print("UNIX PLATFORM FOUND!")
    SHARED_LIB = "./shared/libcamera_handler.so"
else:
    print("WIN32 PLATFORM FOUND!")
    SHARED_DIR = "./shared/"
    dll_path = os.path.abspath(SHARED_DIR)
    os.add_dll_directory(dll_path)
    DALPROXY_LIB = SHARED_DIR + "DALProxy1280_12USB_x64.dll"
    SHARED_LIB = SHARED_DIR + "camera_handler.dll"


# Used as an enum to pass into functions
class eAGC(Enum):
    no_agc = 0
    agc_eq_history = 1
    agc_local = 2
    agc_linear = 3
    agc_total = 4


# Moved defaults into global scope for use in demo functions
DEF_FPS = 60.0
DEF_AGC = eAGC.agc_linear.value
DEF_SL = True
DEF_BP = 1
DEF_NUC = 1
DEF_COLORMAP = "inferno"


def init(fps=DEF_FPS, SL=DEF_SL, BP=DEF_BP, AGC=DEF_AGC, nuc=DEF_NUC):
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


def set_agc(h, agc_value):
    camlib = CDLL(SHARED_LIB)
    return 0
    # int set_agc(HANDLE h, unsigned char agc)
    camlib.set_agc.argtypes = [c_void_p, c_char]
    camlib.set_agc.restype = c_int
    r = camlib.set_agc(h, c_char(agc_value))
    return r


def get_agc(h, agc_value):
    camlib = CDLL(SHARED_LIB)
    AGC_PTR = c_char_p(agc_value)

    # int get_agc(HANDLE h, unsigned char *agc)
    camlib.get_agc.argtypes = [c_void_p, c_char_p]
    camlib.get_agc.restype = c_int
    r = camlib.get_agc(h, AGC_PTR)
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
    ND_POINTER_2 = np.ctypeslib.ndpointer(dtype=np.uint16, ndim=2, flags="C")

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
    r = camlib.sl_calibration_t0(h, iStage)
    return r


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


def controller(img, brightness=255, contrast=127):
    brightness = int((brightness - 0) * (255 - (-255)) / (510 - 0) + (-255))
    contrast = int((contrast - 0) * (127 - (-127)) / (254 - 0) + (-127))

    if brightness != 0:
        if brightness > 0:
            shadow = brightness
            max = 255
        else:
            shadow = 0
            max = 255 + brightness

        al_pha = (max - shadow) / 255
        ga_mma = shadow

        # The function addWeighted calculates
        # the weighted sum of two arrays
        cal = cv.addWeighted(img, al_pha, img, 0, ga_mma)

    else:
        cal = img
    if contrast != 0:
        Alpha = float(131 * (contrast + 127)) / (127 * (131 - contrast))
        Gamma = 127 * (1 - Alpha)

        # The function addWeighted calculates
        # the weighted sum of two arrays
        cal = cv.addWeighted(cal, Alpha, cal, 0, Gamma)

    return cal


def BrightnessContrast(img, brightness=0):
    # getTrackbarPos returns the current
    # position of the specified trackbar.
    brightness = cv.getTrackbarPos("Brightness", "Brightness/Contrast")

    contrast = cv.getTrackbarPos("Contrast", "Brightness/Contrast")

    effect = controller(img, brightness, contrast)

    return effect


def adjust_img(mat, color_map):
    img8 = cv.normalize(mat, None, 0, 255, cv.NORM_MINMAX).astype(np.uint8)
    img8 = np.uint8(img8)

    adj = clahe.apply(img8)
    adj = cv.cvtColor(adj, cv.COLOR_GRAY2BGR)

    adj2 = BrightnessContrast(img8.copy())
    adj2 = cv.cvtColor(adj2, cv.COLOR_GRAY2BGR)

    if color_map == "none":
        pass
    elif color_map == "inferno":
        adj = cv.applyColorMap(adj, cv.COLORMAP_INFERNO)
        adj2 = cv.applyColorMap(adj2, cv.COLORMAP_INFERNO)
    elif color_map == "jet":
        adj = cv.applyColorMap(adj, cv.COLORMAP_JET)
        adj2 = cv.applyColorMap(adj2, cv.COLORMAP_JET)
    elif color_map == "viridis":
        adj = cv.applyColorMap(adj, cv.COLORMAP_VIRIDIS)
        adj2 = cv.applyColorMap(adj2, cv.COLORMAP_VIRIDIS)
    else:
        pass

    return (adj, adj2)


def demo_image():
    global img

    clear_matrix()
    clear_paimage()
    h = init(fps=DEF_FPS, SL=DEF_SL, BP=DEF_BP, AGC=DEF_AGC, nuc=DEF_NUC)

    # We load a bunch of frames after init of the camera to get some history.
    for i in range(0, 120):
        load_frame_buffer(h)
        load_matrix_buffer(False)
        img = get_frame_matrix()

    close_camera(h)

    cv.namedWindow("CLAHE filter", cv.WINDOW_GUI_EXPANDED)
    cv.namedWindow("Brightness/Contrast", cv.WINDOW_GUI_EXPANDED)

    cv.createTrackbar(
        "Brightness", "Brightness/Contrast", 255, 2 * 255, BrightnessContrast
    )

    # Contrast range -127 to 127
    cv.createTrackbar(
        "Contrast", "Brightness/Contrast", 127, 2 * 127, BrightnessContrast
    )

    while True:
        (adj, adj2) = adjust_img(img, DEF_COLORMAP)
        cv.imshow("CLAHE filter", adj)
        cv.imshow("Brightness/Contrast", adj2)

        key = cv.waitKey(16)
        if key == ord("q"):
            break

    cv.destroyAllWindows()


def demo_video():
    global img
    clear_matrix()
    clear_paimage()
    h = init(fps=DEF_FPS, SL=DEF_SL, BP=DEF_BP, AGC=DEF_AGC, nuc=DEF_NUC)

    cv.namedWindow("CLAHE filter", cv.WINDOW_GUI_EXPANDED)
    cv.namedWindow("Brightness/Contrast", cv.WINDOW_GUI_EXPANDED)

    cv.createTrackbar(
        "Brightness", "Brightness/Contrast", 255, 2 * 255, BrightnessContrast
    )

    # Contrast range -127 to 127
    cv.createTrackbar(
        "Contrast", "Brightness/Contrast", 127, 2 * 127, BrightnessContrast
    )

    while True:
        load_frame_buffer(h)
        load_matrix_buffer(False)
        img = get_frame_matrix()

        (adj, adj2) = adjust_img(img, DEF_COLORMAP)

        cv.imshow("CLAHE filter", adj)
        cv.imshow("Brightness/Contrast", adj2)

        key = cv.waitKey(16)
        if key == ord("q"):
            break

    cv.destroyAllWindows()
    close_camera(h)
