#include "camera_test_wrap.h"



const char* __wrap_Proxy1280_12USB_GetErrorString(eDALProxy1280_12USBErr paeError)
{
    return "NOT IMPLIMENTED";
}


eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_GetModuleCount(int* paiCount)
{
    return eProxy1280_12USBSuccess;
}

eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_GetModuleName(int iIdx, char* paName, int iLen)
{
    return eProxy1280_12USBSuccess;
}

eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_DisconnectFromModule(HANDLE paHandle)
{ 
    return eProxy1280_12USBSuccess;
}

eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_GetImage(HANDLE paHandle, unsigned short* paImage, int* paMeta, int paiTimeout)
{
    return eProxy1280_12USBSuccess;
}

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
