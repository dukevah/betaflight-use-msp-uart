/*
 * This file is part of Cleanflight.
 *
 * Cleanflight is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Cleanflight is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Cleanflight.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "platform.h"

#include "build/build_config.h"

#include "drivers/system.h"
#include "drivers/io.h"
#include "drivers/exti.h"
#include "hardware_revision.h"

static const char * const hardwareRevisionNames[] = {
        "Unknown",
        "AlienFlight V1",
        "AlienFlight V2"
};

uint8_t hardwareRevision = UNKNOWN;

static IO_t HWDetectPin = IO_NONE;

void detectHardwareRevision(void)
{
    HWDetectPin = IOGetByTag(IO_TAG(HW_PIN));
    IOInit(HWDetectPin, OWNER_SYSTEM, 0);
    IOConfigGPIO(HWDetectPin, IOCFG_IPU);

    // Check hardware revision
    delayMicroseconds(10);  // allow configuration to settle

    if (IORead(HWDetectPin)) {
        hardwareRevision = AFF4_REV_1;
    } else {
        hardwareRevision = AFF4_REV_2;
    }
}

void updateHardwareRevision(void)
{
}
