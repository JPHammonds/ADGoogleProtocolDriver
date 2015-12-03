#!/bin/tcsh
setenv EPICS_DISPLAY_PATH ../../../../LambdaApp/op/adl:../../../../../ADCore-R2-2/ADApp/op/adl:../../../../../../asyn-4-26/opi/medm

medm -x -macro "P=13LAMBDA1:,R=cam1:" LambdaBase.adl

