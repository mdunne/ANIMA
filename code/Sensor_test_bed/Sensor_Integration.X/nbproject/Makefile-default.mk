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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Sensor_Integration.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Sensor_Integration.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/Sensor_Integration_Test.o ${OBJECTDIR}/Sensor_Integration.o ${OBJECTDIR}/_ext/1436657880/serial.o ${OBJECTDIR}/_ext/1602749850/I2C_Driver.o ${OBJECTDIR}/_ext/2092746018/freescale_accel.o ${OBJECTDIR}/_ext/1436657880/timers.o ${OBJECTDIR}/_ext/2141726714/LED.o ${OBJECTDIR}/_ext/967873263/bosch_accel.o ${OBJECTDIR}/_ext/1595363603/freescale_mag.o ${OBJECTDIR}/_ext/749370040/honeywell_mag.o ${OBJECTDIR}/_ext/1451742739/st_compass.o ${OBJECTDIR}/_ext/2146002203/gps.o ${OBJECTDIR}/_ext/2142338205/Data_Logging.o ${OBJECTDIR}/_ext/1537580865/SD-SPI.o
POSSIBLE_DEPFILES=${OBJECTDIR}/Sensor_Integration_Test.o.d ${OBJECTDIR}/Sensor_Integration.o.d ${OBJECTDIR}/_ext/1436657880/serial.o.d ${OBJECTDIR}/_ext/1602749850/I2C_Driver.o.d ${OBJECTDIR}/_ext/2092746018/freescale_accel.o.d ${OBJECTDIR}/_ext/1436657880/timers.o.d ${OBJECTDIR}/_ext/2141726714/LED.o.d ${OBJECTDIR}/_ext/967873263/bosch_accel.o.d ${OBJECTDIR}/_ext/1595363603/freescale_mag.o.d ${OBJECTDIR}/_ext/749370040/honeywell_mag.o.d ${OBJECTDIR}/_ext/1451742739/st_compass.o.d ${OBJECTDIR}/_ext/2146002203/gps.o.d ${OBJECTDIR}/_ext/2142338205/Data_Logging.o.d ${OBJECTDIR}/_ext/1537580865/SD-SPI.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/Sensor_Integration_Test.o ${OBJECTDIR}/Sensor_Integration.o ${OBJECTDIR}/_ext/1436657880/serial.o ${OBJECTDIR}/_ext/1602749850/I2C_Driver.o ${OBJECTDIR}/_ext/2092746018/freescale_accel.o ${OBJECTDIR}/_ext/1436657880/timers.o ${OBJECTDIR}/_ext/2141726714/LED.o ${OBJECTDIR}/_ext/967873263/bosch_accel.o ${OBJECTDIR}/_ext/1595363603/freescale_mag.o ${OBJECTDIR}/_ext/749370040/honeywell_mag.o ${OBJECTDIR}/_ext/1451742739/st_compass.o ${OBJECTDIR}/_ext/2146002203/gps.o ${OBJECTDIR}/_ext/2142338205/Data_Logging.o ${OBJECTDIR}/_ext/1537580865/SD-SPI.o


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
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Sensor_Integration.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

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
${OBJECTDIR}/Sensor_Integration_Test.o: Sensor_Integration_Test.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Sensor_Integration_Test.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Sensor_Integration_Test.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/118_Libraries/include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Data_Logging.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Freescale_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/freescale_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Bosch_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Honeywell_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/ST_Compass.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/GPS.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/I2C_Driver.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/LED.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include/MDD File System" -MMD -MF "${OBJECTDIR}/Sensor_Integration_Test.o.d" -o ${OBJECTDIR}/Sensor_Integration_Test.o Sensor_Integration_Test.c  
	
${OBJECTDIR}/Sensor_Integration.o: Sensor_Integration.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Sensor_Integration.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Sensor_Integration.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/118_Libraries/include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Data_Logging.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Freescale_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/freescale_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Bosch_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Honeywell_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/ST_Compass.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/GPS.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/I2C_Driver.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/LED.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include/MDD File System" -MMD -MF "${OBJECTDIR}/Sensor_Integration.o.d" -o ${OBJECTDIR}/Sensor_Integration.o Sensor_Integration.c  
	
${OBJECTDIR}/_ext/1436657880/serial.o: ../118_Libraries/src/serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1436657880 
	@${RM} ${OBJECTDIR}/_ext/1436657880/serial.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1436657880/serial.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/118_Libraries/include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Data_Logging.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Freescale_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/freescale_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Bosch_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Honeywell_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/ST_Compass.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/GPS.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/I2C_Driver.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/LED.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include/MDD File System" -MMD -MF "${OBJECTDIR}/_ext/1436657880/serial.o.d" -o ${OBJECTDIR}/_ext/1436657880/serial.o ../118_Libraries/src/serial.c  
	
${OBJECTDIR}/_ext/1602749850/I2C_Driver.o: ../I2C_Driver.X/I2C_Driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1602749850 
	@${RM} ${OBJECTDIR}/_ext/1602749850/I2C_Driver.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1602749850/I2C_Driver.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/118_Libraries/include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Data_Logging.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Freescale_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/freescale_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Bosch_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Honeywell_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/ST_Compass.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/GPS.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/I2C_Driver.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/LED.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include/MDD File System" -MMD -MF "${OBJECTDIR}/_ext/1602749850/I2C_Driver.o.d" -o ${OBJECTDIR}/_ext/1602749850/I2C_Driver.o ../I2C_Driver.X/I2C_Driver.c  
	
${OBJECTDIR}/_ext/2092746018/freescale_accel.o: ../Freescale_Accel.X/freescale_accel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2092746018 
	@${RM} ${OBJECTDIR}/_ext/2092746018/freescale_accel.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2092746018/freescale_accel.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/118_Libraries/include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Data_Logging.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Freescale_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/freescale_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Bosch_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Honeywell_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/ST_Compass.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/GPS.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/I2C_Driver.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/LED.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include/MDD File System" -MMD -MF "${OBJECTDIR}/_ext/2092746018/freescale_accel.o.d" -o ${OBJECTDIR}/_ext/2092746018/freescale_accel.o ../Freescale_Accel.X/freescale_accel.c  
	
${OBJECTDIR}/_ext/1436657880/timers.o: ../118_Libraries/src/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1436657880 
	@${RM} ${OBJECTDIR}/_ext/1436657880/timers.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1436657880/timers.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/118_Libraries/include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Data_Logging.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Freescale_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/freescale_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Bosch_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Honeywell_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/ST_Compass.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/GPS.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/I2C_Driver.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/LED.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include/MDD File System" -MMD -MF "${OBJECTDIR}/_ext/1436657880/timers.o.d" -o ${OBJECTDIR}/_ext/1436657880/timers.o ../118_Libraries/src/timers.c  
	
${OBJECTDIR}/_ext/2141726714/LED.o: ../LED.X/LED.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2141726714 
	@${RM} ${OBJECTDIR}/_ext/2141726714/LED.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2141726714/LED.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/118_Libraries/include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Data_Logging.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Freescale_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/freescale_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Bosch_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Honeywell_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/ST_Compass.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/GPS.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/I2C_Driver.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/LED.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include/MDD File System" -MMD -MF "${OBJECTDIR}/_ext/2141726714/LED.o.d" -o ${OBJECTDIR}/_ext/2141726714/LED.o ../LED.X/LED.c  
	
${OBJECTDIR}/_ext/967873263/bosch_accel.o: ../Bosch_Accel.X/bosch_accel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/967873263 
	@${RM} ${OBJECTDIR}/_ext/967873263/bosch_accel.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/967873263/bosch_accel.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/118_Libraries/include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Data_Logging.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Freescale_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/freescale_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Bosch_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Honeywell_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/ST_Compass.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/GPS.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/I2C_Driver.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/LED.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include/MDD File System" -MMD -MF "${OBJECTDIR}/_ext/967873263/bosch_accel.o.d" -o ${OBJECTDIR}/_ext/967873263/bosch_accel.o ../Bosch_Accel.X/bosch_accel.c  
	
${OBJECTDIR}/_ext/1595363603/freescale_mag.o: ../freescale_Mag.X/freescale_mag.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1595363603 
	@${RM} ${OBJECTDIR}/_ext/1595363603/freescale_mag.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1595363603/freescale_mag.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/118_Libraries/include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Data_Logging.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Freescale_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/freescale_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Bosch_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Honeywell_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/ST_Compass.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/GPS.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/I2C_Driver.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/LED.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include/MDD File System" -MMD -MF "${OBJECTDIR}/_ext/1595363603/freescale_mag.o.d" -o ${OBJECTDIR}/_ext/1595363603/freescale_mag.o ../freescale_Mag.X/freescale_mag.c  
	
${OBJECTDIR}/_ext/749370040/honeywell_mag.o: ../Honeywell_Mag.X/honeywell_mag.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/749370040 
	@${RM} ${OBJECTDIR}/_ext/749370040/honeywell_mag.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/749370040/honeywell_mag.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/118_Libraries/include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Data_Logging.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Freescale_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/freescale_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Bosch_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Honeywell_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/ST_Compass.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/GPS.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/I2C_Driver.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/LED.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include/MDD File System" -MMD -MF "${OBJECTDIR}/_ext/749370040/honeywell_mag.o.d" -o ${OBJECTDIR}/_ext/749370040/honeywell_mag.o ../Honeywell_Mag.X/honeywell_mag.c  
	
${OBJECTDIR}/_ext/1451742739/st_compass.o: ../ST_Compass.X/st_compass.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1451742739 
	@${RM} ${OBJECTDIR}/_ext/1451742739/st_compass.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1451742739/st_compass.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/118_Libraries/include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Data_Logging.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Freescale_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/freescale_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Bosch_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Honeywell_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/ST_Compass.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/GPS.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/I2C_Driver.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/LED.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include/MDD File System" -MMD -MF "${OBJECTDIR}/_ext/1451742739/st_compass.o.d" -o ${OBJECTDIR}/_ext/1451742739/st_compass.o ../ST_Compass.X/st_compass.c  
	
${OBJECTDIR}/_ext/2146002203/gps.o: ../GPS.X/gps.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2146002203 
	@${RM} ${OBJECTDIR}/_ext/2146002203/gps.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2146002203/gps.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/118_Libraries/include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Data_Logging.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Freescale_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/freescale_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Bosch_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Honeywell_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/ST_Compass.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/GPS.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/I2C_Driver.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/LED.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include/MDD File System" -MMD -MF "${OBJECTDIR}/_ext/2146002203/gps.o.d" -o ${OBJECTDIR}/_ext/2146002203/gps.o ../GPS.X/gps.c  
	
${OBJECTDIR}/_ext/2142338205/Data_Logging.o: ../Data_Logging.X/Data_Logging.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2142338205 
	@${RM} ${OBJECTDIR}/_ext/2142338205/Data_Logging.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2142338205/Data_Logging.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/118_Libraries/include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Data_Logging.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Freescale_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/freescale_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Bosch_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Honeywell_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/ST_Compass.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/GPS.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/I2C_Driver.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/LED.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include/MDD File System" -MMD -MF "${OBJECTDIR}/_ext/2142338205/Data_Logging.o.d" -o ${OBJECTDIR}/_ext/2142338205/Data_Logging.o ../Data_Logging.X/Data_Logging.c  
	
${OBJECTDIR}/_ext/1537580865/SD-SPI.o: ../../../../../../../Microchip\ Solutions\ v2012-04-03/Microchip/MDD\ File\ System/SD-SPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1537580865 
	@${RM} ${OBJECTDIR}/_ext/1537580865/SD-SPI.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1537580865/SD-SPI.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/118_Libraries/include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Data_Logging.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Freescale_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/freescale_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Bosch_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Honeywell_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/ST_Compass.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/GPS.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/I2C_Driver.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/LED.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include/MDD File System" -MMD -MF "${OBJECTDIR}/_ext/1537580865/SD-SPI.o.d" -o ${OBJECTDIR}/_ext/1537580865/SD-SPI.o "../../../../../../../Microchip Solutions v2012-04-03/Microchip/MDD File System/SD-SPI.c"  
	
else
${OBJECTDIR}/Sensor_Integration_Test.o: Sensor_Integration_Test.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Sensor_Integration_Test.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Sensor_Integration_Test.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/118_Libraries/include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Data_Logging.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Freescale_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/freescale_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Bosch_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Honeywell_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/ST_Compass.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/GPS.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/I2C_Driver.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/LED.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include/MDD File System" -MMD -MF "${OBJECTDIR}/Sensor_Integration_Test.o.d" -o ${OBJECTDIR}/Sensor_Integration_Test.o Sensor_Integration_Test.c  
	
${OBJECTDIR}/Sensor_Integration.o: Sensor_Integration.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Sensor_Integration.o.d 
	@${FIXDEPS} "${OBJECTDIR}/Sensor_Integration.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/118_Libraries/include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Data_Logging.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Freescale_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/freescale_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Bosch_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Honeywell_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/ST_Compass.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/GPS.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/I2C_Driver.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/LED.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include/MDD File System" -MMD -MF "${OBJECTDIR}/Sensor_Integration.o.d" -o ${OBJECTDIR}/Sensor_Integration.o Sensor_Integration.c  
	
${OBJECTDIR}/_ext/1436657880/serial.o: ../118_Libraries/src/serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1436657880 
	@${RM} ${OBJECTDIR}/_ext/1436657880/serial.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1436657880/serial.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/118_Libraries/include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Data_Logging.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Freescale_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/freescale_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Bosch_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Honeywell_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/ST_Compass.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/GPS.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/I2C_Driver.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/LED.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include/MDD File System" -MMD -MF "${OBJECTDIR}/_ext/1436657880/serial.o.d" -o ${OBJECTDIR}/_ext/1436657880/serial.o ../118_Libraries/src/serial.c  
	
${OBJECTDIR}/_ext/1602749850/I2C_Driver.o: ../I2C_Driver.X/I2C_Driver.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1602749850 
	@${RM} ${OBJECTDIR}/_ext/1602749850/I2C_Driver.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1602749850/I2C_Driver.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/118_Libraries/include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Data_Logging.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Freescale_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/freescale_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Bosch_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Honeywell_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/ST_Compass.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/GPS.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/I2C_Driver.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/LED.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include/MDD File System" -MMD -MF "${OBJECTDIR}/_ext/1602749850/I2C_Driver.o.d" -o ${OBJECTDIR}/_ext/1602749850/I2C_Driver.o ../I2C_Driver.X/I2C_Driver.c  
	
${OBJECTDIR}/_ext/2092746018/freescale_accel.o: ../Freescale_Accel.X/freescale_accel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2092746018 
	@${RM} ${OBJECTDIR}/_ext/2092746018/freescale_accel.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2092746018/freescale_accel.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/118_Libraries/include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Data_Logging.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Freescale_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/freescale_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Bosch_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Honeywell_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/ST_Compass.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/GPS.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/I2C_Driver.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/LED.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include/MDD File System" -MMD -MF "${OBJECTDIR}/_ext/2092746018/freescale_accel.o.d" -o ${OBJECTDIR}/_ext/2092746018/freescale_accel.o ../Freescale_Accel.X/freescale_accel.c  
	
${OBJECTDIR}/_ext/1436657880/timers.o: ../118_Libraries/src/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1436657880 
	@${RM} ${OBJECTDIR}/_ext/1436657880/timers.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1436657880/timers.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/118_Libraries/include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Data_Logging.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Freescale_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/freescale_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Bosch_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Honeywell_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/ST_Compass.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/GPS.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/I2C_Driver.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/LED.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include/MDD File System" -MMD -MF "${OBJECTDIR}/_ext/1436657880/timers.o.d" -o ${OBJECTDIR}/_ext/1436657880/timers.o ../118_Libraries/src/timers.c  
	
${OBJECTDIR}/_ext/2141726714/LED.o: ../LED.X/LED.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2141726714 
	@${RM} ${OBJECTDIR}/_ext/2141726714/LED.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2141726714/LED.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/118_Libraries/include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Data_Logging.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Freescale_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/freescale_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Bosch_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Honeywell_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/ST_Compass.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/GPS.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/I2C_Driver.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/LED.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include/MDD File System" -MMD -MF "${OBJECTDIR}/_ext/2141726714/LED.o.d" -o ${OBJECTDIR}/_ext/2141726714/LED.o ../LED.X/LED.c  
	
${OBJECTDIR}/_ext/967873263/bosch_accel.o: ../Bosch_Accel.X/bosch_accel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/967873263 
	@${RM} ${OBJECTDIR}/_ext/967873263/bosch_accel.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/967873263/bosch_accel.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/118_Libraries/include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Data_Logging.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Freescale_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/freescale_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Bosch_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Honeywell_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/ST_Compass.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/GPS.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/I2C_Driver.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/LED.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include/MDD File System" -MMD -MF "${OBJECTDIR}/_ext/967873263/bosch_accel.o.d" -o ${OBJECTDIR}/_ext/967873263/bosch_accel.o ../Bosch_Accel.X/bosch_accel.c  
	
${OBJECTDIR}/_ext/1595363603/freescale_mag.o: ../freescale_Mag.X/freescale_mag.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1595363603 
	@${RM} ${OBJECTDIR}/_ext/1595363603/freescale_mag.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1595363603/freescale_mag.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/118_Libraries/include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Data_Logging.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Freescale_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/freescale_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Bosch_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Honeywell_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/ST_Compass.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/GPS.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/I2C_Driver.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/LED.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include/MDD File System" -MMD -MF "${OBJECTDIR}/_ext/1595363603/freescale_mag.o.d" -o ${OBJECTDIR}/_ext/1595363603/freescale_mag.o ../freescale_Mag.X/freescale_mag.c  
	
${OBJECTDIR}/_ext/749370040/honeywell_mag.o: ../Honeywell_Mag.X/honeywell_mag.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/749370040 
	@${RM} ${OBJECTDIR}/_ext/749370040/honeywell_mag.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/749370040/honeywell_mag.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/118_Libraries/include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Data_Logging.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Freescale_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/freescale_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Bosch_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Honeywell_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/ST_Compass.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/GPS.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/I2C_Driver.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/LED.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include/MDD File System" -MMD -MF "${OBJECTDIR}/_ext/749370040/honeywell_mag.o.d" -o ${OBJECTDIR}/_ext/749370040/honeywell_mag.o ../Honeywell_Mag.X/honeywell_mag.c  
	
${OBJECTDIR}/_ext/1451742739/st_compass.o: ../ST_Compass.X/st_compass.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1451742739 
	@${RM} ${OBJECTDIR}/_ext/1451742739/st_compass.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1451742739/st_compass.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/118_Libraries/include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Data_Logging.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Freescale_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/freescale_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Bosch_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Honeywell_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/ST_Compass.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/GPS.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/I2C_Driver.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/LED.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include/MDD File System" -MMD -MF "${OBJECTDIR}/_ext/1451742739/st_compass.o.d" -o ${OBJECTDIR}/_ext/1451742739/st_compass.o ../ST_Compass.X/st_compass.c  
	
${OBJECTDIR}/_ext/2146002203/gps.o: ../GPS.X/gps.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2146002203 
	@${RM} ${OBJECTDIR}/_ext/2146002203/gps.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2146002203/gps.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/118_Libraries/include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Data_Logging.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Freescale_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/freescale_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Bosch_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Honeywell_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/ST_Compass.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/GPS.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/I2C_Driver.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/LED.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include/MDD File System" -MMD -MF "${OBJECTDIR}/_ext/2146002203/gps.o.d" -o ${OBJECTDIR}/_ext/2146002203/gps.o ../GPS.X/gps.c  
	
${OBJECTDIR}/_ext/2142338205/Data_Logging.o: ../Data_Logging.X/Data_Logging.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2142338205 
	@${RM} ${OBJECTDIR}/_ext/2142338205/Data_Logging.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2142338205/Data_Logging.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/118_Libraries/include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Data_Logging.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Freescale_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/freescale_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Bosch_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Honeywell_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/ST_Compass.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/GPS.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/I2C_Driver.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/LED.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include/MDD File System" -MMD -MF "${OBJECTDIR}/_ext/2142338205/Data_Logging.o.d" -o ${OBJECTDIR}/_ext/2142338205/Data_Logging.o ../Data_Logging.X/Data_Logging.c  
	
${OBJECTDIR}/_ext/1537580865/SD-SPI.o: ../../../../../../../Microchip\ Solutions\ v2012-04-03/Microchip/MDD\ File\ System/SD-SPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1537580865 
	@${RM} ${OBJECTDIR}/_ext/1537580865/SD-SPI.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1537580865/SD-SPI.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/118_Libraries/include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Data_Logging.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Freescale_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/freescale_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Bosch_Accel.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/Honeywell_Mag.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/ST_Compass.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/GPS.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/I2C_Driver.X" -I"C:/Users/mdunne/Documents/ANIMA/code/Sensor_test_bed/LED.X" -I"C:/Microchip Solutions v2012-04-03/Microchip/Include/MDD File System" -MMD -MF "${OBJECTDIR}/_ext/1537580865/SD-SPI.o.d" -o ${OBJECTDIR}/_ext/1537580865/SD-SPI.o "../../../../../../../Microchip Solutions v2012-04-03/Microchip/MDD File System/SD-SPI.c"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Sensor_Integration.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Sensor_Integration.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}       -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__ICD2RAM=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,--defsym=_min_stack_size=2048,--report-mem,--warn-section-align 
else
dist/${CND_CONF}/${IMAGE_TYPE}/Sensor_Integration.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Sensor_Integration.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}       -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_stack_size=2048,--report-mem,--warn-section-align
	${MP_CC_DIR}\\pic32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/Sensor_Integration.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  
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
