/**
 Copyright (c) 2015, UChicago Argonne, LLC
 See LICENSE file.
 */
/* ADGoogleProtocol.h
 *
 * This is an areaDetector Google Protocol Files.  This driver loads files written by Googlei
 * Protocol plugin and moves them into NDArrays.
 *
 */
#ifndef AD_GOOGLE_PROTOCOL_DRIVER_H
#define AD_GOOGLE_PROTOCOL_DRIVER_H

#include <epicsString.h>
#include <epicsEvent.h>
#include <epicsThread.h>

#include <APSdet_GPB.pb.h>
#include "ADDriver.h"

class epicsShareClass ADGoogleProtocolDriver: public ADDriver {
public:
    static const char *driverName;

    ADGoogleProtocolDriver(const char *portName, const char *configPath, int maxBuffers,
            size_t maxMemory, int priority, int stackSize);
    ~ADGoogleProtocolDriver();
protected:
    // int reference to parameters
    int GP_DRIVER_VersionNumber;
#define GP_DRIVER_FIRST_PARAM GP_DRIVER_VersionNumber
    int GP_DRIVER_OperatingMode;
#define GP_DRIVER_LAST_PARAM GP_DRIVER_OperatingMode


private:
   APSdet_GPB::AGP message;

};

#define NUM_GP_DRIVER_PARAMS ((int)(&GP_DRIVER_LAST_PARAM - &GP_DRIVER_FIRST_PARAM + 1))

#endif
