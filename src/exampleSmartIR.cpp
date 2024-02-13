/*
***********************************************
**** Grab example for 1280_12 SDK ****
************************************************
*/

#include <iostream>
#include <cstdint>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <signal.h>
#if defined (__linux__)
#include <pthread.h>
#include <unistd.h>
#endif

#include "DALProxy1280_12USB.h"
#include "DALProxy1280_12USBDef.h"
#include "DALProxySwitchUSBDef.h"

using namespace DALPROXY_NAMESPACE;

//#include <Poco/types.h>
#if defined (__linux__)
#else
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>
#endif

#define GETIMAGE_TIMEOUT 5000
bool stop;
//Buffer for Image
// todo use Poco::uint16_t instead
uint16_t paImage[IRIMAGE_NBPIXELS*2];
//Buffer for MetaData
int32_t paMeta[135];
#if defined (__linux__)
pthread_t threadImg;
#else
DWORD  threadImg = NULL;
#endif
HANDLE m_Handle = NULL;
HANDLE m_HandleThread = NULL;

static void sighandler(int signum)
{
	(void)signum;
    if (threadImg)
    {
        stop = true;
#if defined (__linux__)
        if (pthread_join(threadImg, NULL))
        {
            std::cerr << "Error in pthread_join \n";
        }
#else
		std::cerr << "Wait for end of thread\n";
        if (WaitForSingleObject(m_HandleThread, INFINITE))
        {
            std::cerr <<  "Error in WaitForSingleObject \n";
        }
        if (m_HandleThread)
        {
            CloseHandle(m_HandleThread);
        }
#endif
    }
    if (m_Handle)
    {
        Proxy1280_12USB_DisconnectFromModule(m_Handle);
    }
    exit(EXIT_SUCCESS);
}

void show_help()
{
    std::cout << "Default call : grab 10 images with 30fps, no NUC or Shutterless processing, bad pixel correction activate and no agc. " << std::endl;
    std::cout << "Options : " << std::endl;
    std::cout << "-framerate X where X is the float value for the desired framerate" << std::endl;
    std::cout << "-n X where X is the number of images grab. If X = 0, then it's a interruptible grab. With creation of imgRAW.bin with last grabed image" << std::endl;
    std::cout << "-NUC [1/0] if -NUC 1 then nuc processing is activated else not." << std::endl;
    std::cout << "-AGC [noAGC/histo/local/linear] give the possibility to choose the agc processing." << std::endl;
    std::cout << "-SL [1/0] activation or desactivation of Shutterless processing." << std::endl;
    std::cout << "-BP [1/0] activation or desactivation of BadPixels corrections." << std::endl;
}

#if defined (__linux__)
void *thread_1(void *pHandle)
#else
DWORD WINAPI thread_1(void *pHandle)
#endif
{
    uint64_t imAvg = 0;
    eDALProxy1280_12USBErr eReturnCode;
    uint64_t iNb = 0;
    HANDLE handle = (HANDLE) pHandle;
    int exiting = 0;

    eReturnCode = Proxy1280_12USB_GetImage(handle, paImage, paMeta, GETIMAGE_TIMEOUT);
    while(!stop)
    {
        //get image
        eReturnCode = Proxy1280_12USB_GetImage(handle, paImage, paMeta, GETIMAGE_TIMEOUT);
        std::cerr << "Im" << iNb << " : " << Proxy1280_12USB_GetErrorString(eReturnCode) << std::endl;
        if (eReturnCode == eProxy1280_12USBCommFailed)
        {
            std::cerr << "Communication lost with the USB device. Exiting..." << std::endl;
            exiting = 1;
            break;
        }

        //make avg of pixel values
        for(int i=0; i<(IRIMAGE_NBPIXELS); i++)
        {
            imAvg += ((uint16_t*)paImage)[i];
        }

        unsigned short *paMeta_ushort;
        paMeta_ushort = (unsigned short*)(paMeta+IRIMAGE_META_COUNTER);
        std::cout << "Image " << iNb << " Frame Counter : " << *paMeta_ushort << " Average Val : " << (imAvg/(IRIMAGE_NBPIXELS)) << std::endl;
        imAvg = 0;
        iNb++;
    }

    if (eReturnCode == eProxy1280_12USBSuccess)
    {
        std::ofstream file("imgRAW.bin", std::ios::out | std::ios::trunc | std::ios::binary);
        file.write ((char*) paImage,IRIMAGE_NBPIXELS*2);
        file.close();
    }
    Proxy1280_12USB_DisconnectFromModule(handle);
    handle = NULL;

    if (exiting) exit(EXIT_FAILURE);
#if defined (__linux__)
    pthread_exit(NULL);
#else
    return 0;
#endif
}

int main(int argc, char* argv[])
{
    int iCount;
    m_Handle = NULL;
    char* name = new char[310];

    uint64_t imAvg = 0;
    float FrameRate = 30.0;
    int nombreImg = 10;
    char nuc = 0;
    bool bSL = false;
    char bBP = 1;
    eAGCProcessingValue agcVal = eNoAGC;
    eDALProxy1280_12USBErr eReturnCode;

    stop = false;

    signal(SIGINT, sighandler);

    //parse parameters
    if(argc >= 2)
    {
        if(strcmp("-help", argv[1]) ==0)
        {
            show_help();
            return 0;
        }
        for(int i=1; i < argc; i++)
        {
			if(strcmp("-framerate", argv[i]) ==0)
            {
                i++;
                if(i < argc)
                {
                    FrameRate = (float)atof(argv[i]);
                    if(FrameRate < 5)
                        FrameRate = 5;
                    else if (FrameRate > 120)
                        FrameRate = 120;
                }
                else
                {
                    std::cerr << "Parameters error" << std::endl;
                    return 0;
                }
            }
            else if(strcmp("-n", argv[i]) ==0)
            {
                i++;
                if(i < argc)
                {
                    nombreImg = atoi(argv[i]);
                    if(nombreImg < 0)
                        nombreImg = 10;
                }
                else
                {
                    std::cerr << "Parameters error" << std::endl;
                    return 0;
                }
            }
            else if(strcmp("-NUC", argv[i]) == 0)
            {
                i++;
                if(i < argc)
                {
                    if(strcmp("1", argv[i])==0)
                        nuc = 1;
                    else if(strcmp("0", argv[i])==0)
                        nuc = 0;
                    else
                    {
                        std::cerr << "Parameters error : -n option must be followed by 0 or 1 \n";
                        return 0;
                    }
                }
                else
                {
                    std::cerr << "Parameters error \n";
                    return 0;
                }
            }
            else if(strcmp("-AGC", argv[i])==0)
            {
                i++;
                if(i < argc)
                {
                    if(strcmp("noAGC", argv[i])==0)
                        agcVal = eNoAGC;
                    else if(strcmp("histo", argv[i])==0)
                        agcVal = eAGCEqHisto;
                    else if(strcmp("local", argv[i])==0)
                        agcVal = eAGCLocal;
                    else if(strcmp("linear", argv[i])==0)
                        agcVal = eAGCLinear;
                    else
                    {
                        std::cerr << "Parameter error : Not a valid agc \n";
                        return 0;
                    }
                }
                else
                {
                    std::cerr << "Parameters error \n";
                    return 0;
                }
            }
            else if(strcmp("-SL", argv[i])==0)
            {
                i++;
                if(i < argc)
                {
                    if(strcmp("1", argv[i])==0)
                        bSL = true;
                    else if(strcmp("0", argv[i])==0)
                        bSL = false;
                    else
                    {
                        std::cerr << "Parameters error \n";
                        return 0;
                    }
                }
                else
                {
                    std::cerr << "Parameters error \n";
                    return 0;
                }
            }
            else if(strcmp("-BP", argv[i])==0)
            {
                i++;
                if(i < argc)
                {
                    if(strcmp("1", argv[i])==0)
                        bBP = 1;
                    else if(strcmp("0", argv[i])==0)
                        bBP = 0;
                    else
                    {
                        std::cerr << "Parameters error \n";
                        return 0;
                    }
                }
                else
                {
                    std::cerr << "Parameters error \n";
                return 0;
                }
            }
        }
    }
    std::cout << "Getting module count : ";
    eReturnCode = Proxy1280_12USB_GetModuleCount(&iCount);

    std::cerr << Proxy1280_12USB_GetErrorString(eReturnCode) << std::endl;
    if (eReturnCode != eProxy1280_12USBSuccess)
    {
        return 0;
    }

    std::cout << "Number of connected modules : " << iCount << std::endl;

    //Just take the first module for this example
    Proxy1280_12USB_GetModuleName(0, name, 300);
    std::cout << "\"" << name << "\" : ";
    eReturnCode = Proxy1280_12USB_ConnectToModule(0, &m_Handle);

    if(eReturnCode != eProxy1280_12USBSuccess)
    {
        std::cout << "Exiting..." << std::endl;
        return 0;
    }

    //Set Processing depending of parameters (NUC/AGC/Shutterless/Framerate)
    Proxy1280_12USB_SetNUCProcessing(m_Handle, bBP, nuc);
    Proxy1280_12USB_SetShutterLessProcessing(m_Handle, bSL);
    Proxy1280_12USB_SetFloatFeature(m_Handle, efFrameRate, FrameRate);
    Proxy1280_12USB_SetAGCProcessing(m_Handle, agcVal);

    //Keyboard interruption capture
    if(nombreImg ==0)
    {
#if defined (__linux__)
        if(pthread_create(&threadImg, NULL, thread_1, m_Handle) == -1)
        {
            std::cerr << "Error in pthread_create \n";
#else
        if((m_HandleThread = CreateThread(NULL, 0, thread_1, m_Handle, 0, &threadImg)) == NULL)
        {
            std::cerr << "Error in CreateThread \n";
#endif
            return -1;
        }

        std::cerr << "Press Ctrl+C to end the program \n";
#if defined (__linux__)
        while(1) sleep(1); // Wait for Ctrl+C
#else
        while(1) Sleep(1); // Wait for Ctrl+C
#endif
    }

    //for n images
    for(int iNb=0; iNb < nombreImg ; iNb++)
    {
        //get image
        eReturnCode = Proxy1280_12USB_GetImage(m_Handle, paImage, paMeta, GETIMAGE_TIMEOUT);
        if (eReturnCode == eProxy1280_12USBCommFailed)
        {
            std::cerr << "Communication lost with the USB device. Exiting..." << std::endl;
            break;
        }
        std::cout << "Im" << iNb << " : " << Proxy1280_12USB_GetErrorString(eReturnCode) << std::endl;

        //make avg of pixel values
        for(int i=0; i<(IRIMAGE_NBPIXELS); i++)
        {
            imAvg += ((uint16_t*)paImage)[i];
        }

        std::cout << "Image " << iNb << "  Average Val : " << (imAvg/(IRIMAGE_NBPIXELS)) << std::endl;
        //Use some metadata
        float* paMeta_float;
        paMeta_float = (float*)(paMeta+IRIMAGE_META_TEMP);
        std::cout << "Im" << iNb << " Temp : " << *paMeta_float << "°C // Period : " << paMeta[1] << "µs // Frame Counter : ";
        uint64_t *paMeta_uint64_t;
        paMeta_uint64_t = (uint64_t*)(paMeta+IRIMAGE_EPOCH);
        unsigned short *paMeta_ushort;
        paMeta_ushort = (unsigned short*)(paMeta+IRIMAGE_META_COUNTER);
        std::cout << *paMeta_ushort << " // Epoch : " << *paMeta_uint64_t << std::endl;
        imAvg = 0;

        char file_name[128] = {'\0'};
        sprintf(file_name, "/tmp/imgRaw%d.bin", iNb);
        std::cout << "saved file: " << file_name << std::endl;

        std::ofstream file(file_name, std::ios::out | std::ios::trunc | std::ios::binary);
        file.write ((char*) paImage,IRIMAGE_NBPIXELS*2);
        file.close();
    }

    Proxy1280_12USB_DisconnectFromModule(m_Handle);

    return 0;
}

