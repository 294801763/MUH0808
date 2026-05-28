#include "includes.h"
#if (_ENABLE_CHIP_BP1048 == _MACRO_ENABLE)
#include "bp1048_bsp.h"

#define BP1048_ADDRESS_1	0x00
#define BP1048_ADDRESS_2	0x10

u8 u8BP1048DeviceTable[BP1048DeviceNumber] =
{
#if (DEV_NUM_BP1048>=1)
	_I2C_TABLE_INDEX_BP1048_0,
#endif
#if (DEV_NUM_BP1048>=2)
	_I2C_TABLE_INDEX_BP1048_1,
#endif
};
u8 u8BP1048DeviceAddress[BP1048DeviceNumber] =
{
	BP1048_ADDRESS_1,
	BP1048_ADDRESS_2,
};

extern SemaphoreHandle_t xSemaphore_IIC[NUM_OF_I2C_BUS_MAX];

uint8_t BP1048_i2c_Read(uint8_t u8DevID, uint8_t reg_addr)
{
	uint8_t input_val = 0;
#if _SYSTEM_SUPPORT_RTOS
		if(vTaskIsRunning() == 1)
		{
			xSemaphoreTake(xSemaphore_IIC[u8BP1048DeviceTable[u8DevID]], portMAX_DELAY);
		}	
#endif
	taskENTER_CRITICAL();
	i2c_read_bytes(u8BP1048DeviceTable[u8DevID], u8BP1048DeviceAddress[u8DevID],reg_addr, (uint8_t *)&input_val, 1, FALSE);
	taskEXIT_CRITICAL();
#if _SYSTEM_SUPPORT_RTOS
    if(vTaskIsRunning() == 1)  
    {
	    xSemaphoreGive(xSemaphore_IIC[u8BP1048DeviceTable[u8DevID]]);
    }
#endif
	return input_val;
}

void BP1048_i2c_write(uint8_t u8DevID, uint8_t *wr_val)
{
#if _SYSTEM_SUPPORT_RTOS
    if(vTaskIsRunning() == 1)
    {
        xSemaphoreTake(xSemaphore_IIC[u8BP1048DeviceTable[u8DevID]], portMAX_DELAY);
    }
#endif
	taskENTER_CRITICAL();

	bp1048_i2c_write_bytes(u8BP1048DeviceTable[u8DevID], u8BP1048DeviceAddress[u8DevID], wr_val, 6);
	taskEXIT_CRITICAL();
#if _SYSTEM_SUPPORT_RTOS
    if(vTaskIsRunning() == 1)
    {
        xSemaphoreGive(xSemaphore_IIC[u8BP1048DeviceTable[u8DevID]]);
    }
#endif
}



#endif

