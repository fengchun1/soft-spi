#include "soft_spi.h"

void spi_io_init()
{
}
void spi_sck_set(uint8_t state)
{
	
}
void spi_mosi_set(uint8_t state)
{
	
}

void spi_miso_set(uint8_t state)
{
	
}
void spi_ness_set(uint8_t state)
{
	
}
uint8_t spi_miso_read(void)
{
}
soft_spi_device_t spi1 =
{
	CPOL0_CPHA0,
	spi_io_init,
	spi_sck_set,
	spi_mosi_set,
	spi_miso_set,
	spi_ness_set,
	spi_miso_read,
	"sensor"
	
}

void spi_writebyte(soft_spi_device_t *spi,uint8_t txbuf)
{
	switch(spi->mode)
	{
		case CPOL0_CPHA0:
			for(uint8_t n=0;n<8;n++)
			{
				spi->spi_sck_set(0);
				if(txbuf&0x80)
					spi->spi_mosi_set(1);
				else 
					spi->spi_mosi_set(0);
				txbuf<<=1;
				spi->spi_sck_set(1);
			}
		break;
		case CPOL0_CPHA1:
		 spi->spi_sck_set(0);
		 for(uint8_t n=0;n<8;n++)
		 {
			spi->spi_sck_set(1);
			if(txbuf&0x80)
				spi->spi_mosi_set(1);
			else 
				spi->spi_mosi_set(0);
			txbuf<<=1;
			spi->spi_sck_set(0);
		 }

		break;
		case CPOL1_CPHA0:
		 for(uint8_t n=0;n<8;n++)
		 {
			spi->spi_sck_set(1);
			if(txbuf&0x80)
				spi->spi_mosi_set(1);
			else 
				spi->spi_mosi_set(0);
			txbuf<<=1;
			spi->spi_sck_set(0);
		 }
		break;
		case CPOL1_CPHA1:
			spi->spi_sck_set(1);
			for(uint8_t n=0;n<8;n++)
			{
				spi->spi_sck_set(0);
				if(txbuf&0x80)
					spi->spi_mosi_set(1);
				else 
					spi->spi_mosi_set(0);
				txbuf<<=1;
				spi->spi_sck_set(1);
			}
		break;
			defaut:
			//可报错提示
			break;
	}

}


uint8_t spi_readbyte(soft_spi_device_t *spi)
{
	uint8_t rxbuf;
	switch(spi->mode)
	{
		case CPOL0_CPHA0:	
		for(uint8_t n=0;n<8;n++)
		{
			spi->spi_sck_set(0);
			rxbuf<<=1;
			if(MISO_IN)
				rxbuf|=0x01;
			else 
				rxbuf&=0xfe;
			spi->spi_sck_set(1);
		}
		break;
		case CPOL0_CPHA1:
			spi->spi_sck_set(0);
			for(uint8_t n=0; n<8; n++)
			{
				spi->spi_sck_set(1);
				rxbuf<<=1;
				if(MISO_IN)
					rxbuf|=0x01;
				else 
					rxbuf&=0xfe;
				spi->spi_sck_set(0);
			}
		break;
		case CPOL1_CPHA0:
			for(uint8_t n=0;n<8;n++)
			 {
				spi->spi_sck_set(1);;
				rxbuf<<=1;
				if(MISO_IN)rxbuf|=0x01;
				else rxbuf&=0xfe;
				spi->spi_sck_set(0);
			 }
			spi->spi_sck_set(1);
		break;
		case CPOL1_CPHA1:
			spi->spi_sck_set(1);
			for(uint8_t n=0;n<8;n++)
			{ 
				spi->spi_sck_set(0);
				rxbuf<<=1;
				if(MISO_IN)
				rxbuf|=0x01;
				else 
				rxbuf&=0xfe;
				spi->spi_sck_set(1);
			}
		break;
		defaut:
		break;
	}
	return rxbuf;
}
































