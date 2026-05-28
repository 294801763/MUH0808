#ifndef _M21452_BSP_H
#define _M21452_BSP_H


uint8_t BP1048_i2c_Read(uint8_t u8DevID, uint8_t reg_addr);
	void BP1048_i2c_write(uint8_t u8DevID, uint8_t reg_addr, uint8_t *wr_val);
#endif

