import pytest
import cam
from ctypes import CDLL  # , POINTER
from ctypes import c_size_t, c_void_p
import numpy as np
# import cv2 as cv
# import matplotlib.pyplot as plt


def f():
    raise SystemExit(1)


def test_mytest():
    with pytest.raises(SystemExit):
        f()


class TestCam:
    cam_address = c_void_p(0x12345678)

    def test_init(self):
        handle = cam.init()
        assert(str(hex(handle)) == "0x12345678")
        assert(handle == self.cam_address.value)

    def test_num_attached(self):
        n = cam.num_attached()
        assert(n == 1)

    def test_close_camera(self):
        h = c_void_p(None)
        n = cam.close_camera(h)
        assert(n == 2)

        h = self.cam_address
        n = cam.close_camera(h)
        assert(n == 0)

    def test_load_frame_buffer(self):
        h = c_void_p(None)
        r = cam.load_frame_buffer(h)
        assert(r == 2)

        h = self.cam_address
        r = cam.load_frame_buffer(h)
        assert(r == 2)

        h = cam.init()
        r = cam.load_frame_buffer(h)
        assert(r == 0)

    def test_get_paimage(self):
        assert(False)


class TestC:
    def test_c_interop(self):
        # load the library
        mylib = CDLL("./mylib.so")
        # C-type corresponding to numpy array
        ND_POINTER_1 = np.ctypeslib.ndpointer(
                dtype=np.float64,
                ndim=1,
                flags="C")
        # define prototypes
        mylib.print_array.argtypes = [ND_POINTER_1, c_size_t]
        mylib.print_array.restype = None

        # create array X = [1 1 1 1 1]
        X = np.ones(5)
        X[4] = 9
        # call function
        mylib.print_array(X, X.size)
        assert(True)

    def test_c_interop_u16(self):
        # load the library
        mylib = CDLL("./mylib.so")
        # C-type corresponding to numpy array
        ND_POINTER_1 = np.ctypeslib.ndpointer(
                dtype=np.uint16,
                ndim=1,
                flags="C")
        # define prototypes
        mylib.print_u16.argtypes = [ND_POINTER_1, c_size_t]
        mylib.print_u16.restype = None

        # create array X = [1 1 1 1 1]
        X = np.ones(5, dtype=np.uint16)
        X[4] = 9
        # call function
        mylib.print_u16(X, X.size)
        assert(True)

    def test_c_interop_u16_2D(self):
        # load the library
        mylib = CDLL("./mylib.so")
        # C-type corresponding to numpy array
        ND_POINTER_2 = np.ctypeslib.ndpointer(
                dtype=np.uint16,
                ndim=2,
                flags="C")

        # define prototypes
        mylib.print_matrix.argtypes = [ND_POINTER_2, c_size_t]
        mylib.print_matrix.restype = None

        M = np.arange(1, 10, 1, dtype=np.uint16).reshape(3, 3, order="C")
        # call function
        mylib.print_matrix(M, *M.shape)
        assert(True)

    def test_c_interop_u16_2D_edit(self):
        # void clear_u16_mat(uint16_t *v, size_t n, size_t p)
        # load the library
        mylib = CDLL("./mylib.so")
        # C-type corresponding to numpy array
        ND_POINTER_2 = np.ctypeslib.ndpointer(
                dtype=np.uint16,
                ndim=2,
                flags="C")

        # define prototypes
        mylib.clear_u16_mat.argtypes = [ND_POINTER_2, c_size_t]
        mylib.clear_u16_mat.restype = None
        mylib.print_matrix.argtypes = [ND_POINTER_2, c_size_t]
        mylib.print_matrix.restype = None

        M = np.arange(1, 10, 1, dtype=np.uint16).reshape(3, 3, order="C")
        # call function
        mylib.clear_u16_mat(M, *M.shape)
        mylib.print_matrix(M, *M.shape)

        for x in np.nditer(M):
            print(x, end=' ')
            assert(x == 0)
        assert(True)

    def test_numpy_1d_array(self):
        assert True
