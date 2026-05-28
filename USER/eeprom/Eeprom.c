/**
 *****************************************************************************
  *                                   Update
  * @Version : V1.0
  * @By      : dengzhiqin
  * @Date    : 2017 / 12 / 05
  * @Brief   : driver of eeprom
  *
  *****************************************************************************
**/
#include "includes.h"

#if (_CHIP_EEPROM_TYPE_USE != _EEPROM_CHIP_NO_USE)

extern SemaphoreHandle_t xSemaphore_IIC[NUM_OF_I2C_BUS_MAX];

void eeprom_write ( uint32_t Address, uint8_t* pDatas, uint32_t length )
{
#if 1

	uint8_t dev_addr, first_page_bytes =0, last_page_bytes = 0;
	uint16_t pages_number = 0, i;
	uint32_t remain_wr_size = 0;

#if _SYSTEM_SUPPORT_RTOS
#ifdef N32G45X
	xSemaphoreTake ( xSemaphore_IIC[_I2C_TABLE_INDEX_EEPROM], /*portMAX_DELAY*/20 );
#else
	xSemaphoreTake ( xSemaphore_IIC[_I2C_TABLE_INDEX_EEPROM], portMAX_DELAY );
#endif
#endif

	//dbg_printf ( "AT24CM01_MAX_ADDR:%d \r\n",AT24CM01_MAX_ADDR );
	//dbg_printf ( "AT24CM01_PAGE_SIZE:%d\r\n",AT24CM01_PAGE_SIZE );

	if ( ( Address >= AT24CM01_MAX_ADDR ) || ( ( Address+length ) >=AT24CM01_MAX_ADDR ) )
	{
		Msg_Eep ( ( "EEPROM OPERATE ADDRESS OUT OF RANGE!\r\n" ) );
		return;
	}

	//dbg_printf ( "step.1 AT24CM01_PAGE_SIZE:%d,( Address <MOD> AT24CM01_PAGE_SIZE ):%d LINE:%d\r\n",AT24CM01_PAGE_SIZE, ( Address%AT24CM01_PAGE_SIZE ) ,__LINE__);
	first_page_bytes = AT24CM01_PAGE_SIZE - ( Address%AT24CM01_PAGE_SIZE );
	if ( length>first_page_bytes )
	{
		remain_wr_size = length - first_page_bytes;
		//dbg_printf ( "step.2-1 length>first_page_bytes - TRUE first_page_bytes:%d remain_wr_size:%d LINE:%d\r\n",first_page_bytes,remain_wr_size ,__LINE__);
		if ( remain_wr_size >= AT24CM01_PAGE_SIZE )
		{
			//dbg_printf ( "step.3-1 remain_wr_size >= AT24CM01_PAGE_SIZE - TRUE LINE:%d \r\n" ,__LINE__);
			pages_number = remain_wr_size/AT24CM01_PAGE_SIZE;
			last_page_bytes =remain_wr_size - ( pages_number*AT24CM01_PAGE_SIZE );
			//dbg_printf ( "step.4 first_page_bytes:%d,pages_number:%d,last_page_bytes:%d LINE:%d \r\n",first_page_bytes,pages_number,last_page_bytes ,__LINE__);
		}
		else
		{
			//dbg_printf ( "step.3-2 remain_wr_size >= AT24CM01_PAGE_SIZE - FALSE first_page_bytes:%d remain_wr_size:%d LINE:%d \r\n",first_page_bytes,remain_wr_size ,__LINE__);
			last_page_bytes = remain_wr_size;
		}
	}
	else
	{
		//dbg_printf ( "step.2-2 length>first_page_bytes - FALSE first_page_bytes = length  length:%d LINE:%d \r\n",length ,__LINE__);
		first_page_bytes = length;
	}

	dev_addr = ( ( ( Address& ( 1<<16 ) ) == ( 1<<16 ) ) <<1 ) | DEVICE_ADDR_AT24CM01;
	//dbg_printf ( "_I2C_TABLE_INDEX_EEPROM:%d dev_addr: 0x%x Address:0x%x,length:%d LINE:%d \r\n",_I2C_TABLE_INDEX_EEPROM,dev_addr,Address,length ,__LINE__);
	//v_hexdump ( pDatas,first_page_bytes );
	i2c_write_bytes ( _I2C_TABLE_INDEX_EEPROM, dev_addr, ( uint16_t ) ( Address&0xFFFF ), \
	                  pDatas, first_page_bytes, TRUE );
//	delay_ms(AT24CM01_DELAY);   // ÑÓ³ÙÓÐÊ±ºò²»¹»5ms
	delay_us ( AT24CM01_DELAY*1000 );
	Address += first_page_bytes;
	pDatas += first_page_bytes;

	if ( pages_number > 0 )
	{
		for ( i=0; i<pages_number; i++ )
		{
			dev_addr = ( ( ( Address& ( 1<<16 ) ) == ( 1<<16 ) ) <<1 ) | DEVICE_ADDR_AT24CM01;
			//dbg_printf ( "pages_number > 0 LINE:%d \r\n" ,__LINE__);
			//v_hexdump ( pDatas,AT24CM01_PAGE_SIZE );
			i2c_write_bytes ( _I2C_TABLE_INDEX_EEPROM, dev_addr, ( uint16_t ) ( Address&0xFFFF ), \
			                  pDatas,	AT24CM01_PAGE_SIZE,	TRUE );
			delay_ms ( AT24CM01_DELAY );
			Address += AT24CM01_PAGE_SIZE;
			pDatas += AT24CM01_PAGE_SIZE;
		}
	}

	if ( last_page_bytes > 0 )
	{
		dev_addr = ( ( ( Address& ( 1<<16 ) ) == ( 1<<16 ) ) <<1 ) | DEVICE_ADDR_AT24CM01;
		//dbg_printf ( "last_page_bytes > 0 LINE:%d \r\n" ,__LINE__);
		//v_hexdump ( pDatas,last_page_bytes );
		i2c_write_bytes ( _I2C_TABLE_INDEX_EEPROM, dev_addr, ( uint16_t ) ( Address&0xFFFF ), \
		                  pDatas, last_page_bytes, TRUE );
//		delay_ms(AT24CM01_DELAY);
		delay_us ( AT24CM01_DELAY*1000 );
	}

#if _SYSTEM_SUPPORT_RTOS
	xSemaphoreGive ( xSemaphore_IIC[_I2C_TABLE_INDEX_EEPROM] );
#endif

#endif
}

void eeprom_read ( uint32_t Address, uint8_t* pDatas, uint32_t length )
{
	uint8_t dev_addr;

#if _SYSTEM_SUPPORT_RTOS
	xSemaphoreTake ( xSemaphore_IIC[_I2C_TABLE_INDEX_EEPROM], portMAX_DELAY );
#endif
	if ( ( Address >= AT24CM01_MAX_ADDR ) || ( ( Address+length ) >=AT24CM01_MAX_ADDR ) )
	{
		Msg_Eep ( ( "EEPROM OPERATE ADDRESS OUT OF RANGE!\r\n" ) );
		return;
	}

	dev_addr = ( ( ( Address& ( 1<<16 ) ) == ( 1<<16 ) ) <<1 ) | DEVICE_ADDR_AT24CM01; // = DEVICE_ADDR_AT24CM01
	i2c_read_bytes ( _I2C_TABLE_INDEX_EEPROM, dev_addr, ( uint16_t ) ( Address&0xFFFF ), \
	                 pDatas,	length,	TRUE );
#if _SYSTEM_SUPPORT_RTOS
	xSemaphoreGive ( xSemaphore_IIC[_I2C_TABLE_INDEX_EEPROM] );
#endif
}

#endif  //#if (_CHIP_EEPROM_TYPE_USE != _EEPROM_CHIP_NO_USE)

