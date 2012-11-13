#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Data_Logging.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Data_Logging.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1436657880/serial.o ${OBJECTDIR}/Data_Logging.o ${OBJECTDIR}/_ext/1436657880/timers.o ${OBJECTDIR}/data_logging_test.o ${OBJECTDIR}/_ext/2141726714/LED.o ${OBJECTDIR}/FSIO.o ${OBJECTDIR}/SD-SPI.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1436657880/serial.o.d ${OBJECTDIR}/Data_Logging.o.d ${OBJECTDIR}/_ext/1436657880/timers.o.d ${OBJECTDIR}/data_logging_test.o.d ${OBJECTDIR}/_ext/2141726714/LED.o.d ${OBJECTDIR}/FSIO.o.d ${OBJECTDIR}/SD-SPI.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1436657880/serial.o ${OBJECTDIR}/Data_Logging.o ${OBJECTDIR}/_ext/1436657880/timers.o ${OBJECTDIR}/data_logging_test.o ${OBJECTDIR}/_ext/2141726714/LED.o ${OBJECTDIR}/FSIO.o ${OBJECTDIR}/SD-SPI.o


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Data_Logging.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX320F128H
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1436657880/serial.o: ../118_Libraries/src/serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1436657880 
	@${RM} ${OBJECTDIR}/_ext/1436657880/serial.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1436657880/serial.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../118_Libraries/include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Data_Logging.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/LED.X" -MMD -MF "${OBJECTDIR}/_ext/1436657880/serial.o.d" -o ${OBJECTDIR}/_ext/1436657880/serial.o ../118_Libraries/src/serial.c  
	
${OBJECTDIR}/Data_Logging.o: Data_Logging.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Data_Logging.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Data_Logging.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../118_Libraries/include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Data_Logging.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/LED.X" -MMD -MF "${OBJECTDIR}/Data_Logging.o.d" -o ${OBJECTDIR}/Data_Logging.o Data_Logging.c  
	
${OBJECTDIR}/_ext/1436657880/timers.o: ../118_Libraries/src/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1436657880 
	@${RM} ${OBJECTDIR}/_ext/1436657880/timers.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1436657880/timers.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../118_Libraries/include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Data_Logging.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/LED.X" -MMD -MF "${OBJECTDIR}/_ext/1436657880/timers.o.d" -o ${OBJECTDIR}/_ext/1436657880/timers.o ../118_Libraries/src/timers.c  
	
${OBJECTDIR}/data_logging_test.o: data_logging_test.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/data_logging_test.o.d 
	@${FIXDEPS} "${OBJECTDIR}/data_logging_test.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../118_Libraries/include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Data_Logging.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/LED.X" -MMD -MF "${OBJECTDIR}/data_logging_test.o.d" -o ${OBJECTDIR}/data_logging_test.o data_logging_test.c  
	
${OBJECTDIR}/_ext/2141726714/LED.o: ../LED.X/LED.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2141726714 
	@${RM} ${OBJECTDIR}/_ext/2141726714/LED.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2141726714/LED.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../118_Libraries/include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Data_Logging.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/LED.X" -MMD -MF "${OBJECTDIR}/_ext/2141726714/LED.o.d" -o ${OBJECTDIR}/_ext/2141726714/LED.o ../LED.X/LED.c  
	
${OBJECTDIR}/FSIO.o: FSIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/FSIO.o.d 
	@${FIXDEPS} "${OBJECTDIR}/FSIO.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../118_Libraries/include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Data_Logging.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/LED.X" -MMD -MF "${OBJECTDIR}/FSIO.o.d" -o ${OBJECTDIR}/FSIO.o FSIO.c  
	
${OBJECTDIR}/SD-SPI.o: SD-SPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/SD-SPI.o.d 
	@${FIXDEPS} "${OBJECTDIR}/SD-SPI.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../118_Libraries/include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Data_Logging.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/LED.X" -MMD -MF "${OBJECTDIR}/SD-SPI.o.d" -o ${OBJECTDIR}/SD-SPI.o SD-SPI.c  
	
else
${OBJECTDIR}/_ext/1436657880/serial.o: ../118_Libraries/src/serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1436657880 
	@${RM} ${OBJECTDIR}/_ext/1436657880/serial.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1436657880/serial.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../118_Libraries/include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Data_Logging.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/LED.X" -MMD -MF "${OBJECTDIR}/_ext/1436657880/serial.o.d" -o ${OBJECTDIR}/_ext/1436657880/serial.o ../118_Libraries/src/serial.c  
	
${OBJECTDIR}/Data_Logging.o: Data_Logging.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Data_Logging.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Data_Logging.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../118_Libraries/include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Data_Logging.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/LED.X" -MMD -MF "${OBJECTDIR}/Data_Logging.o.d" -o ${OBJECTDIR}/Data_Logging.o Data_Logging.c  
	
${OBJECTDIR}/_ext/1436657880/timers.o: ../118_Libraries/src/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1436657880 
	@${RM} ${OBJECTDIR}/_ext/1436657880/timers.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1436657880/timers.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../118_Libraries/include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Data_Logging.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/LED.X" -MMD -MF "${OBJECTDIR}/_ext/1436657880/timers.o.d" -o ${OBJECTDIR}/_ext/1436657880/timers.o ../118_Libraries/src/timers.c  
	
${OBJECTDIR}/data_logging_test.o: data_logging_test.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/data_logging_test.o.d 
	@${FIXDEPS} "${OBJECTDIR}/data_logging_test.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../118_Libraries/include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Data_Logging.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/LED.X" -MMD -MF "${OBJECTDIR}/data_logging_test.o.d" -o ${OBJECTDIR}/data_logging_test.o data_logging_test.c  
	
${OBJECTDIR}/_ext/2141726714/LED.o: ../LED.X/LED.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2141726714 
	@${RM} ${OBJECTDIR}/_ext/2141726714/LED.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2141726714/LED.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../118_Libraries/include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Data_Logging.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/LED.X" -MMD -MF "${OBJECTDIR}/_ext/2141726714/LED.o.d" -o ${OBJECTDIR}/_ext/2141726714/LED.o ../LED.X/LED.c  
	
${OBJECTDIR}/FSIO.o: FSIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/FSIO.o.d 
	@${FIXDEPS} "${OBJECTDIR}/FSIO.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../118_Libraries/include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Data_Logging.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/LED.X" -MMD -MF "${OBJECTDIR}/FSIO.o.d" -o ${OBJECTDIR}/FSIO.o FSIO.c  
	
${OBJECTDIR}/SD-SPI.o: SD-SPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/SD-SPI.o.d 
	@${FIXDEPS} "${OBJECTDIR}/SD-SPI.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../118_Libraries/include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Data_Logging.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/LED.X" -MMD -MF "${OBJECTDIR}/SD-SPI.o.d" -o ${OBJECTDIR}/SD-SPI.o SD-SPI.c  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Data_Logging.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Data_Logging.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}       -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__ICD2RAM=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1
else
dist/${CND_CONF}/${IMAGE_TYPE}/Data_Logging.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Data_Logging.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}       -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION)
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/Data_Logging.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
