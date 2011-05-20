#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
include Makefile

# Environment
MKDIR=mkdir -p
RM=rm -f 
CP=cp 
# Macros
CND_CONF=default

ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/stmicro_accel_test.X.${IMAGE_TYPE}.elf
else
IMAGE_TYPE=production
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/stmicro_accel_test.X.${IMAGE_TYPE}.elf
endif
# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}
# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1853886318/uart2.o ${OBJECTDIR}/_ext/1853886318/write.o ${OBJECTDIR}/_ext/1472/stmicro_accel.o ${OBJECTDIR}/_ext/1853886318/circBuffer.o ${OBJECTDIR}/_ext/1472/stmicro_accel_test.o


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

# Path to java used to run MPLAB X when this makefile was created
MP_JAVA_PATH=C:\\Program\ Files\ \(x86\)\\Java\\jre6/bin/
OS_ORIGINAL="MINGW32_NT-6.1"
OS_CURRENT="$(shell uname -s)"
############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
MP_CC=C:\\Program\ Files\ \(x86\)\\Microchip\\MPLAB\ C30\\bin\\pic30-gcc.exe
# MP_BC is not defined
MP_AS=C:\\Program\ Files\ \(x86\)\\Microchip\\MPLAB\ C30\\bin\\pic30-as.exe
MP_LD=C:\\Program\ Files\ \(x86\)\\Microchip\\MPLAB\ C30\\bin\\pic30-ld.exe
MP_AR=C:\\Program\ Files\ \(x86\)\\Microchip\\MPLAB\ C30\\bin\\pic30-ar.exe
# MP_BC is not defined
MP_CC_DIR=C:\\Program\ Files\ \(x86\)\\Microchip\\MPLAB\ C30\\bin
# MP_BC_DIR is not defined
MP_AS_DIR=C:\\Program\ Files\ \(x86\)\\Microchip\\MPLAB\ C30\\bin
MP_LD_DIR=C:\\Program\ Files\ \(x86\)\\Microchip\\MPLAB\ C30\\bin
MP_AR_DIR=C:\\Program\ Files\ \(x86\)\\Microchip\\MPLAB\ C30\\bin
# MP_BC_DIR is not defined
.build-conf: ${BUILD_SUBPROJECTS}
ifneq ($(OS_CURRENT),$(OS_ORIGINAL))
	@echo "***** WARNING: This make file contains OS dependent code. The OS this makefile is being run is different from the OS it was created in."
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/stmicro_accel_test.X.${IMAGE_TYPE}.elf

MP_PROCESSOR_OPTION=33FJ64MC802
MP_LINKER_FILE_OPTION=,-Tp33FJ64MC802.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1853886318/uart2.o: ../../uart/uart2.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1853886318 
	${RM} ${OBJECTDIR}/_ext/1853886318/uart2.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../../uart" -I".." -MMD -MF ${OBJECTDIR}/_ext/1853886318/uart2.o.d -o ${OBJECTDIR}/_ext/1853886318/uart2.o ../../uart/uart2.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1853886318/uart2.o.d > ${OBJECTDIR}/_ext/1853886318/uart2.o.tmp
	${RM} ${OBJECTDIR}/_ext/1853886318/uart2.o.d 
	${CP} ${OBJECTDIR}/_ext/1853886318/uart2.o.tmp ${OBJECTDIR}/_ext/1853886318/uart2.o.d 
	${RM} ${OBJECTDIR}/_ext/1853886318/uart2.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1853886318/uart2.o.d > ${OBJECTDIR}/_ext/1853886318/uart2.o.tmp
	${RM} ${OBJECTDIR}/_ext/1853886318/uart2.o.d 
	${CP} ${OBJECTDIR}/_ext/1853886318/uart2.o.tmp ${OBJECTDIR}/_ext/1853886318/uart2.o.d 
	${RM} ${OBJECTDIR}/_ext/1853886318/uart2.o.tmp
endif
${OBJECTDIR}/_ext/1853886318/write.o: ../../uart/write.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1853886318 
	${RM} ${OBJECTDIR}/_ext/1853886318/write.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../../uart" -I".." -MMD -MF ${OBJECTDIR}/_ext/1853886318/write.o.d -o ${OBJECTDIR}/_ext/1853886318/write.o ../../uart/write.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1853886318/write.o.d > ${OBJECTDIR}/_ext/1853886318/write.o.tmp
	${RM} ${OBJECTDIR}/_ext/1853886318/write.o.d 
	${CP} ${OBJECTDIR}/_ext/1853886318/write.o.tmp ${OBJECTDIR}/_ext/1853886318/write.o.d 
	${RM} ${OBJECTDIR}/_ext/1853886318/write.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1853886318/write.o.d > ${OBJECTDIR}/_ext/1853886318/write.o.tmp
	${RM} ${OBJECTDIR}/_ext/1853886318/write.o.d 
	${CP} ${OBJECTDIR}/_ext/1853886318/write.o.tmp ${OBJECTDIR}/_ext/1853886318/write.o.d 
	${RM} ${OBJECTDIR}/_ext/1853886318/write.o.tmp
endif
${OBJECTDIR}/_ext/1472/stmicro_accel.o: ../stmicro_accel.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
	${RM} ${OBJECTDIR}/_ext/1472/stmicro_accel.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../../uart" -I".." -MMD -MF ${OBJECTDIR}/_ext/1472/stmicro_accel.o.d -o ${OBJECTDIR}/_ext/1472/stmicro_accel.o ../stmicro_accel.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1472/stmicro_accel.o.d > ${OBJECTDIR}/_ext/1472/stmicro_accel.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/stmicro_accel.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/stmicro_accel.o.tmp ${OBJECTDIR}/_ext/1472/stmicro_accel.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/stmicro_accel.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1472/stmicro_accel.o.d > ${OBJECTDIR}/_ext/1472/stmicro_accel.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/stmicro_accel.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/stmicro_accel.o.tmp ${OBJECTDIR}/_ext/1472/stmicro_accel.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/stmicro_accel.o.tmp
endif
${OBJECTDIR}/_ext/1853886318/circBuffer.o: ../../uart/circBuffer.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1853886318 
	${RM} ${OBJECTDIR}/_ext/1853886318/circBuffer.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../../uart" -I".." -MMD -MF ${OBJECTDIR}/_ext/1853886318/circBuffer.o.d -o ${OBJECTDIR}/_ext/1853886318/circBuffer.o ../../uart/circBuffer.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1853886318/circBuffer.o.d > ${OBJECTDIR}/_ext/1853886318/circBuffer.o.tmp
	${RM} ${OBJECTDIR}/_ext/1853886318/circBuffer.o.d 
	${CP} ${OBJECTDIR}/_ext/1853886318/circBuffer.o.tmp ${OBJECTDIR}/_ext/1853886318/circBuffer.o.d 
	${RM} ${OBJECTDIR}/_ext/1853886318/circBuffer.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1853886318/circBuffer.o.d > ${OBJECTDIR}/_ext/1853886318/circBuffer.o.tmp
	${RM} ${OBJECTDIR}/_ext/1853886318/circBuffer.o.d 
	${CP} ${OBJECTDIR}/_ext/1853886318/circBuffer.o.tmp ${OBJECTDIR}/_ext/1853886318/circBuffer.o.d 
	${RM} ${OBJECTDIR}/_ext/1853886318/circBuffer.o.tmp
endif
${OBJECTDIR}/_ext/1472/stmicro_accel_test.o: ../stmicro_accel_test.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
	${RM} ${OBJECTDIR}/_ext/1472/stmicro_accel_test.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../../uart" -I".." -MMD -MF ${OBJECTDIR}/_ext/1472/stmicro_accel_test.o.d -o ${OBJECTDIR}/_ext/1472/stmicro_accel_test.o ../stmicro_accel_test.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1472/stmicro_accel_test.o.d > ${OBJECTDIR}/_ext/1472/stmicro_accel_test.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/stmicro_accel_test.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/stmicro_accel_test.o.tmp ${OBJECTDIR}/_ext/1472/stmicro_accel_test.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/stmicro_accel_test.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1472/stmicro_accel_test.o.d > ${OBJECTDIR}/_ext/1472/stmicro_accel_test.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/stmicro_accel_test.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/stmicro_accel_test.o.tmp ${OBJECTDIR}/_ext/1472/stmicro_accel_test.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/stmicro_accel_test.o.tmp
endif
else
${OBJECTDIR}/_ext/1853886318/uart2.o: ../../uart/uart2.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1853886318 
	${RM} ${OBJECTDIR}/_ext/1853886318/uart2.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../../uart" -I".." -MMD -MF ${OBJECTDIR}/_ext/1853886318/uart2.o.d -o ${OBJECTDIR}/_ext/1853886318/uart2.o ../../uart/uart2.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1853886318/uart2.o.d > ${OBJECTDIR}/_ext/1853886318/uart2.o.tmp
	${RM} ${OBJECTDIR}/_ext/1853886318/uart2.o.d 
	${CP} ${OBJECTDIR}/_ext/1853886318/uart2.o.tmp ${OBJECTDIR}/_ext/1853886318/uart2.o.d 
	${RM} ${OBJECTDIR}/_ext/1853886318/uart2.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1853886318/uart2.o.d > ${OBJECTDIR}/_ext/1853886318/uart2.o.tmp
	${RM} ${OBJECTDIR}/_ext/1853886318/uart2.o.d 
	${CP} ${OBJECTDIR}/_ext/1853886318/uart2.o.tmp ${OBJECTDIR}/_ext/1853886318/uart2.o.d 
	${RM} ${OBJECTDIR}/_ext/1853886318/uart2.o.tmp
endif
${OBJECTDIR}/_ext/1853886318/write.o: ../../uart/write.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1853886318 
	${RM} ${OBJECTDIR}/_ext/1853886318/write.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../../uart" -I".." -MMD -MF ${OBJECTDIR}/_ext/1853886318/write.o.d -o ${OBJECTDIR}/_ext/1853886318/write.o ../../uart/write.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1853886318/write.o.d > ${OBJECTDIR}/_ext/1853886318/write.o.tmp
	${RM} ${OBJECTDIR}/_ext/1853886318/write.o.d 
	${CP} ${OBJECTDIR}/_ext/1853886318/write.o.tmp ${OBJECTDIR}/_ext/1853886318/write.o.d 
	${RM} ${OBJECTDIR}/_ext/1853886318/write.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1853886318/write.o.d > ${OBJECTDIR}/_ext/1853886318/write.o.tmp
	${RM} ${OBJECTDIR}/_ext/1853886318/write.o.d 
	${CP} ${OBJECTDIR}/_ext/1853886318/write.o.tmp ${OBJECTDIR}/_ext/1853886318/write.o.d 
	${RM} ${OBJECTDIR}/_ext/1853886318/write.o.tmp
endif
${OBJECTDIR}/_ext/1472/stmicro_accel.o: ../stmicro_accel.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
	${RM} ${OBJECTDIR}/_ext/1472/stmicro_accel.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../../uart" -I".." -MMD -MF ${OBJECTDIR}/_ext/1472/stmicro_accel.o.d -o ${OBJECTDIR}/_ext/1472/stmicro_accel.o ../stmicro_accel.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1472/stmicro_accel.o.d > ${OBJECTDIR}/_ext/1472/stmicro_accel.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/stmicro_accel.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/stmicro_accel.o.tmp ${OBJECTDIR}/_ext/1472/stmicro_accel.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/stmicro_accel.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1472/stmicro_accel.o.d > ${OBJECTDIR}/_ext/1472/stmicro_accel.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/stmicro_accel.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/stmicro_accel.o.tmp ${OBJECTDIR}/_ext/1472/stmicro_accel.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/stmicro_accel.o.tmp
endif
${OBJECTDIR}/_ext/1853886318/circBuffer.o: ../../uart/circBuffer.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1853886318 
	${RM} ${OBJECTDIR}/_ext/1853886318/circBuffer.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../../uart" -I".." -MMD -MF ${OBJECTDIR}/_ext/1853886318/circBuffer.o.d -o ${OBJECTDIR}/_ext/1853886318/circBuffer.o ../../uart/circBuffer.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1853886318/circBuffer.o.d > ${OBJECTDIR}/_ext/1853886318/circBuffer.o.tmp
	${RM} ${OBJECTDIR}/_ext/1853886318/circBuffer.o.d 
	${CP} ${OBJECTDIR}/_ext/1853886318/circBuffer.o.tmp ${OBJECTDIR}/_ext/1853886318/circBuffer.o.d 
	${RM} ${OBJECTDIR}/_ext/1853886318/circBuffer.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1853886318/circBuffer.o.d > ${OBJECTDIR}/_ext/1853886318/circBuffer.o.tmp
	${RM} ${OBJECTDIR}/_ext/1853886318/circBuffer.o.d 
	${CP} ${OBJECTDIR}/_ext/1853886318/circBuffer.o.tmp ${OBJECTDIR}/_ext/1853886318/circBuffer.o.d 
	${RM} ${OBJECTDIR}/_ext/1853886318/circBuffer.o.tmp
endif
${OBJECTDIR}/_ext/1472/stmicro_accel_test.o: ../stmicro_accel_test.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR}/_ext/1472 
	${RM} ${OBJECTDIR}/_ext/1472/stmicro_accel_test.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -Wall -I"../../uart" -I".." -MMD -MF ${OBJECTDIR}/_ext/1472/stmicro_accel_test.o.d -o ${OBJECTDIR}/_ext/1472/stmicro_accel_test.o ../stmicro_accel_test.c  
ifneq (,$(findstring MINGW32,$(OS_CURRENT))) 
	@sed -e 's/\"//g' -e 's/\\$$/__EOL__/g' -e 's/\\ /__ESCAPED_SPACES__/g' -e 's/\\/\//g' -e 's/__ESCAPED_SPACES__/\\ /g' -e 's/__EOL__$$/\\/g' ${OBJECTDIR}/_ext/1472/stmicro_accel_test.o.d > ${OBJECTDIR}/_ext/1472/stmicro_accel_test.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/stmicro_accel_test.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/stmicro_accel_test.o.tmp ${OBJECTDIR}/_ext/1472/stmicro_accel_test.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/stmicro_accel_test.o.tmp}
else 
	@sed -e 's/\"//g' ${OBJECTDIR}/_ext/1472/stmicro_accel_test.o.d > ${OBJECTDIR}/_ext/1472/stmicro_accel_test.o.tmp
	${RM} ${OBJECTDIR}/_ext/1472/stmicro_accel_test.o.d 
	${CP} ${OBJECTDIR}/_ext/1472/stmicro_accel_test.o.tmp ${OBJECTDIR}/_ext/1472/stmicro_accel_test.o.d 
	${RM} ${OBJECTDIR}/_ext/1472/stmicro_accel_test.o.tmp
endif
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/stmicro_accel_test.X.${IMAGE_TYPE}.elf: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -omf=elf  -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -o dist/${CND_CONF}/${IMAGE_TYPE}/stmicro_accel_test.X.${IMAGE_TYPE}.elf ${OBJECTFILES}        -Wl,--defsym=__MPLAB_BUILD=1,--heap=1024,-L"..",-Map="$(BINDIR_)$(TARGETBASE).map",--report-mem,--report-mem$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__ICD2RAM=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1
else
dist/${CND_CONF}/${IMAGE_TYPE}/stmicro_accel_test.X.${IMAGE_TYPE}.elf: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -omf=elf  -mcpu=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/stmicro_accel_test.X.${IMAGE_TYPE}.elf ${OBJECTFILES}        -Wl,--defsym=__MPLAB_BUILD=1,--heap=1024,-L"..",-Map="$(BINDIR_)$(TARGETBASE).map",--report-mem,--report-mem$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION)
	${MP_CC_DIR}\\pic30-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/stmicro_accel_test.X.${IMAGE_TYPE}.elf -omf=elf
endif


# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
