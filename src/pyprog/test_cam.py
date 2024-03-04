import pytest
import cam
from ctypes import CDLL  # , POINTER
from ctypes import c_size_t, c_void_p, c_char, c_char_p
import numpy as np

# import cv2 as cv
# import matplotlib.pyplot as plt


def f():
    raise SystemExit(1)


def test_mytest():
    with pytest.raises(SystemExit):
        f()


class TestAGC:
    handle = None
    cam_address = c_void_p(0x12345678)
    num_pixels = 1310720
    last_set_AGC = None

    def test_self(self):
        assert True

    @pytest.fixture
    def camera_connection(self):
        cam.close_camera(self.cam_address)
        self.handle = None
        self.handle = cam.init()
        self.last_set_AGC = cam.DEF_AGC
        assert self.handle == self.cam_address.value
        yield
        cam.close_camera(self.handle)

    def test_get_AGC(self, camera_connection):
        # agc = 0
        # (result, agc) = cam.get_agc(self.handle, agc_value=agc)
        # result = cam.get_agc(self.handle, agc_value=agc)
        # assert result == 0
        # assert agc == 3
        assert False

    def test_set_AGC(self, camera_connection):
        agc = 0
        result = cam.set_agc(self.handle, agc_value=agc)
        assert result == 0

        # result == cam.get_agc(self.handle, agc)
        # assert result == 0
        # assert agc == 0


class TestShutterlessCalibration:
    handle = None
    cam_address = c_void_p(0x12345678)
    num_pixels = 1310720

    @pytest.fixture
    def camera_connection(self):
        cam.close_camera(self.cam_address)
        self.handle = None
        self.handle = cam.init()
        assert self.handle == self.cam_address.value
        yield
        cam.close_camera(self.handle)

    def test_self(self):
        assert True

    def test_t0(self, camera_connection):
        i_stage = 0
        result = cam.shutterless_cal_T0(self.handle, i_stage)
        assert result == 0

        result = cam.shutterless_cal_T0(self.handle, i_stage)
        assert result == 0

    def test_t1(self, camera_connection):
        result = cam.shutterless_cal_T1(self.handle)
        assert result == 0


class TestCal:
    cam_address = c_void_p(0x12345678)
    num_pixels = 1310720

    def test_self(self):
        assert True

    def test_shutter_cal_handle(self):
        handle = c_void_p(None)

        res = cam.shutter_cal(handle)
        assert res == 2

    def test_shutter_cal_valid(self):
        cam.close_camera(self.cam_address)
        handle = cam.init()
        assert handle == self.cam_address.value
        res = cam.shutter_cal(handle)
        assert res == 0

        cam.close_camera(handle)

    def test_two_point_shutter_cal_handle(self):
        handle = self.cam_address

        res = cam.two_point_shutter_cal(handle, 0)
        assert res == 2

        handle = cam.init()
        res = cam.two_point_shutter_cal(handle, 0)
        assert res == 1

    def test_two_point_shutter_cal(self):
        cam.close_camera(self.cam_address)
        handle = cam.init()

        res = cam.two_point_shutter_cal(handle, 1)
        assert res == 0

        res = cam.two_point_shutter_cal(handle, 2)
        assert res == 0

        cam.close_camera(handle)

    def test_fast_cal_save(self):
        cam.close_camera(self.cam_address)
        handle = cam.init()

        res = cam.fast_cal_save(handle)
        assert res == 0

        cam.close_camera(handle)


class TestCam:
    cam_address = c_void_p(0x12345678)
    num_pixels = 1310720

    def test_init(self):
        handle = cam.init()
        assert str(hex(handle)) == "0x12345678"
        assert handle == self.cam_address.value
        cam.close_camera(handle)

    def test_num_attached(self):
        n = cam.num_attached()
        assert n == 1

    def test_close_camera(self):
        h = c_void_p(None)
        n = cam.close_camera(h)
        assert n == 2

        h = self.cam_address
        n = cam.close_camera(h)
        assert n == 2

        h = cam.init()
        n = cam.close_camera(h)
        assert n == 0

    def test_load_frame_buffer(self):
        h = c_void_p(None)
        r = cam.load_frame_buffer(h)
        assert r == 2

        h = self.cam_address
        r = cam.load_frame_buffer(h)
        assert r == 2

        h = cam.init()
        r = cam.load_frame_buffer(h)
        assert r == 0
        cam.close_camera(h)

    def test_get_paimage(self):
        return
        # X = np.zeros(self.num_pixels, dtype=np.uint16)
        X = cam.get_paimage()

        # check that it's all zeros
        avg = 0
        for i in range(0, self.num_pixels):
            avg += X[i]
        avg = avg / self.num_pixels
        assert avg == 0.0

        # Load data then check.
        h = cam.init()
        cam.load_frame_buffer(h)
        cam.close_camera(h)
        X = cam.get_paimage()
        avg = 0
        for i in range(0, self.num_pixels):
            avg += X[i]
        avg = avg / self.num_pixels
        assert avg != 0.0

        cam.close_camera(h)

    def test_print_paimage(self):
        h = cam.init()
        cam.load_frame_buffer(h)
        cam.print_paimage()
        cam.close_camera(h)
        assert True

    def test_load_matrix_bufffer(self):
        h = cam.init()
        cam.load_frame_buffer(h)
        cam.load_matrix_buffer(False)

        cam.load_matrix_buffer(True)

        assert True
        cam.close_camera(h)

    def test_get_frame_matrix(self):
        cam.clear_matrix()
        M = cam.get_frame_matrix()
        assert M.shape == (1024, 1280)
        average = np.mean(M)
        assert average == 0.0

        cam.close_camera(self.cam_address)
        h = cam.init()
        cam.load_frame_buffer(h)
        cam.load_matrix_buffer(False)
        M = cam.get_frame_matrix()

        assert M.shape == (1024, 1280)

        average = np.mean(M)
        assert average > 3000.0

        cam.close_camera(h)
