/* Copyright 2023 Dual Tachyon
 * https://github.com/DualTachyon
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 *     Unless required by applicable law or agreed to in writing, software
 *     distributed under the License is distributed on an "AS IS" BASIS,
 *     WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *     See the License for the specific language governing permissions and
 *     limitations under the License.
 */

#include <stddef.h>
#include <string.h>
#include "bitmaps.h"
#include "driver/st7565.h"
#include "functions.h"
#include "ui/battery.h"
#include "external/printf/printf.h"
#include "helper.h"
#include "helper/battery.h"

void UI_DisplayBattery(uint8_t Level)
{
#if defined(ENABLE_BATT_MODS)
    char String[16];
    sprintf(String, "%d.%02d", gBatteryVoltageAverage / 100, gBatteryVoltageAverage % 100);
    UI_PrintStringSmall(String, 96, 127, -1, 8, true);

#else
    const uint8_t *pBitmap;
    bool bClearMode = false;

    if (gCurrentFunction != 1) {
        switch (Level) {
        case 0:
            pBitmap = NULL;
            bClearMode = true;
            break;
        case 1:
            pBitmap = BITMAP_BatteryLevel1;
            break;
        case 2:
            pBitmap = BITMAP_BatteryLevel2;
            break;
        case 3:
            pBitmap = BITMAP_BatteryLevel3;
            break;
        case 4:
            pBitmap = BITMAP_BatteryLevel4;
            break;
        default:
            pBitmap = BITMAP_BatteryLevel5;
            break;
        }
        if(bClearMode)
            memset(gStatusLine + 110, 0, sizeof(BITMAP_BatteryLevel1));
        else
            memcpy(gStatusLine + 110, pBitmap, sizeof(BITMAP_BatteryLevel1));
    }
#endif
}



