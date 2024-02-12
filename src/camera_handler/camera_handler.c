#include "camera_handler.h"

#include <stdbool.h>
#include <stdint.h>

#include "DALProxy1280_12USB.h"
#include "DALProxy1280_12USBDef.h"
#include "DALProxySwitchUSBDef.h"


uint16_t paImage[IRIMAGE_NBPIXELS*2];

int cam_self_test(void)
{
    return 1;
}
