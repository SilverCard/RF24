/* 
 * File:   spi.cpp
 * Author: Purinda Gunasekara <purinda@gmail.com>
 * 
 * Created on 24 June 2012, 11:00 AM
 * 
 * Inspired from spidev test in linux kernel documentation
 * www.kernel.org/doc/Documentation/spi/spidev_test.c 
 */

#include "Spi.h"


Spi::Spi(char * spiDevice, int speed):_Fd(-1) {
	this->_SpiDevice = spiDevice;
	this->_Speed = speed;
}

Spi::Spi(char * spiDevice):_Fd(-1) {
	this->_Speed = RF24_SPIDEV_SPEED;
}

void Spi::Init()
{
	this->_Bits = 8;
	this->_Mode=0;
	
	int ret;   

	this->_Fd = open(this->_SpiDevice, O_RDWR);
    if (this->_Fd < 0)
    {
        throw "Can't open spi device.";
    }   

	/*
	 * spi mode
	 */
	ret = ioctl(this->_Fd, SPI_IOC_WR_MODE, &this->_Mode);
	if (ret == -1)
	{
		throw "can't set spi mode";		
	}

	ret = ioctl(this->_Fd, SPI_IOC_RD_MODE, &this->_Mode);
	if (ret == -1)
	{
		throw "can't set spi mode";		
	}
	
	/*
	 * bits per word
	 */
	ret = ioctl(this->_Fd, SPI_IOC_WR_BITS_PER_WORD, &this->_Bits);
	if (ret == -1)
	{
		throw "can't set bits per word";			
	}

	ret = ioctl(this->_Fd, SPI_IOC_RD_BITS_PER_WORD, &this->_Bits);
	if (ret == -1)
	{
		throw "can't set bits per word";					
	}
	/*
	 * max speed hz
	 */
	ret = ioctl(this->_Fd, SPI_IOC_WR_MAX_SPEED_HZ, &this->_Speed);
	if (ret == -1)
	{
		throw "can't set max speed hz";						
	}

	ret = ioctl(this->_Fd, SPI_IOC_RD_MAX_SPEED_HZ, &this->_Speed);
	if (ret == -1)
	{
		throw "can't set max speed hz";					
	}
}

uint8_t Spi::Transfer(uint8_t tx_)
{
	int ret;
  	uint8_t tx[1] = {tx_};
	uint8_t rx[1];
     
    //this->init();
	struct spi_ioc_transfer tr = {
	tr.tx_buf = (unsigned long)&tx[0],
	tr.rx_buf = (unsigned long)&rx[0],
	tr.len = 1,//ARRAY_SIZE(tx),
	tr.delay_usecs = 0,
	tr.cs_change=1,
	tr.bits_per_word = this->_Bits,
	};
	
    tr.speed_hz = this->_Speed,	

	ret = ioctl(this->_Fd, SPI_IOC_MESSAGE(1), &tr);
	if (ret < 1)
	{
		perror("can't send spi message");
		abort();		
	}

	return rx[0];
}

//void bcm2835_spi_transfernb(char* tbuf, char* rbuf, uint32_t len)
void Spi::Transfernb(char* tbuf, char* rbuf, uint32_t len)
{	
	int ret;

	struct spi_ioc_transfer tr = {
		tr.tx_buf = (unsigned long)tbuf,
		tr.rx_buf = (unsigned long)rbuf,
		tr.len = len,//ARRAY_SIZE(tx),
		tr.cs_change=1,
		tr.delay_usecs = 0,
		tr.bits_per_word = this->_Bits,
	};
	
    tr.speed_hz = this->_Speed,    

	ret = ioctl(this->_Fd, SPI_IOC_MESSAGE(1), &tr);
	if (ret < 1)
	{
		perror("can't send spi message");
		abort();		
	}
	//return rx[0];
}

void Spi::Transfern(char* buf, uint32_t len)
{
    Transfernb(buf, buf, len);
}


Spi::~Spi() {
    if (!(this->_Fd < 0))
	{
	    close(this->_Fd);
	}
}

