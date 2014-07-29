import sys
import struct
import binascii
import time
from bitstring import BitArray
from operator import xor
from struct import unpack


def CalcCRC16(Data,CRCPolynomial,CRCWidth,Seed=0):
	#Need DataWidth
	#print(Data.bin)
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
		#print(CRCOut.bin)
		if(RemovedBit):
			CRCOut=xor(CRCOut,CRCPolynomial)
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


testfilename="003.bin"

HeaderValue=0xFB3B
FooterValue=0x5F86
HeaderFooterStruct=struct.Struct('<H')
CheckSumStruct=struct.Struct('<H')

CRCPolynomial=0x48A1
CRCWidth=16
CRCSeed=0xffff

#we modify the polynomial and the width according to crc specs
#CRCPolynomial=CRCPolynomial<<1+1
#CRCWidth=CRCWidth+1
CalcCRC16(BitArray('0x55565758595A5B5C5D5E5F606162636465666768'),0x8005,16,0)
#print(HeaderValue)
# print(xor(HeaderValue,FooterValue))
#open the file and read until file is gone
inFile=open(testfilename,"rb")
curSector=inFile.read(512)
ValidSectorCount=0
while curSector!='':

	#check first for header and footer for verification of valid sector
	inHeaderValue=HeaderFooterStruct.unpack(curSector[:2])
	inFooterValue=HeaderFooterStruct.unpack(curSector[-2:])
	if inHeaderValue[0]==HeaderValue and inFooterValue[0]==FooterValue:
		print("Valid Sector Found")
		ValidSectorCount=ValidSectorCount+1
		#extract checksum and calculate new checksum
		inCheckSum=CheckSumStruct.unpack(curSector[-4:-2])[0]
		
		#need the data portion as a bytearray
		#removing header/timestamp from beginning and footer/checksum from the end
		# PacketBitArray=BitArray(int=unpack('b',curSector[4])[0],length=8)
		#print(PacketBitArray)
		FullDataPacket=(curSector[4:-4])
		PacketBitArray=BitArray(bytes=FullDataPacket)
		#print(PacketBitArray.hex)
		#print(xor(BitArray(int=ord("a"),length=8),BitArray(int=ord("b"),length=8)))
		TimeStart=time.time()
		ComputedChecksum=CalcCRC16(PacketBitArray,0x8005,16,0)
		TimeEnd=time.time()
		TimeElapsed=TimeEnd-TimeStart
		#print("asda")
		
		# print(ComputedChecksum, inCheckSum)
		#if(Compute
		if(ComputedChecksum==inCheckSum):
			print("Sector #%d Verified in %f seconds " % (ValidSectorCount,TimeElapsed))
		else:
			print("ERROR==================================================================================================")
		# BitAr=BitArray(int=ord(curSector[0]),length=8)
		
		# print(FullDataPacket[-2])
		#print(inCheckSum[0])
		
		
	curSector=inFile.read(512)
	# break

print(ValidSectorCount)
inFile.close()





exit()



# if len(sys.argv) < 3 :
    # print("Please enter 3 arguments: the file number, a file to read from, and a file to write to.")
    # exit()


dataLine = struct.Struct('<h h h h h h f i ')
ID = struct.Struct('<h')

readFile = open(sys.argv[2], "rb") # open first file to read
writeFile = open(sys.argv[3], "w") # open second file to write

packedData = readFile.read(512)
idNumber = ID.unpack(packedData[0:2])
idCompare = int(sys.argv[1])
writeFile.write("%AccelX\tAccelY\tAccelZ\tMagX\tMagY\tMagZ\tTemp\tTime\n".format())

while idNumber[0] == idCompare: # main loop
	for i in range(0,25):
		line = packedData[4+20*i:24+20*i]
		unpackedData = dataLine.unpack(line);
		#print("{}\t{}\t{}\t{}\t{}\t{}\t{}\t{}".format(unpackedData[0], unpackedData[1], unpackedData[2], unpackedData[3], unpackedData[4], unpackedData[5], unpackedData[6], unpackedData[7]))
		print("{}".format(unpackedData[7]))
		writeFile.write("{}\t{}\t{}\t{}\t{}\t{}\t{}\t{}\n".format(unpackedData[0], unpackedData[1], unpackedData[2], unpackedData[3], unpackedData[4], unpackedData[5], unpackedData[6], unpackedData[7]))
	packedData = readFile.read(512)
	idNumber = ID.unpack(packedData[0:2])

readFile.close()
writeFile.close()