errlogInit(20000)

< envPaths
#epicsThreadSleep(20)
dbLoadDatabase("$(TOP)/dbd/GoogleProtocolDriverApp.dbd")
GoogleProtocolDriverApp_registerRecordDeviceDriver(pdbbase) 

# Prefix for all records
epicsEnvSet("PREFIX", "13GPDrv1:")
# The port name for the detector
epicsEnvSet("PORT",   "GPDRV1")
# The queue size for all plugins
epicsEnvSet("QSIZE",  "30")
# The maximim image width; used for row profiles in the NDPluginStats plugin
epicsEnvSet("XSIZE",  "2048")
# The maximim image height; used for column profiles in the NDPluginStats plugin
epicsEnvSet("YSIZE",  "2048")
# The maximum number of time seried points in the NDPluginStats plugin
epicsEnvSet("NCHANS", "2048")
# The maximum number of frames buffered in the NDPluginCircularBuff plugin
epicsEnvSet("CBUFFS", "500")
# The search path for database files
epicsEnvSet("EPICS_DB_INCLUDE_PATH", "$(ADCORE)/db")

# Create a PICam driver
# LambdaConfig(const char *portName, const char * configPath, IDType, IDValue, maxBuffers, size_t maxMemory, int priority, int stackSize)

# This is for a 
GoogleProtocolDriverConfig("$(PORT)", "config",  0, 0, 0, 0)

asynSetTraceIOMask($(PORT), 0, 2)
#asynSetTraceMask($(PORT),0,0xff)

dbLoadRecords("$(ADCORE)/db/ADBase.template", "P=$(PREFIX),R=cam1:,PORT=$(PORT),ADDR=0,TIMEOUT=1")
#dbLoadRecords("$(ADLAMBDA)/db/ADLambda.template","P=$(PREFIX),R=cam1:,PORT=$(PORT),ADDR=0,TIMEOUT=1")

# Create a standard arrays plugin, set it to get data from Driver.
NDStdArraysConfigure("Image1", 3, 0, "$(PORT)", 0)
dbLoadRecords("$(ADCORE)/db/NDPluginBase.template","P=$(PREFIX),R=image1:,PORT=Image1,ADDR=0,TIMEOUT=1,NDARRAY_PORT=$(PORT),NDARRAY_ADDR=0")
dbLoadRecords("$(ADCORE)/db/NDStdArrays.template", "P=$(PREFIX),R=image1:,PORT=Image1,ADDR=0,TIMEOUT=1,TYPE=Int16,SIZE=16,FTVL=SHORT,NELEMENTS=20000000")

# Load all other plugins using commonPlugins.cmd
< $(ADCORE)/iocBoot/commonPlugins.cmd

NDAPSGoogleProtoConfigure("GoogleProto1", $(QSIZE), 0, "$(PORT)", 0, 0, 0)
dbLoadRecords("$(ADCORE)/db/NDAPSGoogleProto.template", "P=$(PREFIX),R=AGP1:,  PORT=GoogleProto1,ADDR=0,TIMEOUT=1,NDARRAY_PORT=$(PORT)")

set_requestfile_path("$(GOOGLEPROTOCOLDRIVER)/GoogleProtocolDriverApp/Db")

#asynSetTraceMask($(PORT),0,0x09)
#asynSetTraceMask($(PORT),0,0x11)
iocInit()

# save things every thirty seconds
create_monitor_set("auto_settings.req", 30, "P=$(PREFIX)")

