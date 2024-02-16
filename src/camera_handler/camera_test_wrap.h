#ifndef DALProxy1280_12USBDEF_H
#define DALProxy1280_12USBDEF_H

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

// Largest image properties expected
#define DAL_PROXY1280_12_IRIMAGE_WIDTH 1280
#define DAL_PROXY1280_12_IRIMAGE_HEIGHT 1024
#define DAL_PROXY1280_12_IRIMAGE_PIXEL 2
#define DAL_PROXY1280_12_IRIMAGE_RESOLUTION 16
#define DAL_PROXY1280_12_IRIMAGE_PIXEL_MAX 0xFFFF

#define DAL_PROXY1280_12_IRIMAGE_NBPIXELS (DAL_PROXY1280_12_IRIMAGE_WIDTH * DAL_PROXY1280_12_IRIMAGE_HEIGHT)

#define DAL_PROXY1280_12_IRIMAGE_PAYLOAD (DAL_PROXY1280_12_IRIMAGE_NBPIXELS * DAL_PROXY1280_12_IRIMAGE_PIXEL )

#define DAL_PROXY1280_12_IRIMAGE_META_COUNT 135    // Default type : uint32

#define DAL_PROXY1280_12_IRIMAGE_META_TEMP 0
#define DAL_PROXY1280_12_IRIMAGE_META_PERIOD 1   // In micro seconds
#define DAL_PROXY1280_12_IRIMAGE_META_COUNTER 2   // 16bit effective counter
#define DAL_PROXY1280_12_IRIMAGE_EPOCH 3         // Warning : int64 --> 2 slots
#define DAL_PROXY1280_12_IRIMAGE_EPOCHLow 4      // Warning : int64 --> 2 slots
#define DAL_PROXY1280_12_IRIMAGE_FRAMEINFO 5
#define DAL_PROXY1280_12_IRIMAGE_FRAMEAGE 6
#define DAL_PROXY1280_12_IRIMAGE_FRAMEHISTO 7 // Warning : uint32*128 -> 128slots
#define DAL_PROXY1280_12_IRIMAGE_ENDFRAMEHISTO 134

/* Module Slot Type (see Proxy1280_12USB_SlotType() ) */
#define DAL_PROXY1280_12_SLOT_EMPTY 0
#define DAL_PROXY1280_12_SLOT_TYPE_GAIN 1
#define DAL_PROXY1280_12_SLOT_TYPE_OFFSET 2

/* NUC Slot Count */
#define DAL_PROXY1280_12_NUC_SLOT_COUNT 5
/* NUC Bank Count */
#define DAL_PROXY1280_12_NUC_BANK_COUNT 8



/* NUC Info free data size */
#define DAL_PROXY1280_12_NUC_INFO_USER_SIZE 60

/* Bank Settings count */
#define DAL_PROXY1280_12_BANK_SETTINGS_COUNT 8

// Maximum BAD Pixel allowed
#define DAL_PROXY1280_12_BADPIXELS_COUNT 6143 // ( 6K ( -1 to have space for the CRC ) )

// Mask pixel type
#define DAL_PROXY1280_12_PIXEL_IGNORED 0
#define DAL_PROXY1280_12_PIXEL_ORIGINAL 1
#define DAL_PROXY1280_12_PIXEL_FIXED 2

// Feature string regular size
#define DAL_PROXY1280_12_FEATURE_STRING_SIZE 32

/*Stuff from the switch header*/
#define IRIMAGE_WIDTH DAL_PROXY1280_12_IRIMAGE_WIDTH
#define IRIMAGE_HEIGHT DAL_PROXY1280_12_IRIMAGE_HEIGHT
#define IRIMAGE_PIXEL DAL_PROXY1280_12_IRIMAGE_PIXEL
#define IRIMAGE_RESOLUTION DAL_PROXY1280_12_IRIMAGE_RESOLUTION
#define IRIMAGE_PIXEL_MAX DAL_PROXY1280_12_IRIMAGE_PIXEL_MAX
#define IRIMAGE_NBPIXELS DAL_PROXY1280_12_IRIMAGE_NBPIXELS
#define IRIMAGE_PAYLOAD DAL_PROXY1280_12_IRIMAGE_PAYLOAD
#define IRIMAGE_META_COUNT DAL_PROXY1280_12_IRIMAGE_META_COUNT
#define IRIMAGE_META_TEMP DAL_PROXY1280_12_IRIMAGE_META_TEMP
#define IRIMAGE_META_PERIOD DAL_PROXY1280_12_IRIMAGE_META_PERIOD
#define IRIMAGE_META_COUNTER DAL_PROXY1280_12_IRIMAGE_META_COUNTER
#define IRIMAGE_EPOCH DAL_PROXY1280_12_IRIMAGE_EPOCH
#define IRIMAGE_EPOCHLow DAL_PROXY1280_12_IRIMAGE_EPOCHLow
#define IRIMAGE_FRAMEINFO DAL_PROXY1280_12_IRIMAGE_FRAMEINFO
#define IRIMAGE_FRAMEAGE DAL_PROXY1280_12_IRIMAGE_FRAMEAGE
#define IRIMAGE_FRAMEHISTO DAL_PROXY1280_12_IRIMAGE_FRAMEHISTO
#define IRIMAGE_ENDFRAMEHISTO DAL_PROXY1280_12_IRIMAGE_ENDFRAMEHISTO
#define SLOT_EMPTY DAL_PROXY1280_12_SLOT_EMPTY
#define SLOT_TYPE_GAIN DAL_PROXY1280_12_SLOT_TYPE_GAIN
#define SLOT_TYPE_OFFSET DAL_PROXY1280_12_SLOT_TYPE_OFFSET
#define NUC_SLOT_COUNT DAL_PROXY1280_12_NUC_SLOT_COUNT
#define NUC_BANK_COUNT DAL_PROXY1280_12_NUC_BANK_COUNT
#define NUC_INFO_USER_SIZE DAL_PROXY1280_12_NUC_INFO_USER_SIZE
#define BANK_SETTINGS_COUNT DAL_PROXY1280_12_BANK_SETTINGS_COUNT
#define BADPIXELS_COUNT DAL_PROXY1280_12_BADPIXELS_COUNT
#define PIXEL_IGNORED DAL_PROXY1280_12_PIXEL_IGNORED
#define PIXEL_ORIGINAL DAL_PROXY1280_12_PIXEL_ORIGINAL
#define PIXEL_FIXED DAL_PROXY1280_12_PIXEL_FIXED
#define FEATURE_STRING_SIZE DAL_PROXY1280_12_FEATURE_STRING_SIZE



typedef void *HANDLE;

enum eDeviceFeature
{
    // Ident & capabilities
    eStrPartNumber = 0,
    eStrSerialNumber,
    eStrIRSensorSerialNumber,
    eStrFirmwareBuildDataTime,
    eiFirmware0Version,
    eiFirmware1Version,
    eiFirmware2Version,
    eiShutterlessAvailable,
    eiIsExportLimited,
    eiHardwareDetection,
    eiSensorOutputNbr,
    eiUSBSpeed,
    // IR Sensor Settings
    eiGain,
    eiGainMin,
    eiGainMax,
    efGSK,
    efGSKMin,
    efGSKMax,
    efGFID,
    efGFIDMin,
    efGFIDMax,
    efVideoOffset,
    efVideoOffsetMin,
    efVideoOffsetMax,
    efFPATemp,
    efProxyBoardTemp,
    // Sequencer
    eiTriggerMode,
    efFrameRate,
    efFrameRateMin,
    efFrameRateMax,
    efExptime,
    efExptimeMin,
    efExptimeMax,
    efInterLine,
    efInterLineMin,
    efInterLineMax,
    // Video Stream
    eiVideoPattern,
    eiImageWidth,
    eiImageHeight,
    eiImagePixelFormat,
    eiUSBPayloadSize,
    eiFlipHorizontal,
    eiFlipVertical,
    eiVideoUSBOutActivation,
    eiVideoDF12OutputActivation,
    eiVideoDF12ChannelNbr,
    // Shutter management
    eiShutterMode,
    eiShutterActivation,
    efShutterFpaTempThreshold,
    eiShutterActivationDuration,

    // Power Management
    eiPowerMode,

    // Configuration
    eiSaveConfiguration,
    eiLoadConfiguration,
    eiLastConfiguration,

    // Table NUC
    eiLastSavedGainTable,
    eiLastSavedOffsetTable,

    // Table CRC
    eiTableCRC0,
    eiTableCRC1,
    eiTableCRC2,
    eiTableCRC3,
    eiTableCRC4,
    eiTableCRC5,
    eiTableCRC6,
    eiTableCRC7,
    // Last
    eDeviceFeatureTotal
};

enum ePowerModeValue
{
    ePowerNormal=0,
    ePowerStandby,
    ePowerDeepStandby
};

// AGC Processing
enum eAGCProcessingValue
{
    eNoAGC =0,
    eAGCEqHisto,
    eAGCLocal, //eAGCEnhanced,
    eAGCLinear,
    eAGCTotal
};

// Enhancement processing (bitfield)
enum eEnhancementProcessingValue
{
    eNoEnhancement =0,
    eColumnCorrection = 1,  // b0
    eLineCorrection = 2,    // b1
    eDenoising=4            // b2
    //
};

/** Code return by most functions about execution. */
typedef enum
{
    eProxy1280_12USBSuccess=0, /**< Function call success. */
    eProxy1280_12USBParameterError, /**< Function call with wrong parameter. */
    eProxy1280_12USBHandleError, /**< Function call with wrong or invalid Crius1280 handle. */
    eProxy1280_12USBInitFailed,  /**< Internal error occur. */
    eProxy1280_12USBOpenFailed,  /**< Open connection to Crius1280 failed. Maybe already connected */
    eProxy1280_12USBCommFailed,  /**< Exchange with Crius1280 failed. */
    eProxy1280_12USBTimeout, /**< Operation on Crius1280 timeout before completed. */
    eProxy1280_12USBSyncBroken, /**< GetImage(), Sync with Crius1280 broken. */
    //
    eProxy1280_12USBSequencingError, /**< Function call outside correct sequencing */
    eProxy1280_12USBFeatureNotAvailable, /**< Feature not available on this module or can't be use due to present configuration. */
    eProxy1280_12USBBistInitFailure, /**< Built-In Self Test initialisation failed. */
    eProxy1280_12USBBistFailure, /**< Crius1280 reported a Built-In Self Test error. */
    eProxy1280_12USBFormatFailed,  /**< Incompatible file format for Crius1280. */
    eProxy1280_12USBFormatMismatch, /**< Incompatible calibration format for Crius1280. */
    //
    eProxy1280_12USBErrTotal
} eDALProxy1280_12USBErr;


/*
 * ############################
 * TDD stuff 
 * ############################
 */ 

int load_fake_data(char *file_name);
void get_fake_data_address(void *ptr);


const char* __wrap_Proxy1280_12USB_GetErrorString(eDALProxy1280_12USBErr paeError);

eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_IsConnectToModule(HANDLE paHandle);
eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_GetModuleCount(int* paiCount);
eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_GetModuleName(int iIdx, char* paName, int iLen);
eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_ConnectToModule(int iIdx, HANDLE* paHandle);
eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_DisconnectFromModule(HANDLE paHandle);
eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_GetImage(HANDLE paHandle, unsigned short* paImage, int* paMeta, int paiTimeout);



eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_SetNUCProcessing(HANDLE paHandle, unsigned char paBadPixels, unsigned char paNUC);
eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_SetShutterLessProcessing(HANDLE paHandle, bool bActivate);
eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_SetAGCProcessing(HANDLE paHandle, unsigned char paeAGCProcessing);
eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_SetFloatFeature(HANDLE paHandle, int paeFeature, float paFloat);


/*Adding in the calibration function prototypes*/


eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_AbortCalibration(HANDLE paHandle);

/*Shutter 2Pts calibration*/
eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_InitShutter2PtsCalibration(HANDLE paHandle, unsigned int iStage);
eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_StepShutter2PtsCalibration(HANDLE paHandle, unsigned int iStage);
eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_FinishShutter2PtsCalibration(HANDLE paHandle,unsigned int iStage);


/*Shutter calibration*/
eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_InitShutterCalibration(HANDLE paHandle);
eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_StepShutterCalibration(HANDLE paHandle);
eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_FinishShutterCalibration(HANDLE paHandle);

/*SL calibration*/
eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_InitSLCalibrationT0(HANDLE paHandle, unsigned int iStage);
eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_StepSLCalibrationT0(HANDLE paHandle, unsigned int iStage);
eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_FinishSLCalibrationT0(HANDLE paHandle, unsigned int iStage);

/*SL T1 Calibration*/
eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_InitSLCalibrationT1(HANDLE paHandle);
eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_StepSLCalibrationT1(HANDLE paHandle);
eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_FinishSLCalibrationT1(HANDLE paHandle);


#endif
