import sys
import struct
import binascii
import time

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
	
	
testfilename="000.bin"

HeaderValue=0xFB3B
FooterValue=0x5F86
HeaderFooterStruct=struct.Struct('<H')
CheckSumStruct=struct.Struct('<H')

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

# exit()
#print(HeaderValue)
# print(xor(HeaderValue,FooterValue))
#open the file and read until file is gone
inFile=open(testfilename,"rb")
curSector=inFile.read(512)
ValidSectorCount=0
ValidPacketsFound=0
usebitCRC=False
FullStartTime=time.time()
BytesToProcess=0
FullDataPacket=''
MagAccelStruct=struct.Struct('>H 33h') 
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
					if(FirstByte==34):
						print("Found a MagAccel Packet")
						if(len(FullDataPacket)>=68):
							MagAccelRawData=FullDataPacket[0:68]
							MagAccelDataPacket=MagAccelStruct.unpack(MagAccelRawData)
							ValidPacketsFound=ValidPacketsFound+1
							# print(MagAccelDataPacket)
							# print([byte.encode('hex') for byte in MagAccelRawData])
							# print(len(MagAccelRawData))
							FullDataPacket=FullDataPacket[68:]
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
		
		
	curSector=inFile.read(512)
	if(ValidSectorCount>30):
		break
# print([ord(byte) for byte in FullDataPacket])
FullStopTime=time.time()
FullElapsedTime=FullStopTime-FullStartTime
print("Full time to verify was %f" % FullElapsedTime)
print(ValidSectorCount)
inFile.close()
exit()



