/**
 Copyright (c) 2015, UChicago Argonne, LLC
 See LICENSE file.
 */
/* ADLambda.cpp */
#include <iocsh.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <epicsTime.h>
#include <epicsExit.h>
#include <epicsExport.h>

#include <APSdet_GPB.pb.h>
#include "ADGoogleProtocolDriver.h"

extern "C" {
/** Configuration command for PICAM driver; creates a new PICam object.
 * \param[in] portName The name of the asyn port driver to be created.
 * \param[in] path to the config files.
 * \param[in] maxBuffers The maximum number of NDArray buffers that the
 *            NDArrayPool for this driver is
 *            allowed to allocate. Set this to -1 to allow an unlimited number
 *            of buffers.
 * \param[in] maxMemory The maximum amount of memory that the NDArrayPool for
 *            this driver is allowed to allocate. Set this to -1 to allow an
 *            unlimited amount of memory.
 * \param[in] priority The thread priority for the asyn port driver thread if
 *            ASYN_CANBLOCK is set in asynFlags.
 * \param[in] stackSize The stack size for the asyn port driver thread if
 *            ASYN_CANBLOCK is set in asynFlags.
 */
int GoogleProtocolDriverConfig(const char *portName, const char* configPath, int maxBuffers,
        size_t maxMemory, int priority, int stackSize) {
    new ADGoogleProtocolDriver(portName, configPath, maxBuffers, maxMemory, priority,
                             stackSize);
    return (asynSuccess);
}

/**
 * Callback function for exit hook
 */
static void exitCallbackC(void *pPvt) {
    ADGoogleProtocolDriver *pADGPDriver = (ADGoogleProtocolDriver*) pPvt;
    delete pADGPDriver;
}

}

/**
 * Constructor
 *  * \param[in] portName The name of the asyn port driver to be created.
 * \param[in] maxBuffers The maximum number of NDArray buffers that the
 *            NDArrayPool for this driver is
 *            allowed to allocate. Set this to -1 to allow an unlimited number
 *            of buffers.
 * \param[in] maxMemory The maximum amount of memory that the NDArrayPool for
 *            this driver is allowed to allocate. Set this to -1 to allow an
 *            unlimited amount of memory.
 * \param[in] priority The thread priority for the asyn port driver thread if
 *            ASYN_CANBLOCK is set in asynFlags.
 * \param[in] stackSize The stack size for the asyn port driver thread if
 *            ASYN_CANBLOCK is set in asynFlags.
 *
 */
ADGoogleProtocolDriver::ADGoogleProtocolDriver(const char *portName, const char *configPath,
        int maxBuffers, size_t maxMemory, int priority, int stackSize) :
        ADDriver(portName, 1, int(NUM_GP_DRIVER_PARAMS), maxBuffers, maxMemory,
                asynEnumMask, asynEnumMask, ASYN_CANBLOCK, 1, priority,
                stackSize) {
    std::fstream input("/local/data/test_0000.gp", std::ios::in | std::ios::binary);
    message.ParseFromIstream(&input);

    int nDims = message.numdimdata();
    std::string dimStr = message.dimdata();
    APSdet_GPB::AGP_ArrayDataType arrayDataType = message.datatype();
    std::string valuesData = message.valuesdata();
    int numAttrs = message.numattrs();
    std::string nameAttrs = message.nameattrs();
    
    std::cout << "nDims: " << nDims << std::endl;
    std::cout << "dimStr: " << dimStr << std::endl;
    std::cout << "arrayDataType: " << arrayDataType << std::endl;
    std::cout << "numAttrs: " << numAttrs << std::endl;
    std::cout << "nameAttrs: " << nameAttrs << std::endl;
    std::cout << "valuesData: " << valuesData << std::endl;
}

/**
 * Destructor
 */
ADGoogleProtocolDriver::~ADGoogleProtocolDriver() {

}

/* Code for iocsh registration */

/* GooglProtocolConfig */
static const iocshArg GPDriverConfigArg0 = { "Port name", iocshArgString };
static const iocshArg GPDriverConfigArg1 = { "Config file path", iocshArgString };
static const iocshArg GPDriverConfigArg2 = { "maxBuffers", iocshArgInt };
static const iocshArg GPDriverConfigArg3 = { "maxMemory", iocshArgInt };
static const iocshArg GPDriverConfigArg4 = { "priority", iocshArgInt };
static const iocshArg GPDriverConfigArg5 = { "stackSize", iocshArgInt };
static const iocshArg * const GPDriverConfigArgs[] = { &GPDriverConfigArg0,
        &GPDriverConfigArg1, &GPDriverConfigArg2, &GPDriverConfigArg3,
        &GPDriverConfigArg4, &GPDriverConfigArg5 };

static void configGPDriverCallFunc(const iocshArgBuf *args) {
    GoogleProtocolDriverConfig(args[0].sval, args[1].sval, args[2].ival, args[3].ival,
            args[4].ival, args[5].ival);
}
static const iocshFuncDef configGPDriver = { "GoogleProtocolDriverConfig", 6, GPDriverConfigArgs };

static void GoogleProtocolDriverRegister(void) {
    iocshRegister(&configGPDriver, configGPDriverCallFunc);
}

extern "C" {
epicsExportRegistrar(GoogleProtocolDriverRegister);
}
