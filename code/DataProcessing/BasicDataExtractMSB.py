import sys
import struct
import binascii
import time
import ConfigParser
import os
import inspect

from operator import xor
from struct import unpack


def GenerateCRCTable(InputChunkSize,CRCPolynomial,CRCWidth):
	#print(CRCPolynomial,CRCWidth)
	
	ValuesToGenerate=2**(InputChunkSize*8)
	TopBitMask=1<<(CRCWidth*8-1)
	CRCMask=2**(CRCWidth*8)-1
	# print(ValuesToGenerate)
	CRCTable=[]
	for dividend in range(ValuesToGenerate):
		# print(dividend)
		
		ComputedCRC=1
		inByte=dividend<<((CRCWidth-InputChunkSize)*8)
		# print(inByte)
		for i in range(0,8):
			topBit=inByte&TopBitMask
			# print(topBit)
			if(topBit):
				inByte=(inByte<<1)^CRCPolynomial
			else:
				inByte=inByte<<1
				# print('hmm')
			inByte=inByte&CRCMask
		# TransformedDividend=BitArray(uint=dividend,length=InputChunkSize*8)+BitArray(uint=0,length=(CRCWidth-InputChunkSize)*8)
		# #print(TransformedDividend)
		# ComputedCRC=CalcCRC(TransformedDividend,CRCPolynomial,CRCWidth,0)
		
		CRCTable.append(inByte)
		# print(ComputedCRC,inByte)
	#print(ValuesToGenerate)
	return	CRCTable


def CalcCRCTable(Data,CRCPolynomial,CRCWidth,ChunkSize,Table,Seed=65535):
	#print(CRCTable)
	
	#first need the data in a byte array not strings otherwise xor on 
	#the python foo is not strong with this one
	Data=[ord(byte) for byte in Data]
	
	#and generate some masks and shifts
	# CRCWidth=log(CRCWidth)/log(2)  #log does not belong here, need to fix later
	CRCTopShift=(CRCWidth-ChunkSize)*8
	CRCTopMask=(2**(ChunkSize*8)-1)<<CRCTopShift
	CRCMask=2**(CRCWidth*8)-1
	
	# print(CRCTopShift,CRCTopMask)	
	#print(Data[0])
	#print(Data[0]<<8)
	
	#Seed the CRC, this is just the crc value
	# print(ord(Data))
	CRC=Seed
	for NewByte in Data:
		TopByte=(CRC&CRCTopMask)>>CRCTopShift
		CRC=((CRC<<CRCTopShift)|NewByte)&CRCMask
		CRC=CRC^Table[TopByte]
		# print(TopByte)
	
	# print(CRC)
	return CRC
	

def WriteNewPacketConfiguration(PacketID,StringName,StructString,CommentString,ConfigFileName="PacketIDs.cfg"):
	#build a new config object and read in the current config file
	config=ConfigParser.ConfigParser()
	config.read(ConfigFileName)
	SectionName=str(PacketID)
	#attempt to add the section, if already exist we only update the values given
	try:
		config.add_section(SectionName)
	except:
		print('Updating Entry instead of adding a new one, be careful')
		pass
	config.set(SectionName,'stringname',StringName)
	config.set(SectionName,'structstring',StructString)
	
	StructLength=struct.Struct(StructString).size
	config.set(SectionName,'structlength',StructLength)
	config.set(SectionName,'commentstring',CommentString)
	with open(ConfigFileName, 'wb') as configfile:
		config.write(configfile)
	return

#builds a dictionary of dictionaries of required packet information for parsing
def BuildPacketDictionary(ConfigFileName):
	PacketConfigs=ConfigParser.ConfigParser()
	PacketConfigs.read(ConfigFileName)
	PacketDict=dict()
	for Section in PacketConfigs.sections():
		MainDictKey=int(Section)
		CurDict=dict()
		CurDict['stringname']=PacketConfigs.get(Section,'stringname')
		
		#uniquely here we first store the string and then build the struct for unpacking and store that as well
		CurDict['structstring']=PacketConfigs.get(Section,'structstring')
		CurDict['unpackstruct']=struct.Struct(CurDict['structstring'])
		CurDict['structlength']=PacketConfigs.getint(Section,'structlength')
		CurDict['commentstring']=PacketConfigs.get(Section,'commentstring')
		PacketDict[MainDictKey]=CurDict
	return PacketDict
	
#constants along with the commonly used Structs
#while duplication of structs these could change
HeaderValue=0xFB3B+1+1
FooterValue=0x5F86+1+1
HeaderFooterStruct=struct.Struct('<H')
CheckSumStruct=struct.Struct('<H')
TimeStampStruct=struct.Struct('<H')
IDStruct=struct.Struct('H')
ConfigFileName='PacketIDs.cfg'
CRCPolynomial=0x8005
CRCWidth=2  #in bytes
CRCSeed=0xffff
CommentMarker='%'


testfilename="004_1.bin"
#uncomment for normal usage and comment testline
# numArguments
if(len(sys.argv)>1):
	InFileName=sys.argv[1]
else:
	InFileName=testfilename
print(len(sys.argv))

print(InFileName)
# exit()
# 

#need to generate table for quick CRC calculation, should probably store in file if table grows much larger
CRCTable=GenerateCRCTable(1,CRCPolynomial,CRCWidth)

CurTimeStamp=-1
# exit()

inFileHandler=open(InFileName,"rb")


TrimmedFileName,FileExt=os.path.splitext(InFileName)
print(TrimmedFileName,FileExt)
# print(inspect.stack(ConfigParser))
# exit()
OutFileName=TrimmedFileName+'_parsed.txt'
OutFileHandler=open(OutFileName,"w")
# OutFileHandler.seek(0)

curSector=inFileHandler.read(512)
ValidSectorCount=0
ValidPacketsFound=0
usebitCRC=False
FullStartTime=time.time()
BytesToProcess=0
FullDataPacket=''
MagAccelStruct=struct.Struct('<H 33h')

#MagAccelTemplate
# WriteNewPacketConfiguration(42,'Mag_Accel_Packet','<H 33h','this is the line for the top of the file',ConfigFileName)
#GPSTemplate
# WriteNewPacketConfiguration(42,'GPS_Packet','<H 6B 3f 4B','this is the comment line',ConfigFileName)
#TempTemplate
# WriteNewPacketConfiguration(62,'Temp_Packet','<H h','SectorTimeStamp PacketID Temp',ConfigFileName)

PacketDict=BuildPacketDictionary(ConfigFileName)

#we need to build the comment block on the top of the file
#first line is a filler for a date to be filled later

OutFileHandler.write(CommentMarker + 'File ID: 20')
IDSeekPos=OutFileHandler.tell()
IDTempString='{0: <81}'.format('')
FirstGPSFound=False

OutFileHandler.write(IDTempString+'\n')
OutFileHandler.write(CommentMarker+'Lines after this one are packet definitions\n')

for key in PacketDict:
	CommentLine=PacketDict[key]['commentstring']
	OutFileHandler.write(CommentMarker+CommentLine+'\n')

for key in PacketDict:
	CurEntry=PacketDict[key]
	curEntryKey=key
	for key in CurEntry:
		print(curEntryKey,key,CurEntry[key])
# print(PacketConfigs.get('34','stringname'))
ValidPacketsFound=0
ValidChecksumedSectors=0
TotalBytesRemoved=0
TotalSectors=0
# exit()
while curSector!='':
	TotalSectors=TotalSectors+1
	#check first for header and footer for verification of valid sector
	inHeaderValue=HeaderFooterStruct.unpack(curSector[:2])[0]
	inFooterValue=HeaderFooterStruct.unpack(curSector[-2:])[0]
	if inHeaderValue==HeaderValue and inFooterValue==FooterValue:
		# print("Valid Sector Found")
		ValidSectorCount=ValidSectorCount+1
		#extract checksum and calculate new checksum
		inCheckSum=CheckSumStruct.unpack(curSector[-4:-2])[0]
		
		#need the data portion as a bytearray
		#removing header/timestamp from beginning and footer/checksum from the end
		# PacketBitArray=BitArray(int=unpack('b',curSector[4])[0],length=8)
		#print(PacketBitArray)
		IncomingDataPacket=(curSector[4:-4])
		TimeStart=time.time()
		ComputedChecksum=CalcCRCTable(IncomingDataPacket,CRCPolynomial,CRCWidth,1,CRCTable)
		TimeEnd=time.time()
		TimeElapsed=TimeEnd-TimeStart
		#print("asda")
		
		# print(ComputedChecksum, inCheckSum)
		#if(Compute
		if(ComputedChecksum==inCheckSum):
			print('+'),
			# we need to find the new time stamp but not update the value
			PossTimeStamp=TimeStampStruct.unpack(curSector[2:4])[0]
			ValidChecksumedSectors=ValidChecksumedSectors+1
			#the first timestamp needs to be set regardless of packet state
			if(CurTimeStamp==-1):
				CurTimeStamp=PossTimeStamp
			# print("Sector #%d Verified in %f seconds " % (ValidSectorCount,TimeElapsed))
			CurSectorByteCount=0
			BytesToProcess=BytesToProcess+len(IncomingDataPacket)
			FullDataPacket=FullDataPacket+IncomingDataPacket
			
			# print(BytesToProcess)
			# print([ord(byte) for byte in FullDataPacket])
			while(True):
				# print(len(FullDataPacket),ord(FullDataPacket[0]))
				if(len(FullDataPacket)>=2):
					FirstByte=ord(FullDataPacket[0])
					# pic can't pack 8 bits in, need to upshift to 16 bits for id for now fudged as they are the wrong endedness
					FirstByte=IDStruct.unpack(FullDataPacket[0:2])[0]

					# print(ValidSectorCount,len(FullDataPacket))
					
					#we first test to see if the next byte is a known packet ID
					if(FirstByte in PacketDict):
						# print("Found a MagAccel Packet")
						PacketLength=PacketDict[FirstByte]['structlength']
						#we then make sure we have a full packet if not we need to wait for the next sector
						if(len(FullDataPacket)>=PacketLength):
						
							#extract and unpack the packet
							CurRawData=FullDataPacket[0:PacketLength]
							CurDataPacket=PacketDict[FirstByte]['unpackstruct'].unpack(CurRawData)
							ValidPacketsFound=ValidPacketsFound+1
							
							#we do a special check for a gps packet as we need it for the top of the file
							if(PacketDict[FirstByte]['stringname']=='GPS_Packet' and not FirstGPSFound):
								# print('first check worked')
								FirstGPSFound=True
								GPSPacketForID=CurDataPacket
							
							# print([ord(byte) for byte in CurRawData])
							# print([format(ord(byte),'02x') for byte in CurRawData])
							#prepend the time stamp for the outfile and format the string
							OutTuple=(CurTimeStamp,)+CurDataPacket
							# print(OutTuple)
							OutString="\t".join(str(i) for i in OutTuple)
							# print(OutString)
							#add it to the log file
							OutFileHandler.write(OutString+'\n')
							# we can now update the timestamp as this packet is done
							CurTimeStamp=PossTimeStamp
							
							
							# print(CurDataPacket)
							# print([byte.encode('hex') for byte in CurRawData])
							# print(len(CurRawData))
							
							
							#remove the processed packet from the fullDataPacket
							FullDataPacket=FullDataPacket[PacketLength:]
							# print(len(FullDataPacket))
							# print(ValidSectorCount,ValidPacketsFound)
						else:
							break
					else:
						#at this point we do not have valid packet and assume the data stream is corrupted, we need to find the valid start
						BytesToRemove=0
						# print([ord(byte for byte in FullDataPacket])
						for IDIndex in range(0,len(FullDataPacket),2):
							DeadByte=IDStruct.unpack(FullDataPacket[IDIndex:IDIndex+2])[0]
							#print(DeadByte)
							if(DeadByte not in PacketDict):
								BytesToRemove=IDIndex+2
								# print(BytesToRemove)
							else:
								PacketLength=PacketDict[DeadByte]['structlength']
								NextIDByte=IDStruct.unpack(FullDataPacket[IDIndex+PacketLength:PacketLength+IDIndex+2])[0]
								# print(BytesToRemove,PacketLength,NextIDByte),
								if(NextIDByte in PacketDict):
									break
								
								
						# print([ord(byte) for byte in FullDataPacket])
						TotalBytesRemoved=TotalBytesRemoved+BytesToRemove
						FullDataPacket=FullDataPacket[BytesToRemove:]
						# print(FullDataPacket)
						# print([ord(byte) for byte in FullDataPacket])
						# exit()
						# print()
						# print("found something invalid",OutString)
						break
						
				else:
					break
				#break
			
		else:
			print('-'),
			# print("ERROR=================================================================================================="+str(ComputedChecksum)+" "+str(inCheckSum))
		# BitAr=BitArray(int=ord(curSector[0]),length=8)
		
		# print(FullDataPacket[-2])
		#print(inCheckSum[0])
		
	else:
		print('.'),
	curSector=inFileHandler.read(512)
	if(ValidSectorCount>90000000):
		break
# print([ord(byte) for byte in FullDataPacket])
FullStopTime=time.time()
FullElapsedTime=FullStopTime-FullStartTime
print("Full time to verify was %f" % FullElapsedTime)
print(TotalSectors,ValidSectorCount,ValidSectorCount*512,ValidPacketsFound,ValidChecksumedSectors,(ValidChecksumedSectors+0.0)/ValidSectorCount*100,TotalBytesRemoved)
inFileHandler.close()


#we now modify the file to include the ID
OutFileHandler.seek(IDSeekPos)
OutString=[format(i,'02') for i in GPSPacketForID[1:7]]+['{: f} '.format(i) for i in GPSPacketForID[7:9]]
print(OutString)
OutFileHandler.write("".join(OutString))

OutFileHandler.close()
exit()



