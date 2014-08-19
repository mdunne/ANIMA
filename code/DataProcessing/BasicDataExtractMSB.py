import sys
import struct
import binascii
import time
import ConfigParser


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
	

def WriteNewPacketConfiguration(PacketID,StringName,StructString,StructLength,CommentString,ConfigFileName="PacketIDs.cfg"):
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
	config.set(SectionName,'structlength',str(StructLength))
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
	

testfilename="000.bin"

HeaderValue=0xFB3B
FooterValue=0x5F86
HeaderFooterStruct=struct.Struct('<H')
CheckSumStruct=struct.Struct('<H')
TimeStampStruct=struct.Struct('<H')
ConfigFileName='PacketIDs.cfg'
CRCPolynomial=0x8005
CRCWidth=2  #in bytes
CRCSeed=0xffff

#we modify the polynomial and the width according to crc specs
#CRCPolynomial=CRCPolynomial<<1+1
#CRCWidth=CRCWidth+1
TimeStart=time.time()
CRCTable=GenerateCRCTable(1,CRCPolynomial,CRCWidth)
TimeEnd=time.time()
TimeElapsed=TimeEnd-TimeStart
# print(TimeElapsed)
TestString='0123456789'
CurTimeStamp=-1
# exit()
#print(HeaderValue)
#open the file and read until file is gone
inFileHandler=open(testfilename,"rb")

OutFileName='parsed_'+testfilename
OutFileHandler=open(OutFileName,"w")


curSector=inFileHandler.read(512)
ValidSectorCount=0
ValidPacketsFound=0
usebitCRC=False
FullStartTime=time.time()
BytesToProcess=0
FullDataPacket=''
MagAccelStruct=struct.Struct('<H 33h')

# WriteNewPacketConfiguration(34,'Mag_Accel_Packet','<H 33h',68,'this is the line for the top of the file',ConfigFileName)
PacketDict=BuildPacketDictionary(ConfigFileName)

for key in PacketDict:
	CurEntry=PacketDict[key]
	curEntryKey=key
	for key in CurEntry:
		print(curEntryKey,key,CurEntry[key])
# print(PacketConfigs.get('34','stringname'))

# exit()
while curSector!='':

	#check first for header and footer for verification of valid sector
	inHeaderValue=HeaderFooterStruct.unpack(curSector[:2])
	inFooterValue=HeaderFooterStruct.unpack(curSector[-2:])
	if inHeaderValue[0]==HeaderValue and inFooterValue[0]==FooterValue:
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
		
			# we need to find the new time stamp but not update the value
			PossTimeStamp=TimeStampStruct.unpack(curSector[2:4])[0]
			
			#the first timestamp needs to be set regardless of packet state
			if(CurTimeStamp==-1):
				CurTimeStamp=PossTimeStamp
			# print("Sector #%d Verified in %f seconds " % (ValidSectorCount,TimeElapsed))
			CurSectorByteCount=0
			BytesToProcess=BytesToProcess+len(IncomingDataPacket)
			FullDataPacket=FullDataPacket+IncomingDataPacket
			ValidPacketsFound=0
			# print(BytesToProcess)
			# print([ord(byte) for byte in FullDataPacket])
			while(True):
				# print(len(FullDataPacket),ord(FullDataPacket[0]))
				if(len(FullDataPacket)>=2):
					FirstByte=ord(FullDataPacket[0])
					# pic can't pack 8 bits in, need to upshift to 16 bits for id for now fudged as they are the wrong endedness
					FirstByte=struct.Struct('H').unpack(FullDataPacket[0:2])[0]

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
						# BytesToProcess=BytesToProcess-68
					else:
						break
						print("found something invalid")
				else:
					break
				#break
			
		else:
			print("ERROR==================================================================================================")
		# BitAr=BitArray(int=ord(curSector[0]),length=8)
		
		# print(FullDataPacket[-2])
		#print(inCheckSum[0])
		
		
	curSector=inFileHandler.read(512)
	if(ValidSectorCount>4):
		break
# print([ord(byte) for byte in FullDataPacket])
FullStopTime=time.time()
FullElapsedTime=FullStopTime-FullStartTime
print("Full time to verify was %f" % FullElapsedTime)
print(ValidSectorCount)
inFileHandler.close()
OutFileHandler.close()
exit()



