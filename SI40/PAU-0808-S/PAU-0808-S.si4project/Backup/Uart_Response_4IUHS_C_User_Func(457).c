#define __UART_RESPON_USER_FUNC_C__

#include "includes.h"

#include "../USER/project_file/LMX_4IUHS_C/mapp_UartCmdList_4IUHS_C.h"

typedef void (*pFuncUartRes)(uint8_t *pu8Data, uint16_t u16Len);

typedef struct _stUartCmdRx_t_
{
	char 				*cmdStr;
	pFuncUartRes		funcResponse;
}stUartCmdRx_t, *pstUartCmdRx_t;

#if _ENABLE_USER_EDID_LEARNING_FUNCTION
bool StartEdidCostumFlag;
u8 g_u8UserEDIDIndex;
bool g_bInternalEdidFlag;
#endif

extern stUartCom_t				g_stUartCommVar, g_stUart1CommVar;
extern const stUartDeclare_t 	stProjectUartWorkTable[];
#if (!_ENABLE_UART_SEMAPHORE_FUNCTION_BY_PRINT)
extern SemaphoreHandle_t		xSemaphore_Uart1Snd;
extern SemaphoreHandle_t		xSemaphore_Uart2Snd;
extern SemaphoreHandle_t		xSemaphore_Uart3Snd;
#endif
BYTE g_u8MultiCmdDelayCounter = 0;

static eCmdFun_t cmdfunctionID = eFunc_NoUse;

void UartCommVarClear(pstUartCom_t pCommVar);

void GetResolutionText(char *ps8ResText,u8 u8ResID)
{
    switch(u8ResID)
    {

        default:
            break;
    }

}

//eFunc_GetVersion,
static emCmdFuncStaType mapp_CmdfuncGetVersion(pstUartCom_t pCommVar, uint8_t cmdnum)
{

    return emCmdSucess;
}

//eFunc_FactoryReset,
static emCmdFuncStaType mapp_CmdfuncFactoryReset(pstUartCom_t pCommVar,u8 cmdnum)
{

    return emCmdSucess;
}

//eFunc_Reboot,
static emCmdFuncStaType mapp_CmdfuncReboot(pstUartCom_t pCommVar,u8 cmdnum)
{
    return emCmdSucess;
}

//eFunc_GetTestVersion,
static emCmdFuncStaType mapp_CmdfuncGetTestVersion(pstUartCom_t pCommVar,u8 cmdnum)
{

    return emCmdSucess;
}

//eFunc_SwitchInputPort,
static emCmdFuncStaType mapp_CmdfuncSwitchInputPort(pstUartCom_t pCommVar,u8 cmdnum)
{
    emCmdFuncStaType l_state = emCmdSucess;
    return l_state;

}

//eFunc_GetInputStutus,
static emCmdFuncStaType mapp_CmdfuncGetInputStutus(pstUartCom_t pCommVar,u8 cmdnum)
{
    emCmdFuncStaType l_state = emCmdSucess;
    return l_state;
}

//eFunc_SetTxResolution,
static emCmdFuncStaType mapp_CmdfuncSetTxResolution(pstUartCom_t pCommVar,u8 cmdnum)
{
    emCmdFuncStaType l_state = emCmdSucess;

    return l_state;
}
//eFunc_GetTxResolution,
static emCmdFuncStaType mapp_CmdfuncGetTxResolution(pstUartCom_t pCommVar,u8 cmdnum)
{
    emCmdFuncStaType l_state = emCmdSucess;

    return l_state;
}

//eFunc_GetRxResolution,
static emCmdFuncStaType mapp_CmdfuncGetRxResolution(pstUartCom_t pCommVar,u8 cmdnum)
{
    emCmdFuncStaType l_state = emCmdSucess;
    return l_state;
}

//eFunc_SetTxHdcpMode,
static emCmdFuncStaType mapp_CmdfuncSetTxHdcpMode(pstUartCom_t pCommVar,u8 cmdnum)
{
    emCmdFuncStaType l_state = emCmdSucess;
    return l_state;
}


//eFunc_GetTxHdcpMode,
static emCmdFuncStaType mapp_CmdfuncGetTxHdcpMode(pstUartCom_t pCommVar,u8 cmdnum)
{
    emCmdFuncStaType l_state = emCmdSucess;
    return l_state;
}

//eFunc_SetTxFormat,
static emCmdFuncStaType mapp_CmdfuncSetTxFormat(pstUartCom_t pCommVar,u8 cmdnum)
{
    emCmdFuncStaType l_state = emCmdSucess;

    return l_state;
}


//eFunc_GetTxFormat,
static emCmdFuncStaType mapp_CmdfuncGetTxFormat(pstUartCom_t pCommVar,u8 cmdnum)
{
    emCmdFuncStaType l_state = emCmdSucess;
    return l_state;
}


//eFunc_SetFreezeState,
static emCmdFuncStaType mapp_CmdfuncSetFreezeState(pstUartCom_t pCommVar,u8 cmdnum)
{
    emCmdFuncStaType l_state = emCmdSucess;
    return l_state;
}

//eFunc_GetFreezeState
static emCmdFuncStaType mapp_CmdfuncGetFreezeState(pstUartCom_t pCommVar,u8 cmdnum)
{
    emCmdFuncStaType l_state = emCmdSucess;

    return l_state;
}

//eFunc_SwitchFreeze,
static emCmdFuncStaType mapp_CmdfuncSwitchFreeze(pstUartCom_t pCommVar,u8 cmdnum)
{
    emCmdFuncStaType l_state = emCmdSucess;

    return l_state;
}

//eFunc_SetBrightness,
static emCmdFuncStaType mapp_CmdfuncSetBrightness(pstUartCom_t pCommVar,u8 cmdnum)
{
    emCmdFuncStaType l_state = emCmdSucess;

    return l_state;
}

//eFunc_GetBrightness,
static emCmdFuncStaType mapp_CmdfuncGetBrightness(pstUartCom_t pCommVar,u8 cmdnum)
{
    emCmdFuncStaType l_state = emCmdSucess;
    return l_state;
}


//eFunc_SetContrast,
static emCmdFuncStaType mapp_CmdfuncSetContrast(pstUartCom_t pCommVar,u8 cmdnum)
{
    emCmdFuncStaType l_state = emCmdSucess;

    return l_state;
}


//eFunc_GetContrast,
static emCmdFuncStaType mapp_CmdfuncGetContrast(pstUartCom_t pCommVar,u8 cmdnum)
{
    emCmdFuncStaType l_state = emCmdSucess;
    return l_state;
}


//eFunc_SetSaturation,
static emCmdFuncStaType mapp_CmdfuncSetSaturation(pstUartCom_t pCommVar,u8 cmdnum)
{
    emCmdFuncStaType l_state = emCmdSucess;

    return l_state;
}


//eFunc_GetSaturation,
static emCmdFuncStaType mapp_CmdfuncGetSaturation(pstUartCom_t pCommVar,u8 cmdnum)
{
    emCmdFuncStaType l_state = emCmdSucess;

    return l_state;
}


//eFunc_SetHue,
static emCmdFuncStaType mapp_CmdfuncSetHue(pstUartCom_t pCommVar,u8 cmdnum)
{
    emCmdFuncStaType l_state = emCmdSucess;
    return l_state;
}


//eFunc_GetHue,
static emCmdFuncStaType mapp_CmdfuncGetHue(pstUartCom_t pCommVar,u8 cmdnum)
{
    emCmdFuncStaType l_state = emCmdSucess;

    return l_state;
}

//eFunc_SetRxEdidMode,
static emCmdFuncStaType mapp_CmdfuncSetRxEdidMode(pstUartCom_t pCommVar,u8 cmdnum)
{
    emCmdFuncStaType l_state = emCmdSucess;
    return l_state;
}

//eFunc_UpdateUserEdid,
static emCmdFuncStaType mapp_CmdfuncUpdateUserEdid(pstUartCom_t pCommVar,u8 cmdnum)
{
    emCmdFuncStaType l_state = emCmdSucess;
    return l_state;
}

//eFunc_GetTxEdidData
static emCmdFuncStaType mapp_CmdfuncGetTxEdidData(pstUartCom_t pCommVar,u8 cmdnum)
{
    emCmdFuncStaType l_state = emCmdSucess;

    return l_state;
}

//eFunc_SetTxTiming
static emCmdFuncStaType mapp_CmdfuncSetTxTiming(pstUartCom_t pCommVar,u8 cmdnum)
{
    emCmdFuncStaType l_state = emCmdSucess;

    return l_state;
}

//eFunc_SetTxPattern
static emCmdFuncStaType mapp_CmdfuncSetTxPattern(pstUartCom_t pCommVar,u8 cmdnum)
{
    emCmdFuncStaType l_state = emCmdSucess;

    return l_state;
}

//eFunc_GetTxPattern,
static emCmdFuncStaType mapp_CmdfuncGetTxPattern(pstUartCom_t pCommVar,u8 cmdnum)
{
    emCmdFuncStaType l_state = emCmdSucess;
    return l_state;
}

//eFunc_SetColor,
static emCmdFuncStaType mapp_CmdfuncSetColor(pstUartCom_t pCommVar,u8 cmdnum)
{
    emCmdFuncStaType l_state = emCmdSucess;
    return l_state;
}

//eFunc_GetColor,
static emCmdFuncStaType mapp_CmdfuncGetColor(pstUartCom_t pCommVar,u8 cmdnum)
{
    emCmdFuncStaType l_state = emCmdSucess;
    return l_state;
}

//eFunc_SetDebugEn
static emCmdFuncStaType mapp_CmdfuncSetDebugEn(pstUartCom_t pCommVar,u8 cmdnum)
{
    emCmdFuncStaType l_state = emCmdSucess;

    return l_state;
}

//eFunc_SetMs1826Hold
static emCmdFuncStaType mapp_CmdfuncSetMs1826Hold(pstUartCom_t pCommVar,u8 cmdnum)
{
    emCmdFuncStaType l_state = emCmdSucess;

    return l_state;
}

//eFunc_BypassSwitchPort
static emCmdFuncStaType mapp_CmdfuncBypassSwitchPort(pstUartCom_t pCommVar,u8 cmdnum)
{
    emCmdFuncStaType l_state = emCmdSucess;
    return l_state;

}

//eFunc_ModeSwitch
static emCmdFuncStaType mapp_CmdfuncModeSwitch(pstUartCom_t pCommVar,u8 cmdnum)
{
    emCmdFuncStaType l_state = emCmdSucess;
    return l_state;
}

//eFunc_FactoryReset2
static emCmdFuncStaType mapp_CmdfuncFactoryReset2(pstUartCom_t pCommVar,u8 cmdnum)
{
    return emCmdSucess;
}

//eFunc_CheckOutputCardType,
static emCmdFuncStaType mapp_CmdfuncCheckOutputCardType(pstUartCom_t pCommVar,u8 cmdnum)
{
    emCmdFuncStaType l_state = emCmdSucess;
    return l_state;
}

//eFunc_CheckCardFWVersion
static emCmdFuncStaType mapp_CmdfuncCheckCardFWVersion(pstUartCom_t pCommVar,u8 cmdnum)
{
    emCmdFuncStaType l_state = emCmdSucess;
    return l_state;
}

//eFunc_CheckYBJCardType
static emCmdFuncStaType mapp_CmdfuncCheckYBJCardType(pstUartCom_t pCommVar,u8 cmdnum)
{
    emCmdFuncStaType l_state = emCmdSucess;
    return l_state;
}

//eFunc_CheckYBJ2CardType
static emCmdFuncStaType mapp_CmdfuncCheckYBJ2CardType(pstUartCom_t pCommVar,u8 cmdnum)
{
    emCmdFuncStaType l_state = emCmdSucess;
    return l_state;
}

//eFunc_CheckCardMode
static emCmdFuncStaType mapp_CmdfuncCheckCardMode(pstUartCom_t pCommVar,u8 cmdnum)
{
    emCmdFuncStaType l_state = emCmdSucess;
    return l_state;
}

//eFunc_CheckSetEdidData
static emCmdFuncStaType mapp_CmdfuncCheckSetEdidData(pstUartCom_t pCommVar,u8 cmdnum)
{
    emCmdFuncStaType l_state = emCmdSucess;

    return l_state;
}

bool app_SwitchResolution(u8 u8Tx,u8 u8ResID)
{
    bool l_bRetVal = FALSE;
    return l_bRetVal;
}

u8 app_GetCmdResolutionID(u8 u8ResID)
{
	return 0;
}

/****************************************************
Function:    	mapp_All_AudioOutput_Ctrl
Description: 	总音频开关
OnOff: 			0:关闭,1:打开
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_All_AudioOutput_Ctrl(u8 OnOff)
{
	u8 Command[6] = {0xAA,0x01,0,0,0,0};
	Command[3] = OnOff;
	dbg_printf("All_AudioOutput:%d\r\n",OnOff);
	app_All_AudioOutput_Ctrl(0,Command);
}
/****************************************************
Function:    	mapp_SET_Input_Sensitivity
Description: 	输入源灵敏度
channel: 		输入通道
parameter1：		灵敏度(0dB、6dB、12dB、18dB、24dB、30dB、36dB、42dB、48dB)
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_Sensitivity(u8 channel,u8 parameter1)
{
	dbg_printf("Input_Sensitivity,ch%d,parameter1:%d\r\n",channel,parameter1);
}
/****************************************************
Function:    	mapp_SET_Input_Gain
Description: 	输入增益,增益值(-72.0~12.0)
channel: 		输入通道
parameter1：		整数部分
parameter2：		小数部分(后1位)
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_Gain(u8 channel,u8 parameter1, u8 parameter2)
{
	u8 Command[6] = {0xAA,0x03,0,0,0,0};
	Command[2] = channel;
	Command[3] = parameter1;
	Command[4] = parameter2;
	app_Input_Gain(0,Command);

	char f[10];
	if(parameter1&0x80)
	{
		parameter1 = parameter1&0x7f;
		sprintf(f,"-%.1f",(float)(parameter1+parameter2/10.0));
		dbg_printf("Input_Gain,ch:%d,value:%s\r\n", channel,f);
	}else{
		sprintf(f,"%.1f",(float)(parameter1+parameter2/10.0));
		dbg_printf("Input_Gain,ch:%d,value:%s\r\n", channel, f);
	}
}
/****************************************************
Function:    	mapp_SET_Input_Mute
Description: 	输入静音
channel: 		输入通道
parameter1：		0:关闭静音,1:打开静音
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_Mute(u8 channel,u8 OnOff)
{
	u8 Command[6] = {0xAA,0x04,0,0,0,0};
	Command[2] = channel;
	Command[3] = OnOff;
	app_Input_Mute(0,Command);
	dbg_printf("Input_Mute,ch%d,OnOff:%d\r\n",channel,OnOff);
}
/****************************************************
Function:    	mapp_SET_Input_Reverse_phase
Description: 	输入反相
channel: 		输入通道
parameter1：		0:关闭反相,1:打开反相
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_Reverse_phase(u8 channel,u8 OnOff)
{
	u8 Command[6] = {0xAA,0x05,0,0,0,0};
	Command[2] = channel;
	Command[3] = OnOff;
	app_Input_Reverse_phase(0,Command);
	dbg_printf("Input_Reverse_phase,ch%d,OnOff:%d\r\n",channel,OnOff);
}
/****************************************************
Function:    	mapp_SET_Input_Test_Signal_Freq
Description: 	输入通道测试信号开关
channel: 		输入通道
OnOff			0:关闭,1:打开
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_TestSignal_Ctrl(u8 channel,u8 OnOff)
{
	u8 Command[6] = {0xAA,0x06,0,0,0,0};
	Command[2] = channel;
	Command[3] = OnOff;
	app_Input_TestSignal_Ctrl(0,Command);
	dbg_printf("Input_TestSignal,ch%d,OnOff:%d\r\n",channel,OnOff);
}
/****************************************************
Function:    	mapp_SET_Input_Test_Signal_Freq
Description: 	输入通道测试信号频率,频率(20~20000)
channel: 		输入通道
parameter1:		数据高8位
parameter2:		数据低8位
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_TestSignal_Freq(u8 channel,u8 parameter1, u8 parameter2)
{
	u8 Command[6] = {0xAA,0x07,0,0,0,0};
	Command[2] = channel;
	Command[3] = parameter1;
	Command[4] = parameter2;
	app_Input_TestSignal_Freq(0,Command);
	dbg_printf("Input_TestSignal_Freq,ch%d,freq:%d\r\n",channel,(parameter1<<8)+parameter2);
}
/****************************************************
Function:    	mapp_SET_Input_Test_Signal_Level
Description: 	输入通道测试信号电平, 电平(-72.0~0.0)
channel: 		输入通道
parameter1:		数据整数部分
parameter2:		数据小数部分(后1位)
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_TestSignal_Level(u8 channel,u8 parameter1, u8 parameter2)
{	
	u8 Command[6] = {0xAA,0x08,0,0,0,0};
	Command[2] = channel;
	Command[3] = parameter1;
	Command[4] = parameter2;
	app_Input_TestSignal_Level(0,Command);
	char f[10];
	if(parameter1&0x80)
	{
		parameter1 = parameter1&0x7f;
		sprintf(f,"-%.1f",(float)(parameter1+parameter2/10.0));
		dbg_printf("TestSignal_Level,ch:%d,value:%s\r\n", channel,f);
	}else{
		sprintf(f,"%.1f",(float)(parameter1+parameter2/10.0));
		dbg_printf("TestSignal_Level,ch:%d,value:%s\r\n", channel, f);
	}
}
/****************************************************
Function:    	mapp_SET_Input_Compressor_Ctrl
Description: 	输入通道压缩器开关
channel: 		输入通道
OnOff:			0:关闭,1:打开
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_Compressor_Ctrl(u8 channel,u8 OnOff)
{
	dbg_printf("Input_Compressor,ch%d,OnOff:%d\r\n",channel,OnOff);
}
/****************************************************
Function:    	mapp_SET_Input_Compressor_Ctrl
Description: 	输入通道压缩器增益,增益(-72.0~6.0)
channel: 		输入通道
parameter1:		整数部分
parameter1:		小数部分(后1位)
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_Compressor_Gain(u8 channel,u8 parameter1,u8 parameter2)
{
	char f[10];
	if(parameter1&0x80)
	{
		parameter1 = parameter1&0x7f;
		sprintf(f,"-%.1f",(float)(parameter1+parameter2/10.0));
		dbg_printf("Compressor_Gain,ch:%d,value:%s\r\n", channel,f);
	}else{
		sprintf(f,"%.1f",(float)(parameter1+parameter2/10.0));
		dbg_printf("Compressor_Gain,ch:%d,value:%s\r\n", channel, f);
	}
}
/****************************************************
Function:    	mapp_SET_Input_Compressor_Threshold
Description: 	输入通道压缩器阈值,阈值(-48.0~0.0)
channel: 		输入通道
parameter1:		整数部分
parameter1:		小数部分(后1位)
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_Compressor_Threshold(u8 channel,u8 parameter1,u8 parameter2)
{
	char f[10];
	if(parameter1&0x80)
	{
		parameter1 = parameter1&0x7f;
		sprintf(f,"-%.1f",(float)(parameter1+parameter2/10.0));
		dbg_printf("Compressor_Threshold,ch:%d,value:%s\r\n", channel,f);
	}else{
		sprintf(f,"%.1f",(float)(parameter1+parameter2/10.0));
		dbg_printf("Compressor_Threshold,ch:%d,value:%s\r\n", channel, f);
	}
}
/****************************************************
Function:    	mapp_SET_Input_Compressor_Ratio
Description: 	输入通道压缩器比率,比率(1.00~20.00)
channel: 		输入通道
parameter1:		整数部分
parameter2:		小数部分(后2位)
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_Compressor_Ratio(u8 channel,u8 parameter1,u8 parameter2)
{
	char f[10];
	if(parameter1&0x80)
	{
		parameter1 = parameter1&0x7f;
		sprintf(f,"-%.2f",(float)(parameter1+parameter2/100.00));
		dbg_printf("Compressor_Threshold,ch:%d,value:%s\r\n", channel,f);
	}else{
		sprintf(f,"%.2f",(float)(parameter1+parameter2/100.00));
		dbg_printf("Compressor_Threshold,ch:%d,value:%s\r\n", channel, f);
	}
}
/****************************************************
Function:    	mapp_SET_Input_Compressor_StartTime
Description: 	输入通道压缩器启动时间,启动时间(1~500ms)
channel: 		输入通道
parameter1:		数据高8位
parameter2:		数据低8位
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_Compressor_StartTime(u8 channel,u8 parameter1,u8 parameter2)
{
	dbg_printf("Input_Compressor_StartTime,ch%d,value:%d\r\n",channel,(parameter1<<8)+parameter2);	
}
/****************************************************
Function:    	mapp_SET_Input_Compressor_Release_Time
Description: 	输入通道压缩器释放时间,释放时间(1~10000ms)
channel: 		输入通道
parameter1:		数据高8位
parameter2:		数据低8位
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_Compressor_ReleaseTime(u8 channel,u8 parameter1,u8 parameter2)
{
	dbg_printf("Input_Compressor_ReleaseTime,ch%d,value:%d\r\n",channel,(parameter1<<8)+parameter2);		
}
/****************************************************
Function:    	mapp_SET_Input_AutoGain_Ctrl
Description: 	输入通道自动增益开关
channel: 		输入通道
OnOff:			0:关闭,1:打开
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_AutoGain_Ctrl(u8 channel,u8 OnOff)
{
	dbg_printf("Input_AutoGain,ch%d,OnOff:%d\r\n",channel,OnOff);
}
/****************************************************
Function:    	mapp_SET_Input_AutoGain_Threshold
Description: 	输入通道自动增益阈值,阈值(-72.0~-20.0)
channel: 		输入通道
parameter1:		整数部分
parameter2:		小数部分(后1位)
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_AutoGain_Threshold(u8 channel,u8 parameter1,u8 parameter2)
{
	char f[10];
	if(parameter1&0x80)
	{
		parameter1 = parameter1&0x7f;
		sprintf(f,"-%.1f",(float)(parameter1+parameter2/10.0));
		dbg_printf("AutoGain_Threshold,ch:%d,value:%s\r\n", channel,f);
	}else{
		sprintf(f,"%.1f",(float)(parameter1+parameter2/10.0));
		dbg_printf("AutoGain_Threshold,ch:%d,value:%s\r\n", channel, f);
	}
}
/****************************************************
Function:    	mapp_SET_Input_AutoGain_Threshold
Description: 	输入通道自动增益目标阈值,目标阈值(-40.0~0.0)
channel: 		输入通道
parameter1:		整数部分
parameter2:		小数部分(后1位)
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_AutoGain_TargetThreshold(u8 channel,u8 parameter1,u8 parameter2)
{
	char f[10];
	if(parameter1&0x80)
	{
		parameter1 = parameter1&0x7f;
		sprintf(f,"-%.1f",(float)(parameter1+parameter2/10.0));
		dbg_printf("AutoGain_TargetThreshold,ch:%d,value:%s\r\n", channel,f);
	}else{
		sprintf(f,"%.1f",(float)(parameter1+parameter2/10.0));
		dbg_printf("AutoGain_TargetThreshold,ch:%d,value:%s\r\n", channel, f);
	}
}
/****************************************************
Function:    	mapp_SET_Input_AutoGain_Threshold
Description: 	输入通道自动增益比率,比率(1~20)
channel: 		输入通道
parameter1:		整数部分
parameter2:		小数部分(后2位)
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_AutoGain_Ratio(u8 channel,u8 parameter1,u8 parameter2)
{
	char f[10];
	if(parameter1&0x80)
	{
		parameter1 = parameter1&0x7f;
		sprintf(f,"-%.2f",(float)(parameter1+parameter2/100.00));
		dbg_printf("AutoGain_Ratio,ch:%d,value:%s\r\n", channel,f);
	}else{
		sprintf(f,"%.2f",(float)(parameter1+parameter2/100.00));
		dbg_printf("AutoGain_Ratio,ch:%d,value:%s\r\n", channel, f);
	}
	
}
/****************************************************
Function:    	mapp_SET_Input_AutoGain_StartTime
Description: 	输入通道自动增益启动时间,启动时间(1~500ms)
channel: 		输入通道
parameter1:		数据高8位
parameter2:		数据低8位
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_AutoGain_StartTime(u8 channel,u8 parameter1,u8 parameter2)
{
	dbg_printf("Input_AutoGain_StartTime,ch%d,value:%d\r\n",channel,(parameter1<<8)+parameter2);		
}
/****************************************************
Function:    	mapp_SET_Input_AutoGain_ReleaseTime
Description: 	输入通道自动增益释放时间,释放时间(1~10000ms)
channel: 		输入通道
parameter1:		数据高8位
parameter2:		数据低8位
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_AutoGain_ReleaseTime(u8 channel,u8 parameter1,u8 parameter2)
{
	dbg_printf("Input_AutoGain_ReleaseTime,ch%d,value:%d\r\n",channel,(parameter1<<8)+parameter2);	
}
/****************************************************
Function:    	mapp_SET_Input_AutoGain_ReleaseTime
Description: 	输入通道参量均衡某段类型
channel: 		输入通道
parameter1:		某段(0~9)
parameter2:		类型
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_EQ_Type(u8 channel,u8 parameter1,u8 parameter2)
{
	dbg_printf("Input_EQ_Type,ch%d,parameter1:%d,parameter2:%d\r\n",channel,parameter1,parameter2);	
}
/****************************************************
Function:		mapp_SET_Input_AutoGain_ReleaseTime
Description:	输入通道参量均衡某段增益(-24.0~18.0)
channel:		输入通道
parameter1: 	某段(0~9)
parameter2: 	整数部分
parameter3: 	小数部分(后1位)
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_EQ_Gain(unsigned int channel,unsigned int parameter1,unsigned int parameter2,unsigned int parameter3)
{
	char f[10];
	if(parameter2&0x80)
	{
		parameter2 = parameter2&0x7f;
		sprintf(f,"-%.1f",(float)(parameter2+parameter3/10.0));
		dbg_printf("Input_EQ_Gain,ch:%d,parameter1:%d,value:%s\r\n", channel, parameter1, f);
	}else{
		sprintf(f,"%.1f",(float)(parameter2+parameter3/10.0));
		dbg_printf("Input_EQ_Gain,ch:%d,parameter1:%d,value:%s\r\n", channel, parameter1, f);
	}
}
/****************************************************
Function:		mapp_SET_Input_EQ_QualityFactor
Description:	输入通道参量均衡某段品质因数(0.02~50.00)
channel:		输入通道
parameter1: 	某段(0~9)
parameter2: 	整数部分
parameter3: 	小数部分(后2位)
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_EQ_QualityFactor(u8 channel,u8 parameter1,u8 parameter2,u8 parameter3)
{
	char f[10];
	if(parameter2&0x80)
	{
		parameter1 = parameter1&0x7f;
		sprintf(f,"-%.2f",(float)(parameter2+parameter3/100.00));
		dbg_printf("EQ_QualityFactor,ch:%d,parameter1:%d,value:%s\r\n", channel,parameter1,f);
	}else{
		sprintf(f,"%.2f",(float)(parameter2+parameter3/100.00));
		dbg_printf("EQ_QualityFactor,ch:%d,parameter1:%d,value:%s\r\n", channel,parameter1,f);
	}
}
/****************************************************
Function:		mapp_SET_Input_EQ_Ctrl
Description:	输入通道参量均衡某段开关
channel:		输入通道
parameter1: 	某段(0~9)
OnOff: 			0:关闭,1:打开
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_EQ_Ctrl(u8 channel,u8 parameter1,u8 OnOff)
{
	dbg_printf("EQ_Ctrl,ch%d,parameter1:%d,OnOff:%d\r\n",channel,parameter1,OnOff);	
}
/****************************************************
Function:		mapp_SET_Input_HowlingSuppressor_Ctrl
Description:	啸叫抑制器开关
channel:		输入通道
parameter1: 	0:关闭,1:打开
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_HowlingSuppressor_Ctrl(u8 channel,u8 OnOff)
{
	dbg_printf("HowlingSuppressor_Ctrl,ch%d,OnOff:%d\r\n",channel,OnOff);	
	
}
/****************************************************
Function:		mapp_SET_Input_HowlingSuppressor_Grade
Description:	啸叫抑制器等级
parameter1: 	等级(0~10)
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_HowlingSuppressor_Grade(u8 parameter1)
{
	dbg_printf("HowlingSuppressor_Grade,parameter1:%d\r\n",parameter1);	
}
/****************************************************
Function:		mapp_SET_Input_HowlingSuppressor_FreqShift
Description:	啸叫抑制器移频参数
parameter1: 	移频参数( -7,-5,-3,+3，+5,+7)
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_HowlingSuppressor_FreqShift(u8 parameter1)
{
	dbg_printf("HowlingSuppressor_FreqShift,parameter1:%d\r\n",parameter1);		
}
/****************************************************
Function:		mapp_SET_Input_NoiseSuppressor_Grade
Description:	噪声抑制器等级
parameter1: 	等级(0~10)
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_NoiseSuppressor_Grade(u8 parameter1)
{
	dbg_printf("NoiseSuppressor_Gradet,parameter1:%d\r\n",parameter1);		
	
}
/****************************************************
Function:		mapp_SET_Input_NoiseSuppressor_Threshold
Description:	噪声抑制器阈值(-90.0~0.0)
parameter1: 	整数部分
parameter2: 	小数部分(后1位)
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_NoiseSuppressor_Threshold(u8 parameter1,u8 parameter2)
{
	char f[10];
	if(parameter1&0x80)
	{
		parameter1 = parameter1&0x7f;
		sprintf(f,"-%.1f",(float)(parameter1+parameter2/10.0));
		dbg_printf("NoiseSuppressor_Threshold,value:%s\r\n", f);
	}else{
		sprintf(f,"%.1f",(float)(parameter1+parameter2/10.0));
		dbg_printf("NoiseSuppressor_Threshold,value:%s\r\n", f);
	}
	
}
/****************************************************
Function:		mapp_SET_Input_NoiseSuppressor_Ratio
Description:	噪声抑制器比率(1.00~20.00)
parameter1: 	整数部分
parameter2: 	小数部分(后2位)
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_NoiseSuppressor_Ratio(u8 parameter1,u8 parameter2)
{
	char f[10];
	if(parameter1&0x80)
	{
		parameter1 = parameter1&0x7f;
		sprintf(f,"-%.2f",(float)(parameter1+parameter2/100.00));
		dbg_printf("NoiseSuppressor_Ratio,value:%s\r\n", f);
	}else{
		sprintf(f,"%.2f",(float)(parameter1+parameter2/100.00));
		dbg_printf("NoiseSuppressor_Ratio,value:%s\r\n", f);
	}	
}
/****************************************************
Function:		mapp_SET_Input_NoiseSuppressor_StartTime
Description:	噪声抑制器启动时间(0~7500)
parameter1: 	数据高8位
parameter2: 	数据低8位
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_NoiseSuppressor_StartTime(u8 parameter1,u8 parameter2)
{
	dbg_printf("NoiseSuppressor_StartTime,value:%d\r\n", (parameter1<<8)+parameter2);
	
}
/****************************************************
Function:		mapp_SET_Input_NoiseSuppressor_ReleaseTime
Description:	噪声抑制器释放时间(0~7500)
parameter1: 	数据高8位
parameter2: 	数据低8位
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_NoiseSuppressor_ReleaseTime(u8 parameter1,u8 parameter2)
{
	dbg_printf("NoiseSuppressor_ReleaseTime,value:%d\r\n", (parameter1<<8)+parameter2);
	
}
/****************************************************
Function:		mapp_SET_Input_NoiseSuppressor_Ctrl
Description:	噪声抑制器开关(0~7500)
channel: 		通道
parameter1: 	0:关闭,1:打开
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_NoiseSuppressor_Ctrl(u8 channel,u8 OnOff)
{
	dbg_printf("NoiseSuppressor_Ctrl,ch:%d, OnOff:%d\r\n", channel, OnOff);
	
}
/****************************************************
Function:		mapp_SET_Input_EchoCanceller_Ctrl
Description:	回声消除器开关
channel:		通道
parameter1: 	0:关闭,1:打开
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_EchoCanceller_Ctrl(u8 channel,u8 OnOff)
{
	dbg_printf("EchoCanceller_Ctrl,ch:%d, OnOff:%d\r\n", channel, OnOff);
	
}
/****************************************************
Function:		mapp_SET_Input_EchoCanceller_Grade
Description:	回声消除器等级
channel:		通道
parameter1: 	等级(0~10)
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_EchoCanceller_Grade(u8 channel,u8 parameter1)
{
	dbg_printf("EchoCanceller_Grade,ch:%d, parameter1:%d\r\n", channel, parameter1);
}
/****************************************************
Function:		mapp_SET_Input_Exciter_Ctrl
Description:	激励器开关
channel:		通道
parameter1: 	0:关闭,1:打开
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_Exciter_Ctrl(u8 channel,u8 OnOff)
{
	dbg_printf("Exciter_Ctrl,ch:%d, OnOff:%d\r\n", channel, OnOff);
}
/****************************************************
Function:		mapp_SET_Input_HfreqExciter_Grade
Description:	高频激励器等级
channel:		通道
parameter1: 	等级(0~8)
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_HfreqExciter_Grade(u8 channel,u8 parameter1)
{
	dbg_printf("HfreqExciter_Grade,ch:%d, parameter1:%d\r\n", channel, parameter1);
}
/****************************************************
Function:		mapp_SET_Input_LfreqExciter_Grade
Description:	低频激励器等级
channel:		通道
parameter1: 	等级(0~8)
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_LfreqExciter_Grade(u8 channel,u8 parameter1)
{
	dbg_printf("LfreqExciter_Grade,ch:%d, parameter1:%d\r\n", channel, parameter1);
	
}
/****************************************************
Function:		mapp_SET_Input_CallInput
Description:	呼叫输入设置
channel:		通道
parameter1: 	0:取消设置,1:设置为呼叫输入
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_CallInput(u8 channel,u8 OnOff)
{
	dbg_printf("BackgroundInput,ch:%d, OnOff:%d\r\n", channel, OnOff);
}
/****************************************************
Function:		mapp_SET_Input_BackgroundInput
Description:	背景输入设置
channel:		通道
parameter1: 	0:取消设置,1:设置为背景输入
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_BackgroundInput(u8 channel,u8 OnOff)
{
	dbg_printf("BackgroundInput,ch:%d, OnOff:%d\r\n", channel, OnOff);
}
/****************************************************
Function:		mapp_SET_Input_Ducking_Gain
Description:	闪避器增益(-72.0~12.0)
channel:		通道
parameter1: 	整数部分
parameter2: 	小数部分(后1位)
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_Ducking_Gain(u8 channel,u8 parameter1,u8 parameter2)
{
	char f[10];
	if(parameter1&0x80)
	{
		parameter1 = parameter1&0x7f;
		sprintf(f,"-%.1f",(float)(parameter1+parameter2/10.0));
		dbg_printf("Ducking_Gai,ch:%d,value:%s\r\n", channel, f);
	}else{
		sprintf(f,"%.2f",(float)(parameter1+parameter2/10.0));
		dbg_printf("Ducking_Gai,value:%s\r\n", channel, f);
	}	


}
/****************************************************
Function:		mapp_SET_Input_Ducking_Threshold
Description:	闪避器阈值(-60.0~20.0)
parameter1: 	整数部分
parameter2: 	小数部分(后1位)
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_Ducking_Threshold(u8 parameter1,u8 parameter2)
{
	char f[10];
	if(parameter1&0x80)
	{
		parameter1 = parameter1&0x7f;
		sprintf(f,"-%.1f",(float)(parameter1+parameter2/10.0));
		dbg_printf("Ducking_Threshold,value:%s\r\n", f);
	}else{
		sprintf(f,"%.2f",(float)(parameter1+parameter2/10.0));
		dbg_printf("Ducking_Threshold,value:%s\r\n", f);
	}	
}
/****************************************************
Function:		mapp_SET_Input_Ducking_Depth
Description:	闪避器深度(0.0~96.0)
parameter1: 	整数部分
parameter2: 	小数部分(后1位)
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_Ducking_Depth(u8 parameter1,u8 parameter2)
{
	char f[10];
	if(parameter1&0x80)
	{
		parameter1 = parameter1&0x7f;
		sprintf(f,"-%.1f",(float)(parameter1+parameter2/10.0));
		dbg_printf("Ducking_Depth,value:%s\r\n", f);
	}else{
		sprintf(f,"%.2f",(float)(parameter1+parameter2/10.0));
		dbg_printf("Ducking_Depth,value:%s\r\n", f);
	}	
}
/****************************************************
Function:		mapp_SET_Input_Ducking_StartTime
Description:	闪避器启动时间(10~10000)
parameter1: 	数据高8位
parameter2: 	数据低8位
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_Ducking_StartTime(u8 parameter1,u8 parameter2)
{
	dbg_printf("Ducking_StartTime, value:%d\r\n", (parameter1<<8)+parameter2);
}
/****************************************************
Function:		mapp_SET_Input_Ducking_HoldTime
Description:	闪避器保持时间(5~500)
parameter1: 	数据高8位
parameter2: 	数据低8位
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_Ducking_HoldTime(u8 parameter1,u8 parameter2)
{
	dbg_printf("Ducking_HoldTime, value:%d\r\n", (parameter1<<8)+parameter2);
}
/****************************************************
Function:		mapp_SET_Input_Ducking_ReleaseTime
Description:	闪避器释放时间(10~30000)
parameter1: 	数据高8位
parameter2: 	数据低8位
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_Ducking_ReleaseTime(u8 parameter1,u8 parameter2)
{
	dbg_printf("Ducking_ReleaseTime, value:%d\r\n", (parameter1<<8)+parameter2);
}
/****************************************************
Function:		mapp_SET_Input_Ducking_Ctrl
Description:	闪避器开关
parameter1: 	0:关闭,1:打开
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_Ducking_Ctrl(u8 OnOff)
{
	dbg_printf("Ducking_Ctrl, OnOff:%d\r\n", OnOff);
}
/****************************************************
Function:		mapp_SET_Input_Ducking_MatrixSwitching
Description:	矩阵切换
parameter1: 	输出通道
parameter2: 	输入通道
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_MatrixSwitching(u8 parameter1,u8 parameter2)
{


}
/****************************************************
Function:		mapp_SET_Output_DelayTime
Description:	输出延时(1~1200)
channel:		通道
parameter1: 	数据高8位
parameter2: 	数据低8位
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Output_DelayTime(u8 channel,u8 parameter1,u8 parameter2)
{


}
/****************************************************
Function:		mapp_SET_Output_Delay_Ctrl
Description:	输出延时开关
channel:		通道
parameter1: 	0:关闭,1:打开
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Output_Delay_Ctrl(u8 channel,u8 parameter1)
{


}
/****************************************************
Function:		mapp_SET_USBplayer_Ctrl
Description:	USB播放器控制
parameter1: 	控制参数(0~4)(上一首,下一首,播放,暂停,停止)
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_USBplayer_Ctrl(u8 parameter1)
{


}

//eFunc_SetCardFunction
static emCmdFuncStaType mapp_CmdfuncSetCardFunction(pstUartCom_t pCommVar,u8 cmdnum)
{
    emCmdFuncStaType l_state = emCmdNone;
    char *l_pCmd= pCommVar->pRecBuffer+strlen(cmd_list[cmdnum].ucmd);
    u8 l_u8CmdType = 0;
    u8 l_u8channel = 0;
    u8 parameter1 = 0;
    u8 parameter2 = 0;
    u8 parameter3 = 0;
    dbg_printf("%s\r\n", l_pCmd);
	
	l_u8CmdType = (HexAndAsciiChange(*(l_pCmd+0),0)<<4)+(HexAndAsciiChange(*(l_pCmd+1),0));
	l_u8channel = (HexAndAsciiChange(*(l_pCmd+2),0)<<4)+(HexAndAsciiChange(*(l_pCmd+3),0));
	parameter1 = (HexAndAsciiChange(*(l_pCmd+4),0)<<4)+(HexAndAsciiChange(*(l_pCmd+5),0));
	parameter2 = (HexAndAsciiChange(*(l_pCmd+6),0)<<4)+(HexAndAsciiChange(*(l_pCmd+7),0));
	parameter3 = (HexAndAsciiChange(*(l_pCmd+8),0)<<4)+(HexAndAsciiChange(*(l_pCmd+9),0));
	dbg_printf("l_u8CmdType:%x,l_u8channel:%x,parameter1:%x,parameter2:%x,parameter3:%d\r\n",l_u8CmdType,l_u8channel,parameter1,parameter2,parameter3);
	switch(l_u8CmdType)
	{
		case 0x01://总音频
			mapp_All_AudioOutput_Ctrl(parameter1);
			break;
		case 0x02://输入源灵敏度
			mapp_SET_Input_Sensitivity(l_u8channel, parameter1);
			break;
		case 0x03://输入增益
			mapp_SET_Input_Gain(l_u8channel, parameter1, parameter2);
			break;
		case 0x04://输入静音
			mapp_SET_Input_Mute(l_u8channel, parameter1);
			break;
		case 0x05://输入反相
			mapp_SET_Input_Reverse_phase(l_u8channel, parameter1);
			break;
		case 0x06://输入通道测试信号开关
			mapp_SET_Input_TestSignal_Ctrl(l_u8channel, parameter1);
			break;
		case 0x07://测试信号频率
			mapp_SET_Input_TestSignal_Freq(l_u8channel, parameter1, parameter2);
			break;
		case 0x08://测试信号电平
			mapp_SET_Input_TestSignal_Level(l_u8channel, parameter1, parameter2);
			break;
		case 0x09://输入通道压缩器开关
			mapp_SET_Input_Compressor_Ctrl(l_u8channel, parameter1);
			break;
		case 0x0a://输入压缩器增益
			
			mapp_SET_Input_Compressor_Gain(l_u8channel, parameter1, parameter2);
			break;
		case 0x0b://输入压缩器阈值
			mapp_SET_Input_Compressor_Threshold(l_u8channel, parameter1, parameter2);
			break;
		case 0x0c://输入压缩器比率
			mapp_SET_Input_Compressor_Ratio(l_u8channel, parameter1,parameter2);
			break;
		case 0x0d://输入压缩器启动时间
			mapp_SET_Input_Compressor_StartTime(l_u8channel, parameter1, parameter2);
			break;
		case 0x0e://输入压缩器释放时间
			mapp_SET_Input_Compressor_ReleaseTime(l_u8channel, parameter1, parameter2);
			break;
		case 0x0f://输入通道自动增益开关
			mapp_SET_Input_AutoGain_Ctrl(l_u8channel, parameter1);
			break;
		case 0x10://输入通道自动增益阈值
			mapp_SET_Input_AutoGain_Threshold(l_u8channel, parameter1, parameter2);
			break;
		case 0x11://输入通道自动增益目标阈值
			mapp_SET_Input_AutoGain_TargetThreshold(l_u8channel, parameter1, parameter2);
			break;
		case 0x12://输入通道自动增益比率
			mapp_SET_Input_AutoGain_Ratio(l_u8channel, parameter1, parameter2);
			break;
		case 0x13://输入通道自动增益启动时间
			mapp_SET_Input_AutoGain_StartTime(l_u8channel, parameter1, parameter2);
			break;
		case 0x14://输入通道自动增益释放时间
			mapp_SET_Input_AutoGain_ReleaseTime(l_u8channel, parameter1, parameter2);
			break;
		case 0x15://输入参量均衡某段类型
			mapp_SET_Input_EQ_Type(l_u8channel, parameter1, parameter2);
			break;
		case 0x16://输入参量均衡某段增益
			mapp_SET_Input_EQ_Gain(l_u8channel, parameter1, parameter2, parameter3);
			break;
		case 0x17://输入参量均衡某段品质因数
			mapp_SET_Input_EQ_QualityFactor(l_u8channel, parameter1, parameter2, parameter3);
			break;
		case 0x18://输入参量均衡某段开关
			mapp_SET_Input_EQ_Ctrl(l_u8channel, parameter1, parameter2);
			break;
		case 0x19://啸叫抑制器开关
			mapp_SET_Input_HowlingSuppressor_Ctrl(l_u8channel, parameter1);
			break;
		case 0x1a://啸叫抑制器等级
			mapp_SET_Input_HowlingSuppressor_Grade(parameter1);
			break;
		case 0x1b://移频参数
			mapp_SET_Input_HowlingSuppressor_FreqShift(parameter1);
			break;
		case 0x1c://噪声抑制等级
			mapp_SET_Input_NoiseSuppressor_Grade(parameter1);
			break;
		case 0x1d://噪声抑制阈值
			mapp_SET_Input_NoiseSuppressor_Threshold(parameter1, parameter2);
			break;
		case 0x1e://噪声抑制比率
			mapp_SET_Input_NoiseSuppressor_Ratio(parameter1, parameter2);
			break;
		case 0x1f://噪声抑制启动时间
			mapp_SET_Input_NoiseSuppressor_StartTime(parameter1, parameter2);
			break;
		case 0x20://噪声抑制释放时间
			mapp_SET_Input_NoiseSuppressor_ReleaseTime(parameter1, parameter2);
			break;
		case 0x21://噪声抑制开关
			mapp_SET_Input_NoiseSuppressor_Ctrl(l_u8channel, parameter1);
			break;
		case 0x22://回声消除等级
			mapp_SET_Input_EchoCanceller_Grade(l_u8channel, parameter1);
			break;
		case 0x23://回声消除开关
			mapp_SET_Input_EchoCanceller_Ctrl(l_u8channel, parameter1);
			break;
		case 0x24://某路低频激励器等级
			mapp_SET_Input_LfreqExciter_Grade(l_u8channel, parameter1);
			break;
		case 0x25://某路高频激励器等级
			mapp_SET_Input_HfreqExciter_Grade(l_u8channel, parameter1);
			break;
		case 0x26://某路激励器开关
			mapp_SET_Input_Exciter_Ctrl(l_u8channel, parameter1);
			break;
		case 0x27://第几路为呼叫输入
			mapp_SET_Input_CallInput(l_u8channel, parameter1);
			break;
		case 0x28://第几路为背景输入
			mapp_SET_Input_BackgroundInput(l_u8channel, parameter1);
			break;
		case 0x29://某一路闪避器增益
			mapp_SET_Input_Ducking_Gain(l_u8channel, parameter1, parameter2);
			break;
		case 0x2a://闪避器阈值
			mapp_SET_Input_Ducking_Threshold(parameter1, parameter2);
			break;
		case 0x2b://闪避器深度
			mapp_SET_Input_Ducking_Depth(parameter1, parameter2);
			break;
		case 0x2c://闪避器启动时间
			mapp_SET_Input_Ducking_StartTime(parameter1, parameter2);
			break;
		case 0x2d://闪避器保持时间
			mapp_SET_Input_Ducking_HoldTime(parameter1, parameter2);
			break;
		case 0x2e://闪避器释放时间
			mapp_SET_Input_Ducking_ReleaseTime(parameter1, parameter2);
			break;
		case 0x2f://闪避器开关
			mapp_SET_Input_Ducking_Ctrl(parameter1);
			break;
		case 0x30://矩阵切换
			mapp_SET_MatrixSwitching(parameter1, parameter2);
			break;
		case 0x31://输出延时时间
			mapp_SET_Output_DelayTime(l_u8channel, parameter1, parameter2);
			break;
		case 0x32://输入延时开关
			mapp_SET_Output_Delay_Ctrl(l_u8channel, parameter1);
			break;
		case 0x33://USB播放控制
			mapp_SET_USBplayer_Ctrl(parameter1);
			break;
		default:
			break;
	}
    return l_state;
}

//eFunc_SetSTKCardFunction
static emCmdFuncStaType mapp_CmdfuncSetSTKCardFunction(pstUartCom_t pCommVar,u8 cmdnum)
{
    emCmdFuncStaType l_state = emCmdNone;

    return l_state;
}

//===============================================================================
//Function process
//===============================================================================
void  mapp_SetCommandFunctionID(eCmdFun_t cmdfuncid)
{
    cmdfunctionID = cmdfuncid;
}

eCmdFun_t  mapp_GetCommandFunctionID(void)
{
    return cmdfunctionID;
}

//***********************************************************
//@Function name:    mapp_CommandFunctionProcess
//@Input:   u8 flag 标志 , char *cmd 指令集
//@Output: l_bStatus 是否执行成功
//@Description: 根据功能标志，执行相应的功能函数
//              预留了标志位，还有修改的空间
//***********************************************************
emCmdFuncStaType mapp_CommandFunctionProcess(u8 cmdnum,u8 flag,pstUartCom_t pCommVar)
{
    emCmdFuncStaType l_bStatus=emCmdError;

    UNUSED(flag);
    //UNUSED(cmdnum);
    switch( mapp_GetCommandFunctionID())
    {
        case eFunc_GetVersion:
            {
                l_bStatus = mapp_CmdfuncGetVersion(pCommVar,cmdnum);
            }
            break;
        case eFunc_FactoryReset:
            {
                l_bStatus = mapp_CmdfuncFactoryReset(pCommVar,cmdnum);
            }
            break;
        case eFunc_Reboot:
            {
                l_bStatus = mapp_CmdfuncReboot(pCommVar,cmdnum);
            }
            break;
        case eFunc_GetTestVersion:
            {
                l_bStatus = mapp_CmdfuncGetTestVersion(pCommVar,cmdnum);
            }
            break;

        case eFunc_SwitchInputPort:
            {
                l_bStatus = mapp_CmdfuncSwitchInputPort(pCommVar,cmdnum);
            }
            break;
        case eFunc_GetInputStutus:
            {
                l_bStatus = mapp_CmdfuncGetInputStutus(pCommVar,cmdnum);
            }
            break;
        case eFunc_SetTxResolution:
            {
                l_bStatus = mapp_CmdfuncSetTxResolution(pCommVar,cmdnum);
            }
            break;
        case eFunc_GetTxResolution:
            {
                l_bStatus = mapp_CmdfuncGetTxResolution(pCommVar,cmdnum);
            }
            break;
        case eFunc_GetRxResolution:
            {
                l_bStatus = mapp_CmdfuncGetRxResolution(pCommVar,cmdnum);
            }
            break;
        case eFunc_SetTxHdcpMode:
            {
                l_bStatus = mapp_CmdfuncSetTxHdcpMode(pCommVar,cmdnum);
            }
            break;
        case eFunc_GetTxHdcpMode:
            {
                l_bStatus = mapp_CmdfuncGetTxHdcpMode(pCommVar,cmdnum);
            }
            break;
        case eFunc_SetTxFormat:
            {
                l_bStatus = mapp_CmdfuncSetTxFormat(pCommVar,cmdnum);
            }
            break;
        case eFunc_GetTxFormat:
            {
                l_bStatus = mapp_CmdfuncGetTxFormat(pCommVar,cmdnum);
            }
            break;
        case eFunc_SetFreezeState:
            {
                l_bStatus = mapp_CmdfuncSetFreezeState(pCommVar,cmdnum);
            }
            break;
        case eFunc_GetFreezeState:
            {
                l_bStatus = mapp_CmdfuncGetFreezeState(pCommVar,cmdnum);
            }
            break;
        case eFunc_SwitchFreeze:
            {
                l_bStatus = mapp_CmdfuncSwitchFreeze(pCommVar,cmdnum);
            }
            break;

        case eFunc_SetBrightness:
            {
                l_bStatus = mapp_CmdfuncSetBrightness(pCommVar,cmdnum);
            }
            break;
        case eFunc_GetBrightness:
            {
                l_bStatus = mapp_CmdfuncGetBrightness(pCommVar,cmdnum);
            }
            break;
        case eFunc_SetContrast:
            {
                l_bStatus = mapp_CmdfuncSetContrast(pCommVar,cmdnum);
            }
            break;
        case eFunc_GetContrast:
            {
                l_bStatus = mapp_CmdfuncGetContrast(pCommVar,cmdnum);
            }
            break;
        case eFunc_SetSaturation:
            {
                l_bStatus = mapp_CmdfuncSetSaturation(pCommVar,cmdnum);
            }
            break;
        case eFunc_GetSaturation:
            {
                l_bStatus = mapp_CmdfuncGetSaturation(pCommVar,cmdnum);
            }
            break;
        case eFunc_SetHue:
            {
                l_bStatus = mapp_CmdfuncSetHue(pCommVar,cmdnum);
            }
            break;
        case eFunc_GetHue:
            {
                l_bStatus = mapp_CmdfuncGetHue(pCommVar,cmdnum);
            }
            break;
        case eFunc_SetRxEdidMode:
            {
                l_bStatus = mapp_CmdfuncSetRxEdidMode(pCommVar,cmdnum);
            }
            break;
        case eFunc_GetRxEdidMode:
            {
            }
            break;
        case eFunc_UpdateUserEdid:
            {
                l_bStatus = mapp_CmdfuncUpdateUserEdid(pCommVar,cmdnum);
            }
            break;
        case eFunc_GetTxEdidData:
            {
                l_bStatus = mapp_CmdfuncGetTxEdidData(pCommVar,cmdnum);
            }
            break;
        case eFunc_SetTxTiming:
            {
                l_bStatus = mapp_CmdfuncSetTxTiming(pCommVar,cmdnum);
            }
            break;
        case eFunc_SetTxPattern:
            {
                l_bStatus = mapp_CmdfuncSetTxPattern(pCommVar,cmdnum);
            }
            break;
        case eFunc_GetTxPattern:
            {
                l_bStatus = mapp_CmdfuncGetTxPattern(pCommVar,cmdnum);
            }
            break;
        case eFunc_SetColor:
            {
                l_bStatus = mapp_CmdfuncSetColor(pCommVar,cmdnum);
            }
            break;
        case eFunc_GetColor:
            {
                l_bStatus = mapp_CmdfuncGetColor(pCommVar,cmdnum);
            }
            break;
        case eFunc_SetDebugEn:
            {
                l_bStatus = mapp_CmdfuncSetDebugEn(pCommVar,cmdnum);
            }
            break;
        case eFunc_SetMs1826Hold:
            {
                l_bStatus = mapp_CmdfuncSetMs1826Hold(pCommVar,cmdnum);
            }
            break;
        case eFunc_BypassSwitchPort:
            {
                l_bStatus = mapp_CmdfuncBypassSwitchPort(pCommVar,cmdnum);
            }
            break;
        case eFunc_ModeSwitch:
            {
                l_bStatus = mapp_CmdfuncModeSwitch(pCommVar,cmdnum);
            }
            break;
        case eFunc_FactoryReset2:
            {
                l_bStatus = mapp_CmdfuncFactoryReset2(pCommVar,cmdnum);
            }
            break;
        case eFunc_CheckOutputCardType:
            {
                l_bStatus = mapp_CmdfuncCheckOutputCardType(pCommVar,cmdnum);
            }
            break;
        case eFunc_CheckCardFWVersion:
            {
                l_bStatus = mapp_CmdfuncCheckCardFWVersion(pCommVar,cmdnum);
            }
            break;
#if ENABLE_CARD_YBJ_RECORD
        case eFunc_CheckYBJCardType:
            {
                l_bStatus = mapp_CmdfuncCheckYBJCardType(pCommVar,cmdnum);
            }
            break;
        case eFunc_CheckYBJ2CardType:
            {
                l_bStatus = mapp_CmdfuncCheckYBJ2CardType(pCommVar,cmdnum);
            }
            break;
#endif
        case eFunc_CheckCardMode:
            {
                l_bStatus = mapp_CmdfuncCheckCardMode(pCommVar,cmdnum);
            }
            break;
        case eFunc_CheckSetEdidData:
            {
                l_bStatus = mapp_CmdfuncCheckSetEdidData(pCommVar,cmdnum);
            }
            break;

        case eFunc_SetCardFunction:
            {
                l_bStatus = mapp_CmdfuncSetCardFunction(pCommVar,cmdnum);
            }
            break;
        case eFunc_SetSTKCardFunction:
            {
                l_bStatus = mapp_CmdfuncSetSTKCardFunction(pCommVar,cmdnum);
            }
            break;

        case eFunc_NoUse:
        case eFunc_Max:
        default:
            break;
    }
    if(( mapp_GetCommandFunctionID()!=eFunc_NoUse)&&( mapp_GetCommandFunctionID()!=eFunc_Max))
    {
         mapp_SetCommandFunctionID(eFunc_NoUse);
    }
    return l_bStatus;
}

bool mapp_CmdlenIsOK(u8 index, pstUartCom_t pCommVar)
{
    //RS232_printf("cmdlen:%d\r\n",pCommVar->u16RecCnt);
    if(cmd_list[index].flag&Flag_UserValueLength)
    {
        if((pCommVar->u16RecCnt<=(strlen(cmd_list[index].ucmd)+cmd_list[index].valuelen+cmd_list[index].cmdoffset))
            &&(pCommVar->u16RecCnt>=(strlen(cmd_list[index].ucmd)+cmd_list[index].cmdoffset)))
            return TRUE;
    }
    else
    {
        if(pCommVar->u16RecCnt==(strlen(cmd_list[index].ucmd)+cmd_list[index].valuelen+cmd_list[index].cmdoffset))
            return TRUE;
    }
    return FALSE;
}

void mapp_UsartSystemCmdFun(pstUartCom_t pCommVar)
{
    u8 i;
    u8 l_u8Flag = 0;
    u8 l_u8Cmdnumber = 0;
    emCmdFuncStaType l_bStatus=emCmdError;
    u8 l_u8MatchCnt = 0;
    char *l_ps8StartStr = pCommVar->pRecBuffer;
    char *l_ps8EndStr = l_ps8StartStr;

    //RS232_printf("Cmd:%s",pCommVar->pRecBuffer);
    {
    RecheckCmd:
        l_u8MatchCnt = 0;
        for(i=0;i<MaxCmdNum;i++)
        {
            if(cmd_list[i].eCmdFun==eFunc_Max || cmd_list[i].flag==Flag_End)
            {
                break;
            }
            if((cmd_list[i].flag&Flag_NoFunction)==Flag_NoFunction)
                continue;
            if((cmd_list[i].flag&Flag_HeadMatch)==Flag_HeadMatch)
            {
                if(strncmp(l_ps8StartStr,cmd_list[i].ucmd,strlen(cmd_list[i].ucmd))==0)
                {
                    pCommVar->bIsMultiCmdDetect = TRUE;
                    if(pCommVar->u8MatchCmdCounter<MaxCmdlist)
                    {
                        if(*(l_ps8StartStr+strlen(cmd_list[i].ucmd)-1) != ')')        // 指令不是以')'结尾
                        {
                            if(cmd_list[i].valuelen==0)
                                l_ps8EndStr = FindChar(l_ps8StartStr+strlen(cmd_list[i].ucmd),')',Cmdlength(i)-1);    // delet end char self
                            else
                                l_ps8EndStr = FindChar(l_ps8StartStr+strlen(cmd_list[i].ucmd),')',Cmdlength(i));
                            pCommVar->stMultiCmdType[pCommVar->u8MatchCmdCounter].u8CmdCounter = (char*)l_ps8EndStr-l_ps8StartStr/*+strlen(cmd_list[i].ucmd)*/+1; // 指令结尾加上结束符本身
                        }
                        else
                        {
                            l_ps8EndStr = l_ps8StartStr+strlen(cmd_list[i].ucmd);
                            //l_ps8EndStr = FindChar(l_ps8StartStr+strlen(cmd_list[i].ucmd),')',Cmdlength(i));
                            pCommVar->stMultiCmdType[pCommVar->u8MatchCmdCounter].u8CmdCounter = (char*)l_ps8EndStr-l_ps8StartStr/*+strlen(cmd_list[i].ucmd)*/;
                        }
                        memcpy(pCommVar->stMultiCmdType[pCommVar->u8MatchCmdCounter].s8MultiCmd,l_ps8StartStr/*-strlen(cmd_list[i].ucmd)*/,pCommVar->stMultiCmdType[pCommVar->u8MatchCmdCounter].u8CmdCounter);
                        memset(l_ps8StartStr,'0',pCommVar->stMultiCmdType[pCommVar->u8MatchCmdCounter].u8CmdCounter);   // 覆盖已识别的指令
                        l_ps8StartStr = l_ps8StartStr+pCommVar->stMultiCmdType[pCommVar->u8MatchCmdCounter].u8CmdCounter;
                        dbg_printf("cmd:%s\r\n",pCommVar->stMultiCmdType[pCommVar->u8MatchCmdCounter].s8MultiCmd);
                        dbg_printf("len:%d\r\n",pCommVar->stMultiCmdType[pCommVar->u8MatchCmdCounter].u8CmdCounter);
                    }
                    else
                    {
                        l_u8MatchCnt = 0;
                        break;
                    }
                    pCommVar->u8MatchCmdCounter++;
                    if(pCommVar->u8MatchCmdCounter>MaxCmdlist)
                    {
                        pCommVar->u8MatchCmdCounter=MaxCmdlist;
                    }
                    l_u8MatchCnt++;

                    break;
                }
                else
                {
//                    if(pCommVar->u8MatchCmdCounter==0)
//                        pCommVar->bIsMultiCmdDetect = FALSE;
                    if(cmd_list[i].eCmdFun==eFunc_Max || cmd_list[i].flag==Flag_End)
                    {
                        break;
                    }
                    else
                        continue;
                }
                //break;
            }
            else if((cmd_list[i].flag&Flag_NomalMatch)==Flag_NomalMatch)
            {
#if 0
                if(strcmp(pCommVar->pRecBuffer,cmd_list[i].ucmd)==0)
                {
                    mapp_SetCommandFunctionID(cmd_list[i].eCmdFun);
                    l_u8Flag = cmd_list[i].flag;
                    l_u8Cmdnumber = i;
                    break;
                }
#endif
                if((strncmp(pCommVar->pRecBuffer,cmd_list[i].ucmd,strlen(cmd_list[i].ucmd))==0)
                    &&(mapp_CmdlenIsOK(i,pCommVar))
                    )
                {
                    mapp_SetCommandFunctionID(cmd_list[i].eCmdFun);
                    l_u8Flag = cmd_list[i].flag;
                    l_u8Cmdnumber = i;
                    break;
                }
            }
            else if((cmd_list[i].flag&Flag_MiddleMatch)==Flag_MiddleMatch)
            {
                char *l_ps8tempStr = my_StrStr(l_ps8StartStr,cmd_list[i].ucmd);
                if(l_ps8tempStr != NULL)
                {
                    pCommVar->bIsMultiCmdDetect = TRUE;
                    if(pCommVar->u8MatchCmdCounter<MaxCmdlist)
                    {
                        if(*(l_ps8tempStr-1) != ')')        // 指令不是以')'结尾
                        {
                            if(cmd_list[i].valuelen==0)
                                l_ps8EndStr = FindChar(l_ps8tempStr,')',Cmdlength(i)-1);    // delet end char self
                            else
                                l_ps8EndStr = FindChar(l_ps8tempStr,')',Cmdlength(i));
                            pCommVar->stMultiCmdType[pCommVar->u8MatchCmdCounter].u8CmdCounter = (char*)l_ps8EndStr-l_ps8tempStr+strlen(cmd_list[i].ucmd)+1; // 指令结尾加上结束符本身
                        }
                        else
                        {
                            l_ps8EndStr = l_ps8tempStr;
                            pCommVar->stMultiCmdType[pCommVar->u8MatchCmdCounter].u8CmdCounter = (char*)l_ps8EndStr-l_ps8tempStr+strlen(cmd_list[i].ucmd);
                        }
                        memcpy(pCommVar->stMultiCmdType[pCommVar->u8MatchCmdCounter].s8MultiCmd,l_ps8tempStr-strlen(cmd_list[i].ucmd),pCommVar->stMultiCmdType[pCommVar->u8MatchCmdCounter].u8CmdCounter);
                        l_ps8StartStr = l_ps8StartStr+pCommVar->stMultiCmdType[pCommVar->u8MatchCmdCounter].u8CmdCounter;
                        dbg_printf("cmd:%s\r\n",pCommVar->stMultiCmdType[pCommVar->u8MatchCmdCounter].s8MultiCmd);
                        dbg_printf("len:%d\r\n",pCommVar->stMultiCmdType[pCommVar->u8MatchCmdCounter].u8CmdCounter);
                    }
                    else
                    {
                        l_u8MatchCnt = 0;
                        break;
                    }
                    memset(l_ps8tempStr-strlen(cmd_list[i].ucmd),'0',strlen(cmd_list[i].ucmd));   // 覆盖已识别的指令
                    pCommVar->u8MatchCmdCounter++;
                    if(pCommVar->u8MatchCmdCounter>MaxCmdlist)
                    {
                        pCommVar->u8MatchCmdCounter=MaxCmdlist;
                    }
                    l_u8MatchCnt++;

                    break;
                }
                else
                {
                    if(pCommVar->u8MatchCmdCounter==0)
                        pCommVar->bIsMultiCmdDetect = FALSE;
                }
            }
        }

        if(l_u8MatchCnt>0)
        {
            goto RecheckCmd;
        }

        #if 0
        if(!pstBasicSpecVar->bPowerOnSta)
        {
            if(( mapp_GetCommandFunctionID() != eFunc_SwitchPowerState)
                &&( mapp_GetCommandFunctionID() != eFunc_GetPowerState)
                &&( mapp_GetCommandFunctionID() != eFunc_FactoryReset)
                )
            {
                mapp_SetCommandFunctionID(eFunc_NoUse);
                return;
            }
        }
        #endif

        if(pCommVar->u8MatchCmdCounter)
            l_bStatus = emCmdNone;
        else
            l_bStatus = mapp_CommandFunctionProcess(l_u8Cmdnumber,l_u8Flag, pCommVar);
    }

    if( l_bStatus == emCmdError )
    {
        pCommVar->SendPrintf("err\r\n");
    }
    else if( l_bStatus == emCmdOutOfRange )
    {
        pCommVar->SendPrintf("out of range\r\n");
    }
    else if( l_bStatus == emCmdSucess)
    {
        pCommVar->SendPrintf("ok\r\n");
    }
}

#if 1
void mapp_MultiCmdMatchFunction(pstUartCom_t pCommVar)
{
    u8 i/*,j*/;
    char *l_ps8Cmdbuf = NULL;  //g_CMMFCmd;
    //u8 l_u8RankingCmdCnt[MaxCmdlist];
    static u8 sl_u8CmdIndex = 0;
    u8 l_u8Flag = 0;
    u8 l_u8Cmdnumber = 0;
    emCmdFuncStaType l_bStatus=emCmdError;

    if(g_u8MultiCmdDelayCounter)
    {
        g_u8MultiCmdDelayCounter--;
        return;
    }

    l_ps8Cmdbuf = pCommVar->stMultiCmdType[sl_u8CmdIndex].s8MultiCmd;
    //dbg_printf("init: %s\r\n",l_ps8Cmdbuf);
    for(i=0; i<MaxCmdNum ; i++)
    {
        if(pCommVar->stMultiCmdType[sl_u8CmdIndex].u8CmdCounter!=0)
        {
            if(strncmp(l_ps8Cmdbuf,cmd_list[i].ucmd,strlen(cmd_list[i].ucmd))==NULL)    // 识别命令
            {
                mapp_SetCommandFunctionID(cmd_list[i].eCmdFun);
                l_u8Flag = cmd_list[i].flag;
                l_u8Cmdnumber = i;
                pCommVar->bIsMultiCmdDetect = TRUE;
                memcpy(pCommVar->pRecBuffer, l_ps8Cmdbuf,pCommVar->stMultiCmdType[sl_u8CmdIndex].u8CmdCounter);
                pCommVar->u16RecCnt = pCommVar->stMultiCmdType[sl_u8CmdIndex].u8CmdCounter;
                sl_u8CmdIndex++;
                break;
            }
            else
            {
                pCommVar->bIsMultiCmdDetect = FALSE;
            }
        }
    }

    l_bStatus = mapp_CommandFunctionProcess(l_u8Cmdnumber,l_u8Flag, pCommVar);
    if(i >= MaxCmdNum||(sl_u8CmdIndex>=MaxCmdlist)||(sl_u8CmdIndex>=pCommVar->u8MatchCmdCounter))
    {
        pCommVar->bIsMultiCmdDetect = FALSE;
        sl_u8CmdIndex = 0;
        pCommVar->u8MatchCmdCounter= 0;
        memset(pCommVar->stMultiCmdType,0,sizeof(stMultiCmdType_t)*MaxCmdlist);     // clean buffer
        //_Printf("end: %d\r\n",0);
    }
    if( l_bStatus == emCmdError )
    {
        pCommVar->SendPrintf("err\r\n");
    }
    else if( l_bStatus == emCmdOutOfRange )
    {
        pCommVar->SendPrintf("out of range\r\n");
    }
    else if( l_bStatus == emCmdSucess)
    {
        pCommVar->SendPrintf("ok\r\n");
    }
}
#endif

void mapp_SetPowerState(bool bPwrSta)
{
	pstProjectSpecVar_t			pstSpecVar = &stLMX_4IUHS_CSpecVar;
	pstBasicSpecVar_t			pstBasicSpecVar = &pstSpecVar->stBasSpecVar;
    if(bPwrSta)
    {
        if(!pstBasicSpecVar->bPowerOnSta)
        {
            pstBasicSpecVar->bPowerOnSta = TRUE;
            SetUserData_SpecBasicVar();
        }
    }
    else
    {
        if(pstBasicSpecVar->bPowerOnSta)
        {
            pstBasicSpecVar->bPowerOnSta = FALSE;
            SetUserData_SpecBasicVar();
        }
    }
}

void mapp_Usart1SystemCmdFun(pstUartCom_t pCommVar)
{
    u8 l_u8Addr;
    u8 l_u8Cmd;
//    u8 l_u8ID=0;
    if((pCommVar->pRecBuffer[0]==0xFF)&&(pCommVar->pRecBuffer[1]==0xFF)&&(pCommVar->pRecBuffer[2]==0xA5))
    {
        l_u8Addr = pCommVar->pRecBuffer[3];
        l_u8Cmd = pCommVar->pRecBuffer[4];

        dbg_printf("addr[0x%x],cmd[0x%x]\r\n",l_u8Addr,l_u8Cmd);
    }
}

#if _ENABLE_USER_EDID_LEARNING_FUNCTION
void mapp_UartUserEdidReceive(pstUartCom_t pUartCommVar)
{
}
#endif

