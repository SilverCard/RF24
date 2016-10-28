/* 
 * File:   spi.h
 * Author: Purinda Gunasekara <purinda@gmail.com>
 * 
 * Created on 24 June 2012, 11:00 AM
 */

#ifndef SPI_H
#define	SPI_H

/**
 * @file spi.h
 * \cond HIDDEN_SYMBOLS
 * Class declaration for SPI helper files
 */
 
 /**
 * Example GPIO.h file
 *
 * @defgroup SPI SPI Example
 *
 * See RF24_arch_config.h for additional information
 * @{
 */
 
#include <string>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <inttypes.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

#ifndef RF24_SPIDEV_SPEED
/* 8MHz as default */
#define RF24_SPIDEV_SPEED 8000000
#endif

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

using namespace std;

class Spi {
public:
	
	/**
	* SPI constructor
	*/	 
	Spi(char * spiDevice, int speed);
	
	/**
	* SPI constructor
	*/	 
	Spi(char * spiDevice);
	
	/**
	* Start SPI
	*/
	void Init();
	
	/**
	* Transfer a single byte
	* @param tx_ Byte to send
	* @return Data returned via spi
	*/
	uint8_t Transfer(uint8_t tx_);
	
	/**
	* Transfer a buffer of data
	* @param tbuf Transmit buffer
	* @param rbuf Receive buffer
	* @param len Length of the data
	*/
	void Transfernb(char* tbuf, char* rbuf, uint32_t len);

	/**
	* Transfer a buffer of data without an rx buffer
	* @param buf Pointer to a buffer of data
	* @param len Length of the data
	*/	
	void Transfern(char* buf, uint32_t len);
	
	virtual ~Spi();

private:

	/** Default SPI device */
	char * _SpiDevice;
	/** SPI Mode set */
	uint8_t _Mode;
	/** word size*/
	uint8_t _Bits;
	/** Set SPI speed*/
	uint32_t _Speed;
	int _Fd;
};

/**
 * \endcond
 */
/*@}*/
#endif	/* SPI_H */

