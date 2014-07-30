import sys
import struct
import binascii
import time
from bitstring import BitArray
from operator import xor
from struct import unpack


def CalcCRC(Data,CRCPolynomial,CRCWidth,Seed=65535):
	#Need DataWidth
	#print(Data.bin)
	
	#Convert CRCWidth to bits not bytes
	CRCWidth=CRCWidth*8
	DataWidth=len(Data)+CRCWidth
	DataWidth=len(Data)
	#pad the data with zeros the size of the CRC
	# Data=Data+BitArray(int=0,length=CRCWidth)
	Data=Data
	
	#convert polynomial and shift the polynomial,add one to match form
	CRCPolynomial=BitArray(uint=CRCPolynomial,length=CRCWidth)
	# CRCPolynomial=BitArray(uint=CRCPolynomial,length=CRCWidth)+BitArray("0b1")
	
	#print(Data)
	#print(Data[-0])
	#print(Data.bin)
	#print(CRCPolynomial.bin)
	CRCOut=BitArray(uint=65535,length=CRCWidth)
	for iterator in range(0,DataWidth):
		#print(iterator)
		NewBit=Data[iterator]
		if(NewBit):
			CRCOut=CRCOut+BitArray("0b1")
		else:
			CRCOut=CRCOut+BitArray("0b0")
		RemovedBit=CRCOut[0]
		#print(RemovedBit)
		
		CRCOut=CRCOut[-CRCWidth:]
		# print(CRCOut.bin)
		if(RemovedBit):
			CRCOut=CRCOut^CRCPolynomial
		#extract the current set to be xor
		# CurDataSection=Data[iterator:iterator+CRCWidth+1]
		#FirstBit=CurDataSection[0]
		#we only perform crc on sections starting with 1
		# if FirstBit:
			# Data[iterator:iterator+CRCWidth+1]=xor(CurDataSection,CRCPolynomial)
			#print(CurDataSection.bin)
		#print(Data.bin)
	# print(CRCWidth)
	# print(Seed)
	
	#print(CRCOut.hex)
	#print(Data[-16:].bin)
	#print(Data.hex)
	
	return CRCOut.uint

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
	
	
testfilename="003.bin"

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
CRCTable=GenerateCRCTable(1,CRCPolynomial,CRCWidth)
TestString='0123456789'
RefCRC=CalcCRC(BitArray(bytes=TestString),CRCPolynomial,CRCWidth,0)
TableCRC=CalcCRCTable(TestString,CRCPolynomial,CRCWidth,1,CRCTable)
print(RefCRC,TableCRC)
# exit()
#print(HeaderValue)
# print(xor(HeaderValue,FooterValue))
#open the file and read until file is gone
inFile=open(testfilename,"rb")
curSector=inFile.read(512)
ValidSectorCount=0
usebitCRC=True
FullStartTime=time.time()

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
		FullDataPacket=(curSector[4:-4])
		TimeStart=time.time()
		if(usebitCRC):
			# print(type(FullDataPacket))
			PacketBitArray=BitArray(bytes=FullDataPacket)
			#print(PacketBitArray.hex)
			#print(xor(BitArray(int=ord("a"),length=8),BitArray(int=ord("b"),length=8)))
			ComputedChecksum=CalcCRC(PacketBitArray,CRCPolynomial,CRCWidth,0)
		else:
			ComputedChecksum=CalcCRCTable(FullDataPacket,CRCPolynomial,CRCWidth,1,CRCTable)
		TimeEnd=time.time()
		TimeElapsed=TimeEnd-TimeStart
		#print("asda")
		
		# print(ComputedChecksum, inCheckSum)
		#if(Compute
		# if(ComputedChecksum==inCheckSum):
			# print("Sector #%d Verified in %f seconds " % (ValidSectorCount,TimeElapsed))
		# else:
			# print("ERROR==================================================================================================")
		# BitAr=BitArray(int=ord(curSector[0]),length=8)
		
		# print(FullDataPacket[-2])
		#print(inCheckSum[0])
		
		
	curSector=inFile.read(512)
	#break
	
FullStopTime=time.time()
FullElapsedTime=FullStopTime-FullStartTime
print("Full time to verify was %f" % FullElapsedTime)
print(ValidSectorCount)
inFile.close()
exit()



