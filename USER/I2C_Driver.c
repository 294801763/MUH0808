/**
 *****************************************************************************
  *                                   Update
  * @Version : V1.0
  * @By      : dengzhiqin
  * @Date    : 2017 / 12 / 05
  * @Brief   : driver of i2c device
  *
  *****************************************************************************
**/
#include "includes.h"

extern const stI2cDeclare_t stProjectI2cTable[];
extern const stI2CSwitchCtrl_t stProjectI2cSwitchTable[];


//pin configuration
void bsp_InitI2C ( void )
{
	pstI2cDeclare_t pI2cN, pI2cS = ( pstI2cDeclare_t ) &stProjectI2cTable[0];

	pI2cN = pI2cS;
	while ( pI2cN->pstSclPort != NULL )
	{
		i2c_Stop ( pI2cN-pI2cS );
		pI2cN ++;
	}
	Init_I2cLineChangePin();
}

void Init_I2cLineChangePin ( void )
{
	pstI2CSwitchCtrl_t pI2cSwCur,pI2cSwStart = ( pstI2CSwitchCtrl_t ) &stProjectI2cSwitchTable[0];

	pI2cSwCur = pI2cSwStart;
	while ( pI2cSwCur->pstCtrlPortA != NULL )
	{
#if _ENABLE_SW4052_CS_PIN
		mdrv_SetI2cSw4052CsState ( pI2cSwCur-pI2cSwStart,ePinLevel_High );
#endif
		mdrv_SetI2cLineChange ( pI2cSwCur-pI2cSwStart,0 );
		pI2cSwCur++;
	}
}

void mdrv_SetLineChangePin ( pstGpioConfig_t pGpio, ePinLevel_t e_level )
{
	if ( e_level == ePinLevel_High )
	{
		if ( IS_MCU_GPIO ( pGpio->u8PortType ) )
		{
#if (defined(GD32F4XX))
			gpio_bit_write ( STM32_GPIO_PORT[pGpio->u8PortType-PORT_GPIOA],pGpio->u16GpioPin,SET );
#else
			GPIO_WriteBit ( STM32_GPIO_PORT[pGpio->u8PortType-PORT_GPIOA],pGpio->u16GpioPin,Bit_SET );
#endif
		}
#if _ENABLE_CHIP_LM74HC138
		else if ( IS_138_GPIO ( pGpio->u8PortType ) )
		{
			mapp_Set138Value ( pGpio->u16GpioPin );
		}
#endif
	}
	else
	{
		if ( IS_MCU_GPIO ( pGpio->u8PortType ) )
		{
#if (defined(GD32F4XX))
			gpio_bit_write ( STM32_GPIO_PORT[pGpio->u8PortType-PORT_GPIOA],pGpio->u16GpioPin,RESET );
#else
			GPIO_WriteBit ( STM32_GPIO_PORT[pGpio->u8PortType-PORT_GPIOA],pGpio->u16GpioPin,Bit_RESET );
#endif
		}
#if _ENABLE_CHIP_LM74HC138
		else if ( IS_138_GPIO ( pGpio->u8PortType ) )
		{
			mapp_Set138Value ( pGpio->u16GpioPin );
		}
#endif
	}
}

void mdrv_SetI2cLineChange ( u8 u8Dev,u8 u8index )
{
	pstI2CSwitchCtrl_t pI2cSw = ( pstI2CSwitchCtrl_t ) &stProjectI2cSwitchTable[u8Dev];

#if 0//_ENABLE_SW4052_CS_PIN
	if ( pI2cSw->pstCtrlCsPin != NULL )
	{
		mdrv_SetLineChangePin ( pI2cSw->pstCtrlCsPin,ePinLevel_Low );
	}
#endif

	if ( pI2cSw->pstCtrlPortA != NULL )
	{
		if ( pI2cSw->pstCtrlPortB != NULL )
		{
			switch ( u8index )
			{
				case 0:
					mdrv_SetLineChangePin ( pI2cSw->pstCtrlPortA,ePinLevel_Low );
					mdrv_SetLineChangePin ( pI2cSw->pstCtrlPortB,ePinLevel_Low );
					break;
				case 1:
					mdrv_SetLineChangePin ( pI2cSw->pstCtrlPortA,ePinLevel_High );
					mdrv_SetLineChangePin ( pI2cSw->pstCtrlPortB,ePinLevel_Low );
					break;
				case 2:
					mdrv_SetLineChangePin ( pI2cSw->pstCtrlPortA,ePinLevel_Low );
					mdrv_SetLineChangePin ( pI2cSw->pstCtrlPortB,ePinLevel_High );
					break;
				case 3:
					mdrv_SetLineChangePin ( pI2cSw->pstCtrlPortA,ePinLevel_High );
					mdrv_SetLineChangePin ( pI2cSw->pstCtrlPortB,ePinLevel_High );
					break;
				default:
					break;
			}
		}
		else
		{
			switch ( u8index )
			{
				case 0:
					mdrv_SetLineChangePin ( pI2cSw->pstCtrlPortA,ePinLevel_Low );
					break;
				case 1:
					mdrv_SetLineChangePin ( pI2cSw->pstCtrlPortA,ePinLevel_High );
					break;
				default:
					break;
			}
		}
	}
}

#if _ENABLE_SW4052_CS_PIN
void mdrv_SetI2cSw4052CsState ( u8 u8Dev,ePinLevel_t e_level )
{
	pstI2CSwitchCtrl_t pI2cSw = ( pstI2CSwitchCtrl_t ) &stProjectI2cSwitchTable[u8Dev];

	if ( pI2cSw->pstCtrlCsPin != NULL )
	{
		mdrv_SetLineChangePin ( pI2cSw->pstCtrlCsPin,e_level );
	}
}
#endif

//iic bus pin set
void i2c_pin_set ( pstGpioConfig_t pGpio, ePinLevel_t e_level )
{
	if ( e_level == ePinLevel_High )
	{
#if (defined(GD32F4XX))
		gpio_bit_set ( STM32_GPIO_PORT[pGpio->u8PortType-PORT_GPIOA],pGpio->u16GpioPin );
#else
		GPIO_SetBits ( STM32_GPIO_PORT[pGpio->u8PortType-PORT_GPIOA],pGpio->u16GpioPin );
#endif
	}
	else
	{
#if (defined(GD32F4XX))
		gpio_bit_reset ( STM32_GPIO_PORT[pGpio->u8PortType-PORT_GPIOA],pGpio->u16GpioPin );
#else
		GPIO_ResetBits ( STM32_GPIO_PORT[pGpio->u8PortType-PORT_GPIOA],pGpio->u16GpioPin );
#endif
	}
}

/**
  * @brief I2C 等待事件
  * @params I2C_EVENT 同 I2C_CheckEvent
  * @returns None
  */
uint8_t IIC_WaitEvent ( I2C_TypeDef* I2Cx, uint32_t I2C_EVENT )
{
	uint32_t Stutas = SUCCESS;
	//uint32_t Timeout = 1000000;							//给定超时计数时间
	uint32_t Timeout = 1000;
	while ( I2C_CheckEvent ( I2Cx, I2C_EVENT ) != SUCCESS )	//等待指定事件
	{
		Timeout--;
		if ( Timeout == 0 )								//判断是否等待超时
		{
			/*超时的错误处理代码，可以添加到此处*/
			Stutas = ERROR;
			break;
		}
	}
	return Stutas;
}

/**
  * @brief I2C 空闲判断
  * @params I2C_EVENT 同 I2C_CheckEvent
  * @returns None
  */
uint8_t IIC_WaitBUSY ( I2C_TypeDef* I2Cx, uint32_t I2C_FLAG )
{
	uint32_t Stutas = SUCCESS;
	//int32_t Timeout = 1000000;
	uint32_t Timeout = 1000;
	while ( I2C_GetFlagStatus ( I2Cx, I2C_FLAG ) != RESET )
	{
		Timeout--;
		if ( Timeout == 0 )								//判断是否等待超时
		{
			/*超时的错误处理代码，可以添加到此处*/
			Stutas = ERROR;
			break;
		}
	}
	return Stutas;
}

u8 I2C_WriteByte ( uint8_t dev, uint8_t slaveAddr, uint8_t* data,uint8_t data_num )
{
	uint8_t statu;
	u8 cnt = 0;

	//dbg_printf("Function %s ",__FUNCTION__);
	if (!dev )
	{
		dbg_printf ( "dev: %s,slaveAddr: 0x%02x,data_num: %d\r\n","I2C1",slaveAddr,data_num );
	}
	else
	{
		dbg_printf ( "dev: %s,slaveAddr: 0x%02x,data_num: %d\r\n","I2C2",slaveAddr,data_num );
	}

start:
	statu = IIC_WaitBUSY ( dev? I2C1 : I2C2, I2C_FLAG_BUSY );
	if ( statu == ERROR )
	{
		dbg_printf ( "function:%s,line:%d,cnt:%d\r\n",__FUNCTION__,__LINE__,cnt );
		//goto fail;
	}

	I2C_GenerateSTART ( dev? I2C1 : I2C2, ENABLE );
	statu = IIC_WaitEvent ( dev? I2C1 : I2C2, I2C_EVENT_MASTER_MODE_SELECT );
	if ( statu == ERROR )
	{
		dbg_printf ( "function:%s,line:%d,cnt:%d\r\n",__FUNCTION__,__LINE__,cnt );
		//goto fail;
	}

	I2C_Send7bitAddress ( dev? I2C1 : I2C2, slaveAddr, I2C_Direction_Transmitter );
	statu = IIC_WaitEvent ( dev? I2C1 : I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED );
	if ( statu == ERROR )
	{
		dbg_printf ( "function:%s,line:%d,cnt:%d\r\n",__FUNCTION__,__LINE__,cnt );
		//goto fail;
	}

	for ( u8 i = 0; i < data_num; i++ )
	{
		// 发送数据
		//I2C_SendData(dev? I2C1 : I2C2, 0x01);
		I2C_SendData ( dev? I2C1 : I2C2,data[i] );
#if 1
		dbg_printf ( "Write IIC data[%d]:%02x !\r\n",i,data[i] ); //disabled - error
#endif

		statu = IIC_WaitEvent ( dev? I2C1 : I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED );
		if ( statu == ERROR )
		{
			dbg_printf ( "function:%s,line:%d,cnt:%d\r\n",__FUNCTION__,__LINE__,cnt );
			//goto fail;
		}
	}

// 发送停止信号
	I2C_GenerateSTOP ( dev? I2C1 : I2C2, ENABLE );

//重试5次
fail:

#if 0
	cnt++;
	if ( ( cnt <= 5 ) && ( statu == ERROR ) )
	{
		goto start;
	}
	else
	{
		return 0;
	}
#endif

	return 1;
}

//切换函数 - 临时改名
void I2C_WriteByte_backup_v1_0 ( uint8_t dev, uint8_t slaveAddr, uint8_t* data,uint8_t data_num )
{

	dbg_printf ( "Function %s ",__FUNCTION__ );
	if (!dev )
	{
		dbg_printf ( "dev: %s,slaveAddr: 0x%02x,data_num: %d\r\n","I2C1",slaveAddr,data_num );
	}
	else
	{
		dbg_printf ( "dev: %s,slaveAddr: 0x%02x,data_num: %d\r\n","I2C2",slaveAddr,data_num );
	}

	// 发送起始信号
	I2C_GenerateSTART ( dev? I2C1 : I2C2, ENABLE );
	if (!I2C_CheckEvent ( dev? I2C1 : I2C2, I2C_EVENT_MASTER_MODE_SELECT ) )
	{
		dbg_printf ( "Write IIC Start fail!\r\n" );

		if ( I2C2->SR2 & I2C_FLAG_BUSY )
		{
			dbg_printf ( "I2C2 is BUSY!\r\n" );
		}

		if ( I2C1->SR2 & I2C_FLAG_BUSY )
		{
			dbg_printf ( "I2C1 is BUSY!\r\n" );
		}


		if ( I2C_GetFlagStatus ( I2C2,I2C_FLAG_BUSY ) )
		{
			dbg_printf ( "I2C2 is BUSY!\r\n" );
		}

		if ( I2C_GetFlagStatus ( I2C1,I2C_FLAG_BUSY ) )
		{
			dbg_printf ( "I2C1 is BUSY!\r\n" );
		}

	}

	// 发送从机地址和写操作
	I2C_Send7bitAddress ( dev? I2C1 : I2C2, slaveAddr, I2C_Direction_Transmitter );
	if (!I2C_CheckEvent ( dev? I2C1 : I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED ) )
	{
		//I2C_Send7bitAddress(dev? I2C1 : I2C2, slaveAddr, I2C_Direction_Transmitter);
		dbg_printf ( "Write IIC Address[0x%02x] fail!\r\n",slaveAddr ); //disabled - error

		if ( I2C2->SR2 & I2C_FLAG_BUSY )
		{
			dbg_printf ( "I2C2 is BUSY!\r\n" );
		}

		if ( I2C1->SR2 & I2C_FLAG_BUSY )
		{
			dbg_printf ( "I2C1 is BUSY!\r\n" );
		}


		if ( I2C_GetFlagStatus ( I2C2,I2C_FLAG_BUSY ) )
		{
			dbg_printf ( "I2C2 is BUSY!\r\n" );
		}

		if ( I2C_GetFlagStatus ( I2C1,I2C_FLAG_BUSY ) )
		{
			dbg_printf ( "I2C1 is BUSY!\r\n" );
		}

		//delay_ms(5);
	}
	else
	{
		dbg_printf ( "Write IIC Address[0x%02x] success!\r\n",slaveAddr );
	}

	for ( u8 i = 0; i < data_num; i++ )
	{
		// 发送数据
		//I2C_SendData(dev? I2C1 : I2C2, 0x01);
		I2C_SendData ( dev? I2C1 : I2C2,data[i] );
		dbg_printf ( "Write IIC data[%d]:%02x !\r\n",i,data[i] ); //disabled - error
		//delay_ms(5);
#if 1
		if (!I2C_CheckEvent ( dev? I2C1 : I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED ) )
		{
			//dbg_printf("Write IIC data[%d]:%02x fail!\r\n",i,data[i]);
			if ( I2C2->SR2 & I2C_FLAG_BUSY )
			{
				dbg_printf ( "I2C2 is BUSY!\r\n" );
			}

			if ( I2C1->SR2 & I2C_FLAG_BUSY )
			{
				dbg_printf ( "I2C1 is BUSY!\r\n" );
			}


			if ( I2C_GetFlagStatus ( I2C2,I2C_FLAG_BUSY ) )
			{
				dbg_printf ( "I2C2 is BUSY!\r\n" );
			}

			if ( I2C_GetFlagStatus ( I2C1,I2C_FLAG_BUSY ) )
			{
				dbg_printf ( "I2C1 is BUSY!\r\n" );
			}

		}
#endif
	}

	// 发送停止信号
	I2C_GenerateSTOP ( dev? I2C1 : I2C2, ENABLE );
}

u8 I2C_WriteByte_v1 ( uint8_t dev, uint8_t slaveAddr, uint8_t* data,uint8_t data_num )
{

	dbg_printf ( "Function %s ",__FUNCTION__ );
	if (!dev )
	{
		dbg_printf ( "dev: %s,slaveAddr: 0x%02x,data_num: %d\r\n","I2C1",slaveAddr,data_num );
	}
	else
	{
		dbg_printf ( "dev: %s,slaveAddr: 0x%02x,data_num: %d\r\n","I2C2",slaveAddr,data_num );
	}

	// 发送起始信号
	I2C_GenerateSTART ( dev? I2C1 : I2C2, ENABLE );
	if (!I2C_CheckEvent ( dev? I2C1 : I2C2, I2C_EVENT_MASTER_MODE_SELECT ) )
	{
		dbg_printf ( "Write IIC Start fail!\r\n" ); //这一句屏蔽后出现I2C处理不正确的情况.
	}

	// 发送从机地址和写操作
	I2C_Send7bitAddress ( dev? I2C1 : I2C2, slaveAddr, I2C_Direction_Transmitter );
	if (!I2C_CheckEvent ( dev? I2C1 : I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED ) )
	{
		//dbg_printf("Write IIC Address[0x%02x] fail!\r\n",slaveAddr);
	}

	for ( u8 i = 0; i < data_num; i++ )
	{
		// 发送数据
		//I2C_SendData(dev? I2C1 : I2C2, 0x01);
		I2C_SendData ( dev? I2C1 : I2C2,data[i] );
		dbg_printf ( "Write IIC data[%d]:%02x !\r\n",i,data[i] ); //这一句屏蔽后出现I2C处理不正确的情况.
#if 1
		if (!I2C_CheckEvent ( dev? I2C1 : I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED ) )
		{
			//dbg_printf("Write IIC data[%d]:%02x fail!\r\n",i,data[i]);
		}
#endif
	}

	// 发送停止信号
	I2C_GenerateSTOP ( dev? I2C1 : I2C2, ENABLE );
	return 0;
}

//iic bus pin get
ePinLevel_t i2c_pin_get ( pstGpioConfig_t pGpio )
{
#if (defined(GD32F4XX))
	return  ( gpio_input_bit_get ( STM32_GPIO_PORT[pGpio->u8PortType-PORT_GPIOA],pGpio->u16GpioPin ) ==SET ) \
	        ?ePinLevel_High: ePinLevel_Low;
#else
	return  ( GPIO_ReadInputDataBit ( STM32_GPIO_PORT[pGpio->u8PortType-PORT_GPIOA],pGpio->u16GpioPin ) ==Bit_SET ) \
	        ?ePinLevel_High: ePinLevel_Low;
#endif
}

void i2c_delay ( uint16_t u16DelayTime )
{
	uint16_t i;
	for ( i=0; i<u16DelayTime; i++ );
}

//i2c start
void i2c_Start ( uint8_t dev )
{
	//当SCL高电平时，SDA出现一个下跳沿表示I2C总线启动信号
	pstI2cDeclare_t pI2c = ( pstI2cDeclare_t ) &stProjectI2cTable[dev];

	mdrv_SetI2cLineChange ( pI2c->u8SwitchPortDev,pI2c->u8SwitchPortNum );

	i2c_pin_set ( pI2c->pstSdaPort, ePinLevel_High );
	i2c_pin_set ( pI2c->pstSclPort, ePinLevel_High );
	i2c_delay ( pI2c->u16I2cDelayT );
	i2c_pin_set ( pI2c->pstSdaPort, ePinLevel_Low );
	i2c_delay ( pI2c->u16I2cDelayT );
	i2c_pin_set ( pI2c->pstSclPort, ePinLevel_Low );
	i2c_delay ( pI2c->u16I2cDelayT );

}

//i2c stop
void i2c_Stop ( uint8_t dev )
{
	//当SCL高电平是， SDA出现一个上跳沿表示I2C总线停止信号
	pstI2cDeclare_t pI2c = ( pstI2cDeclare_t ) &stProjectI2cTable[dev];

	mdrv_SetI2cLineChange ( pI2c->u8SwitchPortDev,pI2c->u8SwitchPortNum );

	i2c_pin_set ( pI2c->pstSdaPort, ePinLevel_Low );
	i2c_pin_set ( pI2c->pstSclPort, ePinLevel_High );
	i2c_delay ( pI2c->u16I2cDelayT );
	i2c_pin_set ( pI2c->pstSdaPort, ePinLevel_High );
	i2c_delay ( pI2c->u16I2cDelayT );

}

//i2c send byte
void i2c_SendByte ( uint8_t dev, uint8_t _ucByte )
{
	uint8_t i;
	pstI2cDeclare_t pI2c = ( pstI2cDeclare_t ) &stProjectI2cTable[dev];

	mdrv_SetI2cLineChange ( pI2c->u8SwitchPortDev,pI2c->u8SwitchPortNum );

	for ( i = 0; i < 8; i++ )
	{
		i2c_pin_set ( pI2c->pstSdaPort, ( _ucByte & 0x80 ) ?ePinLevel_High: ePinLevel_Low );
		i2c_delay ( pI2c->u16I2cDelayT );
		i2c_pin_set ( pI2c->pstSclPort, ePinLevel_High );
		i2c_delay ( pI2c->u16I2cDelayT );
		i2c_pin_set ( pI2c->pstSclPort, ePinLevel_Low );
		if ( i == 7 )
		{
			i2c_pin_set ( pI2c->pstSdaPort, ePinLevel_High );
		}
		_ucByte <<= 1;
		i2c_delay ( pI2c->u16I2cDelayT );
	}
}

//i2c receive byte
uint8_t i2c_ReadByte ( uint8_t dev )
{
	uint8_t i, value = 0;
	pstI2cDeclare_t pI2c = ( pstI2cDeclare_t ) &stProjectI2cTable[dev];

	mdrv_SetI2cLineChange ( pI2c->u8SwitchPortDev,pI2c->u8SwitchPortNum );

	for ( i = 0; i < 8; i++ )
	{
		value <<= 1;
		i2c_pin_set ( pI2c->pstSclPort, ePinLevel_High );
		i2c_delay ( pI2c->u16I2cDelayT );
		if ( i2c_pin_get ( pI2c->pstSdaPort ) )
		{
			value++;
		}
		i2c_pin_set ( pI2c->pstSclPort, ePinLevel_Low );
		i2c_delay ( pI2c->u16I2cDelayT );
	}


	return value;
}

//i2c wait ack
uint8_t i2c_WaitAck ( uint8_t dev )
{
	uint8_t ret;
	pstI2cDeclare_t pI2c = ( pstI2cDeclare_t ) &stProjectI2cTable[dev];

	mdrv_SetI2cLineChange ( pI2c->u8SwitchPortDev,pI2c->u8SwitchPortNum );

	i2c_pin_set ( pI2c->pstSdaPort, ePinLevel_High );
	i2c_delay ( pI2c->u16I2cDelayT );
	i2c_pin_set ( pI2c->pstSclPort, ePinLevel_High );
	i2c_delay ( pI2c->u16I2cDelayT );
	ret = ( i2c_pin_get ( pI2c->pstSdaPort ) ) ?1:0;
	i2c_pin_set ( pI2c->pstSclPort, ePinLevel_Low );
	i2c_delay ( pI2c->u16I2cDelayT );

	return ret;
}

//i2c ack
void i2c_Ack ( uint8_t dev )
{
	pstI2cDeclare_t pI2c = ( pstI2cDeclare_t ) &stProjectI2cTable[dev];

	mdrv_SetI2cLineChange ( pI2c->u8SwitchPortDev,pI2c->u8SwitchPortNum );

	i2c_pin_set ( pI2c->pstSdaPort, ePinLevel_Low );
	i2c_delay ( pI2c->u16I2cDelayT );
	i2c_pin_set ( pI2c->pstSclPort, ePinLevel_High );
	i2c_delay ( pI2c->u16I2cDelayT );
	i2c_pin_set ( pI2c->pstSclPort, ePinLevel_Low );
	i2c_delay ( pI2c->u16I2cDelayT );
	i2c_pin_set ( pI2c->pstSdaPort, ePinLevel_High );

}

//i2c nack
void i2c_NAck ( uint8_t dev )
{
	pstI2cDeclare_t pI2c = ( pstI2cDeclare_t ) &stProjectI2cTable[dev];

	mdrv_SetI2cLineChange ( pI2c->u8SwitchPortDev,pI2c->u8SwitchPortNum );

	i2c_pin_set ( pI2c->pstSdaPort, ePinLevel_High );
	i2c_delay ( pI2c->u16I2cDelayT );
	i2c_pin_set ( pI2c->pstSclPort, ePinLevel_High );
	i2c_delay ( pI2c->u16I2cDelayT );
	i2c_pin_set ( pI2c->pstSclPort, ePinLevel_Low );
	i2c_delay ( pI2c->u16I2cDelayT );

}

//check device
uint8_t i2c_CheckDevice ( uint8_t dev, uint8_t _Address )
{
	uint8_t ucAck;
	pstI2cDeclare_t pI2c = ( pstI2cDeclare_t ) &stProjectI2cTable[dev];

	mdrv_SetI2cLineChange ( pI2c->u8SwitchPortDev,pI2c->u8SwitchPortNum );

	if ( i2c_pin_get ( pI2c->pstSdaPort ) && i2c_pin_get ( pI2c->pstSclPort ) )
	{
		i2c_Start ( dev );
		i2c_SendByte ( dev, _Address|I2C_WR );
		ucAck = i2c_WaitAck ( dev );
		i2c_Stop ( dev );
#if _ENABLE_SW4052_CS_PIN
		mdrv_SetI2cSw4052CsState ( pI2c->u8SwitchPortDev,ePinLevel_High );
#endif
		return ucAck;
	}
	return 1;
}

//read bytes
uint8_t i2c_read_bytes ( uint8_t dev, uint8_t dev_addr,
                         uint16_t reg_addr, uint8_t* pData, uint16_t byte_no, bool two_bytes_addr )
{
	uint16_t i = 0;

#if _ENABLE_SW4052_CS_PIN
	pstI2cDeclare_t pI2c = ( pstI2cDeclare_t ) &stProjectI2cTable[dev];

	mdrv_SetI2cSw4052CsState ( pI2c->u8SwitchPortDev,ePinLevel_Low );
#endif
	i2c_Start ( dev );
	i2c_SendByte ( dev, ( dev_addr&0xFE ) );
	if ( i2c_WaitAck ( dev ) != 0 )
	{
		Msg_I2c ( ( "[R DEV %d]: I2C write device addr[0x%02x] fail\r\n",dev,dev_addr&0xFE ) );
		goto i2c_fail;
	}

	if ( two_bytes_addr )
	{
		i2c_SendByte ( dev, ( uint8_t ) ( reg_addr>>8 ) );
		if ( i2c_WaitAck ( dev ) != 0 )
		{
			Msg_I2c ( ( "[R DEV %d]: I2C write reg addr fail\r\n", dev ) );
			goto i2c_fail;
		}
	}

	i2c_SendByte ( dev, ( uint8_t ) ( reg_addr&0xFF ) );
	if ( i2c_WaitAck ( dev ) != 0 )
	{
		Msg_I2c ( ( "[R DEV %d]: I2C write reg addr fail\r\n", dev ) );
		goto i2c_fail;
	}

	i2c_Start ( dev );
	i2c_SendByte ( dev, ( dev_addr|0x01 ) );
	if ( i2c_WaitAck ( dev ) != 0 )
	{
		Msg_I2c ( ( "[R DEV %d]: I2C write device addr fail\r\n", dev ) );
		goto i2c_fail;
	}

	for ( i = 0; i < byte_no; i++ )
	{
		pData[i] = i2c_ReadByte ( dev );
		if ( i != byte_no - 1 )
		{
			i2c_Ack ( dev );
		}
		else
		{
			i2c_NAck ( dev );
		}
	}

	i2c_Stop ( dev );
#if _ENABLE_SW4052_CS_PIN
	mdrv_SetI2cSw4052CsState ( pI2c->u8SwitchPortDev,ePinLevel_High );
#endif
	return 0;

i2c_fail:
	i2c_Stop ( dev );
#if _ENABLE_SW4052_CS_PIN
	mdrv_SetI2cSw4052CsState ( pI2c->u8SwitchPortDev,ePinLevel_High );
#endif
	return 1;
}

//write bytes
uint8_t i2c_write_bytes ( uint8_t dev,uint8_t dev_addr,
                          uint16_t reg_addr, uint8_t* pData, uint16_t byte_no, bool two_bytes_addr )
{
#if 0
	uint16_t i = 0;
#if _ENABLE_SW4052_CS_PIN
	pstI2cDeclare_t pI2c = ( pstI2cDeclare_t ) &stProjectI2cTable[dev];

	mdrv_SetI2cSw4052CsState ( pI2c->u8SwitchPortDev,ePinLevel_Low );
#endif

	i2c_Start ( dev );
	i2c_SendByte ( dev, ( dev_addr&0xFE ) );
	if ( i2c_WaitAck ( dev ) != 0 )
	{
		Msg_I2c ( ( "[W DEV %d]: I2C write device addr[0x%02x] fail\r\n", dev,dev_addr&0xFE ) );
		goto i2c_fail;
	}

	if ( two_bytes_addr )
	{
		i2c_SendByte ( dev, ( uint8_t ) ( reg_addr>>8 ) );
		if ( i2c_WaitAck ( dev ) != 0 )
		{
			Msg_I2c ( ( "[W DEV %d]: I2C write reg addr fail\r\n", dev ) );
			goto i2c_fail;
		}
	}

	i2c_SendByte ( dev, ( uint8_t ) ( reg_addr&0xFF ) );
	if ( i2c_WaitAck ( dev ) != 0 )
	{
		Msg_I2c ( ( "[W DEV %d]: I2C write reg addr fail\r\n", dev ) );
		goto i2c_fail;
	}

	for ( i = 0; i < byte_no; i++ )
	{
		i2c_SendByte ( dev, pData[i] );
		if ( i2c_WaitAck ( dev ) != 0 )
		{
			Msg_I2c ( ( "[W DEV %d]: I2C write data fail\r\n", dev ) );
			goto i2c_fail;
		}
	}

	i2c_Stop ( dev );
#if _ENABLE_SW4052_CS_PIN
	mdrv_SetI2cSw4052CsState ( pI2c->u8SwitchPortDev,ePinLevel_High );
#endif
	return 0;

i2c_fail:
	i2c_Stop ( dev );
#if _ENABLE_SW4052_CS_PIN
	mdrv_SetI2cSw4052CsState ( pI2c->u8SwitchPortDev,ePinLevel_High );
#endif
#endif
	return 1;
}

uint8_t bp1048_i2c_write_bytes ( uint8_t dev,uint8_t dev_addr,
                                 uint8_t* pData, uint16_t byte_no )
{
//	uint16_t i = 0;
//#if _ENABLE_SW4052_CS_PIN
//	pstI2cDeclare_t pI2c = (pstI2cDeclare_t)&stProjectI2cTable[dev];
//
//	mdrv_SetI2cSw4052CsState(pI2c->u8SwitchPortDev,ePinLevel_Low);
//#endif
//
//	i2c_Start(dev);
//	i2c_SendByte(dev, (dev_addr&0xFE));
//	if (i2c_WaitAck(dev) != 0)
//	{
//		Msg_I2c(("[W DEV %d]: I2C write device addr[0x%02x] fail\r\n", dev,dev_addr&0xFE));
//		goto i2c_fail;
//	}
//
//	for (i = 0; i < byte_no; i++)
//	{
//		i2c_SendByte(dev, pData[i]);
//		if (i2c_WaitAck(dev) != 0)
//		{
//			Msg_I2c(("[W DEV %d]: I2C write data fail\r\n", dev));
//			goto i2c_fail;
//		}
//	}
//
//	i2c_Stop(dev);
//#if _ENABLE_SW4052_CS_PIN
//	mdrv_SetI2cSw4052CsState(pI2c->u8SwitchPortDev,ePinLevel_High);
//#endif
//	return 0;
//
//	i2c_fail:
//	i2c_Stop(dev);
//#if _ENABLE_SW4052_CS_PIN
//	mdrv_SetI2cSw4052CsState(pI2c->u8SwitchPortDev,ePinLevel_High);
//#endif
	return I2C_WriteByte ( dev, dev_addr,pData,byte_no );;
}

uint8_t bp1048_i2c_write_bytes_v1 ( uint8_t dev,uint8_t dev_addr,
                                    uint8_t* pData, uint16_t byte_no )
{
	I2C_WriteByte_v1 ( dev, dev_addr,pData,byte_no );
	return 1;
}


#if 1//((IT663XX_VER != IT663XX_NONE)||(IT666X_VER != IT666X_NONE)||_ENABLE_CHIP_ITE66351||_ENABLE_CHIP_ITE6615)
extern SemaphoreHandle_t xSemaphore_IIC[NUM_OF_I2C_BUS_MAX];
iTE_u1 i2c_read_byte ( iTE_u8 address, iTE_u8 offset, iTE_u8 byteno, iTE_u8 *p_data, iTE_u8 device )
{
	iTE_u1 ret_val;

#if _SYSTEM_SUPPORT_RTOS
	xSemaphoreTake ( xSemaphore_IIC[device], portMAX_DELAY );
#endif
	ret_val = i2c_read_bytes ( device, address, ( uint16_t ) offset, p_data, byteno, FALSE );
#if _SYSTEM_SUPPORT_RTOS
	xSemaphoreGive ( xSemaphore_IIC[device] );
#endif

	return ( ret_val ) ?0:1;
}

iTE_u1 i2c_write_byte ( iTE_u8 address, iTE_u8 offset, iTE_u8 byteno, iTE_u8 *p_data, iTE_u8 device )
{
	iTE_u1 ret_val;

#if _SYSTEM_SUPPORT_RTOS
	xSemaphoreTake ( xSemaphore_IIC[device], portMAX_DELAY );
#endif
	ret_val = i2c_write_bytes ( device, address, ( uint16_t ) offset, p_data, byteno, FALSE );
#if _SYSTEM_SUPPORT_RTOS
	xSemaphoreGive ( xSemaphore_IIC[device] );
#endif

	return ( ret_val ) ?0:1;
}
#endif


