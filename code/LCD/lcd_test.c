



#include "FSIO.h"
#include "p33FJ256GP710.h"
#include "stdio.h"
#include "overflowBuffer.h"
#include "uart2.h"
#include "id_code.h"
#include "data_logger.h"
#include "lcd.h"
#include "delay.h"
_FOSCSEL(FNOSC_FRC & IESO_ON);
_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_XT);
_FWDT(FWDTEN_OFF); 


#define FILESIZE 10000


//#define TESTOVERFLOWBUFFER


#if defined (__PIC24F__)

    _CONFIG2(IESO_OFF & FNOSC_PRIPLL & FCKSM_CSDCMD & OSCIOFNC_OFF & POSCMOD_HS)
    _CONFIG1(JTAGEN_OFF & GCP_OFF & GWRP_OFF & COE_OFF & ICS_PGx2 & FWDTEN_OFF)

#elif defined (__PIC32MX__)
    #pragma config FPLLMUL  = MUL_15        // PLL Multiplier
    #pragma config FPLLIDIV = DIV_2         // PLL Input Divider
    #pragma config FPLLODIV = DIV_1         // PLL Output Divider
    #pragma config FPBDIV   = DIV_1         // Peripheral Clock divisor
    #pragma config FWDTEN   = OFF           // Watchdog Timer
    #pragma config WDTPS    = PS1           // Watchdog Timer Postscale
    #pragma config FCKSM    = CSDCMD        // Clock Switching & Fail Safe Clock Monitor
    #pragma config OSCIOFNC = OFF           // CLKO Enable
    #pragma config POSCMOD  = HS            // Primary Oscillator
    #pragma config IESO     = OFF           // Internal/External Switch-over
    #pragma config FSOSCEN  = OFF           // Secondary Oscillator Enable (KLO was off)
    #pragma config FNOSC    = PRIPLL        // Oscillator Selection
    #pragma config CP       = OFF           // Code Protect
    #pragma config BWP      = OFF           // Boot Flash Write Protect
    #pragma config PWP      = OFF           // Program Flash Write Protect
    #pragma config ICESEL   = ICS_PGx2      // ICE/ICD Comm Channel Select
    #pragma config DEBUG    = ON            // Background Debugger Enable
#endif

   
int main (void)
{

   FSFILE * pointer=NULL;
   DWORD first_sector;
   SearchRec rec;
   pointer=NULL;
   unsigned char attributes;
   unsigned char size = 0, i;
        PLLFBD =38;
        CLKDIVbits.PLLPOST=0;
        CLKDIVbits.PLLPRE=0;
        __builtin_write_OSCCONH(0b011);
        __builtin_write_OSCCONL(0b01);
	while (OSCCONbits.COSC != 0b011);	// Wait for Clock switch to occur	
	while(OSCCONbits.LOCK != 1) {};
	UART2Init();
	printf("starting Integration test\r\n");
	//DataEEInit();
	int id=0;
	//id=Get_ID_Code();
	printf("ID: %u\r\n",id);
	//OFB_init(id);
	//Increment_ID_Code();
	#ifdef __DEBUG
		printf("Clock Switch Complete, Waiting For Media\r\n");
	#endif
	
   char filename[9];
   sprintf(filename,"%05d.bin",id);
   // Create a file
   TRISAbits.TRISA5=0;
   _RA5=0;
   Delay( Delay_5mS_Cnt);
   _RA5=1;
   Delay( Delay_1mS_Cnt);
   _RA5=0;
   Delay(Delay_1mS_Cnt);
   _RA5=1;
   Delay( Delay_1mS_Cnt);
   _RA5=0;
   Delay(Delay_2mS_Cnt);
   _RA5=1;
   
    Delay( Delay_1mS_Cnt);
   _RA5=0;
   Delay(Delay_15mS_Cnt);
   _RA5=1;
   
       Delay( Delay_1mS_Cnt);
   _RA5=0;
   Delay_Us(Delay_15mS_Cnt);
   _RA5=1;
   
   printf("filename will be: %s\r\n",filename);
   //while(1);
   Init_LCD();
   home_clr();
   home_it();
   puts_lcd((unsigned char*) &filename[0],9);
   //waits for a card to be inserted
   	while (!MDD_MediaDetect());
	#ifdef __DEBUG
		printf("Media Found, Waiting for FSinit\r\n");
	#endif
   // Initialize the library
   while (!FSInit());
   while(pointer==NULL)
   {
   		pointer = FSfopen (filename, "w");
   }
   #ifdef __DEBUG
   	printf("File Has been opened\r\n");
   #endif		
	
	while(1)
	{
		Service_Spi(pointer);
	}	
	//printf("stuipd thing");
	//TRISD=0x0FF;
	//setting up pins to show on usb debugger
	TRISDbits.TRISD6=1;
	TRISAbits.TRISA7=0;
	TRISAbits.TRISA6=0;
	TRISAbits.TRISA5=0;
	TRISAbits.TRISA4=0;
	TRISGbits.TRISG0=0;
	AD1PCFGLbits.PCFG0=1;	
	//LATA=1;
	//_LATA4=1;
	//_RA7=1;
	//_LATA6=1;
	
	//_LATA5=1;
	//_LATA7=1;
	
	//printf("they should be on now");
	//while(1);
	//LATAbits.LATA7=0;
	//TRISB=0xFFFF;
	//AD1PCFGLbits.PCFG1=1;	
	//Service_Spi();
	/*#ifdef __DEBUG
		printf("Clock Switch Complete, Waiting For Media\r\n");
	#endif
	//waits for a card to be inserted
   while (!MDD_MediaDetect());
   
   
	#ifdef __DEBUG
		printf("Media Found, Waiting for FSinit\r\n");
	#endif
   // Initialize the library
   while (!FSInit());
	char temp;
	int character_count,remove_success;
	character_count=0;
   // Create a file
   printf("starting up\r\n");
   remove_success=FSremove("WRITE.TXT");
   printf("Removal of prev: %d\r\n",remove_success);
   pointer = FSfopen ("WRITE.TXT", "w");

   if (pointer == NULL)
   {
	   #ifdef __DEBUG
	   	printf("File open failed\r\n");
	   #endif
      while(1);
   }   

   printf("waiting for operation\r\n");
   printf("in file resize_test\r\n");
   
   
   DWORD sizeinbytes;
   //need to convert from number of sectors to number of bytes and allocate that much space
   sizeinbytes=(DWORD)FILESIZE*(DWORD)512;
   printf("Chew Fat: %lu\r\nChew Fat Sectors: %d\r\n",CHEW_FAT_SIZE,CHEW_FAT_SIZE_IN_SECTORS);
   //sizeinbytes=3774873*(DWORD)512;
   //allocate_size(sizeinbytes,pointer,FALSE);
   //FSfclose(pointer);*/
   /*FILEallocate_multiple_clusters(pointer,24);
   FAT_print_cluster_chain(pointer->cluster, pointer->dsk);
   FILEallocate_multiple_clusters(pointer,24);
   FAT_print_cluster_chain(pointer->cluster, pointer->dsk);
   int numclus,numcount;
   //DWORD clusttemp;
   printf("First CLuster in main: %lu\r\n",get_First_Sector(pointer));
   for (numclus=0;numclus<48;numclus++)
   {
		for(numcount=0;numcount<512;numcount++)
		{
		   test_array[numcount]=numclus+48;
		}
		MDD_SDSPI_SectorWrite(get_First_Sector(pointer)+numclus,test_array,FALSE);
	}*/
   //FILEallocate_multiple_clusters(pointer,24);
   //FILEallocate_multiple_clusters(pointer,24);
   //FILEallocate_multiple_clusters(pointer,CHEW_FAT_SIZE_IN_SECTORS);
   //FSfclose(pointer);
   //FILEallocate_multiple_clusters(pointer,4096);
   //FSfclose(pointer);
   //FILEallocate_multiple_clusters(pointer,1024);
   //FILEallocate_multiple_clusters(pointer,1024);
   
   //FSfseek(pointer,0,SEEK_SET);
   first_sector=get_First_Sector(pointer);
   set_First_Sector(first_sector);
   DWORD erasure;
   OFB_init(0x1f1f);
   //FSfclose(pointer);
   //MDD_ShutdownMedia();
   printf("done with file allocation\r\n");
   #ifdef DMAON
   #else
   #endif
      
      //while(UART2IsEmpty());
      //temp=UART2GetChar();
      //write_array[character_count]=temp;
      //character_count++;
    while(1)
    {
	    Service_Spi(pointer);
	} 
	/*while(temp!='+')
	{
		if(character_count<512)
		{
			if(!UART2IsEmpty())
			{
				temp=UART2GetChar();
				write_array[character_count]=temp;
				character_count++;
				//printf("%08d\r",character_count);
			}
		}
		else
		{
		FSfwrite(write_array,1,character_count, pointer);
		character_count=0;
		}
	}*/
	 //FSfwrite(write_array,1,character_count, pointer);
   	//FSfwrite(sendBuffer,1,21, pointer);
   	unsigned int buffer[512];
   	char buffersign;
   	//bufferreturn(buffer);
   	while(1)
   	{
	 /*buffersign=bufferreturn(buffer);
	 if(buffersign==1)
	 {
		 //FSfwrite(buffer,1,512,pointer);
	 }*/
   	if(!PORTDbits.RD6)
   	{   
	   	DMA0CONbits.CHEN=0;	
		//FSfclose(pointer);
		DMA0CONbits.CHEN=0;
		printf("done with operations\r\n");
		MDD_ShutdownMedia();
		while(1){}
	}
	}
	/*
   // Write 21 1-byte objects from sendBuffer into the file
   if (FSfwrite (sendBuffer, 1, 21, pointer) != 21)
      while(1);

   // FSftell returns the file's current position
   if (FSftell (pointer) != 21)
      while(1);

   // FSfseek sets the position one byte before the end
   // It can also set the position of a file forward from the
   // beginning or forward from the current position
   if (FSfseek(pointer, 1, SEEK_END))
      while(1);

   // Write a 2 at the end of the string
   if (FSfwrite (send2, 1, 1, pointer) != 1)
      while(1);

   // Close the file
   if (FSfclose (pointer))
      while(1);

   // Create a second file
   pointer = FSfopen ("FILE2.TXT", "w");
   if (pointer == NULL)
      while(1);

   // Write the string to it again
   if (FSfwrite ((void *)sendBuffer, 1, 21, pointer) != 21)
      while(1);

   // Close the file
   if (FSfclose (pointer))
      while(1);

   // Open file 1 in read mode
   pointer = FSfopen ("FILE1.TXT", "r");
   if (pointer == NULL)
      while(1);

   // Read one four-byte object
   if (FSfread (receiveBuffer, 4, 1, pointer) != 1)
      while(1);

   // Check if this is the end of the file- it shouldn't be
   if (FSfeof (pointer))
      while(1);

   // Close the file
   if (FSfclose (pointer))
      while(1);

   // Make sure we read correctly
   if ((receiveBuffer[0] != 'T') ||
         (receiveBuffer[1] != 'h')  ||
         (receiveBuffer[2] != 'i')  ||
         (receiveBuffer[3] != 's'))
   {
      while(1);
   }

   // Create a small directory tree
   // Beginning the path string with a '.' will create the tree in
   // the current directory.  Beginning with a '..' would create the
   // tree in the previous directory.  Beginning with just a '\' would
   // create the tree in the root directory.  Beginning with a dir name
   // would also create the tree in the current directory
   if (FSmkdir (".\\ONE\\TWO\\THREE"))
      while(1);

   // Change to directory THREE in our new tree
   if (FSchdir ("ONE\\TWO\\THREE"))
      while(1);

   // Create another tree in directory THREE
   if (FSmkdir ("FOUR\\FIVE\\SIX"))
      while(1);

   // Create a third file in directory THREE
   pointer = FSfopen ("FILE3.TXT", "w");
   if (pointer == NULL)
      while(1);

   // Get the name of the current working directory it should be "\ONE\TWO\THREE"
   pointer2 = FSgetcwd (path, count);
   if (pointer2 != path)
      while(1);

   // Simple string length calculation
   i = 0;
   while(*(path + i) != 0x00)
   {
      size++;
      i++;
   }
   // Write the name to FILE3.TXT
   if (FSfwrite (path, size, 1, pointer) != 1)
      while(1);

   // Close the file
   if (FSfclose (pointer))
      while(1);

   // Create some more directories
   if (FSmkdir ("FOUR\\FIVE\\SEVEN\\..\\EIGHT\\..\\..\\NINE\\TEN\\..\\ELEVEN\\..\\TWELVE"))
      while(1);*/

   /*******************************************************************
      Now our tree looks like this

      \ -> ONE -> TWO -> THREE -> FOUR -> FIVE -> SIX
                                                 -> SEVEN
                                                 -> EIGHT
                                            NINE -> TEN
                                                 -> ELEVEN
                                                 -> TWELVE
   ********************************************************************/

   // This will delete only directory eight
   // If we tried to delete directory FIVE with this call, the FSrmdir
   // function would return -1, since FIVE is non-empty
   /*if (FSrmdir ("\\ONE\\TWO\\THREE\\FOUR\\FIVE\\EIGHT", FALSE))
      while(1);

   // This will delete directory NINE and all three of its sub-directories
   if (FSrmdir ("FOUR\\NINE", TRUE))
      while(1);

   // Change directory to the root dir
   if (FSchdir ("\\"))
      while(1);

   // Set attributes
   attributes = ATTR_DIRECTORY | ATTR_ARCHIVE | ATTR_READ_ONLY | ATTR_HIDDEN;
   // Find the first TXT file with any (or none) of those attributes that
   // has a name beginning with the letters "FILE"
   // These functions are more useful for finding out which files are
   // in your current working directory
   if (FindFirst ("FILE*.TXT", attributes, &rec))
      while(1);

   // Keep finding files until we get FILE2.TXT
   while(rec.filename[4] != '2')
   {
      if (FindNext (&rec))
         while(1);
   }

   // Delete file 2
   if (FSremove (rec.filename))
      while(1);*/

MDD_ShutdownMedia();
/*********************************************************************
   The final contents of our card should look like this:
   \ -> FILE1.TXT
      -> ONE       -> TWO -> THREE -> FILE3.TXT
                                   -> FOUR      -> FIVE -> SIX
                                                        -> SEVEN

*********************************************************************/


   while(1);
}








