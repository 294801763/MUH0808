#ifndef __PROJECT_BOARD_CONFIG_H__
#define __PROJECT_BOARD_CONFIG_H__

typedef enum _eProjectGpioName_t_
{
    // Led
    eGpioName_LedActive,

	//i2c
	eGpioName_I2cEepromScl,
	eGpioName_I2cEepromSda,
    eGpioName_I2cAlpuCScl,
    eGpioName_I2cAlpuCSda,

    //Reserve SPI
    eGpioName_SpiFlashClk,
    eGpioName_SpiFlashCs,
    eGpioName_SpiFlashMosi,
    eGpioName_SpiFlashMiso,

    //48V_CTR
    eGpioName_48V_CTR1,
    eGpioName_48V_CTR2,
    eGpioName_48V_CTR3,
    eGpioName_48V_CTR4,
	eGpioName_48V_CTR5,
	eGpioName_48V_CTR6,
	eGpioName_48V_CTR7,
	eGpioName_48V_CTR8,

	//CTR_-12V,
	eGpioName_CTR_12V,

	//BP1048_IIC
	eGpioName_BP1048_IIC_1_SDA,
	eGpioName_BP1048_IIC_1_SCL,
	eGpioName_BP1048_IIC_2_SDA,
	eGpioName_BP1048_IIC_2_SCL,

    //Reset
    eGpioName_SSD212Reset,

	eGpioName_Max,
}eProjectGpioName_t;

typedef enum _eI2cDevice_t_
{
	eI2cDevice_Eeprom = 0,
    eI2cDevice_BP1048_1,
    eI2cDevice_BP1048_2,
    eI2cDevice_ALPU_C,

	eI2cDevice_Max,
}eI2cDevice_t;

extern const stGpioConfig_t stProjectGpioTable[eGpioName_Max];
extern const stKeyDeclare_t stProjectKeyTable[];
extern const stLedDeclare_t stProjectLedTable[];
extern const stI2cDeclare_t stProjectI2cTable[];
extern const stSpiDeclare_t stProjectSpiTable[];
extern const stRxHpdDetDeclare_t stProjectRxHpdDetTable[];
extern const stIT663xxRstDeclare_t stProjectIT663xxRstTable[];
extern const stIrWorkDeclare_t stProjectIrWorkTable;
extern const st5VControl_t stProjectTx5VControlTable[];
extern const stUartDeclare_t stProjectUartWorkTable[];
extern const stCecDeclare_t stProjectCecWorkTable[];
#if _ENABLE_NEW_USER_KEY_DEFINE_FUNCTION
extern const stNewKeyDeclare_t stProjectNewKeyTable[];
#endif
extern const stI2CSwitchCtrl_t stProjectI2cSwitchTable[];
#if _ENABLE_CHIP_GSV_CHIP_SERIES
extern const stGsvChipResetPinCfg_t stProjectGsvChipResetTable[];
#endif
#if _ENABLE_CHIP_MS1826
extern const stMS1826ChipResetPinCfg_t stProjectMS1826ChipResetTable[];
#endif

#endif

