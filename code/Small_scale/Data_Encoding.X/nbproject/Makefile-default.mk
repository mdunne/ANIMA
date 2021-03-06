#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Data_Encoding.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Data_Encoding.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=Data_Encoding_Test.c ../118_Libraries/src/BOARD.c ../118_Libraries/src/serial.c ../118_Libraries/src/timers.c DataEncoding.c ../Data_Logging.X/Data_Logging.c ../Data_Logging.X/FSIO.c ../Data_Logging.X/SD-SPI.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/Data_Encoding_Test.o ${OBJECTDIR}/_ext/1436657880/BOARD.o ${OBJECTDIR}/_ext/1436657880/serial.o ${OBJECTDIR}/_ext/1436657880/timers.o ${OBJECTDIR}/DataEncoding.o ${OBJECTDIR}/_ext/2142338205/Data_Logging.o ${OBJECTDIR}/_ext/2142338205/FSIO.o ${OBJECTDIR}/_ext/2142338205/SD-SPI.o
POSSIBLE_DEPFILES=${OBJECTDIR}/Data_Encoding_Test.o.d ${OBJECTDIR}/_ext/1436657880/BOARD.o.d ${OBJECTDIR}/_ext/1436657880/serial.o.d ${OBJECTDIR}/_ext/1436657880/timers.o.d ${OBJECTDIR}/DataEncoding.o.d ${OBJECTDIR}/_ext/2142338205/Data_Logging.o.d ${OBJECTDIR}/_ext/2142338205/FSIO.o.d ${OBJECTDIR}/_ext/2142338205/SD-SPI.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/Data_Encoding_Test.o ${OBJECTDIR}/_ext/1436657880/BOARD.o ${OBJECTDIR}/_ext/1436657880/serial.o ${OBJECTDIR}/_ext/1436657880/timers.o ${OBJECTDIR}/DataEncoding.o ${OBJECTDIR}/_ext/2142338205/Data_Logging.o ${OBJECTDIR}/_ext/2142338205/FSIO.o ${OBJECTDIR}/_ext/2142338205/SD-SPI.o

# Source Files
SOURCEFILES=Data_Encoding_Test.c ../118_Libraries/src/BOARD.c ../118_Libraries/src/serial.c ../118_Libraries/src/timers.c DataEncoding.c ../Data_Logging.X/Data_Logging.c ../Data_Logging.X/FSIO.c ../Data_Logging.X/SD-SPI.c


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
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Data_Encoding.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX250F128D
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
${OBJECTDIR}/Data_Encoding_Test.o: Data_Encoding_Test.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Data_Encoding_Test.o.d 
	@${RM} ${OBJECTDIR}/Data_Encoding_Test.o 
	@${FIXDEPS} "${OBJECTDIR}/Data_Encoding_Test.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DDATAENCODING_TEST -I"../118_Libraries/include" -I"../Data_Logging.X" -MMD -MF "${OBJECTDIR}/Data_Encoding_Test.o.d" -o ${OBJECTDIR}/Data_Encoding_Test.o Data_Encoding_Test.c   
	
${OBJECTDIR}/_ext/1436657880/BOARD.o: ../118_Libraries/src/BOARD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1436657880 
	@${RM} ${OBJECTDIR}/_ext/1436657880/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1436657880/BOARD.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1436657880/BOARD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DDATAENCODING_TEST -I"../118_Libraries/include" -I"../Data_Logging.X" -MMD -MF "${OBJECTDIR}/_ext/1436657880/BOARD.o.d" -o ${OBJECTDIR}/_ext/1436657880/BOARD.o ../118_Libraries/src/BOARD.c   
	
${OBJECTDIR}/_ext/1436657880/serial.o: ../118_Libraries/src/serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1436657880 
	@${RM} ${OBJECTDIR}/_ext/1436657880/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/1436657880/serial.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1436657880/serial.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DDATAENCODING_TEST -I"../118_Libraries/include" -I"../Data_Logging.X" -MMD -MF "${OBJECTDIR}/_ext/1436657880/serial.o.d" -o ${OBJECTDIR}/_ext/1436657880/serial.o ../118_Libraries/src/serial.c   
	
${OBJECTDIR}/_ext/1436657880/timers.o: ../118_Libraries/src/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1436657880 
	@${RM} ${OBJECTDIR}/_ext/1436657880/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1436657880/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1436657880/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DDATAENCODING_TEST -I"../118_Libraries/include" -I"../Data_Logging.X" -MMD -MF "${OBJECTDIR}/_ext/1436657880/timers.o.d" -o ${OBJECTDIR}/_ext/1436657880/timers.o ../118_Libraries/src/timers.c   
	
${OBJECTDIR}/DataEncoding.o: DataEncoding.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/DataEncoding.o.d 
	@${RM} ${OBJECTDIR}/DataEncoding.o 
	@${FIXDEPS} "${OBJECTDIR}/DataEncoding.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DDATAENCODING_TEST -I"../118_Libraries/include" -I"../Data_Logging.X" -MMD -MF "${OBJECTDIR}/DataEncoding.o.d" -o ${OBJECTDIR}/DataEncoding.o DataEncoding.c   
	
${OBJECTDIR}/_ext/2142338205/Data_Logging.o: ../Data_Logging.X/Data_Logging.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2142338205 
	@${RM} ${OBJECTDIR}/_ext/2142338205/Data_Logging.o.d 
	@${RM} ${OBJECTDIR}/_ext/2142338205/Data_Logging.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2142338205/Data_Logging.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DDATAENCODING_TEST -I"../118_Libraries/include" -I"../Data_Logging.X" -MMD -MF "${OBJECTDIR}/_ext/2142338205/Data_Logging.o.d" -o ${OBJECTDIR}/_ext/2142338205/Data_Logging.o ../Data_Logging.X/Data_Logging.c   
	
${OBJECTDIR}/_ext/2142338205/FSIO.o: ../Data_Logging.X/FSIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2142338205 
	@${RM} ${OBJECTDIR}/_ext/2142338205/FSIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/2142338205/FSIO.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2142338205/FSIO.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DDATAENCODING_TEST -I"../118_Libraries/include" -I"../Data_Logging.X" -MMD -MF "${OBJECTDIR}/_ext/2142338205/FSIO.o.d" -o ${OBJECTDIR}/_ext/2142338205/FSIO.o ../Data_Logging.X/FSIO.c   
	
${OBJECTDIR}/_ext/2142338205/SD-SPI.o: ../Data_Logging.X/SD-SPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2142338205 
	@${RM} ${OBJECTDIR}/_ext/2142338205/SD-SPI.o.d 
	@${RM} ${OBJECTDIR}/_ext/2142338205/SD-SPI.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2142338205/SD-SPI.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DDATAENCODING_TEST -I"../118_Libraries/include" -I"../Data_Logging.X" -MMD -MF "${OBJECTDIR}/_ext/2142338205/SD-SPI.o.d" -o ${OBJECTDIR}/_ext/2142338205/SD-SPI.o ../Data_Logging.X/SD-SPI.c   
	
else
${OBJECTDIR}/Data_Encoding_Test.o: Data_Encoding_Test.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Data_Encoding_Test.o.d 
	@${RM} ${OBJECTDIR}/Data_Encoding_Test.o 
	@${FIXDEPS} "${OBJECTDIR}/Data_Encoding_Test.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DDATAENCODING_TEST -I"../118_Libraries/include" -I"../Data_Logging.X" -MMD -MF "${OBJECTDIR}/Data_Encoding_Test.o.d" -o ${OBJECTDIR}/Data_Encoding_Test.o Data_Encoding_Test.c   
	
${OBJECTDIR}/_ext/1436657880/BOARD.o: ../118_Libraries/src/BOARD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1436657880 
	@${RM} ${OBJECTDIR}/_ext/1436657880/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1436657880/BOARD.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1436657880/BOARD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DDATAENCODING_TEST -I"../118_Libraries/include" -I"../Data_Logging.X" -MMD -MF "${OBJECTDIR}/_ext/1436657880/BOARD.o.d" -o ${OBJECTDIR}/_ext/1436657880/BOARD.o ../118_Libraries/src/BOARD.c   
	
${OBJECTDIR}/_ext/1436657880/serial.o: ../118_Libraries/src/serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1436657880 
	@${RM} ${OBJECTDIR}/_ext/1436657880/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/1436657880/serial.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1436657880/serial.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DDATAENCODING_TEST -I"../118_Libraries/include" -I"../Data_Logging.X" -MMD -MF "${OBJECTDIR}/_ext/1436657880/serial.o.d" -o ${OBJECTDIR}/_ext/1436657880/serial.o ../118_Libraries/src/serial.c   
	
${OBJECTDIR}/_ext/1436657880/timers.o: ../118_Libraries/src/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1436657880 
	@${RM} ${OBJECTDIR}/_ext/1436657880/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1436657880/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1436657880/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DDATAENCODING_TEST -I"../118_Libraries/include" -I"../Data_Logging.X" -MMD -MF "${OBJECTDIR}/_ext/1436657880/timers.o.d" -o ${OBJECTDIR}/_ext/1436657880/timers.o ../118_Libraries/src/timers.c   
	
${OBJECTDIR}/DataEncoding.o: DataEncoding.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/DataEncoding.o.d 
	@${RM} ${OBJECTDIR}/DataEncoding.o 
	@${FIXDEPS} "${OBJECTDIR}/DataEncoding.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DDATAENCODING_TEST -I"../118_Libraries/include" -I"../Data_Logging.X" -MMD -MF "${OBJECTDIR}/DataEncoding.o.d" -o ${OBJECTDIR}/DataEncoding.o DataEncoding.c   
	
${OBJECTDIR}/_ext/2142338205/Data_Logging.o: ../Data_Logging.X/Data_Logging.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2142338205 
	@${RM} ${OBJECTDIR}/_ext/2142338205/Data_Logging.o.d 
	@${RM} ${OBJECTDIR}/_ext/2142338205/Data_Logging.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2142338205/Data_Logging.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DDATAENCODING_TEST -I"../118_Libraries/include" -I"../Data_Logging.X" -MMD -MF "${OBJECTDIR}/_ext/2142338205/Data_Logging.o.d" -o ${OBJECTDIR}/_ext/2142338205/Data_Logging.o ../Data_Logging.X/Data_Logging.c   
	
${OBJECTDIR}/_ext/2142338205/FSIO.o: ../Data_Logging.X/FSIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2142338205 
	@${RM} ${OBJECTDIR}/_ext/2142338205/FSIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/2142338205/FSIO.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2142338205/FSIO.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DDATAENCODING_TEST -I"../118_Libraries/include" -I"../Data_Logging.X" -MMD -MF "${OBJECTDIR}/_ext/2142338205/FSIO.o.d" -o ${OBJECTDIR}/_ext/2142338205/FSIO.o ../Data_Logging.X/FSIO.c   
	
${OBJECTDIR}/_ext/2142338205/SD-SPI.o: ../Data_Logging.X/SD-SPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2142338205 
	@${RM} ${OBJECTDIR}/_ext/2142338205/SD-SPI.o.d 
	@${RM} ${OBJECTDIR}/_ext/2142338205/SD-SPI.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2142338205/SD-SPI.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DDATAENCODING_TEST -I"../118_Libraries/include" -I"../Data_Logging.X" -MMD -MF "${OBJECTDIR}/_ext/2142338205/SD-SPI.o.d" -o ${OBJECTDIR}/_ext/2142338205/SD-SPI.o ../Data_Logging.X/SD-SPI.c   
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Data_Encoding.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Data_Encoding.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/Data_Encoding.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Data_Encoding.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/Data_Encoding.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
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
