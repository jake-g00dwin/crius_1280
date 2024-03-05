#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "camera_test_wrap.h"

/*All the code here is copied from the unit tests*/
/*It's just here for being able to link it in as a fake shared lib.*/
/*This allows testing of the python code that requires a shared lib.*/


/*
 * ###################################
 * MOCKS
 * ##################################
 */

/*Mocked globals*/
void *ptr = (void*)0x12345678;  // Example address
int camera_index = 0;
static const char name[] = "IrLugX1M3  sn:FR382312-01-001";
uint16_t fake_image[IRIMAGE_NBPIXELS*2];
bool is_connected = false;
bool pa_nuc_enabled = true;
bool pa_bad_pixels_enabled = true;
unsigned char last_agc_value = 0;
bool sl_t0_calibration_in_progress = false;
bool sl_t1_calibration_in_progress = false;



/*
 * ############################
 * Helpers for testing
 * ############################
 */ 

bool is_valid_handle(HANDLE h)
{
    if(h != ptr || !is_connected){
        return eProxy1280_12USBHandleError;
    }
    return eProxy1280_12USBHandleError;
}

/*
 * ############################
 * Mocked functions
 * ############################
 */ 

/*Read the image file for testing form the file.*/
int load_fake_data(char *file_name)
{
    int fd = open(file_name, O_RDONLY);
    if(fd < 0){
        return fd;
    }
    read(fd, fake_image, IRIMAGE_NBPIXELS*2);
    close(fd);
    return 0;
}


void get_fake_data_address(void *ptr)
{
    ptr = (void *)fake_image;
}

const char* __wrap_Proxy1280_12USB_GetErrorString(eDALProxy1280_12USBErr paeError)
{
    switch(paeError){
        case eProxy1280_12USBSuccess:
            return "Function call Success.";
        case eProxy1280_12USBParameterError:
            return "Parameter Error";
        case eProxy1280_12USBHandleError:
            return "Function call with invalid handle";
        case eProxy1280_12USBInitFailed:
            return "Init failed.";
        case eProxy1280_12USBOpenFailed:
            return "Open connection to camera failed";
        case eProxy1280_12USBCommFailed:
            return "exchange with cam failed.";
        case eProxy1280_12USBTimeout:
            return "operation timedout before completion.";
        case eProxy1280_12USBSyncBroken:
            return "USB sync broken";
        case eProxy1280_12USBSequencingError:
            return "function call outside of correct sequencing.";
        default:
            return "NOT A VALID ERROR!";
    }
}


eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_GetImage(HANDLE paHandle, unsigned short* paImage, int* paMeta, int paiTimeout)
{
    if(paHandle != ptr || !is_connected){
        return eProxy1280_12USBHandleError;
    }
    int r = load_fake_data("/tmp/testdata.bin");
    memcpy(paImage, fake_image, sizeof(fake_image));
    return r;
}


/*
 * ############################
 * Other conncetion features 
 * ############################
 */ 

eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_GetModuleCount(int* paiCount)
{
    *paiCount = 1;
    return eProxy1280_12USBSuccess;
}

eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_GetModuleName(int iIdx, char* paName, int iLen)
{
    if(iIdx == camera_index) {
        memcpy(paName, name, iLen);
        return eProxy1280_12USBSuccess;
    }   
    return eProxy1280_12USBHandleError;
}


eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_ConnectToModule(int iIdx, HANDLE* paHandle)
{
    if(iIdx == camera_index && !is_connected) {
        *paHandle = ptr;
        is_connected = true;
        return eProxy1280_12USBSuccess;
    }
    return eProxy1280_12USBParameterError;
}


eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_DisconnectFromModule(HANDLE paHandle)
{
    if(paHandle == ptr && is_connected){
        is_connected = false;
        return eProxy1280_12USBSuccess;
    }
    return eProxy1280_12USBHandleError;
}


eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_IsConnectToModule(HANDLE paHandle)
{
    //function_called();
    if(paHandle == ptr && is_connected){
        //printf("handle: %p\n", paHandle);
        //printf("saved_handle: %p\n", ptr);
        //printf("is_connected: %d\n", is_connected);
        return eProxy1280_12USBSuccess;
    }
    return eProxy1280_12USBHandleError;
}


/*
 * ############################
 * SETTING FEATURES 
 * ############################
 */ 


eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_GetNUCProcessing(HANDLE paHandle, unsigned char *paBadPixels, unsigned char *paNUC)
{
    //function_called();

    if(!is_valid_handle(paHandle)){
        return eProxy1280_12USBHandleError;
    }
    
    /*Check if the passed parameters are valid*/ 
    if(*paBadPixels > 1 || *paBadPixels < 0) {
        return eProxy1280_12USBParameterError;
    }
    if(*paNUC > 1 || *paNUC < 0) {
        return eProxy1280_12USBParameterError;
    }

    //get NUC proccessing "global val"
    *paNUC = pa_nuc_enabled;
    *paBadPixels = pa_bad_pixels_enabled;        

    return eProxy1280_12USBSuccess;
}


eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_SetNUCProcessing(HANDLE paHandle, unsigned char paBadPixels, unsigned char paNUC)
{
    if(!is_valid_handle(paHandle)){
        return eProxy1280_12USBHandleError;
    }
    return eProxy1280_12USBSuccess;
}

eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_SetShutterLessProcessing(HANDLE paHandle, bool bActivate)
{
    if(!is_valid_handle(paHandle)){
        return eProxy1280_12USBHandleError;
    }
    return eProxy1280_12USBSuccess;
}

eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_SetAGCProcessing(HANDLE paHandle, unsigned char paeAGCProcessing)
{
    if(!is_valid_handle(paHandle)){
        return eProxy1280_12USBHandleError;
    }

    last_agc_value = paeAGCProcessing;

    return eProxy1280_12USBSuccess;
}


eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_GetAGCProcessing(HANDLE paHandle, unsigned char *paeAGCProcessing)
{
 
    if(!is_valid_handle(paHandle)){
        return eProxy1280_12USBHandleError;
    }
    
    *paeAGCProcessing = last_agc_value;

    return eProxy1280_12USBSuccess;

}

eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_SetFloatFeature(HANDLE paHandle, int paeFeature, float paFloat)
{
    if(!is_valid_handle(paHandle)){
        return eProxy1280_12USBHandleError;
    }
    return eProxy1280_12USBSuccess;
}





/*
 * ############################
 * CALIBRATION FUNCTIONS 
 * ############################
 */ 


eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_AbortCalibration(HANDLE paHandle)
{
    //function_called();
	return is_valid_handle(paHandle);
}



/*Shutter 2Pts calibration*/
eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_InitShutter2PtsCalibration(HANDLE paHandle, unsigned int iStage)
{
    //function_called();
    if(iStage != 1 && iStage != 2) {return eProxy1280_12USBParameterError;}
    if( !is_valid_handle(paHandle)) { return eProxy1280_12USBHandleError;}
    
    return eProxy1280_12USBSuccess;
}


eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_StepShutter2PtsCalibration(HANDLE paHandle, unsigned int iStage)
{
    //function_called();
    if(iStage != 1 && iStage != 2) {return eProxy1280_12USBParameterError;}
    if( !is_valid_handle(paHandle)) { return eProxy1280_12USBHandleError;}
    
    return eProxy1280_12USBSuccess;
}


eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_FinishShutter2PtsCalibration(HANDLE paHandle,unsigned int iStage)
{
    //function_called();
    if(iStage != 1 && iStage != 2) {return eProxy1280_12USBParameterError;}
    if( !is_valid_handle(paHandle)) { return eProxy1280_12USBHandleError;}
    
    return eProxy1280_12USBSuccess;
}




/*Shutter calibration*/
eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_InitShutterCalibration(HANDLE paHandle)
{
    //function_called();
    //check_expected_ptr(paHandle);
    if( !is_valid_handle(paHandle)) { return eProxy1280_12USBHandleError;}
    return eProxy1280_12USBSuccess;
}


eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_StepShutterCalibration(HANDLE paHandle)
{
    //function_called();
    if( !is_valid_handle(paHandle)) { return eProxy1280_12USBHandleError;}
    return eProxy1280_12USBSuccess;
}


eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_FinishShutterCalibration(HANDLE paHandle)
{

    //function_called();
    if( !is_valid_handle(paHandle)) { return eProxy1280_12USBHandleError;}
    return eProxy1280_12USBSuccess;
}



/*SL calibration*/
eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_InitSLCalibrationT0(HANDLE paHandle, unsigned int iStage)
{
    //function_called();
    if( !is_valid_handle(paHandle)) { return eProxy1280_12USBHandleError;}
    if(iStage != 1 && iStage != 2) {return eProxy1280_12USBParameterError;}

    if(sl_t0_calibration_in_progress) {
        return eProxy1280_12USBSequencingError;
    }

    sl_t0_calibration_in_progress = true;

    return eProxy1280_12USBSuccess;
}


eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_StepSLCalibrationT0(HANDLE paHandle, unsigned int iStage)
{
    //function_called();
    if( !is_valid_handle(paHandle)) { return eProxy1280_12USBHandleError;}
    if(iStage != 1 && iStage != 2) {return eProxy1280_12USBParameterError;}

    if(!sl_t0_calibration_in_progress) {
        return eProxy1280_12USBSequencingError;
    }

    return eProxy1280_12USBSuccess;
}


eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_FinishSLCalibrationT0(HANDLE paHandle, unsigned int iStage)
{

    //function_called();
    if( !is_valid_handle(paHandle)) { return eProxy1280_12USBHandleError;}
    if(iStage != 1 && iStage != 2) {return eProxy1280_12USBParameterError;}

    if(!sl_t0_calibration_in_progress) {
        return eProxy1280_12USBSequencingError;
    }
    
    sl_t0_calibration_in_progress = false;
    return eProxy1280_12USBSuccess;
}



/*SL T1 Calibration*/
eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_InitSLCalibrationT1(HANDLE paHandle)
{
    //function_called();
    if( !is_valid_handle(paHandle)) { return eProxy1280_12USBHandleError;}

    if(sl_t1_calibration_in_progress) {
        return eProxy1280_12USBSequencingError;
    }

    sl_t1_calibration_in_progress = true;
    return eProxy1280_12USBSuccess;
}


eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_StepSLCalibrationT1(HANDLE paHandle)
{
    //function_called();
    if( !is_valid_handle(paHandle)) { return eProxy1280_12USBHandleError;}

    if(!sl_t1_calibration_in_progress) {
        return eProxy1280_12USBSequencingError;
    } 

    return eProxy1280_12USBSuccess;
}


eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_FinishSLCalibrationT1(HANDLE paHandle)
{
    //function_called();
    if( !is_valid_handle(paHandle)) { return eProxy1280_12USBHandleError;}
    
    if(!sl_t1_calibration_in_progress) {
        return eProxy1280_12USBSequencingError;
    } 
    
    sl_t1_calibration_in_progress = false;
    return eProxy1280_12USBSuccess;
}

/*The functions needed to do the simple calibration/save*/

eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_SaveCurrentTableGain(
        HANDLE paHandle,
        unsigned char paiIndex,
        const void *paData)
{
    //function_called();
    if( !is_valid_handle(paHandle)) { return eProxy1280_12USBHandleError;}
    return eProxy1280_12USBSuccess;
}


eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_SaveCurrentBadPixels(HANDLE paHandle)
{
    //function_called();
    if( !is_valid_handle(paHandle)) { return eProxy1280_12USBHandleError;}
    return eProxy1280_12USBSuccess;
}


eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_SaveCurrentTableOffset(HANDLE paHandle,
        unsigned char paiIndex,
        const void *paData)
{
    //function_called();
    if( !is_valid_handle(paHandle)) { return eProxy1280_12USBHandleError;}
    return eProxy1280_12USBSuccess;
}

eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_SaveCurrentShutterlessTables(HANDLE paHandle)
{
    //function_called();
    if( !is_valid_handle(paHandle)) { return eProxy1280_12USBHandleError;}

    return eProxy1280_12USBSuccess;
}


eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_LoadCurrentShutterlessTables(HANDLE paHandle)
{
    //function_called();
    if( !is_valid_handle(paHandle)) { return eProxy1280_12USBHandleError;}
    
    return eProxy1280_12USBSuccess;
}


/*
 * ###################################
 * END OF MOCKS
 * ##################################
 */



