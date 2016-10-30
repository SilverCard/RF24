#include <RF24.h>

int main(int argc, char** argv)
{
	if(argc >= 4)
	{
		int cePin = atoi(argv[1]);		
		int csnPin = atoi(argv[2]);	
		char * spiDevice = argv[3];
		
		printf("Testing on spi device %s with CePin %i CsnPin %i.\n", spiDevice, cePin, csnPin );
		
		RF24 * radio = new RF24(cePin, csnPin, 8000000, spiDevice);
		
		radio->begin();
		radio->setPayloadSize(4);
		radio->setAutoAck(false);
		radio->setDataRate(RF24_250KBPS);
		radio->setPALevel(RF24_PA_MAX);
		radio->setChannel(125);
		radio->setCRCLength(RF24_CRC_8);
		radio->startListening();
		radio->printDetails();

		delete radio;				
	}
	else
	{
		printf("Command line is Tester CePin CsnPin /dev/spidevX.X\n");
	}
}