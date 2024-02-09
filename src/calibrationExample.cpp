/***********************************************
**** Calibration example for 1280_12 SDK ****
************************************************/

#include <iostream>
#include <cstdint>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#if defined (__linux__)
#include <unistd.h>
#endif

#include "DALProxy1280_12USB.h"
#include "DALProxy1280_12USBDef.h"
#include "DALProxySwitchUSBDef.h"

using namespace DALPROXY_NAMESPACE;

#define GETIMAGE_TIMEOUT 4000

int main(int argc, char* argv[])
{
	(void)argc;
    int iCount;
    HANDLE m_Handle;
    m_Handle = NULL;
    char* name = new char[310];

    int nombreImg = 50;
    eDALProxy1280_12USBErr eReturnCode;

    std::cerr << "Getting module count : ";
    eReturnCode = Proxy1280_12USB_GetModuleCount(&iCount);
   
    std::cerr << Proxy1280_12USB_GetErrorString(eReturnCode) << std::endl;
    if (eReturnCode != eProxy1280_12USBSuccess)
    {
        return -1;
    }
   
    std::cerr << "Number of connected modules : " << iCount << std::endl;

    //Just take the first module for this example
    Proxy1280_12USB_GetModuleName(0, name, 300);
    std::cerr << "\"" << name << "\" : ";
    eReturnCode = Proxy1280_12USB_ConnectToModule(0, &m_Handle);
    
    if(eReturnCode != eProxy1280_12USBSuccess)
      return -1;

    Proxy1280_12USB_SetFloatFeature(m_Handle, efFrameRate, 30.0);

    //begin of calibration process
    std::cerr << "Start Calibration process step 1" << std::endl;
    eReturnCode = Proxy1280_12USB_InitShutter2PtsCalibration(m_Handle, 1);
    if(eReturnCode != eProxy1280_12USBSuccess)
        return -1;

    //wait the black body for low temperature
    std::cerr << "Low temperature step, press enter to start when you are ready" << std::endl;
    getchar();
	
    //do some steps to avoid temporal noise
    for(int iNb = 0; iNb < nombreImg; iNb++)
    {
        eReturnCode = Proxy1280_12USB_StepShutter2PtsCalibration(m_Handle, 1);
        if(eReturnCode != eProxy1280_12USBSuccess)
        {
            std::cerr << "Image Acquisition Error" << std::endl;
            return -1;
        }
    }

    std::cerr << "Finish Calibration process step 1" << std::endl;
    eReturnCode = Proxy1280_12USB_FinishShutter2PtsCalibration(m_Handle, 1);
    if(eReturnCode != eProxy1280_12USBSuccess)
        return -1;

    std::cerr << "Start Calibration process step 2" << std::endl;
    eReturnCode = Proxy1280_12USB_InitShutter2PtsCalibration(m_Handle, 2);
    if(eReturnCode != eProxy1280_12USBSuccess)
        return -1;

    //wait the black body for high temperature
    std::cerr << "High temperature step, press enter to start when you are ready" << std::endl;
    getchar();
	
    //do some steps to avoid temporal noise
    for(int iNb = 0; iNb < nombreImg; iNb++)
    {
        eReturnCode = Proxy1280_12USB_StepShutter2PtsCalibration(m_Handle, 2);
        if(eReturnCode != eProxy1280_12USBSuccess)
        {
            std::cerr << "Image Acquisition Error" << std::endl;
            return -1;
        }
    }

    std::cerr << "End of Calibration" << std::endl;
    eReturnCode = Proxy1280_12USB_FinishShutter2PtsCalibration(m_Handle, 2);
    if(eReturnCode != eProxy1280_12USBSuccess)
        return -1;
		
    //Calibration success, save tables and Bad pixels
    std::cerr << "Save Bad Pixels" << std::endl;
    eReturnCode = Proxy1280_12USB_SaveCurrentBadPixels(m_Handle);
    if(eReturnCode != eProxy1280_12USBSuccess)
        return -1;

    std::cerr << "Save Offsets" << std::endl;
    eReturnCode = Proxy1280_12USB_SaveCurrentTableOffset(m_Handle, 1, NULL);
    if(eReturnCode != eProxy1280_12USBSuccess)
        return -1;
   
    std::cerr << "Save Gains" << std::endl;
    eReturnCode = Proxy1280_12USB_SaveCurrentTableGain(m_Handle, 0, NULL);
    if(eReturnCode != eProxy1280_12USBSuccess)
        return -1;

    Proxy1280_12USB_DisconnectFromModule(m_Handle);

    return 0;
}
