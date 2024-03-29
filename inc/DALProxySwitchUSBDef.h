#ifndef DALPROXYSWITCHUSBDEF_H
#define DALPROXYSWITCHUSBDEF_H

#ifdef SMARTIR80L
	#define DALPROXY_NAMESPACE DALProxy80LUSB_namespace
    #include "DALProxy80LUSBDef.h"
#elif SMARTIR384C
	#define DALPROXY_NAMESPACE DALProxy384CUSB_namespace
    #include "DALProxy384CUSBDef.h"
#elif SMARTIR384L
	#define DALPROXY_NAMESPACE DALProxy384LUSB_namespace
    #include "DALProxy384LUSBDef.h"
#elif SMARTIR384
	#define DALPROXY_NAMESPACE DALProxy384USB_namespace
    #include "DALProxy384USBDef.h"
#elif SMARTIR160
	#define DALPROXY_NAMESPACE DALProxy160USB_namespace
    #include "DALProxy160USBDef.h"
#elif IRLUGX320
	#define DALPROXY_NAMESPACE DALProxy320_12USB_namespace
    #include "DALProxy320_12USBDef.h"
#elif IRLUGX640
	#define DALPROXY_NAMESPACE DALProxy640_12USB_namespace
    #include "DALProxy640_12USBDef.h"
#elif MICROCUBE640
	#define DALPROXY_NAMESPACE DALProxy640M_12USB_namespace
    #include "DALProxy640M_12USBDef.h"
#elif SMARTIR640
	#define DALPROXY_NAMESPACE DALProxy640USB_namespace
    #include "DALProxy640USBDef.h"
#elif IRLUGX1M3
	#define DALPROXY_NAMESPACE DALProxy1280_12USB_namespace
    #include "DALProxy1280_12USBDef.h"
#endif

#ifdef CONFIG_DAL
    #include "DALProxyUSB_internal.h"
#endif


#ifdef SMARTIR80L

#define IRIMAGE_WIDTH DAL_PROXY80L_IRIMAGE_WIDTH
#define IRIMAGE_HEIGHT DAL_PROXY80L_IRIMAGE_HEIGHT
#define IRIMAGE_PIXEL DAL_PROXY80L_IRIMAGE_PIXEL
#define IRIMAGE_RESOLUTION DAL_PROXY80L_IRIMAGE_RESOLUTION
#define IRIMAGE_PIXEL_MAX DAL_PROXY80L_IRIMAGE_PIXEL_MAX
#define IRIMAGE_NBPIXELS DAL_PROXY80L_IRIMAGE_NBPIXELS
#define IRIMAGE_PAYLOAD DAL_PROXY80L_IRIMAGE_PAYLOAD
#define IRIMAGE_META_COUNT DAL_PROXY80L_IRIMAGE_META_COUNT
#define IRIMAGE_META_TEMP DAL_PROXY80L_IRIMAGE_META_TEMP
#define IRIMAGE_META_PERIOD DAL_PROXY80L_IRIMAGE_META_PERIOD
#define IRIMAGE_META_COUNTER DAL_PROXY80L_IRIMAGE_META_COUNTER
#define IRIMAGE_EPOCH DAL_PROXY80L_IRIMAGE_EPOCH
#define IRIMAGE_EPOCHLow DAL_PROXY80L_IRIMAGE_EPOCHLow
#define IRIMAGE_FRAMEINFO DAL_PROXY80L_IRIMAGE_FRAMEINFO
#define IRIMAGE_FRAMEAGE DAL_PROXY80L_IRIMAGE_FRAMEAGE
#define IRIMAGE_FRAMEHISTO DAL_PROXY80L_IRIMAGE_FRAMEHISTO
#define IRIMAGE_ENDFRAMEHISTO DAL_PROXY80L_IRIMAGE_ENDFRAMEHISTO
#define SLOT_EMPTY DAL_PROXY80L_SLOT_EMPTY
#define SLOT_TYPE_GAIN DAL_PROXY80L_SLOT_TYPE_GAIN
#define SLOT_TYPE_OFFSET DAL_PROXY80L_SLOT_TYPE_OFFSET
#define NUC_SLOT_COUNT DAL_PROXY80L_NUC_SLOT_COUNT
#define NUC_BANK_COUNT DAL_PROXY80L_NUC_BANK_COUNT
#define NUC_INFO_USER_SIZE DAL_PROXY80L_NUC_INFO_USER_SIZE
#define BANK_SETTINGS_COUNT DAL_PROXY80L_BANK_SETTINGS_COUNT
#define BADPIXELS_COUNT DAL_PROXY80L_BADPIXELS_COUNT
#define PIXEL_IGNORED DAL_PROXY80L_PIXEL_IGNORED
#define PIXEL_ORIGINAL DAL_PROXY80L_PIXEL_ORIGINAL
#define PIXEL_FIXED DAL_PROXY80L_PIXEL_FIXED
#define FEATURE_STRING_SIZE DAL_PROXY80L_FEATURE_STRING_SIZE

#elif SMARTIR160

#define IRIMAGE_WIDTH DAL_PROXY160_IRIMAGE_WIDTH
#define IRIMAGE_HEIGHT DAL_PROXY160_IRIMAGE_HEIGHT
#define IRIMAGE_PIXEL DAL_PROXY160_IRIMAGE_PIXEL
#define IRIMAGE_RESOLUTION DAL_PROXY160_IRIMAGE_RESOLUTION
#define IRIMAGE_PIXEL_MAX DAL_PROXY160_IRIMAGE_PIXEL_MAX
#define IRIMAGE_NBPIXELS DAL_PROXY160_IRIMAGE_NBPIXELS
#define IRIMAGE_PAYLOAD DAL_PROXY160_IRIMAGE_PAYLOAD
#define IRIMAGE_META_COUNT DAL_PROXY160_IRIMAGE_META_COUNT
#define IRIMAGE_META_TEMP DAL_PROXY160_IRIMAGE_META_TEMP
#define IRIMAGE_META_PERIOD DAL_PROXY160_IRIMAGE_META_PERIOD
#define IRIMAGE_META_COUNTER DAL_PROXY160_IRIMAGE_META_COUNTER
#define IRIMAGE_EPOCH DAL_PROXY160_IRIMAGE_EPOCH
#define IRIMAGE_EPOCHLow DAL_PROXY160_IRIMAGE_EPOCHLow
#define IRIMAGE_FRAMEINFO DAL_PROXY160_IRIMAGE_FRAMEINFO
#define IRIMAGE_FRAMEAGE DAL_PROXY160_IRIMAGE_FRAMEAGE
#define IRIMAGE_FRAMEHISTO DAL_PROXY160_IRIMAGE_FRAMEHISTO
#define IRIMAGE_ENDFRAMEHISTO DAL_PROXY160_IRIMAGE_ENDFRAMEHISTO
#define SLOT_EMPTY DAL_PROXY160_SLOT_EMPTY
#define SLOT_TYPE_GAIN DAL_PROXY160_SLOT_TYPE_GAIN
#define SLOT_TYPE_OFFSET DAL_PROXY160_SLOT_TYPE_OFFSET
#define NUC_SLOT_COUNT DAL_PROXY160_NUC_SLOT_COUNT
#define NUC_BANK_COUNT DAL_PROXY160_NUC_BANK_COUNT
#define NUC_INFO_USER_SIZE DAL_PROXY160_NUC_INFO_USER_SIZE
#define BANK_SETTINGS_COUNT DAL_PROXY160_BANK_SETTINGS_COUNT
#define BADPIXELS_COUNT DAL_PROXY160_BADPIXELS_COUNT
#define PIXEL_IGNORED DAL_PROXY160_PIXEL_IGNORED
#define PIXEL_ORIGINAL DAL_PROXY160_PIXEL_ORIGINAL
#define PIXEL_FIXED DAL_PROXY160_PIXEL_FIXED
#define FEATURE_STRING_SIZE DAL_PROXY160_FEATURE_STRING_SIZE

#elif IRLUGX320 // SMARTIR320

#define IRIMAGE_WIDTH DAL_PROXY320_12_IRIMAGE_WIDTH
#define IRIMAGE_HEIGHT DAL_PROXY320_12_IRIMAGE_HEIGHT
#define IRIMAGE_PIXEL DAL_PROXY320_12_IRIMAGE_PIXEL
#define IRIMAGE_RESOLUTION DAL_PROXY320_12_IRIMAGE_RESOLUTION
#define IRIMAGE_PIXEL_MAX DAL_PROXY320_12_IRIMAGE_PIXEL_MAX
#define IRIMAGE_NBPIXELS DAL_PROXY320_12_IRIMAGE_NBPIXELS
#define IRIMAGE_PAYLOAD DAL_PROXY320_12_IRIMAGE_PAYLOAD
#define IRIMAGE_META_COUNT DAL_PROXY320_12_IRIMAGE_META_COUNT
#define IRIMAGE_META_TEMP DAL_PROXY320_12_IRIMAGE_META_TEMP
#define IRIMAGE_META_PERIOD DAL_PROXY320_12_IRIMAGE_META_PERIOD
#define IRIMAGE_META_COUNTER DAL_PROXY320_12_IRIMAGE_META_COUNTER
#define IRIMAGE_EPOCH DAL_PROXY320_12_IRIMAGE_EPOCH
#define IRIMAGE_EPOCHLow DAL_PROXY320_12_IRIMAGE_EPOCHLow
#define IRIMAGE_FRAMEINFO DAL_PROXY320_12_IRIMAGE_FRAMEINFO
#define IRIMAGE_FRAMEAGE DAL_PROXY320_12_IRIMAGE_FRAMEAGE
#define IRIMAGE_FRAMEHISTO DAL_PROXY320_12_IRIMAGE_FRAMEHISTO
#define IRIMAGE_ENDFRAMEHISTO DAL_PROXY320_12_IRIMAGE_ENDFRAMEHISTO
#define SLOT_EMPTY DAL_PROXY320_12_SLOT_EMPTY
#define SLOT_TYPE_GAIN DAL_PROXY320_12_SLOT_TYPE_GAIN
#define SLOT_TYPE_OFFSET DAL_PROXY320_12_SLOT_TYPE_OFFSET
#define NUC_SLOT_COUNT DAL_PROXY320_12_NUC_SLOT_COUNT
#define NUC_BANK_COUNT DAL_PROXY320_12_NUC_BANK_COUNT
#define NUC_INFO_USER_SIZE DAL_PROXY320_12_NUC_INFO_USER_SIZE
#define BANK_SETTINGS_COUNT DAL_PROXY320_12_BANK_SETTINGS_COUNT
#define BADPIXELS_COUNT DAL_PROXY320_12_BADPIXELS_COUNT
#define PIXEL_IGNORED DAL_PROXY320_12_PIXEL_IGNORED
#define PIXEL_ORIGINAL DAL_PROXY320_12_PIXEL_ORIGINAL
#define PIXEL_FIXED DAL_PROXY320_12_PIXEL_FIXED
#define FEATURE_STRING_SIZE DAL_PROXY320_12_FEATURE_STRING_SIZE

#elif SMARTIR384L

#define IRIMAGE_WIDTH DAL_PROXY384L_IRIMAGE_WIDTH
#define IRIMAGE_HEIGHT DAL_PROXY384L_IRIMAGE_HEIGHT
#define IRIMAGE_PIXEL DAL_PROXY384L_IRIMAGE_PIXEL
#define IRIMAGE_RESOLUTION DAL_PROXY384L_IRIMAGE_RESOLUTION
#define IRIMAGE_PIXEL_MAX DAL_PROXY384L_IRIMAGE_PIXEL_MAX
#define IRIMAGE_NBPIXELS DAL_PROXY384L_IRIMAGE_NBPIXELS
#define IRIMAGE_PAYLOAD DAL_PROXY384L_IRIMAGE_PAYLOAD
#define IRIMAGE_META_COUNT DAL_PROXY384L_IRIMAGE_META_COUNT
#define IRIMAGE_META_TEMP DAL_PROXY384L_IRIMAGE_META_TEMP
#define IRIMAGE_META_PERIOD DAL_PROXY384L_IRIMAGE_META_PERIOD
#define IRIMAGE_META_COUNTER DAL_PROXY384L_IRIMAGE_META_COUNTER
#define IRIMAGE_EPOCH DAL_PROXY384L_IRIMAGE_EPOCH
#define IRIMAGE_EPOCHLow DAL_PROXY384L_IRIMAGE_EPOCHLow
#define IRIMAGE_FRAMEINFO DAL_PROXY384L_IRIMAGE_FRAMEINFO
#define IRIMAGE_FRAMEAGE DAL_PROXY384L_IRIMAGE_FRAMEAGE
#define IRIMAGE_FRAMEHISTO DAL_PROXY384L_IRIMAGE_FRAMEHISTO
#define IRIMAGE_ENDFRAMEHISTO DAL_PROXY384L_IRIMAGE_ENDFRAMEHISTO
#define SLOT_EMPTY DAL_PROXY384L_SLOT_EMPTY
#define SLOT_TYPE_GAIN DAL_PROXY384L_SLOT_TYPE_GAIN
#define SLOT_TYPE_OFFSET DAL_PROXY384L_SLOT_TYPE_OFFSET
#define NUC_SLOT_COUNT DAL_PROXY384L_NUC_SLOT_COUNT
#define NUC_BANK_COUNT DAL_PROXY384L_NUC_BANK_COUNT
#define NUC_INFO_USER_SIZE DAL_PROXY384L_NUC_INFO_USER_SIZE
#define BANK_SETTINGS_COUNT DAL_PROXY384L_BANK_SETTINGS_COUNT
#define BADPIXELS_COUNT DAL_PROXY384L_BADPIXELS_COUNT
#define PIXEL_IGNORED DAL_PROXY384L_PIXEL_IGNORED
#define PIXEL_ORIGINAL DAL_PROXY384L_PIXEL_ORIGINAL
#define PIXEL_FIXED DAL_PROXY384L_PIXEL_FIXED
#define FEATURE_STRING_SIZE DAL_PROXY384L_FEATURE_STRING_SIZE

#elif SMARTIR384C

#define IRIMAGE_WIDTH DAL_PROXY384C_IRIMAGE_WIDTH
#define IRIMAGE_HEIGHT DAL_PROXY384C_IRIMAGE_HEIGHT
#define IRIMAGE_PIXEL DAL_PROXY384C_IRIMAGE_PIXEL
#define IRIMAGE_RESOLUTION DAL_PROXY384C_IRIMAGE_RESOLUTION
#define IRIMAGE_PIXEL_MAX DAL_PROXY384C_IRIMAGE_PIXEL_MAX
#define IRIMAGE_NBPIXELS DAL_PROXY384C_IRIMAGE_NBPIXELS
#define IRIMAGE_PAYLOAD DAL_PROXY384C_IRIMAGE_PAYLOAD
#define IRIMAGE_META_COUNT DAL_PROXY384C_IRIMAGE_META_COUNT
#define IRIMAGE_META_TEMP DAL_PROXY384C_IRIMAGE_META_TEMP
#define IRIMAGE_META_PERIOD DAL_PROXY384C_IRIMAGE_META_PERIOD
#define IRIMAGE_META_COUNTER DAL_PROXY384C_IRIMAGE_META_COUNTER
#define IRIMAGE_EPOCH DAL_PROXY384C_IRIMAGE_EPOCH
#define IRIMAGE_EPOCHLow DAL_PROXY384C_IRIMAGE_EPOCHLow
#define IRIMAGE_FRAMEINFO DAL_PROXY384C_IRIMAGE_FRAMEINFO
#define IRIMAGE_FRAMEAGE DAL_PROXY384C_IRIMAGE_FRAMEAGE
#define IRIMAGE_FRAMEHISTO DAL_PROXY384C_IRIMAGE_FRAMEHISTO
#define IRIMAGE_ENDFRAMEHISTO DAL_PROXY384C_IRIMAGE_ENDFRAMEHISTO
#define SLOT_EMPTY DAL_PROXY384C_SLOT_EMPTY
#define SLOT_TYPE_GAIN DAL_PROXY384C_SLOT_TYPE_GAIN
#define SLOT_TYPE_OFFSET DAL_PROXY384C_SLOT_TYPE_OFFSET
#define NUC_SLOT_COUNT DAL_PROXY384C_NUC_SLOT_COUNT
#define NUC_BANK_COUNT DAL_PROXY384C_NUC_BANK_COUNT
#define NUC_INFO_USER_SIZE DAL_PROXY384C_NUC_INFO_USER_SIZE
#define BANK_SETTINGS_COUNT DAL_PROXY384C_BANK_SETTINGS_COUNT
#define BADPIXELS_COUNT DAL_PROXY384C_BADPIXELS_COUNT
#define PIXEL_IGNORED DAL_PROXY384C_PIXEL_IGNORED
#define PIXEL_ORIGINAL DAL_PROXY384C_PIXEL_ORIGINAL
#define PIXEL_FIXED DAL_PROXY384C_PIXEL_FIXED
#define FEATURE_STRING_SIZE DAL_PROXY384C_FEATURE_STRING_SIZE

#elif SMARTIR384

#define IRIMAGE_WIDTH DAL_PROXY384_IRIMAGE_WIDTH
#define IRIMAGE_HEIGHT DAL_PROXY384_IRIMAGE_HEIGHT
#define IRIMAGE_PIXEL DAL_PROXY384_IRIMAGE_PIXEL
#define IRIMAGE_RESOLUTION DAL_PROXY384_IRIMAGE_RESOLUTION
#define IRIMAGE_PIXEL_MAX DAL_PROXY384_IRIMAGE_PIXEL_MAX
#define IRIMAGE_NBPIXELS DAL_PROXY384_IRIMAGE_NBPIXELS
#define IRIMAGE_PAYLOAD DAL_PROXY384_IRIMAGE_PAYLOAD
#define IRIMAGE_META_COUNT DAL_PROXY384_IRIMAGE_META_COUNT
#define IRIMAGE_META_TEMP DAL_PROXY384_IRIMAGE_META_TEMP
#define IRIMAGE_META_PERIOD DAL_PROXY384_IRIMAGE_META_PERIOD
#define IRIMAGE_META_COUNTER DAL_PROXY384_IRIMAGE_META_COUNTER
#define IRIMAGE_EPOCH DAL_PROXY384_IRIMAGE_EPOCH
#define IRIMAGE_EPOCHLow DAL_PROXY384_IRIMAGE_EPOCHLow
#define IRIMAGE_FRAMEINFO DAL_PROXY384_IRIMAGE_FRAMEINFO
#define IRIMAGE_FRAMEAGE DAL_PROXY384_IRIMAGE_FRAMEAGE
#define IRIMAGE_FRAMEHISTO DAL_PROXY384_IRIMAGE_FRAMEHISTO
#define IRIMAGE_ENDFRAMEHISTO DAL_PROXY384_IRIMAGE_ENDFRAMEHISTO
#define SLOT_EMPTY DAL_PROXY384_SLOT_EMPTY
#define SLOT_TYPE_GAIN DAL_PROXY384_SLOT_TYPE_GAIN
#define SLOT_TYPE_OFFSET DAL_PROXY384_SLOT_TYPE_OFFSET
#define NUC_SLOT_COUNT DAL_PROXY384_NUC_SLOT_COUNT
#define NUC_BANK_COUNT DAL_PROXY384_NUC_BANK_COUNT
#define NUC_INFO_USER_SIZE DAL_PROXY384_NUC_INFO_USER_SIZE
#define BANK_SETTINGS_COUNT DAL_PROXY384_BANK_SETTINGS_COUNT
#define BADPIXELS_COUNT DAL_PROXY384_BADPIXELS_COUNT
#define PIXEL_IGNORED DAL_PROXY384_PIXEL_IGNORED
#define PIXEL_ORIGINAL DAL_PROXY384_PIXEL_ORIGINAL
#define PIXEL_FIXED DAL_PROXY384_PIXEL_FIXED
#define FEATURE_STRING_SIZE DAL_PROXY384_FEATURE_STRING_SIZE

#elif IRLUGX640

#define IRIMAGE_WIDTH DAL_PROXY640_12_IRIMAGE_WIDTH
#define IRIMAGE_HEIGHT DAL_PROXY640_12_IRIMAGE_HEIGHT
#define IRIMAGE_PIXEL DAL_PROXY640_12_IRIMAGE_PIXEL
#define IRIMAGE_RESOLUTION DAL_PROXY640_12_IRIMAGE_RESOLUTION
#define IRIMAGE_PIXEL_MAX DAL_PROXY640_12_IRIMAGE_PIXEL_MAX
#define IRIMAGE_NBPIXELS DAL_PROXY640_12_IRIMAGE_NBPIXELS
#define IRIMAGE_PAYLOAD DAL_PROXY640_12_IRIMAGE_PAYLOAD
#define IRIMAGE_META_COUNT DAL_PROXY640_12_IRIMAGE_META_COUNT
#define IRIMAGE_META_TEMP DAL_PROXY640_12_IRIMAGE_META_TEMP
#define IRIMAGE_META_PERIOD DAL_PROXY640_12_IRIMAGE_META_PERIOD
#define IRIMAGE_META_COUNTER DAL_PROXY640_12_IRIMAGE_META_COUNTER
#define IRIMAGE_EPOCH DAL_PROXY640_12_IRIMAGE_EPOCH
#define IRIMAGE_EPOCHLow DAL_PROXY640_12_IRIMAGE_EPOCHLow
#define IRIMAGE_FRAMEINFO DAL_PROXY640_12_IRIMAGE_FRAMEINFO
#define IRIMAGE_FRAMEAGE DAL_PROXY640_12_IRIMAGE_FRAMEAGE
#define IRIMAGE_FRAMEHISTO DAL_PROXY640_12_IRIMAGE_FRAMEHISTO
#define IRIMAGE_ENDFRAMEHISTO DAL_PROXY640_12_IRIMAGE_ENDFRAMEHISTO
#define SLOT_EMPTY DAL_PROXY640_12_SLOT_EMPTY
#define SLOT_TYPE_GAIN DAL_PROXY640_12_SLOT_TYPE_GAIN
#define SLOT_TYPE_OFFSET DAL_PROXY640_12_SLOT_TYPE_OFFSET
#define NUC_SLOT_COUNT DAL_PROXY640_12_NUC_SLOT_COUNT
#define NUC_BANK_COUNT DAL_PROXY640_12_NUC_BANK_COUNT
#define NUC_INFO_USER_SIZE DAL_PROXY640_12_NUC_INFO_USER_SIZE
#define BANK_SETTINGS_COUNT DAL_PROXY640_12_BANK_SETTINGS_COUNT
#define BADPIXELS_COUNT DAL_PROXY640_12_BADPIXELS_COUNT
#define PIXEL_IGNORED DAL_PROXY640_12_PIXEL_IGNORED
#define PIXEL_ORIGINAL DAL_PROXY640_12_PIXEL_ORIGINAL
#define PIXEL_FIXED DAL_PROXY640_12_PIXEL_FIXED
#define FEATURE_STRING_SIZE DAL_PROXY640_12_FEATURE_STRING_SIZE

#elif MICROCUBE640

#define IRIMAGE_WIDTH DAL_PROXY640M_12_IRIMAGE_WIDTH
#define IRIMAGE_HEIGHT DAL_PROXY640M_12_IRIMAGE_HEIGHT
#define IRIMAGE_PIXEL DAL_PROXY640M_12_IRIMAGE_PIXEL
#define IRIMAGE_RESOLUTION DAL_PROXY640M_12_IRIMAGE_RESOLUTION
#define IRIMAGE_PIXEL_MAX DAL_PROXY640M_12_IRIMAGE_PIXEL_MAX
#define IRIMAGE_NBPIXELS DAL_PROXY640M_12_IRIMAGE_NBPIXELS
#define IRIMAGE_PAYLOAD DAL_PROXY640M_12_IRIMAGE_PAYLOAD
#define IRIMAGE_META_COUNT DAL_PROXY640M_12_IRIMAGE_META_COUNT
#define IRIMAGE_META_TEMP DAL_PROXY640M_12_IRIMAGE_META_TEMP
#define IRIMAGE_META_PERIOD DAL_PROXY640M_12_IRIMAGE_META_PERIOD
#define IRIMAGE_META_COUNTER DAL_PROXY640M_12_IRIMAGE_META_COUNTER
#define IRIMAGE_EPOCH DAL_PROXY640M_12_IRIMAGE_EPOCH
#define IRIMAGE_EPOCHLow DAL_PROXY640M_12_IRIMAGE_EPOCHLow
#define IRIMAGE_FRAMEINFO DAL_PROXY640M_12_IRIMAGE_FRAMEINFO
#define IRIMAGE_FRAMEAGE DAL_PROXY640M_12_IRIMAGE_FRAMEAGE
#define IRIMAGE_FRAMEHISTO DAL_PROXY640M_12_IRIMAGE_FRAMEHISTO
#define IRIMAGE_ENDFRAMEHISTO DAL_PROXY640M_12_IRIMAGE_ENDFRAMEHISTO
#define SLOT_EMPTY DAL_PROXY640M_12_SLOT_EMPTY
#define SLOT_TYPE_GAIN DAL_PROXY640M_12_SLOT_TYPE_GAIN
#define SLOT_TYPE_OFFSET DAL_PROXY640M_12_SLOT_TYPE_OFFSET
#define NUC_SLOT_COUNT DAL_PROXY640M_12_NUC_SLOT_COUNT
#define NUC_BANK_COUNT DAL_PROXY640M_12_NUC_BANK_COUNT
#define NUC_INFO_USER_SIZE DAL_PROXY640M_12_NUC_INFO_USER_SIZE
#define BANK_SETTINGS_COUNT DAL_PROXY640M_12_BANK_SETTINGS_COUNT
#define BADPIXELS_COUNT DAL_PROXY640M_12_BADPIXELS_COUNT
#define PIXEL_IGNORED DAL_PROXY640M_12_PIXEL_IGNORED
#define PIXEL_ORIGINAL DAL_PROXY640M_12_PIXEL_ORIGINAL
#define PIXEL_FIXED DAL_PROXY640M_12_PIXEL_FIXED
#define FEATURE_STRING_SIZE DAL_PROXY640M_12_FEATURE_STRING_SIZE

#elif SMARTIR640

#define IRIMAGE_WIDTH DAL_PROXY640_IRIMAGE_WIDTH
#define IRIMAGE_HEIGHT DAL_PROXY640_IRIMAGE_HEIGHT
#define IRIMAGE_PIXEL DAL_PROXY640_IRIMAGE_PIXEL
#define IRIMAGE_RESOLUTION DAL_PROXY640_IRIMAGE_RESOLUTION
#define IRIMAGE_PIXEL_MAX DAL_PROXY640_IRIMAGE_PIXEL_MAX
#define IRIMAGE_NBPIXELS DAL_PROXY640_IRIMAGE_NBPIXELS
#define IRIMAGE_PAYLOAD DAL_PROXY640_IRIMAGE_PAYLOAD
#define IRIMAGE_META_COUNT DAL_PROXY640_IRIMAGE_META_COUNT
#define IRIMAGE_META_TEMP DAL_PROXY640_IRIMAGE_META_TEMP
#define IRIMAGE_META_PERIOD DAL_PROXY640_IRIMAGE_META_PERIOD
#define IRIMAGE_META_COUNTER DAL_PROXY640_IRIMAGE_META_COUNTER
#define IRIMAGE_EPOCH DAL_PROXY640_IRIMAGE_EPOCH
#define IRIMAGE_EPOCHLow DAL_PROXY640_IRIMAGE_EPOCHLow
#define IRIMAGE_FRAMEINFO DAL_PROXY640_IRIMAGE_FRAMEINFO
#define IRIMAGE_FRAMEAGE DAL_PROXY640_IRIMAGE_FRAMEAGE
#define IRIMAGE_FRAMEHISTO DAL_PROXY640_IRIMAGE_FRAMEHISTO
#define IRIMAGE_ENDFRAMEHISTO DAL_PROXY640_IRIMAGE_ENDFRAMEHISTO
#define SLOT_EMPTY DAL_PROXY640_SLOT_EMPTY
#define SLOT_TYPE_GAIN DAL_PROXY640_SLOT_TYPE_GAIN
#define SLOT_TYPE_OFFSET DAL_PROXY640_SLOT_TYPE_OFFSET
#define NUC_SLOT_COUNT DAL_PROXY640_NUC_SLOT_COUNT
#define NUC_BANK_COUNT DAL_PROXY640_NUC_BANK_COUNT
#define NUC_INFO_USER_SIZE DAL_PROXY640_NUC_INFO_USER_SIZE
#define BANK_SETTINGS_COUNT DAL_PROXY640_BANK_SETTINGS_COUNT
#define BADPIXELS_COUNT DAL_PROXY640_BADPIXELS_COUNT
#define PIXEL_IGNORED DAL_PROXY640_PIXEL_IGNORED
#define PIXEL_ORIGINAL DAL_PROXY640_PIXEL_ORIGINAL
#define PIXEL_FIXED DAL_PROXY640_PIXEL_FIXED
#define FEATURE_STRING_SIZE DAL_PROXY640_FEATURE_STRING_SIZE

#elif IRLUGX1M3

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

#endif




#endif // DALPROXYSWITCHUSBDEF_H
