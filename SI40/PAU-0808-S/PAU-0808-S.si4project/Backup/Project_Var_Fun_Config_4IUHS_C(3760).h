#ifndef __PROJECT_VAR_FUN_CONFIG_H__
#define __PROJECT_VAR_FUN_CONFIG_H__

#define SaveSpecificVarInit				LMX_4IUHS_C_SpecificVarInit
#define EepSpecVarInvalid				LMX_4IUHS_C_SpecVarValidCheck
#define PrjStatePowerOnInit				LMX_4IUHS_C_PrjStatePowerOnInit
#if _ENABLE_NEW_USER_KEY_DEFINE_FUNCTION
#define mapp_NewKeyPadProcess           mapp_KeyFunctionProcess
#endif
#define StartupMessage 					mapp_LMX_4IUHS_CStartupMessage
#define SaveSpecificVarDefault          LMX_4IUHS_C_SpecificVarDefault


typedef enum _led_index_name_t_
{
    led_name_ActiveLed= 0,

    led_name_End,
	led_name_max_number
}led_index_name_t;

#if _ENABLE_NEW_USER_KEY_DEFINE_FUNCTION
typedef enum _key_counter_index_name_
{
    emKeyName_Source = 0,

    emKeyName_max,
}key_counter_index_name_t;
#endif

typedef enum _emUserTimerType_t_
{
    emUserTimer_LedActive = 0,
    emUserTimer_SwitchPortTime,
    emUserTimer_AutoSwitch,

    emUserTimer_Max,
}emUserTimerType_t;


typedef __packed struct _stBasicSpecVar_t_
{
	bool			bPowerOnSta;
	bool			bIsDebugEn;

	uint8_t			u8CheckSum;
}stBasicSpecVar_t, *pstBasicSpecVar_t;


typedef struct _stProjectSpecVar_t_
{
	stBasicSpecVar_t	stBasSpecVar;
}stProjectSpecVar_t, *pstProjectSpecVar_t;


extern const u8 cg_u8ChannelTable[4][3];


#ifdef __PROJECT_VAR_FUN_CONFIG_C__
#define INTERFACE
#else
#define INTERFACE       extern
#endif
INTERFACE void GetResolutionText(char *ps8ResText,u8 u8ResID);
INTERFACE void LMX_4IUHS_C_SpecificVarInit(void);
INTERFACE void LMX_4IUHS_C_SpecBasicVarDefault(void);
INTERFACE void LMX_4IUHS_C_SpecCustomEdidVarDefault(void);
INTERFACE bool LMX_4IUHS_C_SpecVarValidCheck(void);
// the status when power on device
INTERFACE void LMX_4IUHS_C_PrjStatePowerOnInit(void);
INTERFACE void LMX_4IUHS_C_LedWork_Loop(void);
INTERFACE void LMX_4IUHS_C_FuncWork_LoopRunning(void);
INTERFACE void SetUserData_SpecBasicVar(void);
INTERFACE void SetUserData_SpecCustomEdid(uint8_t u8CustomEdidIndex);
INTERFACE void mapp_LMX_4IUHS_CStartupMessage(void);

#undef INTERFACE
#endif
