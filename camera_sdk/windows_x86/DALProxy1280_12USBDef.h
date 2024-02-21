#ifndef DALProxy1280_12USBDEF_H
#define DALProxy1280_12USBDEF_H

#ifdef __cplusplus
namespace DALProxy1280_12USB_namespace
{
#endif

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

#ifdef __cplusplus
}
#endif


#endif // DALProxy1280_12USBDEF_H
