TOP=../..
include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE

ifeq (windows-x64, $(findstring windows-x64, $(T_A)))
USR_CPPFLAGS += -D__X64
endif

LIBRARY_IOC = ADGoogleProtocolDriver
LIB_SRCS += ADGoogleProtocolDriver.cpp
#LIB_LIBS += lambda

DBD += GoogleProtocolDriverSupport.dbd

include $(ADCORE)/ADApp/commonLibraryMakefile
USR_INCLUDES          += -I$(AREA_DETECTOR)/ADPluginAPSGoogleProto/APSgoogleProtoApp/APSgoogleProtoSrc
USR_INCLUDES += -I$(AREA_DETECTOR)/ADPluginAPSGoogleProto/APSgoogleProtoSupport/GoogleProtoBuf/os/linux-x86_64/include
ifdef ADPLUGINAPSGOOGLEPROTO
  PROD_LIBS             += NDPluginAPSGoogleProto
  $(PROD_NAME)_DBD      += NDPluginAPSGoogleProto.dbd
  GoogleProto_DIR       +=$(GOOGLEPROTO_LIB)
  PROD_LDFLAGS          +=-L$(GOOGLEPROTO_LIB)
  PROD_LIBS             += protobuf
  PROD_LIBS             += protoc
  PROD_LIBS             += protobuf-lite
endif

#=============================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

