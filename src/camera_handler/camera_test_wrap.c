#include "camera_test_wrap.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void *ptr = (void*)0x12345678;  // Example address
int camera_index = 0;
static const char name[] = "IrLugX1M3  sn:FR382312-01-001";
uint16_t fake_image[IRIMAGE_NBPIXELS*2];
bool is_connected = false;


/*Read the image file for testing form the file.*/
void load_fake_data(char *file_name)
{
    int fd = open(file_name, O_RDONLY);
    read(fd, fake_image, IRIMAGE_NBPIXELS*2);
    close(fd);
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
    load_fake_data("src/camera_handler/testdata.bin");
    memcpy(paImage, fake_image, sizeof(fake_image));
    return eProxy1280_12USBSuccess;
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
    if(paHandle == ptr && is_connected){
        printf("handle: %p\n", paHandle);
        return eProxy1280_12USBSuccess;
    }
    return eProxy1280_12USBHandleError;
}


/*
 * ############################
 * SETTING FEATURES 
 * ############################
 */ 

eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_SetNUCProcessing(HANDLE paHandle, unsigned char paBadPixels, unsigned char paNUC)
{
    return eProxy1280_12USBSuccess;
}

eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_SetShutterLessProcessing(HANDLE paHandle, bool bActivate)
{
    return eProxy1280_12USBSuccess;
}

eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_SetAGCProcessing(HANDLE paHandle, unsigned char paeAGCProcessing)
{
    return eProxy1280_12USBSuccess;
}

eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_SetFloatFeature(HANDLE paHandle, int paeFeature, float paFloat)
{
    return eProxy1280_12USBSuccess;
}


