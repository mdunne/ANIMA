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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Sampler.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Sampler.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=C:/Users/mdunne/Documents/ANIMA/code/Small_scale/Sampler.X/sampler_test.c ../118_Libraries/src/BOARD.c ../118_Libraries/src/serial.c ../118_Libraries/src/timers.c Sampler.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/91374146/sampler_test.o ${OBJECTDIR}/_ext/1436657880/BOARD.o ${OBJECTDIR}/_ext/1436657880/serial.o ${OBJECTDIR}/_ext/1436657880/timers.o ${OBJECTDIR}/Sampler.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/91374146/sampler_test.o.d ${OBJECTDIR}/_ext/1436657880/BOARD.o.d ${OBJECTDIR}/_ext/1436657880/serial.o.d ${OBJECTDIR}/_ext/1436657880/timers.o.d ${OBJECTDIR}/Sampler.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/91374146/sampler_test.o ${OBJECTDIR}/_ext/1436657880/BOARD.o ${OBJECTDIR}/_ext/1436657880/serial.o ${OBJECTDIR}/_ext/1436657880/timers.o ${OBJECTDIR}/Sampler.o

# Source Files
SOURCEFILES=C:/Users/mdunne/Documents/ANIMA/code/Small_scale/Sampler.X/sampler_test.c ../118_Libraries/src/BOARD.c ../118_Libraries/src/serial.c ../118_Libraries/src/timers.c Sampler.c


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
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Sampler.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

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
${OBJECTDIR}/_ext/91374146/sampler_test.o: C:/Users/mdunne/Documents/ANIMA/code/Small_scale/Sampler.X/sampler_test.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/91374146 
	@${RM} ${OBJECTDIR}/_ext/91374146/sampler_test.o.d 
	@${RM} ${OBJECTDIR}/_ext/91374146/sampler_test.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/91374146/sampler_test.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../118_Libraries/include" -MMD -MF "${OBJECTDIR}/_ext/91374146/sampler_test.o.d" -o ${OBJECTDIR}/_ext/91374146/sampler_test.o C:/Users/mdunne/Documents/ANIMA/code/Small_scale/Sampler.X/sampler_test.c   
	
${OBJECTDIR}/_ext/1436657880/BOARD.o: ../118_Libraries/src/BOARD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1436657880 
	@${RM} ${OBJECTDIR}/_ext/1436657880/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1436657880/BOARD.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1436657880/BOARD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../118_Libraries/include" -MMD -MF "${OBJECTDIR}/_ext/1436657880/BOARD.o.d" -o ${OBJECTDIR}/_ext/1436657880/BOARD.o ../118_Libraries/src/BOARD.c   
	
${OBJECTDIR}/_ext/1436657880/serial.o: ../118_Libraries/src/serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1436657880 
	@${RM} ${OBJECTDIR}/_ext/1436657880/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/1436657880/serial.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1436657880/serial.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../118_Libraries/include" -MMD -MF "${OBJECTDIR}/_ext/1436657880/serial.o.d" -o ${OBJECTDIR}/_ext/1436657880/serial.o ../118_Libraries/src/serial.c   
	
${OBJECTDIR}/_ext/1436657880/timers.o: ../118_Libraries/src/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1436657880 
	@${RM} ${OBJECTDIR}/_ext/1436657880/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1436657880/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1436657880/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../118_Libraries/include" -MMD -MF "${OBJECTDIR}/_ext/1436657880/timers.o.d" -o ${OBJECTDIR}/_ext/1436657880/timers.o ../118_Libraries/src/timers.c   
	
${OBJECTDIR}/Sampler.o: Sampler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Sampler.o.d 
	@${RM} ${OBJECTDIR}/Sampler.o 
	@${FIXDEPS} "${OBJECTDIR}/Sampler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../118_Libraries/include" -MMD -MF "${OBJECTDIR}/Sampler.o.d" -o ${OBJECTDIR}/Sampler.o Sampler.c   
	
else
${OBJECTDIR}/_ext/91374146/sampler_test.o: C:/Users/mdunne/Documents/ANIMA/code/Small_scale/Sampler.X/sampler_test.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/91374146 
	@${RM} ${OBJECTDIR}/_ext/91374146/sampler_test.o.d 
	@${RM} ${OBJECTDIR}/_ext/91374146/sampler_test.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/91374146/sampler_test.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../118_Libraries/include" -MMD -MF "${OBJECTDIR}/_ext/91374146/sampler_test.o.d" -o ${OBJECTDIR}/_ext/91374146/sampler_test.o C:/Users/mdunne/Documents/ANIMA/code/Small_scale/Sampler.X/sampler_test.c   
	
${OBJECTDIR}/_ext/1436657880/BOARD.o: ../118_Libraries/src/BOARD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1436657880 
	@${RM} ${OBJECTDIR}/_ext/1436657880/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1436657880/BOARD.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1436657880/BOARD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../118_Libraries/include" -MMD -MF "${OBJECTDIR}/_ext/1436657880/BOARD.o.d" -o ${OBJECTDIR}/_ext/1436657880/BOARD.o ../118_Libraries/src/BOARD.c   
	
${OBJECTDIR}/_ext/1436657880/serial.o: ../118_Libraries/src/serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1436657880 
	@${RM} ${OBJECTDIR}/_ext/1436657880/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/1436657880/serial.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1436657880/serial.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../118_Libraries/include" -MMD -MF "${OBJECTDIR}/_ext/1436657880/serial.o.d" -o ${OBJECTDIR}/_ext/1436657880/serial.o ../118_Libraries/src/serial.c   
	
${OBJECTDIR}/_ext/1436657880/timers.o: ../118_Libraries/src/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1436657880 
	@${RM} ${OBJECTDIR}/_ext/1436657880/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1436657880/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1436657880/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../118_Libraries/include" -MMD -MF "${OBJECTDIR}/_ext/1436657880/timers.o.d" -o ${OBJECTDIR}/_ext/1436657880/timers.o ../118_Libraries/src/timers.c   
	
${OBJECTDIR}/Sampler.o: Sampler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Sampler.o.d 
	@${RM} ${OBJECTDIR}/Sampler.o 
	@${FIXDEPS} "${OBJECTDIR}/Sampler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../118_Libraries/include" -MMD -MF "${OBJECTDIR}/Sampler.o.d" -o ${OBJECTDIR}/Sampler.o Sampler.c   
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Sampler.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Sampler.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/Sampler.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Sampler.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/Sampler.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
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