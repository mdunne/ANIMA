//#define Fcy  14754600
#define Fcy  18181818





void Delay( unsigned int delay_count );
void Delay_Us( unsigned int delayUs_count );

#define Delay200uS_count  (Fcy * 0.0002) / 1080
/*#define Delay_1mS_Cnt	  (Fcy * 0.001) / 2950
#define Delay_2mS_Cnt	  (Fcy * 0.002) / 2950
#define Delay_5mS_Cnt	  (Fcy * 0.005) / 2950
#define Delay_15mS_Cnt 	  (Fcy * 0.015) / 2950
#define Delay_1S_Cnt	  (Fcy * 1) / 2950 */

#define Delay_1mS_Cnt	  1
#define Delay_2mS_Cnt	  2
#define Delay_5mS_Cnt	  3
#define Delay_15mS_Cnt 	  4
#define Delay_1S_Cnt	  5
