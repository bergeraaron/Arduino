#include <SmartResponseXE.h>
#include "RadioFunctions.h"

//channels 11-26

uint8_t channels[16] = {11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26};

uint8_t packets[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

uint8_t cnl_x_offset[16] = {0,0,0,0,0,0,0,0,180,180,180,180,180,180,180,180};
uint8_t cnl_y_offset[16] = {20,30,40,50,60,70,80,90,20,30,40,50,60,70,80,90};

void setup()
{
	// CS, D/C, RESET
	SRXEInit(0xe7, 0xd6, 0xa2); // initialize display
	SRXEWriteString(0,0,"SmartResponseXE Sniffer", FONT_NORMAL, 3, 0); // draw large black text at x=0,y=120, fg=3, bg=0

	print_channel_setup();
}

void print_channel_setup()
{
	char lcd_out[32];
	for(int i=0;i<16;i++)
	{
		//print out the number of packets;
		sprintf(lcd_out,"[%d] # Pkts:%d",channels[i],packets[i]);
		SRXEWriteString(cnl_x_offset[i],cnl_y_offset[i],lcd_out, FONT_NORMAL, 3, 0);
	}	
}

void loop()
{
	char lcd_out[32];
	char packet_out[512];
	int cnl_ctr = 0;
	char rf_byte=0x00;
	char rf_packet[128];
	int rfctr = 0;
	//loop through the channels and see if we are seeing any data
	while(1)
	{
		//cnl_ctr = 0;
		sprintf(lcd_out,"Sniffing Channel:%d",channels[cnl_ctr]);
		SRXEWriteString(0,10,lcd_out, FONT_NORMAL, 3, 0); // draw large black text at x=0,y=120, fg=3, bg=0
		delay(10);
		//set channel
		rfChannel(channels[cnl_ctr]);
		delay(10);//delay before we look for data
		for(int ctr=0;ctr<60;ctr++)
		{
			if (rfAvailable())  // If data receievd on radio...
			{
				rf_byte = rfRead();
				while(rf_byte != 255)
				{
					rf_packet[rfctr] = rf_byte;rfctr++;
				}

				sprintf(packet_out,"%02x %02x %02x %02x %02x %02x",rf_packet[0],rf_packet[1],rf_packet[2],rf_packet[3],rf_packet[4],rf_packet[5]);
				SRXEWriteString(0, 120, packet_out, FONT_NORMAL, 3, 0);
				//SRXEWriteString(0,120,"Got a Packet", FONT_NORMAL, 3, 0);
				packets[cnl_ctr]++;
			}
			delay(500); 
		}

		//print out the number of packets;
		sprintf(lcd_out,"[%d] # Pkts:%d",channels[cnl_ctr],packets[cnl_ctr]);
		SRXEWriteString(cnl_x_offset[cnl_ctr],cnl_y_offset[cnl_ctr],lcd_out, FONT_NORMAL, 3, 0);
		cnl_ctr++;
		if(cnl_ctr == 16)//loop back around
			cnl_ctr=0;
	}

}
