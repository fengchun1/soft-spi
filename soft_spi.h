#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
	CS_ON=0,
	CS_OFF=1

}CS_Type;

typedef enum
{
	CPOL0_CPHA0 = 0,
	CPOL0_CPHA1,
	CPOL1_CPHA0,
	CPOL1_CPHA1,
}SPI_Mode;
typedef void (SPI_IO_INIT*) (void);
typedef void (SPI_MSCK_SET*)(uint8_t state);
typedef void (SPI_MOSI_SET*)(uint8_t state);
typedef void (SPI_MISO_SET*)(uint8_t state);
typedef void (SPI_NESS_SET*)(uint8_t state);
typedef uint8_t (SPI_MISO_READ*)(void);

typedef struct
{
	SPI_Mode mode;
	SPI_IO_INIT  spi_io_init;
	SPI_SCK_SET spi_sck_set;
	SPI_MOSI_SET spi_mosi_set;
	SPI_MISO_SET spi_miso_set;
	SPI_NESS_SET spi_ness_set;
	SPI_MISO_READ spi_miso_read;
	
	char* name;
}soft_spi_device_t;
void spi_writebyte(soft_spi_device_t *spi,uint8_t txbuf);
uint8_t spi_readbyte(soft_spi_device_t *spi);
#ifdef __cplusplus
}
#endif
