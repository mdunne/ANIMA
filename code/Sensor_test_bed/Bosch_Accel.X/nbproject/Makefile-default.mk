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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Bosch_Accel.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Bosch_Accel.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1436657880/serial.o ${OBJECTDIR}/bosch_accel.o ${OBJECTDIR}/bosch_accel_test.o ${OBJECTDIR}/_ext/1602749850/I2C_Driver.o ${OBJECTDIR}/_ext/1436657880/timers.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1436657880/serial.o.d ${OBJECTDIR}/bosch_accel.o.d ${OBJECTDIR}/bosch_accel_test.o.d ${OBJECTDIR}/_ext/1602749850/I2C_Driver.o.d ${OBJECTDIR}/_ext/1436657880/timers.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1436657880/serial.o ${OBJECTDIR}/bosch_accel.o ${OBJECTDIR}/bosch_accel_test.o ${OBJECTDIR}/_ext/1602749850/I2C_Driver.o ${OBJECTDIR}/_ext/1436657880/timers.o


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
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Bosch_Accel.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX320F128H
MP_LINKER_FILE_OPTION=,--script="..\boot_loader\elf32pic32mx_v2_ds30_app.ld"
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
	@${FIXDEPS} "${OBJECTDIR}/_ext/1436657880/serial.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../I2C_Driver.X" -I"../118_Libraries/include" -I"../LED.X" -MMD -MF "${OBJECTDIR}/_ext/1436657880/serial.o.d" -o ${OBJECTDIR}/_ext/1436657880/serial.o ../118_Libraries/src/serial.c  
	
${OBJECTDIR}/bosch_accel.o: bosch_accel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/bosch_accel.o.d 
	@${FIXDEPS} "${OBJECTDIR}/bosch_accel.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../I2C_Driver.X" -I"../118_Libraries/include" -I"../LED.X" -MMD -MF "${OBJECTDIR}/bosch_accel.o.d" -o ${OBJECTDIR}/bosch_accel.o bosch_accel.c  
	
${OBJECTDIR}/bosch_accel_test.o: bosch_accel_test.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/bosch_accel_test.o.d 
	@${FIXDEPS} "${OBJECTDIR}/bosch_accel_test.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../I2C_Driver.X" -I"../118_Libraries/include" -I"../LED.X" -MMD -MF "${OBJECTDIR}/bosch_accel_test.o.d" -o ${OBJECTDIR}/bosch_accel_test.o bosch_accel_test.c  
	
${OBJECTDIR}/_ext/1602749850/I2C_Driver.o: ../I2C_Driver.X/I2C_Driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1602749850 
	@${RM} ${OBJECTDIR}/_ext/1602749850/I2C_Driver.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1602749850/I2C_Driver.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../I2C_Driver.X" -I"../118_Libraries/include" -I"../LED.X" -MMD -MF "${OBJECTDIR}/_ext/1602749850/I2C_Driver.o.d" -o ${OBJECTDIR}/_ext/1602749850/I2C_Driver.o ../I2C_Driver.X/I2C_Driver.c  
	
${OBJECTDIR}/_ext/1436657880/timers.o: ../118_Libraries/src/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1436657880 
	@${RM} ${OBJECTDIR}/_ext/1436657880/timers.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1436657880/timers.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../I2C_Driver.X" -I"../118_Libraries/include" -I"../LED.X" -MMD -MF "${OBJECTDIR}/_ext/1436657880/timers.o.d" -o ${OBJECTDIR}/_ext/1436657880/timers.o ../118_Libraries/src/timers.c  
	
else
${OBJECTDIR}/_ext/1436657880/serial.o: ../118_Libraries/src/serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1436657880 
	@${RM} ${OBJECTDIR}/_ext/1436657880/serial.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1436657880/serial.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../I2C_Driver.X" -I"../118_Libraries/include" -I"../LED.X" -MMD -MF "${OBJECTDIR}/_ext/1436657880/serial.o.d" -o ${OBJECTDIR}/_ext/1436657880/serial.o ../118_Libraries/src/serial.c  
	
${OBJECTDIR}/bosch_accel.o: bosch_accel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/bosch_accel.o.d 
	@${FIXDEPS} "${OBJECTDIR}/bosch_accel.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../I2C_Driver.X" -I"../118_Libraries/include" -I"../LED.X" -MMD -MF "${OBJECTDIR}/bosch_accel.o.d" -o ${OBJECTDIR}/bosch_accel.o bosch_accel.c  
	
${OBJECTDIR}/bosch_accel_test.o: bosch_accel_test.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/bosch_accel_test.o.d 
	@${FIXDEPS} "${OBJECTDIR}/bosch_accel_test.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../I2C_Driver.X" -I"../118_Libraries/include" -I"../LED.X" -MMD -MF "${OBJECTDIR}/bosch_accel_test.o.d" -o ${OBJECTDIR}/bosch_accel_test.o bosch_accel_test.c  
	
${OBJECTDIR}/_ext/1602749850/I2C_Driver.o: ../I2C_Driver.X/I2C_Driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1602749850 
	@${RM} ${OBJECTDIR}/_ext/1602749850/I2C_Driver.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1602749850/I2C_Driver.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../I2C_Driver.X" -I"../118_Libraries/include" -I"../LED.X" -MMD -MF "${OBJECTDIR}/_ext/1602749850/I2C_Driver.o.d" -o ${OBJECTDIR}/_ext/1602749850/I2C_Driver.o ../I2C_Driver.X/I2C_Driver.c  
	
${OBJECTDIR}/_ext/1436657880/timers.o: ../118_Libraries/src/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1436657880 
	@${RM} ${OBJECTDIR}/_ext/1436657880/timers.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1436657880/timers.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../I2C_Driver.X" -I"../118_Libraries/include" -I"../LED.X" -MMD -MF "${OBJECTDIR}/_ext/1436657880/timers.o.d" -o ${OBJECTDIR}/_ext/1436657880/timers.o ../118_Libraries/src/timers.c  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Bosch_Accel.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Bosch_Accel.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}       -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__ICD2RAM=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1 
else
dist/${CND_CONF}/${IMAGE_TYPE}/Bosch_Accel.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Bosch_Accel.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}       -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION)
	${MP_CC_DIR}\\pic32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/Bosch_Accel.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  
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
