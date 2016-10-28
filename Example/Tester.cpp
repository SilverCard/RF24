#include <RF24.h>




int main(int argc, char** argv)
{
	if(argc >= 3)
	{

		int pin = atoi(argv[1]);		
		char * spiDevice = argv[2];
		
		printf("Testing device %s with pin %i.\n", spiDevice, pin);
		
		RF24 * radio = new RF24(pin, 0, 8000000, spiDevice);
		
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
		printf("Command line is Tester pin /dev/spidevX.X");
	}
}