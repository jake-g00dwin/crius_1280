#ifndef __DALProxy1280_12USB_H__
#define __DALProxy1280_12USB_H__

#ifdef __cplusplus
extern "C" { /* using a C++ compiler */
#endif

#include <stdio.h>

#if (defined (LINUX) || defined (__linux__))
    typedef void *HANDLE;
#else
    #include <winsock2.h> // We don't want Windows.h to include winsock.h
	//#include <Windows.h>  /*I commented this out for use with mingw32*/
	#include <windows.h>
#endif

#ifdef __cplusplus
namespace DALProxy1280_12USB_namespace
{
#endif

#ifndef DOXYGEN
#if (defined (LINUX) || defined (__linux__))
    #ifdef DALProxy1280_12USB_LIBRARY
    #define DALProxy1280_12USB_API __attribute__((visibility("default")))
    #else
    #define DALProxy1280_12USB_API
    #endif
#else
    #ifdef DALProxy1280_12USB_LIBRARY
    #define DALProxy1280_12USB_API __declspec(dllexport)
    #else
    #define DALProxy1280_12USB_API __declspec(dllimport)
    #endif
#endif
#endif


/** \defgroup Module_Management Crius1280 Management
  * \brief Etablish and manage communication with Crius1280.
  */

/** \defgroup Module_Processing Crius1280 Processing
  * \brief Control Crius1280 image processing.
  * Query module connected to workstation, Open and close link.
  */

/** \defgroup Module_Control Crius1280 Control
  * \brief Set or Get module features. Refer to module user guide for details on feature, and SDK header file for paeFeature definition.
  */

/** \defgroup Module_Image Crius1280 Image
  * \brief Query Image from Crius1280.
  */

/** \defgroup Module_Storage Crius1280 Storage
  * \brief Store and retrieve processing settings into Crius1280.
  */

/** \defgroup Module_Calibration Crius1280 Calibration
  * \brief Crius1280 NUC, bad pixel and Shutterless correction calibration. Refer to calibration example provided with the SDK for detailed usage of the following function.
  *
  * NUC can be a two points calibration, or a one point calibration.
  * Shutterless can be a T0 calibration only or T0 and T1 calibration.
  */

/** \defgroup Module_ErrFunc Function return code
 * \brief Function execution returned code.
  */

/** \addtogroup Module_ErrFunc
  * \ref eDALProxy1280_12USBErr is return by most functions as a result of execution.
  * \see eDALProxy1280_12USBErr() to convert code to user friendly string.
  *  @{ */

/** Code return by most functions about execution. */
DALProxy1280_12USB_API typedef enum
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


/** Convert \ref eDALProxy1280_12USBErr to user message.
 * \param[in] paeError Function returns error code.
 * \return User error message from eDALProxy1280_12USBErr.
 * \note String is C-Style, i.e. Ascii with null terminate byte.
*/
DALProxy1280_12USB_API const char* Proxy1280_12USB_GetErrorString(eDALProxy1280_12USBErr paeError);

/** @} */


/** \addtogroup Module_Management
 *
 * This set provides :
 * \li Functions to enumerates and name plugged Crius1280.
 * \li Function to connect and disconnect to Crius1280.
 *
 * Application call Proxy1280_12USB_GetModuleCount() to know how many Crius1280 are plugged to workstation.
 * First Crius1280 index is 0, and so on.
 *
 * Calling Proxy1280_12USB_GetModuleCount() check Crius1280 count. So, call it will refresh Crius1280 list.
 *
 * Before calling any other function's group, Application must connect to a Crius1280 using Proxy1280_12USB_ConnectToModule().<br>
 * Once a Crius1280 is connected by an application, it's not available to another application.
 * Application must release Crius1280 by calling Proxy1280_12USB_DisconnectFromModule().
 *
 * Connection to Crius1280 will provide a \em handle. This \em handle is use by all functions addressing this Crius1280.
 * It remains valid until Proxy1280_12USB_DisconnectFromModule() is called.
 *
 * Application can connect several Crius1280, using different \em handles.
* @{ */

/** Retrieve current count of plugged module.
 * \param[out] paiCount Number of plugged module.
*/
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_GetModuleCount(int* paiCount);

/** Query Crius1280 name by index.
 * \param[in] iIdx Module index.
 * \param[out] paName Crius1280 name from index.
 * \param[in] iLen paName storage size.
*/
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_GetModuleName(int iIdx, char* paName, int iLen);

/** Connect to Crius1280 by index.<br>
 * This function will return a handle, which will be uses as Crius1280 identifier.<br>
 * Connection may failed if Crius1280 is already connected by another application.
 * \param[in] iIdx Module index. First Crius1280 index is 0.
 * \param[out] paHandle Crius1280 handle.
 **/
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_ConnectToModule(int iIdx, HANDLE* paHandle);

/** Check if handle connection.
 * This function will check if handle is still valid, and then check connection with Crius1280.
 * \param[in] paHandle Crius1280 handle.
 *\return \ref eProxy1280_12USBSuccess on success, or error code.
 **/
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_IsConnectToModule(HANDLE paHandle);

/** Disconnect to Crius1280 by index.
 * This function will release Crius1280 connection.
 * \param[in] paHandle Crius1280 handle.
 **/
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_DisconnectFromModule(HANDLE paHandle);

/** Run the Crius1280 Built-In Self-Test.
 * This function will check if handle is still valid, and then run the built-in self tests.
 * \param[in] paHandle Crius1280 handle.
 * \param[out] diagCode Diagnostic code provided by the Crius1280. Value is 0 in case of success.
 * \return \ref eProxy1280_12USBSuccess on success, or error code.
 **/
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_RunBIST(HANDLE paHandle, unsigned int *diagCode);

//! @}


/** \addtogroup Module_Image
 *
 * This set provides a single function to query current Crius1280 image.
 * Calling it will block application until an image is available, or timeout occurs.
 *
 * Application may provide image storage for new IR image. Image nature (Raw or Fixed) depend on
 * processing settings (see \ref Module_Processing).
 *
 * IR image is <b>1280 width by 1024 heigth</b>. Pixel storage is unsigned short, with 16bit effective, LSB aligned.
 *
 * Along IR Image, some meta data are provides.
 *
 * @{ */
/** Query image from Crius1280.
 * \param[in] paHandle Crius1280 handle.
 * \param[out] paImage Image placeholder for new image. Must be at least <em>1280 x 1024 x 2= 2000KB</em>.
 * \param[out] paMeta Meta-Data placeholder. Must be at least 135 32bit values :
 * \li [0] fpa temperature in celsius (cast float to get it).
 * \li [1] period from previous image (in microsecond).
 * \li [2] frame counter (16bit effective).
 * \li [3-4] microseconds since epoch (Jan 1, 1970), on 64 bits (use 2 values).
 * \li [5-6] Reserved.
 * \li [7-134] Histogram.
 * \param[in] paiTimeout Operation timeout in millisecond.
 *
*/
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_GetImage(HANDLE paHandle, unsigned short* paImage, int* paMeta, int paiTimeout);

//! @}


/** \addtogroup Module_Control
 *
 *
 * @{ */

/** Query string feature.
 * \param[in] paHandle Crius1280 handle.
 * \param[in] paeFeature Feature requested.
 * \param[out] paStr String from requested feature.
 * \warning String Feature are 32 byte large, including null byte. Ensure paStr is large enougt.
*/
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_GetStringFeature(HANDLE paHandle, int paeFeature, char* paStr);

/** Query integer feature.
 * \param[in] paHandle Crius1280 handle.
 * \param[in] paeFeature Feature requested.
 * \param[out] paUInt Integer value from requested feature.
*/
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_GetUIntFeature(HANDLE paHandle, int paeFeature, unsigned int* paUInt);

/** Query float feature.
 * \param[in] paHandle Crius1280 handle.
 * \param[in] paeFeature Feature requested.
 * \param[out] paFloat Float value from requested feature.
*/
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_GetFloatFeature(HANDLE paHandle, int paeFeature, float* paFloat);


/** Set string feature.
 * \param[in] paHandle Crius1280 handle.
 * \param[in] paeFeature Feature written.
 * \param[in] paStr String for written feature.
 * \warning String Feature are 32 byte large, including null byte. Ensure paStr is large enougt.
*/
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_SetStringFeature(HANDLE paHandle, int paeFeature, const char* paStr);

/** Set integer feature.
 * \param[in] paHandle Crius1280 handle.
 * \param[in] paeFeature Feature written.
 * \param[in] paUInt Integer value for written feature.
*/
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_SetUIntFeature(HANDLE paHandle, int paeFeature, unsigned int paUInt);

/** Query float feature.
 * \param[in] paHandle Crius1280 handle.
 * \param[in] paeFeature Feature written.
 * \param[in] paFloat Float value for written feature.
*/
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_SetFloatFeature(HANDLE paHandle, int paeFeature, float paFloat);

//! @}

/** \addtogroup Module_Processing
 *
 * This set of function provides control over image processing.
 * \li Query and change processing step state (enable or disable).
 * \li Query processing parameters.
 * \li Set processing parameters.
 *
 * Processing is compose of :
 * \li Bad pixel correction.
 * \li Non linearity correction.
 *
 * \see <em>User's Guide</em> or \ref ProcessingChainPage for details
 *
 * @{ */

/** Configure Internal Calibration.
 * \param[in] paHandle Crius1280 handle.
 * \param[in] paParam configuration to apply.
 * \li bit[0] Enable (1) or Disable (0) the automatic fast calibration associated with mechanical shutter
 * \li bit[1-31] Reserved.
*/
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_SetCalibrationConfig(HANDLE paHandle, int paParam);

/** Enable/Disable NUC processing steps. These are enabled by default at connection.
 * \param[in] paHandle Crius1280 handle.
 * \param[in] paBadPixels Enable(1)/Disable(0) bad pixels correction.
 * \param[in] paNUC Enable(1)/Disable(0) Non Uniformity Correction.
 * \return This return error eProxy1280_12USBFeatureNotAvailable if Shutterless is activated.
*/
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_SetNUCProcessing(HANDLE paHandle, unsigned char paBadPixels, unsigned char paNUC);

/** Query NUC processing steps status.
 * \param[in] paHandle Crius1280 handle.
 * \param[out] paBadPixels bad pixels correction enable(1) or disable(0).
 * \param[out] paNUC Non Uniformity Correction enable(1) or disable(0).
 * \return This return error eProxy1280_12USBFeatureNotAvailable if Shutterless is activated.
*/
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_GetNUCProcessing(HANDLE paHandle, unsigned char* paBadPixels, unsigned char* paNUC);


/** Enable/Disable ShutterLess processing.
 * \param[in] paHandle Crius1280 handle.
 * \param[in] bActivate Enable(true)/Disable(false) Shutterless processing.
 * \return This function return eProxy1280_12USBFeatureNotAvailable error if Shutterless is unavailable on this module.
*/
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_SetShutterLessProcessing(HANDLE paHandle, bool bActivate);

/** Query Shutterless processing status.
 * \param[in] paHandle Crius1280 handle.
 * \param[out] pbIsActive shutterless processing enable(true) or disable(false).
*/
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_GetShutterLessProcessing(HANDLE paHandle, bool *pbIsActive);

/** Set Auto Gain Control processing step. By default, No AGC processing set.
 * \param[in] paHandle Crius1280 handle.
 * \param[in] paeAGCProcessing see eAGCProcessingValue for values.
*/
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_SetAGCProcessing(HANDLE paHandle, unsigned char paeAGCProcessing);

/** Query processing steps status.
 * \param[in] paHandle Crius1280 handle.
 * \param[out] paeAGCProcessing see eAGCProcessingValue for values.
*/
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_GetAGCProcessing(HANDLE paHandle, unsigned char* paeAGCProcessing);

DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_SetCurrentAGCLocal(
    HANDLE       panhandle,
    //customer acces
    float        paGlobalContrastStrength,
    float        paLocalContrastStrength,
    int          paSpeed
);

DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_SetCurrentAGCLocal_devinternalonly(
    HANDLE       panhandle,
    //dev acces only
    unsigned int paAGCLocalMode,     // uniquement Semiauto (pour l’instant)
    int          pabins,
    int          paeAGCNb_tiles_x,
    int          paeAGCNb_tiles_y,
    int          paeAGCswitch_external,
    float        paeAGCHot_details
);


/** Set Gains values for NUC processing.
 * \param[in] paHandle Crius1280 handle.
 * \param[in] paTableGains New Gains values for NUC processing.
 * \note Each pixel must have a value. So paTableGains must contains 1280 * 1280 float values (4 bytes float).
*/
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_SetCurrentTableGain(HANDLE paHandle, float* paTableGains);

/** Set Offset values for NUC processing.
 * \param[in] paHandle Crius1280 handle.
 * \param[in] paTableOffsets New offsets values for NUC processing.
 * \note Each pixel must have a value. So paTableGains must contains 1280 * 1024 values (2 bytes signed value).
*/
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_SetCurrentTableOffset(HANDLE paHandle, signed short* paTableOffsets);

/** Set bad pixels position in image for bad pixels correction.
 * \param[in] paHandle Crius1280 handle.
 * \param[in] paTableX,paTableY Bad pixels position in image.
 * \param[in] paCount bad pixels count.
*/
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_SetCurrentBadPixels(HANDLE paHandle, unsigned short *paTableX, unsigned short *paTableY,
                                             unsigned short paCount );

/** Set Shutterless data for restore purpose. Shutterless data must be considered as binary and must not be modified.
 * \param[in] paHandle Crius1280 handle.
 * \param[in] paShutterless values.
*/
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_SetCurrentShutterless(HANDLE paHandle, unsigned int* paShutterless);

/** Get Shutterless size of the data for backup and restore purpose.
 * \param[in] paHandle Crius1280 handle.
 * \param[out] pSize size of shutterless data in bytes.
*/
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_GetCurrentShutterlessSize(HANDLE paHandle, unsigned int* pSize);

/** Get Shutterless data for backup purpose. Shutterless data must be considered as binary and must not be modified.
 * \param[in] paHandle Crius1280 handle.
 * \param[in] paShutterless New Shutterless values.
*/
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_GetCurrentShutterless(HANDLE paHandle, unsigned int* paShutterless);

/** Get Gains current values from NUC processing.
 * \param[in] paHandle Crius1280 handle.
 * \param[in] paTableGains New Gains values for NUC processing.
 * \note Each pixel must have a value. So paTableGains must contains 1280 * 1024 float values (4 bytes float).
*/
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_GetCurrentTableGain(HANDLE paHandle, float* paTableGains);

/** Get Offset current values from NUC processing.
 * \param[in] paHandle Crius1280 handle.
 * \param[in] paTableOffsets New offsets values for NUC processing.
 * \note Each pixel must have a value. So  paTableGains must contains 1280 * 1024 values (2 bytes signed value).
*/
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_GetCurrentTableOffset(HANDLE paHandle, signed short* paTableOffsets);

/** Get current bad pixels position in image from bad pixels correction.
 * \param[in] paHandle Crius1280 handle.
 * \param[in] paTableX,paTableY Bad pixels position in image.
 * \param paCount Initial bad pixels array size, on return, bad pixel count.
 * \note paCount must be init with  paTableX / paTableY placeholder size (to avoid overflow),
 * and will be modified by function with current bad pixel count.
*/
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_GetCurrentBadPixels(HANDLE paHandle, unsigned short *paTableX, unsigned short *paTableY,
                                             unsigned short *paCount );

//! @}

/** \addtogroup Module_Storage
 *  Crius1280 provides \b 8 slots to store Gain or Offset value. Slot are not dedicated to a kind of data.
 *  \attention Storage space is limited into Crius1280. Hence, data (Gain or Offset) are rounded to fit into slot.
 *  This may involve difference if your store data, read it, and compare to your initial values.
 *  For coherence, this data reduction is also apply when update NUC processing data (see \ref Module_Processing).
 *
 *  Save functions provides a \em MakeDefault parameter. When set to 1 (enable), this will mark slot as default.
 * When application connect to Crius1280, Proxy1280_12USB_ConnectToModule() function will look for default slot,
 * and load into processing data from slot.
 @{ */

/** Default slot index for Gain values and Offset values, last setting's bank used.
 * \param[in] paHandle Crius1280 handle.
 * \param[out] paiIdxGains Gain slot index, of 255 if no default Gain slot index.
 * \param[out] paiIdxOffsets Offset slot index, of 255 if no default Offset slot index.
 * \param[out] paiIdxBank Settings bank index, of 255 if no default settings index.
 * \note No need to call and use this function (already done at Crius1280 connection)
 **/
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_StartupDefault(HANDLE paHandle, unsigned char *paiIdxGains, unsigned char* paiIdxOffsets, unsigned char *paiIdxBank);

/** Query slot data type.
 * \param[in] paHandle Crius1280 handle.
 * \param[in] paiIndex Slot index to query.
 * \param[out] paeType Slot type.
 * \param[out] paData Table associate data. NULL, or 60 bytes placeholder. paData is additional data associated to Gain or Offset array, which can be used freely by application for instance to keep a trace of Gain or Offset table calibration conditions, either sensitivity, either focal plane array temperature.
 * Slot type value are :
 *\li 0 :Empty slot.
 *\li 1 :Gain values.
 *\li 2 :Offset values.
 **/
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_SlotType(HANDLE paHandle, unsigned char paiIndex, unsigned char* paeType,
                                                           void* paData);


/** Retrieve Crius1280 slot data as Gain values.<br>
 * This function may failed if slot is empty, or slot data are not Gain values.
 * \param[in] paHandle Crius1280 handle.
 * \param[in] paiIndex Slot index as data.
 * \param[out] paTableGain Gain values from Crius1280 slot.
 * \param[out] paData Table associate data. NULL, or 60 bytes placeholder. paData is additional data associated to Gain or Offset array, which can be used freely by application for instance to keep a trace of Gain or Offset table calibration conditions, either sensitivity, either focal plane array temperature.
 */
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_LoadTableGain(HANDLE paHandle, unsigned char paiIndex, float* paTableGain,
                                                                void* paData);

/** Retrieve Crius1280 slot data as Offset values.<br>
 * This function may failed if slot is empty, or slot data are not Offset values.
 * \param[in] paHandle Crius1280 handle.
 * \param[in] paiIndex Slot index as data.
 * \param[out] paTableOffset Offset values from Crius1280 slot.
 * \param[out] paData Table associate data. NULL, or 60 bytes placeholder. paData is additional data associated to Gain or Offset array, which can be used freely by application for instance to keep a trace of Gain or Offset table calibration conditions, either sensitivity, either focal plane array temperature.
 */
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_LoadTableOffset(HANDLE paHandle, unsigned char paiIndex, short* paTableOffset,
                                                                  void* paData);


/** Retrieve bad pixel position in image from Crius1280.
 * \param[in] paHandle Crius1280 handle.
 * \param[out] paTableX,paTableY Bad pixels position in image.
 * \param paCount Initial bad pixels array size, on return, bad pixel count.
 * \note paCount must be init with paTableX / paTableY placeholder size (to avoid overflow),
 * and will be modified by function with current bad pixel count.
*/
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_LoadBadPixels(HANDLE paHandle,
                                                                unsigned short *paTableX, unsigned short *paTableY,
                                                                unsigned short* paCount);


/** Save Gain values into Crius1280 slot data.
 * \param[in] paHandle Crius1280 handle.
 * \param[in] paiIndex Slot index.
 * \param[in] paTableGain Gain values to store into Crius1280 slot.
 * \param[in] paData Table associate data. NULL, or 60 bytes placeholder. paData is additional data associated to Gain or Offset array, which can be used freely by application for instance to keep a trace of Gain or Offset table calibration conditions, either sensitivity, either focal plane array temperature.
 */
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_SaveTableGain(HANDLE paHandle, unsigned char paiIndex, const float* paTableGain,
                                              void* paData);

/** Save Offset values into Crius1280 slot data.
 * \param[in] paHandle Crius1280 handle.
 * \param[in] paiIndex Slot index.
 * \param[in] paTableOffset Offset values to store into Crius1280 slot.
 * \param[in] paData Table associate data. NULL, or 60 bytes placeholder. paData is additional data associated to Gain or Offset array, which can be used freely by application for instance to keep a trace of Gain or Offset table calibration conditions, either sensitivity, either focal plane array temperature.
 */
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_SaveTableOffset(HANDLE paHandle, unsigned char paiIndex, const short* paTableOffset,
                                                                  void* paData);

/** Save bad pixel position into Crius1280 slot data.
 * \param[in] paHandle Crius1280 handle.
 * \param[in] paTableX,paTableY Bad pixels position in image.
 * \param[in] paCount bad pixels count.
*/
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_SaveBadPixels(HANDLE paHandle, const unsigned short *paTableX, const unsigned short* paTableY, unsigned short paCount);


/** Use Crius1280 slot data as Gain values for NUC processing,
 * i.e. retrieve it from Crius1280, and set it to NUC processing.
 * \param[in] paHandle Crius1280 handle.
 * \param[in] paiIndex Slot index as data.
 */
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_LoadCurrentTableGain(HANDLE paHandle, unsigned char paiIndex);

/** Use Crius1280 slot data as Offset values for NUC processing,
 * i.e. retrieve it from Crius1280, and set it to NUC processing.
 * \param[in] paHandle Crius1280 handle.
 * \param[in] paiIndex Slot index as data.
 */
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_LoadCurrentTableOffset(HANDLE paHandle, unsigned char paiIndex);

/** Use Crius1280 stored bad pixel for bad pixel correction.
 * \param[in] paHandle Crius1280 handle.
 */
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_LoadCurrentBadPixels(HANDLE paHandle);

/** Save current Gain values into Crius1280 slot data.
 * \param[in] paHandle Crius1280 handle.
 * \param[in] paiIndex Slot index.
 * \param[in] paData Table associate data. NULL, or 60 bytes placeholder. paData is additional data associated to Gain or Offset array, which can be used freely by application for instance to keep a trace of Gain or Offset table calibration conditions, either sensitivity, either focal plane array temperature.
 */
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_SaveCurrentTableGain(HANDLE paHandle, unsigned char paiIndex, const void *paData);

/** Save Offset values into Crius1280 slot data.
 * \param[in] paHandle Crius1280 handle.
 * \param[in] paiIndex Slot index.
 * \param[in] paData Table associate data. NULL, or 60 bytes placeholder. paData is additional data associated to Gain or Offset array, which can be used freely by application for instance to keep a trace of Gain or Offset table calibration conditions, either sensitivity, either focal plane array temperature.
 */
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_SaveCurrentTableOffset(HANDLE paHandle, unsigned char paiIndex, const void *paData);

/** Save bad pixel position into Crius1280 slot data.
 * \param[in] paHandle Crius1280 handle.
*/
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_SaveCurrentBadPixels(HANDLE paHandle);

/** Save Shutterless Tables into Crius1280.
 * \param[in] paHandle Crius1280 handle.
 * \return eProxy1280_12USBFeatureNotAvailable error if Shutterless is unavailable on the module.
*/
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_SaveCurrentShutterlessTables(HANDLE paHandle);

/** Load Shutterless Tables from Crius1280 in order to use it with shutterless processing
 * \param[in] paHandle Crius1280 handle.
 * \return eProxy1280_12USBFeatureNotAvailable error if Shutterless is unavailable on the module.
*/
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_LoadCurrentShutterlessTables(HANDLE paHandle);

/** Clear Saved Calibration data format from Crius1280 in order to be able to save the other format (to avoid format mismatch error).
 * \param[in] paHandle Crius1280 handle.
 * \param[in] paiType Calibration type.
 * Calibration type values are :
 *\li 1 :Standard calibration.
 *\li 2 :Shutterless calibration.
**/
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_ClearSavedCalibrationData(HANDLE paHandle, unsigned char paiType);

//! @}


/** \addtogroup Module_Calibration
 * This set of function provide 2 kind of NUC calibrations :
 * \li Full Calibration.
 * \li Fast Calibration.
 *
 * And Shutterless Calibration compose of :
 * \li T0 Calibration.
 * \li T1 Calibration.
 *
 * \see <em>User's Guide</em> or \ref CalibrationProcessPage for details.
* @{ */


/** Abort a Calibration process and reset the sequencing.
 * None of the corrections table will be change by the abort calibration.
 *
 * \param[in] paHandle Crius1280 Handle.
 */
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_AbortCalibration(HANDLE paHandle);

/** Prepare NUC Calibration engine.
 * \param[in] paHandle Crius1280 Handle.
 * \param[in] iStage Stage of the calibration (1 or 2).
 * \return eProxy1280_12USBSequencingError see \ref CalibrationProcessPage for details.
*/
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_InitShutter2PtsCalibration(HANDLE paHandle, unsigned int iStage);

/** Add image for Shutter 2pts calibration.
  *
  * Low temperature image for iStage = 1, High temperature image for iStage = 2.
  *
  * \param[in] paHandle Crius1280 Handle.
  * \param[in] iStage Stage of calibration (1 (low) or 2 (high)).
  * \return eProxy1280_12USBSequencingError see \ref CalibrationProcessPage for details.
  */
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_StepShutter2PtsCalibration(HANDLE paHandle, unsigned int iStage);

/** Perform two points calibration using low and high temperature images.
 *
 * Once calibration is done, new Gain, Offset and bad pixel are set to current NUC and BPC processing.
 *
 * \param[in] paHandle Crius1280 handle.
 * \param[in] iStage Stage of the calibration. If stage = 2, perform the final step of calibration. Once is done, new Gain, Offset
 * and bad pixel are set to current NUC and BPC processing.
 * \return eProxy1280_12USBSequencingError see \ref CalibrationProcessPage for details.
 */
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_FinishShutter2PtsCalibration(HANDLE paHandle,unsigned int iStage);

/** Prepare Shutter Calibration engine, also called one point calibration.
 *
 * This calibration will only produce new Offset values.
 *
 * \param[in] paHandle Crius1280 handle.
 * \return eProxy1280_12USBSequencingError see \ref CalibrationProcessPage for details.
*/
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_InitShutterCalibration(HANDLE paHandle);

/** Add image to prepare Shutter Calibration
 *
 * \param[in] paHandle Crius1280 handle.
 * \return eProxy1280_12USBSequencingError see \ref CalibrationProcessPage for details.
 */
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_StepShutterCalibration(HANDLE paHandle);

/** Perform Shutter calibration.
 *
 * Once calibration is done, Offset values are set to current NUC processing.
 *
 * \param[in] paHandle Crius1280 handle.
 * \return eProxy1280_12USBSequencingError see \ref CalibrationProcessPage for details.
 */
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_FinishShutterCalibration(HANDLE paHandle);



/** Initialise Stage for Shutterless Calibration T0
 *
 * Must be use on correct sequencing with Crius1280 shutterless module.
 *
 * \param[in] paHandle Crius1280 handle.
 * \param[in] iStage Stage number of calibration.
 * \return eProxy1280_12USBSequencingError see \ref CalibrationProcessPage for details.
 */
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_InitSLCalibrationT0(HANDLE paHandle, unsigned int iStage);

/** Add image for Shutterless Calibration T0
 *
 * Must be used on correct sequencing with Crius1280 shutterless module.
 *
 * \param[in] paHandle Crius1280 handle.
 * \param[in] iStage Stage number of calibration (1 = low temperature, 2 = high temperature).
 * \return eProxy1280_12USBSequencingError see \ref CalibrationProcessPage for details.
 */
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_StepSLCalibrationT0(HANDLE paHandle, unsigned int iStage);

/** Perform Shutterless T0 calibration
 *
 * Must be used on correct sequencing with Crius1280 shutterless module.
 * Once calibration is done, new Shutterless tables are set to current Shutterless processing.
 *
 * \param[in] paHandle Crius1280 handle.
 * \param[in] iStage Stage number of calibration (1 = low temperature, 2 = high temperature).
 * \return eProxy1280_12USBSequencingError see \ref CalibrationProcessPage for details.
 */
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_FinishSLCalibrationT0(HANDLE paHandle, unsigned int iStage);



/** Initialise Shutterless Calibration T1
 *
 * Must be use on correct sequencing with Crius1280 shutterless module.
 *
 * \param[in] paHandle Crius1280 handle.
 * \return eProxy1280_12USBSequencingError see \ref CalibrationProcessPage for details.
 */
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_InitSLCalibrationT1(HANDLE paHandle);

/** Add image for Shutterless Calibration T1
 *
 * Must be use on correct sequencing with Crius1280 shutterless module.
 *
 * \param[in] paHandle Crius1280 handle.
 * \return eProxy1280_12USBSequencingError see \ref CalibrationProcessPage for details.
 */
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_StepSLCalibrationT1(HANDLE paHandle);

/** Perform Shutterless Calibration T1
 *
 * Must be use on correct sequencing with Crius1280 shutterless module.
 * Once Calibration is done, new Shutterless T1 tables are set for current Shutterless processing.
 *
 * \param[in] paHandle Crius1280 handle.
 * \return eProxy1280_12USBSequencingError see \ref CalibrationProcessPage for details.
 */
DALProxy1280_12USB_API eDALProxy1280_12USBErr Proxy1280_12USB_FinishSLCalibrationT1(HANDLE paHandle);

//! @}

#ifdef __cplusplus
}
   }
#endif

#endif // __DALProxy1280_12USB_H__
