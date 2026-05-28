#define __UART_RESPON_USER_FUNC_C__

#include "includes.h"

#include "../USER/project_file/LMX_4IUHS_C/mapp_UartCmdList_4IUHS_C.h"

typedef void (*pFuncUartRes ) ( uint8_t* pu8Data, uint16_t u16Len );

typedef struct _stUartCmdRx_t_
{
	char* 				cmdStr;
	pFuncUartRes		funcResponse;
} stUartCmdRx_t, *pstUartCmdRx_t;

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

//总开关
//static u16 mainSwith = 0;
//stMachVal_t guiParamter[eFunc_Max] = {0};

SemaphoreHandle_t xMutex = NULL;

void UartCommVarClear ( pstUartCom_t pCommVar );

void GetResolutionText ( char* ps8ResText,u8 u8ResID )
{
	switch ( u8ResID )
	{

		default:
			break;
	}

}
const char* json_str = "{\"name\":\"Huan\",\"age\":19,\"city\":\"Mei Zhou\"}";

typedef struct
{
	char name[10];
	uint8_t age;
	char city[10];
} Student_TypeDef;



uint8_t myJsonTest ( const char* jsonString, Student_TypeDef *student )
{
	// 解析JSON字符串
	json_t* root;
	json_error_t error;

	root = json_loads ( jsonString, 0, &error );
	if (!root )
	{
		fprintf ( stderr, "Error parsing JSON: %s\r\n", error.text );
		return 1;
	}

	// 检查JSON对象是否为有效对象
	if (!json_is_object ( root ) )
	{
		fprintf ( stderr, "Error: JSON is not an object\r\n" );
		json_decref ( root );
		return 1;
	}

	// 提取并打印name字段
	json_t* name_value = json_object_get ( root, "name" );
	if ( json_is_string ( name_value ) )
	{
		strcpy ( student->name, json_string_value ( name_value ) );
	}
	else
	{
		dbg_printf ( "Name field is not a string\r\n" );
	}

	// 提取并打印age字段
	json_t* age_value = json_object_get ( root, "age" );
	if ( json_is_integer ( age_value ) )
	{
		student->age = json_integer_value ( age_value );
	}
	else
	{
		dbg_printf ( "Age field is not an integer\r\n" );
	}

	// 提取并打印city字段
	json_t* city_value = json_object_get ( root, "city" );
	if ( json_is_string ( city_value ) )
	{
		strcpy ( student->city, json_string_value ( city_value ) );
	}
	else
	{
		dbg_printf ( "City field is not a string\r\n" );
	}

	// 释放JSON对象
	json_decref ( root );

	return 0;
}
void extract_number ( const char* str, double* number )
{
	char* endptr;
	char f[4];
	// 尝试将字符串转换为浮点数
	*number = strtod ( str, &endptr );

	// 检查转换是否成功
	if ( endptr == str )
	{
		fprintf ( stderr, "Error: No digits were found in the string: %s\n", str );
	}
	else if (*endptr != '\0' )
	{
		fprintf ( stderr, "Error: The string contains non-numeric characters: %s\n", str );
	}
	else
	{
		sprintf ( f,"%f", *number );
		dbg_printf ( "Successfully extracted number: %s\n", f );
	}
}

//add by hy 2024/12/18 START

static void setJSONToReturnResults ( u8 flag )
{
	RS232_printf ( "r,%d\r\n",flag );
}

//SET
static emCmdFuncStaType mapp_CmdfuncSetProductName ( pstUartCom_t pCommVar,u8 cmdnum )
{
	emCmdFuncStaType  l_emRtState = emCmdSucess;
	pstProjectGlobalAllVar_t	pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t	pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pstProjectNameSet_t			pstPrjNameSet = &pstPrjSaveVar->stPrjNameSet;
	char* l_pCmd = pCommVar->pRecBuffer+strlen ( cmd_list[cmdnum].ucmd );
	u8 l_u8Len;

	l_u8Len = my_StrStr ( l_pCmd,")" ) - l_pCmd;

	if ( l_emRtState == emCmdSucess )
	{
		//char l_cDisplayText[16];

		//memset ( l_cDisplayText,' ',16 );
		SetUserData_ProjectName ( l_pCmd,l_u8Len );
		pCommVar->SendPrintf ( "product name:%s\r\n",pstPrjNameSet->sPrjName );

		if ( pstPrjNameSet->sPrjName[0]!=0 )
		{
			//strncpy ( l_cDisplayText, ( char* ) pstPrjNameSet->sPrjName,l_u8Len );
		}
		else
		{
			//strncpy ( l_cDisplayText, LcdNone,16 );
		}
		//LCD_LineRefresh ( l_cDisplayText,LINE2 );
	}
	return l_emRtState;
}

emCmdFuncStaType set_all_audio_output ( pststMachVal_t pstval,u8 iswrite )
{
	u8 Command[6] = {0xAA,0x01,1,1,1,1};

	Command[3] = pstval->param1[0];

	if (!app_All_AudioOutput_Ctrl ( 0, Command ) & !app_All_AudioOutput_Ctrl ( 1, Command ) )
	{
		if ( iswrite )
		{
			WriteUserData_GUIData ( eFunc_SetAllAudioOutput - eFunc_SetProductName - 1 );
		}

		return emCmdSucess;
	}

	return emCmdError;
}

static emCmdFuncStaType mapp_CmdfuncSetAllAudioOutput ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	//emCmdFuncStaType l_state = emCmdNone;
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetAllAudioOutput - eFunc_SetProductName - 1];

	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	u8 Command[6] = {0xAA,0x01,1,1,1,1};

	Command[3] = atoi ( l_pCmd );

#if 1

	//1000 0000 0000 0000 - 音频总开关 - 小端序   8000 ->   00 80
	//mainSwith |= 1<<15;

	//dbg_printf("############mainSwith###########\r\n");
	//v_hexdump((char *)&mainSwith, sizeof(mainSwith));
	//memset ( pstval,0,sizeof ( stMachVal_t ) );
	pstval->ch = 0xFF;
	pstval->param1[0] = atoi ( l_pCmd );
	pstval->param2[0] = 0;
	pstval->param3[0] = 0;
	//pstval->param4[0] = 0;

	//strncpy ( pstval->command,Command + 1,5 );
	memcpy ( pstval->command,Command + 1,5 );
	v_hexdump ( pstval->command,5 );

	if (!app_All_AudioOutput_Ctrl ( 0, Command ) && !app_All_AudioOutput_Ctrl ( 1, Command ) )
	{
		setJSONToReturnResults ( 1 );
		WriteUserData_GUIData ( eFunc_SetAllAudioOutput - eFunc_SetProductName - 1 );
		//void SaveUserDataToEep ( eEepDataIndex_t eIndex, uint32_t u32EepAdr, uint8_t* pu8Buffer, uint32_t u32Len, uint16_t u16SaveTime, bool bFromIsr );
	}
	else
	{
		setJSONToReturnResults ( 0 );
	}
#endif

	//dbg_printf ( "l_pCmd: %s\r\n", l_pCmd );
	//dbg_printf ( "%s \t cmd:%s\r\n",__FUNCTION__,"(set,AllAudioOutput,switch)" );

	return emCmdSucess;
}

emCmdFuncStaType set_in_sensitivity ( pststMachVal_t pstval,u8 iswrite )
{
	emCmdFuncStaType l_state = emCmdNone;
	u8 Command[6] = {0xAA,0x02,0,0,0,0};

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			Command[2] = cg_u8_IN_ChannelTable[i][0];
			Command[3] = ( u8 ) pstval->param1[Command[2]];

			if (!app_Input_Sensitivity ( cg_u8_IN_ChannelTable[i][1], Command ) )
			{
				if ( iswrite )
				{
					WriteUserData_GUIData ( eFunc_SetInputSensitivity - eFunc_SetProductName - 1 );
				}

				l_state = emCmdSucess;
			}
		}
	}

	return l_state;
}

static emCmdFuncStaType mapp_CmdfuncSetInputSensitivity ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputSensitivity - eFunc_SetProductName - 1];

	u8 Command[6] = {0xAA,0x02,0,0,0,0};
	u8 dev = 0;
	char* token = strtok ( l_pCmd,"," );

	if ( token != NULL )
	{
		dev = cg_u8_IN_ChannelTable[atoi ( token )][1];
		Command[2] = cg_u8_IN_ChannelTable[atoi ( token )][0];

		pstval->ch |= 1 << Command[2];
		pstval->ch |= 1 << ( atoi ( token ) + 0x10 );

		//dbg_printf("Command[2]:%d,token:%s,atoi(token):%d \r\n",Command[2],token,atoi ( token ));
		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		Command[3] = atoi ( token );

		pstval->param1[Command[2]] = atoi ( token );

		token = strtok ( NULL,"," );
	}

	//v_hexdump ( Command + 1, 5 );
	memcpy ( pstval->command,Command + 1,5 );
	if (!app_Input_Sensitivity ( dev, Command ) )
	{
		setJSONToReturnResults ( 1 );
		WriteUserData_GUIData ( eFunc_SetInputSensitivity - eFunc_SetProductName - 1 );
	}
	else
	{
		setJSONToReturnResults ( 0 );
	}

#if 0
	while ( token != NULL )
	{
		dbg_printf ( "token str:%s\r\n",token );
		token = strtok ( NULL,"," );
	}

	dbg_printf ( "token:%c\r\n",token );
#endif

	//u8 dev = cg_u8_IN_ChannelTable[channel][1];
	//Command[3] = cg_u8_IN_ChannelTable[channel][0];
	//Command[4] = parameter1;

	//dbg_printf ( "%s \t cmd:%s,Command:%d,%d\r\n",__FUNCTION__,l_pCmd, Command[3],Command[4] );

	return emCmdSucess;
}

emCmdFuncStaType set_in_gain ( pststMachVal_t pstval,u8 iswrite )
{
	emCmdFuncStaType l_state = emCmdNone;
	u8 Command[6] = {0xAA,0x03,0,0,0,0};

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			Command[2] = cg_u8_IN_ChannelTable[i][0];
			Command[3] = pstval->param1[Command[2]];
			Command[4] = pstval->param2[Command[2]];

			if (!app_Input_Gain ( cg_u8_IN_ChannelTable[i][1], Command ) )
			{
				if ( iswrite )
				{
					WriteUserData_GUIData ( eFunc_SetInputGain - eFunc_SetProductName - 1 );
				}

				l_state = emCmdSucess;
			}
		}
	}

	return l_state;
}

static emCmdFuncStaType mapp_CmdfuncSetInputGain ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputGain - eFunc_SetProductName - 1];
	u8 Command[6] = {0xAA,0x03,0,0,0,0};
	u8 dev = 0;
	char* token = strtok ( l_pCmd,"," );

	if ( token != NULL )
	{
		dev = cg_u8_IN_ChannelTable[atoi ( token )][1];
		Command[2] = cg_u8_IN_ChannelTable[atoi ( token )][0];

		pstval->ch |= 1 << Command[2];
		pstval->ch |= 1 << ( atoi ( token ) + 0x10 );

		//dbg_printf ( "Command[2]:%d,token:%s,atoi(token):%d \r\n",Command[2],token,atoi ( token ) );
		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		Command[3] = atoi ( token );
		pstval->param1[Command[2]] = atoi ( token );

		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		Command[4] = atoi ( token );
		pstval->param2[Command[2]] = atoi ( token );

		token = strtok ( NULL,"," );
	}

	memcpy ( pstval->command,Command + 1,5 );
	if (!app_Input_Gain ( dev, Command ) )
	{
		setJSONToReturnResults ( 1 );
		WriteUserData_GUIData ( eFunc_SetInputGain - eFunc_SetProductName - 1 );
	}
	else
	{
		setJSONToReturnResults ( 0 );
	}

	//u8 dev = cg_u8_IN_ChannelTable[channel][1];
	//Command[3] = cg_u8_IN_ChannelTable[channel][0];
	//Command[4] = parameter1;
	//Command[5] = parameter2;

	//dbg_printf ( "%s \t cmd:%s\r\n",__FUNCTION__,l_pCmd );
	return emCmdSucess;
}

emCmdFuncStaType set_in_mute ( pststMachVal_t pstval,u8 iswrite )
{
	emCmdFuncStaType l_state = emCmdNone;
	u8 Command[6] = {0xAA,0x04,0,0,0,0};

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			Command[2] = cg_u8_IN_ChannelTable[i][0];
			Command[3] = pstval->param1[Command[2]];

			if (!app_Input_Mute ( cg_u8_IN_ChannelTable[i][1], Command ) )
			{
				if ( iswrite )
				{
					WriteUserData_GUIData ( eFunc_SetInputMute - eFunc_SetProductName - 1 );
				}

				l_state = emCmdSucess;
			}
		}
	}

	return l_state;
}

static emCmdFuncStaType mapp_CmdfuncSetInputMute ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputMute - eFunc_SetProductName - 1];
	u8 Command[6] = {0xAA,0x04,0,0,0,0};
	u8 dev = 0;
	char* token = strtok ( l_pCmd,"," );

	if ( token != NULL )
	{
		dev = cg_u8_IN_ChannelTable[atoi ( token )][1];
		Command[2] = cg_u8_IN_ChannelTable[atoi ( token )][0];

		pstval->ch |= 1 << Command[2];
		pstval->ch |= 1 << ( atoi ( token ) + 0x10 );

		//dbg_printf("Command[2]:%d,token:%s,atoi(token):%d \r\n",Command[2],token,atoi ( token ));
		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		Command[3] = atoi ( token );
		pstval->param1[Command[2]] = atoi ( token );

		token = strtok ( NULL,"," );
	}

	memcpy ( pstval->command,Command + 1,5 );
	if (!app_Input_Mute ( dev, Command ) )
	{
		setJSONToReturnResults ( 1 );
		WriteUserData_GUIData ( eFunc_SetInputMute - eFunc_SetProductName - 1 );
	}
	else
	{
		setJSONToReturnResults ( 0 );
	}

	//u8 dev = cg_u8_IN_ChannelTable[channel][1];
	//Command[3] = cg_u8_IN_ChannelTable[channel][0];
	//Command[4] = OnOff;

	//dbg_printf ( "%s \t cmd:%s,dev:%d\r\n",__FUNCTION__,l_pCmd,dev );
	return emCmdSucess;
}

emCmdFuncStaType set_in_reversephase ( pststMachVal_t pstval,u8 iswrite )
{
	emCmdFuncStaType l_state = emCmdNone;
	u8 Command[6] = {0xAA,0x05,0,0,0,0};

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			Command[2] = cg_u8_IN_ChannelTable[i][0];
			Command[3] = pstval->param1[Command[2]];

			if (!app_Input_Reverse_phase ( cg_u8_IN_ChannelTable[i][1], Command ) )
			{
				if ( iswrite )
				{
					WriteUserData_GUIData ( eFunc_SetInputReversephase - eFunc_SetProductName - 1 );
				}

				l_state = emCmdSucess;
			}
		}
	}

	return l_state;
}

static emCmdFuncStaType mapp_CmdfuncSetInputReversephase ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputReversephase - eFunc_SetProductName - 1];
	u8 Command[6] = {0xAA,0x05,0,0,0,0};
	u8 dev = 0;
	char* token = strtok ( l_pCmd,"," );

	if ( token != NULL )
	{
		dev = cg_u8_IN_ChannelTable[atoi ( token )][1];
		Command[2] = cg_u8_IN_ChannelTable[atoi ( token )][0];

		pstval->ch |= 1 << Command[2];
		pstval->ch |= 1 << ( atoi ( token ) + 0x10 );

		//dbg_printf("Command[2]:%d,token:%s,atoi(token):%d \r\n",Command[2],token,atoi ( token ));
		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		Command[3] = atoi ( token );
		pstval->param1[Command[2]] = atoi ( token );

		token = strtok ( NULL,"," );
	}

	memcpy ( pstval->command,Command + 1,5 );
	if (!app_Input_Reverse_phase ( dev, Command ) )
	{
		setJSONToReturnResults ( 1 );
		WriteUserData_GUIData ( eFunc_SetInputReversephase - eFunc_SetProductName - 1 );
	}
	else
	{
		setJSONToReturnResults ( 0 );
	}
	//u8 dev = cg_u8_IN_ChannelTable[channel][1];
	//Command[3] = cg_u8_IN_ChannelTable[channel][0];
	//Command[4] = OnOff;

	//dbg_printf ( "%s \t cmd:%s\r\n",__FUNCTION__,l_pCmd );
	return emCmdSucess;
}

emCmdFuncStaType set_in_test_signal_ctrl ( pststMachVal_t pstval,u8 iswrite )
{
	emCmdFuncStaType l_state = emCmdNone;
	u8 Command[6] = {0xAA,0x06,0,0,0,0};

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			Command[2] = cg_u8_IN_ChannelTable[i][0];
			Command[3] = pstval->param1[Command[2]];

			if (!app_Input_TestSignal_Ctrl ( cg_u8_IN_ChannelTable[i][1], Command ) )
			{
				if ( iswrite )
				{
					WriteUserData_GUIData ( eFunc_SetInputTestSignalCtrl - eFunc_SetProductName - 1 );
				}

				l_state = emCmdSucess;
			}
		}
	}

	return l_state;
}

static emCmdFuncStaType mapp_CmdfuncSetInputTestSignalCtrl ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputTestSignalCtrl - eFunc_SetProductName - 1];
	u8 Command[6] = {0xAA,0x06,0,0,0,0};
	u8 dev = 0;
	char* token = strtok ( l_pCmd,"," );

	if ( token != NULL )
	{
		dev = cg_u8_IN_ChannelTable[atoi ( token )][1];
		Command[2] = cg_u8_IN_ChannelTable[atoi ( token )][0];

		pstval->ch |= 1 << Command[2];
		pstval->ch |= 1 << ( atoi ( token ) + 0x10 );

		//dbg_printf("Command[2]:%d,token:%s,atoi(token):%d \r\n",Command[2],token,atoi ( token ));

		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		Command[3] = atoi ( token );
		pstval->param1[Command[2]] = atoi ( token );

		token = strtok ( NULL,"," );
	}

	memcpy ( pstval->command,Command + 1,5 );
	if (!app_Input_TestSignal_Ctrl ( dev, Command ) )
	{
		setJSONToReturnResults ( 1 );
		WriteUserData_GUIData ( eFunc_SetInputTestSignalCtrl - eFunc_SetProductName - 1 );
	}
	else
	{
		setJSONToReturnResults ( 0 );
	}
	//u8 dev = cg_u8_IN_ChannelTable[channel][1];
	//Command[3] = cg_u8_IN_ChannelTable[channel][0];
	//Command[4] = OnOff;

	//dbg_printf ( "%s \t cmd:%s\r\n",__FUNCTION__,l_pCmd );

	return emCmdSucess;
}

emCmdFuncStaType set_in_test_signal_freq ( pststMachVal_t pstval,u8 iswrite )
{
	emCmdFuncStaType l_state = emCmdNone;
	u8 Command[6] = {0xAA,0x07,0,0,0,0};

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			char* p = ( char* ) & ( pstval->param1[cg_u8_IN_ChannelTable[i][0]] );
			u8* pcmd = Command;

			Command[2] = cg_u8_IN_ChannelTable[i][0];

			if ( pstval->param1[cg_u8_IN_ChannelTable[i][0]] <= 0xFFFF )
			{
				memcpy ( pcmd + 3,p + 1,sizeof ( char ) );
				memcpy ( pcmd + 4,p,sizeof ( char ) );
			}

			if (!app_Input_TestSignal_Freq ( cg_u8_IN_ChannelTable[i][1], Command ) )
			{
				if ( iswrite )
				{
					WriteUserData_GUIData ( eFunc_SetInputTestSignalFreq - eFunc_SetProductName - 1 );
				}

				l_state = emCmdSucess;
			}
		}
	}

	return l_state;
}

static emCmdFuncStaType mapp_CmdfuncSetInputTestSignalFreq ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputTestSignalFreq - eFunc_SetProductName - 1];
	u8 Command[6] = {0xAA,0x07,0,0,0,0};
	u8 dev = 0;
	char* token = strtok ( l_pCmd,"," );

#if 1
	if ( token != NULL )
	{
		dev = cg_u8_IN_ChannelTable[atoi ( token )][1];
		Command[2] = cg_u8_IN_ChannelTable[atoi ( token )][0];

		pstval->ch |= 1 << Command[2];
		pstval->ch |= 1 << ( atoi ( token ) + 0x10 );

		token = strtok ( NULL,"," );
	}
#endif

	if ( token != NULL )
	{
		int32_t val = atoi ( token );
		char* p = ( char* ) &val;
		u8* pcmd = Command;

		if ( val <= 0xFFFF )
		{
			memcpy ( pcmd + 3,p + 1,sizeof ( char ) );
			memcpy ( pcmd + 4,p,sizeof ( char ) );

			pstval->param1[Command[2]] = val;
		}

		token = strtok ( NULL,"," );
	}

	memcpy ( pstval->command,Command + 1,5 );
	if (!app_Input_TestSignal_Freq ( dev, Command ) )
	{
		setJSONToReturnResults ( 1 );
		WriteUserData_GUIData ( eFunc_SetInputTestSignalFreq - eFunc_SetProductName - 1 );
	}
	else
	{
		setJSONToReturnResults ( 0 );
	}

	return emCmdSucess;
}

emCmdFuncStaType set_in_test_signal_level ( pststMachVal_t pstval,u8 iswrite )
{
	emCmdFuncStaType l_state = emCmdNone;
	u8 Command[6] = {0xAA,0x08,0,0,0,0};

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			Command[2] = cg_u8_IN_ChannelTable[i][0];
			Command[3] = pstval->param1[Command[2]];
			Command[4] = pstval->param2[Command[2]];

			if (!app_Input_TestSignal_Level ( cg_u8_IN_ChannelTable[i][1], Command ) )
			{
				if ( iswrite )
				{
					WriteUserData_GUIData ( eFunc_SetInputTestSignalLevel - eFunc_SetProductName - 1 );
				}

				l_state = emCmdSucess;
			}
		}
	}

	return l_state;
}

static emCmdFuncStaType mapp_CmdfuncSetInputTestSignalLevel ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputTestSignalLevel - eFunc_SetProductName - 1];
	u8 Command[6] = {0xAA,0x08,0,0,0,0};
	u8 dev = 0;
	char* token = strtok ( l_pCmd,"," );

#if 1
	if ( token != NULL )
	{
		dev = cg_u8_IN_ChannelTable[atoi ( token )][1];
		Command[2] = cg_u8_IN_ChannelTable[atoi ( token )][0];

		pstval->ch |= 1 << Command[2];
		pstval->ch |= 1 << ( atoi ( token ) + 0x10 );

		//dbg_printf("Command[2]:%d,token:%s,atoi(token):%d \r\n",Command[2],token,atoi ( token ));

		token = strtok ( NULL,"," );
	}
#endif

	if ( token != NULL )
	{
		Command[3] = atoi ( token );
		pstval->param1[Command[2]] = atoi ( token );

		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		Command[4] = atoi ( token );
		pstval->param2[Command[2]] = atoi ( token );

		token = strtok ( NULL,"," );
	}

	memcpy ( pstval->command,Command + 1,5 );
	if (!app_Input_TestSignal_Level ( dev, Command ) )
	{
		setJSONToReturnResults ( 1 );
		WriteUserData_GUIData ( eFunc_SetInputTestSignalLevel - eFunc_SetProductName - 1 );
	}
	else
	{
		setJSONToReturnResults ( 0 );
	}

	//u8 dev = cg_u8_IN_ChannelTable[channel][1];
	//Command[3] = cg_u8_IN_ChannelTable[channel][0];
	//Command[4] = parameter1;
	//Command[5] = parameter2;

	//dbg_printf ( "%s \t cmd:%s\r\n",__FUNCTION__,l_pCmd );

	return emCmdSucess;
}

emCmdFuncStaType set_in_compressor_ctrl ( pststMachVal_t pstval,u8 iswrite )
{
	emCmdFuncStaType l_state = emCmdNone;
	u8 Command[6] = {0xAA,0x09,0,0,0,0};

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			Command[2] = cg_u8_IN_ChannelTable[i][0];
			Command[3] = pstval->param1[Command[2]];

			if (!app_Input_Compressor_Ctrl ( cg_u8_IN_ChannelTable[i][1], Command ) )
			{
				if ( iswrite )
				{
					WriteUserData_GUIData ( eFunc_SetInputCompressorCtrl - eFunc_SetProductName - 1 );
				}

				l_state = emCmdSucess;
			}
		}
	}

	return l_state;
}

static emCmdFuncStaType mapp_CmdfuncSetInputCompressorCtrl ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputCompressorCtrl - eFunc_SetProductName - 1];
	u8 Command[6] = {0xAA,0x09,0,0,0,0};
	u8 dev = 0;
	char* token = strtok ( l_pCmd,"," );

	if ( token != NULL )
	{
		dev = cg_u8_IN_ChannelTable[atoi ( token )][1];
		Command[2] = cg_u8_IN_ChannelTable[atoi ( token )][0];

		pstval->ch |= 1 << Command[2];
		pstval->ch |= 1 << ( atoi ( token ) + 0x10 );

		//dbg_printf("Command[2]:%d,token:%s,atoi(token):%d \r\n",Command[2],token,atoi ( token ));
		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		Command[3] = atoi ( token );
		pstval->param1[Command[2]] = atoi ( token );

		token = strtok ( NULL,"," );
	}

	memcpy ( pstval->command,Command + 1,5 );
	if (!app_Input_Compressor_Ctrl ( dev, Command ) )
	{
		setJSONToReturnResults ( 1 );
		WriteUserData_GUIData ( eFunc_SetInputCompressorCtrl - eFunc_SetProductName - 1 );
	}
	else
	{
		setJSONToReturnResults ( 0 );
	}

	//u8 dev = cg_u8_IN_ChannelTable[channel][1];
	//Command[3] = cg_u8_IN_ChannelTable[channel][0];
	//Command[4] = OnOff;

	//dbg_printf ( "%s \t cmd:%s\r\n",__FUNCTION__,l_pCmd );

	return emCmdSucess;
}

emCmdFuncStaType set_in_compressor_gain ( pststMachVal_t pstval,u8 iswrite )
{
	emCmdFuncStaType l_state = emCmdNone;
	u8 Command[6] = {0xAA,0x0a,0,0,0,0};

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			Command[2] = cg_u8_IN_ChannelTable[i][0];
			Command[3] = pstval->param1[Command[2]];
			Command[4] = pstval->param2[Command[2]];

			if (!app_Input_Compressor_Gain ( cg_u8_IN_ChannelTable[i][1], Command ) )
			{
				if ( iswrite )
				{
					WriteUserData_GUIData ( eFunc_SetInputCompressorGain - eFunc_SetProductName - 1 );
				}

				l_state = emCmdSucess;
			}
		}
	}

	return l_state;
}

static emCmdFuncStaType mapp_CmdfuncSetInputCompressorGain ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputCompressorGain - eFunc_SetProductName - 1];
	u8 Command[6] = {0xAA,0x0a,0,0,0,0};
	u8 dev = 0;
	char* token = strtok ( l_pCmd,"," );

	if ( token != NULL )
	{
		dev = cg_u8_IN_ChannelTable[atoi ( token )][1];
		Command[2] = cg_u8_IN_ChannelTable[atoi ( token )][0];

		pstval->ch |= 1 << Command[2];
		pstval->ch |= 1 << ( atoi ( token ) + 0x10 );

		//dbg_printf("Command[2]:%d,token:%s,atoi(token):%d \r\n",Command[2],token,atoi ( token ));
		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		Command[3] = atoi ( token );
		pstval->param1[Command[2]] = atoi ( token );

		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		Command[4] = atoi ( token );
		pstval->param2[Command[2]] = atoi ( token );

		token = strtok ( NULL,"," );
	}

	memcpy ( pstval->command,Command + 1,5 );
	if (!app_Input_Compressor_Gain ( dev, Command ) )
	{
		setJSONToReturnResults ( 1 );
		WriteUserData_GUIData ( eFunc_SetInputCompressorGain - eFunc_SetProductName - 1 );
	}
	else
	{
		setJSONToReturnResults ( 0 );
	}

	//u8 dev = cg_u8_IN_ChannelTable[channel][1];
	//Command[3] = cg_u8_IN_ChannelTable[channel][0];
	//Command[4] = parameter1;
	//Command[5] = parameter2;

	//dbg_printf ( "%s \t cmd:%s\r\n",__FUNCTION__,l_pCmd );

	return emCmdSucess;
}

emCmdFuncStaType set_in_compressor_threshold ( pststMachVal_t pstval,u8 iswrite )
{
	emCmdFuncStaType l_state = emCmdNone;
	u8 Command[6] = {0xAA,0x0b,0,0,0,0};

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			Command[2] = cg_u8_IN_ChannelTable[i][0];
			Command[3] = pstval->param1[Command[2]];
			Command[4] = pstval->param2[Command[2]];

			if (!app_Input_Compressor_Threshold ( cg_u8_IN_ChannelTable[i][1], Command ) )
			{
				if ( iswrite )
				{
					WriteUserData_GUIData ( eFunc_SetInputCompressorThreshold - eFunc_SetProductName - 1 );
				}

				l_state = emCmdSucess;
			}
		}
	}

	return l_state;
}

static emCmdFuncStaType mapp_CmdfuncSetInputCompressorThreshold ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputCompressorThreshold - eFunc_SetProductName - 1];
	u8 Command[6] = {0xAA,0x0b,0,0,0,0};
	u8 dev = 0;
	char* token = strtok ( l_pCmd,"," );

	if ( token != NULL )
	{
		dev = cg_u8_IN_ChannelTable[atoi ( token )][1];
		Command[2] = cg_u8_IN_ChannelTable[atoi ( token )][0];

		pstval->ch |= 1 << Command[2];
		pstval->ch |= 1 << ( atoi ( token ) + 0x10 );

		//dbg_printf("Command[2]:%d,token:%s,atoi(token):%d \r\n",Command[2],token,atoi ( token ));
		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		Command[3] = atoi ( token );
		pstval->param1[Command[2]] = atoi ( token );

		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		Command[4] = atoi ( token );
		pstval->param2[Command[2]] = atoi ( token );

		token = strtok ( NULL,"," );
	}

	memcpy ( pstval->command,Command + 1,5 );
	if (!app_Input_Compressor_Threshold ( dev, Command ) )
	{
		setJSONToReturnResults ( 1 );
		WriteUserData_GUIData ( eFunc_SetInputCompressorThreshold - eFunc_SetProductName - 1 );
	}
	else
	{
		setJSONToReturnResults ( 0 );
	}
	//u8 dev = cg_u8_IN_ChannelTable[channel][1];
	//Command[3] = cg_u8_IN_ChannelTable[channel][0];
	//Command[4] = parameter1;
	//Command[5] = parameter2;

	//dbg_printf ( "%s \t cmd:%s\r\n",__FUNCTION__,l_pCmd );

	return emCmdSucess;
}

emCmdFuncStaType set_in_compressor_ratio ( pststMachVal_t pstval,u8 iswrite )
{
	emCmdFuncStaType l_state = emCmdNone;
	u8 Command[6] = {0xAA,0x0c,0,0,0,0};

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			Command[2] = cg_u8_IN_ChannelTable[i][0];
			Command[3] = pstval->param1[Command[2]];
			Command[4] = pstval->param2[Command[2]];

			if (!app_Input_Compressor_Ratio ( cg_u8_IN_ChannelTable[i][1], Command ) )
			{
				if ( iswrite )
				{
					WriteUserData_GUIData ( eFunc_SetInputCompressorRatio - eFunc_SetProductName - 1 );
				}

				l_state = emCmdSucess;
			}
		}
	}

	return l_state;
}

static emCmdFuncStaType mapp_CmdfuncSetInputCompressorRatio ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputCompressorRatio - eFunc_SetProductName - 1];
	u8 Command[6] = {0xAA,0x0c,0,0,0,0};
	u8 dev = 0;
	char* token = strtok ( l_pCmd,"," );

	if ( token != NULL )
	{
		dev = cg_u8_IN_ChannelTable[atoi ( token )][1];
		Command[2] = cg_u8_IN_ChannelTable[atoi ( token )][0];

		pstval->ch |= 1 << Command[2];
		pstval->ch |= 1 << ( atoi ( token ) + 0x10 );

		//dbg_printf("Command[2]:%d,token:%s,atoi(token):%d \r\n",Command[2],token,atoi ( token ));
		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		Command[3] = atoi ( token );
		pstval->param1[Command[2]] = atoi ( token );

		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		Command[4] = atoi ( token );
		pstval->param2[Command[2]] = atoi ( token );

		token = strtok ( NULL,"," );
	}

	memcpy ( pstval->command,Command + 1,5 );
	if (!app_Input_Compressor_Ratio ( dev, Command ) )
	{
		setJSONToReturnResults ( 1 );
		WriteUserData_GUIData ( eFunc_SetInputCompressorRatio - eFunc_SetProductName - 1 );
	}
	else
	{
		setJSONToReturnResults ( 0 );
	}
	//u8 dev = cg_u8_IN_ChannelTable[channel][1];
	//Command[3] = cg_u8_IN_ChannelTable[channel][0];
	//Command[4] = parameter1;
	//Command[5] = parameter2;

	//dbg_printf ( "%s \t cmd:%s\r\n",__FUNCTION__,l_pCmd );

	return emCmdSucess;
}

emCmdFuncStaType set_in_compressor_start_time ( pststMachVal_t pstval,u8 iswrite )
{
	emCmdFuncStaType l_state = emCmdNone;
	u8 Command[6] = {0xAA,0x0d,0,0,0,0};

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			char* p = ( char* ) & ( pstval->param1[cg_u8_IN_ChannelTable[i][0]] );
			u8* pcmd = Command;

			Command[2] = cg_u8_IN_ChannelTable[i][0];

			if ( pstval->param1[Command[2]] <= 0xFFFF )
			{
				memcpy ( pcmd + 3,p + 1,sizeof ( char ) );
				memcpy ( pcmd + 4,p,sizeof ( char ) );
			}

			Command[5] = pstval->param2[Command[2]];

			if (!app_Input_Compressor_StartTime ( cg_u8_IN_ChannelTable[i][1], Command ) )
			{
				if ( iswrite )
				{
					WriteUserData_GUIData ( eFunc_SetInputCompressorStartTime - eFunc_SetProductName - 1 );
				}

				l_state = emCmdSucess;
			}
		}
	}

	return l_state;
}

static emCmdFuncStaType mapp_CmdfuncSetInputCompressorStartTime ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputCompressorStartTime - eFunc_SetProductName - 1];
	u8 Command[6] = {0xAA,0x0d,0,0,0,0};
	u8 dev = 0;
	char* token = strtok ( l_pCmd,"," );

	if ( token != NULL )
	{
		dev = cg_u8_IN_ChannelTable[atoi ( token )][1];
		Command[2] = cg_u8_IN_ChannelTable[atoi ( token )][0];

		pstval->ch |= 1 << Command[2];
		pstval->ch |= 1 << ( atoi ( token ) + 0x10 );

		//dbg_printf("Command[2]:%d,token:%s,atoi(token):%d \r\n",Command[2],token,atoi ( token ));
		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		int32_t val = atoi ( token );
		char* p = ( char* ) &val;
		u8* pcmd = Command;

		if ( val <= 0xFFFF )
		{
			memcpy ( pcmd + 3,p + 1,sizeof ( char ) );
			memcpy ( pcmd + 4,p,sizeof ( char ) );

			pstval->param1[Command[2]] = val;
		}

		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		Command[5] = atoi ( token );
		pstval->param2[Command[2]] = atoi ( token );

		token = strtok ( NULL,"," );
	}

	memcpy ( pstval->command,Command + 1,5 );
	if (!app_Input_Compressor_StartTime ( dev, Command ) )
	{
		setJSONToReturnResults ( 1 );
		WriteUserData_GUIData ( eFunc_SetInputCompressorStartTime - eFunc_SetProductName - 1 );
	}
	else
	{
		setJSONToReturnResults ( 0 );
	}
	//u8 dev = cg_u8_IN_ChannelTable[channel][1];
	//Command[3] = cg_u8_IN_ChannelTable[channel][0];
	//Command[4] = parameter1;
	//Command[5] = parameter2;

	//dbg_printf ( "%s \t cmd:%s\r\n",__FUNCTION__,l_pCmd );

	return emCmdSucess;
}

emCmdFuncStaType set_in_compressor_rel_time ( pststMachVal_t pstval,u8 iswrite )
{
	emCmdFuncStaType l_state = emCmdNone;
	u8 Command[6] = {0xAA,0x0e,0,0,0,0};

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			char* p = ( char* ) & ( pstval->param1[cg_u8_IN_ChannelTable[i][0]] );
			u8* pcmd = Command;

			Command[2] = cg_u8_IN_ChannelTable[i][0];

			if ( pstval->param1[Command[2]] <= 0xFFFF )
			{
				memcpy ( pcmd + 3,p + 1,sizeof ( char ) );
				memcpy ( pcmd + 4,p,sizeof ( char ) );
			}

			Command[5] = pstval->param2[Command[2]];

			if (!app_Input_Compressor_ReleaseTime ( cg_u8_IN_ChannelTable[i][1], Command ) )
			{
				if ( iswrite )
				{
					WriteUserData_GUIData ( eFunc_SetInputCompressorReleaseTime - eFunc_SetProductName - 1 );
				}

				l_state = emCmdSucess;
			}
		}
	}

	return l_state;
}

static emCmdFuncStaType mapp_CmdfuncSetInputCompressorReleaseTime ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputCompressorReleaseTime - eFunc_SetProductName - 1];
	u8 Command[6] = {0xAA,0x0e,0,0,0,0};
	u8 dev = 0;
	char* token = strtok ( l_pCmd,"," );

	if ( token != NULL )
	{
		dev = cg_u8_IN_ChannelTable[atoi ( token )][1];
		Command[2] = cg_u8_IN_ChannelTable[atoi ( token )][0];

		pstval->ch |= 1 << Command[2];
		pstval->ch |= 1 << ( atoi ( token ) + 0x10 );

		//dbg_printf("Command[2]:%d,token:%s,atoi(token):%d \r\n",Command[2],token,atoi ( token ));
		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		int32_t val = atoi ( token );
		char* p = ( char* ) &val;
		u8* pcmd = Command;

		if ( val <= 0xFFFF )
		{
			memcpy ( pcmd + 3,p + 1,sizeof ( char ) );
			memcpy ( pcmd + 4,p,sizeof ( char ) );

			pstval->param1[Command[2]] = val;
		}

		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		Command[5] = atoi ( token );
		pstval->param2[Command[2]] = atoi ( token );

		token = strtok ( NULL,"," );
	}

	memcpy ( pstval->command,Command + 1,5 );
	if (!app_Input_Compressor_ReleaseTime ( dev, Command ) )
	{
		setJSONToReturnResults ( 1 );
		WriteUserData_GUIData ( eFunc_SetInputCompressorReleaseTime - eFunc_SetProductName - 1 );
	}
	else
	{
		setJSONToReturnResults ( 0 );
	}
	//u8 dev = cg_u8_IN_ChannelTable[channel][1];
	//Command[3] = cg_u8_IN_ChannelTable[channel][0];
	//Command[4] = parameter1;
	//Command[5] = parameter2;

	//dbg_printf ( "%s \t cmd:%s\r\n",__FUNCTION__,l_pCmd );

	return emCmdSucess;
}

emCmdFuncStaType set_in_auto_gain_ctrl ( pststMachVal_t pstval,u8 iswrite )
{
	emCmdFuncStaType l_state = emCmdNone;
	u8 Command[6] = {0xAA,0x0f,0,0,0,0};

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			Command[2] = cg_u8_IN_ChannelTable[i][0];
			Command[3] = pstval->param1[Command[2]];

			if (!app_Input_AutoGain_Ctrl ( cg_u8_IN_ChannelTable[i][1], Command ) )
			{
				if ( iswrite )
				{
					WriteUserData_GUIData ( eFunc_SetInputAutoGainCtrl - eFunc_SetProductName - 1 );
				}

				l_state = emCmdSucess;
			}
		}
	}

	return l_state;
}

static emCmdFuncStaType mapp_CmdfuncSetInputAutoGainCtrl ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputAutoGainCtrl - eFunc_SetProductName - 1];
	u8 Command[6] = {0xAA,0x0f,0,0,0,0};
	u8 dev = 0;
	char* token = strtok ( l_pCmd,"," );

	if ( token != NULL )
	{
		dev = cg_u8_IN_ChannelTable[atoi ( token )][1];
		Command[2] = cg_u8_IN_ChannelTable[atoi ( token )][0];

		pstval->ch |= 1 << Command[2];
		pstval->ch |= 1 << ( atoi ( token ) + 0x10 );

		//dbg_printf("Command[2]:%d,token:%s,atoi(token):%d \r\n",Command[2],token,atoi ( token ));
		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		Command[3] = atoi ( token );
		pstval->param1[Command[2]] = atoi ( token );

		token = strtok ( NULL,"," );
	}

	memcpy ( pstval->command,Command + 1,5 );
	if (!app_Input_AutoGain_Ctrl ( dev, Command ) )
	{
		setJSONToReturnResults ( 1 );
		WriteUserData_GUIData ( eFunc_SetInputAutoGainCtrl - eFunc_SetProductName - 1 );
	}
	else
	{
		setJSONToReturnResults ( 0 );
	}
	//u8 dev = cg_u8_IN_ChannelTable[channel][1];
	//Command[3] = cg_u8_IN_ChannelTable[channel][0];
	//Command[4] = OnOff;

	//dbg_printf ( "%s \t cmd:%s\r\n",__FUNCTION__,l_pCmd );

	return emCmdSucess;
}

emCmdFuncStaType set_in_auto_gain_threshold ( pststMachVal_t pstval,u8 iswrite )
{
	emCmdFuncStaType l_state = emCmdNone;
	u8 Command[6] = {0xAA,0x10,0,0,0,0};

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			Command[2] = cg_u8_IN_ChannelTable[i][0];
			Command[3] = pstval->param1[Command[2]];
			Command[4] = pstval->param2[Command[2]];

			if (!app_Input_AutoGain_Threshold ( cg_u8_IN_ChannelTable[i][1], Command ) )
			{
				if ( iswrite )
				{
					WriteUserData_GUIData ( eFunc_SetInputAutoGainThreshold - eFunc_SetProductName - 1 );
				}

				l_state = emCmdSucess;
			}
		}
	}

	return l_state;
}

static emCmdFuncStaType mapp_CmdfuncSetInputAutoGainThreshold ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputAutoGainThreshold - eFunc_SetProductName - 1];
	u8 Command[6] = {0xAA,0x10,0,0,0,0};
	u8 dev = 0;
	char* token = strtok ( l_pCmd,"," );

	if ( token != NULL )
	{
		dev = cg_u8_IN_ChannelTable[atoi ( token )][1];
		Command[2] = cg_u8_IN_ChannelTable[atoi ( token )][0];

		pstval->ch |= 1 << Command[2];
		pstval->ch |= 1 << ( atoi ( token ) + 0x10 );

		//dbg_printf("Command[2]:%d,token:%s,atoi(token):%d \r\n",Command[2],token,atoi ( token ));
		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		Command[3] = atoi ( token );
		pstval->param1[Command[2]] = atoi ( token );

		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		Command[4] = atoi ( token );
		pstval->param2[Command[2]] = atoi ( token );

		token = strtok ( NULL,"," );
	}

	memcpy ( pstval->command,Command + 1,5 );
	if (!app_Input_AutoGain_Threshold ( dev, Command ) )
	{
		setJSONToReturnResults ( 1 );
		WriteUserData_GUIData ( eFunc_SetInputAutoGainThreshold - eFunc_SetProductName - 1 );
	}
	else
	{
		setJSONToReturnResults ( 0 );
	}
	//u8 dev = cg_u8_IN_ChannelTable[channel][1];
	//Command[3] = cg_u8_IN_ChannelTable[channel][0];
	//Command[4] = parameter1;
	//Command[5] = parameter2;

	//dbg_printf ( "%s \t cmd:%s\r\n",__FUNCTION__,l_pCmd );

	return emCmdSucess;
}

emCmdFuncStaType set_in_auto_gain_tarset_threshold ( pststMachVal_t pstval,u8 iswrite )
{
	emCmdFuncStaType l_state = emCmdNone;
	u8 Command[6] = {0xAA,0x11,0,0,0,0};

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			Command[2] = cg_u8_IN_ChannelTable[i][0];
			Command[3] = pstval->param1[Command[2]];
			Command[4] = pstval->param2[Command[2]];

			if (!app_Input_AutoGain_TargetThreshold ( cg_u8_IN_ChannelTable[i][1], Command ) )
			{
				if ( iswrite )
				{
					WriteUserData_GUIData ( eFunc_SetInputAutoGainTargetThreshold - eFunc_SetProductName - 1 );
				}

				l_state = emCmdSucess;
			}
		}
	}

	return l_state;
}

static emCmdFuncStaType mapp_CmdfuncSetInputAutoGainTargetThreshold ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputAutoGainTargetThreshold - eFunc_SetProductName - 1];
	u8 Command[6] = {0xAA,0x11,0,0,0,0};
	u8 dev = 0;
	char* token = strtok ( l_pCmd,"," );

	if ( token != NULL )
	{
		dev = cg_u8_IN_ChannelTable[atoi ( token )][1];
		Command[2] = cg_u8_IN_ChannelTable[atoi ( token )][0];

		pstval->ch |= 1 << Command[2];
		pstval->ch |= 1 << ( atoi ( token ) + 0x10 );

		//dbg_printf("Command[2]:%d,token:%s,atoi(token):%d \r\n",Command[2],token,atoi ( token ));
		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		Command[3] = atoi ( token );
		pstval->param1[Command[2]] = atoi ( token );

		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		Command[4] = atoi ( token );
		pstval->param2[Command[2]] = atoi ( token );

		token = strtok ( NULL,"," );
	}

	memcpy ( pstval->command,Command + 1,5 );
	if (!app_Input_AutoGain_TargetThreshold ( dev, Command ) )
	{
		setJSONToReturnResults ( 1 );
		WriteUserData_GUIData ( eFunc_SetInputAutoGainTargetThreshold - eFunc_SetProductName - 1 );
	}
	else
	{
		setJSONToReturnResults ( 0 );
	}
	//u8 dev = cg_u8_IN_ChannelTable[channel][1];
	//Command[3] = cg_u8_IN_ChannelTable[channel][0];
	//Command[4] = parameter1;
	//Command[5] = parameter2;

	//dbg_printf ( "%s \t cmd:%s\r\n",__FUNCTION__,l_pCmd );

	return emCmdSucess;
}

emCmdFuncStaType set_in_auto_gain_ratio ( pststMachVal_t pstval,u8 iswrite )
{
	emCmdFuncStaType l_state = emCmdNone;
	u8 Command[6] = {0xAA,0x12,0,0,0,0};

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			Command[2] = cg_u8_IN_ChannelTable[i][0];
			Command[3] = pstval->param1[Command[2]];
			Command[4] = pstval->param2[Command[2]];

			if (!app_Input_AutoGain_Ratio ( cg_u8_IN_ChannelTable[i][1], Command ) )
			{
				if ( iswrite )
				{
					WriteUserData_GUIData ( eFunc_SetInputAutoGainRatio - eFunc_SetProductName - 1 );
				}

				l_state = emCmdSucess;
			}
		}
	}

	return l_state;
}

static emCmdFuncStaType mapp_CmdfuncSetInputAutoGainRatio ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputAutoGainRatio - eFunc_SetProductName - 1];
	u8 Command[6] = {0xAA,0x12,0,0,0,0};
	u8 dev = 0;
	char* token = strtok ( l_pCmd,"," );

	if ( token != NULL )
	{
		dev = cg_u8_IN_ChannelTable[atoi ( token )][1];
		Command[2] = cg_u8_IN_ChannelTable[atoi ( token )][0];

		pstval->ch |= 1 << Command[2];
		pstval->ch |= 1 << ( atoi ( token ) + 0x10 );

		//dbg_printf("Command[2]:%d,token:%s,atoi(token):%d \r\n",Command[2],token,atoi ( token ));

		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		Command[3] = atoi ( token );
		pstval->param1[Command[2]] = atoi ( token );

		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		Command[4] = atoi ( token );
		pstval->param2[Command[2]] = atoi ( token );

		token = strtok ( NULL,"," );
	}

	memcpy ( pstval->command,Command + 1,5 );
	if (!app_Input_AutoGain_Ratio ( dev, Command ) )
	{
		setJSONToReturnResults ( 1 );
		WriteUserData_GUIData ( eFunc_SetInputAutoGainRatio - eFunc_SetProductName - 1 );
	}
	else
	{
		setJSONToReturnResults ( 0 );
	}
	//u8 dev = cg_u8_IN_ChannelTable[channel][1];
	//Command[3] = cg_u8_IN_ChannelTable[channel][0];
	//Command[4] = parameter1;
	//Command[5] = parameter2;

	//dbg_printf ( "%s \t cmd:%s\r\n",__FUNCTION__,l_pCmd );

	return emCmdSucess;
}

emCmdFuncStaType set_in_auto_gain_start_time ( pststMachVal_t pstval,u8 iswrite )
{
	emCmdFuncStaType l_state = emCmdNone;
	u8 Command[6] = {0xAA,0x13,0,0,0,0};

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			char* p = ( char* ) & ( pstval->param1[cg_u8_IN_ChannelTable[i][0]] );
			u8* pcmd = Command;

			Command[2] = cg_u8_IN_ChannelTable[i][0];
			if ( pstval->param1[Command[2]] <= 0xFFFF )
			{
				memcpy ( pcmd + 3,p + 1,sizeof ( char ) );
				memcpy ( pcmd + 4,p,sizeof ( char ) );
			}

			if (!app_Input_AutoGain_StartTime ( cg_u8_IN_ChannelTable[i][1], Command ) )
			{
				if ( iswrite )
				{
					WriteUserData_GUIData ( eFunc_SetInputAutoGainStartTime - eFunc_SetProductName - 1 );
				}

				l_state = emCmdSucess;
			}
		}
	}

	return l_state;
}

static emCmdFuncStaType mapp_CmdfuncSetInputAutoGainStartTime ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputAutoGainStartTime - eFunc_SetProductName - 1];
	u8 Command[6] = {0xAA,0x13,0,0,0,0};
	u8 dev = 0;
	char* token = strtok ( l_pCmd,"," );

	if ( token != NULL )
	{
		dev = cg_u8_IN_ChannelTable[atoi ( token )][1];
		Command[2] = cg_u8_IN_ChannelTable[atoi ( token )][0];

		pstval->ch |= 1 << Command[2];
		pstval->ch |= 1 << ( atoi ( token ) + 0x10 );

		//dbg_printf("Command[2]:%d,token:%s,atoi(token):%d \r\n",Command[2],token,atoi ( token ));
		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		int32_t val = atoi ( token );
		char* p = ( char* ) &val;
		u8* pcmd = Command;

		if ( val <= 0xFFFF )
		{
			memcpy ( pcmd + 3,p + 1,sizeof ( char ) );
			memcpy ( pcmd + 4,p,sizeof ( char ) );

			pstval->param1[Command[2]] = val;
		}

		token = strtok ( NULL,"," );
	}

	memcpy ( pstval->command,Command + 1,5 );
	if (!app_Input_AutoGain_StartTime ( dev, Command ) )
	{
		setJSONToReturnResults ( 1 );
		WriteUserData_GUIData ( eFunc_SetInputAutoGainStartTime - eFunc_SetProductName - 1 );
	}
	else
	{
		setJSONToReturnResults ( 0 );
	}
	//u8 dev = cg_u8_IN_ChannelTable[channel][1];
	//Command[3] = cg_u8_IN_ChannelTable[channel][0];
	//Command[4] = parameter1;
	//Command[5] = parameter2;

	//dbg_printf ( "%s \t cmd:%s\r\n",__FUNCTION__,l_pCmd );

	return emCmdSucess;
}

emCmdFuncStaType set_in_auto_gain_rel_time ( pststMachVal_t pstval,u8 iswrite )
{
	emCmdFuncStaType l_state = emCmdNone;
	u8 Command[6] = {0xAA,0x14,0,0,0,0};

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			char* p = ( char* ) & ( pstval->param1[cg_u8_IN_ChannelTable[i][0]] );
			u8* pcmd = Command;

			Command[2] = cg_u8_IN_ChannelTable[i][0];
			if ( pstval->param1[Command[2]] <= 0xFFFF )
			{
				memcpy ( pcmd + 3,p + 1,sizeof ( char ) );
				memcpy ( pcmd + 4,p,sizeof ( char ) );
			}

			if (!app_Input_AutoGain_ReleaseTime ( cg_u8_IN_ChannelTable[i][1], Command ) )
			{
				if ( iswrite )
				{
					WriteUserData_GUIData ( eFunc_SetInputAutoGainReleaseTime - eFunc_SetProductName - 1 );
				}

				l_state = emCmdSucess;
			}
		}
	}

	return l_state;
}

static emCmdFuncStaType mapp_CmdfuncSetInputAutoGainReleaseTime ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputAutoGainReleaseTime - eFunc_SetProductName - 1];
	u8 Command[6] = {0xAA,0x14,0,0,0,0};
	u8 dev = 0;
	char* token = strtok ( l_pCmd,"," );

	if ( token != NULL )
	{
		dev = cg_u8_IN_ChannelTable[atoi ( token )][1];
		Command[2] = cg_u8_IN_ChannelTable[atoi ( token )][0];

		pstval->ch |= 1 << Command[2];
		pstval->ch |= 1 << ( atoi ( token ) + 0x10 );

		//dbg_printf("Command[2]:%d,token:%s,atoi(token):%d \r\n",Command[2],token,atoi ( token ));
		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		int32_t val = atoi ( token );
		char* p = ( char* ) &val;
		u8* pcmd = Command;

		if ( val <= 0xFFFF )
		{
			memcpy ( pcmd + 3,p + 1,sizeof ( char ) );
			memcpy ( pcmd + 4,p,sizeof ( char ) );

			pstval->param1[Command[2]] = val;
		}

		token = strtok ( NULL,"," );
	}

	memcpy ( pstval->command,Command + 1,5 );
	if (!app_Input_AutoGain_ReleaseTime ( dev, Command ) )
	{
		setJSONToReturnResults ( 1 );
		WriteUserData_GUIData ( eFunc_SetInputAutoGainReleaseTime - eFunc_SetProductName - 1 );
	}
	else
	{
		setJSONToReturnResults ( 0 );
	}
	//u8 dev = cg_u8_IN_ChannelTable[channel][1];
	//Command[3] = cg_u8_IN_ChannelTable[channel][0];
	//Command[4] = parameter1;
	//Command[5] = parameter2;

	//dbg_printf ( "%s \t cmd:%s\r\n",__FUNCTION__,l_pCmd );

	return emCmdSucess;
}

emCmdFuncStaType set_in_EQ_type ( pststMachVal_t pstval,u8 iswrite )
{
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	u16* pval = pstPrjSaveVar->EQParamter[0];

	emCmdFuncStaType l_state = emCmdNone;
	u8 Command[6] = {0xAA,0x15,0,0,0,0};

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			for ( u8 n = 0; n < EQ; n++ )
			{
				Command[2] = cg_u8_IN_ChannelTable[i][0];
				Command[3] = n;
				Command[4] = (u8)pval[(2 * EQ * i) + (n * 2)];

				if (!app_Input_EQ_Type ( cg_u8_IN_ChannelTable[i][1], Command ) )
				{
					if ( iswrite )
					{
						WriteUserData_GUIData ( eFunc_SetInputEQType - eFunc_SetProductName - 1 );
					}

					l_state = emCmdSucess;
				}
			}
		}
	}

	return l_state;
}

static emCmdFuncStaType mapp_CmdfuncSetInputEQType ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputEQType - eFunc_SetProductName - 1];
	u16* pval = pstPrjSaveVar->EQParamter[0];

	u8 Command[6] = {0xAA,0x15,0,0,0,0};
	u8 dev = 0;
	u8 ch = 0;

	char* token = strtok ( l_pCmd,"," );

	if ( token != NULL )
	{
		dev = cg_u8_IN_ChannelTable[atoi ( token )][1];
		Command[2] = cg_u8_IN_ChannelTable[atoi ( token )][0];

		pstval->ch |= 1 << dev;
		pstval->ch |= 1 << ( atoi ( token ) + 0x10 );
		ch = atoi ( token );

		//dbg_printf("Command[2]:%d,token:%s,atoi(token):%d \r\n",Command[2],token,atoi ( token ));
		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		Command[3] = atoi ( token );
		//pstval->param1[Command[2]] = atoi ( token );

		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		Command[4] = atoi ( token );
		//pstval->param2[Command[2]] = atoi ( token );
    pval[ (2 * EQ * ch) + (Command[3] * 2) ] = Command[4];

		token = strtok ( NULL,"," );
	}

	memcpy ( pstval->command,Command + 1,5 );
	if (!app_Input_EQ_Type ( dev, Command ) )
	{
		setJSONToReturnResults ( 1 );
		WriteUserData_GUIData ( eFunc_SetInputEQType - eFunc_SetProductName - 1 );
	}
	else
	{
		setJSONToReturnResults ( 0 );
	}
	//u8 dev = cg_u8_IN_ChannelTable[channel][1];
	//Command[3] = cg_u8_IN_ChannelTable[channel][0];
	//Command[4] = parameter1;
	//Command[5] = parameter2;

	//dbg_printf ( "%s \t cmd:%s\r\n",__FUNCTION__,l_pCmd );

	return emCmdSucess;
}

emCmdFuncStaType set_in_EQ_gain ( pststMachVal_t pstval,u8 iswrite )
{
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	u16* pval = pstPrjSaveVar->EQParamter[1];
	char* pstEQ =  ( char* ) pval;

	emCmdFuncStaType l_state = emCmdNone;
	u8 Command[6] = {0xAA,0x16,0,0,0,0};

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			for ( u8 n = 0; n < EQ; n++ )
			{
				Command[2] = cg_u8_IN_ChannelTable[i][0];
				Command[3] = n;
				Command[4] = ( u8 ) pstEQ[(2 * EQ * i) + (n * 2)];
				Command[5] = ( u8 ) pstEQ[(2 * EQ * i) + (n * 2 + 1)];

				if (!app_Input_EQ_Gain ( cg_u8_IN_ChannelTable[i][1], Command ) )
				{
					if ( iswrite )
					{
						WriteUserData_GUIData ( eFunc_SetInputEQGain - eFunc_SetProductName - 1 );
					}

					l_state = emCmdSucess;
				}
			}
		}
	}

	return l_state;
}

static emCmdFuncStaType mapp_CmdfuncSetInputEQGain ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputEQGain - eFunc_SetProductName - 1];
	u16* pval = pstPrjSaveVar->EQParamter[1];

	u8 Command[6] = {0xAA,0x16,0,0,0,0};
	u8 dev = 0;
	u8 ch = 0;

	char* token = strtok ( l_pCmd,"," );
	char* pstEQ =  ( char* ) pval;

	if ( token != NULL )
	{
		dev = cg_u8_IN_ChannelTable[atoi ( token )][1];
		Command[2] = cg_u8_IN_ChannelTable[atoi ( token )][0];

		pstval->ch |= 1 << Command[2];
		pstval->ch |= 1 << ( atoi ( token ) + 0x10 );
    ch = atoi ( token );

		//dbg_printf("Command[2]:%d,token:%s,atoi(token):%d \r\n",Command[2],token,atoi ( token ));
		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		Command[3] = atoi ( token );

		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		Command[4] = atoi ( token );
		pstEQ[ (2 * EQ * ch) + (Command[3] * 2) ] = Command[4];

		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		Command[5] = atoi ( token );
		pstEQ[ (2 * EQ * ch) + (Command[3] * 2 + 1) ] = Command[5];

		token = strtok ( NULL,"," );
	}

	memcpy ( pstval->command,Command + 1,5 );
	if (!app_Input_EQ_Gain ( dev, Command ) )
	{
		setJSONToReturnResults ( 1 );
		WriteUserData_GUIData ( eFunc_SetInputEQGain - eFunc_SetProductName - 1 );
	}
	else
	{
		setJSONToReturnResults ( 0 );
	}
	//u8 dev = cg_u8_IN_ChannelTable[channel][1];
	//Command[3] = cg_u8_IN_ChannelTable[channel][0];
	//Command[4] = parameter1;
	//Command[5] = parameter2;

	//dbg_printf ( "%s \t cmd:%s\r\n",__FUNCTION__,l_pCmd );

	return emCmdSucess;
}

emCmdFuncStaType set_in_EQ_quality_factor ( pststMachVal_t pstval,u8 iswrite )
{
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	u16* pval = pstPrjSaveVar->EQParamter[2];
	char* pstEQ =  ( char* ) pval;

	emCmdFuncStaType l_state = emCmdNone;
	u8 Command[6] = {0xAA,0x17,0,0,0,0};

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			for ( u8 n = 0; n < EQ; n++ )
			{
				Command[2] = cg_u8_IN_ChannelTable[i][0];
				Command[3] = n;
				Command[4] = ( u8 ) pstEQ[(2 * EQ * i) + (n * 2)];
				Command[5] = ( u8 ) pstEQ[(2 * EQ * i) + (n * 2 + 1)];

				if (!app_Input_EQ_QualityFactor ( cg_u8_IN_ChannelTable[i][1], Command ) )
				{
					if ( iswrite )
					{
						WriteUserData_GUIData ( eFunc_SetInputEQQualityFactor - eFunc_SetProductName - 1 );
					}

					l_state = emCmdSucess;
				}
			}
		}
	}

	return l_state;
}

static emCmdFuncStaType mapp_CmdfuncSetInputEQQualityFactor ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputEQQualityFactor - eFunc_SetProductName - 1];
	u16* pval = pstPrjSaveVar->EQParamter[2];

	u8 Command[6] = {0xAA,0x17,0,0,0,0};
	u8 dev = 0;
	u8 ch = 0;

	char* token = strtok ( l_pCmd,"," );
	char* pstEQ =  ( char* ) pval;

	if ( token != NULL )
	{
		dev = cg_u8_IN_ChannelTable[atoi ( token )][1];
		Command[2] = cg_u8_IN_ChannelTable[atoi ( token )][0];

		pstval->ch |= 1 << Command[2];
		pstval->ch |= 1 << ( atoi ( token ) + 0x10 );

		//dbg_printf("Command[2]:%d,token:%s,atoi(token):%d \r\n",Command[2],token,atoi ( token ));
		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		Command[3] = atoi ( token );

		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		Command[4] = atoi ( token );
		pstEQ[ (2 * EQ * ch) + (Command[3] * 2) ] = Command[4];

		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		Command[5] = atoi ( token );
		pstEQ[ (2 * EQ * ch) + (Command[3] * 2 + 1) ] = Command[5];

		token = strtok ( NULL,"," );
	}

	memcpy ( pstval->command,Command + 1,5 );
	if (!app_Input_EQ_QualityFactor ( dev, Command ) )
	{
		setJSONToReturnResults ( 1 );
		WriteUserData_GUIData ( eFunc_SetInputEQQualityFactor - eFunc_SetProductName - 1 );
	}
	else
	{
		setJSONToReturnResults ( 0 );
	}
	//u8 dev = cg_u8_IN_ChannelTable[channel][1];
	//Command[3] = cg_u8_IN_ChannelTable[channel][0];
	//Command[4] = parameter1;
	//Command[5] = parameter2;

	//dbg_printf ( "%s \t cmd:%s\r\n",__FUNCTION__,l_pCmd );

	return emCmdSucess;
}

emCmdFuncStaType set_in_EQ_ctrl ( pststMachVal_t pstval,u8 iswrite )
{
	emCmdFuncStaType l_state = emCmdNone;
	u8 Command[6] = {0xAA,0x18,0,0,0,0};

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			Command[2] = cg_u8_IN_ChannelTable[i][0];
			for ( u8 n = 0; n < EQ; n ++ )
			{
				if ( ( pstval->param1[cg_u8_IN_ChannelTable[n][0]] >> n ) & 0x1 ) //关闭
				{
					Command[3] = n;
					Command[4] = 0;

					if (!app_Input_EQ_Ctrl ( cg_u8_IN_ChannelTable[i][1], Command ) )
					{
						if ( iswrite )
						{
							WriteUserData_GUIData ( eFunc_SetInputEQCtrl - eFunc_SetProductName - 1 );
						}

						l_state = emCmdSucess;
					}
				}

				if ( ( pstval->param2[cg_u8_IN_ChannelTable[n][0]] >> n ) & 0x1 ) //打开
				{
					Command[3] = n;
					Command[4] = 1;

					if (!app_Input_EQ_Ctrl ( cg_u8_IN_ChannelTable[i][1], Command ) )
					{
						if ( iswrite )
						{
							WriteUserData_GUIData ( eFunc_SetInputEQCtrl - eFunc_SetProductName - 1 );
						}

						l_state = emCmdSucess;
					}
				}
			}
		}
	}

	return l_state;
}

static emCmdFuncStaType mapp_CmdfuncSetInputEQCtrl ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputEQCtrl - eFunc_SetProductName - 1];
	u8 Command[6] = {0xAA,0x18,0,0,0,0};
	u8 dev = 0;
	int val = 0;
	char* token = strtok ( l_pCmd,"," );

	if ( token != NULL )
	{
		dev = cg_u8_IN_ChannelTable[atoi ( token )][1];
		Command[2] = cg_u8_IN_ChannelTable[atoi ( token )][0];

		val = atoi ( token );
		pstval->ch |= 1 << cg_u8_IN_ChannelTable[atoi ( token )][1];
		pstval->ch |= 1 << ( atoi ( token ) + 0x10 );
		//pstval->param3[atoi ( token )] = cg_u8_IN_ChannelTable[atoi ( token )][1];

		//dbg_printf("Command[2]:%d,token:%s,atoi(token):%d \r\n",Command[2],token,atoi ( token ));
		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		Command[3] = atoi ( token );

		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		Command[4] = atoi ( token );

		if ( Command[4] == 0 ) //关闭
		{
			pstval->param1[val] |= ( 1 << Command[3] );     //关闭标志
			pstval->param2[val] &= ~ ( 1 << Command[3] );   //打开标志

#if 0
			dbg_printf ( "77777777777777777777\r\n" );
			hexdump ( ( void* ) & ( pstval->param1[val] ),sizeof ( pstval->param1[0] ) );
			dbg_printf ( "88888888888888888888888\r\n" );
			hexdump ( ( void* ) & ( pstval->param2[val] ),sizeof ( pstval->param2[0] ) );

			dbg_printf ( "99999999999999999999999,%x,%x\r\n",pstval->param1[val],pstval->param2[val] );
			hexdump ( ( void* ) & ( pstval->param1[val] ),sizeof ( u16 ) );
			hexdump ( ( void* ) & ( pstval->param2[val] ),sizeof ( u16 ) );
#endif
		}

		if ( Command[4] == 1 ) //打开
		{
			pstval->param1[val] &= ~ ( 1 << Command[3] );     //关闭标志
			pstval->param2[val] |= ( 1 << Command[3] );   //打开标志

#if 0
			dbg_printf ( "77777777777777777777\r\n" );
			hexdump ( ( void* ) & ( pstval->param1[val] ),sizeof ( pstval->param1[0] ) );
			dbg_printf ( "88888888888888888888888\r\n" );
			hexdump ( ( void* ) & ( pstval->param2[val] ),sizeof ( pstval->param2[0] ) );

			dbg_printf ( "99999999999999999999,%x,%x\r\n",pstval->param1[val],pstval->param2[val] );
			hexdump ( ( void* ) & ( pstval->param1[val] ),sizeof ( u16 ) );
			hexdump ( ( void* ) & ( pstval->param2[val] ),sizeof ( u16 ) );
#endif
		}

		token = strtok ( NULL,"," );
	}

	memcpy ( pstval->command,Command + 1,5 );
	if (!app_Input_EQ_Ctrl ( dev, Command ) )
	{
		setJSONToReturnResults ( 1 );
		WriteUserData_GUIData ( eFunc_SetInputEQCtrl - eFunc_SetProductName - 1 );
	}
	else
	{
		setJSONToReturnResults ( 0 );
	}

#if 0
	dbg_printf ( "2222222222222222\r\n" );
	hexdump ( ( void* ) pstval,sizeof ( stMachVal_t ) );
	dbg_printf ( "44444444444444444444,%x\r\n",pstval->ch );
	hexdump ( ( void* ) & ( pstval->ch ),sizeof ( pstval->ch ) );
	dbg_printf ( "555555555555555555\r\n" );
	hexdump ( ( void* ) pstval->param1,sizeof ( pstval->param1 ) );
	dbg_printf ( "66666666666666666666666666666666\r\n" );
	hexdump ( ( void* ) pstval->param2,sizeof ( pstval->param2 ) );
	dbg_printf ( "3333333333333333\r\n" );
	hexdump ( ( void* ) & ( pstval->param1[0] ),sizeof ( u16 ) );
	hexdump ( ( void* ) & ( pstval->param2[0] ),sizeof ( u16 ) );
#endif
	return emCmdSucess;
}

emCmdFuncStaType set_in_howling_suppressor_ctrl ( pststMachVal_t pstval,u8 iswrite )
{
	emCmdFuncStaType l_state = emCmdNone;
	u8 Command[6] = {0xAA,0x19,0,0,0,0};

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			Command[2] = cg_u8_IN_ChannelTable[i][0];
			Command[3] = pstval->param1[Command[2]];

			if (!app_Input_HowlingSuppressor_Ctrl ( cg_u8_IN_ChannelTable[i][1], Command ) )
			{
				if ( iswrite )
				{
					WriteUserData_GUIData ( eFunc_SetInputHowlingSuppressorCtrl - eFunc_SetProductName - 1 );
				}

				l_state = emCmdSucess;
			}
		}
	}

	return l_state;
}

static emCmdFuncStaType mapp_CmdfuncSetInputHowlingSuppressorCtrl ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputHowlingSuppressorCtrl - eFunc_SetProductName - 1];
	u8 Command[6] = {0xAA,0x19,0,0,0,0};
	u8 dev = 0;
	char* token = strtok ( l_pCmd,"," );

	if ( token != NULL )
	{
		dev = cg_u8_IN_ChannelTable[atoi ( token )][1];
		Command[2] = cg_u8_IN_ChannelTable[atoi ( token )][0];

		pstval->ch |= 1 << Command[2];
		pstval->ch |= 1 << ( atoi ( token ) + 0x10 );

		//dbg_printf("Command[2]:%d,token:%s,atoi(token):%d \r\n",Command[2],token,atoi ( token ));
		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		Command[3] = atoi ( token );
		pstval->param1[Command[2]] = atoi ( token );

		token = strtok ( NULL,"," );
	}

	memcpy ( pstval->command,Command + 1,5 );
	if (!app_Input_HowlingSuppressor_Ctrl ( dev, Command ) )
	{
		setJSONToReturnResults ( 1 );
		WriteUserData_GUIData ( eFunc_SetInputHowlingSuppressorCtrl - eFunc_SetProductName - 1 );
	}
	else
	{
		setJSONToReturnResults ( 0 );
	}
	//u8 dev = cg_u8_IN_ChannelTable[channel][1];
	//Command[3] = cg_u8_IN_ChannelTable[channel][0];
	//Command[4] = OnOff;

	//dbg_printf ( "%s \t cmd:%s\r\n",__FUNCTION__,l_pCmd );

	return emCmdSucess;
}

emCmdFuncStaType set_in_howling_suppressor_grade ( pststMachVal_t pstval,u8 iswrite )
{
	emCmdFuncStaType l_state = emCmdNone;
	u8 Command[6] = {0xAA,0x1a,0,0,0,0};

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			Command[3] = pstval->param1[0];

			if (!app_Input_HowlingSuppressor_Grade ( cg_u8_IN_ChannelTable[i][1], Command ) )
			{
				if ( iswrite )
				{
					WriteUserData_GUIData ( eFunc_SetInputHowlingSuppressorGrade - eFunc_SetProductName - 1 );
				}

				l_state = emCmdSucess;
			}
		}
	}

	return l_state;
}

static emCmdFuncStaType mapp_CmdfuncSetInputHowlingSuppressorGrade ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputHowlingSuppressorGrade - eFunc_SetProductName - 1];
	u8 Command[6] = {0xAA,0x1a,0,0,0,0};
	u8 dev = 0;
	char* token = strtok ( l_pCmd,"," );

	if ( token != NULL )
	{
		Command[3] = atoi ( token );

		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		u8 len = strlen ( token );
		char param[4] = {0};

		memcpy ( param,token,len - 1 );
		switch ( atoi ( param ) )
		{
			case emInLeft:
				dev = cg_u8_IN_ChannelTable[0][1];
				pstval->ch |= 1 << cg_u8_IN_ChannelTable[0][1];
				pstval->ch |= 1 << 0x10;

				pstval->param1[cg_u8_IN_ChannelTable[0][0]] = Command[3];
				pstval->param2[cg_u8_IN_ChannelTable[0][0]] = emInLeft;
				break;
			case emInRight:
				dev = cg_u8_IN_ChannelTable[5][1];
				pstval->ch |= 1 << cg_u8_IN_ChannelTable[5][1];
				pstval->ch |= 1 << 0x15;

				pstval->param1[cg_u8_IN_ChannelTable[5][0]] = Command[3];
				pstval->param2[cg_u8_IN_ChannelTable[5][0]] = emInRight;
				break;
			default:
				break;
		}

		//dbg_printf ( "LINE:%d param2:%s,len:%d,param:%s,dev:%d\r\n",__LINE__,token,len,param,dev );
		token = strtok ( NULL,"," );
	}

	memcpy ( pstval->command,Command + 1,5 );
	if (!app_Input_HowlingSuppressor_Grade ( dev, Command ) )
	{
		setJSONToReturnResults ( 1 );
		WriteUserData_GUIData ( eFunc_SetInputHowlingSuppressorGrade - eFunc_SetProductName - 1 );
	}
	else
	{
		setJSONToReturnResults ( 0 );
	}
	//Command[4] = parameter1;

	dbg_printf ( "%s \t cmd:%s\r\n",__FUNCTION__,l_pCmd );

	return emCmdSucess;
}

emCmdFuncStaType set_in_howling_suppressor_freq_shift ( pststMachVal_t pstval,u8 iswrite )
{
	emCmdFuncStaType l_state = emCmdNone;
	u8 Command[6] = {0xAA,0x1b,0,0,0,0};

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			Command[3] = pstval->param1[i];

			if (!app_Input_HowlingSuppressor_FreqShift ( cg_u8_IN_ChannelTable[i][1], Command ) )
			{
				if ( iswrite )
				{
					WriteUserData_GUIData ( eFunc_SetInputHowlingSuppressorFreqShift - eFunc_SetProductName - 1 );
				}

				l_state = emCmdSucess;
			}
		}
	}

	return l_state;
}

static emCmdFuncStaType mapp_CmdfuncSetInputHowlingSuppressorFreqShift ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputHowlingSuppressorFreqShift - eFunc_SetProductName - 1];
	u8 Command[6] = {0xAA,0x1b,0,0,0,0};
	u8 dev = 0;
	char* token = strtok ( l_pCmd,"," );

	if ( token != NULL )
	{
		Command[3] = atoi ( token );

		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		u8 len = strlen ( token );
		char param[4] = {0};

		memcpy ( param,token,len - 1 );
		switch ( atoi ( param ) )
		{
			case emInLeft:
				dev = cg_u8_IN_ChannelTable[0][1];
				pstval->ch |= 1 << cg_u8_IN_ChannelTable[0][1];
				pstval->ch |= 1 << 0x10;

				pstval->param1[cg_u8_IN_ChannelTable[0][0]] = Command[3];
				pstval->param2[cg_u8_IN_ChannelTable[0][0]] = emInLeft;
				break;
			case emInRight:
				dev = cg_u8_IN_ChannelTable[5][1];
				pstval->ch |= 1 << cg_u8_IN_ChannelTable[5][1];
				pstval->ch |= 1 << 0x15;

				pstval->param1[cg_u8_IN_ChannelTable[5][0]] = Command[3];
				pstval->param2[cg_u8_IN_ChannelTable[5][0]] = emInRight;
				break;
			default:
				break;
		}

		//dbg_printf ( "LINE:%d param2:%s,len:%d,param:%s,dev:%d\r\n",__LINE__,token,len,param,dev );
		token = strtok ( NULL,"," );
	}

	memcpy ( pstval->command,Command + 1,5 );
	if (!app_Input_HowlingSuppressor_FreqShift ( dev, Command ) )
	{
		setJSONToReturnResults ( 1 );
		WriteUserData_GUIData ( eFunc_SetInputHowlingSuppressorFreqShift - eFunc_SetProductName - 1 );
	}
	else
	{
		setJSONToReturnResults ( 0 );
	}
//Command[4] = parameter1;

	dbg_printf ( "%s \t cmd:%s\r\n",__FUNCTION__,l_pCmd );

	return emCmdSucess;
}

emCmdFuncStaType set_in_noise_suppressor_grade ( pststMachVal_t pstval,u8 iswrite )
{
	emCmdFuncStaType l_state = emCmdNone;
	u8 Command[6] = {0xAA,0x1c,0,0,0,0};

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			Command[3] = pstval->param1[1];

			if (!app_Input_NoiseSuppressor_Grade ( cg_u8_IN_ChannelTable[i][1], Command ) )
			{
				if ( iswrite )
				{
					WriteUserData_GUIData ( eFunc_SetInputNoiseSuppressorGrade - eFunc_SetProductName - 1 );
				}

				l_state = emCmdSucess;
			}
		}
	}

	return l_state;
}

/**
针对单个INPUT生效,噪声抑制只针对输入有效
**/
static emCmdFuncStaType mapp_CmdfuncSetInputNoiseSuppressorGrade ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputNoiseSuppressorGrade - eFunc_SetProductName - 1];
	u8 Command[6] = {0xAA,0x1c,0,0,0,0};
	u8 dev = 0;
	char* token = strtok ( l_pCmd,"," );

	if ( token != NULL )
	{
		Command[3] = atoi ( token );

		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		u8 len = strlen ( token );
		char param[4] = {0};

		memcpy ( param,token,len - 1 );
		switch ( atoi ( param ) )
		{
			case emInLeft:
				dev = cg_u8_IN_ChannelTable[0][1];
				pstval->ch |= 1 << cg_u8_IN_ChannelTable[0][1];
				pstval->ch |= 1 << 0x10;

				pstval->param1[cg_u8_IN_ChannelTable[0][0]] = Command[3];
				pstval->param2[0] = emInLeft;
				break;
			case emInRight:
				dev = cg_u8_IN_ChannelTable[5][1];
				pstval->ch |= 1 << cg_u8_IN_ChannelTable[5][1];
				pstval->ch |= 1 << 0x15;

				pstval->param1[cg_u8_IN_ChannelTable[5][1]] = Command[3];
				pstval->param2[0] = emInRight;
				break;
			default:
				break;
		}

		//dbg_printf ( "step.2 param2:%s,len:%d,param:%s,dev:%d\r\n",token,len,param,dev );
		token = strtok ( NULL,"," );
	}

#if 1
	memcpy ( pstval->command,Command + 1,5 );
	if (!app_Input_NoiseSuppressor_Grade ( dev, Command ) )
	{
		setJSONToReturnResults ( 1 );
		WriteUserData_GUIData ( eFunc_SetInputNoiseSuppressorGrade - eFunc_SetProductName - 1 );
	}
	else
	{
		setJSONToReturnResults ( 0 );
	}
#endif
	//Command[4] = parameter1;

	//dbg_printf ( "%s \t cmd:%s\r\n",__FUNCTION__,l_pCmd );

	return emCmdSucess;
}

emCmdFuncStaType set_in_noise_suppressor_threshold ( pststMachVal_t pstval,u8 iswrite )
{
	emCmdFuncStaType l_state = emCmdNone;
	u8 Command[6] = {0xAA,0x1d,0,0,0,0};

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			Command[3] = pstval->param1[i];
			Command[4] = pstval->param2[i];

			if (!app_Input_NoiseSuppressor_Threshold ( cg_u8_IN_ChannelTable[i][1], Command ) )
			{
				if ( iswrite )
				{
					WriteUserData_GUIData ( eFunc_SetInputNoiseSuppressorThreshold - eFunc_SetProductName - 1 );
				}

				l_state = emCmdSucess;
			}
		}
	}

	return l_state;
}

static emCmdFuncStaType mapp_CmdfuncSetInputNoiseSuppressorThreshold ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputNoiseSuppressorThreshold - eFunc_SetProductName - 1];
	u8 Command[6] = {0xAA,0x1d,0,0,0,0};
	u8 dev = 0;
	char* token = strtok ( l_pCmd,"," );

	if ( token != NULL )
	{
		Command[3] = atoi ( token );

		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		Command[4] = atoi ( token );

		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		u8 len = strlen ( token );
		char param[4] = {0};

		memcpy ( param,token,len - 1 );
		switch ( atoi ( param ) )
		{
			case emInLeft:
				dev = cg_u8_IN_ChannelTable[0][1];
				pstval->ch |= 1 << cg_u8_IN_ChannelTable[0][1];
				pstval->ch |= 1 << 0x10;

				pstval->param1[cg_u8_IN_ChannelTable[0][0]] = Command[3];
				pstval->param2[cg_u8_IN_ChannelTable[0][0]] = Command[4];
				pstval->param3[cg_u8_IN_ChannelTable[0][0]] = emInLeft;
				break;
			case emInRight:
				dev = cg_u8_IN_ChannelTable[5][1];
				pstval->ch |= 1 << cg_u8_IN_ChannelTable[5][1];
				pstval->ch |= 1 << 0x15;

				pstval->param1[cg_u8_IN_ChannelTable[5][0]] = Command[3];
				pstval->param2[cg_u8_IN_ChannelTable[5][0]] = Command[4];
				pstval->param3[cg_u8_IN_ChannelTable[5][0]] = emInRight;
				break;
			default:
				break;
		}

		//dbg_printf ( "LINE:%d token:%s,len:%d,param:%s,dev:%d\r\n",__LINE__,token,len,param,dev );
		token = strtok ( NULL,"," );
	}

	memcpy ( pstval->command,Command + 1,5 );
	if (!app_Input_NoiseSuppressor_Threshold ( dev, Command ) )
	{
		setJSONToReturnResults ( 1 );
		WriteUserData_GUIData ( eFunc_SetInputNoiseSuppressorThreshold - eFunc_SetProductName - 1 );
	}
	else
	{
		setJSONToReturnResults ( 0 );
	}

//Command[4] = parameter1;
	//Command[5] = parameter2;

	//dbg_printf ( "%s \t cmd:%s\r\n",__FUNCTION__,l_pCmd );
	//setJSONToReturnResults ( 1 );

	return emCmdSucess;
}

emCmdFuncStaType set_in_noise_suppressor_ratio ( pststMachVal_t pstval,u8 iswrite )
{
	emCmdFuncStaType l_state = emCmdNone;
	u8 Command[6] = {0xAA,0x1e,0,0,0,0};

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			Command[3] = pstval->param1[i];
			Command[4] = pstval->param2[i];

			if (!app_Input_NoiseSuppressor_Ratio ( cg_u8_IN_ChannelTable[i][1], Command ) )
			{
				if ( iswrite )
				{
					WriteUserData_GUIData ( eFunc_SetInputNoiseSuppressorRatio - eFunc_SetProductName - 1 );
				}

				l_state = emCmdSucess;
			}
		}
	}

	return l_state;
}

static emCmdFuncStaType mapp_CmdfuncSetInputNoiseSuppressorRatio ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputNoiseSuppressorRatio - eFunc_SetProductName - 1];
	u8 Command[6] = {0xAA,0x1e,0,0,0,0};
	u8 dev = 0;
	char* token = strtok ( l_pCmd,"," );

#if 0
	if ( token != NULL )
	{
		dev = cg_u8_IN_ChannelTable[atoi ( token )][1];
		//Command[3] = cg_u8_IN_ChannelTable[atoi ( token )][0];

		token = strtok ( NULL,"," );
	}
#endif

	if ( token != NULL )
	{
		Command[3] = atoi ( token );

		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		Command[4] = atoi ( token );

		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		u8 len = strlen ( token );
		char param[4] = {0};

		memcpy ( param,token,len - 1 );
		switch ( atoi ( param ) )
		{
			case emInLeft:
				dev = cg_u8_IN_ChannelTable[0][1];
				pstval->ch |= 1 << cg_u8_IN_ChannelTable[0][1];
				pstval->ch |= 1 << 0x10;

				pstval->param1[cg_u8_IN_ChannelTable[0][0]] = Command[3];
				pstval->param2[cg_u8_IN_ChannelTable[0][0]] = Command[4];
				pstval->param3[cg_u8_IN_ChannelTable[0][0]] = emInLeft;
				break;
			case emInRight:
				dev = cg_u8_IN_ChannelTable[5][1];
				pstval->ch |= 1 << cg_u8_IN_ChannelTable[5][1];
				pstval->ch |= 1 << 0x15;

				pstval->param1[cg_u8_IN_ChannelTable[5][0]] = Command[3];
				pstval->param2[cg_u8_IN_ChannelTable[5][0]] = Command[4];
				pstval->param3[cg_u8_IN_ChannelTable[5][0]] = emInRight;
				break;
			default:
				break;
		}

		//dbg_printf ( "LINE:%d token:%s,len:%d,param:%s,dev:%d\r\n",__LINE__,token,len,param,dev );
		token = strtok ( NULL,"," );
	}

	memcpy ( pstval->command,Command + 1,5 );
	if (!app_Input_NoiseSuppressor_Ratio ( dev, Command ) )
	{
		setJSONToReturnResults ( 1 );
		WriteUserData_GUIData ( eFunc_SetInputNoiseSuppressorRatio - eFunc_SetProductName - 1 );
	}
	else
	{
		setJSONToReturnResults ( 0 );
	}
//Command[4] = parameter1;
	//Command[5] = parameter2;

	//dbg_printf ( "%s \t cmd:%s\r\n",__FUNCTION__,l_pCmd );

	return emCmdSucess;
}

emCmdFuncStaType set_in_noise_suppressor_start_time ( pststMachVal_t pstval,u8 iswrite )
{
	emCmdFuncStaType l_state = emCmdNone;
	u8 Command[6] = {0xAA,0x1f,0,0,0,0};

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			char* p = ( char* ) & ( pstval->param1[cg_u8_IN_ChannelTable[i][0]] );
			u8* pcmd = Command;

			if ( pstval->param1[i] <= 0xFFFF )
			{
				memcpy ( pcmd + 3,p + 1,sizeof ( char ) );
				memcpy ( pcmd + 4,p,sizeof ( char ) );
			}

			if (!app_Input_NoiseSuppressor_StartTime ( cg_u8_IN_ChannelTable[i][1], Command ) )
			{
				if ( iswrite )
				{
					WriteUserData_GUIData ( eFunc_SetInputNoiseSuppressorStartTime - eFunc_SetProductName - 1 );
				}

				l_state = emCmdSucess;
			}
		}
	}

	return l_state;
}

static emCmdFuncStaType mapp_CmdfuncSetInputNoiseSuppressorStartTime ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputNoiseSuppressorStartTime - eFunc_SetProductName - 1];
	u8 Command[6] = {0xAA,0x1f,0,0,0,0};
	u8 dev = 0;
	int32_t val = 0;
	char* token = strtok ( l_pCmd,"," );

#if 0
	if ( token != NULL )
	{
		dev = cg_u8_IN_ChannelTable[atoi ( token )][1];
		//Command[3] = cg_u8_IN_ChannelTable[atoi ( token )][0];

		token = strtok ( NULL,"," );
	}
#endif

	if ( token != NULL )
	{
		char* p = ( char* ) &val;
		u8* pcmd = Command;

		val = atoi ( token );
		if ( val <= 0xFFFF )
		{
			memcpy ( pcmd + 3,p + 1,sizeof ( char ) );
			memcpy ( pcmd + 4,p,sizeof ( char ) );
		}

		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		u8 len = strlen ( token );
		char param[4] = {0};

		memcpy ( param,token,len - 1 );
		switch ( atoi ( param ) )
		{
			case emInLeft:
				dev = cg_u8_IN_ChannelTable[0][1];
				pstval->ch |= 1 << cg_u8_IN_ChannelTable[0][1];
				pstval->ch |= 1 << 0x10;

				pstval->param1[cg_u8_IN_ChannelTable[0][0]] = val;
				pstval->param3[cg_u8_IN_ChannelTable[0][0]] = emInLeft;
				break;
			case emInRight:
				dev = cg_u8_IN_ChannelTable[5][1];
				pstval->ch |= 1 << cg_u8_IN_ChannelTable[5][1];
				pstval->ch |= 1 << 0x15;

				pstval->param1[cg_u8_IN_ChannelTable[5][0]] = val;
				pstval->param3[0] = emInRight;
				break;
			default:
				break;
		}

		//dbg_printf ( "LINE:%d token:%s,len:%d,param:%s,dev:%d\r\n",__LINE__,token,len,param,dev );
		token = strtok ( NULL,"," );
	}

	memcpy ( pstval->command,Command + 1,5 );
	if (!app_Input_NoiseSuppressor_StartTime ( dev, Command ) )
	{
		setJSONToReturnResults ( 1 );
		WriteUserData_GUIData ( eFunc_SetInputNoiseSuppressorStartTime - eFunc_SetProductName - 1 );
	}
	else
	{
		setJSONToReturnResults ( 0 );
	}
//Command[4] = parameter1;
	//Command[5] = parameter2;

	//dbg_printf ( "%s \t cmd:%s\r\n",__FUNCTION__,l_pCmd );

	return emCmdSucess;
}

emCmdFuncStaType set_in_noise_suppressor_rel_time ( pststMachVal_t pstval,u8 iswrite )
{
	emCmdFuncStaType l_state = emCmdNone;
	u8 Command[6] = {0xAA,0x20,0,0,0,0};

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			char* p = ( char* ) & ( pstval->param1[cg_u8_IN_ChannelTable[i][0]] );
			u8* pcmd = Command;

			if ( pstval->param1[i] <= 0xFFFF )
			{
				memcpy ( pcmd + 3,p + 1,sizeof ( char ) );
				memcpy ( pcmd + 4,p,sizeof ( char ) );
			}

			if (!app_Input_NoiseSuppressor_ReleaseTime ( cg_u8_IN_ChannelTable[i][1], Command ) )
			{
				if ( iswrite )
				{
					WriteUserData_GUIData ( eFunc_SetInputNoiseSuppressorReleaseTime - eFunc_SetProductName - 1 );
				}

				l_state = emCmdSucess;
			}
		}
	}

	return l_state;
}

static emCmdFuncStaType mapp_CmdfuncSetInputNoiseSuppressorReleaseTime ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputNoiseSuppressorReleaseTime - eFunc_SetProductName - 1];
	u8 Command[6] = {0xAA,0x20,0,0,0,0};
	u8 dev = 0;
	int32_t val = 0;
	char* token = strtok ( l_pCmd,"," );

#if 0
	if ( token != NULL )
	{
		dev = cg_u8_IN_ChannelTable[atoi ( token )][1];
		//Command[3] = cg_u8_IN_ChannelTable[atoi ( token )][0];

		token = strtok ( NULL,"," );
	}
#endif

	if ( token != NULL )
	{
		char* p = ( char* ) &val;
		u8* pcmd = Command;

		val = atoi ( token );
		if ( val <= 0xFFFF )
		{
			memcpy ( pcmd + 3,p + 1,sizeof ( char ) );
			memcpy ( pcmd + 4,p,sizeof ( char ) );
		}

		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		u8 len = strlen ( token );
		char param[4] = {0};

		memcpy ( param,token,len - 1 );
		switch ( atoi ( param ) )
		{
			case emInLeft:
				dev = cg_u8_IN_ChannelTable[0][1];
				pstval->ch |= 1 << cg_u8_IN_ChannelTable[0][1];
				pstval->ch |= 1 << 0x10;

				pstval->param1[cg_u8_IN_ChannelTable[0][0]] = val;
				pstval->param2[cg_u8_IN_ChannelTable[0][0]] = emInLeft;
				break;
			case emInRight:
				dev = cg_u8_IN_ChannelTable[5][1];
				pstval->ch |= 1 << cg_u8_IN_ChannelTable[5][1];
				pstval->ch |= 1 << 0x15;

				pstval->param1[cg_u8_IN_ChannelTable[5][0]] = val;
				pstval->param2[cg_u8_IN_ChannelTable[5][0]] = emInRight;
				break;
			default:
				break;
		}

		//dbg_printf ( "LINE:%d token:%s,len:%d,param:%s,dev:%d\r\n",__LINE__,token,len,param,dev );
		token = strtok ( NULL,"," );
	}

	memcpy ( pstval->command,Command + 1,5 );
	if (!app_Input_NoiseSuppressor_ReleaseTime ( dev, Command ) )
	{
		setJSONToReturnResults ( 1 );
		WriteUserData_GUIData ( eFunc_SetInputNoiseSuppressorReleaseTime - eFunc_SetProductName - 1 );
	}
	else
	{
		setJSONToReturnResults ( 0 );
	}
//Command[4] = parameter1;
	//Command[5] = parameter2;

	//dbg_printf ( "%s \t cmd:%s\r\n",__FUNCTION__,l_pCmd );

	return emCmdSucess;
}

emCmdFuncStaType set_in_noise_suppressor_ctrl ( pststMachVal_t pstval,u8 iswrite )
{
	emCmdFuncStaType l_state = emCmdNone;
	u8 Command[6] = {0xAA,0x21,0,0,0,0};

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			Command[2] = cg_u8_IN_ChannelTable[i][0];
			Command[3] = pstval->param1[Command[2]];

			if (!app_Input_NoiseSuppressor_Ctrl ( cg_u8_IN_ChannelTable[i][1], Command ) )
			{
				if ( iswrite )
				{
					WriteUserData_GUIData ( eFunc_SetInputNoiseSuppressorCtrl - eFunc_SetProductName - 1 );
				}

				l_state = emCmdSucess;
			}
		}
	}

	return l_state;
}

static emCmdFuncStaType mapp_CmdfuncSetInputNoiseSuppressorCtrl ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputNoiseSuppressorCtrl - eFunc_SetProductName - 1];
	u8 Command[6] = {0xAA,0x21,0,0,0,0};
	u8 dev = 0;
	char* token = strtok ( l_pCmd,"," );

	if ( token != NULL )
	{
		dev = cg_u8_IN_ChannelTable[atoi ( token )][1];
		Command[2] = cg_u8_IN_ChannelTable[atoi ( token )][0];

		pstval->ch |= 1 << Command[2];
		pstval->ch |= 1 << ( atoi ( token ) + 0x10 );

		//dbg_printf("Command[2]:%d,token:%s,atoi(token):%d \r\n",Command[2],token,atoi ( token ));
		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		Command[3] = atoi ( token );
		pstval->param1[Command[2]] = atoi ( token );

		token = strtok ( NULL,"," );
	}

	memcpy ( pstval->command,Command + 1,5 );
	if (!app_Input_NoiseSuppressor_Ctrl ( dev, Command ) )
	{
		setJSONToReturnResults ( 1 );
		WriteUserData_GUIData ( eFunc_SetInputNoiseSuppressorCtrl - eFunc_SetProductName - 1 );
	}
	else
	{
		setJSONToReturnResults ( 0 );
	}
	//u8 dev = cg_u8_IN_ChannelTable[channel][1];
	//Command[3] = cg_u8_IN_ChannelTable[channel][0];
	//Command[4] = OnOff;

	//dbg_printf ( "%s \t cmd:%s\r\n",__FUNCTION__,l_pCmd );

	return emCmdSucess;
}

emCmdFuncStaType set_in_echo_canceller_grade ( pststMachVal_t pstval,u8 iswrite )
{
	emCmdFuncStaType l_state = emCmdNone;
	u8 Command[6] = {0xAA,0x22,0,0,0,0};

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			Command[3] = pstval->param1[i];

			if (!app_Input_EchoCanceller_Ctrl ( cg_u8_IN_ChannelTable[i][1], Command ) )
			{
				if ( iswrite )
				{
					WriteUserData_GUIData ( eFunc_SetInputEchoCancellerGrade - eFunc_SetProductName - 1 );
				}

				l_state = emCmdSucess;
			}
		}
	}

	return l_state;
}

static emCmdFuncStaType mapp_CmdfuncSetInputEchoCancellerGrade ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputEchoCancellerGrade - eFunc_SetProductName - 1];
	u8 Command[6] = {0xAA,0x22,0,0,0,0};
	u8 dev = 0;
	char* token = strtok ( l_pCmd,"," );

	if ( token != NULL )
	{
		Command[3] = atoi ( token );

		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		u8 len = strlen ( token );
		char param[4] = {0};

		memcpy ( param,token,len - 1 );
		switch ( atoi ( param ) )
		{
			case emInLeft:
				dev = cg_u8_IN_ChannelTable[0][1];

				pstval->ch |= 1 << cg_u8_IN_ChannelTable[0][1];
				pstval->ch |= 1 << 0x10;

				pstval->param1[cg_u8_IN_ChannelTable[0][0]] = Command[3];
				pstval->param2[cg_u8_IN_ChannelTable[0][0]] = emInLeft;
				break;
			case emInRight:
				dev = cg_u8_IN_ChannelTable[5][1];

				pstval->ch |= 1 << cg_u8_IN_ChannelTable[5][1];
				pstval->ch |= 1 << 0x15;

				pstval->param1[cg_u8_IN_ChannelTable[5][0]] = Command[3];
				pstval->param2[cg_u8_IN_ChannelTable[5][0]] = emInRight;
				break;
			default:
				break;
		}

		//dbg_printf ( "LINE:%d param2:%s,len:%d,param:%s,dev:%d\r\n",__LINE__,token,len,param,dev );
		token = strtok ( NULL,"," );
	}

	memcpy ( pstval->command,Command + 1,5 );
	if (!app_Input_EchoCanceller_Ctrl ( dev, Command ) )
	{
		setJSONToReturnResults ( 1 );
		WriteUserData_GUIData ( eFunc_SetInputEchoCancellerGrade - eFunc_SetProductName - 1 );
	}
	else
	{
		setJSONToReturnResults ( 0 );
	}
//u8 dev = cg_u8_IN_ChannelTable[channel][1];
	//Command[3] = cg_u8_IN_ChannelTable[channel][0];
	//Command[4] = parameter1;

	//dbg_printf ( "%s \t cmd:%s\r\n",__FUNCTION__,l_pCmd );

	return emCmdSucess;
}

emCmdFuncStaType set_in_echo_canceller_ctrl ( pststMachVal_t pstval,u8 iswrite )
{
	emCmdFuncStaType l_state = emCmdNone;
	u8 Command[6] = {0xAA,0x23,0,0,0,0};

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			Command[2] = cg_u8_IN_ChannelTable[i][0];
			Command[3] = pstval->param1[Command[2]];

			if (!app_Input_EchoCanceller_Grade ( cg_u8_IN_ChannelTable[i][1], Command ) )
			{
				if ( iswrite )
				{
					WriteUserData_GUIData ( eFunc_SetInputEchoCancellerCtrl - eFunc_SetProductName - 1 );
				}

				l_state = emCmdSucess;
			}
		}
	}

	return l_state;
}

static emCmdFuncStaType mapp_CmdfuncSetInputEchoCancellerCtrl ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputEchoCancellerCtrl - eFunc_SetProductName - 1];
	u8 Command[6] = {0xAA,0x23,0,0,0,0};
	u8 dev = 0;
	char* token = strtok ( l_pCmd,"," );

	if ( token != NULL )
	{
		dev = cg_u8_IN_ChannelTable[atoi ( token )][1];
		Command[2] = cg_u8_IN_ChannelTable[atoi ( token )][0];

		pstval->ch |= 1 << Command[2];
		pstval->ch |= 1 << ( atoi ( token ) + 0x10 );

		//dbg_printf("Command[2]:%d,token:%s,atoi(token):%d \r\n",Command[2],token,atoi ( token ));
		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		Command[3] = atoi ( token );
		pstval->param1[Command[2]] = atoi ( token );

		token = strtok ( NULL,"," );
	}

	memcpy ( pstval->command,Command + 1,5 );
	if (!app_Input_EchoCanceller_Grade ( dev, Command ) )
	{
		setJSONToReturnResults ( 1 );
		WriteUserData_GUIData ( eFunc_SetInputEchoCancellerCtrl - eFunc_SetProductName - 1 );
	}
	else
	{
		setJSONToReturnResults ( 0 );
	}
//u8 dev = cg_u8_IN_ChannelTable[channel][1];
	//Command[3] = cg_u8_IN_ChannelTable[channel][0];
	//Command[4] = OnOff;

	//dbg_printf ( "%s \t cmd:%s\r\n",__FUNCTION__,l_pCmd );

	return emCmdSucess;
}

emCmdFuncStaType set_in_l_freq_exciter_grade ( pststMachVal_t pstval,u8 iswrite )
{
	emCmdFuncStaType l_state = emCmdNone;
	u8 Command[6] = {0xAA,0x24,0,0,0,0};

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			Command[2] = cg_u8_IN_ChannelTable[i][0];
			Command[3] = pstval->param1[Command[2]];

			if (!app_Input_LfreqExciter_Grade ( cg_u8_IN_ChannelTable[i][1], Command ) )
			{
				if ( iswrite )
				{
					WriteUserData_GUIData ( eFunc_SetInputLfreqExciterGrade - eFunc_SetProductName - 1 );
				}

				l_state = emCmdSucess;
			}
		}
	}

	return l_state;
}

static emCmdFuncStaType mapp_CmdfuncSetInputLfreqExciterGrade ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputLfreqExciterGrade - eFunc_SetProductName - 1];
	u8 Command[6] = {0xAA,0x24,0,0,0,0};
	u8 dev = 0;
	char* token = strtok ( l_pCmd,"," );

	if ( token != NULL )
	{
		dev = cg_u8_IN_ChannelTable[atoi ( token )][1];
		Command[2] = cg_u8_IN_ChannelTable[atoi ( token )][0];

		pstval->ch |= 1 << Command[2];
		pstval->ch |= 1 << ( atoi ( token ) + 0x10 );

		//dbg_printf("Command[2]:%d,token:%s,atoi(token):%d \r\n",Command[2],token,atoi ( token ));
		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		Command[3] = atoi ( token );
		pstval->param1[Command[2]] = atoi ( token );

		token = strtok ( NULL,"," );
	}

	memcpy ( pstval->command,Command + 1,5 );
	if (!app_Input_LfreqExciter_Grade ( dev, Command ) )
	{
		setJSONToReturnResults ( 1 );
		WriteUserData_GUIData ( eFunc_SetInputLfreqExciterGrade - eFunc_SetProductName - 1 );
	}
	else
	{
		setJSONToReturnResults ( 0 );
	}
//u8 dev = cg_u8_IN_ChannelTable[channel][1];
	//Command[3] = cg_u8_IN_ChannelTable[channel][0];
	//Command[4] = parameter1;

	//dbg_printf ( "%s \t cmd:%s\r\n",__FUNCTION__,l_pCmd );

	return emCmdSucess;
}

emCmdFuncStaType set_in_h_freq_exciter_grade ( pststMachVal_t pstval,u8 iswrite )
{
	emCmdFuncStaType l_state = emCmdNone;
	u8 Command[6] = {0xAA,0x25,0,0,0,0};

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			Command[2] = cg_u8_IN_ChannelTable[i][0];
			Command[3] = pstval->param1[Command[2]];

			if (!app_Input_HfreqExciter_Grade ( cg_u8_IN_ChannelTable[i][1], Command ) )
			{
				if ( iswrite )
				{
					WriteUserData_GUIData ( eFunc_SetInputHfreqExciterGrade - eFunc_SetProductName - 1 );
				}

				l_state = emCmdSucess;
			}
		}
	}

	return l_state;
}

static emCmdFuncStaType mapp_CmdfuncSetInputHfreqExciterGrade ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputHfreqExciterGrade - eFunc_SetProductName - 1];
	u8 Command[6] = {0xAA,0x25,0,0,0,0};
	u8 dev = 0;
	char* token = strtok ( l_pCmd,"," );

	if ( token != NULL )
	{
		dev = cg_u8_IN_ChannelTable[atoi ( token )][1];
		Command[2] = cg_u8_IN_ChannelTable[atoi ( token )][0];

		pstval->ch |= 1 << Command[2];
		pstval->ch |= 1 << ( atoi ( token ) + 0x10 );

		//dbg_printf("Command[2]:%d,token:%s,atoi(token):%d \r\n",Command[2],token,atoi ( token ));
		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		Command[3] = atoi ( token );
		pstval->param1[Command[2]] = atoi ( token );

		token = strtok ( NULL,"," );
	}

	memcpy ( pstval->command,Command + 1,5 );
	if (!app_Input_HfreqExciter_Grade ( dev, Command ) )
	{
		setJSONToReturnResults ( 1 );
		WriteUserData_GUIData ( eFunc_SetInputHfreqExciterGrade - eFunc_SetProductName - 1 );
	}
	else
	{
		setJSONToReturnResults ( 0 );
	}
//u8 dev = cg_u8_IN_ChannelTable[channel][1];
	//Command[3] = cg_u8_IN_ChannelTable[channel][0];
	//Command[4] = parameter1;

	//dbg_printf ( "%s \t cmd:%s\r\n",__FUNCTION__,l_pCmd );

	return emCmdSucess;
}

emCmdFuncStaType set_in_exciter_ctrl ( pststMachVal_t pstval,u8 iswrite )
{
	emCmdFuncStaType l_state = emCmdNone;
	u8 Command[6] = {0xAA,0x26,0,0,0,0};

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			Command[2] = cg_u8_IN_ChannelTable[i][0];
			Command[3] = pstval->param1[Command[2]];

			if (!app_Input_Exciter_Ctrl ( cg_u8_IN_ChannelTable[i][1], Command ) )
			{
				if ( iswrite )
				{
					WriteUserData_GUIData ( eFunc_SetInputExciterCtrl - eFunc_SetProductName - 1 );
				}

				l_state = emCmdSucess;
			}
		}
	}

	return l_state;
}

static emCmdFuncStaType mapp_CmdfuncSetInputExciterCtrl ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputExciterCtrl - eFunc_SetProductName - 1];
	u8 Command[6] = {0xAA,0x26,0,0,0,0};
	u8 dev = 0;
	char* token = strtok ( l_pCmd,"," );

	if ( token != NULL )
	{
		dev = cg_u8_IN_ChannelTable[atoi ( token )][1];
		Command[2] = cg_u8_IN_ChannelTable[atoi ( token )][0];

		pstval->ch |= 1 << Command[2];
		pstval->ch |= 1 << ( atoi ( token ) + 0x10 );

		//dbg_printf("Command[2]:%d,token:%s,atoi(token):%d \r\n",Command[2],token,atoi ( token ));
		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		Command[3] = atoi ( token );
		pstval->param1[Command[2]] = atoi ( token );

		token = strtok ( NULL,"," );
	}

	memcpy ( pstval->command,Command + 1,5 );
	if (!app_Input_Exciter_Ctrl ( dev, Command ) )
	{
		setJSONToReturnResults ( 1 );
		WriteUserData_GUIData ( eFunc_SetInputExciterCtrl - eFunc_SetProductName - 1 );
	}
	else
	{
		setJSONToReturnResults ( 0 );
	}
//u8 dev = cg_u8_IN_ChannelTable[channel][1];
	//Command[3] = cg_u8_IN_ChannelTable[channel][0];
	//Command[4] = OnOff;

	//dbg_printf ( "%s \t cmd:%s\r\n",__FUNCTION__,l_pCmd );

	return emCmdSucess;
}

emCmdFuncStaType set_in_call_input ( pststMachVal_t pstval,u8 iswrite )
{
	emCmdFuncStaType l_state = emCmdNone;
	u8 Command[6] = {0xAA,0x27,0,0,0,0};

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			Command[2] = cg_u8_IN_ChannelTable[i][0];
			Command[3] = pstval->param1[Command[2]];

			if (!app_Input_CallInput ( cg_u8_IN_ChannelTable[i][1], Command ) )
			{
				if ( iswrite )
				{
					WriteUserData_GUIData ( eFunc_SetInputCallInput - eFunc_SetProductName - 1 );
				}

				l_state = emCmdSucess;
			}
		}
	}

	return l_state;
}

static emCmdFuncStaType mapp_CmdfuncSetInputCallInput ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputCallInput - eFunc_SetProductName - 1];
	u8 Command[6] = {0xAA,0x27,0,0,0,0};
	u8 dev = 0;
	char* token = strtok ( l_pCmd,"," );

	if ( token != NULL )
	{
		dev = cg_u8_IN_ChannelTable[atoi ( token )][1];
		Command[2] = cg_u8_IN_ChannelTable[atoi ( token )][0];

		pstval->ch |= 1 << Command[2];
		pstval->ch |= 1 << ( atoi ( token ) + 0x10 );

		//dbg_printf("Command[2]:%d,token:%s,atoi(token):%d \r\n",Command[2],token,atoi ( token ));
		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		Command[3] = atoi ( token );
		pstval->param1[Command[2]] = atoi ( token );

		token = strtok ( NULL,"," );
	}

	memcpy ( pstval->command,Command + 1,5 );
	if (!app_Input_CallInput ( dev, Command ) )
	{
		setJSONToReturnResults ( 1 );
		WriteUserData_GUIData ( eFunc_SetInputCallInput - eFunc_SetProductName - 1 );
	}
	else
	{
		setJSONToReturnResults ( 0 );
	}
//u8 dev = cg_u8_IN_ChannelTable[channel][1];
	//Command[3] = cg_u8_IN_ChannelTable[channel][0];
	//Command[4] = OnOff;

	//dbg_printf ( "%s \t cmd:%s\r\n",__FUNCTION__,l_pCmd );

	return emCmdSucess;
}

emCmdFuncStaType set_in_background_input ( pststMachVal_t pstval,u8 iswrite )
{
	emCmdFuncStaType l_state = emCmdNone;
	u8 Command[6] = {0xAA,0x28,0,0,0,0};

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			Command[2] = cg_u8_IN_ChannelTable[i][0];
			Command[3] = pstval->param1[Command[2]];

			if (!app_Input_BackgroundInput ( cg_u8_IN_ChannelTable[i][1], Command ) )
			{
				if ( iswrite )
				{
					WriteUserData_GUIData ( eFunc_SetInputBackgroundInput - eFunc_SetProductName - 1 );
				}

				l_state = emCmdSucess;
			}
		}
	}

	return l_state;
}

static emCmdFuncStaType mapp_CmdfuncSetInputBackgroundInput ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputBackgroundInput - eFunc_SetProductName - 1];
	u8 Command[6] = {0xAA,0x28,0,0,0,0};
	u8 dev = 0;
	char* token = strtok ( l_pCmd,"," );

	if ( token != NULL )
	{
		dev = cg_u8_IN_ChannelTable[atoi ( token )][1];
		Command[2] = cg_u8_IN_ChannelTable[atoi ( token )][0];

		pstval->ch |= 1 << Command[2];
		pstval->ch |= 1 << ( atoi ( token ) + 0x10 );

		//dbg_printf("Command[2]:%d,token:%s,atoi(token):%d \r\n",Command[2],token,atoi ( token ));
		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		Command[3] = atoi ( token );
		pstval->param1[Command[2]] = atoi ( token );

		token = strtok ( NULL,"," );
	}

	memcpy ( pstval->command,Command + 1,5 );
	if (!app_Input_BackgroundInput ( dev, Command ) )
	{
		setJSONToReturnResults ( 1 );
		WriteUserData_GUIData ( eFunc_SetInputBackgroundInput - eFunc_SetProductName - 1 );
	}
	else
	{
		setJSONToReturnResults ( 0 );
	}
//u8 dev = cg_u8_IN_ChannelTable[channel][1];
	//Command[3] = cg_u8_IN_ChannelTable[channel][0];
	//Command[4] = OnOff;

	//dbg_printf ( "%s \t cmd:%s\r\n",__FUNCTION__,l_pCmd );

	return emCmdSucess;
}

emCmdFuncStaType set_in_ducking_gain ( pststMachVal_t pstval,u8 iswrite )
{
	emCmdFuncStaType l_state = emCmdNone;
	u8 Command[6] = {0xAA,0x29,0,0,0,0};

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			Command[2] = cg_u8_IN_ChannelTable[i][0];
			Command[3] = pstval->param1[Command[2]];
			Command[4] = pstval->param2[Command[2]];

			if (!app_Input_Ducking_Gain ( cg_u8_IN_ChannelTable[i][1], Command ) )
			{
				if ( iswrite )
				{
					WriteUserData_GUIData ( eFunc_SetInputDuckingGain - eFunc_SetProductName - 1 );
				}

				l_state = emCmdSucess;
			}
		}
	}

	return l_state;
}

static emCmdFuncStaType mapp_CmdfuncSetInputDuckingGain ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputDuckingGain - eFunc_SetProductName - 1];
	u8 Command[6] = {0xAA,0x29,0,0,0,0};
	u8 dev = 0;
	char* token = strtok ( l_pCmd,"," );

	if ( token != NULL )
	{
		dev = cg_u8_IN_ChannelTable[atoi ( token )][1];
		Command[2] = cg_u8_IN_ChannelTable[atoi ( token )][0];

		pstval->ch |= 1 << Command[2];
		pstval->ch |= 1 << ( atoi ( token ) + 0x10 );

		//dbg_printf("Command[2]:%d,token:%s,atoi(token):%d \r\n",Command[2],token,atoi ( token ));
		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		Command[3] = atoi ( token );
		pstval->param1[Command[2]] = atoi ( token );

		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		Command[4] = atoi ( token );
		pstval->param2[Command[2]] = atoi ( token );

		token = strtok ( NULL,"," );
	}

	memcpy ( pstval->command,Command + 1,5 );
	if (!app_Input_Ducking_Gain ( dev, Command ) )
	{
		setJSONToReturnResults ( 1 );
		WriteUserData_GUIData ( eFunc_SetInputDuckingGain - eFunc_SetProductName - 1 );
	}
	else
	{
		setJSONToReturnResults ( 0 );
	}
//u8 dev = cg_u8_IN_ChannelTable[channel][1];
	//Command[3] = cg_u8_IN_ChannelTable[channel][0];
	//Command[4] = parameter1;
	//Command[5] = parameter2;

	//dbg_printf ( "%s \t cmd:%s\r\n",__FUNCTION__,l_pCmd );

	return emCmdSucess;
}

emCmdFuncStaType set_in_ducking_threshold ( pststMachVal_t pstval,u8 iswrite )
{
	emCmdFuncStaType l_state = emCmdNone;
	u8 Command[6] = {0xAA,0x2a,0,0,0,0};

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			Command[3] = pstval->param1[0];
			Command[4] = pstval->param2[0];

			if (!app_Input_Ducking_Threshold ( cg_u8_IN_ChannelTable[i][1], Command ) )
			{
				if ( iswrite )
				{
					WriteUserData_GUIData ( eFunc_SetInputDuckingThreshold - eFunc_SetProductName - 1 );
				}

				l_state = emCmdSucess;
			}
		}
	}

	return l_state;
}

static emCmdFuncStaType mapp_CmdfuncSetInputDuckingThreshold ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputDuckingThreshold - eFunc_SetProductName - 1];
	u8 Command[6] = {0xAA,0x2a,0,0,0,0};
	//u8 dev = 0;
	u8 dev1 = 0,dev2 = 0;
	char* token = strtok ( l_pCmd,"," );

#if 0
	if ( token != NULL )
	{
		dev = cg_u8_IN_ChannelTable[atoi ( token )][1];
		//Command[3] = cg_u8_IN_ChannelTable[atoi ( token )][0];

		token = strtok ( NULL,"," );
	}
#endif

	//memset ( pstval,0,sizeof ( stMachVal_t ) );
	if ( token != NULL )
	{
		Command[3] = atoi ( token );
		pstval->param1[0] = atoi ( token );

		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		Command[4] = atoi ( token );
		pstval->param2[0] = atoi ( token );

		token = strtok ( NULL,"," );
	}

#if 0
	if ( token != NULL )
	{
		u8 len = strlen ( token );
		char param[4] = {0};

		memcpy ( param,token,len - 1 );
		switch ( atoi ( param ) )
		{
			case emInLeft:
				dev = cg_u8_IN_ChannelTable[0][1];
				pstval->ch |= 1 << cg_u8_IN_ChannelTable[0][0];
				pstval->param3[0] = emInLeft;
				break;
			case emInRight:
				dev = cg_u8_IN_ChannelTable[5][1];
				pstval->ch |= 1 << cg_u8_IN_ChannelTable[5][0];
				pstval->param3[0] = emInRight;
				break;
			default:
				break;
		}

		dbg_printf ( "LINE:%d param2:%s,len:%d,param:%s,dev:%d\r\n",__LINE__,token,len,param,dev );
		token = strtok ( NULL,"," );
	}
#endif

	dev1 = cg_u8_IN_ChannelTable[0][1];
	pstval->ch |= 1 << cg_u8_IN_ChannelTable[0][0];
	pstval->ch |= 1 << 0x10;
	pstval->param3[0] = emInLeft;

	dev2 = cg_u8_IN_ChannelTable[5][1];
	pstval->ch |= 1 << cg_u8_IN_ChannelTable[5][0];
	pstval->ch |= 1 << 0x15;
	pstval->param3[0] = emInRight;

	memcpy ( pstval->command,Command + 1,5 );
	if (!app_Input_Ducking_Threshold ( dev1, Command ) && !app_Input_Ducking_Threshold ( dev2, Command ) )
	{
		WriteUserData_GUIData ( eFunc_SetInputDuckingThreshold - eFunc_SetProductName - 1 );
		setJSONToReturnResults ( 1 );
	}
	else
	{
		setJSONToReturnResults ( 0 );
	}
//Command[4] = parameter1;
	//Command[5] = parameter2;

	//dbg_printf ( "%s \t cmd:%s\r\n",__FUNCTION__,l_pCmd );

	return emCmdSucess;
}

emCmdFuncStaType set_in_ducking_depth ( pststMachVal_t pstval,u8 iswrite )
{
	emCmdFuncStaType l_state = emCmdNone;
	u8 Command[6] = {0xAA,0x2b,0,0,0,0};

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			Command[3] = pstval->param1[0];
			Command[4] = pstval->param2[0];

			if (!app_Input_Ducking_Depth ( cg_u8_IN_ChannelTable[i][1], Command ) )
			{
				if ( iswrite )
				{
					WriteUserData_GUIData ( eFunc_SetInputDuckingDepth - eFunc_SetProductName - 1 );
				}

				l_state = emCmdSucess;
			}
		}
	}

	return l_state;
}

static emCmdFuncStaType mapp_CmdfuncSetInputDuckingDepth ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputDuckingDepth - eFunc_SetProductName - 1];
	u8 Command[6] = {0xAA,0x2b,0,0,0,0};
	//u8 dev = 0;
	u8 dev1 = 0,dev2 = 0;
	char* token = strtok ( l_pCmd,"," );

#if 0
	if ( token != NULL )
	{
		dev = cg_u8_IN_ChannelTable[atoi ( token )][1];
		//Command[3] = cg_u8_IN_ChannelTable[atoi ( token )][0];

		token = strtok ( NULL,"," );
	}
#endif

	if ( token != NULL )
	{
		Command[3] = atoi ( token );
		pstval->param1[0] = atoi ( token );

		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		Command[4] = atoi ( token );
		pstval->param2[0] = atoi ( token );

		token = strtok ( NULL,"," );
	}

#if 0
	if ( token != NULL )
	{
		u8 len = strlen ( token );
		char param[4] = {0};

		memcpy ( param,token,len - 1 );
		switch ( atoi ( param ) )
		{
			case emInLeft:
				dev = cg_u8_IN_ChannelTable[0][1];
				pstval->ch |= 1 << cg_u8_IN_ChannelTable[0][0];
				pstval->param3[0] = emInLeft;
				break;
			case emInRight:
				dev = cg_u8_IN_ChannelTable[5][1];
				pstval->ch |= 1 << cg_u8_IN_ChannelTable[5][0];
				pstval->param3[0] = emInRight;
				break;
			default:
				break;
		}

		dbg_printf ( "LINE:%d param2:%s,len:%d,param:%s,dev:%d\r\n",__LINE__,token,len,param,dev );
		token = strtok ( NULL,"," );
	}
#endif

	dev1 = cg_u8_IN_ChannelTable[0][1];
	pstval->ch |= 1 << cg_u8_IN_ChannelTable[0][0];
	pstval->ch |= 1 << 0x10;
	pstval->param3[0] = emInLeft;

	dev2 = cg_u8_IN_ChannelTable[5][1];
	pstval->ch |= 1 << cg_u8_IN_ChannelTable[5][0];
	pstval->ch |= 1 << 0x15;
	pstval->param3[0] = emInRight;

	memcpy ( pstval->command,Command + 1,5 );
	if (!app_Input_Ducking_Depth ( dev1, Command ) & !app_Input_Ducking_Depth ( dev2, Command ) )
	{
		WriteUserData_GUIData ( eFunc_SetInputDuckingDepth - eFunc_SetProductName - 1 );
		setJSONToReturnResults ( 1 );
	}
	else
	{
		setJSONToReturnResults ( 0 );
	}
//Command[4] = parameter1;
	//Command[5] = parameter2;

	//dbg_printf ( "%s \t cmd:%s\r\n",__FUNCTION__,l_pCmd );

	return emCmdSucess;
}

emCmdFuncStaType set_in_ducking_start_time ( pststMachVal_t pstval,u8 iswrite )
{
	emCmdFuncStaType l_state = emCmdNone;
	u8 Command[6] = {0xAA,0x2c,0,0,0,0};

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			char* p = ( char* ) & ( pstval->param1[cg_u8_IN_ChannelTable[i][0]] );
			u8* pcmd = Command;

			if ( pstval->param1[Command[2]] <= 0xFFFF )
			{
				memcpy ( pcmd + 3,p + 1,sizeof ( char ) );
				memcpy ( pcmd + 4,p,sizeof ( char ) );
			}

			if (!app_Input_Ducking_StartTime ( cg_u8_IN_ChannelTable[i][1], Command ) )
			{
				if ( iswrite )
				{
					WriteUserData_GUIData ( eFunc_SetInputDuckingStartTime - eFunc_SetProductName - 1 );
				}

				l_state = emCmdSucess;
			}
		}
	}

	return l_state;
}

static emCmdFuncStaType mapp_CmdfuncSetInputDuckingStartTime ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputDuckingStartTime - eFunc_SetProductName - 1];
	u8 Command[6] = {0xAA,0x2c,0,0,0,0};
	//u8 dev = 0;
	u8 dev1 = 0,dev2 = 0;
	int32_t val;
	char* token = strtok ( l_pCmd,"," );

	if ( token != NULL )
	{
		char* p = ( char* ) &val;
		u8* pcmd = Command;

		val = atoi ( token );
		if ( val <= 0xFFFF )
		{
			memcpy ( pcmd + 3,p + 1,sizeof ( char ) );
			memcpy ( pcmd + 4,p,sizeof ( char ) );
		}

		token = strtok ( NULL,"," );
	}

	dev1 = cg_u8_IN_ChannelTable[0][1];
	pstval->ch |= 1 << cg_u8_IN_ChannelTable[0][1];
	pstval->ch |= 1 << 0x10;

	pstval->param1[cg_u8_IN_ChannelTable[0][0]] = val;
	pstval->param2[0] = emInLeft;

	dev2 = cg_u8_IN_ChannelTable[5][1];
	pstval->ch |= 1 << cg_u8_IN_ChannelTable[5][1];
	pstval->ch |= 1 << 0x15;

	pstval->param1[cg_u8_IN_ChannelTable[5][0]] = val;
	pstval->param2[0] = emInRight;

	memcpy ( pstval->command,Command + 1,5 );
	if (!app_Input_Ducking_StartTime ( dev1, Command ) & !app_Input_Ducking_StartTime ( dev2, Command ) )
	{
		WriteUserData_GUIData ( eFunc_SetInputDuckingStartTime - eFunc_SetProductName - 1 );
		setJSONToReturnResults ( 1 );
	}
	else
	{
		setJSONToReturnResults ( 0 );
	}
//Command[4] = parameter1;
	//Command[5] = parameter2;

	//dbg_printf ( "%s \t cmd:%s\r\n",__FUNCTION__,l_pCmd );

	return emCmdSucess;
}

emCmdFuncStaType set_in_ducking_hold_time ( pststMachVal_t pstval,u8 iswrite )
{
	emCmdFuncStaType l_state = emCmdNone;
	u8 Command[6] = {0xAA,0x2d,0,0,0,0};

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			char* p = ( char* ) & ( pstval->param1[cg_u8_IN_ChannelTable[i][0]] );
			u8* pcmd = Command;

			if ( pstval->param1[Command[2]] <= 0xFFFF )
			{
				memcpy ( pcmd + 3,p + 1,sizeof ( char ) );
				memcpy ( pcmd + 4,p,sizeof ( char ) );
			}

			if (!app_Input_Ducking_HoldTime ( cg_u8_IN_ChannelTable[i][1], Command ) )
			{
				if ( iswrite )
				{
					WriteUserData_GUIData ( eFunc_SetInputDuckingHoldTime - eFunc_SetProductName - 1 );
				}

				l_state = emCmdSucess;
			}
		}
	}

	return l_state;
}

static emCmdFuncStaType mapp_CmdfuncSetInputDuckingHoldTime ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputDuckingHoldTime - eFunc_SetProductName - 1];
	u8 Command[6] = {0xAA,0x2d,0,0,0,0};
	//u8 dev = 0;
	u8 dev1 = 0,dev2 = 0;
	int32_t val;
	char* token = strtok ( l_pCmd,"," );

	if ( token != NULL )
	{
		char* p = ( char* ) &val;
		u8* pcmd = Command;

		val = atoi ( token );
		if ( val <= 0xFFFF )
		{
			memcpy ( pcmd + 3,p + 1,sizeof ( char ) );
			memcpy ( pcmd + 4,p,sizeof ( char ) );
		}

		token = strtok ( NULL,"," );
	}

	dev1 = cg_u8_IN_ChannelTable[0][1];
	pstval->ch |= 1 << cg_u8_IN_ChannelTable[0][1];
	pstval->ch |= 1 << 0x10;

	pstval->param1[cg_u8_IN_ChannelTable[0][0]] = val;
	pstval->param2[0] = emInLeft;

	dev2 = cg_u8_IN_ChannelTable[5][1];
	pstval->ch |= 1 << cg_u8_IN_ChannelTable[5][1];
	pstval->ch |= 1 << 0x15;

	pstval->param1[cg_u8_IN_ChannelTable[5][0]] = val;
	pstval->param2[0] = emInRight;


	memcpy ( pstval->command,Command + 1,5 );
	if (!app_Input_Ducking_HoldTime ( dev1, Command ) & !app_Input_Ducking_HoldTime ( dev2, Command ) )
	{
		WriteUserData_GUIData ( eFunc_SetInputDuckingHoldTime - eFunc_SetProductName - 1 );
		setJSONToReturnResults ( 1 );
	}
	else
	{
		setJSONToReturnResults ( 0 );
	}
//Command[4] = parameter1;
	//Command[5] = parameter2;

	//dbg_printf ( "%s \t cmd:%s\r\n",__FUNCTION__,l_pCmd );

	return emCmdSucess;
}

emCmdFuncStaType set_in_ducking_rel_time ( pststMachVal_t pstval,u8 iswrite )
{
	emCmdFuncStaType l_state = emCmdNone;
	u8 Command[6] = {0xAA,0x2e,0,0,0,0};

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			char* p = ( char* ) & ( pstval->param1[cg_u8_IN_ChannelTable[i][0]] );
			u8* pcmd = Command;

			if ( pstval->param1[Command[2]] <= 0xFFFF )
			{
				memcpy ( pcmd + 3,p + 1,sizeof ( char ) );
				memcpy ( pcmd + 4,p,sizeof ( char ) );
			}

			if (!app_Input_Ducking_ReleaseTime ( cg_u8_IN_ChannelTable[i][1], Command ) )
			{
				if ( iswrite )
				{
					WriteUserData_GUIData ( eFunc_SetInputDuckingReleaseTime - eFunc_SetProductName - 1 );
				}

				l_state = emCmdSucess;
			}
		}
	}

	return l_state;
}

static emCmdFuncStaType mapp_CmdfuncSetInputDuckingReleaseTime ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputDuckingReleaseTime - eFunc_SetProductName - 1];
	u8 Command[6] = {0xAA,0x2e,0,0,0,0};
	//u8 dev = 0;
	u8 dev1 = 0,dev2 = 0;
	int32_t val;
	char* token = strtok ( l_pCmd,"," );

#if 0
	if ( token != NULL )
	{
		dev = cg_u8_IN_ChannelTable[atoi ( token )][1];
		//Command[3] = cg_u8_IN_ChannelTable[atoi ( token )][0];

		token = strtok ( NULL,"," );
	}
#endif

	if ( token != NULL )
	{
		char* p = ( char* ) &val;
		u8* pcmd = Command;

		val = atoi ( token );
		if ( val <= 0xFFFF )
		{
			memcpy ( pcmd + 3,p + 1,sizeof ( char ) );
			memcpy ( pcmd + 4,p,sizeof ( char ) );
		}

		token = strtok ( NULL,"," );
	}

	dev1 = cg_u8_IN_ChannelTable[0][1];
	pstval->ch |= 1 << cg_u8_IN_ChannelTable[0][1];
	pstval->ch |= 1 << 0x10;

	pstval->param1[cg_u8_IN_ChannelTable[0][0]] = val;
	pstval->param3[cg_u8_IN_ChannelTable[0][0]] = emInLeft;

	dev2 = cg_u8_IN_ChannelTable[5][1];
	pstval->ch |= 1 << cg_u8_IN_ChannelTable[5][1];
	pstval->ch |= 1 << 0x15;

	pstval->param1[cg_u8_IN_ChannelTable[5][0]] = val;
	pstval->param3[cg_u8_IN_ChannelTable[5][0]] = emInRight;

	memcpy ( pstval->command,Command + 1,5 );
	if (!app_Input_Ducking_ReleaseTime ( dev1, Command ) & !app_Input_Ducking_ReleaseTime ( dev2, Command ) )
	{
		WriteUserData_GUIData ( eFunc_SetInputDuckingReleaseTime - eFunc_SetProductName - 1 );
		setJSONToReturnResults ( 1 );
	}
	else
	{
		setJSONToReturnResults ( 0 );
	}
//Command[4] = parameter1;
	//Command[5] = parameter2;

	//dbg_printf ( "%s \t cmd:%s\r\n",__FUNCTION__,l_pCmd );

	return emCmdSucess;
}

emCmdFuncStaType set_in_ducking_ctrl ( pststMachVal_t pstval,u8 iswrite )
{
	emCmdFuncStaType l_state = emCmdNone;
	u8 Command[6] = {0xAA,0x2f,0,0,0,0};

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			Command[3] = pstval->param1[0];

			if (!app_Input_Ducking_Ctrl ( cg_u8_IN_ChannelTable[i][1], Command ) )
			{
				if ( iswrite )
				{
					WriteUserData_GUIData ( eFunc_SetInputDuckingCtrl - eFunc_SetProductName - 1 );
				}

				l_state = emCmdSucess;
			}
		}
	}

	return l_state;
}

static emCmdFuncStaType mapp_CmdfuncSetInputDuckingCtrl ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputDuckingCtrl - eFunc_SetProductName - 1];
	u8 Command[6] = {0xAA,0x2f,0,0,0,0};
	//u8 dev = 0;
	u8 dev1 = 0,dev2 = 0;
	char* token = strtok ( l_pCmd,"," );

#if 0
	if ( token != NULL )
	{
		dev = cg_u8_IN_ChannelTable[atoi ( token )][1];
		//Command[3] = cg_u8_IN_ChannelTable[atoi ( token )][0];

		token = strtok ( NULL,"," );
	}
#endif

	if ( token != NULL )
	{
		Command[3] = atoi ( token );
		pstval->param1[0] = atoi ( token );

		token = strtok ( NULL,"," );
	}

#if 0
	if ( token != NULL )
	{
		u8 len = strlen ( token );
		char param[4] = {0};

		memcpy ( param,token,len - 1 );
		switch ( atoi ( param ) )
		{
			case emInLeft:
				dev = cg_u8_IN_ChannelTable[0][1];
				pstval->ch |= 1 << cg_u8_IN_ChannelTable[0][0];
				pstval->param2[0] = emInLeft;
				break;
			case emInRight:
				dev = cg_u8_IN_ChannelTable[5][1];
				pstval->ch |= 1 << cg_u8_IN_ChannelTable[5][0];
				pstval->param2[0] = emInRight;
				break;
			default:
				break;
		}

		dbg_printf ( "LINE:%d param2:%s,len:%d,param:%s,dev:%d\r\n",__LINE__,token,len,param,dev );
		token = strtok ( NULL,"," );
	}
#endif

	dev1 = cg_u8_IN_ChannelTable[0][1];
	pstval->ch |= 1 << cg_u8_IN_ChannelTable[0][0];
	pstval->ch |= 1 << 0x10;
	pstval->param3[0] = emInLeft;

	dev2 = cg_u8_IN_ChannelTable[5][1];
	pstval->ch |= 1 << cg_u8_IN_ChannelTable[5][0];
	pstval->ch |= 1 << 0x15;
	pstval->param3[0] = emInRight;

	memcpy ( pstval->command,Command + 1,5 );
	if (!app_Input_Ducking_Ctrl ( dev1, Command ) & !app_Input_Ducking_Ctrl ( dev2, Command ) )
	{
		WriteUserData_GUIData ( eFunc_SetInputDuckingCtrl - eFunc_SetProductName - 1 );
		setJSONToReturnResults ( 1 );
	}
	else
	{
		setJSONToReturnResults ( 0 );
	}
//Command[4] = OnOff;

	//dbg_printf ( "%s \t cmd:%s\r\n",__FUNCTION__,l_pCmd );

	return emCmdSucess;
}

emCmdFuncStaType set_matrixswitch ( pststMachVal_t pstval,u8 iswrite )
{
	emCmdFuncStaType l_state = emCmdNone;
	u8 Command[6] = {0xAA,0x30,0,0,0,0};
	u8 ischanged = 0;

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> i ) & 0x1 )
		{
			Command[3] = i;
			for ( u8 m = 0; m < MAX_CH_LEN ; m++ )
			{
				Command[4] = m;
				if ( ( pstval->param1[i] >> m ) & 0x1 )
				{
					Command[5] = 1;
					ischanged = 1;
				}

				if ( ( pstval->param2[i] >> m ) & 0x1 )
				{
					Command[5] = 0;
					ischanged =1;
				}

				if ( ischanged )
				{
					if (! ( app_MatrixSwitching ( 1, Command ) & app_MatrixSwitching ( 0, Command ) ) )
					{
						if ( iswrite )
						{
							WriteUserData_GUIData ( eFunc_SetMatrixSwitching - eFunc_SetProductName - 1 );
						}

						ischanged = 0;
					}
				}
			}
		}

		l_state = emCmdSucess;
	}

	return l_state;
}

static emCmdFuncStaType mapp_CmdfuncSetMatrixSwitching ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetMatrixSwitching - eFunc_SetProductName - 1];
	u8 Command[6] = {0xAA,0x30,0,0,0,0};
	//u8 dev = 0;
	char* token = strtok ( l_pCmd,"," );

	if ( token != NULL )
	{
		Command[3] = atoi ( token );

		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		Command[4] = atoi ( token );

		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		Command[5] = atoi ( token );

		token = strtok ( NULL,"," );
	}

	pstval->ch |= ( 1 << Command[3] );
	pstval->ch |= ( 1 << ( 0x10 + Command[4] ) );

	if ( Command[5] )    //on
	{
		pstval->param1[ Command[3] ] |=   ( 1 << Command[4] );
		pstval->param2[ Command[3] ] &= ~ ( 1 << Command[4] ); //关闭置0
	}
	else                //off
	{
		pstval->param1[ Command[3] ] &= ~ ( 1 << Command[4] );
		pstval->param2[ Command[3] ] |=   ( 1 << Command[4] );  //关闭置1
	}

	memcpy ( pstval->command,Command + 1,5 );
	if (! ( app_MatrixSwitching ( 1, Command ) & app_MatrixSwitching ( 0, Command ) ) )
	{
		WriteUserData_GUIData ( eFunc_SetMatrixSwitching - eFunc_SetProductName - 1 );
		setJSONToReturnResults ( 1 );
	}
	else
	{
		setJSONToReturnResults ( 0 );
	}

	//u8 dev = cg_u8_OUT_ChannelTable[parameter1][1];
	//Command[4] = cg_u8_OUT_ChannelTable[parameter1][0];
	//Command[5] = cg_u8_IN_ChannelTable[parameter2][0];

	//dbg_printf ( "%s \t cmd:%s\r\n",__FUNCTION__,l_pCmd );

	return emCmdSucess;
}

emCmdFuncStaType set_out_delay_time ( pststMachVal_t pstval,u8 iswrite )
{
	emCmdFuncStaType l_state = emCmdNone;
	u8 Command[6] = {0xAA,0x31,0,0,0,0};

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			char* p = ( char* ) & ( pstval->param1[cg_u8_OUT_ChannelTable[i][0]] );
			u8* pcmd = Command;

			Command[2] = cg_u8_OUT_ChannelTable[i][0];

			if ( pstval->param1[Command[2]] <= 0xFFFF )
			{
				memcpy ( pcmd + 3,p + 1,sizeof ( char ) );
				memcpy ( pcmd + 4,p,sizeof ( char ) );
			}

			if (!app_Output_DelayTime ( cg_u8_OUT_ChannelTable[i][1], Command ) )
			{
				if ( iswrite )
				{
					WriteUserData_GUIData ( eFunc_SetOutputDelayTime - eFunc_SetProductName - 1 );
				}

				l_state = emCmdSucess;
			}
		}
	}

	return l_state;
}

static emCmdFuncStaType mapp_CmdfuncSetOutputDelayTime ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetOutputDelayTime - eFunc_SetProductName - 1];
	u8 Command[6] = {0xAA,0x31,0,0,0,0};

	u8 dev = 0;
	int32_t val;
	char* token = strtok ( l_pCmd,"," );

	if ( token != NULL )
	{
		dev = cg_u8_OUT_ChannelTable[atoi ( token )][1];
		Command[2] = cg_u8_OUT_ChannelTable[atoi ( token )][0];

		pstval->ch |= 1 << Command[2];
		pstval->ch |= 1 << ( atoi ( token ) + 0x10 );

		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		char* p = ( char* ) &val;
		u8* pcmd = Command;

		val = atoi ( token );
		if ( val <= 0xFFFF )
		{
			memcpy ( pcmd + 3,p + 1,sizeof ( char ) );
			memcpy ( pcmd + 4,p,sizeof ( char ) );

			pstval->param1[Command[2]] = val;
		}

		token = strtok ( NULL,"," );
	}

	memcpy ( pstval->command,Command + 1,5 );
	if (!app_Output_DelayTime ( dev, Command ) )
	{
		setJSONToReturnResults ( 1 );
		WriteUserData_GUIData ( eFunc_SetOutputDelayTime - eFunc_SetProductName - 1 );
	}
	else
	{
		setJSONToReturnResults ( 0 );
	}

	//Command[3] = cg_u8_OUT_ChannelTable[channel][0];
	//Command[4] = parameter1;
	//Command[5] = parameter2;

	//dbg_printf ( "%s \t cmd:%s\r\n",__FUNCTION__,l_pCmd );

	return emCmdSucess;
}

emCmdFuncStaType set_out_delay_ctrl ( pststMachVal_t pstval,u8 iswrite )
{
	emCmdFuncStaType l_state = emCmdNone;
	u8 Command[6] = {0xAA,0x32,0,0,0,0};

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			Command[2] = cg_u8_OUT_ChannelTable[i][0];
			Command[3] = pstval->param1[Command[2]];

			if (!app_Output_Delay_Ctrl ( cg_u8_OUT_ChannelTable[i][1], Command ) )
			{
				if ( iswrite )
				{
					WriteUserData_GUIData ( eFunc_SetOutputDelayCtrl - eFunc_SetProductName - 1 );
				}

				l_state = emCmdSucess;
			}
		}
	}

	return l_state;
}

static emCmdFuncStaType mapp_CmdfuncSetOutputDelayCtrl ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetOutputDelayCtrl - eFunc_SetProductName - 1];
	u8 Command[6] = {0xAA,0x32,0,0,0,0};
	u8 dev = 0;
	char* token = strtok ( l_pCmd,"," );

	if ( token != NULL )
	{
		dev = cg_u8_OUT_ChannelTable[atoi ( token )][1];
		Command[2] = cg_u8_OUT_ChannelTable[atoi ( token )][0];

		pstval->ch |= 1 << Command[2];
		pstval->ch |= 1 << ( atoi ( token ) + 0x10 );

		//dbg_printf("Command[2]:%d,token:%s,atoi(token):%d \r\n",Command[2],token,atoi ( token ));
		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		Command[3] = atoi ( token );
		pstval->param1[Command[2]] = atoi ( token );

		token = strtok ( NULL,"," );
	}

	memcpy ( pstval->command,Command + 1,5 );
	if (!app_Output_Delay_Ctrl ( dev, Command ) )
	{
		setJSONToReturnResults ( 1 );
		WriteUserData_GUIData ( eFunc_SetOutputDelayCtrl - eFunc_SetProductName - 1 );
	}
	else
	{
		setJSONToReturnResults ( 0 );
	}

//u8 dev = cg_u8_OUT_ChannelTable[channel][1];

	//Command[3] = cg_u8_OUT_ChannelTable[channel][0];
	//Command[4] = parameter1;

	//dbg_printf ( "%s \t cmd:%s\r\n",__FUNCTION__,l_pCmd );

	return emCmdSucess;
}

emCmdFuncStaType set_usbplayer_ctrl ( pststMachVal_t pstval,u8 iswrite )
{
	emCmdFuncStaType l_state = emCmdNone;
	u8 Command[6] = {0xAA,0x33,0,0,0,0};

	Command[3] = pstval->param1[0];
	Command[4] = pstval->param2[0];

	if (! ( app_USBplayer_Ctrl ( 0, Command ) && app_USBplayer_Ctrl ( 1, Command ) ) )
	{
		if ( iswrite )
		{
			WriteUserData_GUIData ( eFunc_SetUSBplayerCtrl - eFunc_SetProductName - 1 );
		}

		l_state = emCmdSucess;
	}

	return l_state;
}

static emCmdFuncStaType mapp_CmdfuncSetUSBplayerCtrl ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetUSBplayerCtrl - eFunc_SetProductName - 1];
	u8 Command[6] = {0xAA,0x33,0,0,0,0};

	//u8 dev = 0;
	char* token = strtok ( l_pCmd,"," );

	if ( token != NULL )
	{
		Command[3] = atoi ( token );
		pstval->param1[0] = atoi ( token );

		token = strtok ( NULL,"," );
	}

	if ( token != NULL )
	{
		Command[4] = atoi ( token );
		pstval->param2[0] = atoi ( token );

		token = strtok ( NULL,"," );
	}

	memcpy ( pstval->command,Command + 1,5 );
	if (! ( app_USBplayer_Ctrl ( 0, Command ) && app_USBplayer_Ctrl ( 1, Command ) ) )
	{
		setJSONToReturnResults ( 1 );
		WriteUserData_GUIData ( eFunc_SetUSBplayerCtrl - eFunc_SetProductName - 1 );
	}
	else
	{
		setJSONToReturnResults ( 0 );
	}

	//u8 dev = cg_u8_OUT_ChannelTable[channel][1];

	//Command[3] = cg_u8_OUT_ChannelTable[channel][0];
	//Command[4] = parameter1;

	//dbg_printf ( "%s \t cmd:%s\r\n",__FUNCTION__,l_pCmd );

	return emCmdSucess;
}

static emCmdFuncStaType set_all_data ( pststMachVal_t pstval, eCmdFun_t em,u8 iswrite )
{
	switch ( em )
	{
		case eFunc_SetAllAudioOutput - eFunc_SetProductName - 1:
		{
			set_all_audio_output ( pstval,iswrite );
			break;
		}
		case eFunc_SetInputSensitivity - eFunc_SetProductName - 1:
		{
			set_in_sensitivity ( pstval,iswrite );
			break;
		}
		case eFunc_SetInputGain - eFunc_SetProductName - 1:
		{
			set_in_gain ( pstval,iswrite );
			break;
		}
		case eFunc_SetInputMute - eFunc_SetProductName - 1:
		{
			set_in_mute ( pstval,iswrite );
			break;
		}
		case eFunc_SetInputReversephase - eFunc_SetProductName - 1:
		{
			set_in_reversephase ( pstval,iswrite );
			break;
		}
		case eFunc_SetInputTestSignalCtrl - eFunc_SetProductName - 1:
		{
			set_in_test_signal_ctrl ( pstval,iswrite );
			break;
		}
		case eFunc_SetInputTestSignalFreq - eFunc_SetProductName - 1:
		{
			set_in_test_signal_freq ( pstval,iswrite );
			break;
		}
		case eFunc_SetInputTestSignalLevel - eFunc_SetProductName - 1:
		{
			set_in_test_signal_level ( pstval,iswrite );
			break;
		}
		case eFunc_SetInputCompressorCtrl - eFunc_SetProductName - 1:
		{
			set_in_compressor_ctrl ( pstval,iswrite );
			break;
		}
		case eFunc_SetInputCompressorGain - eFunc_SetProductName - 1:
		{
			set_in_compressor_gain ( pstval,iswrite );
			break;
		}
		case eFunc_SetInputCompressorThreshold - eFunc_SetProductName - 1:
		{
			set_in_compressor_threshold ( pstval,iswrite );
			break;
		}
		case eFunc_SetInputCompressorRatio - eFunc_SetProductName - 1:
		{
			set_in_compressor_ratio ( pstval,iswrite );
			break;
		}
		case eFunc_SetInputCompressorStartTime - eFunc_SetProductName - 1:
		{
			set_in_compressor_start_time ( pstval,iswrite );
			break;
		}
		case eFunc_SetInputCompressorReleaseTime - eFunc_SetProductName - 1:
		{
			set_in_compressor_rel_time ( pstval,iswrite );
			break;
		}
		case eFunc_SetInputAutoGainCtrl - eFunc_SetProductName - 1:
		{
			set_in_auto_gain_ctrl ( pstval,iswrite );
			break;
		}
		case eFunc_SetInputAutoGainThreshold - eFunc_SetProductName - 1:
		{
			set_in_auto_gain_threshold ( pstval,iswrite );
			break;
		}
		case eFunc_SetInputAutoGainTargetThreshold - eFunc_SetProductName - 1:
		{
			set_in_auto_gain_tarset_threshold ( pstval,iswrite );
			break;
		}
		case eFunc_SetInputAutoGainRatio - eFunc_SetProductName - 1:
		{
			set_in_auto_gain_ratio ( pstval,iswrite );
			break;
		}
		case eFunc_SetInputAutoGainStartTime - eFunc_SetProductName - 1:
		{
			set_in_auto_gain_start_time ( pstval,iswrite );
			break;
		}
		case eFunc_SetInputAutoGainReleaseTime - eFunc_SetProductName - 1:
		{
			set_in_auto_gain_rel_time ( pstval,iswrite );
			break;
		}
		case eFunc_SetInputEQType - eFunc_SetProductName - 1:
		{
			set_in_EQ_type ( pstval,iswrite );
			break;
		}
		case eFunc_SetInputEQGain - eFunc_SetProductName - 1:
		{
			set_in_EQ_gain ( pstval,iswrite );
			break;
		}
		case eFunc_SetInputEQQualityFactor - eFunc_SetProductName - 1:
		{
			set_in_EQ_quality_factor ( pstval,iswrite );
			break;
		}
		case eFunc_SetInputEQCtrl - eFunc_SetProductName - 1:
		{
			set_in_EQ_ctrl ( pstval,iswrite );
			break;
		}
		case eFunc_SetInputHowlingSuppressorCtrl - eFunc_SetProductName - 1:
		{
			set_in_howling_suppressor_ctrl ( pstval,iswrite );
			break;
		}
		case eFunc_SetInputHowlingSuppressorGrade - eFunc_SetProductName - 1:
		{
			set_in_howling_suppressor_grade ( pstval,iswrite );
			break;
		}
		case eFunc_SetInputHowlingSuppressorFreqShift - eFunc_SetProductName - 1:
		{
			set_in_howling_suppressor_freq_shift ( pstval,iswrite );
			break;
		}
		case eFunc_SetInputNoiseSuppressorGrade - eFunc_SetProductName - 1:
		{
			set_in_noise_suppressor_grade ( pstval,iswrite );
			break;
		}
		case eFunc_SetInputNoiseSuppressorThreshold - eFunc_SetProductName - 1:
		{
			set_in_noise_suppressor_threshold ( pstval,iswrite );
			break;
		}
		case eFunc_SetInputNoiseSuppressorRatio - eFunc_SetProductName - 1:
		{
			set_in_noise_suppressor_ratio ( pstval,iswrite );
			break;
		}
		case eFunc_SetInputNoiseSuppressorStartTime - eFunc_SetProductName - 1:
		{
			set_in_noise_suppressor_start_time ( pstval,iswrite );
			break;
		}
		case eFunc_SetInputNoiseSuppressorReleaseTime - eFunc_SetProductName - 1:
		{
			set_in_noise_suppressor_rel_time ( pstval,iswrite );
			break;
		}
		case eFunc_SetInputNoiseSuppressorCtrl - eFunc_SetProductName - 1:
		{
			set_in_noise_suppressor_ctrl ( pstval,iswrite );
			break;
		}
		case eFunc_SetInputEchoCancellerGrade - eFunc_SetProductName - 1:
		{
			set_in_echo_canceller_grade ( pstval,iswrite );
			break;
		}
		case eFunc_SetInputEchoCancellerCtrl - eFunc_SetProductName - 1:
		{
			set_in_echo_canceller_ctrl ( pstval,iswrite );
			break;
		}
		case eFunc_SetInputLfreqExciterGrade - eFunc_SetProductName - 1:
		{
			set_in_l_freq_exciter_grade ( pstval,iswrite );
			break;
		}
		case eFunc_SetInputHfreqExciterGrade - eFunc_SetProductName - 1:
		{
			set_in_h_freq_exciter_grade ( pstval,iswrite );
			break;
		}
		case eFunc_SetInputExciterCtrl - eFunc_SetProductName - 1:
		{
			set_in_exciter_ctrl ( pstval,iswrite );
			break;
		}
		case eFunc_SetInputCallInput - eFunc_SetProductName - 1:
		{
			set_in_call_input ( pstval,iswrite );
			break;
		}
		case eFunc_SetInputBackgroundInput - eFunc_SetProductName - 1:
		{
			set_in_background_input ( pstval,iswrite );
			break;
		}
		case eFunc_SetInputDuckingGain - eFunc_SetProductName - 1:
		{
			set_in_ducking_gain ( pstval,iswrite );
			break;
		}
		case eFunc_SetInputDuckingThreshold - eFunc_SetProductName - 1:
		{
			set_in_ducking_threshold ( pstval,iswrite );
			break;
		}
		case eFunc_SetInputDuckingDepth - eFunc_SetProductName - 1:
		{
			set_in_ducking_depth ( pstval,iswrite );
			break;
		}
		case eFunc_SetInputDuckingStartTime - eFunc_SetProductName - 1:
		{
			set_in_ducking_start_time ( pstval,iswrite );
			break;
		}
		case eFunc_SetInputDuckingHoldTime - eFunc_SetProductName - 1:
		{
			set_in_ducking_hold_time ( pstval,iswrite );
			break;
		}
		case eFunc_SetInputDuckingReleaseTime - eFunc_SetProductName - 1:
		{
			set_in_ducking_rel_time ( pstval,iswrite );
			break;
		}
		case eFunc_SetInputDuckingCtrl - eFunc_SetProductName - 1:
		{
			set_in_ducking_ctrl ( pstval,iswrite );
			break;
		}
		case eFunc_SetMatrixSwitching - eFunc_SetProductName - 1:
		{
			set_matrixswitch ( pstval,iswrite );
			break;
		}
		case eFunc_SetOutputDelayTime - eFunc_SetProductName - 1:
		{
			set_out_delay_time ( pstval,iswrite );
			break;
		}
		case eFunc_SetOutputDelayCtrl - eFunc_SetProductName - 1:
		{
			set_out_delay_ctrl ( pstval,iswrite );
			break;
		}
		case eFunc_SetUSBplayerCtrl - eFunc_SetProductName - 1:
		{
			set_usbplayer_ctrl ( pstval,iswrite );
			break;
		}
	}

	return emCmdSucess;
}

void defaultValue()
{
	stMachVal_t stmv;
	pststMachVal_t pstmv = &stmv;
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;

#if 1
	for ( u8 i= ( eFunc_SetAllAudioOutput - eFunc_SetProductName - 1 ); i <= ( eFunc_SetUSBplayerCtrl - eFunc_SetProductName - 1 ); i++ )
		//for ( u8 i= ( eFunc_SetInputEQQualityFactor - eFunc_SetProductName - 1 ); i == ( eFunc_SetInputEQQualityFactor - eFunc_SetProductName - 1 ); i++ )
	{
#endif
		//u8 i = eFunc_SetInputEchoCancellerGrade - eFunc_SetProductName - 1;
		memset ( pstmv,0,sizeof ( stMachVal_t ) );
		switch ( i )
		{
			case eFunc_SetAllAudioOutput - eFunc_SetProductName - 1:
			{

				continue;
			}
			case eFunc_SetInputSensitivity - eFunc_SetProductName - 1:
			{
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputSensitivity - eFunc_SetProductName - 1];

				for ( u8 n = 0; n < MAX_CH_LEN; n++ )
				{
					pstmv->ch |= 1 << cg_u8_IN_ChannelTable[n][1];
					pstmv->ch |= 1 << ( n + 0x10 );

					pstmv->param1[cg_u8_IN_ChannelTable[n][0]] = 0;
				}

				memcpy ( pstval, pstmv,sizeof ( stMachVal_t ) );
				set_all_data ( pstval, ( eCmdFun_t ) ( eFunc_SetInputSensitivity - eFunc_SetProductName - 1 ),0x1 );
				continue;
			}
			case eFunc_SetInputGain - eFunc_SetProductName - 1:
			{

				continue;
			}
			case eFunc_SetInputMute - eFunc_SetProductName - 1:
			{
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputMute - eFunc_SetProductName - 1];

				for ( u8 n = 0; n < MAX_CH_LEN; n++ )
				{
					pstmv->ch |= 1 << cg_u8_IN_ChannelTable[n][1];
					pstmv->ch |= 1 << ( n + 0x10 );

					pstmv->param1[cg_u8_IN_ChannelTable[n][0]] = 0;
				}

				memcpy ( pstval, pstmv,sizeof ( stMachVal_t ) );
				set_all_data ( pstval, ( eCmdFun_t ) ( eFunc_SetInputMute - eFunc_SetProductName - 1 ),0x1 );
				continue;
			}
			case eFunc_SetInputReversephase - eFunc_SetProductName - 1:
			{
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputReversephase - eFunc_SetProductName - 1];

				for ( u8 n = 0; n < MAX_CH_LEN; n++ )
				{
					pstmv->ch |= 1 << cg_u8_IN_ChannelTable[n][1];
					pstmv->ch |= 1 << ( n + 0x10 );

					pstmv->param1[cg_u8_IN_ChannelTable[n][0]] = 0;
				}

				memcpy ( pstval, pstmv,sizeof ( stMachVal_t ) );
				set_all_data ( pstval, ( eCmdFun_t ) ( eFunc_SetInputReversephase - eFunc_SetProductName - 1 ),0x1 );
				continue;
			}
			case eFunc_SetInputTestSignalCtrl - eFunc_SetProductName - 1:
			{
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputTestSignalCtrl - eFunc_SetProductName - 1];

				for ( u8 n = 0; n < MAX_CH_LEN; n++ )
				{
					pstmv->ch |= 1 << cg_u8_IN_ChannelTable[n][1];
					pstmv->ch |= 1 << ( n + 0x10 );

					pstmv->param1[cg_u8_IN_ChannelTable[n][0]] = 0;
				}

				memcpy ( pstval, pstmv,sizeof ( stMachVal_t ) );
				set_all_data ( pstval, ( eCmdFun_t ) ( eFunc_SetInputTestSignalCtrl - eFunc_SetProductName - 1 ),0x1 );
				continue;
			}
			case eFunc_SetInputTestSignalFreq - eFunc_SetProductName - 1:
			{

				continue;
			}
			case eFunc_SetInputTestSignalLevel - eFunc_SetProductName - 1:
			{

				continue;
			}
			case eFunc_SetInputCompressorCtrl - eFunc_SetProductName - 1:
			{
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputCompressorCtrl - eFunc_SetProductName - 1];

				for ( u8 n = 0; n < MAX_CH_LEN; n++ )
				{
					pstmv->ch |= 1 << cg_u8_IN_ChannelTable[n][1];
					pstmv->ch |= 1 << ( n + 0x10 );

					pstmv->param1[cg_u8_IN_ChannelTable[n][0]] = 0;
				}

				memcpy ( pstval, pstmv,sizeof ( stMachVal_t ) );
				set_all_data ( pstval, ( eCmdFun_t ) ( eFunc_SetInputCompressorCtrl - eFunc_SetProductName - 1 ),0x1 );
				continue;
			}
			case eFunc_SetInputCompressorGain - eFunc_SetProductName - 1:
			{
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputCompressorGain - eFunc_SetProductName - 1];

				for ( u8 n = 0; n < MAX_CH_LEN; n++ )
				{
					pstmv->ch |= 1 << cg_u8_IN_ChannelTable[n][1];
					pstmv->ch |= 1 << ( n + 0x10 );

					pstmv->param1[cg_u8_IN_ChannelTable[n][0]] = 0;
					pstmv->param2[cg_u8_IN_ChannelTable[n][0]] = 0;
				}

				memcpy ( pstval, pstmv,sizeof ( stMachVal_t ) );
				set_all_data ( pstval, ( eCmdFun_t ) ( eFunc_SetInputCompressorGain - eFunc_SetProductName - 1 ),0x1 );
				continue;
			}
			case eFunc_SetInputCompressorThreshold - eFunc_SetProductName - 1:
			{

				continue;
			}
			case eFunc_SetInputCompressorRatio - eFunc_SetProductName - 1:
			{
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputCompressorRatio - eFunc_SetProductName - 1];

				for ( u8 n = 0; n < MAX_CH_LEN; n++ )
				{
					pstmv->ch |= 1 << cg_u8_IN_ChannelTable[n][1];
					pstmv->ch |= 1 << ( n + 0x10 );

					pstmv->param1[cg_u8_IN_ChannelTable[n][0]] = 1;
					pstmv->param2[cg_u8_IN_ChannelTable[n][0]] = 0;
				}

				memcpy ( pstval, pstmv,sizeof ( stMachVal_t ) );
				set_all_data ( pstval, ( eCmdFun_t ) ( eFunc_SetInputCompressorRatio - eFunc_SetProductName - 1 ),0x1 );
				continue;
			}
			case eFunc_SetInputCompressorStartTime - eFunc_SetProductName - 1:
			{
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputCompressorStartTime - eFunc_SetProductName - 1];

				for ( u8 n = 0; n < MAX_CH_LEN; n++ )
				{
					pstmv->ch |= 1 << cg_u8_IN_ChannelTable[n][1];
					pstmv->ch |= 1 << ( n + 0x10 );

					pstmv->param1[cg_u8_IN_ChannelTable[n][0]] = 1;
				}

				memcpy ( pstval, pstmv,sizeof ( stMachVal_t ) );
				set_all_data ( pstval, ( eCmdFun_t ) ( eFunc_SetInputCompressorStartTime - eFunc_SetProductName - 1 ),0x1 );
				continue;
			}
			case eFunc_SetInputCompressorReleaseTime - eFunc_SetProductName - 1:
			{
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputCompressorReleaseTime - eFunc_SetProductName - 1];

				for ( u8 n = 0; n < MAX_CH_LEN; n++ )
				{
					pstmv->ch |= 1 << cg_u8_IN_ChannelTable[n][1];
					pstmv->ch |= 1 << ( n + 0x10 );

					pstmv->param1[cg_u8_IN_ChannelTable[n][0]] = 500;
				}

				memcpy ( pstval, pstmv,sizeof ( stMachVal_t ) );
				set_all_data ( pstval, ( eCmdFun_t ) ( eFunc_SetInputCompressorReleaseTime - eFunc_SetProductName - 1 ),0x1 );
				continue;
			}
			case eFunc_SetInputAutoGainCtrl - eFunc_SetProductName - 1:
			{
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputAutoGainCtrl - eFunc_SetProductName - 1];

				for ( u8 n = 0; n < MAX_CH_LEN; n++ )
				{
					pstmv->ch |= 1 << cg_u8_IN_ChannelTable[n][1];
					pstmv->ch |= 1 << ( n + 0x10 );

					pstmv->param1[cg_u8_IN_ChannelTable[n][0]] = 0;
				}

				memcpy ( pstval, pstmv,sizeof ( stMachVal_t ) );
				set_all_data ( pstval, ( eCmdFun_t ) ( eFunc_SetInputAutoGainCtrl - eFunc_SetProductName - 1 ),0x1 );
				continue;
			}
			case eFunc_SetInputAutoGainThreshold - eFunc_SetProductName - 1:
			{
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputAutoGainThreshold - eFunc_SetProductName - 1];

				for ( u8 n = 0; n < MAX_CH_LEN; n++ )
				{
					pstmv->ch |= 1 << cg_u8_IN_ChannelTable[n][1];
					pstmv->ch |= 1 << ( n + 0x10 );

					pstmv->param1[cg_u8_IN_ChannelTable[n][0]] = ( uint8_t )-48;
					pstmv->param2[cg_u8_IN_ChannelTable[n][0]] = 0;
				}

				memcpy ( pstval, pstmv,sizeof ( stMachVal_t ) );
				set_all_data ( pstval, ( eCmdFun_t ) ( eFunc_SetInputAutoGainThreshold - eFunc_SetProductName - 1 ),0x1 );
				continue;
			}
			case eFunc_SetInputAutoGainTargetThreshold - eFunc_SetProductName - 1:
			{
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputAutoGainTargetThreshold - eFunc_SetProductName - 1];

				for ( u8 n = 0; n < MAX_CH_LEN; n++ )
				{
					pstmv->ch |= 1 << cg_u8_IN_ChannelTable[n][1];
					pstmv->ch |= 1 << ( n + 0x10 );

					pstmv->param1[cg_u8_IN_ChannelTable[n][0]] = 0;
					pstmv->param2[cg_u8_IN_ChannelTable[n][0]] = 0;
				}

				memcpy ( pstval, pstmv,sizeof ( stMachVal_t ) );
				set_all_data ( pstval, ( eCmdFun_t ) ( eFunc_SetInputAutoGainTargetThreshold - eFunc_SetProductName - 1 ),0x1 );
				continue;
			}
			case eFunc_SetInputAutoGainRatio - eFunc_SetProductName - 1:
			{
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputAutoGainRatio - eFunc_SetProductName - 1];

				for ( u8 n = 0; n < MAX_CH_LEN; n++ )
				{
					pstmv->ch |= 1 << cg_u8_IN_ChannelTable[n][1];
					pstmv->ch |= 1 << ( n + 0x10 );

					pstmv->param1[cg_u8_IN_ChannelTable[n][0]] = 1;
					pstmv->param2[cg_u8_IN_ChannelTable[n][0]] = 0;
				}

				memcpy ( pstval, pstmv,sizeof ( stMachVal_t ) );
				set_all_data ( pstval, ( eCmdFun_t ) ( eFunc_SetInputAutoGainRatio - eFunc_SetProductName - 1 ),0x1 );
				continue;
			}
			case eFunc_SetInputAutoGainStartTime - eFunc_SetProductName - 1:
			{
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputAutoGainStartTime - eFunc_SetProductName - 1];

				for ( u8 n = 0; n < MAX_CH_LEN; n++ )
				{
					pstmv->ch |= 1 << cg_u8_IN_ChannelTable[n][1];
					pstmv->ch |= 1 << ( n + 0x10 );

					pstmv->param1[cg_u8_IN_ChannelTable[n][0]] = 1;
				}

				memcpy ( pstval, pstmv,sizeof ( stMachVal_t ) );
				set_all_data ( pstval, ( eCmdFun_t ) ( eFunc_SetInputAutoGainStartTime - eFunc_SetProductName - 1 ),0x1 );
				continue;
			}
			case eFunc_SetInputAutoGainReleaseTime - eFunc_SetProductName - 1:
			{
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputCompressorReleaseTime - eFunc_SetProductName - 1];

				for ( u8 n = 0; n < MAX_CH_LEN; n++ )
				{
					pstmv->ch |= 1 << cg_u8_IN_ChannelTable[n][1];
					pstmv->ch |= 1 << ( n + 0x10 );

					pstmv->param1[cg_u8_IN_ChannelTable[n][0]] = 500;
				}

				memcpy ( pstval, pstmv,sizeof ( stMachVal_t ) );
				set_all_data ( pstval, ( eCmdFun_t ) ( eFunc_SetInputCompressorReleaseTime - eFunc_SetProductName - 1 ),0x1 );
				continue;
			}
			case eFunc_SetInputEQType - eFunc_SetProductName - 1:
			{
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputEQType - eFunc_SetProductName - 1];
				u16* pval = pstPrjSaveVar->EQParamter[0];
				char* pstEQ =  ( char* ) pval;

				for ( u8 n = 0; n < MAX_CH_LEN; n++ )
				{
					pstmv->ch |= 1 << cg_u8_IN_ChannelTable[n][1];
					pstmv->ch |= 1 << ( n + 0x10 );

					for ( u8 m = 0; m < EQ; m++ )
					{
						pstEQ[(2 * EQ * n) + (m * 2)] = 0;

						//dbg_printf ( "*************************************************%s,%d\r\n",__FUNCTION__,__LINE__ );
						//hexdump ( pval, sizeof ( pstPrjSaveVar->EQParamter[0] ) );

            //dbg_printf("v_hexdump\r\n");
            //v_hexdump((unsigned char*)pval, sizeof ( pstPrjSaveVar->EQParamter[0]));
						break;
					}
				}

				memcpy ( pstval, pstmv,sizeof ( stMachVal_t ) );
				set_all_data ( pstval, ( eCmdFun_t ) ( eFunc_SetInputEQType - eFunc_SetProductName - 1 ),0x1 );
				continue;
			}
			case eFunc_SetInputEQGain - eFunc_SetProductName - 1:
			{
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputEQGain - eFunc_SetProductName - 1];
				u16* pval = pstPrjSaveVar->EQParamter[1];
				char* pstEQ =  ( char* ) pval;

				for ( u8 n = 0; n < MAX_CH_LEN; n++ )
				{
					pstmv->ch |= 1 << cg_u8_IN_ChannelTable[n][1];
					pstmv->ch |= 1 << ( n + 0x10 );

					for ( u8 m = 0; m < EQ; m++ )
					{
						pstEQ[(2 * EQ * n) + (m * 2)] = 0;
						pstEQ[(2 * EQ * n) + (m * 2 + 1)] = 0;
					}
				}

				memcpy ( pstval, pstmv,sizeof ( stMachVal_t ) );
				set_all_data ( pstval, ( eCmdFun_t ) ( eFunc_SetInputEQGain - eFunc_SetProductName - 1 ),0x1 );
				continue;
			}
			case eFunc_SetInputEQQualityFactor - eFunc_SetProductName - 1:
			{
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputEQQualityFactor - eFunc_SetProductName - 1];
				u16* pval = pstPrjSaveVar->EQParamter[2];
				char* pstEQ = ( char* ) pval;

				for ( u8 n = 0; n < MAX_CH_LEN; n++ )
				{
					pstmv->ch |= 1 << cg_u8_IN_ChannelTable[n][1];
					pstmv->ch |= 1 << ( n + 0x10 );

					for ( u8 m = 0; m < EQ; m++ )
					{
						pstEQ[(2 * EQ * n) + (m * 2)] = 0;
						pstEQ[(2 * EQ * n) + (m * 2 + 1)] = 71;

            //dbg_printf ("####################################### %s,%d,n = %d,m = %d\r\n",__FUNCTION__,__LINE__,n,m );
						//hexdump ( pval, sizeof ( pstPrjSaveVar->EQParamter[2] ) );

            //dbg_printf("v_hexdump\r\n");
            //v_hexdump((unsigned char*)pval, sizeof ( pstPrjSaveVar->EQParamter[0]));
					}
				}

				memcpy ( pstval, pstmv,sizeof ( stMachVal_t ) );
				set_all_data ( pstval, ( eCmdFun_t ) ( eFunc_SetInputEQQualityFactor - eFunc_SetProductName - 1 ),0x1 );
				continue;
			}
			case eFunc_SetInputEQCtrl - eFunc_SetProductName - 1:  /*EQ 这里因数据空间不够后面在考虑怎么存储*/
			{
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputEQCtrl - eFunc_SetProductName - 1];

				for ( u8 n = 0; n < MAX_CH_LEN; n++ )
				{
					pstmv->ch |= 1 << cg_u8_IN_ChannelTable[n][1];
					pstmv->ch |= 1 << ( n + 0x10 );

					for ( u8 m = 0; m < EQ; m++ )
					{
						pstmv->param1[n] |= ( 1 << m );     //关闭标志
						pstmv->param2[n] &= ~ ( 1 << m );   //打开标志
					}
				}

				memcpy ( pstval, pstmv,sizeof ( stMachVal_t ) );
				set_all_data ( pstval, ( eCmdFun_t ) ( eFunc_SetInputEQCtrl - eFunc_SetProductName - 1 ),0x1 );
				continue;
			}
			case eFunc_SetInputHowlingSuppressorCtrl - eFunc_SetProductName - 1:
			{
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputHowlingSuppressorCtrl - eFunc_SetProductName - 1];

				for ( u8 n = 0; n < MAX_CH_LEN; n++ )
				{
					pstmv->ch |= 1 << cg_u8_IN_ChannelTable[n][1];
					pstmv->ch |= 1 << ( n + 0x10 );

					pstmv->param1[cg_u8_IN_ChannelTable[n][0]] = 0;
				}

				memcpy ( pstval, pstmv,sizeof ( stMachVal_t ) );
				set_all_data ( pstval, ( eCmdFun_t ) ( eFunc_SetInputHowlingSuppressorCtrl - eFunc_SetProductName - 1 ),0x1 );
				continue;
			}
			case eFunc_SetInputHowlingSuppressorGrade - eFunc_SetProductName - 1:
			{
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputHowlingSuppressorGrade - eFunc_SetProductName - 1];

				pstmv->ch |= 1 << cg_u8_IN_ChannelTable[0][1];
				pstmv->ch |= 1 << 0x10;

				pstmv->param1[cg_u8_IN_ChannelTable[0][0]] = 1;
				pstmv->param2[cg_u8_IN_ChannelTable[0][0]] = emInLeft;

				pstmv->ch |= 1 << cg_u8_IN_ChannelTable[5][1];
				pstmv->ch |= 1 << 0x15;

				pstmv->param1[cg_u8_IN_ChannelTable[5][0]] = 1;
				pstmv->param2[cg_u8_IN_ChannelTable[5][0]] = emInRight;

				memcpy ( pstval, pstmv,sizeof ( stMachVal_t ) );
				set_all_data ( pstval, ( eCmdFun_t ) ( eFunc_SetInputHowlingSuppressorGrade - eFunc_SetProductName - 1 ),0x1 );
				continue;
			}
			case eFunc_SetInputHowlingSuppressorFreqShift - eFunc_SetProductName - 1:
			{
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputHowlingSuppressorFreqShift - eFunc_SetProductName - 1];

				pstmv->ch |= 1 << cg_u8_IN_ChannelTable[0][1];
				pstmv->ch |= 1 << 0x10;

				pstmv->param1[cg_u8_IN_ChannelTable[0][0]] = 0;
				pstmv->param2[cg_u8_IN_ChannelTable[0][0]] = emInLeft;

				pstmv->ch |= 1 << cg_u8_IN_ChannelTable[5][1];
				pstmv->ch |= 1 << 0x15;

				pstmv->param1[cg_u8_IN_ChannelTable[5][0]] = 0;
				pstmv->param2[cg_u8_IN_ChannelTable[5][0]] = emInRight;

				memcpy ( pstval, pstmv,sizeof ( stMachVal_t ) );
				set_all_data ( pstval, ( eCmdFun_t ) ( eFunc_SetInputHowlingSuppressorFreqShift - eFunc_SetProductName - 1 ),0x1 );
				continue;
			}
			case eFunc_SetInputNoiseSuppressorGrade - eFunc_SetProductName - 1:
			{
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputEchoCancellerGrade - eFunc_SetProductName - 1];

				pstmv->ch |= 1 << cg_u8_IN_ChannelTable[0][1];
				pstmv->ch |= 1 << 0x10;

				pstmv->param1[cg_u8_IN_ChannelTable[0][0]] = ( uint8_t )-48;
				pstmv->param2[cg_u8_IN_ChannelTable[0][0]] = 0;
				pstmv->param3[cg_u8_IN_ChannelTable[0][0]] = emInLeft;

				pstmv->ch |= 1 << cg_u8_IN_ChannelTable[5][1];
				pstmv->ch |= 1 << 0x15;

				pstmv->param1[cg_u8_IN_ChannelTable[5][0]] = ( uint8_t )-48;
				pstmv->param2[cg_u8_IN_ChannelTable[5][0]] = 0;
				pstmv->param3[cg_u8_IN_ChannelTable[5][0]] = emInRight;

				memcpy ( pstval, pstmv,sizeof ( stMachVal_t ) );
				set_all_data ( pstval, ( eCmdFun_t ) ( eFunc_SetInputEchoCancellerGrade - eFunc_SetProductName - 1 ),0x1 );
				continue;
			}
			case eFunc_SetInputNoiseSuppressorThreshold - eFunc_SetProductName - 1:
			{
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputEchoCancellerGrade - eFunc_SetProductName - 1];

				pstmv->ch |= 1 << cg_u8_IN_ChannelTable[0][1];
				pstmv->ch |= 1 << 0x10;

				pstmv->param1[cg_u8_IN_ChannelTable[0][0]] = 1;
				pstmv->param2[cg_u8_IN_ChannelTable[0][0]] = emInLeft;

				pstmv->ch |= 1 << cg_u8_IN_ChannelTable[5][1];
				pstmv->ch |= 1 << 0x15;

				pstmv->param1[cg_u8_IN_ChannelTable[5][0]] = 1;
				pstmv->param2[cg_u8_IN_ChannelTable[5][0]] = emInRight;

				memcpy ( pstval, pstmv,sizeof ( stMachVal_t ) );
				set_all_data ( pstval, ( eCmdFun_t ) ( eFunc_SetInputEchoCancellerGrade - eFunc_SetProductName - 1 ),0x1 );
				continue;
			}
			case eFunc_SetInputNoiseSuppressorRatio - eFunc_SetProductName - 1:
			{

				continue;
			}
			case eFunc_SetInputNoiseSuppressorStartTime - eFunc_SetProductName - 1:
			{

				continue;
			}
			case eFunc_SetInputNoiseSuppressorReleaseTime - eFunc_SetProductName - 1:
			{

				continue;
			}
			case eFunc_SetInputNoiseSuppressorCtrl - eFunc_SetProductName - 1:
			{

				continue;
			}
			case eFunc_SetInputEchoCancellerGrade - eFunc_SetProductName - 1:
			{
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputEchoCancellerGrade - eFunc_SetProductName - 1];

				pstmv->ch |= 1 << cg_u8_IN_ChannelTable[0][1];
				pstmv->ch |= 1 << 0x10;

				pstmv->param1[cg_u8_IN_ChannelTable[0][0]] = 1;
				pstmv->param2[cg_u8_IN_ChannelTable[0][0]] = emInLeft;

				pstmv->ch |= 1 << cg_u8_IN_ChannelTable[5][1];
				pstmv->ch |= 1 << 0x15;

				pstmv->param1[cg_u8_IN_ChannelTable[5][0]] = 1;
				pstmv->param2[cg_u8_IN_ChannelTable[5][0]] = emInRight;

				memcpy ( pstval, pstmv,sizeof ( stMachVal_t ) );
				set_all_data ( pstval, ( eCmdFun_t ) ( eFunc_SetInputEchoCancellerGrade - eFunc_SetProductName - 1 ),0x1 );
				continue;
			}
			case eFunc_SetInputEchoCancellerCtrl - eFunc_SetProductName - 1:
			{
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputEchoCancellerCtrl - eFunc_SetProductName - 1];

				for ( u8 n = 0; n < MAX_CH_LEN; n++ )
				{
					pstmv->ch |= 1 << cg_u8_IN_ChannelTable[n][1];
					pstmv->ch |= 1 << ( n + 0x10 );

					pstmv->param1[cg_u8_IN_ChannelTable[n][0]] = 0;
				}

				memcpy ( pstval, pstmv,sizeof ( stMachVal_t ) );
				set_all_data ( pstval, ( eCmdFun_t ) ( eFunc_SetInputEchoCancellerCtrl - eFunc_SetProductName - 1 ),0x1 );
				continue;
			}
			case eFunc_SetInputLfreqExciterGrade - eFunc_SetProductName - 1:
			{
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputLfreqExciterGrade - eFunc_SetProductName - 1];

				for ( u8 n = 0; n < MAX_CH_LEN; n++ )
				{
					pstmv->ch |= 1 << cg_u8_IN_ChannelTable[n][1];
					pstmv->ch |= 1 << ( n + 0x10 );

					pstmv->param1[cg_u8_IN_ChannelTable[n][0]] = 1;
				}

				memcpy ( pstval, pstmv,sizeof ( stMachVal_t ) );
				set_all_data ( pstval, ( eCmdFun_t ) ( eFunc_SetInputLfreqExciterGrade - eFunc_SetProductName - 1 ),0x1 );
				continue;
			}
			case eFunc_SetInputHfreqExciterGrade - eFunc_SetProductName - 1:
			{
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputHfreqExciterGrade - eFunc_SetProductName - 1];

				for ( u8 n = 0; n < MAX_CH_LEN; n++ )
				{
					pstmv->ch |= 1 << cg_u8_IN_ChannelTable[n][1];
					pstmv->ch |= 1 << ( n + 0x10 );

					pstmv->param1[cg_u8_IN_ChannelTable[n][0]] = 1;
				}

				memcpy ( pstval, pstmv,sizeof ( stMachVal_t ) );
				set_all_data ( pstval, ( eCmdFun_t ) ( eFunc_SetInputHfreqExciterGrade - eFunc_SetProductName - 1 ),0x1 );
				continue;
			}
			case eFunc_SetInputExciterCtrl - eFunc_SetProductName - 1:
			{
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputExciterCtrl - eFunc_SetProductName - 1];

				for ( u8 n = 0; n < MAX_CH_LEN; n++ )
				{
					pstmv->ch |= 1 << cg_u8_IN_ChannelTable[n][1];
					pstmv->ch |= 1 << ( n + 0x10 );

					pstmv->param1[cg_u8_IN_ChannelTable[n][0]] = 0;
				}

				memcpy ( pstval, pstmv,sizeof ( stMachVal_t ) );
				set_all_data ( pstval, ( eCmdFun_t ) ( eFunc_SetInputExciterCtrl - eFunc_SetProductName - 1 ),0x1 );
				continue;
			}
			case eFunc_SetInputCallInput - eFunc_SetProductName - 1:
			{
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputCallInput - eFunc_SetProductName - 1];

				for ( u8 n = 0; n < MAX_CH_LEN; n++ )
				{
					pstmv->ch |= 1 << cg_u8_IN_ChannelTable[n][1];
					pstmv->ch |= 1 << ( n + 0x10 );

					pstmv->param1[cg_u8_IN_ChannelTable[n][0]] = 0;
				}

				memcpy ( pstval, pstmv,sizeof ( stMachVal_t ) );
				set_all_data ( pstval, ( eCmdFun_t ) ( eFunc_SetInputCallInput - eFunc_SetProductName - 1 ),0x1 );
				continue;
			}
			case eFunc_SetInputBackgroundInput - eFunc_SetProductName - 1:
			{
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputBackgroundInput - eFunc_SetProductName - 1];

				for ( u8 n = 0; n < MAX_CH_LEN; n++ )
				{
					pstmv->ch |= 1 << cg_u8_IN_ChannelTable[n][1];
					pstmv->ch |= 1 << ( n + 0x10 );

					pstmv->param1[cg_u8_IN_ChannelTable[n][0]] = 0;
				}

				memcpy ( pstval, pstmv,sizeof ( stMachVal_t ) );
				set_all_data ( pstval, ( eCmdFun_t ) ( eFunc_SetInputBackgroundInput - eFunc_SetProductName - 1 ),0x1 );
				continue;
			}
			case eFunc_SetInputDuckingGain - eFunc_SetProductName - 1:
			{
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputDuckingGain - eFunc_SetProductName - 1];

				for ( u8 n = 0; n < MAX_CH_LEN; n++ )
				{
					pstmv->ch |= 1 << cg_u8_IN_ChannelTable[n][1];
					pstmv->ch |= 1 << ( n + 0x10 );

					pstmv->param1[cg_u8_IN_ChannelTable[n][0]] = 0;
				}

				memcpy ( pstval, pstmv,sizeof ( stMachVal_t ) );
				set_all_data ( pstval, ( eCmdFun_t ) ( eFunc_SetInputDuckingGain - eFunc_SetProductName - 1 ),0x1 );
				continue;
			}
			case eFunc_SetInputDuckingThreshold - eFunc_SetProductName - 1:
			{
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputDuckingDepth - eFunc_SetProductName - 1];

				pstmv->ch |= 1 << cg_u8_IN_ChannelTable[0][1];
				pstmv->ch |= 1 << 0x10;

				pstmv->param1[cg_u8_IN_ChannelTable[0][0]] = 20;
				pstmv->param2[cg_u8_IN_ChannelTable[0][0]] = 0;
				pstmv->param3[cg_u8_IN_ChannelTable[0][0]] = emInLeft;


				pstmv->ch |= 1 << cg_u8_IN_ChannelTable[5][1];
				pstmv->ch |= 1 << 0x15;

				pstmv->param1[cg_u8_IN_ChannelTable[5][0]] = 20;
				pstmv->param2[cg_u8_IN_ChannelTable[5][0]] = 0;
				pstmv->param3[cg_u8_IN_ChannelTable[5][0]] = emInRight;

				memcpy ( pstval, pstmv,sizeof ( stMachVal_t ) );
				set_all_data ( pstval, ( eCmdFun_t ) ( eFunc_SetInputDuckingDepth - eFunc_SetProductName - 1 ),0x1 );
				continue;
			}
			case eFunc_SetInputDuckingDepth - eFunc_SetProductName - 1:
			{
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputDuckingDepth - eFunc_SetProductName - 1];

				pstmv->ch |= 1 << cg_u8_IN_ChannelTable[0][1];
				pstmv->ch |= 1 << 0x10;

				pstmv->param1[cg_u8_IN_ChannelTable[0][0]] = 96;
				pstmv->param2[cg_u8_IN_ChannelTable[0][0]] = 0;
				pstmv->param3[cg_u8_IN_ChannelTable[0][0]] = emInLeft;


				pstmv->ch |= 1 << cg_u8_IN_ChannelTable[5][1];
				pstmv->ch |= 1 << 0x15;

				pstmv->param1[cg_u8_IN_ChannelTable[5][0]] = 96;
				pstmv->param2[cg_u8_IN_ChannelTable[5][0]] = 0;
				pstmv->param3[cg_u8_IN_ChannelTable[5][0]] = emInRight;

				memcpy ( pstval, pstmv,sizeof ( stMachVal_t ) );
				set_all_data ( pstval, ( eCmdFun_t ) ( eFunc_SetInputDuckingDepth - eFunc_SetProductName - 1 ),0x1 );
				continue;
			}
			case eFunc_SetInputDuckingStartTime - eFunc_SetProductName - 1:
			{
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputDuckingStartTime - eFunc_SetProductName - 1];

				pstmv->ch |= 1 << cg_u8_IN_ChannelTable[0][1];
				pstmv->ch |= 1 << 0x10;

				pstmv->param1[cg_u8_IN_ChannelTable[0][0]] = 10000;
				pstmv->param2[cg_u8_IN_ChannelTable[0][0]] = emInLeft;

				pstmv->ch |= 1 << cg_u8_IN_ChannelTable[5][1];
				pstmv->ch |= 1 << 0x15;

				pstmv->param1[cg_u8_IN_ChannelTable[5][0]] = 10000;
				pstmv->param2[cg_u8_IN_ChannelTable[5][0]] = emInRight;

				memcpy ( pstval, pstmv,sizeof ( stMachVal_t ) );
				set_all_data ( pstval, ( eCmdFun_t ) ( eFunc_SetInputDuckingStartTime - eFunc_SetProductName - 1 ),0x1 );
				continue;
			}
			case eFunc_SetInputDuckingHoldTime - eFunc_SetProductName - 1:
			{
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputDuckingHoldTime - eFunc_SetProductName - 1];

				pstmv->ch |= 1 << cg_u8_IN_ChannelTable[0][1];
				pstmv->ch |= 1 << 0x10;

				pstmv->param1[cg_u8_IN_ChannelTable[0][0]] = 500;
				pstmv->param2[cg_u8_IN_ChannelTable[0][0]] = emInLeft;

				pstmv->ch |= 1 << cg_u8_IN_ChannelTable[5][1];
				pstmv->ch |= 1 << 0x15;

				pstmv->param1[cg_u8_IN_ChannelTable[5][0]] = 500;
				pstmv->param2[cg_u8_IN_ChannelTable[5][0]] = emInRight;

				memcpy ( pstval, pstmv,sizeof ( stMachVal_t ) );
				set_all_data ( pstval, ( eCmdFun_t ) ( eFunc_SetInputDuckingHoldTime - eFunc_SetProductName - 1 ),0x1 );
				continue;
			}
			case eFunc_SetInputDuckingReleaseTime - eFunc_SetProductName - 1:
			{
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputDuckingReleaseTime - eFunc_SetProductName - 1];

				pstmv->ch |= 1 << cg_u8_IN_ChannelTable[0][1];
				pstmv->ch |= 1 << 0x10;

				pstmv->param1[cg_u8_IN_ChannelTable[0][0]] = 30000;
				pstmv->param2[cg_u8_IN_ChannelTable[0][0]] = emInLeft;

				pstmv->ch |= 1 << cg_u8_IN_ChannelTable[5][1];
				pstmv->ch |= 1 << 0x15;

				pstmv->param1[cg_u8_IN_ChannelTable[5][0]] = 30000;
				pstmv->param2[cg_u8_IN_ChannelTable[5][0]] = emInRight;

				memcpy ( pstval, pstmv,sizeof ( stMachVal_t ) );
				set_all_data ( pstval, ( eCmdFun_t ) ( eFunc_SetInputDuckingReleaseTime - eFunc_SetProductName - 1 ),0x1 );
				continue;
			}
			case eFunc_SetInputDuckingCtrl - eFunc_SetProductName - 1:
			{
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputDuckingCtrl - eFunc_SetProductName - 1];

				pstmv->ch |= 1 << cg_u8_IN_ChannelTable[0][1];
				pstmv->ch |= 1 << 0x10;

				pstmv->param1[cg_u8_IN_ChannelTable[0][0]] = 0;
				pstmv->param2[cg_u8_IN_ChannelTable[0][0]] = emInLeft;

				pstmv->ch |= 1 << cg_u8_IN_ChannelTable[5][1];
				pstmv->ch |= 1 << 0x15;

				pstmv->param1[cg_u8_IN_ChannelTable[5][0]] = 0;
				pstmv->param2[cg_u8_IN_ChannelTable[5][0]] = emInRight;

				memcpy ( pstval, pstmv,sizeof ( stMachVal_t ) );
				set_all_data ( pstval, ( eCmdFun_t ) ( eFunc_SetInputDuckingCtrl - eFunc_SetProductName - 1 ),0x1 );
				continue;
			}
			case eFunc_SetMatrixSwitching - eFunc_SetProductName - 1:
			{
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetMatrixSwitching - eFunc_SetProductName - 1];

				for ( u8 n = 0; n < MAX_CH_LEN; n++ )
				{
					for ( u8 m = 0; m < MAX_CH_LEN; m++ )
					{
						pstmv->ch |= ( 1 << n );
						pstmv->ch |= ( 1 << ( 0x10 + m ) );

						if ( n == m )
						{
							pstmv->param1[ n ] |=   ( 1 << m );
							pstmv->param2[ n ] &= ~ ( 1 << m );
						}
						else
						{
							pstmv->param1[ n ] &= ~ ( 1 << m );
							pstmv->param2[ n ] |=   ( 1 << m );
						}
					}
				}

				memcpy ( pstval, pstmv,sizeof ( stMachVal_t ) );
				set_all_data ( pstval, ( eCmdFun_t ) ( eFunc_SetMatrixSwitching - eFunc_SetProductName - 1 ),0x1 );
				continue;
			}
			case eFunc_SetOutputDelayTime - eFunc_SetProductName - 1:
			{
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetOutputDelayTime - eFunc_SetProductName - 1];

				for ( u8 n = 0; n < MAX_CH_LEN; n++ )
				{
					pstmv->ch |= 1 << cg_u8_OUT_ChannelTable[n][1];
					pstmv->ch |= 1 << ( n + 0x10 );

					pstmv->param1[cg_u8_OUT_ChannelTable[n][0]] = 1;
					pstmv->param2[cg_u8_OUT_ChannelTable[n][0]] = 0;
				}

				memcpy ( pstval, pstmv,sizeof ( stMachVal_t ) );
				set_all_data ( pstval, ( eCmdFun_t ) ( eFunc_SetOutputDelayTime - eFunc_SetProductName - 1 ),0x1 );
				continue;
			}
			case eFunc_SetOutputDelayCtrl - eFunc_SetProductName - 1:
			{
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetOutputDelayCtrl - eFunc_SetProductName - 1];

				for ( u8 n = 0; n < MAX_CH_LEN; n++ )
				{
					pstmv->ch |= 1 << cg_u8_OUT_ChannelTable[n][1];
					pstmv->ch |= 1 << ( n + 0x10 );

					pstmv->param1[cg_u8_OUT_ChannelTable[n][0]] = 0;
				}

				memcpy ( pstval, pstmv,sizeof ( stMachVal_t ) );
				set_all_data ( pstval, ( eCmdFun_t ) ( eFunc_SetOutputDelayCtrl - eFunc_SetProductName - 1 ),0x1 );
				continue;
			}
			case eFunc_SetUSBplayerCtrl - eFunc_SetProductName - 1:
			{
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetUSBplayerCtrl - eFunc_SetProductName - 1];

				pstmv->param1[0] = 4;
				pstmv->param2[0] = 0;

				memcpy ( pstval, pstmv,sizeof ( stMachVal_t ) );
				set_all_data ( pstval, ( eCmdFun_t ) ( eFunc_SetUSBplayerCtrl - eFunc_SetProductName - 1 ),0x1 );
				continue;
			}
		}
#if 1
	}
#endif
}

//char gbuffer[100] = {1};
void xx ( pstUartCom_t pCommVar, uint8_t cmdnum, uint8_t index, char* name )
{
#if 1
	//emCmdFuncStaType l_state = emCmdNone;
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputGain - eFunc_SetProductName - 1];

	char buffer[127] = {0};
	char value[32] = {0};
	char* p = buffer;
	char* token = strtok ( l_pCmd,"," );

	sprintf ( p,"%s,",name );
	p += strlen ( name ) + 1;

	if (!strncmp ( l_pCmd,"-1",2 ) )
	{
		for ( u8 i = 0; pstval->ch >> i; i++ )
		{
			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d",i );
			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;

			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d.%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[i][0]],pstval->param2[cg_u8_IN_ChannelTable[i][0]] );
			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;

			//memset(value,0,sizeof(value));
			//sprintf(value,"%d",pstval->param2[cg_u8_IN_ChannelTable[i][0]]);
			//sprintf(p,"%s,",value);
			//p += strlen(value) + 1;
		}
	}
	else
	{
		if ( token != NULL )
		{
			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d",atoi ( token ) );
			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;

			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d.%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[atoi ( token )][0]],pstval->param2[cg_u8_IN_ChannelTable[atoi ( token )][0]] );
			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;

			//memset(value,0,sizeof(value));
			//sprintf(value,"%d",pstval->param2[cg_u8_IN_ChannelTable[atoi(token)][0]]);
			//sprintf(p,"%s,",value);
			//p += strlen(value) + 1;

			token = strtok ( NULL,"," );
		}
	}

	sprintf ( p,"%s","EOF" );

	//v_hexdump ( buffer, 127 );
	//dbg_printf ( "name:%s,index:%d \r\n",name,index );
#endif
}

//GET
#define BUFLEN 160
int Uart3_printf ( const char* fmt, ... )
{

}

static emCmdFuncStaType mapp_CmdfuncGetProductName ( pstUartCom_t pCommVar,u8 cmdnum )
{

	return emCmdSucess;
}

void get_all_audio_output ( pststMachVal_t pstval )
{
	char buffer[BUFLEN] = {0};
	char value[32] = {0};
	char* p = buffer;


	sprintf ( p,"%s,","allAudioOutput" );
	p += strlen ( p );

	memset ( value,0,sizeof ( value ) );
	sprintf ( value,"%d", ( int8_t ) pstval->param1[0] );

	sprintf ( p,"%s,",value );
	p += strlen ( value ) + 1;

	sprintf ( p,"%s","EOF" );

	Uart3_printf ( "%s\r\n",buffer );
	dbg_printf ( "%s\r\n",buffer );

	//将数据发送给uart3
	//v_hexdump ( buffer, BUFLEN );
}

//{allAudioOutput:0}
static emCmdFuncStaType mapp_CmdfuncGetAllAudioOutput ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	//emCmdFuncStaType l_state = emCmdNone;
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetAllAudioOutput - eFunc_SetProductName - 1];

	char* token = strtok ( l_pCmd,"," );

	get_all_audio_output ( pstval );

	return emCmdSucess;
}

void get_in_sensitivity ( pststMachVal_t pstval )
{
	char buffer[BUFLEN] = {0};
	char value[32] = {0};
	char* p = buffer;

	sprintf ( p,"%s,","InSensitivity" );
	p += strlen ( p );

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d",i );

			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;

			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[i][0]] );

			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;
		}
	}

	sprintf ( p,"%s","EOF" );

	Uart3_printf ( "%s\r\n",buffer );
	dbg_printf ( "%s\r\n",buffer );
}

//{"InSensitivity":{"0":{"val1":6},"1":{"val1":12},...}}
static emCmdFuncStaType mapp_CmdfuncGetInputSensitivity ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	//emCmdFuncStaType l_state = emCmdNone;
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputSensitivity - eFunc_SetProductName - 1];

	char* token = strtok ( l_pCmd,"," );

	if (!strncmp ( l_pCmd,"-1",2 ) )
	{
		//for ( u8 i = 0; (pstval->ch >> i) & 0x1; i++ )
		get_in_sensitivity ( pstval );
	}
	else
	{
		if ( token != NULL )
		{
			char buffer[BUFLEN] = {0};
			char value[32] = {0};
			char* p = buffer;

			sprintf ( p,"%s,","InSensitivity" );
			p += strlen ( p );

			if ( ( pstval->ch >> ( atoi ( token ) + 0x10 ) ) & 0x1 )
			{
				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d",atoi ( token ) );

				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;

				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[atoi ( token )][0]] );

				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;
			}

			sprintf ( p,"%s","EOF" );

			Uart3_printf ( "%s\r\n",buffer );
			dbg_printf ( "%s\r\n",buffer );

			//v_hexdump ( buffer, BUFLEN );

			token = strtok ( NULL,"," );
		}
	}

	return emCmdSucess;
}

void get_in_gain ( pststMachVal_t pstval )
{
	char buffer[BUFLEN] = {0};
	char value[32] = {0};
	char* p = buffer;

	sprintf ( p,"%s,","InGain" );
	p += strlen ( p );

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d",i );

			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;

			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d.%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[i][0]],pstval->param2[cg_u8_IN_ChannelTable[i][0]] );

			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;
		}
	}

	sprintf ( p,"%s","EOF" );

	Uart3_printf ( "%s\r\n",buffer );
	dbg_printf ( "%s\r\n",buffer );
}

/**
*(get,InputGain,x)
*x=-1 表示获取所有通道数据
*x=0~8表示获取对应通道数据
*/
static emCmdFuncStaType mapp_CmdfuncGetInputGain ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	//emCmdFuncStaType l_state = emCmdNone;
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputGain - eFunc_SetProductName - 1];

	char* token = strtok ( l_pCmd,"," );

	if (!strncmp ( l_pCmd,"-1",2 ) )
	{
		//for ( u8 i = 0; (pstval->ch >> i) & 0x1; i++ )
		get_in_gain ( pstval );
	}
	else
	{
		if ( token != NULL )
		{
			char buffer[BUFLEN] = {0};
			char value[32] = {0};
			char* p = buffer;

			sprintf ( p,"%s,","InGain" );
			p += strlen ( p );

			if ( ( pstval->ch >> ( atoi ( token ) + 0x10 ) ) & 0x1 )
			{
				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d",atoi ( token ) );

				sprintf ( p,"%s,",value );
				p += strlen ( value );

				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d.%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[atoi ( token )][0]],pstval->param2[cg_u8_IN_ChannelTable[atoi ( token )][0]] );

				sprintf ( p,"%s,",value );
				p += strlen ( value );
			}

			sprintf ( p,"%s","EOF" );

			Uart3_printf ( "%s\r\n",buffer );
			dbg_printf ( "%s\r\n",buffer );

			//将数据发送给uart3
			//v_hexdump ( buffer, BUFLEN );

			token = strtok ( NULL,"," );
		}
	}

	return emCmdSucess;
}

void get_in_mute ( pststMachVal_t pstval )
{
	char buffer[BUFLEN] = {0};
	char value[32] = {0};
	char* p = buffer;

	sprintf ( p,"%s,","InMute" );
	p += strlen ( p );

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d",i );

			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;

			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[i][0]] );
			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;
		}
	}

	sprintf ( p,"%s","EOF" );

	Uart3_printf ( "%s\r\n",buffer );
	dbg_printf ( "%s\r\n",buffer );

	//将数据发送给uart3
	//v_hexdump ( buffer, BUFLEN );
}

static emCmdFuncStaType mapp_CmdfuncGetInputMute ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	//emCmdFuncStaType l_state = emCmdNone;
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputMute - eFunc_SetProductName - 1];

	char* token = strtok ( l_pCmd,"," );

	if (!strncmp ( l_pCmd,"-1",2 ) )
	{
		//for ( u8 i = 0; (pstval->ch >> i) & 0x1; i++ )
		get_in_mute ( pstval );
	}
	else
	{
		char buffer[BUFLEN] = {0};
		char value[32] = {0};
		char* p = buffer;

		sprintf ( p,"%s,","InMute" );
		p += strlen ( p );

		if ( token != NULL )
		{
			if ( ( pstval->ch >> ( atoi ( token ) + 0x10 ) ) & 0x1 )
			{
				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d",atoi ( token ) );

				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;

				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[atoi ( token )][0]] );
				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;
			}

			sprintf ( p,"%s","EOF" );

			Uart3_printf ( "%s\r\n",buffer );
			dbg_printf ( "%s\r\n",buffer );

			//将数据发送给uart3
			//v_hexdump ( buffer, BUFLEN );

			token = strtok ( NULL,"," );
		}
	}

	return emCmdSucess;
}

void get_in_reversephase ( pststMachVal_t pstval )
{
	char buffer[BUFLEN] = {0};
	char value[32] = {0};
	char* p = buffer;

	sprintf ( p,"%s,","InReversephase" );
	p += strlen ( p );

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d",i );

			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;

			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[i][0]] );
			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;
		}
	}

	sprintf ( p,"%s","EOF" );

	Uart3_printf ( "%s\r\n",buffer );
	dbg_printf ( "%s\r\n",buffer );

	//将数据发送给uart3
	//v_hexdump ( buffer, BUFLEN );
}

static emCmdFuncStaType mapp_CmdfuncGetInputReversephase ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	//emCmdFuncStaType l_state = emCmdNone;
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputReversephase - eFunc_SetProductName - 1];

	char* token = strtok ( l_pCmd,"," );

	if (!strncmp ( l_pCmd,"-1",2 ) )
	{
		//for ( u8 i = 0; (pstval->ch >> i) & 0x1; i++ )
		get_in_reversephase ( pstval );
	}
	else
	{
		if ( token != NULL )
		{
			char buffer[BUFLEN] = {0};
			char value[32] = {0};
			char* p = buffer;

			sprintf ( p,"%s,","InReversephase" );
			p += strlen ( p );

			if ( ( pstval->ch >> ( atoi ( token ) + 0x10 ) ) & 0x1 )
			{
				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d",atoi ( token ) );

				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;

				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[atoi ( token )][0]] );
				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;
			}

			sprintf ( p,"%s","EOF" );

			Uart3_printf ( "%s\r\n",buffer );
			dbg_printf ( "%s\r\n",buffer );

			//将数据发送给uart3
			//v_hexdump ( buffer, BUFLEN );

			token = strtok ( NULL,"," );
		}
	}

	return emCmdSucess;
}

void get_in_test_signal_ctrl ( pststMachVal_t pstval )
{
	char buffer[BUFLEN] = {0};
	char value[32] = {0};
	char* p = buffer;

	sprintf ( p,"%s,","InTestSignalCtrl" );
	p += strlen ( p );

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d",i );

			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;

			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[i][0]] );
			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;
		}
	}

	sprintf ( p,"%s","EOF" );

	Uart3_printf ( "%s\r\n",buffer );
	dbg_printf ( "%s\r\n",buffer );

	//将数据发送给uart3
	//v_hexdump ( buffer, BUFLEN );
}

static emCmdFuncStaType mapp_CmdfuncGetInputTestSignalCtrl ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	//emCmdFuncStaType l_state = emCmdNone;
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputTestSignalCtrl - eFunc_SetProductName - 1];

	char* token = strtok ( l_pCmd,"," );

	if (!strncmp ( l_pCmd,"-1",2 ) )
	{
		//for ( u8 i = 0; (pstval->ch >> i) & 0x1; i++ )
		get_in_test_signal_ctrl ( pstval );
	}
	else
	{
		if ( token != NULL )
		{
			char buffer[BUFLEN] = {0};
			char value[32] = {0};
			char* p = buffer;

			sprintf ( p,"%s,","InTestSignalCtrl" );
			p += strlen ( p );

			if ( ( pstval->ch >> ( atoi ( token ) + 0x10 ) ) & 0x1 )
			{
				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d",atoi ( token ) );

				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;

				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[atoi ( token )][0]] );
				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;
			}

			sprintf ( p,"%s","EOF" );

			Uart3_printf ( "%s\r\n",buffer );
			dbg_printf ( "%s\r\n",buffer );

			//将数据发送给uart3
			//v_hexdump ( buffer, BUFLEN );

			token = strtok ( NULL,"," );
		}
	}



	return emCmdSucess;
}

void get_in_test_signal_freq ( pststMachVal_t pstval )
{
	char buffer[BUFLEN] = {0};
	char value[32] = {0};
	char* p = buffer;

	//memset(buffer,0,strlen(buffer));
	sprintf ( p,"%s,","InTestSignalFreq" );
	p += strlen ( p );

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d",i );

			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;

			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d", ( int16_t ) pstval->param1[cg_u8_IN_ChannelTable[i][0]] );
			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;
		}
	}

	sprintf ( p,"%s","EOF" );

	Uart3_printf ( "%s\r\n",buffer );
	dbg_printf ( "%s\r\n",buffer );

	//将数据发送给uart3
	//v_hexdump ( buffer, BUFLEN );
}

static emCmdFuncStaType mapp_CmdfuncGetInputTestSignalFreq ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	//emCmdFuncStaType l_state = emCmdNone;
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputTestSignalFreq - eFunc_SetProductName - 1];

	char* token = strtok ( l_pCmd,"," );

	if (!strncmp ( l_pCmd,"-1",2 ) )
	{
		//for ( u8 i = 0; (pstval->ch >> i) & 0x1; i++ )
		get_in_test_signal_freq ( pstval );
	}
	else
	{
		if ( token != NULL )
		{
			char buffer[BUFLEN] = {0};
			char value[32] = {0};
			char* p = buffer;

			//memset(buffer,0,strlen(buffer));
			sprintf ( p,"%s,","InTestSignalFreq" );
			p += strlen ( p );

			if ( ( pstval->ch >> ( atoi ( token ) + 0x10 ) ) & 0x1 )
			{
				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d",atoi ( token ) );

				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;

				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d", ( int16_t ) pstval->param1[cg_u8_IN_ChannelTable[atoi ( token )][0]] );
				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;
			}

			sprintf ( p,"%s","EOF" );

			Uart3_printf ( "%s\r\n",buffer );
			dbg_printf ( "%s\r\n",buffer );

			//将数据发送给uart3
			//v_hexdump ( buffer, BUFLEN );

			token = strtok ( NULL,"," );
		}
	}

	return emCmdSucess;
}

void get_in_test_signal_level ( pststMachVal_t pstval )
{
	char buffer[BUFLEN] = {0};
	char value[32] = {0};
	char* p = buffer;

	sprintf ( p,"%s,","InTestSignalLevel" );
	p += strlen ( p );

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d",i );

			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;

			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d.%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[i][0]],pstval->param2[cg_u8_IN_ChannelTable[i][0]] );
			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;
		}
	}

	sprintf ( p,"%s","EOF" );

	Uart3_printf ( "%s\r\n",buffer );
	dbg_printf ( "%s\r\n",buffer );

	//将数据发送给uart3
	//v_hexdump ( buffer, BUFLEN );
}

static emCmdFuncStaType mapp_CmdfuncGetInputTestSignalLevel ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	//emCmdFuncStaType l_state = emCmdNone;
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputTestSignalLevel - eFunc_SetProductName - 1];

	char* token = strtok ( l_pCmd,"," );

	if (!strncmp ( l_pCmd,"-1",2 ) )
	{
		get_in_test_signal_level ( pstval );
	}
	else
	{
		if ( token != NULL )
		{
			char buffer[BUFLEN] = {0};
			char value[32] = {0};
			char* p = buffer;

			sprintf ( p,"%s,","InTestSignalLevel" );
			p += strlen ( p );

			if ( ( pstval->ch >> ( atoi ( token ) + 0x10 ) ) & 0x1 )
			{
				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d",atoi ( token ) );

				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;

				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d.%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[atoi ( token )][0]],pstval->param2[cg_u8_IN_ChannelTable[atoi ( token )][0]] );
				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;
			}

			sprintf ( p,"%s","EOF" );

			Uart3_printf ( "%s\r\n",buffer );
			dbg_printf ( "%s\r\n",buffer );

			//将数据发送给uart3
			//v_hexdump ( buffer, BUFLEN );

			token = strtok ( NULL,"," );
		}
	}

	return emCmdSucess;
}

void get_in_compressor_ctrl ( pststMachVal_t pstval )
{
	char buffer[BUFLEN] = {0};
	char value[32] = {0};
	char* p = buffer;

	sprintf ( p,"%s,","InCompressorCtrl" );
	p += strlen ( p );

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d",i );

			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;

			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[i][0]] );
			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;
		}
	}

	sprintf ( p,"%s","EOF" );

	Uart3_printf ( "%s\r\n",buffer );
	dbg_printf ( "%s\r\n",buffer );

	//将数据发送给uart3
	//v_hexdump ( buffer, BUFLEN );
}

static emCmdFuncStaType mapp_CmdfuncGetInputCompressorCtrl ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	//emCmdFuncStaType l_state = emCmdNone;
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputCompressorCtrl - eFunc_SetProductName - 1];

	char* token = strtok ( l_pCmd,"," );

	if (!strncmp ( l_pCmd,"-1",2 ) )
	{
		get_in_compressor_ctrl ( pstval );
	}
	else
	{
		if ( token != NULL )
		{
			char buffer[BUFLEN] = {0};
			char value[32] = {0};
			char* p = buffer;

			sprintf ( p,"%s,","InCompressorCtrl" );
			p += strlen ( p );

			if ( ( pstval->ch >> ( atoi ( token ) + 0x10 ) ) & 0x1 )
			{
				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d",atoi ( token ) );

				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;

				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[atoi ( token )][0]] );
				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;
			}

			sprintf ( p,"%s","EOF" );

			Uart3_printf ( "%s\r\n",buffer );
			dbg_printf ( "%s\r\n",buffer );

			//将数据发送给uart3
			//v_hexdump ( buffer, BUFLEN );

			token = strtok ( NULL,"," );
		}
	}

	return emCmdSucess;
}

void get_in_compressor_gain ( pststMachVal_t pstval )
{
	char buffer[BUFLEN] = {0};
	char value[32] = {0};
	char* p = buffer;

	sprintf ( p,"%s,","InCompressorGain" );
	p += strlen ( p );

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d",i );

			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;

			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d.%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[i][0]],pstval->param2[cg_u8_IN_ChannelTable[i][0]] );
			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;
		}
	}

	sprintf ( p,"%s","EOF" );

	Uart3_printf ( "%s\r\n",buffer );
	dbg_printf ( "%s\r\n",buffer );

	//将数据发送给uart3
	//v_hexdump ( buffer, BUFLEN );
}

static emCmdFuncStaType mapp_CmdfuncGetInputCompressorGain ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	//emCmdFuncStaType l_state = emCmdNone;
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputCompressorGain - eFunc_SetProductName - 1];

	char* token = strtok ( l_pCmd,"," );

	if (!strncmp ( l_pCmd,"-1",2 ) )
	{
		get_in_compressor_gain ( pstval );
	}
	else
	{
		if ( token != NULL )
		{
			char buffer[BUFLEN] = {0};
			char value[32] = {0};
			char* p = buffer;

			sprintf ( p,"%s,","InCompressorGain" );
			p += strlen ( p );

			if ( ( pstval->ch >> ( atoi ( token ) + 0x10 ) ) & 0x1 )
			{
				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d",atoi ( token ) );

				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;

				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d.%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[atoi ( token )][0]],pstval->param2[cg_u8_IN_ChannelTable[atoi ( token )][0]] );
				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;
			}

			sprintf ( p,"%s","EOF" );

			Uart3_printf ( "%s\r\n",buffer );
			dbg_printf ( "%s\r\n",buffer );

			//将数据发送给uart3
			//v_hexdump ( buffer, BUFLEN );

			token = strtok ( NULL,"," );
		}
	}

	return emCmdSucess;
}

void get_in_compressor_threshold ( pststMachVal_t pstval )
{
	char buffer[BUFLEN] = {0};
	char value[32] = {0};
	char* p = buffer;

	sprintf ( p,"%s,","InCompressorThreshold" );
	p += strlen ( p );

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d",i );

			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;

			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d.%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[i][0]],pstval->param2[cg_u8_IN_ChannelTable[i][0]] );
			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;
		}
	}

	sprintf ( p,"%s","EOF" );

	Uart3_printf ( "%s\r\n",buffer );
	dbg_printf ( "%s\r\n",buffer );

	//将数据发送给uart3
	//v_hexdump ( buffer, BUFLEN );
}

static emCmdFuncStaType mapp_CmdfuncGetInputCompressorThreshold ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	//emCmdFuncStaType l_state = emCmdNone;
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputCompressorThreshold - eFunc_SetProductName - 1];

	char* token = strtok ( l_pCmd,"," );

	if (!strncmp ( l_pCmd,"-1",2 ) )
	{
		get_in_compressor_threshold ( pstval );
	}
	else
	{
		if ( token != NULL )
		{
			char buffer[BUFLEN] = {0};
			char value[32] = {0};
			char* p = buffer;

			sprintf ( p,"%s,","InCompressorThreshold" );
			p += strlen ( p );

			if ( ( pstval->ch >> ( atoi ( token ) + 0x10 ) ) & 0x1 )
			{
				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d",atoi ( token ) );

				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;

				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d.%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[atoi ( token )][0]],pstval->param2[cg_u8_IN_ChannelTable[atoi ( token )][0]] );
				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;
			}

			sprintf ( p,"%s","EOF" );

			Uart3_printf ( "%s\r\n",buffer );
			dbg_printf ( "%s\r\n",buffer );

			//将数据发送给uart3
			//v_hexdump ( buffer, BUFLEN );

			token = strtok ( NULL,"," );
		}
	}

	return emCmdSucess;
}

void get_in_compressor_ratio ( pststMachVal_t pstval )
{
	char buffer[BUFLEN] = {0};
	char value[32] = {0};
	char* p = buffer;

	sprintf ( p,"%s,","InCompressorRatio" );
	p += strlen ( p );

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d",i );

			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;

			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d.%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[i][0]],pstval->param2[cg_u8_IN_ChannelTable[i][0]] );
			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;
		}
	}

	sprintf ( p,"%s","EOF" );

	Uart3_printf ( "%s\r\n",buffer );
	dbg_printf ( "%s\r\n",buffer );

	//将数据发送给uart3
	//v_hexdump ( buffer, BUFLEN );
}

static emCmdFuncStaType mapp_CmdfuncGetInputCompressorRatio ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	//emCmdFuncStaType l_state = emCmdNone;
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputCompressorRatio - eFunc_SetProductName - 1];

	char* token = strtok ( l_pCmd,"," );

	if (!strncmp ( l_pCmd,"-1",2 ) )
	{
		get_in_compressor_ratio ( pstval );
	}
	else
	{
		if ( token != NULL )
		{
			char buffer[BUFLEN] = {0};
			char value[32] = {0};
			char* p = buffer;

			sprintf ( p,"%s,","InCompressorRatio" );
			p += strlen ( p ) + 1;

			if ( ( pstval->ch >> ( atoi ( token ) + 0x10 ) ) & 0x1 )
			{
				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d",atoi ( token ) );

				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;

				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d.%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[atoi ( token )][0]],pstval->param2[cg_u8_IN_ChannelTable[atoi ( token )][0]] );
				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;
			}

			sprintf ( p,"%s","EOF" );

			Uart3_printf ( "%s\r\n",buffer );
			dbg_printf ( "%s\r\n",buffer );

			//将数据发送给uart3
			//v_hexdump ( buffer, BUFLEN );

			token = strtok ( NULL,"," );
		}
	}

	return emCmdSucess;
}

void get_in_compressor_start_time ( pststMachVal_t pstval )
{
	char buffer[BUFLEN] = {0};
	char value[32] = {0};
	char* p = buffer;

	sprintf ( p,"%s,","InCompressorStartTime" );
	p += strlen ( p );

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d",i );

			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;

			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d", pstval->param1[cg_u8_IN_ChannelTable[i][0]] );

			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;
		}
	}

	sprintf ( p,"%s","EOF" );

	Uart3_printf ( "%s\r\n",buffer );
	dbg_printf ( "%s\r\n",buffer );
}

static emCmdFuncStaType mapp_CmdfuncGetInputCompressorStartTime ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	//emCmdFuncStaType l_state = emCmdNone;
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputCompressorStartTime - eFunc_SetProductName - 1];

	char* token = strtok ( l_pCmd,"," );

	if (!strncmp ( l_pCmd,"-1",2 ) )
	{
		get_in_compressor_start_time ( pstval );
	}
	else
	{
		if ( token != NULL )
		{
			char buffer[BUFLEN] = {0};
			char value[32] = {0};
			char* p = buffer;

			sprintf ( p,"%s,","InCompressorStartTime" );
			p += strlen ( p );

			if ( ( pstval->ch >> ( atoi ( token ) + 0x10 ) ) & 0x1 )
			{
				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d",atoi ( token ) );

				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;

				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d", pstval->param1[cg_u8_IN_ChannelTable[atoi ( token )][0]] );
				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;
			}

			sprintf ( p,"%s","EOF" );

			Uart3_printf ( "%s\r\n",buffer );
			dbg_printf ( "%s\r\n",buffer );

			//将数据发送给uart3
			//v_hexdump ( buffer, BUFLEN );

			token = strtok ( NULL,"," );
		}
	}

	return emCmdSucess;
}

void get_in_compressor_rel_time ( pststMachVal_t pstval )
{
	char buffer[BUFLEN] = {0};
	char value[32] = {0};
	char* p = buffer;

	sprintf ( p,"%s,","InCompressorReleaseTime" );
	p += strlen ( p );

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d",i );

			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;

			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d", pstval->param1[cg_u8_IN_ChannelTable[i][0]] );
			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;
		}
	}

	sprintf ( p,"%s","EOF" );

	Uart3_printf ( "%s\r\n",buffer );
	dbg_printf ( "%s\r\n",buffer );

	//将数据发送给uart3
	//v_hexdump ( buffer, BUFLEN );
}

static emCmdFuncStaType mapp_CmdfuncGetInputCompressorReleasetime ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	//emCmdFuncStaType l_state = emCmdNone;
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputCompressorReleaseTime - eFunc_SetProductName - 1];

	char* token = strtok ( l_pCmd,"," );

	if (!strncmp ( l_pCmd,"-1",2 ) )
	{
		get_in_compressor_rel_time ( pstval );
	}
	else
	{
		if ( token != NULL )
		{
			char buffer[BUFLEN] = {0};
			char value[32] = {0};
			char* p = buffer;

			sprintf ( p,"%s,","InCompressorReleaseTime" );
			p += strlen ( p );

			if ( ( pstval->ch >> ( atoi ( token ) + 0x10 ) ) & 0x1 )
			{
				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d",atoi ( token ) );

				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;

				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d", pstval->param1[cg_u8_IN_ChannelTable[atoi ( token )][0]] );
				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;
			}

			sprintf ( p,"%s","EOF" );

			Uart3_printf ( "%s\r\n",buffer );
			dbg_printf ( "%s\r\n",buffer );

			//将数据发送给uart3
			//v_hexdump ( buffer, BUFLEN );

			token = strtok ( NULL,"," );
		}
	}

	return emCmdSucess;
}

void get_in_auto_gain_ctrl ( pststMachVal_t pstval )
{
	char buffer[BUFLEN] = {0};
	char value[32] = {0};
	char* p = buffer;

	sprintf ( p,"%s,","InAutoGainCtrl" );
	p += strlen ( p );

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d",i );

			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;

			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[i][0]] );
			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;
		}
	}

	sprintf ( p,"%s","EOF" );

	Uart3_printf ( "%s\r\n",buffer );
	dbg_printf ( "%s\r\n",buffer );

	//将数据发送给uart3
	//v_hexdump ( buffer, BUFLEN );
}

static emCmdFuncStaType mapp_CmdfuncGetInputAutoGainCtrl ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	//emCmdFuncStaType l_state = emCmdNone;
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputAutoGainCtrl - eFunc_SetProductName - 1];

	char* token = strtok ( l_pCmd,"," );

	if (!strncmp ( l_pCmd,"-1",2 ) )
	{
		get_in_auto_gain_ctrl ( pstval );
	}
	else
	{
		if ( token != NULL )
		{
			char buffer[BUFLEN] = {0};
			char value[32] = {0};
			char* p = buffer;

			sprintf ( p,"%s,","InAutoGainCtrl" );
			p += strlen ( p );

			if ( ( pstval->ch >> ( atoi ( token ) + 0x10 ) ) & 0x1 )
			{
				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d",atoi ( token ) );

				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;

				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[atoi ( token )][0]] );
				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;
			}

			sprintf ( p,"%s","EOF" );

			Uart3_printf ( "%s\r\n",buffer );
			dbg_printf ( "%s\r\n",buffer );

			//将数据发送给uart3
			//v_hexdump ( buffer, BUFLEN );

			token = strtok ( NULL,"," );
		}
	}

	return emCmdSucess;
}

void get_in_auto_gain_threshold ( pststMachVal_t pstval )
{
	char buffer[BUFLEN] = {0};
	char value[32] = {0};
	char* p = buffer;

	sprintf ( p,"%s,","InAutoGainThreshold" );
	p += strlen ( p );

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d",i );

			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;

			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d.%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[i][0]],pstval->param2[cg_u8_IN_ChannelTable[i][0]] );
			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;
		}
	}

	sprintf ( p,"%s","EOF" );

	Uart3_printf ( "%s\r\n",buffer );
	dbg_printf ( "%s\r\n",buffer );

	//将数据发送给uart3
	//v_hexdump ( buffer, BUFLEN );
}

static emCmdFuncStaType mapp_CmdfuncGetInputAutoGainThreshold ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	//emCmdFuncStaType l_state = emCmdNone;
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputAutoGainThreshold - eFunc_SetProductName - 1];

	char* token = strtok ( l_pCmd,"," );

	if (!strncmp ( l_pCmd,"-1",2 ) )
	{
		get_in_auto_gain_threshold ( pstval );
	}
	else
	{
		if ( token != NULL )
		{
			char buffer[BUFLEN] = {0};
			char value[32] = {0};
			char* p = buffer;

			sprintf ( p,"%s,","InAutoGainThreshold" );
			p += strlen ( p );

			if ( ( pstval->ch >> ( atoi ( token ) + 0x10 ) ) & 0x1 )
			{
				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d",atoi ( token ) );

				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;

				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d.%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[atoi ( token )][0]],pstval->param2[cg_u8_IN_ChannelTable[atoi ( token )][0]] );
				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;
			}

			sprintf ( p,"%s","EOF" );

			Uart3_printf ( "%s\r\n",buffer );
			dbg_printf ( "%s\r\n",buffer );

			//将数据发送给uart3
			//v_hexdump ( buffer, BUFLEN );

			token = strtok ( NULL,"," );
		}
	}

	return emCmdSucess;
}

void get_in_auto_gain_target_threshold ( pststMachVal_t pstval )
{
	char buffer[BUFLEN] = {0};
	char value[32] = {0};
	char* p = buffer;

	sprintf ( p,"%s,","InAutoGainTargetThreshold" );
	p += strlen ( p );

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d",i );

			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;

			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d.%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[i][0]],pstval->param2[cg_u8_IN_ChannelTable[i][0]] );
			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;
		}
	}

	sprintf ( p,"%s","EOF" );

	Uart3_printf ( "%s\r\n",buffer );
	dbg_printf ( "%s\r\n",buffer );

	//将数据发送给uart3
	//v_hexdump ( buffer, BUFLEN );
}

static emCmdFuncStaType mapp_CmdfuncGetInputAutoGainTargetThreshold ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	//emCmdFuncStaType l_state = emCmdNone;
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputAutoGainTargetThreshold - eFunc_SetProductName - 1];

	char* token = strtok ( l_pCmd,"," );

	if (!strncmp ( l_pCmd,"-1",2 ) )
	{
		get_in_auto_gain_target_threshold ( pstval );
	}
	else
	{
		if ( token != NULL )
		{
			char buffer[BUFLEN] = {0};
			char value[32] = {0};
			char* p = buffer;

			sprintf ( p,"%s,","InAutoGainTargetThreshold" );
			p += strlen ( p );

			if ( ( pstval->ch >> ( atoi ( token ) + 0x10 ) ) & 0x1 )
			{
				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d",atoi ( token ) );

				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;

				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d.%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[atoi ( token )][0]],pstval->param2[cg_u8_IN_ChannelTable[atoi ( token )][0]] );
				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;
			}

			sprintf ( p,"%s","EOF" );

			Uart3_printf ( "%s\r\n",buffer );
			dbg_printf ( "%s\r\n",buffer );

			//将数据发送给uart3
			//v_hexdump ( buffer, BUFLEN );

			token = strtok ( NULL,"," );
		}
	}

	return emCmdSucess;
}

void get_in_auto_gain_ratio ( pststMachVal_t pstval )
{
	char buffer[BUFLEN] = {0};
	char value[32] = {0};
	char* p = buffer;

	sprintf ( p,"%s,","InAutoGainRatio" );
	p += strlen ( p );

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d",i );

			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;

			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d.%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[i][0]],pstval->param2[cg_u8_IN_ChannelTable[i][0]] );
			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;
		}
	}

	sprintf ( p,"%s","EOF" );

	Uart3_printf ( "%s\r\n",buffer );
	dbg_printf ( "%s\r\n",buffer );

	//将数据发送给uart3
	//v_hexdump ( buffer, BUFLEN );
}

static emCmdFuncStaType mapp_CmdfuncGetInputAutoGainRatio ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	//emCmdFuncStaType l_state = emCmdNone;
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputAutoGainRatio - eFunc_SetProductName - 1];

	char* token = strtok ( l_pCmd,"," );

	if (!strncmp ( l_pCmd,"-1",2 ) )
	{
		get_in_auto_gain_ratio ( pstval );
	}
	else
	{
		if ( token != NULL )
		{
			char buffer[BUFLEN] = {0};
			char value[32] = {0};
			char* p = buffer;

			sprintf ( p,"%s,","InAutoGainRatio" );
			p += strlen ( p );

			if ( ( pstval->ch >> ( atoi ( token ) + 0x10 ) ) & 0x1 )
			{
				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d",atoi ( token ) );

				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;

				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d.%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[atoi ( token )][0]],pstval->param2[cg_u8_IN_ChannelTable[atoi ( token )][0]] );
				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;
			}

			sprintf ( p,"%s","EOF" );

			Uart3_printf ( "%s\r\n",buffer );
			dbg_printf ( "%s\r\n",buffer );

			//将数据发送给uart3
			//v_hexdump ( buffer, BUFLEN );

			token = strtok ( NULL,"," );
		}
	}

	return emCmdSucess;
}

void get_in_auto_gain_start_time ( pststMachVal_t pstval )
{
	char buffer[BUFLEN] = {0};
	char value[32] = {0};
	char* p = buffer;

	sprintf ( p,"%s,","InAutoGainStartTime" );
	p += strlen ( p );

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d",i );

			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;

			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[i][0]] );
			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;
		}
	}

	sprintf ( p,"%s","EOF" );

	Uart3_printf ( "%s\r\n",buffer );
	dbg_printf ( "%s\r\n",buffer );

	//将数据发送给uart3
	//v_hexdump ( buffer, BUFLEN );
}

static emCmdFuncStaType mapp_CmdfuncGetInputAutoGainStartTime ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	//emCmdFuncStaType l_state = emCmdNone;
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputAutoGainStartTime - eFunc_SetProductName - 1];

	char* token = strtok ( l_pCmd,"," );

	if (!strncmp ( l_pCmd,"-1",2 ) )
	{
		get_in_auto_gain_start_time ( pstval );
	}
	else
	{
		if ( token != NULL )
		{
			char buffer[BUFLEN] = {0};
			char value[32] = {0};
			char* p = buffer;

			sprintf ( p,"%s,","InAutoGainStartTime" );
			p += strlen ( p );

			if ( ( pstval->ch >> ( atoi ( token ) + 0x10 ) ) & 0x1 )
			{
				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d",atoi ( token ) );

				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;

				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[atoi ( token )][0]] );
				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;
			}

			sprintf ( p,"%s","EOF" );

			Uart3_printf ( "%s\r\n",buffer );
			dbg_printf ( "%s\r\n",buffer );

			//将数据发送给uart3
			//v_hexdump ( buffer, BUFLEN );

			token = strtok ( NULL,"," );
		}
	}

	return emCmdSucess;
}

void get_in_auto_gain_rel_time ( pststMachVal_t pstval )
{
	char buffer[BUFLEN] = {0};
	char value[32] = {0};
	char* p = buffer;

	sprintf ( p,"%s,","InAutoGainReleaseTime" );
	p += strlen ( p );

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d",i );

			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;

			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[i][0]] );
			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;
		}
	}

	sprintf ( p,"%s","EOF" );

	Uart3_printf ( "%s\r\n",buffer );
	dbg_printf ( "%s\r\n",buffer );

	//将数据发送给uart3
	//v_hexdump ( buffer, BUFLEN );
}

static emCmdFuncStaType mapp_CmdfuncGetInputAutoGainReleasetime ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	//emCmdFuncStaType l_state = emCmdNone;
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputAutoGainReleaseTime - eFunc_SetProductName - 1];

	char* token = strtok ( l_pCmd,"," );

	if (!strncmp ( l_pCmd,"-1",2 ) )
	{
		get_in_auto_gain_rel_time ( pstval );
	}
	else
	{
		if ( token != NULL )
		{
			char buffer[BUFLEN] = {0};
			char value[32] = {0};
			char* p = buffer;

			sprintf ( p,"%s,","InAutoGainReleaseTime" );
			p += strlen ( p );

			if ( ( pstval->ch >> ( atoi ( token ) + 0x10 ) ) & 0x1 )
			{
				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d",atoi ( token ) );

				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;

				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[atoi ( token )][0]] );

				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;
			}

			sprintf ( p,"%s","EOF" );

			Uart3_printf ( "%s\r\n",buffer );
			dbg_printf ( "%s\r\n",buffer );

			//将数据发送给uart3
			//v_hexdump ( buffer, BUFLEN );

			token = strtok ( NULL,"," );
		}
	}

	return emCmdSucess;
}

void get_in_EQ_type ( pststMachVal_t pstval )
{
	pstProjectGlobalAllVar_t pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	u16* pval = pstPrjSaveVar->EQParamter[0];

	char buffer[BUFLEN] = {0};
	char value[32] = {0};
	char* p = buffer;
	unsigned char hasvalue = 0;

	sprintf ( p,"%s,","InEQType" );
	p += strlen ( p );

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( hasvalue )
		{
			sprintf ( p,"%s,","InEQType" );
			p += strlen ( p );
		}

		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			hasvalue = 1;

			for ( u8 n = 0; n < EQ; n++ )
			{
				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d",i );

				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;

				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d", n );

				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;

				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d", pval[(2 * EQ * i) + (n * 2)] );

				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;
			}

			sprintf ( p,"%s","EOF" );

			Uart3_printf ( "%s\r\n",buffer );
			dbg_printf ( "%s\r\n",buffer );

			memset ( buffer,0,sizeof ( buffer ) );
			p = buffer;
		}
	}

	if (!hasvalue )
	{
		sprintf ( p,"%s","EOF" );

		Uart3_printf ( "%s\r\n",buffer );
		dbg_printf ( "%s\r\n",buffer );
	}
}

static emCmdFuncStaType mapp_CmdfuncGetInputEQType ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	//emCmdFuncStaType l_state = emCmdNone;
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputEQType - eFunc_SetProductName - 1];
	u16* pval = pstPrjSaveVar->EQParamter[0];

	char* token = strtok ( l_pCmd,"," );

	if (!strncmp ( l_pCmd,"-1",2 ) )
	{
		get_in_EQ_type ( pstval );
	}
	else
	{
		if ( token != NULL )
		{
			char buffer[BUFLEN] = {0};
			char value[32] = {0};
			char* p = buffer;

			sprintf ( p,"%s,","InEQType" );
			p += strlen ( p );

			if ( ( pstval->ch >> ( atoi ( token ) + 0x10 ) ) & 0x1 )
			{
				for ( u8 n = 0; n < EQ; n++ )
				{
					memset ( value,0,sizeof ( value ) );
					sprintf ( value,"%d",atoi ( token ) );

					sprintf ( p,"%s,",value );
					p += strlen ( value ) + 1;

					memset ( value,0,sizeof ( value ) );
					sprintf ( value,"%d", n );

					sprintf ( p,"%s,",value );
					p += strlen ( value ) + 1;

					memset ( value,0,sizeof ( value ) );
					sprintf ( value,"%d", pval[(2 * EQ * atoi ( token )) + (n * 2)]);

					sprintf ( p,"%s,",value );
					p += strlen ( value ) + 1;
				}
			}

			sprintf ( p,"%s","EOF" );

			Uart3_printf ( "%s\r\n",buffer );
			dbg_printf ( "%s\r\n",buffer );

			//将数据发送给uart3
			//v_hexdump ( buffer, BUFLEN );

			token = strtok ( NULL,"," );
		}
	}

	return emCmdSucess;
}

void get_in_EQ_gain ( pststMachVal_t pstval )
{
	pstProjectGlobalAllVar_t pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	u16* pval = pstPrjSaveVar->EQParamter[1];

	char buffer[BUFLEN] = {0};
	char value[32] = {0};
	char* p = buffer;
	char* pstEQ = ( char* ) pval;
	unsigned char hasvalue = 0;

	sprintf ( p,"%s,","InEQGain" );
	p += strlen ( p );

#if 1
	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( hasvalue )
		{
			sprintf ( p,"%s,","InEQGain" );
			p += strlen ( p );
		}

		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			hasvalue = 1;

			for ( u8 n = 0; n < EQ; n++ )
			{
				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d",i );

				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;

				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d", n );

				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;

				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d.%d", (u8)pstEQ[(2 * EQ * i) + (n * 2)], (u8)pstEQ[(2 * EQ * i) + (n * 2 + 1)] );

				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;
			}

			sprintf ( p,"%s","EOF" );

			Uart3_printf ( "%s\r\n",buffer );
			dbg_printf ( "%s\r\n",buffer );

			memset ( buffer,0,sizeof ( buffer ) );
			p = buffer;
		}
	}
#endif

	if (!hasvalue )
	{
		sprintf ( p,"%s","EOF" );

		Uart3_printf ( "%s\r\n",buffer );
		dbg_printf ( "%s\r\n",buffer );
	}

	//将数据发送给uart3
	//v_hexdump ( buffer, BUFLEN );
}

static emCmdFuncStaType mapp_CmdfuncGetInputEQGain ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	//emCmdFuncStaType l_state = emCmdNone;
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputEQGain - eFunc_SetProductName - 1];
	u16* pval = pstPrjSaveVar->EQParamter[1];

	char* token = strtok ( l_pCmd,"," );
  char* pstEQ = ( char* ) pval;

	if (!strncmp ( l_pCmd,"-1",2 ) )
	{
		get_in_EQ_gain ( pstval );
	}
	else
	{
		if ( token != NULL )
		{
			char buffer[BUFLEN] = {0};
			char value[32] = {0};
			char* p = buffer;

			sprintf ( p,"%s,","InEQGain" );
			p += strlen ( p );

			if ( ( pstval->ch >> ( atoi ( token ) + 0x10 ) ) & 0x1 )
			{
				for ( u8 n = 0; n < EQ; n++ )
				{
					memset ( value,0,sizeof ( value ) );
					sprintf ( value,"%d",atoi ( token ) );

					sprintf ( p,"%s,",value );
					p += strlen ( value ) + 1;

					memset ( value,0,sizeof ( value ) );
					sprintf ( value,"%d", n );

					sprintf ( p,"%s,",value );
					p += strlen ( value ) + 1;

					memset ( value,0,sizeof ( value ) );
					sprintf ( value,"%d.%d", pstEQ[(2 * EQ * atoi ( token )) + (n * 2)], pstEQ[ (2 * EQ * atoi ( token )) + (n * 2 + 1)] );
					sprintf ( p,"%s,",value );
					p += strlen ( value ) + 1;
				}
			}

			sprintf ( p,"%s","EOF" );

			Uart3_printf ( "%s\r\n",buffer );
			dbg_printf ( "%s\r\n",buffer );

			//将数据发送给uart3
			//v_hexdump ( buffer, BUFLEN );

			token = strtok ( NULL,"," );
		}
	}

	return emCmdSucess;
}

void get_in_EQ_quality_factor ( pststMachVal_t pstval )
{
	pstProjectGlobalAllVar_t pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	u16* pval = pstPrjSaveVar->EQParamter[2];

	char buffer[BUFLEN] = {0};
	char value[32] = {0};
	char* p = buffer;
	char* pstEQ = ( char* ) pval;
	unsigned char hasvalue = 0;

	sprintf ( p,"%s,","InEQQualityFactor" );
	p += strlen ( p );

  //dbg_printf ("####################################### %s,%d,n = %d,m = %d\r\n",__FUNCTION__,__LINE__,n,m );
  //dbg_printf ("####################################### %s,%d\r\n",__FUNCTION__,__LINE__ );
	//hexdump ( pval, sizeof ( pstPrjSaveVar->EQParamter[2] ) );

#if 1
	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( hasvalue )
		{
			sprintf ( p,"%s,","InEQQualityFactor" );
			p += strlen ( p );
		}

		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			hasvalue = 1;

			for ( u8 n = 0; n < EQ; n++ )
			{
				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d",i );

				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;

				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d", n );
				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;

				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d.%d", (u8)pstEQ[(2 * EQ * i) + (n * 2)], (u8)pstEQ[(2 * EQ * i) + (n * 2 + 1)]);
        
				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;
			}

			sprintf ( p,"%s","EOF" );

			Uart3_printf ( "%s\r\n",buffer );
			dbg_printf ( "%s\r\n",buffer );

			memset ( buffer,0,sizeof ( buffer ) );
			p = buffer;
		}
	}
#endif

	if (!hasvalue )
	{
		sprintf ( p,"%s","EOF" );

		Uart3_printf ( "%s\r\n",buffer );
		dbg_printf ( "%s\r\n",buffer );
	}

	//将数据发送给uart3
	//v_hexdump ( buffer, BUFLEN );
}

static emCmdFuncStaType mapp_CmdfuncGetInputEQQualityFactor ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	//emCmdFuncStaType l_state = emCmdNone;
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputEQQualityFactor - eFunc_SetProductName - 1];
	u16* pval = pstPrjSaveVar->EQParamter[2];

	char* token = strtok ( l_pCmd,"," );
  char* pstEQ = ( char* ) pval;

	if (!strncmp ( l_pCmd,"-1",2 ) )
	{
		get_in_EQ_quality_factor ( pstval );
	}
	else
	{
		if ( token != NULL )
		{
			char buffer[BUFLEN] = {0};
			char value[32] = {0};
			char* p = buffer;

			sprintf ( p,"%s,","InEQQualityFactor" );
			p += strlen ( p );

			if ( ( pstval->ch >> ( atoi ( token ) + 0x10 ) ) & 0x1 )
			{
				for ( u8 n = 0; n < EQ; n++ )
				{
					memset ( value,0,sizeof ( value ) );
					sprintf ( value,"%d",atoi ( token ) );

					sprintf ( p,"%s,",value );
					p += strlen ( value ) + 1;

					memset ( value,0,sizeof ( value ) );
					sprintf ( value,"%d", n );
					sprintf ( p,"%s,",value );
					p += strlen ( value ) + 1;

					memset ( value,0,sizeof ( value ) );
					sprintf ( value,"%d.%d", pstEQ[(2 * EQ * atoi ( token )) + (n * 2)], pstEQ[ (2 * EQ * atoi ( token )) + (n * 2 + 1)] );
					sprintf ( p,"%s,",value );
					p += strlen ( value ) + 1;
				}
			}

			sprintf ( p,"%s","EOF" );

			Uart3_printf ( "%s\r\n",buffer );
			dbg_printf ( "%s\r\n",buffer );

			//将数据发送给uart3
			//v_hexdump ( buffer, BUFLEN );

			token = strtok ( NULL,"," );
		}
	}

	return emCmdSucess;
}

void get_in_EQ_ctrl ( pststMachVal_t pstval )
{
	char buffer[BUFLEN] = {0};
	char value[32] = {0};
	char* p = buffer;
	unsigned char hasvalue = 0;

	sprintf ( p,"%s,","InEQCtrl" );
	p += strlen ( p );

#if 0
	dbg_printf ( "11111111111111111111\r\n" );
	hexdump ( ( void* ) buffer,strlen ( buffer ) );
	v_hexdump ( buffer,strlen ( buffer ) );
	dbg_printf ( "2222222222222222\r\n" );
	hexdump ( ( void* ) pstval,sizeof ( stMachVal_t ) );
	dbg_printf ( "44444444444444444444,%x\r\n",pstval->ch );
	hexdump ( ( void* ) & ( pstval->ch ),sizeof ( pstval->ch ) );
	dbg_printf ( "555555555555555555\r\n" );
	hexdump ( ( void* ) pstval->param1,sizeof ( pstval->param1 ) );
	dbg_printf ( "66666666666666666666666666666666\r\n" );
	hexdump ( ( void* ) pstval->param2,sizeof ( pstval->param2 ) );
	dbg_printf ( "3333333333333333\r\n" );
	hexdump ( ( void* ) & ( pstval->param1[0] ),sizeof ( u16 ) );
	hexdump ( ( void* ) & ( pstval->param2[0] ),sizeof ( u16 ) );
#endif

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( hasvalue )
		{
			sprintf ( p,"%s,","InEQCtrl" );
			p += strlen ( p );
		}

		for ( u8 n = 0; n < EQ; n ++ ) //关闭
		{
#if 0
			dbg_printf ( "77777777777777777777\r\n" );
			hexdump ( ( void* ) & ( pstval->param1[i] ),sizeof ( pstval->param1[0] ) );
			dbg_printf ( "88888888888888888888888\r\n" );
			hexdump ( ( void* ) & ( pstval->param2[i] ),sizeof ( pstval->param2[0] ) );

			dbg_printf ( "%d,%d on:%d,off:%d\r\n",i,n, ( pstval->param1[i] >> n ) & 0x1, ( pstval->param2[i] >> n ) & 0x1 );
#endif

			if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
			{
				hasvalue = 1;

				if ( ( pstval->param1[i] >> n ) & 0x1 )
				{
					memset ( value,0,sizeof ( value ) );
					sprintf ( value,"%d",i );

					sprintf ( p,"%s,",value );
					p += strlen ( value ) + 1;

					memset ( value,0,sizeof ( value ) );
					sprintf ( value,"%d", n );

					sprintf ( p,"%s,",value );
					p += strlen ( value ) + 1;

					memset ( value,0,sizeof ( value ) );
					sprintf ( value,"%d", 0 );

					sprintf ( p,"%s,",value );
					p += strlen ( value ) + 1;
				}

				if ( ( pstval->param2[i] >> n ) & 0x1 ) //打开
				{
					memset ( value,0,sizeof ( value ) );
					sprintf ( value,"%d",i );

					sprintf ( p,"%s,",value );
					p += strlen ( value ) + 1;

					memset ( value,0,sizeof ( value ) );
					sprintf ( value,"%d", n );

					sprintf ( p,"%s,",value );
					p += strlen ( value ) + 1;

					memset ( value,0,sizeof ( value ) );
					sprintf ( value,"%d", 1 );

					sprintf ( p,"%s,",value );
					p += strlen ( value ) + 1;
				}
			}
		}

		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			sprintf ( p,"%s","EOF" );

			//Uart3_printf ( "%s\r\n",buffer );
			dbg_printf ( "%s\r\n",buffer );

			memset ( buffer,0,sizeof ( buffer ) );
			p = buffer;
		}
	}

	if (!hasvalue )
	{
		sprintf ( p,"%s","EOF" );

		//Uart3_printf ( "%s\r\n",buffer );
		dbg_printf ( "%s\r\n",buffer );
	}

	//将数据发送给uart3
	//v_hexdump ( buffer, BUFLEN );
}

static emCmdFuncStaType mapp_CmdfuncGetInputEQCtrl ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	//emCmdFuncStaType l_state = emCmdNone;
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputEQCtrl - eFunc_SetProductName - 1];

	char* token = strtok ( l_pCmd,"," );

	if (!strncmp ( l_pCmd,"-1",2 ) )
	{
		get_in_EQ_ctrl ( pstval );
	}
	else
	{
		if ( token != NULL )
		{
			char buffer[BUFLEN] = {0};
			char value[32] = {0};
			char* p = buffer;

			sprintf ( p,"%s,","InEQCtrl" );
			p += strlen ( p );

			if ( ( pstval->ch >> ( atoi ( token ) + 0x10 ) ) & 0x1 )
			{
				for ( u8 n = 0; n < EQ; n ++ )
				{
					if ( ( pstval->param1[i] >> n ) & 0x1 )
					{
						memset ( value,0,sizeof ( value ) );
						sprintf ( value,"%d",atoi ( token ) );

						sprintf ( p,"%s,",value );
						p += strlen ( value ) + 1;

						memset ( value,0,sizeof ( value ) );
						sprintf ( value,"%d", 0 );

						sprintf ( p,"%s,",value );
						p += strlen ( value ) + 1;
					}

					if ( ( pstval->param2[i] >> n ) & 0x1 ) //打开
					{
						memset ( value,0,sizeof ( value ) );
						sprintf ( value,"%d",atoi ( token ) );

						sprintf ( p,"%s,",value );
						p += strlen ( value ) + 1;

						memset ( value,0,sizeof ( value ) );
						sprintf ( value,"%d", 1 );

						sprintf ( p,"%s,",value );
						p += strlen ( value ) + 1;
					}
				}
			}

			sprintf ( p,"%s","EOF" );

			Uart3_printf ( "%s\r\n",buffer );
			dbg_printf ( "%s\r\n",buffer );

			//将数据发送给uart3
			//v_hexdump ( buffer, BUFLEN );

			token = strtok ( NULL,"," );
		}
	}

	return emCmdSucess;
}

void get_in_howling_suppressor_ctrl ( pststMachVal_t pstval )
{
	char buffer[BUFLEN] = {0};
	char value[32] = {0};
	char* p = buffer;

	sprintf ( p,"%s,","InHowlingSuppressorCtrl" );
	p += strlen ( p );

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d",i );

			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;

			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d.%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[i][0]],pstval->param2[cg_u8_IN_ChannelTable[i][0]] );
			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;
		}
	}

	sprintf ( p,"%s","EOF" );

	Uart3_printf ( "%s\r\n",buffer );
	dbg_printf ( "%s\r\n",buffer );

	//将数据发送给uart3
	//v_hexdump ( buffer, BUFLEN );
}

static emCmdFuncStaType mapp_CmdfuncGetInputHowlingSuppressorCtrl ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	//emCmdFuncStaType l_state = emCmdNone;
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputHowlingSuppressorCtrl - eFunc_SetProductName - 1];

	char* token = strtok ( l_pCmd,"," );

	if (!strncmp ( l_pCmd,"-1",2 ) )
	{
		get_in_howling_suppressor_ctrl ( pstval );
	}
	else
	{
		if ( token != NULL )
		{
			char buffer[BUFLEN] = {0};
			char value[32] = {0};
			char* p = buffer;

			sprintf ( p,"%s,","InHowlingSuppressorCtrl" );
			p += strlen ( p );

			if ( ( pstval->ch >> ( atoi ( token ) + 0x10 ) ) & 0x1 )
			{
				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d",atoi ( token ) );

				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;

				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d.%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[atoi ( token )][0]],pstval->param2[cg_u8_IN_ChannelTable[atoi ( token )][0]] );
				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;
			}

			sprintf ( p,"%s","EOF" );

			Uart3_printf ( "%s\r\n",buffer );
			dbg_printf ( "%s\r\n",buffer );

			//将数据发送给uart3
			//v_hexdump ( buffer, BUFLEN );

			token = strtok ( NULL,"," );
		}
	}

	return emCmdSucess;
}

void get_in_howling_suppressor_grade ( pststMachVal_t pstval )
{
	char buffer[BUFLEN] = {0};
	char value[32] = {0};
	char* p = buffer;

	sprintf ( p,"%s,","InHowlingSuppressorGrade" );
	p += strlen ( p );

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d", pstval->param1[cg_u8_IN_ChannelTable[i][0]] );
			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;

			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d", pstval->param2[cg_u8_IN_ChannelTable[i][0]] );
			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;
		}
	}

	sprintf ( p,"%s","EOF" );

	Uart3_printf ( "%s\r\n",buffer );
	dbg_printf ( "%s\r\n",buffer );

	//将数据发送给uart3
	//v_hexdump ( buffer, BUFLEN );
}

static emCmdFuncStaType mapp_CmdfuncGetInputHowlingSuppressorGrade ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	//emCmdFuncStaType l_state = emCmdNone;
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputHowlingSuppressorGrade - eFunc_SetProductName - 1];

	char* token = strtok ( l_pCmd,"," );

	if (!strncmp ( l_pCmd,"-1",2 ) )
	{
		get_in_howling_suppressor_grade ( pstval );
	}
	else
	{
		if ( token != NULL )
		{
			char buffer[BUFLEN] = {0};
			char value[32] = {0};
			char* p = buffer;

			u8 len = strlen ( token );
			char param[4] = {0};

			sprintf ( p,"%s,","InHowlingSuppressorGrade" );
			p += strlen ( p );

			memcpy ( param,token,len - 1 );
			switch ( atoi ( param ) )
			{
				case emInLeft:
					if ( ( pstval->ch >>  0x10 ) & 0x1 )
					{
						memset ( value,0,sizeof ( value ) );
						sprintf ( value,"%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[0][0]] );
						sprintf ( p,"%s,",value );
						p += strlen ( value ) + 1;

						memset ( value,0,sizeof ( value ) );
						sprintf ( value,"%d", pstval->param2[cg_u8_IN_ChannelTable[0][0]] );
						sprintf ( p,"%s,",value );
						p += strlen ( value ) + 1;
					}

					break;
				case emInRight:
					if ( ( pstval->ch >> 0x15 ) & 0x1 )
					{
						memset ( value,0,sizeof ( value ) );
						sprintf ( value,"%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[5][0]] );
						sprintf ( p,"%s,",value );
						p += strlen ( value ) + 1;

						memset ( value,0,sizeof ( value ) );
						sprintf ( value,"%d", pstval->param2[cg_u8_IN_ChannelTable[5][0]] );
						sprintf ( p,"%s,",value );
						p += strlen ( value ) + 1;
					}

					break;
				default:
					break;
			}

			sprintf ( p,"%s","EOF" );

			Uart3_printf ( "%s\r\n",buffer );
			dbg_printf ( "%s\r\n",buffer );

			//将数据发送给uart3
			//v_hexdump ( buffer, BUFLEN );

			token = strtok ( NULL,"," );
		}
	}

	return emCmdSucess;
}

void get_in_howling_suppressor_freq_shift ( pststMachVal_t pstval )
{
	char buffer[BUFLEN] = {0};
	char value[32] = {0};
	char* p = buffer;

	sprintf ( p,"%s,","InHowlingSuppressorFreqShift" );
	p += strlen ( p );

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[i][0]] );
			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;

			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d", pstval->param2[cg_u8_IN_ChannelTable[i][0]] );
			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;
		}
	}

	sprintf ( p,"%s","EOF" );

	Uart3_printf ( "%s\r\n",buffer );
	dbg_printf ( "%s\r\n",buffer );

	//将数据发送给uart3
	//v_hexdump ( buffer, BUFLEN );
}

static emCmdFuncStaType mapp_CmdfuncGetInputHowlingSuppressorFreqShift ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	//emCmdFuncStaType l_state = emCmdNone;
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputHowlingSuppressorFreqShift - eFunc_SetProductName - 1];

	char* token = strtok ( l_pCmd,"," );

	if (!strncmp ( l_pCmd,"-1",2 ) )
	{
		get_in_howling_suppressor_freq_shift ( pstval );
	}
	else
	{
		if ( token != NULL )
		{
			char buffer[BUFLEN] = {0};
			char value[32] = {0};
			char* p = buffer;

			u8 len = strlen ( token );
			char param[4] = {0};

			sprintf ( p,"%s,","InHowlingSuppressorFreqShift" );
			p += strlen ( p );

			memcpy ( param,token,len - 1 );
			switch ( atoi ( param ) )
			{
				case emInLeft:
					if ( ( pstval->ch >>  0x10 ) & 0x1 )
					{
						memset ( value,0,sizeof ( value ) );
						sprintf ( value,"%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[0][0]] );
						sprintf ( p,"%s,",value );
						p += strlen ( value ) + 1;

						memset ( value,0,sizeof ( value ) );
						sprintf ( value,"%d", pstval->param2[cg_u8_IN_ChannelTable[0][0]] );
						sprintf ( p,"%s,",value );
						p += strlen ( value ) + 1;
					}

					break;
				case emInRight:
					if ( ( pstval->ch >> 0x15 ) & 0x1 )
					{
						memset ( value,0,sizeof ( value ) );
						sprintf ( value,"%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[5][0]] );
						sprintf ( p,"%s,",value );
						p += strlen ( value ) + 1;

						memset ( value,0,sizeof ( value ) );
						sprintf ( value,"%d", pstval->param2[cg_u8_IN_ChannelTable[5][0]] );
						sprintf ( p,"%s,",value );
						p += strlen ( value ) + 1;
					}

					break;
				default:
					break;
			}

			sprintf ( p,"%s","EOF" );

			Uart3_printf ( "%s\r\n",buffer );
			dbg_printf ( "%s\r\n",buffer );

			//将数据发送给uart3
			//v_hexdump ( buffer, BUFLEN );

			token = strtok ( NULL,"," );
		}
	}

	return emCmdSucess;
}

void get_in_noise_suppressor_grade ( pststMachVal_t pstval )
{
	char buffer[BUFLEN] = {0};
	char value[32] = {0};
	char* p = buffer;

	sprintf ( p,"%s,","InNoiseSuppressorGrade" );
	p += strlen ( p );

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[i][0]] );
			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;

			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d", pstval->param2[cg_u8_IN_ChannelTable[i][0]] );
			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;
		}
	}

	sprintf ( p,"%s","EOF" );

	Uart3_printf ( "%s\r\n",buffer );
	dbg_printf ( "%s\r\n",buffer );

	//将数据发送给uart3
	//v_hexdump ( buffer, BUFLEN );
}

/**
针对单个INPUT生效,噪声抑制只针对输入有效
**/
static emCmdFuncStaType mapp_CmdfuncGetInputNoiseSuppressorGrade ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	//emCmdFuncStaType l_state = emCmdNone;
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputNoiseSuppressorGrade - eFunc_SetProductName - 1];

	char* token = strtok ( l_pCmd,"," );

	if (!strncmp ( l_pCmd,"-1",2 ) )
	{
		get_in_noise_suppressor_grade ( pstval );
	}
	else
	{
		if ( token != NULL )
		{
			char buffer[BUFLEN] = {0};
			char value[32] = {0};
			char* p = buffer;

			u8 len = strlen ( token );
			char param[4] = {0};

			sprintf ( p,"%s,","InNoiseSuppressorGrade" );
			p += strlen ( p );

			memcpy ( param,token,len - 1 );
			switch ( atoi ( param ) )
			{
				case emInLeft:
					if ( ( pstval->ch >>  0x10 ) & 0x1 )
					{
						memset ( value,0,sizeof ( value ) );
						sprintf ( value,"%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[0][0]] );
						sprintf ( p,"%s,",value );
						p += strlen ( value ) + 1;

						memset ( value,0,sizeof ( value ) );
						sprintf ( value,"%d", pstval->param2[cg_u8_IN_ChannelTable[0][0]] );
						sprintf ( p,"%s,",value );
						p += strlen ( value ) + 1;
					}

					break;
				case emInRight:
					if ( ( pstval->ch >> 0x15 ) & 0x1 )
					{
						memset ( value,0,sizeof ( value ) );
						sprintf ( value,"%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[5][0]] );
						sprintf ( p,"%s,",value );
						p += strlen ( value ) + 1;

						memset ( value,0,sizeof ( value ) );
						sprintf ( value,"%d", pstval->param2[cg_u8_IN_ChannelTable[5][0]] );
						sprintf ( p,"%s,",value );
						p += strlen ( value ) + 1;
					}

					break;
				default:
					break;
			}

			sprintf ( p,"%s","EOF" );

			Uart3_printf ( "%s\r\n",buffer );
			dbg_printf ( "%s\r\n",buffer );

			//将数据发送给uart3
			//v_hexdump ( buffer, BUFLEN );

			token = strtok ( NULL,"," );
		}
	}

	return emCmdSucess;
}

void get_in_noise_suppressor_threshold ( pststMachVal_t pstval )
{
	char buffer[BUFLEN] = {0};
	char value[32] = {0};
	char* p = buffer;

	sprintf ( p,"%s,","InNoiseSuppressorThreshold" );
	p += strlen ( p );

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d.%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[i][0]],pstval->param2[cg_u8_IN_ChannelTable[i][0]] );
			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;

			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d", pstval->param3[cg_u8_IN_ChannelTable[i][0]] );
			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;
		}
	}

	sprintf ( p,"%s","EOF" );

	Uart3_printf ( "%s\r\n",buffer );
	dbg_printf ( "%s\r\n",buffer );

	//将数据发送给uart3
	//v_hexdump ( buffer, BUFLEN );
}

static emCmdFuncStaType mapp_CmdfuncGetInputNoiseSuppressorThreshold ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	//emCmdFuncStaType l_state = emCmdNone;
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputNoiseSuppressorThreshold - eFunc_SetProductName - 1];

	char* token = strtok ( l_pCmd,"," );

	if (!strncmp ( l_pCmd,"-1",2 ) )
	{
		get_in_noise_suppressor_threshold ( pstval );
	}
	else
	{
		if ( token != NULL )
		{
			char buffer[BUFLEN] = {0};
			char value[32] = {0};
			char* p = buffer;

			u8 len = strlen ( token );
			char param[4] = {0};

			sprintf ( p,"%s,","InNoiseSuppressorThreshold" );
			p += strlen ( p );

			memcpy ( param,token,len - 1 );
			switch ( atoi ( param ) )
			{
				case emInLeft:
					if ( ( pstval->ch >>  0x10 ) & 0x1 )
					{
						memset ( value,0,sizeof ( value ) );
						sprintf ( value,"%d.%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[0][0]],pstval->param2[cg_u8_IN_ChannelTable[0][0]] );
						sprintf ( p,"%s,",value );
						p += strlen ( value ) + 1;

						memset ( value,0,sizeof ( value ) );
						sprintf ( value,"%d", pstval->param3[cg_u8_IN_ChannelTable[0][0]] );
						sprintf ( p,"%s,",value );
						p += strlen ( value ) + 1;
					}

					break;
				case emInRight:
					if ( ( pstval->ch >> 0x15 ) & 0x1 )
					{
						memset ( value,0,sizeof ( value ) );
						sprintf ( value,"%d.%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[5][0]],pstval->param2[cg_u8_IN_ChannelTable[5][0]] );
						sprintf ( p,"%s,",value );
						p += strlen ( value ) + 1;

						memset ( value,0,sizeof ( value ) );
						sprintf ( value,"%d", pstval->param3[cg_u8_IN_ChannelTable[5][0]] );
						sprintf ( p,"%s,",value );
						p += strlen ( value ) + 1;
					}

					break;
				default:
					break;
			}

			sprintf ( p,"%s","EOF" );

			Uart3_printf ( "%s\r\n",buffer );
			dbg_printf ( "%s\r\n",buffer );

			//将数据发送给uart3
			//v_hexdump ( buffer, BUFLEN );

			token = strtok ( NULL,"," );
		}
	}

	return emCmdSucess;
}

void get_in_noise_suppressor_ratio ( pststMachVal_t pstval )
{
	char buffer[BUFLEN] = {0};
	char value[32] = {0};
	char* p = buffer;

	sprintf ( p,"%s,","InNoiseSuppressorRatio" );
	p += strlen ( p );

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d.%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[i][0]],pstval->param2[cg_u8_IN_ChannelTable[i][0]] );
			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;

			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d", pstval->param3[cg_u8_IN_ChannelTable[i][0]] );
			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;
		}
	}

	sprintf ( p,"%s","EOF" );

	Uart3_printf ( "%s\r\n",buffer );
	dbg_printf ( "%s\r\n",buffer );

	//将数据发送给uart3
	//v_hexdump ( buffer, BUFLEN );
}

static emCmdFuncStaType mapp_CmdfuncGetInputNoiseSuppressorRatio ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	//emCmdFuncStaType l_state = emCmdNone;
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputNoiseSuppressorRatio - eFunc_SetProductName - 1];

	char* token = strtok ( l_pCmd,"," );

	if (!strncmp ( l_pCmd,"-1",2 ) )
	{
		get_in_noise_suppressor_ratio ( pstval );
	}
	else
	{
		if ( token != NULL )
		{
			char buffer[BUFLEN] = {0};
			char value[32] = {0};
			char* p = buffer;

			u8 len = strlen ( token );
			char param[4] = {0};

			sprintf ( p,"%s,","InNoiseSuppressorRatio" );
			p += strlen ( p );

			memcpy ( param,token,len - 1 );
			switch ( atoi ( param ) )
			{
				case emInLeft:
					if ( ( pstval->ch >>  0x10 ) & 0x1 )
					{
						memset ( value,0,sizeof ( value ) );
						sprintf ( value,"%d.%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[0][0]],pstval->param2[cg_u8_IN_ChannelTable[0][0]] );
						sprintf ( p,"%s,",value );
						p += strlen ( value ) + 1;

						memset ( value,0,sizeof ( value ) );
						sprintf ( value,"%d", pstval->param3[cg_u8_IN_ChannelTable[0][0]] );
						sprintf ( p,"%s,",value );
						p += strlen ( value ) + 1;
					}

					break;
				case emInRight:
					if ( ( pstval->ch >> 0x15 ) & 0x1 )
					{
						memset ( value,0,sizeof ( value ) );
						sprintf ( value,"%d.%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[5][0]],pstval->param2[cg_u8_IN_ChannelTable[5][0]] );
						sprintf ( p,"%s,",value );
						p += strlen ( value ) + 1;

						memset ( value,0,sizeof ( value ) );
						sprintf ( value,"%d", pstval->param3[cg_u8_IN_ChannelTable[5][0]] );
						sprintf ( p,"%s,",value );
						p += strlen ( value ) + 1;
					}

					break;
				default:
					break;
			}

			sprintf ( p,"%s","EOF" );

			Uart3_printf ( "%s\r\n",buffer );
			dbg_printf ( "%s\r\n",buffer );

			//将数据发送给uart3
			//v_hexdump ( buffer, BUFLEN );

			token = strtok ( NULL,"," );
		}
	}

	return emCmdSucess;
}

void get_in_noise_suppressor_start_time ( pststMachVal_t pstval )
{
	char buffer[BUFLEN] = {0};
	char value[32] = {0};
	char* p = buffer;

	sprintf ( p,"%s,","InNoiseSuppressorStartTime" );
	p += strlen ( p );

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d", pstval->param1[cg_u8_IN_ChannelTable[i][0]] );
			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;

			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d", pstval->param2[cg_u8_IN_ChannelTable[i][0]] );
			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;
		}
	}

	sprintf ( p,"%s","EOF" );

	Uart3_printf ( "%s\r\n",buffer );
	dbg_printf ( "%s\r\n",buffer );

	//将数据发送给uart3
	//v_hexdump ( buffer, BUFLEN );
}

static emCmdFuncStaType mapp_CmdfuncGetInputNoiseSuppressorStartTime ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	//emCmdFuncStaType l_state = emCmdNone;
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputNoiseSuppressorStartTime - eFunc_SetProductName - 1];

	char* token = strtok ( l_pCmd,"," );

	if (!strncmp ( l_pCmd,"-1",2 ) )
	{
		get_in_noise_suppressor_start_time ( pstval );
	}
	else
	{
		if ( token != NULL )
		{
			char buffer[BUFLEN] = {0};
			char value[32] = {0};
			char* p = buffer;

			u8 len = strlen ( token );
			char param[4] = {0};

			sprintf ( p,"%s,","InNoiseSuppressorStartTime" );
			p += strlen ( p );

			memcpy ( param,token,len - 1 );
			switch ( atoi ( param ) )
			{
				case emInLeft:
					if ( ( pstval->ch >>  0x10 ) & 0x1 )
					{
						memset ( value,0,sizeof ( value ) );
						sprintf ( value,"%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[0][0]] );
						sprintf ( p,"%s,",value );
						p += strlen ( value ) + 1;

						memset ( value,0,sizeof ( value ) );
						sprintf ( value,"%d", pstval->param2[cg_u8_IN_ChannelTable[0][0]] );
						sprintf ( p,"%s,",value );
						p += strlen ( value ) + 1;
					}

					break;
				case emInRight:
					if ( ( pstval->ch >> 0x15 ) & 0x1 )
					{
						memset ( value,0,sizeof ( value ) );
						sprintf ( value,"%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[5][0]] );
						sprintf ( p,"%s,",value );
						p += strlen ( value ) + 1;

						memset ( value,0,sizeof ( value ) );
						sprintf ( value,"%d", pstval->param2[cg_u8_IN_ChannelTable[5][0]] );
						sprintf ( p,"%s,",value );
						p += strlen ( value ) + 1;
					}

					break;
				default:
					break;
			}

			sprintf ( p,"%s","EOF" );

			Uart3_printf ( "%s\r\n",buffer );
			dbg_printf ( "%s\r\n",buffer );

			//将数据发送给uart3
			//v_hexdump ( buffer, BUFLEN );

			token = strtok ( NULL,"," );
		}
	}

	return emCmdSucess;
}

void get_in_noise_suppressor_rel_time ( pststMachVal_t pstval )
{
	char buffer[BUFLEN] = {0};
	char value[32] = {0};
	char* p = buffer;

	sprintf ( p,"%s,","InputNoiseSuppressorReleaseTime" );
	p += strlen ( p );

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d", pstval->param1[cg_u8_IN_ChannelTable[i][0]] );
			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;

			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d", pstval->param2[cg_u8_IN_ChannelTable[i][0]] );
			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;
		}
	}

	sprintf ( p,"%s","EOF" );

	Uart3_printf ( "%s\r\n",buffer );
	dbg_printf ( "%s\r\n",buffer );

	//将数据发送给uart3
	//v_hexdump ( buffer, BUFLEN );
}

static emCmdFuncStaType mapp_CmdfuncGetInputNoiseSuppressorReleasetime ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	//emCmdFuncStaType l_state = emCmdNone;
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputNoiseSuppressorReleaseTime - eFunc_SetProductName - 1];

	char* token = strtok ( l_pCmd,"," );

	if (!strncmp ( l_pCmd,"-1",2 ) )
	{
		get_in_noise_suppressor_rel_time ( pstval );
	}
	else
	{
		if ( token != NULL )
		{
			char buffer[BUFLEN] = {0};
			char value[32] = {0};
			char* p = buffer;

			u8 len = strlen ( token );
			char param[4] = {0};

			sprintf ( p,"%s,","InputNoiseSuppressorReleaseTime" );
			p += strlen ( p );

			memcpy ( param,token,len - 1 );
			switch ( atoi ( param ) )
			{
				case emInLeft:
					if ( ( pstval->ch >>  0x10 ) & 0x1 )
					{
						memset ( value,0,sizeof ( value ) );
						sprintf ( value,"%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[0][0]] );
						sprintf ( p,"%s,",value );
						p += strlen ( value ) + 1;

						memset ( value,0,sizeof ( value ) );
						sprintf ( value,"%d", pstval->param2[cg_u8_IN_ChannelTable[0][0]] );
						sprintf ( p,"%s,",value );
						p += strlen ( value ) + 1;
					}

					break;
				case emInRight:
					if ( ( pstval->ch >> 0x15 ) & 0x1 )
					{
						memset ( value,0,sizeof ( value ) );
						sprintf ( value,"%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[5][0]] );
						sprintf ( p,"%s,",value );
						p += strlen ( value ) + 1;

						memset ( value,0,sizeof ( value ) );
						sprintf ( value,"%d", pstval->param2[cg_u8_IN_ChannelTable[5][0]] );
						sprintf ( p,"%s,",value );
						p += strlen ( value ) + 1;
					}

					break;
				default:
					break;
			}

			sprintf ( p,"%s","EOF" );

			Uart3_printf ( "%s\r\n",buffer );
			dbg_printf ( "%s\r\n",buffer );

			//将数据发送给uart3
			//v_hexdump ( buffer, BUFLEN );

			token = strtok ( NULL,"," );
		}
	}

	return emCmdSucess;
}

void get_in_noise_suppressor_ctrl ( pststMachVal_t pstval )
{
	char buffer[BUFLEN] = {0};
	char value[32] = {0};
	char* p = buffer;

	sprintf ( p,"%s,","InNoiseSuppressorCtrl" );
	p += strlen ( p );

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d",i );

			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;

			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[i][0]] );
			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;
		}
	}

	sprintf ( p,"%s","EOF" );

	Uart3_printf ( "%s\r\n",buffer );
	dbg_printf ( "%s\r\n",buffer );

	//将数据发送给uart3
	//v_hexdump ( buffer, BUFLEN );
}

static emCmdFuncStaType mapp_CmdfuncGetInputNoiseSuppressorCtrl ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	//emCmdFuncStaType l_state = emCmdNone;
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputNoiseSuppressorCtrl - eFunc_SetProductName - 1];

	char* token = strtok ( l_pCmd,"," );

	if (!strncmp ( l_pCmd,"-1",2 ) )
	{
		get_in_noise_suppressor_ctrl ( pstval );
	}
	else
	{
		if ( token != NULL )
		{
			char buffer[BUFLEN] = {0};
			char value[32] = {0};
			char* p = buffer;

			sprintf ( p,"%s,","InNoiseSuppressorCtrl" );
			p += strlen ( p );

			if ( ( pstval->ch >> ( atoi ( token ) + 0x10 ) ) & 0x1 )
			{
				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d",atoi ( token ) );

				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;

				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[atoi ( token )][0]] );
				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;
			}

			sprintf ( p,"%s","EOF" );

			Uart3_printf ( "%s\r\n",buffer );
			dbg_printf ( "%s\r\n",buffer );

			//将数据发送给uart3
			//v_hexdump ( buffer, BUFLEN );

			token = strtok ( NULL,"," );
		}
	}

	return emCmdSucess;
}

void get_in_echo_canceller_grade ( pststMachVal_t pstval )
{
	char buffer[BUFLEN] = {0};
	char value[32] = {0};
	char* p = buffer;

	sprintf ( p,"%s,","InputEchoCancellerGrade" );
	p += strlen ( p );

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[i][0]] );
			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;

			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d", pstval->param2[cg_u8_IN_ChannelTable[i][0]] );
			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;
		}
	}

	sprintf ( p,"%s","EOF" );

	Uart3_printf ( "%s\r\n",buffer );
	dbg_printf ( "%s\r\n",buffer );

	//将数据发送给uart3
	//v_hexdump ( buffer, BUFLEN );
}

static emCmdFuncStaType mapp_CmdfuncGetInputEchoCancellerGrade ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	//emCmdFuncStaType l_state = emCmdNone;
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputEchoCancellerGrade - eFunc_SetProductName - 1];

	char* token = strtok ( l_pCmd,"," );

	if (!strncmp ( l_pCmd,"-1",2 ) )
	{
		get_in_echo_canceller_grade ( pstval );
	}
	else
	{
		if ( token != NULL )
		{
			char buffer[BUFLEN] = {0};
			char value[32] = {0};
			char* p = buffer;

			u8 len = strlen ( token );
			char param[4] = {0};

			sprintf ( p,"%s,","InputEchoCancellerGrade" );
			p += strlen ( p );

			memcpy ( param,token,len - 1 );
			switch ( atoi ( param ) )
			{
				case emInLeft:
					if ( ( pstval->ch >>  0x10 ) & 0x1 )
					{
						memset ( value,0,sizeof ( value ) );
						sprintf ( value,"%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[0][0]] );
						sprintf ( p,"%s,",value );
						p += strlen ( value ) + 1;

						memset ( value,0,sizeof ( value ) );
						sprintf ( value,"%d", pstval->param2[cg_u8_IN_ChannelTable[0][0]] );
						sprintf ( p,"%s,",value );
						p += strlen ( value ) + 1;
					}

					break;
				case emInRight:
					if ( ( pstval->ch >> 0x15 ) & 0x1 )
					{
						memset ( value,0,sizeof ( value ) );
						sprintf ( value,"%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[5][0]] );
						sprintf ( p,"%s,",value );
						p += strlen ( value ) + 1;

						memset ( value,0,sizeof ( value ) );
						sprintf ( value,"%d", pstval->param2[cg_u8_IN_ChannelTable[5][0]] );
						sprintf ( p,"%s,",value );
						p += strlen ( value ) + 1;
					}

					break;
				default:
					break;
			}

			sprintf ( p,"%s","EOF" );

			Uart3_printf ( "%s\r\n",buffer );
			dbg_printf ( "%s\r\n",buffer );

			//将数据发送给uart3
			//v_hexdump ( buffer, BUFLEN );

			token = strtok ( NULL,"," );
		}
	}

	return emCmdSucess;
}

void get_in_echo_canceller_ctrl ( pststMachVal_t pstval )
{
	char buffer[BUFLEN] = {0};
	char value[32] = {0};
	char* p = buffer;

	sprintf ( p,"%s,","InEchoCancellerCtrl" );
	p += strlen ( p );

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d",i );

			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;

			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[i][0]] );
			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;
		}
	}

	sprintf ( p,"%s","EOF" );

	Uart3_printf ( "%s\r\n",buffer );
	dbg_printf ( "%s\r\n",buffer );

	//将数据发送给uart3
	//v_hexdump ( buffer, BUFLEN );
}

static emCmdFuncStaType mapp_CmdfuncGetInputEchoCancellerCtrl ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	//emCmdFuncStaType l_state = emCmdNone;
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputEchoCancellerCtrl - eFunc_SetProductName - 1];

	char* token = strtok ( l_pCmd,"," );

	if (!strncmp ( l_pCmd,"-1",2 ) )
	{
		get_in_echo_canceller_ctrl ( pstval );
	}
	else
	{
		if ( token != NULL )
		{
			char buffer[BUFLEN] = {0};
			char value[32] = {0};
			char* p = buffer;

			sprintf ( p,"%s,","InEchoCancellerCtrl" );
			p += strlen ( p );

			if ( ( pstval->ch >> ( atoi ( token ) + 0x10 ) ) & 0x1 )
			{
				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d",atoi ( token ) );

				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;

				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[atoi ( token )][0]] );
				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;
			}

			sprintf ( p,"%s","EOF" );

			Uart3_printf ( "%s\r\n",buffer );
			dbg_printf ( "%s\r\n",buffer );

			//将数据发送给uart3
			//v_hexdump ( buffer, BUFLEN );

			token = strtok ( NULL,"," );
		}
	}

	return emCmdSucess;
}

void get_in_l_freq_exciter_grade ( pststMachVal_t pstval )
{
	char buffer[BUFLEN] = {0};
	char value[32] = {0};
	char* p = buffer;

	sprintf ( p,"%s,","InLfreqExciterGrade" );
	p += strlen ( p );

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d",i );

			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;

			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[i][0]] );
			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;
		}
	}

	sprintf ( p,"%s","EOF" );

	Uart3_printf ( "%s\r\n",buffer );
	dbg_printf ( "%s\r\n",buffer );

	//将数据发送给uart3
	//v_hexdump ( buffer, BUFLEN );
}

static emCmdFuncStaType mapp_CmdfuncGetInputLfreqExciterGrade ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	//emCmdFuncStaType l_state = emCmdNone;
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputLfreqExciterGrade - eFunc_SetProductName - 1];

	char* token = strtok ( l_pCmd,"," );

	if (!strncmp ( l_pCmd,"-1",2 ) )
	{
		get_in_l_freq_exciter_grade ( pstval );
	}
	else
	{
		if ( token != NULL )
		{
			char buffer[BUFLEN] = {0};
			char value[32] = {0};
			char* p = buffer;

			sprintf ( p,"%s,","InLfreqExciterGrade" );
			p += strlen ( p );

			if ( ( pstval->ch >> ( atoi ( token ) + 0x10 ) ) & 0x1 )
			{
				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d",atoi ( token ) );

				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;

				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[atoi ( token )][0]] );
				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;
			}

			sprintf ( p,"%s","EOF" );

			Uart3_printf ( "%s\r\n",buffer );
			dbg_printf ( "%s\r\n",buffer );

			//将数据发送给uart3
			//v_hexdump ( buffer, BUFLEN );

			token = strtok ( NULL,"," );
		}
	}

	return emCmdSucess;
}

void get_in_h_freq_exciter_grade ( pststMachVal_t pstval )
{
	char buffer[BUFLEN] = {0};
	char value[32] = {0};
	char* p = buffer;

	sprintf ( p,"%s,","InHfreqExciterGrade" );
	p += strlen ( p );

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d",i );

			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;

			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[i][0]] );
			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;
		}
	}

	sprintf ( p,"%s","EOF" );

	Uart3_printf ( "%s\r\n",buffer );
	dbg_printf ( "%s\r\n",buffer );

	//将数据发送给uart3
	//v_hexdump ( buffer, BUFLEN );
}

static emCmdFuncStaType mapp_CmdfuncGetInputHfreqExciterGrade ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	//emCmdFuncStaType l_state = emCmdNone;
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputHfreqExciterGrade - eFunc_SetProductName - 1];

	char* token = strtok ( l_pCmd,"," );

	if (!strncmp ( l_pCmd,"-1",2 ) )
	{
		get_in_h_freq_exciter_grade ( pstval );
	}
	else
	{
		if ( token != NULL )
		{
			char buffer[BUFLEN] = {0};
			char value[32] = {0};
			char* p = buffer;

			sprintf ( p,"%s,","InHfreqExciterGrade" );
			p += strlen ( p );

			if ( ( pstval->ch >> ( atoi ( token ) + 0x10 ) ) & 0x1 )
			{
				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d",atoi ( token ) );

				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;

				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[atoi ( token )][0]] );
				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;
			}

			sprintf ( p,"%s","EOF" );

			Uart3_printf ( "%s\r\n",buffer );
			dbg_printf ( "%s\r\n",buffer );

			//将数据发送给uart3
			//v_hexdump ( buffer, BUFLEN );

			token = strtok ( NULL,"," );
		}
	}

	return emCmdSucess;
}

void get_in_exciter_ctrl ( pststMachVal_t pstval )
{
	char buffer[BUFLEN] = {0};
	char value[32] = {0};
	char* p = buffer;

	sprintf ( p,"%s,","InExciterCtrl" );
	p += strlen ( p );

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d",i );

			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;

			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[i][0]] );
			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;
		}
	}

	sprintf ( p,"%s","EOF" );

	Uart3_printf ( "%s\r\n",buffer );
	dbg_printf ( "%s\r\n",buffer );

	//将数据发送给uart3
	//v_hexdump ( buffer, BUFLEN );
}

static emCmdFuncStaType mapp_CmdfuncGetInputExciterCtrl ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	//emCmdFuncStaType l_state = emCmdNone;
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputExciterCtrl - eFunc_SetProductName - 1];

	char* token = strtok ( l_pCmd,"," );

	if (!strncmp ( l_pCmd,"-1",2 ) )
	{
		get_in_exciter_ctrl ( pstval );
	}
	else
	{
		if ( token != NULL )
		{
			char buffer[BUFLEN] = {0};
			char value[32] = {0};
			char* p = buffer;

			sprintf ( p,"%s,","InExciterCtrl" );
			p += strlen ( p );

			if ( ( pstval->ch >> ( atoi ( token ) + 0x10 ) ) & 0x1 )
			{
				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d",atoi ( token ) );

				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;

				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[atoi ( token )][0]] );
				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;
			}

			token = strtok ( NULL,"," );
		}
	}

	return emCmdSucess;
}

void get_in_call_input ( pststMachVal_t pstval )
{
	char buffer[BUFLEN] = {0};
	char value[32] = {0};
	char* p = buffer;

	sprintf ( p,"%s,","InCallInput" );
	p += strlen ( p );

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d",i );

			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;

			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[i][0]] );
			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;
		}
	}

	sprintf ( p,"%s","EOF" );

	Uart3_printf ( "%s\r\n",buffer );
	dbg_printf ( "%s\r\n",buffer );

	//将数据发送给uart3
	//v_hexdump ( buffer, BUFLEN );
}

static emCmdFuncStaType mapp_CmdfuncGetInputCallInput ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	//emCmdFuncStaType l_state = emCmdNone;
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputCallInput - eFunc_SetProductName - 1];

	char* token = strtok ( l_pCmd,"," );

	if (!strncmp ( l_pCmd,"-1",2 ) )
	{
		get_in_call_input ( pstval );
	}
	else
	{
		if ( token != NULL )
		{
			char buffer[BUFLEN] = {0};
			char value[32] = {0};
			char* p = buffer;

			sprintf ( p,"%s,","InCallInput" );
			p += strlen ( p );

			if ( ( pstval->ch >> ( atoi ( token ) + 0x10 ) ) & 0x1 )
			{
				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d",atoi ( token ) );

				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;

				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[atoi ( token )][0]] );
				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;
			}

			sprintf ( p,"%s","EOF" );

			Uart3_printf ( "%s\r\n",buffer );
			dbg_printf ( "%s\r\n",buffer );

			//将数据发送给uart3
			//v_hexdump ( buffer, BUFLEN );

			token = strtok ( NULL,"," );
		}
	}

	return emCmdSucess;
}

void get_in_background_input ( pststMachVal_t pstval )
{
	char buffer[BUFLEN] = {0};
	char value[32] = {0};
	char* p = buffer;

	sprintf ( p,"%s,","InBackgroundInput" );
	p += strlen ( p );

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d",i );

			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;

			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[i][0]] );
			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;
		}
	}

	sprintf ( p,"%s","EOF" );

	Uart3_printf ( "%s\r\n",buffer );
	dbg_printf ( "%s\r\n",buffer );

	//将数据发送给uart3
	//v_hexdump ( buffer, BUFLEN );
}

static emCmdFuncStaType mapp_CmdfuncGetInputBackgroundInput ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	//emCmdFuncStaType l_state = emCmdNone;
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputBackgroundInput - eFunc_SetProductName - 1];

	char* token = strtok ( l_pCmd,"," );

	if (!strncmp ( l_pCmd,"-1",2 ) )
	{
		get_in_background_input ( pstval );
	}
	else
	{
		if ( token != NULL )
		{
			char buffer[BUFLEN] = {0};
			char value[32] = {0};
			char* p = buffer;

			sprintf ( p,"%s,","InBackgroundInput" );
			p += strlen ( p );

			if ( ( pstval->ch >> ( atoi ( token ) + 0x10 ) ) & 0x1 )
			{
				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d",atoi ( token ) );

				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;

				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[atoi ( token )][0]] );
				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;
			}

			sprintf ( p,"%s","EOF" );

			Uart3_printf ( "%s\r\n",buffer );
			dbg_printf ( "%s\r\n",buffer );

			//将数据发送给uart3
			//v_hexdump ( buffer, BUFLEN );

			token = strtok ( NULL,"," );
		}
	}

	return emCmdSucess;
}

void get_in_ducking_gain ( pststMachVal_t pstval )
{
	char buffer[BUFLEN] = {0};
	char value[32] = {0};
	char* p = buffer;

	sprintf ( p,"%s,","InDuckingGain" );
	p += strlen ( p );

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d",i );

			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;

			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d.%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[i][0]],pstval->param2[cg_u8_IN_ChannelTable[i][0]] );
			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;
		}
	}

	sprintf ( p,"%s","EOF" );

	Uart3_printf ( "%s\r\n",buffer );
	dbg_printf ( "%s\r\n",buffer );

	//将数据发送给uart3
	//v_hexdump ( buffer, BUFLEN );
}

static emCmdFuncStaType mapp_CmdfuncGetInputDuckingGain ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	//emCmdFuncStaType l_state = emCmdNone;
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputDuckingGain - eFunc_SetProductName - 1];

	char* token = strtok ( l_pCmd,"," );

	if (!strncmp ( l_pCmd,"-1",2 ) )
	{
		get_in_ducking_gain ( pstval );
	}
	else
	{
		if ( token != NULL )
		{
			char buffer[BUFLEN] = {0};
			char value[32] = {0};
			char* p = buffer;

			sprintf ( p,"%s,","InDuckingGain" );
			p += strlen ( p );

			if ( ( pstval->ch >> ( atoi ( token ) + 0x10 ) ) & 0x1 )
			{
				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d",atoi ( token ) );

				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;

				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d.%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[atoi ( token )][0]],pstval->param2[cg_u8_IN_ChannelTable[atoi ( token )][0]] );
				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;
			}

			sprintf ( p,"%s","EOF" );

			Uart3_printf ( "%s\r\n",buffer );
			dbg_printf ( "%s\r\n",buffer );

			//将数据发送给uart3
			//v_hexdump ( buffer, BUFLEN );

			token = strtok ( NULL,"," );
		}
	}

	return emCmdSucess;
}

void get_in_ducking_threshold ( pststMachVal_t pstval )
{
	char buffer[BUFLEN] = {0};
	char value[32] = {0};
	char* p = buffer;

	sprintf ( p,"%s,","InDuckingThreshold" );
	p += strlen ( p );

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d.%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[i][0]],pstval->param2[cg_u8_IN_ChannelTable[i][0]] );
			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;
			break;
		}
	}

	sprintf ( p,"%s","EOF" );

	Uart3_printf ( "%s\r\n",buffer );
	dbg_printf ( "%s\r\n",buffer );

	//将数据发送给uart3
	//v_hexdump ( buffer, BUFLEN );
}

static emCmdFuncStaType mapp_CmdfuncGetInputDuckingThreshold ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	//emCmdFuncStaType l_state = emCmdNone;
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputDuckingThreshold - eFunc_SetProductName - 1];

	char* token = strtok ( l_pCmd,"," );

	if (!strncmp ( l_pCmd,"-1",2 ) )
	{
		get_in_ducking_threshold ( pstval );
	}
	else
	{
		if ( ( pstval->ch >> ( atoi ( token ) + 0x10 ) ) & 0x1 )
		{
			char buffer[BUFLEN] = {0};
			char value[32] = {0};
			char* p = buffer;
			char* token = strtok ( l_pCmd,"," );

			sprintf ( p,"%s,","InDuckingThreshold" );
			p += strlen ( p );

			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d.%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[0][0]],pstval->param2[cg_u8_IN_ChannelTable[0][0]] );
			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;

			sprintf ( p,"%s","EOF" );

			Uart3_printf ( "%s\r\n",buffer );
			dbg_printf ( "%s\r\n",buffer );

			//将数据发送给uart3
			//v_hexdump ( buffer, BUFLEN );
		}
	}

	return emCmdSucess;
}

void get_in_ducking_depth ( pststMachVal_t pstval )
{
	char buffer[BUFLEN] = {0};
	char value[32] = {0};
	char* p = buffer;

	sprintf ( p,"%s,","InDuckingDepth" );
	p += strlen ( p );

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d.%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[i][0]],pstval->param2[cg_u8_IN_ChannelTable[i][0]] );
			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;
			break;
		}
	}

	sprintf ( p,"%s","EOF" );

	Uart3_printf ( "%s\r\n",buffer );
	dbg_printf ( "%s\r\n",buffer );

	//将数据发送给uart3
	//v_hexdump ( buffer, BUFLEN );
}

static emCmdFuncStaType mapp_CmdfuncGetInputDuckingDepth ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	//emCmdFuncStaType l_state = emCmdNone;
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputDuckingDepth - eFunc_SetProductName - 1];

	char* token = strtok ( l_pCmd,"," );

	if (!strncmp ( l_pCmd,"-1",2 ) )
	{
		get_in_ducking_depth ( pstval );
	}
	else
	{
		if ( ( pstval->ch >> ( atoi ( token ) + 0x10 ) ) & 0x1 )
		{
			char buffer[BUFLEN] = {0};
			char value[32] = {0};
			char* p = buffer;

			sprintf ( p,"%s,","InDuckingDepth" );
			p += strlen ( p );

			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d.%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[0][0]],pstval->param2[cg_u8_IN_ChannelTable[0][0]] );
			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;

			sprintf ( p,"%s","EOF" );

			Uart3_printf ( "%s\r\n",buffer );
			dbg_printf ( "%s\r\n",buffer );

			//将数据发送给uart3
			//v_hexdump ( buffer, BUFLEN );
		}
	}

	return emCmdSucess;
}

void get_in_ducking_start_time ( pststMachVal_t pstval )
{
	char buffer[BUFLEN] = {0};
	char value[32] = {0};
	char* p = buffer;

	sprintf ( p,"%s,","InDuckingStartTime" );
	p += strlen ( p );

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d", pstval->param1[cg_u8_IN_ChannelTable[i][0]] );
			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;
			break;
		}
	}

	sprintf ( p,"%s","EOF" );

	Uart3_printf ( "%s\r\n",buffer );
	dbg_printf ( "%s\r\n",buffer );

	//将数据发送给uart3
	//v_hexdump ( buffer, BUFLEN );
}

static emCmdFuncStaType mapp_CmdfuncGetInputDuckingStartTime ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	//emCmdFuncStaType l_state = emCmdNone;
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputDuckingStartTime - eFunc_SetProductName - 1];

	char* token = strtok ( l_pCmd,"," );

	if (!strncmp ( l_pCmd,"-1",2 ) )
	{
		get_in_ducking_start_time ( pstval );
	}
	else
	{
		if ( ( pstval->ch >> ( atoi ( token ) + 0x10 ) ) & 0x1 )
		{
			char buffer[BUFLEN] = {0};
			char value[32] = {0};
			char* p = buffer;

			sprintf ( p,"%s,","InDuckingStartTime" );
			p += strlen ( p );

			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[0][0]] );
			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;

			sprintf ( p,"%s","EOF" );

			Uart3_printf ( "%s\r\n",buffer );
			dbg_printf ( "%s\r\n",buffer );

			//将数据发送给uart3
			//v_hexdump ( buffer, BUFLEN );
		}
	}

	return emCmdSucess;
}

void get_in_ducking_hold_time ( pststMachVal_t pstval )
{

	char buffer[BUFLEN] = {0};
	char value[32] = {0};
	char* p = buffer;

	sprintf ( p,"%s,","InDuckingHoldTime" );
	p += strlen ( p );

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d", pstval->param1[cg_u8_IN_ChannelTable[i][0]] );
			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;
			break;
		}
	}

	sprintf ( p,"%s","EOF" );

	Uart3_printf ( "%s\r\n",buffer );
	dbg_printf ( "%s\r\n",buffer );

	//将数据发送给uart3
	//v_hexdump ( buffer, BUFLEN );
}

static emCmdFuncStaType mapp_CmdfuncGetInputDuckingHoldTime ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	//emCmdFuncStaType l_state = emCmdNone;
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputDuckingHoldTime - eFunc_SetProductName - 1];

	char* token = strtok ( l_pCmd,"," );

	if (!strncmp ( l_pCmd,"-1",2 ) )
	{
		get_in_ducking_hold_time ( pstval );
	}
	else
	{
		if ( ( pstval->ch >> ( atoi ( token ) + 0x10 ) ) & 0x1 )
		{
			char buffer[BUFLEN] = {0};
			char value[32] = {0};
			char* p = buffer;

			sprintf ( p,"%s,","InDuckingHoldTime" );
			p += strlen ( p );

			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[0][0]] );
			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;

			sprintf ( p,"%s","EOF" );

			Uart3_printf ( "%s\r\n",buffer );
			dbg_printf ( "%s\r\n",buffer );

			//将数据发送给uart3
			//v_hexdump ( buffer, BUFLEN );
		}
	}

	return emCmdSucess;
}

void get_in_ducking_rel_time ( pststMachVal_t pstval )
{
	char buffer[BUFLEN] = {0};
	char value[32] = {0};
	char* p = buffer;

	sprintf ( p,"%s,","InDuckingReleaseTime" );
	p += strlen ( p );

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d", pstval->param1[cg_u8_IN_ChannelTable[i][0]] );

			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;
			break;
		}
	}

	sprintf ( p,"%s","EOF" );

	Uart3_printf ( "%s\r\n",buffer );
	dbg_printf ( "%s\r\n",buffer );

	//将数据发送给uart3
	//v_hexdump ( buffer, BUFLEN );
}

static emCmdFuncStaType mapp_CmdfuncGetInputDuckingReleasetime ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	//emCmdFuncStaType l_state = emCmdNone;
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputDuckingReleaseTime - eFunc_SetProductName - 1];

	char* token = strtok ( l_pCmd,"," );

	if (!strncmp ( l_pCmd,"-1",2 ) )
	{
		get_in_ducking_rel_time ( pstval );
	}
	else
	{
		if ( ( pstval->ch >> ( atoi ( token ) + 0x10 ) ) & 0x1 )
		{
			char buffer[BUFLEN] = {0};
			char value[32] = {0};
			char* p = buffer;

			sprintf ( p,"%s,","InDuckingReleaseTime" );
			p += strlen ( p );

			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[0][0]] );

			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;

			sprintf ( p,"%s","EOF" );

			Uart3_printf ( "%s\r\n",buffer );
			dbg_printf ( "%s\r\n",buffer );

			//将数据发送给uart3
			//v_hexdump ( buffer, BUFLEN );
		}
	}

	return emCmdSucess;
}

void get_in_ducking_ctrl ( pststMachVal_t pstval )
{
	char buffer[BUFLEN] = {0};
	char value[32] = {0};
	char* p = buffer;

	sprintf ( p,"%s,","InDuckingCtrl" );
	p += strlen ( p );

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d", pstval->param1[cg_u8_IN_ChannelTable[i][0]] );
			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;
			break;
		}
	}

	sprintf ( p,"%s","EOF" );

	Uart3_printf ( "%s\r\n",buffer );
	dbg_printf ( "%s\r\n",buffer );

	//将数据发送给uart3
	//v_hexdump ( buffer, BUFLEN );
}

static emCmdFuncStaType mapp_CmdfuncGetInputDuckingCtrl ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	//emCmdFuncStaType l_state = emCmdNone;
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputDuckingCtrl - eFunc_SetProductName - 1];

	char* token = strtok ( l_pCmd,"," );

	if (!strncmp ( l_pCmd,"-1",2 ) )
	{
		get_in_ducking_ctrl ( pstval );
	}
	else
	{
		if ( ( pstval->ch >> ( atoi ( token ) + 0x10 ) ) & 0x1 )
		{
			char buffer[BUFLEN] = {0};
			char value[32] = {0};
			char* p = buffer;

			sprintf ( p,"%s,","InDuckingCtrl" );
			p += strlen ( p );

			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[0][0]] );

			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;

			sprintf ( p,"%s","EOF" );

			Uart3_printf ( "%s\r\n",buffer );
			dbg_printf ( "%s\r\n",buffer );

			//将数据发送给uart3
			//v_hexdump ( buffer, BUFLEN );
			return emCmdSucess;
		}
	}

	return emCmdSucess;
}


void get_matrixswitch ( pststMachVal_t pstval )
{
	char buffer[BUFLEN] = {0};
	char value[8] = {0};
	char* p = buffer;
	unsigned char hasvalue = 0;

	sprintf ( p,"%s,","MatrixSwitching" );
	p += strlen ( p );

	for ( u8 i = 0,m = 0; i < MAX_CH_LEN; i++ )
	{
		if ( ( pstval->ch >> i  ) & 0x1 )
		{
			if ( hasvalue )
			{
				sprintf ( p,"%s,","MatrixSwitching" );
				p += strlen ( p );
			}

			hasvalue = 1;

			for ( m = 0; m < MAX_CH_LEN ; m++ )
			{
				//输出已经打开的矩阵
				if ( ( pstval->param1[i] >> m ) & 0x1 )
				{
					memset ( value,0,sizeof ( value ) );
					sprintf ( value,"%d", i );
					sprintf ( p,"%s,",value );
					p += strlen ( value ) + 1;

					memset ( value,0,sizeof ( value ) );
					sprintf ( value,"%d", m );
					sprintf ( p,"%s,",value );
					p += strlen ( value ) + 1;

					memset ( value,0,sizeof ( value ) );
					sprintf ( value,"%d", 1 );               //打开
					sprintf ( p,"%s,",value );
					p += strlen ( value ) + 1;
				}

				//输出已经关闭的矩阵
				if ( ( pstval->param2[i] >> m ) & 0x1 )
				{
					memset ( value,0,sizeof ( value ) );
					sprintf ( value,"%d", i );
					sprintf ( p,"%s,",value );
					p += strlen ( value ) + 1;

					memset ( value,0,sizeof ( value ) );
					sprintf ( value,"%d", m );
					sprintf ( p,"%s,",value );
					p += strlen ( value ) + 1;

					memset ( value,0,sizeof ( value ) );
					sprintf ( value,"%d", 0 );             //关闭
					sprintf ( p,"%s,",value );
					p += strlen ( value ) + 1;
				}
			}

			sprintf ( p,"%s","EOF" );
			dbg_printf ( "%s\r\n",buffer );

			memset ( buffer,0,sizeof ( buffer ) );
			p = buffer;
		}
	}

	if (!hasvalue )
	{
		sprintf ( p,"%s","EOF" );
		dbg_printf ( "%s\r\n",buffer );
	}
}

static emCmdFuncStaType mapp_CmdfuncGetMatrixSwitching ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	//emCmdFuncStaType l_state = emCmdNone;
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetMatrixSwitching - eFunc_SetProductName - 1];

	char* token = strtok ( l_pCmd,"," );

	if (!strncmp ( l_pCmd,"-1",2 ) )
	{
		get_matrixswitch ( pstval );
	}
	else
	{
		if ( token != NULL )
		{

			token = strtok ( NULL,"," );
		}
	}

	return emCmdSucess;
}

void get_out_delay_time ( pststMachVal_t pstval )
{
	char buffer[BUFLEN] = {0};
	char value[32] = {0};
	char* p = buffer;

	sprintf ( p,"%s,","OutDelayTime" );
	p += strlen ( p );

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d",i );

			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;

			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d", pstval->param1[cg_u8_OUT_ChannelTable[i][0]] );

			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;
		}
	}

	sprintf ( p,"%s","EOF" );

	Uart3_printf ( "%s\r\n",buffer );
	dbg_printf ( "%s\r\n",buffer );

	//将数据发送给uart3
	//v_hexdump ( buffer, BUFLEN );
}

static emCmdFuncStaType mapp_CmdfuncGetOutputDelayTime ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	//emCmdFuncStaType l_state = emCmdNone;
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetOutputDelayTime - eFunc_SetProductName - 1];

	char* token = strtok ( l_pCmd,"," );

	if (!strncmp ( l_pCmd,"-1",2 ) )
	{
		get_out_delay_time ( pstval );
	}
	else
	{
		if ( token != NULL )
		{
			char buffer[BUFLEN] = {0};
			char value[32] = {0};
			char* p = buffer;

			sprintf ( p,"%s,","OutDelayTime" );
			p += strlen ( p );

			if ( ( pstval->ch >> ( atoi ( token ) + 0x10 ) ) & 0x1 )
			{
				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d",atoi ( token ) );

				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;

				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d", ( int8_t ) pstval->param1[cg_u8_OUT_ChannelTable[atoi ( token )][0]] );

				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;
			}

			sprintf ( p,"%s","EOF" );

			Uart3_printf ( "%s\r\n",buffer );
			dbg_printf ( "%s\r\n",buffer );

			//将数据发送给uart3
			//v_hexdump ( buffer, BUFLEN );

			token = strtok ( NULL,"," );
		}
	}

	return emCmdSucess;
}


void get_out_delay_ctrl ( pststMachVal_t pstval )
{
	char buffer[BUFLEN] = {0};
	char value[32] = {0};
	char* p = buffer;

	sprintf ( p,"%s,","OutDelayCtrl" );
	p += strlen ( p );

	for ( u8 i = 0; i < MAX_CH_LEN ; i++ )
	{
		if ( ( pstval->ch >> ( i + 0x10 ) ) & 0x1 )
		{
			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d",i );

			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;

			memset ( value,0,sizeof ( value ) );
			sprintf ( value,"%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[i][0]] );

			sprintf ( p,"%s,",value );
			p += strlen ( value ) + 1;
		}
	}

	sprintf ( p,"%s","EOF" );

	Uart3_printf ( "%s\r\n",buffer );
	dbg_printf ( "%s\r\n",buffer );

	//将数据发送给uart3
	//v_hexdump ( buffer, BUFLEN );
}

static emCmdFuncStaType mapp_CmdfuncGetOutputDelayCtrl ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	//emCmdFuncStaType l_state = emCmdNone;
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetOutputDelayCtrl - eFunc_SetProductName - 1];

	char* token = strtok ( l_pCmd,"," );

	if (!strncmp ( l_pCmd,"-1",2 ) )
	{
		get_out_delay_ctrl ( pstval );
	}
	else
	{
		if ( token != NULL )
		{
			char buffer[BUFLEN] = {0};
			char value[32] = {0};
			char* p = buffer;

			sprintf ( p,"%s,","OutDelayCtrl" );
			p += strlen ( p );

			if ( ( pstval->ch >> ( atoi ( token ) + 0x10 ) ) & 0x1 )
			{
				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d",atoi ( token ) );

				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;

				memset ( value,0,sizeof ( value ) );
				sprintf ( value,"%d", ( int8_t ) pstval->param1[cg_u8_IN_ChannelTable[atoi ( token )][0]] );

				sprintf ( p,"%s,",value );
				p += strlen ( value ) + 1;
			}

			sprintf ( p,"%s","EOF" );

			Uart3_printf ( "%s\r\n",buffer );
			dbg_printf ( "%s\r\n",buffer );

			//将数据发送给uart3
			//v_hexdump ( buffer, BUFLEN );

			token = strtok ( NULL,"," );
		}
	}

	return emCmdSucess;
}

void get_usbplayer_ctrl ( pststMachVal_t pstval )
{
	char buffer[BUFLEN] = {0};
	char value[32] = {0};
	char* p = buffer;

	sprintf ( p,"%s,","USBplayerCtrl" );
	p += strlen ( p );

	memset ( value,0,sizeof ( value ) );
	sprintf ( value,"%d", ( int8_t ) pstval->param1[0] );
	sprintf ( p,"%s,",value );
	p += strlen ( value ) + 1;

	memset ( value,0,sizeof ( value ) );
	sprintf ( value,"%d", ( int8_t ) pstval->param2[0] );
	sprintf ( p,"%s,",value );
	p += strlen ( value ) + 1;

	sprintf ( p,"%s","EOF" );

	Uart3_printf ( "%s\r\n",buffer );
	dbg_printf ( "%s\r\n",buffer );

	//将数据发送给uart3
	//v_hexdump ( buffer, BUFLEN );
}

static emCmdFuncStaType mapp_CmdfuncGetUSBplayerCtrl ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	//emCmdFuncStaType l_state = emCmdNone;
	char* l_pCmd= pCommVar->pRecBuffer + strlen ( cmd_list[cmdnum].ucmd );
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetUSBplayerCtrl - eFunc_SetProductName - 1];

	get_usbplayer_ctrl ( pstval );
	return emCmdSucess;
}

//返回
static emCmdFuncStaType mapp_CmdfuncGetAllData ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	for ( u8 i= ( eFunc_SetAllAudioOutput - eFunc_SetProductName - 1 ); i <= ( eFunc_SetUSBplayerCtrl - eFunc_SetProductName - 1 ); i++ )
	{
		switch ( i )
		{
			case eFunc_SetAllAudioOutput - eFunc_SetProductName - 1:
			{
				pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
				pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetAllAudioOutput - eFunc_SetProductName - 1];
				get_all_audio_output ( pstval );
				continue;
			}
			case eFunc_SetInputSensitivity - eFunc_SetProductName - 1:
			{
				pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
				pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputSensitivity - eFunc_SetProductName - 1];
				get_in_sensitivity ( pstval );
				continue;
			}
			case eFunc_SetInputGain - eFunc_SetProductName - 1:
			{
				pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
				pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputGain - eFunc_SetProductName - 1];
				get_in_gain ( pstval );
				continue;
			}
			case eFunc_SetInputMute - eFunc_SetProductName - 1:
			{
				pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
				pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputMute - eFunc_SetProductName - 1];
				get_in_mute ( pstval );
				continue;
			}
			case eFunc_SetInputReversephase - eFunc_SetProductName - 1:
			{
				pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
				pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputReversephase - eFunc_SetProductName - 1];
				get_in_reversephase ( pstval );
				continue;
			}
			case eFunc_SetInputTestSignalCtrl - eFunc_SetProductName - 1:
			{
				pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
				pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputTestSignalCtrl - eFunc_SetProductName - 1];
				get_in_test_signal_ctrl ( pstval );
				continue;
			}
			case eFunc_SetInputTestSignalFreq - eFunc_SetProductName - 1:
			{
				pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
				pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputTestSignalFreq - eFunc_SetProductName - 1];
				get_in_test_signal_freq ( pstval );
				continue;
			}
			case eFunc_SetInputTestSignalLevel - eFunc_SetProductName - 1:
			{
				pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
				pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputTestSignalLevel - eFunc_SetProductName - 1];
				get_in_test_signal_level ( pstval );
				continue;
			}
			case eFunc_SetInputCompressorCtrl - eFunc_SetProductName - 1:
			{
				pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
				pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputCompressorCtrl - eFunc_SetProductName - 1];
				get_in_compressor_ctrl ( pstval );
				continue;
			}
			case eFunc_SetInputCompressorGain - eFunc_SetProductName - 1:
			{
				pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
				pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputCompressorGain - eFunc_SetProductName - 1];
				get_in_compressor_gain ( pstval );
				continue;
			}
			case eFunc_SetInputCompressorThreshold - eFunc_SetProductName - 1:
			{
				pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
				pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputCompressorThreshold - eFunc_SetProductName - 1];
				get_in_compressor_threshold ( pstval );
				continue;
			}
			case eFunc_SetInputCompressorRatio - eFunc_SetProductName - 1:
			{
				pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
				pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputCompressorRatio - eFunc_SetProductName - 1];
				get_in_compressor_ratio ( pstval );
				continue;
			}
			case eFunc_SetInputCompressorStartTime - eFunc_SetProductName - 1:
			{
				pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
				pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputCompressorStartTime - eFunc_SetProductName - 1];
				get_in_compressor_start_time ( pstval );
				continue;
			}
			case eFunc_SetInputCompressorReleaseTime - eFunc_SetProductName - 1:
			{
				pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
				pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputCompressorReleaseTime - eFunc_SetProductName - 1];
				get_in_compressor_rel_time ( pstval );
				continue;
			}
			case eFunc_SetInputAutoGainCtrl - eFunc_SetProductName - 1:
			{
				pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
				pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputAutoGainCtrl - eFunc_SetProductName - 1];
				get_in_auto_gain_ctrl ( pstval );
				continue;
			}
			case eFunc_SetInputAutoGainThreshold - eFunc_SetProductName - 1:
			{
				pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
				pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputAutoGainThreshold - eFunc_SetProductName - 1];
				get_in_auto_gain_threshold ( pstval );
				continue;
			}
			case eFunc_SetInputAutoGainTargetThreshold - eFunc_SetProductName - 1:
			{
				pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
				pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputAutoGainTargetThreshold - eFunc_SetProductName - 1];
				get_in_auto_gain_target_threshold ( pstval );
				continue;
			}
			case eFunc_SetInputAutoGainRatio - eFunc_SetProductName - 1:
			{
				pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
				pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputAutoGainRatio - eFunc_SetProductName - 1];
				get_in_auto_gain_ratio ( pstval );
				continue;
			}
			case eFunc_SetInputAutoGainStartTime - eFunc_SetProductName - 1:
			{
				pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
				pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputAutoGainStartTime - eFunc_SetProductName - 1];
				get_in_auto_gain_start_time ( pstval );
				continue;
			}
			case eFunc_SetInputAutoGainReleaseTime - eFunc_SetProductName - 1:
			{
				pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
				pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputAutoGainReleaseTime - eFunc_SetProductName - 1];
				get_in_auto_gain_rel_time ( pstval );
				continue;
			}
			case eFunc_SetInputEQType - eFunc_SetProductName - 1:
			{
				pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
				pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputEQType - eFunc_SetProductName - 1];
				get_in_EQ_type ( pstval );
				continue;
			}
			case eFunc_SetInputEQGain - eFunc_SetProductName - 1:
			{
				pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
				pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputEQGain - eFunc_SetProductName - 1];
				get_in_EQ_gain ( pstval );
				continue;
			}
			case eFunc_SetInputEQQualityFactor - eFunc_SetProductName - 1:
			{
				pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
				pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputEQQualityFactor - eFunc_SetProductName - 1];
				get_in_EQ_quality_factor ( pstval );
				continue;
			}
			case eFunc_SetInputEQCtrl - eFunc_SetProductName - 1:
			{
				pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
				pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputEQCtrl - eFunc_SetProductName - 1];
				get_in_EQ_ctrl ( pstval );
				continue;
			}
			case eFunc_SetInputHowlingSuppressorCtrl - eFunc_SetProductName - 1:
			{
				pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
				pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputHowlingSuppressorCtrl - eFunc_SetProductName - 1];
				get_in_howling_suppressor_ctrl ( pstval );
				continue;
			}
			case eFunc_SetInputHowlingSuppressorGrade - eFunc_SetProductName - 1:
			{
				pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
				pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputHowlingSuppressorGrade - eFunc_SetProductName - 1];
				get_in_howling_suppressor_grade ( pstval );
				continue;
			}
			case eFunc_SetInputHowlingSuppressorFreqShift - eFunc_SetProductName - 1:
			{
				pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
				pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputHowlingSuppressorFreqShift - eFunc_SetProductName - 1];
				get_in_howling_suppressor_freq_shift ( pstval );
				continue;
			}
			case eFunc_SetInputNoiseSuppressorGrade - eFunc_SetProductName - 1:
			{
				pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
				pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputNoiseSuppressorGrade - eFunc_SetProductName - 1];
				get_in_noise_suppressor_grade ( pstval );
				continue;
			}
			case eFunc_SetInputNoiseSuppressorThreshold - eFunc_SetProductName - 1:
			{
				pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
				pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputNoiseSuppressorThreshold - eFunc_SetProductName - 1];
				get_in_noise_suppressor_threshold ( pstval );
				continue;
			}
			case eFunc_SetInputNoiseSuppressorRatio - eFunc_SetProductName - 1:
			{
				pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
				pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputNoiseSuppressorRatio - eFunc_SetProductName - 1];
				get_in_noise_suppressor_ratio ( pstval );
				continue;
			}
			case eFunc_SetInputNoiseSuppressorStartTime - eFunc_SetProductName - 1:
			{
				pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
				pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputNoiseSuppressorStartTime - eFunc_SetProductName - 1];
				get_in_noise_suppressor_start_time ( pstval );
				continue;
			}
			case eFunc_SetInputNoiseSuppressorReleaseTime - eFunc_SetProductName - 1:
			{
				pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
				pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputNoiseSuppressorReleaseTime - eFunc_SetProductName - 1];
				get_in_noise_suppressor_rel_time ( pstval );
				continue;
			}
			case eFunc_SetInputNoiseSuppressorCtrl - eFunc_SetProductName - 1:
			{
				pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
				pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputNoiseSuppressorCtrl - eFunc_SetProductName - 1];
				get_in_noise_suppressor_ctrl ( pstval );
				continue;
			}
			case eFunc_SetInputEchoCancellerGrade - eFunc_SetProductName - 1:
			{
				pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
				pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputEchoCancellerGrade - eFunc_SetProductName - 1];
				get_in_echo_canceller_grade ( pstval );
				continue;
			}
			case eFunc_SetInputEchoCancellerCtrl - eFunc_SetProductName - 1:
			{
				pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
				pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputEchoCancellerCtrl - eFunc_SetProductName - 1];
				get_in_echo_canceller_ctrl ( pstval );
				continue;
			}
			case eFunc_SetInputLfreqExciterGrade - eFunc_SetProductName - 1:
			{
				pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
				pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputLfreqExciterGrade - eFunc_SetProductName - 1];
				get_in_l_freq_exciter_grade ( pstval );
				continue;
			}
			case eFunc_SetInputHfreqExciterGrade - eFunc_SetProductName - 1:
			{
				pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
				pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputHfreqExciterGrade - eFunc_SetProductName - 1];
				get_in_h_freq_exciter_grade ( pstval );
				continue;
			}
			case eFunc_SetInputExciterCtrl - eFunc_SetProductName - 1:
			{
				pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
				pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputExciterCtrl - eFunc_SetProductName - 1];
				get_in_exciter_ctrl ( pstval );
				continue;
			}
			case eFunc_SetInputCallInput - eFunc_SetProductName - 1:
			{
				pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
				pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputCallInput - eFunc_SetProductName - 1];
				get_in_call_input ( pstval );
				continue;
			}
			case eFunc_SetInputBackgroundInput - eFunc_SetProductName - 1:
			{
				pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
				pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputBackgroundInput - eFunc_SetProductName - 1];
				get_in_background_input ( pstval );
				continue;
			}
			case eFunc_SetInputDuckingGain - eFunc_SetProductName - 1:
			{
				pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
				pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputDuckingGain - eFunc_SetProductName - 1];
				get_in_ducking_gain ( pstval );
				continue;
			}
			case eFunc_SetInputDuckingThreshold - eFunc_SetProductName - 1:
			{
				pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
				pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputDuckingThreshold - eFunc_SetProductName - 1];
				get_in_ducking_threshold ( pstval );
				continue;
			}
			case eFunc_SetInputDuckingDepth - eFunc_SetProductName - 1:
			{
				pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
				pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputDuckingDepth - eFunc_SetProductName - 1];
				get_in_ducking_depth ( pstval );
				continue;
			}
			case eFunc_SetInputDuckingStartTime - eFunc_SetProductName - 1:
			{
				pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
				pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputDuckingStartTime - eFunc_SetProductName - 1];
				get_in_ducking_start_time ( pstval );
				continue;
			}
			case eFunc_SetInputDuckingHoldTime - eFunc_SetProductName - 1:
			{
				pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
				pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputDuckingHoldTime - eFunc_SetProductName - 1];
				get_in_ducking_hold_time ( pstval );
				continue;
			}
			case eFunc_SetInputDuckingReleaseTime - eFunc_SetProductName - 1:
			{
				pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
				pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputDuckingReleaseTime - eFunc_SetProductName - 1];
				get_in_ducking_rel_time ( pstval );
				continue;
			}
			case eFunc_SetInputDuckingCtrl - eFunc_SetProductName - 1:
			{
				pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
				pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetInputDuckingCtrl - eFunc_SetProductName - 1];
				get_in_ducking_ctrl ( pstval );
				continue;
			}
			case eFunc_SetMatrixSwitching - eFunc_SetProductName - 1:
			{
				pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
				pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetMatrixSwitching - eFunc_SetProductName - 1];
				get_matrixswitch ( pstval );
				continue;
			}
			case eFunc_SetOutputDelayTime - eFunc_SetProductName - 1:
			{
				pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
				pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetOutputDelayTime - eFunc_SetProductName - 1];
				get_out_delay_time ( pstval );
				continue;
			}
			case eFunc_SetOutputDelayCtrl - eFunc_SetProductName - 1:
			{
				pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
				pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetOutputDelayCtrl - eFunc_SetProductName - 1];
				get_out_delay_ctrl ( pstval );
				continue;
			}
			case eFunc_SetUSBplayerCtrl - eFunc_SetProductName - 1:
			{
				pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
				pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
				pststMachVal_t pstval = &pstPrjSaveVar->guiParamter[eFunc_SetUSBplayerCtrl - eFunc_SetProductName - 1];
				get_usbplayer_ctrl ( pstval );
				continue;
			}
		}
	}

	return emCmdSucess;
}

static emCmdFuncStaType  mapp_CmdfuncResetData ( pstUartCom_t pCommVar, uint8_t cmdnum )
{
	defaultValue();

	return emCmdSucess;
}

//add by hy 2024/12/18 END


//eFunc_GetVersion,
static emCmdFuncStaType mapp_CmdfuncGetVersion ( pstUartCom_t pCommVar, uint8_t cmdnum )
{

	return emCmdSucess;
}

//eFunc_FactoryReset,
static emCmdFuncStaType mapp_CmdfuncFactoryReset ( pstUartCom_t pCommVar,u8 cmdnum )
{

	return emCmdSucess;
}

//eFunc_Reboot,
static emCmdFuncStaType mapp_CmdfuncReboot ( pstUartCom_t pCommVar,u8 cmdnum )
{
	return emCmdSucess;
}

//eFunc_GetTestVersion,
static emCmdFuncStaType mapp_CmdfuncGetTestVersion ( pstUartCom_t pCommVar,u8 cmdnum )
{

	return emCmdSucess;
}

//eFunc_SwitchInputPort,
static emCmdFuncStaType mapp_CmdfuncSwitchInputPort ( pstUartCom_t pCommVar,u8 cmdnum )
{
	emCmdFuncStaType l_state = emCmdSucess;
	return l_state;

}

//eFunc_GetInputStutus,
static emCmdFuncStaType mapp_CmdfuncGetInputStutus ( pstUartCom_t pCommVar,u8 cmdnum )
{
	emCmdFuncStaType l_state = emCmdSucess;
	return l_state;
}

//eFunc_SetTxResolution,
static emCmdFuncStaType mapp_CmdfuncSetTxResolution ( pstUartCom_t pCommVar,u8 cmdnum )
{
	emCmdFuncStaType l_state = emCmdSucess;

	return l_state;
}
//eFunc_GetTxResolution,
static emCmdFuncStaType mapp_CmdfuncGetTxResolution ( pstUartCom_t pCommVar,u8 cmdnum )
{
	emCmdFuncStaType l_state = emCmdSucess;

	return l_state;
}

//eFunc_GetRxResolution,
static emCmdFuncStaType mapp_CmdfuncGetRxResolution ( pstUartCom_t pCommVar,u8 cmdnum )
{
	emCmdFuncStaType l_state = emCmdSucess;
	return l_state;
}

//eFunc_SetTxHdcpMode,
static emCmdFuncStaType mapp_CmdfuncSetTxHdcpMode ( pstUartCom_t pCommVar,u8 cmdnum )
{
	emCmdFuncStaType l_state = emCmdSucess;
	return l_state;
}


//eFunc_GetTxHdcpMode,
static emCmdFuncStaType mapp_CmdfuncGetTxHdcpMode ( pstUartCom_t pCommVar,u8 cmdnum )
{
	emCmdFuncStaType l_state = emCmdSucess;
	return l_state;
}

//eFunc_SetTxFormat,
static emCmdFuncStaType mapp_CmdfuncSetTxFormat ( pstUartCom_t pCommVar,u8 cmdnum )
{
	emCmdFuncStaType l_state = emCmdSucess;

	return l_state;
}


//eFunc_GetTxFormat,
static emCmdFuncStaType mapp_CmdfuncGetTxFormat ( pstUartCom_t pCommVar,u8 cmdnum )
{
	emCmdFuncStaType l_state = emCmdSucess;
	return l_state;
}


//eFunc_SetFreezeState,
static emCmdFuncStaType mapp_CmdfuncSetFreezeState ( pstUartCom_t pCommVar,u8 cmdnum )
{
	emCmdFuncStaType l_state = emCmdSucess;
	return l_state;
}

//eFunc_GetFreezeState
static emCmdFuncStaType mapp_CmdfuncGetFreezeState ( pstUartCom_t pCommVar,u8 cmdnum )
{
	emCmdFuncStaType l_state = emCmdSucess;

	return l_state;
}

//eFunc_SwitchFreeze,
static emCmdFuncStaType mapp_CmdfuncSwitchFreeze ( pstUartCom_t pCommVar,u8 cmdnum )
{
	emCmdFuncStaType l_state = emCmdSucess;

	return l_state;
}

//eFunc_SetBrightness,
static emCmdFuncStaType mapp_CmdfuncSetBrightness ( pstUartCom_t pCommVar,u8 cmdnum )
{
	emCmdFuncStaType l_state = emCmdSucess;

	return l_state;
}

//eFunc_GetBrightness,
static emCmdFuncStaType mapp_CmdfuncGetBrightness ( pstUartCom_t pCommVar,u8 cmdnum )
{
	emCmdFuncStaType l_state = emCmdSucess;
	return l_state;
}


//eFunc_SetContrast,
static emCmdFuncStaType mapp_CmdfuncSetContrast ( pstUartCom_t pCommVar,u8 cmdnum )
{
	emCmdFuncStaType l_state = emCmdSucess;

	return l_state;
}


//eFunc_GetContrast,
static emCmdFuncStaType mapp_CmdfuncGetContrast ( pstUartCom_t pCommVar,u8 cmdnum )
{
	emCmdFuncStaType l_state = emCmdSucess;
	return l_state;
}


//eFunc_SetSaturation,
static emCmdFuncStaType mapp_CmdfuncSetSaturation ( pstUartCom_t pCommVar,u8 cmdnum )
{
	emCmdFuncStaType l_state = emCmdSucess;

	return l_state;
}


//eFunc_GetSaturation,
static emCmdFuncStaType mapp_CmdfuncGetSaturation ( pstUartCom_t pCommVar,u8 cmdnum )
{
	emCmdFuncStaType l_state = emCmdSucess;

	return l_state;
}


//eFunc_SetHue,
static emCmdFuncStaType mapp_CmdfuncSetHue ( pstUartCom_t pCommVar,u8 cmdnum )
{
	emCmdFuncStaType l_state = emCmdSucess;
	return l_state;
}


//eFunc_GetHue,
static emCmdFuncStaType mapp_CmdfuncGetHue ( pstUartCom_t pCommVar,u8 cmdnum )
{
	emCmdFuncStaType l_state = emCmdSucess;

	return l_state;
}

//eFunc_SetRxEdidMode,
static emCmdFuncStaType mapp_CmdfuncSetRxEdidMode ( pstUartCom_t pCommVar,u8 cmdnum )
{
	emCmdFuncStaType l_state = emCmdSucess;
	return l_state;
}

//eFunc_UpdateUserEdid,
static emCmdFuncStaType mapp_CmdfuncUpdateUserEdid ( pstUartCom_t pCommVar,u8 cmdnum )
{
	emCmdFuncStaType l_state = emCmdSucess;
	return l_state;
}

//eFunc_GetTxEdidData
static emCmdFuncStaType mapp_CmdfuncGetTxEdidData ( pstUartCom_t pCommVar,u8 cmdnum )
{
	emCmdFuncStaType l_state = emCmdSucess;

	return l_state;
}

//eFunc_SetTxTiming
static emCmdFuncStaType mapp_CmdfuncSetTxTiming ( pstUartCom_t pCommVar,u8 cmdnum )
{
	emCmdFuncStaType l_state = emCmdSucess;

	return l_state;
}

//eFunc_SetTxPattern
static emCmdFuncStaType mapp_CmdfuncSetTxPattern ( pstUartCom_t pCommVar,u8 cmdnum )
{
	emCmdFuncStaType l_state = emCmdSucess;

	return l_state;
}

//eFunc_GetTxPattern,
static emCmdFuncStaType mapp_CmdfuncGetTxPattern ( pstUartCom_t pCommVar,u8 cmdnum )
{
	emCmdFuncStaType l_state = emCmdSucess;
	return l_state;
}

//eFunc_SetColor,
static emCmdFuncStaType mapp_CmdfuncSetColor ( pstUartCom_t pCommVar,u8 cmdnum )
{
	emCmdFuncStaType l_state = emCmdSucess;
	return l_state;
}

//eFunc_GetColor,
static emCmdFuncStaType mapp_CmdfuncGetColor ( pstUartCom_t pCommVar,u8 cmdnum )
{
	emCmdFuncStaType l_state = emCmdSucess;
	return l_state;
}

//eFunc_SetDebugEn
static emCmdFuncStaType mapp_CmdfuncSetDebugEn ( pstUartCom_t pCommVar,u8 cmdnum )
{
	emCmdFuncStaType l_state = emCmdSucess;

	return l_state;
}

//eFunc_SetMs1826Hold
static emCmdFuncStaType mapp_CmdfuncSetMs1826Hold ( pstUartCom_t pCommVar,u8 cmdnum )
{
	emCmdFuncStaType l_state = emCmdSucess;

	return l_state;
}

//eFunc_BypassSwitchPort
static emCmdFuncStaType mapp_CmdfuncBypassSwitchPort ( pstUartCom_t pCommVar,u8 cmdnum )
{
	emCmdFuncStaType l_state = emCmdSucess;
	return l_state;

}

//eFunc_ModeSwitch
static emCmdFuncStaType mapp_CmdfuncModeSwitch ( pstUartCom_t pCommVar,u8 cmdnum )
{
	emCmdFuncStaType l_state = emCmdSucess;
	return l_state;
}

//eFunc_FactoryReset2
static emCmdFuncStaType mapp_CmdfuncFactoryReset2 ( pstUartCom_t pCommVar,u8 cmdnum )
{
	return emCmdSucess;
}

//eFunc_CheckOutputCardType,
static emCmdFuncStaType mapp_CmdfuncCheckOutputCardType ( pstUartCom_t pCommVar,u8 cmdnum )
{
	emCmdFuncStaType l_state = emCmdSucess;
	return l_state;
}

//eFunc_CheckCardFWVersion
static emCmdFuncStaType mapp_CmdfuncCheckCardFWVersion ( pstUartCom_t pCommVar,u8 cmdnum )
{
	emCmdFuncStaType l_state = emCmdSucess;
	return l_state;
}

//eFunc_CheckYBJCardType
static emCmdFuncStaType mapp_CmdfuncCheckYBJCardType ( pstUartCom_t pCommVar,u8 cmdnum )
{
	emCmdFuncStaType l_state = emCmdSucess;
	return l_state;
}

//eFunc_CheckYBJ2CardType
static emCmdFuncStaType mapp_CmdfuncCheckYBJ2CardType ( pstUartCom_t pCommVar,u8 cmdnum )
{
	emCmdFuncStaType l_state = emCmdSucess;
	return l_state;
}

//eFunc_CheckCardMode
static emCmdFuncStaType mapp_CmdfuncCheckCardMode ( pstUartCom_t pCommVar,u8 cmdnum )
{
	emCmdFuncStaType l_state = emCmdSucess;
	return l_state;
}

//eFunc_CheckSetEdidData
static emCmdFuncStaType mapp_CmdfuncCheckSetEdidData ( pstUartCom_t pCommVar,u8 cmdnum )
{
	emCmdFuncStaType l_state = emCmdSucess;

	return l_state;
}

bool app_SwitchResolution ( u8 u8Tx,u8 u8ResID )
{
	bool l_bRetVal = FALSE;
	return l_bRetVal;
}

u8 app_GetCmdResolutionID ( u8 u8ResID )
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
void mapp_All_AudioOutput_Ctrl ( u8 OnOff )
{
	//u8 Command[6] = {0xAA,0x01,0,0,0,0};
	u8 Command[7] = {0x00,0xAA,0x01,1,1,1,1};
//	double number;
	Command[4] = OnOff;
//	Student_TypeDef student = {{0}, 0, {0}};
//	extract_number(str,&number);
//	dbg_printf("\r\n%s\r\n",json_str);
//	myJsonTest(json_str, &student);
	dbg_printf ( "All_AudioOutput:%d\r\n",OnOff );
	app_All_AudioOutput_Ctrl ( 0,Command );
	app_All_AudioOutput_Ctrl ( 1,Command );
}

void mapp_All_AudioOutput_Ctrl_v1 ( u8 OnOff )
{
	//u8 Command[6] = {0xAA,0x01,0,0,0,0};
	u8 Command[7] = {0x00,0xAA,0x01,1,1,1,1};
//	double number;
	Command[4] = OnOff;
//	Student_TypeDef student = {{0}, 0, {0}};
//	extract_number(str,&number);
//	dbg_printf("\r\n%s\r\n",json_str);
//	myJsonTest(json_str, &student);
	dbg_printf ( "All_AudioOutput:%d\r\n",OnOff );
	app_All_AudioOutput_Ctrl ( 0,Command );
	app_All_AudioOutput_Ctrl ( 1,Command );
}

/****************************************************
Function:    	mapp_SET_Input_Sensitivity
Description: 	输入源灵敏度
channel: 		输入通道
parameter1：		灵敏度(0dB、6dB、12dB、18dB、24dB、30dB、36dB、42dB、48dB)
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_Sensitivity ( u8 channel,u8 parameter1 )
{
	u8 Command[7] = {0x00,0xAA,0x02,0,0,0,0};
	u8 dev = cg_u8_IN_ChannelTable[channel][1];
	Command[3] = cg_u8_IN_ChannelTable[channel][0];
	Command[4] = parameter1;
	app_Input_Sensitivity ( dev, Command );
	dbg_printf ( "Input_Sensitivity,ch%d,parameter1:%d\r\n",channel,parameter1 );
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
void mapp_SET_Input_Gain ( u8 channel,u8 parameter1, u8 parameter2 )
{
	u8 Command[7] = {0x00,0xAA,0x03,0,0,0,0};
	u8 dev = cg_u8_IN_ChannelTable[channel][1];
	Command[3] = cg_u8_IN_ChannelTable[channel][0];
	Command[4] = parameter1;
	Command[5] = parameter2;
	app_Input_Gain ( dev,Command );

	char f[10];
	if ( parameter1&0x80 )
	{
		parameter1 = parameter1&0x7f;
		sprintf ( f,"-%.1f", ( float ) ( parameter1+parameter2/10.0 ) );
		dbg_printf ( "Input_Gain,ch:%d,value:%s\r\n", channel,f );
	}
	else
	{
		sprintf ( f,"%.1f", ( float ) ( parameter1+parameter2/10.0 ) );
		dbg_printf ( "Input_Gain,ch:%d,value:%s\r\n", channel, f );
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
void mapp_SET_Input_Mute ( u8 channel,u8 OnOff )
{
	u8 Command[7] = {0x00,0xAA,0x04,0,0,0,0};
	u8 dev = cg_u8_IN_ChannelTable[channel][1];
	Command[3] = cg_u8_IN_ChannelTable[channel][0];
	Command[4] = OnOff;
	app_Input_Mute ( dev,Command );
	dbg_printf ( "Input_Mute,ch%d,OnOff:%d\r\n",channel,OnOff );
}
/****************************************************
Function:    	mapp_SET_Input_Reverse_phase
Description: 	输入反相
channel: 		输入通道
parameter1：		0:关闭反相,1:打开反相
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_Reverse_phase ( u8 channel,u8 OnOff )
{
	u8 Command[7] = {0x00,0xAA,0x05,0,0,0,0};
	u8 dev = cg_u8_IN_ChannelTable[channel][1];
	Command[3] = cg_u8_IN_ChannelTable[channel][0];
	Command[4] = OnOff;
	app_Input_Reverse_phase ( dev,Command );
	dbg_printf ( "Input_Reverse_phase,ch%d,OnOff:%d\r\n",channel,OnOff );
}
/****************************************************
Function:    	mapp_SET_Input_Test_Signal_Freq
Description: 	输入通道测试信号开关
channel: 		输入通道
OnOff			0:关闭,1:打开
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_TestSignal_Ctrl ( u8 channel,u8 OnOff )
{
	u8 Command[7] = {0x00,0xAA,0x06,0,0,0,0};
	u8 dev = cg_u8_IN_ChannelTable[channel][1];
	Command[3] = cg_u8_IN_ChannelTable[channel][0];
	Command[4] = OnOff;
	app_Input_TestSignal_Ctrl ( dev,Command );
	dbg_printf ( "Input_TestSignal,ch%d,OnOff:%d\r\n",channel,OnOff );
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
void mapp_SET_Input_TestSignal_Freq ( u8 channel,u8 parameter1, u8 parameter2 )
{
	u8 Command[7] = {0x00,0xAA,0x07,0,0,0,0};
	u8 dev = cg_u8_IN_ChannelTable[channel][1];
	Command[3] = cg_u8_IN_ChannelTable[channel][0];
	Command[4] = parameter1;
	Command[5] = parameter2;
	app_Input_TestSignal_Freq ( dev,Command );
	dbg_printf ( "Input_TestSignal_Freq,ch%d,freq:%d\r\n",channel, ( parameter1<<8 )+parameter2 );
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
void mapp_SET_Input_TestSignal_Level ( u8 channel,u8 parameter1, u8 parameter2 )
{
	u8 Command[7] = {0x00,0xAA,0x08,0,0,0,0};
	u8 dev = cg_u8_IN_ChannelTable[channel][1];
	Command[3] = cg_u8_IN_ChannelTable[channel][0];
	Command[4] = parameter1;
	Command[5] = parameter2;
	char f[10];
	app_Input_TestSignal_Level ( dev, Command );
	if ( parameter1&0x80 )
	{
		parameter1 = parameter1&0x7f;
		sprintf ( f,"-%.1f", ( float ) ( parameter1+parameter2/10.0 ) );
		dbg_printf ( "TestSignal_Level,ch:%d,value:%s\r\n", channel,f );
	}
	else
	{
		sprintf ( f,"%.1f", ( float ) ( parameter1+parameter2/10.0 ) );
		dbg_printf ( "TestSignal_Level,ch:%d,value:%s\r\n", channel, f );
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
void mapp_SET_Input_Compressor_Ctrl ( u8 channel,u8 OnOff )
{
	u8 Command[7] = {0x00,0xAA,0x09,0,0,0,0};
	u8 dev = cg_u8_IN_ChannelTable[channel][1];
	Command[3] = cg_u8_IN_ChannelTable[channel][0];
	Command[4] = OnOff;
	app_Input_Compressor_Ctrl ( dev, Command );
	dbg_printf ( "Input_Compressor,ch%d,OnOff:%d\r\n",channel,OnOff );
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
void mapp_SET_Input_Compressor_Gain ( u8 channel,u8 parameter1,u8 parameter2 )
{
	u8 Command[7] = {0x00,0xAA,0x0a,0,0,0,0};
	u8 dev = cg_u8_IN_ChannelTable[channel][1];
	Command[3] = cg_u8_IN_ChannelTable[channel][0];
	Command[4] = parameter1;
	Command[5] = parameter2;
	char f[10];
	app_Input_Compressor_Gain ( dev, Command );
	if ( parameter1&0x80 )
	{
		parameter1 = parameter1&0x7f;
		sprintf ( f,"-%.1f", ( float ) ( parameter1+parameter2/10.0 ) );
		dbg_printf ( "Compressor_Gain,ch:%d,value:%s\r\n", channel,f );
	}
	else
	{
		sprintf ( f,"%.1f", ( float ) ( parameter1+parameter2/10.0 ) );
		dbg_printf ( "Compressor_Gain,ch:%d,value:%s\r\n", channel, f );
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
void mapp_SET_Input_Compressor_Threshold ( u8 channel,u8 parameter1,u8 parameter2 )
{
	u8 Command[7] = {0x00,0xAA,0x0b,0,0,0,0};
	u8 dev = cg_u8_IN_ChannelTable[channel][1];
	Command[3] = cg_u8_IN_ChannelTable[channel][0];
	Command[4] = parameter1;
	Command[5] = parameter2;
	char f[10];
	app_Input_Compressor_Threshold ( dev, Command );
	if ( parameter1&0x80 )
	{
		parameter1 = parameter1&0x7f;
		sprintf ( f,"-%.1f", ( float ) ( parameter1+parameter2/10.0 ) );
		dbg_printf ( "Compressor_Threshold,ch:%d,value:%s\r\n", channel,f );
	}
	else
	{
		sprintf ( f,"%.1f", ( float ) ( parameter1+parameter2/10.0 ) );
		dbg_printf ( "Compressor_Threshold,ch:%d,value:%s\r\n", channel, f );
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
void mapp_SET_Input_Compressor_Ratio ( u8 channel,u8 parameter1,u8 parameter2 )
{
	u8 Command[7] = {0x00,0xAA,0x0c,0,0,0,0};
	u8 dev = cg_u8_IN_ChannelTable[channel][1];
	Command[3] = cg_u8_IN_ChannelTable[channel][0];
	Command[4] = parameter1;
	Command[5] = parameter2;
	char f[10];
	app_Input_Compressor_Ratio ( dev, Command );
	if ( parameter1&0x80 )
	{
		parameter1 = parameter1&0x7f;
		sprintf ( f,"-%.2f", ( float ) ( parameter1+parameter2/100.00 ) );
		dbg_printf ( "Compressor_Threshold,ch:%d,value:%s\r\n", channel,f );
	}
	else
	{
		sprintf ( f,"%.2f", ( float ) ( parameter1+parameter2/100.00 ) );
		dbg_printf ( "Compressor_Threshold,ch:%d,value:%s\r\n", channel, f );
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
void mapp_SET_Input_Compressor_StartTime ( u8 channel,u8 parameter1,u8 parameter2 )
{
	u8 Command[7] = {0x00,0xAA,0x0d,0,0,0,0};
	u8 dev = cg_u8_IN_ChannelTable[channel][1];
	Command[3] = cg_u8_IN_ChannelTable[channel][0];
	Command[4] = parameter1;
	Command[5] = parameter2;
	app_Input_Compressor_StartTime ( dev, Command );
	dbg_printf ( "Input_Compressor_StartTime,ch%d,value:%d\r\n",channel, ( parameter1<<8 )+parameter2 );
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
void mapp_SET_Input_Compressor_ReleaseTime ( u8 channel,u8 parameter1,u8 parameter2 )
{
	u8 Command[7] = {0x00,0xAA,0x0e,0,0,0,0};
	u8 dev = cg_u8_IN_ChannelTable[channel][1];
	Command[3] = cg_u8_IN_ChannelTable[channel][0];
	Command[4] = parameter1;
	Command[5] = parameter2;
	app_Input_Compressor_ReleaseTime ( dev, Command );
	dbg_printf ( "Input_Compressor_ReleaseTime,ch%d,value:%d\r\n",channel, ( parameter1<<8 )+parameter2 );
}
/****************************************************
Function:    	mapp_SET_Input_AutoGain_Ctrl
Description: 	输入通道自动增益开关
channel: 		输入通道
OnOff:			0:关闭,1:打开
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_AutoGain_Ctrl ( u8 channel,u8 OnOff )
{
	u8 Command[7] = {0x00,0xAA,0x0f,0,0,0,0};
	u8 dev = cg_u8_IN_ChannelTable[channel][1];
	Command[3] = cg_u8_IN_ChannelTable[channel][0];
	Command[4] = OnOff;
	app_Input_AutoGain_Ctrl ( dev, Command );
	dbg_printf ( "Input_AutoGain,ch%d,OnOff:%d\r\n",channel,OnOff );
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
void mapp_SET_Input_AutoGain_Threshold ( u8 channel,u8 parameter1,u8 parameter2 )
{
	u8 Command[7] = {0x00,0xAA,0x10,0,0,0,0};
	u8 dev = cg_u8_IN_ChannelTable[channel][1];
	Command[3] = cg_u8_IN_ChannelTable[channel][0];
	Command[4] = parameter1;
	Command[5] = parameter2;
	char f[10];
	app_Input_AutoGain_Threshold ( dev, Command );
	if ( parameter1&0x80 )
	{
		parameter1 = parameter1&0x7f;
		sprintf ( f,"-%.1f", ( float ) ( parameter1+parameter2/10.0 ) );
		dbg_printf ( "AutoGain_Threshold,ch:%d,value:%s\r\n", channel,f );
	}
	else
	{
		sprintf ( f,"%.1f", ( float ) ( parameter1+parameter2/10.0 ) );
		dbg_printf ( "AutoGain_Threshold,ch:%d,value:%s\r\n", channel, f );
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
void mapp_SET_Input_AutoGain_TargetThreshold ( u8 channel,u8 parameter1,u8 parameter2 )
{
	u8 Command[7] = {0x00,0xAA,0x11,0,0,0,0};
	u8 dev = cg_u8_IN_ChannelTable[channel][1];
	Command[3] = cg_u8_IN_ChannelTable[channel][0];
	Command[4] = parameter1;
	Command[5] = parameter2;
	char f[10];
	app_Input_AutoGain_TargetThreshold ( dev, Command );
	if ( parameter1&0x80 )
	{
		parameter1 = parameter1&0x7f;
		sprintf ( f,"-%.1f", ( float ) ( parameter1+parameter2/10.0 ) );
		dbg_printf ( "AutoGain_TargetThreshold,ch:%d,value:%s\r\n", channel,f );
	}
	else
	{
		sprintf ( f,"%.1f", ( float ) ( parameter1+parameter2/10.0 ) );
		dbg_printf ( "AutoGain_TargetThreshold,ch:%d,value:%s\r\n", channel, f );
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
void mapp_SET_Input_AutoGain_Ratio ( u8 channel,u8 parameter1,u8 parameter2 )
{
	u8 Command[7] = {0x00,0xAA,0x12,0,0,0,0};
	u8 dev = cg_u8_IN_ChannelTable[channel][1];
	Command[3] = cg_u8_IN_ChannelTable[channel][0];
	Command[4] = parameter1;
	Command[5] = parameter2;
	char f[10];
	app_Input_AutoGain_Ratio ( dev, Command );
	if ( parameter1&0x80 )
	{
		parameter1 = parameter1&0x7f;
		sprintf ( f,"-%.2f", ( float ) ( parameter1+parameter2/100.00 ) );
		dbg_printf ( "AutoGain_Ratio,ch:%d,value:%s\r\n", channel,f );
	}
	else
	{
		sprintf ( f,"%.2f", ( float ) ( parameter1+parameter2/100.00 ) );
		dbg_printf ( "AutoGain_Ratio,ch:%d,value:%s\r\n", channel, f );
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
void mapp_SET_Input_AutoGain_StartTime ( u8 channel,u8 parameter1,u8 parameter2 )
{
	u8 Command[7] = {0x00,0xAA,0x13,0,0,0,0};
	u8 dev = cg_u8_IN_ChannelTable[channel][1];
	Command[3] = cg_u8_IN_ChannelTable[channel][0];
	Command[4] = parameter1;
	Command[5] = parameter2;
	app_Input_AutoGain_StartTime ( dev, Command );
	dbg_printf ( "Input_AutoGain_StartTime,ch%d,value:%d\r\n",channel, ( parameter1<<8 )+parameter2 );
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
void mapp_SET_Input_AutoGain_ReleaseTime ( u8 channel,u8 parameter1,u8 parameter2 )
{
	u8 Command[7] = {0x00,0xAA,0x14,0,0,0,0};
	u8 dev = cg_u8_IN_ChannelTable[channel][1];
	Command[3] = cg_u8_IN_ChannelTable[channel][0];
	Command[4] = parameter1;
	Command[5] = parameter2;
	app_Input_AutoGain_ReleaseTime ( dev, Command );
	dbg_printf ( "Input_AutoGain_ReleaseTime,ch%d,value:%d\r\n",channel, ( parameter1<<8 )+parameter2 );
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
void mapp_SET_Input_EQ_Type ( u8 channel,u8 parameter1,u8 parameter2 )
{
	u8 Command[7] = {0x00,0xAA,0x15,0,0,0,0};
	u8 dev = cg_u8_IN_ChannelTable[channel][1];
	Command[3] = cg_u8_IN_ChannelTable[channel][0];
	Command[4] = parameter1;
	Command[5] = parameter2;
	app_Input_EQ_Type ( dev, Command );
	dbg_printf ( "Input_EQ_Type,ch%d,parameter1:%d,parameter2:%d\r\n",channel,parameter1,parameter2 );
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
void mapp_SET_Input_EQ_Gain ( unsigned int channel,unsigned int parameter1,unsigned int parameter2,unsigned int parameter3 )
{
	u8 Command[7] = {0x00,0xAA,0x16,0,0,0,0};
	u8 dev = cg_u8_IN_ChannelTable[channel][1];
	Command[3] = cg_u8_IN_ChannelTable[channel][0];
	Command[4] = parameter1;
	Command[5] = parameter2;
	char f[10];
	app_Input_EQ_Gain ( dev, Command );
	if ( parameter2&0x80 )
	{
		parameter2 = parameter2&0x7f;
		sprintf ( f,"-%.1f", ( float ) ( parameter2+parameter3/10.0 ) );
		dbg_printf ( "Input_EQ_Gain,ch:%d,parameter1:%d,value:%s\r\n", channel, parameter1, f );
	}
	else
	{
		sprintf ( f,"%.1f", ( float ) ( parameter2+parameter3/10.0 ) );
		dbg_printf ( "Input_EQ_Gain,ch:%d,parameter1:%d,value:%s\r\n", channel, parameter1, f );
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
void mapp_SET_Input_EQ_QualityFactor ( u8 channel,u8 parameter1,u8 parameter2,u8 parameter3 )
{
	u8 Command[7] = {0x00,0xAA,0x17,0,0,0,0};
	u8 dev = cg_u8_IN_ChannelTable[channel][1];
	Command[3] = cg_u8_IN_ChannelTable[channel][0];
	Command[4] = parameter1;
	Command[5] = parameter2;
	char f[10];
	app_Input_EQ_QualityFactor ( dev, Command );
	if ( parameter2&0x80 )
	{
		parameter1 = parameter1&0x7f;
		sprintf ( f,"-%.2f", ( float ) ( parameter2+parameter3/100.00 ) );
		dbg_printf ( "EQ_QualityFactor,ch:%d,parameter1:%d,value:%s\r\n", channel,parameter1,f );
	}
	else
	{
		sprintf ( f,"%.2f", ( float ) ( parameter2+parameter3/100.00 ) );
		dbg_printf ( "EQ_QualityFactor,ch:%d,parameter1:%d,value:%s\r\n", channel,parameter1,f );
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
void mapp_SET_Input_EQ_Ctrl ( u8 channel,u8 parameter1,u8 OnOff )
{
	u8 Command[7] = {0x00,0xAA,0x18,0,0,0,0};
	u8 dev = cg_u8_IN_ChannelTable[channel][1];
	Command[3] = cg_u8_IN_ChannelTable[channel][0];
	Command[4] = parameter1;
	Command[5] = OnOff;
	app_Input_EQ_Ctrl ( dev, Command );
	dbg_printf ( "EQ_Ctrl,ch%d,parameter1:%d,OnOff:%d\r\n",channel,parameter1,OnOff );
}
/****************************************************
Function:		mapp_SET_Input_HowlingSuppressor_Ctrl
Description:	啸叫抑制器开关
channel:		输入通道
parameter1: 	0:关闭,1:打开
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_HowlingSuppressor_Ctrl ( u8 channel,u8 OnOff )
{
	u8 Command[7] = {0x00,0xAA,0x19,0,0,0,0};
	u8 dev = cg_u8_IN_ChannelTable[channel][1];
	Command[3] = cg_u8_IN_ChannelTable[channel][0];
	Command[4] = OnOff;
	app_Input_HowlingSuppressor_Ctrl ( dev, Command );
	dbg_printf ( "HowlingSuppressor_Ctrl,ch%d,OnOff:%d\r\n",channel,OnOff );

}
/****************************************************
Function:		mapp_SET_Input_HowlingSuppressor_Grade
Description:	啸叫抑制器等级
parameter1: 	等级(0~10)
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_HowlingSuppressor_Grade ( u8 dev, u8 parameter1 )
{
	u8 Command[7] = {0x00,0xAA,0x1a,0,0,0,0};
	Command[4] = parameter1;
	app_Input_HowlingSuppressor_Grade ( dev, Command );
	dbg_printf ( "HowlingSuppressor_Grade,dev:%d  parameter1:%d\r\n",dev, parameter1 );
}
/****************************************************
Function:		mapp_SET_Input_HowlingSuppressor_FreqShift
Description:	啸叫抑制器移频参数
parameter1: 	移频参数( -7,-5,-3,+3，+5,+7)
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_HowlingSuppressor_FreqShift ( u8 dev, u8 parameter1 )
{
	u8 Command[7] = {0x00,0xAA,0x1b,0,0,0,0};
	Command[4] = parameter1;
	app_Input_HowlingSuppressor_FreqShift ( dev, Command );
	dbg_printf ( "HowlingSuppressor_FreqShift,dev:%d  parameter1:%d\r\n",dev, parameter1 );
}
/****************************************************
Function:		mapp_SET_Input_NoiseSuppressor_Grade
Description:	噪声抑制器等级
parameter1: 	等级(0~10)
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_NoiseSuppressor_Grade ( u8 dev, u8 parameter1 )
{
	u8 Command[7] = {0x00,0xAA,0x1c,0,0,0,0};
	Command[4] = parameter1;
	app_Input_NoiseSuppressor_Ctrl ( dev, Command );
	dbg_printf ( "NoiseSuppressor_Gradet,dev:%d  parameter1:%d\r\n",dev, parameter1 );

}
/****************************************************
Function:		mapp_SET_Input_NoiseSuppressor_Threshold
Description:	噪声抑制器阈值(-90.0~0.0)
parameter1: 	整数部分
parameter2: 	小数部分(后1位)
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_NoiseSuppressor_Threshold ( u8 dev, u8 parameter1,u8 parameter2 )
{
	u8 Command[7] = {0x00,0xAA,0x1d,0,0,0,0};
	Command[4] = parameter1;
	Command[5] = parameter2;
	char f[10];
	app_Input_NoiseSuppressor_Threshold ( dev, Command );
	if ( parameter1&0x80 )
	{
		parameter1 = parameter1&0x7f;
		sprintf ( f,"-%.1f", ( float ) ( parameter1+parameter2/10.0 ) );
		dbg_printf ( "NoiseSuppressor_Threshold,dev:%d  value:%s\r\n",dev, f );
	}
	else
	{
		sprintf ( f,"%.1f", ( float ) ( parameter1+parameter2/10.0 ) );
		dbg_printf ( "NoiseSuppressor_Threshold,dev:%d  value:%s\r\n",dev, f );
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
void mapp_SET_Input_NoiseSuppressor_Ratio ( u8 dev, u8 parameter1,u8 parameter2 )
{
	u8 Command[7] = {0x00,0xAA,0x1e,0,0,0,0};
	Command[4] = parameter1;
	Command[5] = parameter2;
	char f[10];
	app_Input_NoiseSuppressor_Ratio ( dev, Command );
	if ( parameter1&0x80 )
	{
		parameter1 = parameter1&0x7f;
		sprintf ( f,"-%.2f", ( float ) ( parameter1+parameter2/100.00 ) );
		dbg_printf ( "NoiseSuppressor_Ratio,dev:%d  value:%s\r\n",dev, f );
	}
	else
	{
		sprintf ( f,"%.2f", ( float ) ( parameter1+parameter2/100.00 ) );
		dbg_printf ( "NoiseSuppressor_Ratio,dev:%d value:%s\r\n",dev, f );
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
void mapp_SET_Input_NoiseSuppressor_StartTime ( u8 dev, u8 parameter1,u8 parameter2 )
{
	u8 Command[7] = {0x00,0xAA,0x1f,0,0,0,0};
	Command[4] = parameter1;
	Command[5] = parameter2;
	app_Input_NoiseSuppressor_StartTime ( dev, Command );
	dbg_printf ( "NoiseSuppressor_StartTime,dev:%d  value:%d\r\n",dev, ( parameter1<<8 )+parameter2 );

}
/****************************************************
Function:		mapp_SET_Input_NoiseSuppressor_ReleaseTime
Description:	噪声抑制器释放时间(0~7500)
parameter1: 	数据高8位
parameter2: 	数据低8位
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_NoiseSuppressor_ReleaseTime ( u8 dev, u8 parameter1,u8 parameter2 )
{
	u8 Command[7] = {0x00,0xAA,0x20,0,0,0,0};
	Command[4] = parameter1;
	Command[5] = parameter2;
	app_Input_NoiseSuppressor_ReleaseTime ( dev, Command );
	dbg_printf ( "NoiseSuppressor_ReleaseTime,dev :%d  value:%d\r\n", dev, ( parameter1<<8 )+parameter2 );

}

/****************************************************
Function:		mapp_SET_Input_NoiseSuppressor_Ctrl
Description:	噪声抑制器开关(0~7500)
channel: 		通道
parameter1: 	0:关闭,1:打开
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_NoiseSuppressor_Ctrl ( u8 channel,u8 OnOff )
{
	u8 Command[7] = {0x00,0xAA,0x21,0,0,0,0};
	u8 dev = cg_u8_IN_ChannelTable[channel][1];
	Command[3] = cg_u8_IN_ChannelTable[channel][0];
	Command[4] = OnOff;
	app_Input_NoiseSuppressor_Ctrl ( dev, Command );
	dbg_printf ( "NoiseSuppressor_Ctrl,ch:%d, OnOff:%d\r\n", channel, OnOff );

}

/****************************************************
Function:		mapp_SET_Input_EchoCanceller_Grade
Description:	回声消除器等级
channel:		通道
parameter1: 	等级(0~10)
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_EchoCanceller_Grade ( u8 channel,u8 parameter1 )
{
	u8 Command[7] = {0x00,0xAA,0x22,0,0,0,0};
	u8 dev = cg_u8_IN_ChannelTable[channel][1];
	Command[3] = cg_u8_IN_ChannelTable[channel][0];
	Command[4] = parameter1;
	app_Input_EchoCanceller_Grade ( dev, Command );
	dbg_printf ( "EchoCanceller_Grade,ch:%d, parameter1:%d\r\n", channel, parameter1 );
}

/****************************************************
Function:		mapp_SET_Input_EchoCanceller_Ctrl
Description:	回声消除器开关
channel:		通道
parameter1: 	0:关闭,1:打开
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_EchoCanceller_Ctrl ( u8 channel,u8 OnOff )
{
	u8 Command[7] = {0x00,0xAA,0x23,0,0,0,0};
	u8 dev = cg_u8_IN_ChannelTable[channel][1];
	Command[3] = cg_u8_IN_ChannelTable[channel][0];
	Command[4] = OnOff;
	app_Input_EchoCanceller_Ctrl ( dev, Command );
	dbg_printf ( "EchoCanceller_Ctrl,ch:%d, OnOff:%d\r\n", channel, OnOff );

}

/****************************************************
Function:		mapp_SET_Input_LfreqExciter_Grade
Description:	低频激励器等级
channel:		通道
parameter1: 	等级(0~8)
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_LfreqExciter_Grade ( u8 channel,u8 parameter1 )
{
	u8 Command[7] = {0x00,0xAA,0x24,0,0,0,0};
	u8 dev = cg_u8_IN_ChannelTable[channel][1];
	Command[3] = cg_u8_IN_ChannelTable[channel][0];
	Command[4] = parameter1;
	app_Input_LfreqExciter_Grade ( dev, Command );
	dbg_printf ( "LfreqExciter_Grade,ch:%d, parameter1:%d\r\n", channel, parameter1 );

}

/****************************************************
Function:		mapp_SET_Input_HfreqExciter_Grade
Description:	高频激励器等级
channel:		通道
parameter1: 	等级(0~8)
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_HfreqExciter_Grade ( u8 channel,u8 parameter1 )
{
	u8 Command[7] = {0x00,0xAA,0x25,0,0,0,0};
	u8 dev = cg_u8_IN_ChannelTable[channel][1];
	Command[3] = cg_u8_IN_ChannelTable[channel][0];
	Command[4] = parameter1;
	app_Input_HfreqExciter_Grade ( dev, Command );
	dbg_printf ( "HfreqExciter_Grade,ch:%d, parameter1:%d\r\n", channel, parameter1 );
}

/****************************************************
Function:		mapp_SET_Input_Exciter_Ctrl
Description:	激励器开关
channel:		通道
parameter1: 	0:关闭,1:打开
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_Exciter_Ctrl ( u8 channel,u8 OnOff )
{
	u8 Command[7] = {0x00,0xAA,0x26,0,0,0,0};
	u8 dev = cg_u8_IN_ChannelTable[channel][1];
	Command[3] = cg_u8_IN_ChannelTable[channel][0];
	Command[4] = OnOff;
	app_Input_Exciter_Ctrl ( dev, Command );
	dbg_printf ( "Exciter_Ctrl,ch:%d, OnOff:%d\r\n", channel, OnOff );
}

/****************************************************
Function:		mapp_SET_Input_CallInput
Description:	呼叫输入设置
channel:		通道
parameter1: 	0:取消设置,1:设置为呼叫输入
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_CallInput ( u8 channel,u8 OnOff )
{
	u8 Command[7] = {0x00,0xAA,0x27,0,0,0,0};
	u8 dev = cg_u8_IN_ChannelTable[channel][1];
	Command[3] = cg_u8_IN_ChannelTable[channel][0];
	Command[4] = OnOff;
	app_Input_CallInput ( dev, Command );
	dbg_printf ( "BackgroundInput,ch:%d, OnOff:%d\r\n", channel, OnOff );
}

/****************************************************
Function:		mapp_SET_Input_BackgroundInput
Description:	背景输入设置
channel:		通道
parameter1: 	0:取消设置,1:设置为背景输入
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_BackgroundInput ( u8 channel,u8 OnOff )
{
	u8 Command[7] = {0x00,0xAA,0x28,0,0,0,0};
	u8 dev = cg_u8_IN_ChannelTable[channel][1];
	Command[3] = cg_u8_IN_ChannelTable[channel][0];
	Command[4] = OnOff;
	app_Input_BackgroundInput ( dev, Command );
	dbg_printf ( "BackgroundInput,ch:%d, OnOff:%d\r\n", channel, OnOff );
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
void mapp_SET_Input_Ducking_Gain ( u8 channel,u8 parameter1,u8 parameter2 )
{
	u8 Command[7] = {0x00,0xAA,0x29,0,0,0,0};
	u8 dev = cg_u8_IN_ChannelTable[channel][1];
	Command[3] = cg_u8_IN_ChannelTable[channel][0];
	Command[4] = parameter1;
	Command[5] = parameter2;
	char f[10];
	app_Input_Ducking_Gain ( dev, Command );
	if ( parameter1&0x80 )
	{
		parameter1 = parameter1&0x7f;
		sprintf ( f,"-%.1f", ( float ) ( parameter1+parameter2/10.0 ) );
		dbg_printf ( "Ducking_Gai,ch:%d,value:%s\r\n", channel, f );
	}
	else
	{
		sprintf ( f,"%.1f", ( float ) ( parameter1+parameter2/10.0 ) );
		dbg_printf ( "Ducking_Gai,value:%s\r\n", channel, f );
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
void mapp_SET_Input_Ducking_Threshold ( u8 dev, u8 parameter1,u8 parameter2 )
{
	u8 Command[7] = {0x00,0xAA,0x2a,0,0,0,0};
	Command[4] = parameter1;
	Command[5] = parameter2;
	char f[10];
	app_Input_Ducking_Threshold ( dev, Command );
	if ( parameter1&0x80 )
	{
		parameter1 = parameter1&0x7f;
		sprintf ( f,"-%.1f", ( float ) ( parameter1+parameter2/10.0 ) );
		dbg_printf ( "Ducking_Threshold,dev:%d  value:%s\r\n", dev, f );
	}
	else
	{
		sprintf ( f,"%.1f", ( float ) ( parameter1+parameter2/10.0 ) );
		dbg_printf ( "Ducking_Threshold,dev:%d  value:%s\r\n", dev, f );
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
void mapp_SET_Input_Ducking_Depth ( u8 dev, u8 parameter1,u8 parameter2 )
{
	u8 Command[7] = {0x00,0xAA,0x2b,0,0,0,0};
	Command[4] = parameter1;
	Command[5] = parameter2;
	char f[10];
	app_Input_Ducking_Depth ( dev, Command );
	if ( parameter1&0x80 )
	{
		parameter1 = parameter1&0x7f;
		sprintf ( f,"-%.1f", ( float ) ( parameter1+parameter2/10.0 ) );
		dbg_printf ( "Ducking_Depth, dev:%d  value:%s\r\n", dev, f );
	}
	else
	{
		sprintf ( f,"%.1f", ( float ) ( parameter1+parameter2/10.0 ) );
		dbg_printf ( "Ducking_Depth,dev:%d  value:%s\r\n", dev, f );
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
void mapp_SET_Input_Ducking_StartTime ( u8 dev, u8 parameter1,u8 parameter2 )
{
	u8 Command[7] = {0x00,0xAA,0x2c,0,0,0,0};
	Command[4] = parameter1;
	Command[5] = parameter2;
	app_Input_Ducking_StartTime ( dev, Command );
	dbg_printf ( "Ducking_StartTime,dev:%d value:%d\r\n", dev, ( parameter1<<8 )+parameter2 );
}

/****************************************************
Function:		mapp_SET_Input_Ducking_HoldTime
Description:	闪避器保持时间(5~500)
parameter1: 	数据高8位
parameter2: 	数据低8位
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_Ducking_HoldTime ( u8 dev, u8 parameter1,u8 parameter2 )
{
	u8 Command[7] = {0x00,0xAA,0x2d,0,0,0,0};
	Command[4] = parameter1;
	Command[5] = parameter2;
	app_Input_Ducking_HoldTime ( dev, Command );
	dbg_printf ( "Ducking_HoldTime,dev:%d value:%d\r\n", dev, ( parameter1<<8 )+parameter2 );
}

/****************************************************
Function:		mapp_SET_Input_Ducking_ReleaseTime
Description:	闪避器释放时间(10~30000)
parameter1: 	数据高8位
parameter2: 	数据低8位
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_Ducking_ReleaseTime ( u8 dev, u8 parameter1,u8 parameter2 )
{
	u8 Command[7] = {0x00,0xAA,0x2e,0,0,0,0};
	Command[4] = parameter1;
	Command[5] = parameter2;
	app_Input_Ducking_ReleaseTime ( dev, Command );
	dbg_printf ( "Ducking_ReleaseTime,dev:%d value:%d\r\n",dev, ( parameter1<<8 )+parameter2 );
}

/****************************************************
Function:		mapp_SET_Input_Ducking_Ctrl
Description:	闪避器开关
parameter1: 	0:关闭,1:打开
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Input_Ducking_Ctrl ( u8 dev, u8 OnOff )
{
	u8 Command[7] = {0x00,0xAA,0x2f,0,0,0,0};
	Command[4] = OnOff;
	app_Input_Ducking_Ctrl ( dev, Command );
	dbg_printf ( "Ducking_Ctrl, dev:%d OnOff:%d\r\n",dev, OnOff );
}

/****************************************************
Function:		mapp_SET_Input_Ducking_MatrixSwitching
Description:	矩阵切换
parameter1: 	输出通道
parameter2: 	输入通道
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_MatrixSwitching ( u8 parameter1,u8 parameter2 )
{
	u8 Command[7] = {0x00,0xAA,0x30,0,0,0,0};

	u8 dev = cg_u8_OUT_ChannelTable[parameter1][1];
	Command[4] = cg_u8_OUT_ChannelTable[parameter1][0];
	Command[5] = cg_u8_IN_ChannelTable[parameter2][0];
	app_MatrixSwitching ( dev, Command );
	dbg_printf ( "input %d to output %d\r\n",parameter2, parameter1 );

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
void mapp_SET_Output_DelayTime ( u8 channel,u8 parameter1,u8 parameter2 )
{
	u8 Command[7] = {0x00,0xAA,0x31,0,0,0,0};
	u8 dev = cg_u8_OUT_ChannelTable[channel][1];

	Command[3] = cg_u8_OUT_ChannelTable[channel][0];
	Command[4] = parameter1;
	Command[5] = parameter2;
	app_Output_DelayTime ( dev, Command );
	dbg_printf ( "Output_DelayTime,channel:%d,onoff:%d\r\n",channel, ( parameter1<<8 )+parameter2 );


}

/****************************************************
Function:		mapp_SET_Output_Delay_Ctrl
Description:	输出延时开关
channel:		通道
parameter1: 	0:关闭,1:打开
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_Output_Delay_Ctrl ( u8 channel,u8 parameter1 )
{
	u8 Command[7] = {0x00,0xAA,0x32,0,0,0,0};
	u8 dev = cg_u8_OUT_ChannelTable[channel][1];

	Command[3] = cg_u8_OUT_ChannelTable[channel][0];
	Command[4] = parameter1;
	app_Output_Delay_Ctrl ( dev,Command );
	dbg_printf ( "Output_Delay_Ctrl,channel:%d,onoff:%d\r\n", channel, parameter1 );
}

/****************************************************
Function:		mapp_SET_USBplayer_Ctrl
Description:	USB播放器控制
parameter1: 	控制参数(0~4)(上一首,下一首,播放,暂停,停止)
add by: 		yml
time:			24.11.5
****************************************************/
void mapp_SET_USBplayer_Ctrl ( u8 parameter1 )
{
	u8 Command[7] = {0x00,0xAA,0x33,0,0,0,0};
	Command[4] = parameter1;
	app_USBplayer_Ctrl ( 0,Command );
	dbg_printf ( "USBplayer:%d\r\n", parameter1 );


}

//eFunc_SetCardFunction
static emCmdFuncStaType mapp_CmdfuncSetCardFunction ( pstUartCom_t pCommVar,u8 cmdnum )
{
	emCmdFuncStaType l_state = emCmdNone;
	char* l_pCmd= pCommVar->pRecBuffer+strlen ( cmd_list[cmdnum].ucmd );
	u8 l_u8CmdType = 0;
	u8 l_u8channel = 0;
	u8 parameter1 = 0;
	u8 parameter2 = 0;
	u8 parameter3 = 0;
	dbg_printf ( "l_pCmd: %s\r\n", l_pCmd );
	l_u8CmdType = ( HexAndAsciiChange (* ( l_pCmd+0 ),0 ) <<4 )+ ( HexAndAsciiChange (* ( l_pCmd+1 ),0 ) );
	l_u8channel = ( HexAndAsciiChange (* ( l_pCmd+2 ),0 ) <<4 )+ ( HexAndAsciiChange (* ( l_pCmd+3 ),0 ) );
	parameter1 = ( HexAndAsciiChange (* ( l_pCmd+4 ),0 ) <<4 )+ ( HexAndAsciiChange (* ( l_pCmd+5 ),0 ) );
	parameter2 = ( HexAndAsciiChange (* ( l_pCmd+6 ),0 ) <<4 )+ ( HexAndAsciiChange (* ( l_pCmd+7 ),0 ) );
	parameter3 = ( HexAndAsciiChange (* ( l_pCmd+8 ),0 ) <<4 )+ ( HexAndAsciiChange (* ( l_pCmd+9 ),0 ) );
	dbg_printf ( "l_u8CmdType:%x,l_u8channel:%x,parameter1:%x,parameter2:%x,parameter3:%d\r\n",l_u8CmdType,l_u8channel,parameter1,parameter2,parameter3 );
	switch ( l_u8CmdType )
	{
		case 0x01://总音频
			mapp_All_AudioOutput_Ctrl ( parameter1 );
			break;
		case 0x02://输入源灵敏度
			mapp_SET_Input_Sensitivity ( l_u8channel, parameter1 );
			break;
		case 0x03://输入增益
			mapp_SET_Input_Gain ( l_u8channel, parameter1, parameter2 );
			break;
		case 0x04://输入静音
			mapp_SET_Input_Mute ( l_u8channel, parameter1 );
			break;
		case 0x05://输入反相
			mapp_SET_Input_Reverse_phase ( l_u8channel, parameter1 );
			break;
		case 0x06://输入通道测试信号开关
			mapp_SET_Input_TestSignal_Ctrl ( l_u8channel, parameter1 );
			break;
		case 0x07://测试信号频率
			mapp_SET_Input_TestSignal_Freq ( l_u8channel, parameter1, parameter2 );
			break;
		case 0x08://测试信号电平
			mapp_SET_Input_TestSignal_Level ( l_u8channel, parameter1, parameter2 );
			break;
		case 0x09://输入通道压缩器开关
			mapp_SET_Input_Compressor_Ctrl ( l_u8channel, parameter1 );
			break;
		case 0x0a://输入压缩器增益

			mapp_SET_Input_Compressor_Gain ( l_u8channel, parameter1, parameter2 );
			break;
		case 0x0b://输入压缩器阈值
			mapp_SET_Input_Compressor_Threshold ( l_u8channel, parameter1, parameter2 );
			break;
		case 0x0c://输入压缩器比率
			mapp_SET_Input_Compressor_Ratio ( l_u8channel, parameter1,parameter2 );
			break;
		case 0x0d://输入压缩器启动时间
			mapp_SET_Input_Compressor_StartTime ( l_u8channel, parameter1, parameter2 );
			break;
		case 0x0e://输入压缩器释放时间
			mapp_SET_Input_Compressor_ReleaseTime ( l_u8channel, parameter1, parameter2 );
			break;
		case 0x0f://输入通道自动增益开关
			mapp_SET_Input_AutoGain_Ctrl ( l_u8channel, parameter1 );
			break;
		case 0x10://输入通道自动增益阈值
			mapp_SET_Input_AutoGain_Threshold ( l_u8channel, parameter1, parameter2 );
			break;
		case 0x11://输入通道自动增益目标阈值
			mapp_SET_Input_AutoGain_TargetThreshold ( l_u8channel, parameter1, parameter2 );
			break;
		case 0x12://输入通道自动增益比率
			mapp_SET_Input_AutoGain_Ratio ( l_u8channel, parameter1, parameter2 );
			break;
		case 0x13://输入通道自动增益启动时间
			mapp_SET_Input_AutoGain_StartTime ( l_u8channel, parameter1, parameter2 );
			break;
		case 0x14://输入通道自动增益释放时间
			mapp_SET_Input_AutoGain_ReleaseTime ( l_u8channel, parameter1, parameter2 );
			break;
		case 0x15://输入参量均衡某段类型
			mapp_SET_Input_EQ_Type ( l_u8channel, parameter1, parameter2 );
			break;
		case 0x16://输入参量均衡某段增益
			mapp_SET_Input_EQ_Gain ( l_u8channel, parameter1, parameter2, parameter3 );
			break;
		case 0x17://输入参量均衡某段品质因数
			mapp_SET_Input_EQ_QualityFactor ( l_u8channel, parameter1, parameter2, parameter3 );
			break;
		case 0x18://输入参量均衡某段开关
			mapp_SET_Input_EQ_Ctrl ( l_u8channel, parameter1, parameter2 );
			break;
		case 0x19://啸叫抑制器开关
			mapp_SET_Input_HowlingSuppressor_Ctrl ( l_u8channel, parameter1 );
			break;
		case 0x1a://啸叫抑制器等级
			mapp_SET_Input_HowlingSuppressor_Grade ( l_u8channel, parameter1 );
			break;
		case 0x1b://移频参数
			mapp_SET_Input_HowlingSuppressor_FreqShift ( l_u8channel, parameter1 );
			break;
		case 0x1c://噪声抑制等级
			mapp_SET_Input_NoiseSuppressor_Grade ( l_u8channel, parameter1 );
			break;
		case 0x1d://噪声抑制阈值
			mapp_SET_Input_NoiseSuppressor_Threshold ( l_u8channel, parameter1, parameter2 );
			break;
		case 0x1e://噪声抑制比率
			mapp_SET_Input_NoiseSuppressor_Ratio ( l_u8channel, parameter1, parameter2 );
			break;
		case 0x1f://噪声抑制启动时间
			mapp_SET_Input_NoiseSuppressor_StartTime ( l_u8channel, parameter1, parameter2 );
			break;
		case 0x20://噪声抑制释放时间
			mapp_SET_Input_NoiseSuppressor_ReleaseTime ( l_u8channel, parameter1, parameter2 );
			break;
		case 0x21://噪声抑制开关
			mapp_SET_Input_NoiseSuppressor_Ctrl ( l_u8channel, parameter1 );
			break;
		case 0x22://回声消除等级
			mapp_SET_Input_EchoCanceller_Grade ( l_u8channel, parameter1 );
			break;
		case 0x23://回声消除开关
			mapp_SET_Input_EchoCanceller_Ctrl ( l_u8channel, parameter1 );
			break;
		case 0x24://某路低频激励器等级
			mapp_SET_Input_LfreqExciter_Grade ( l_u8channel, parameter1 );
			break;
		case 0x25://某路高频激励器等级
			mapp_SET_Input_HfreqExciter_Grade ( l_u8channel, parameter1 );
			break;
		case 0x26://某路激励器开关
			mapp_SET_Input_Exciter_Ctrl ( l_u8channel, parameter1 );
			break;
		case 0x27://第几路为呼叫输入
			mapp_SET_Input_CallInput ( l_u8channel, parameter1 );
			break;
		case 0x28://第几路为背景输入
			mapp_SET_Input_BackgroundInput ( l_u8channel, parameter1 );
			break;
		case 0x29://某一路闪避器增益
			mapp_SET_Input_Ducking_Gain ( l_u8channel, parameter1, parameter2 );
			break;
		case 0x2a://闪避器阈值
			mapp_SET_Input_Ducking_Threshold ( l_u8channel, parameter1, parameter2 );
			break;
		case 0x2b://闪避器深度
			mapp_SET_Input_Ducking_Depth ( l_u8channel, parameter1, parameter2 );
			break;
		case 0x2c://闪避器启动时间
			mapp_SET_Input_Ducking_StartTime ( l_u8channel, parameter1, parameter2 );
			break;
		case 0x2d://闪避器保持时间
			mapp_SET_Input_Ducking_HoldTime ( l_u8channel, parameter1, parameter2 );
			break;
		case 0x2e://闪避器释放时间
			mapp_SET_Input_Ducking_ReleaseTime ( l_u8channel, parameter1, parameter2 );
			break;
		case 0x2f://闪避器开关
			mapp_SET_Input_Ducking_Ctrl ( l_u8channel, parameter1 );
			break;
		case 0x30://矩阵切换
			mapp_SET_MatrixSwitching ( parameter1, parameter2 );
			break;
		case 0x31://输出延时时间
			mapp_SET_Output_DelayTime ( l_u8channel, parameter1, parameter2 );
			break;
		case 0x32://输入延时开关
			mapp_SET_Output_Delay_Ctrl ( l_u8channel, parameter1 );
			break;
		case 0x33://USB播放控制
			mapp_SET_USBplayer_Ctrl ( parameter1 );
			break;
		default:
			break;
	}
	return l_state;
}

/**
*BP1048 - 参数的获取
*/
static emCmdFuncStaType mapp_CmdfuncGetCardFunction ( pstUartCom_t pCommVar,u8 cmdnum )
{
	emCmdFuncStaType l_state = emCmdNone;

	return l_state;
}

/**
*GUI - 参数的设置
*/
static emCmdFuncStaType mapp_CmdfuncSetGUIFunction ( pstUartCom_t pCommVar,u8 cmdnum )
{
	emCmdFuncStaType l_state = emCmdNone;
	dbg_printf ( "1111111111111111111%s11111111111111111\r\n",__FUNCTION__ );
	return l_state;
}

/**
*GUI - 参数的获取
*/
static emCmdFuncStaType mapp_CmdfuncGetGUIFunction ( pstUartCom_t pCommVar,u8 cmdnum )
{
	emCmdFuncStaType l_state = emCmdNone;

	return l_state;
}

//eFunc_SetSTKCardFunction
static emCmdFuncStaType mapp_CmdfuncSetSTKCardFunction ( pstUartCom_t pCommVar,u8 cmdnum )
{
	emCmdFuncStaType l_state = emCmdNone;

	return l_state;
}

//===============================================================================
//Function process
//===============================================================================
void  mapp_SetCommandFunctionID ( eCmdFun_t cmdfuncid )
{
	cmdfunctionID = cmdfuncid;
}

eCmdFun_t  mapp_GetCommandFunctionID ( void )
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
emCmdFuncStaType mapp_CommandFunctionProcess ( u8 cmdnum,u8 flag,pstUartCom_t pCommVar )
{
	emCmdFuncStaType l_bStatus=emCmdError;

	UNUSED ( flag );
	//UNUSED(cmdnum);
#if 0
	if ( mapp_GetCommandFunctionID() == eFunc_SetAllAudioOutput )
	{
		dbg_printf ( "cmd_list:%d eFunc_SetCardFunction:%d\teFunc_SetGUIFunction:%d,%x \t eFunc_SetAllAudioOutput: %d,%x \r\n",mapp_GetCommandFunctionID(), \
		             eFunc_SetCardFunction, \
		             eFunc_SetGUIFunction,eFunc_SetGUIFunction, \
		             eFunc_SetAllAudioOutput,eFunc_SetAllAudioOutput );
		\
	}
#endif

	switch ( mapp_GetCommandFunctionID() )
	{
		case eFunc_GetVersion:
		{
			l_bStatus = mapp_CmdfuncGetVersion ( pCommVar,cmdnum );
		}
		break;
		case eFunc_FactoryReset:
		{
			l_bStatus = mapp_CmdfuncFactoryReset ( pCommVar,cmdnum );
		}
		break;
		case eFunc_Reboot:
		{
			l_bStatus = mapp_CmdfuncReboot ( pCommVar,cmdnum );
		}
		break;
		case eFunc_GetTestVersion:
		{
			l_bStatus = mapp_CmdfuncGetTestVersion ( pCommVar,cmdnum );
		}
		break;

		case eFunc_SwitchInputPort:
		{
			l_bStatus = mapp_CmdfuncSwitchInputPort ( pCommVar,cmdnum );
		}
		break;
		case eFunc_GetInputStutus:
		{
			l_bStatus = mapp_CmdfuncGetInputStutus ( pCommVar,cmdnum );
		}
		break;
		case eFunc_SetTxResolution:
		{
			l_bStatus = mapp_CmdfuncSetTxResolution ( pCommVar,cmdnum );
		}
		break;
		case eFunc_GetTxResolution:
		{
			l_bStatus = mapp_CmdfuncGetTxResolution ( pCommVar,cmdnum );
		}
		break;
		case eFunc_GetRxResolution:
		{
			l_bStatus = mapp_CmdfuncGetRxResolution ( pCommVar,cmdnum );
		}
		break;
		case eFunc_SetTxHdcpMode:
		{
			l_bStatus = mapp_CmdfuncSetTxHdcpMode ( pCommVar,cmdnum );
		}
		break;
		case eFunc_GetTxHdcpMode:
		{
			l_bStatus = mapp_CmdfuncGetTxHdcpMode ( pCommVar,cmdnum );
		}
		break;
		case eFunc_SetTxFormat:
		{
			l_bStatus = mapp_CmdfuncSetTxFormat ( pCommVar,cmdnum );
		}
		break;
		case eFunc_GetTxFormat:
		{
			l_bStatus = mapp_CmdfuncGetTxFormat ( pCommVar,cmdnum );
		}
		break;
		case eFunc_SetFreezeState:
		{
			l_bStatus = mapp_CmdfuncSetFreezeState ( pCommVar,cmdnum );
		}
		break;
		case eFunc_GetFreezeState:
		{
			l_bStatus = mapp_CmdfuncGetFreezeState ( pCommVar,cmdnum );
		}
		break;
		case eFunc_SwitchFreeze:
		{
			l_bStatus = mapp_CmdfuncSwitchFreeze ( pCommVar,cmdnum );
		}
		break;

		case eFunc_SetBrightness:
		{
			l_bStatus = mapp_CmdfuncSetBrightness ( pCommVar,cmdnum );
		}
		break;
		case eFunc_GetBrightness:
		{
			l_bStatus = mapp_CmdfuncGetBrightness ( pCommVar,cmdnum );
		}
		break;
		case eFunc_SetContrast:
		{
			l_bStatus = mapp_CmdfuncSetContrast ( pCommVar,cmdnum );
		}
		break;
		case eFunc_GetContrast:
		{
			l_bStatus = mapp_CmdfuncGetContrast ( pCommVar,cmdnum );
		}
		break;
		case eFunc_SetSaturation:
		{
			l_bStatus = mapp_CmdfuncSetSaturation ( pCommVar,cmdnum );
		}
		break;
		case eFunc_GetSaturation:
		{
			l_bStatus = mapp_CmdfuncGetSaturation ( pCommVar,cmdnum );
		}
		break;
		case eFunc_SetHue:
		{
			l_bStatus = mapp_CmdfuncSetHue ( pCommVar,cmdnum );
		}
		break;
		case eFunc_GetHue:
		{
			l_bStatus = mapp_CmdfuncGetHue ( pCommVar,cmdnum );
		}
		break;
		case eFunc_SetRxEdidMode:
		{
			l_bStatus = mapp_CmdfuncSetRxEdidMode ( pCommVar,cmdnum );
		}
		break;
		case eFunc_GetRxEdidMode:
		{
		}
		break;
		case eFunc_UpdateUserEdid:
		{
			l_bStatus = mapp_CmdfuncUpdateUserEdid ( pCommVar,cmdnum );
		}
		break;
		case eFunc_GetTxEdidData:
		{
			l_bStatus = mapp_CmdfuncGetTxEdidData ( pCommVar,cmdnum );
		}
		break;
		case eFunc_SetTxTiming:
		{
			l_bStatus = mapp_CmdfuncSetTxTiming ( pCommVar,cmdnum );
		}
		break;
		case eFunc_SetTxPattern:
		{
			l_bStatus = mapp_CmdfuncSetTxPattern ( pCommVar,cmdnum );
		}
		break;
		case eFunc_GetTxPattern:
		{
			l_bStatus = mapp_CmdfuncGetTxPattern ( pCommVar,cmdnum );
		}
		break;
		case eFunc_SetColor:
		{
			l_bStatus = mapp_CmdfuncSetColor ( pCommVar,cmdnum );
		}
		break;
		case eFunc_GetColor:
		{
			l_bStatus = mapp_CmdfuncGetColor ( pCommVar,cmdnum );
		}
		break;
		case eFunc_SetDebugEn:
		{
			l_bStatus = mapp_CmdfuncSetDebugEn ( pCommVar,cmdnum );
		}
		break;
		case eFunc_SetMs1826Hold:
		{
			l_bStatus = mapp_CmdfuncSetMs1826Hold ( pCommVar,cmdnum );
		}
		break;
		case eFunc_BypassSwitchPort:
		{
			l_bStatus = mapp_CmdfuncBypassSwitchPort ( pCommVar,cmdnum );
		}
		break;
		case eFunc_ModeSwitch:
		{
			l_bStatus = mapp_CmdfuncModeSwitch ( pCommVar,cmdnum );
		}
		break;
		case eFunc_FactoryReset2:
		{
			l_bStatus = mapp_CmdfuncFactoryReset2 ( pCommVar,cmdnum );
		}
		break;
		case eFunc_CheckOutputCardType:
		{
			l_bStatus = mapp_CmdfuncCheckOutputCardType ( pCommVar,cmdnum );
		}
		break;
		case eFunc_CheckCardFWVersion:
		{
			l_bStatus = mapp_CmdfuncCheckCardFWVersion ( pCommVar,cmdnum );
		}
		break;
#if ENABLE_CARD_YBJ_RECORD
		case eFunc_CheckYBJCardType:
		{
			l_bStatus = mapp_CmdfuncCheckYBJCardType ( pCommVar,cmdnum );
		}
		break;
		case eFunc_CheckYBJ2CardType:
		{
			l_bStatus = mapp_CmdfuncCheckYBJ2CardType ( pCommVar,cmdnum );
		}
		break;
#endif
		case eFunc_CheckCardMode:
		{
			l_bStatus = mapp_CmdfuncCheckCardMode ( pCommVar,cmdnum );
		}
		break;
		case eFunc_CheckSetEdidData:
		{
			l_bStatus = mapp_CmdfuncCheckSetEdidData ( pCommVar,cmdnum );
		}
		break;

		/*音频卡(BP1048,GUI,以":"开始)主要功能 - 开始*/
		case eFunc_SetCardFunction:
		{
			l_bStatus = mapp_CmdfuncSetCardFunction ( pCommVar,cmdnum );
		}
		break;
		case eFunc_GetCardFunction:
		{
			l_bStatus = mapp_CmdfuncGetCardFunction ( pCommVar,cmdnum );
		}
		break;
			/*音频卡(BP1048,GUI,以":"开始)主要功能 - 结束*/











			/**********************************************************/
			/*音频卡(GUI - JSON,以"{"开始)主要功能 - 开始*/
#if 1     //音频卡 - if-START

		case eFunc_SetProductName:
		{
			l_bStatus = 	mapp_CmdfuncSetProductName ( pCommVar,cmdnum );
			break;
		}
		case eFunc_SetAllAudioOutput:
		{
#if 0
			dbg_printf ( "xxxxxxxxxxxxxxxxxxxx\r\n" );
#endif
			l_bStatus = 	mapp_CmdfuncSetAllAudioOutput ( pCommVar,cmdnum );
			break;
		}
		case eFunc_SetInputSensitivity:
		{
			l_bStatus = 	mapp_CmdfuncSetInputSensitivity ( pCommVar,cmdnum );
			break;
		}
		case eFunc_SetInputGain:
		{
			l_bStatus = 	mapp_CmdfuncSetInputGain ( pCommVar,cmdnum );
			break;
		}
		case eFunc_SetInputMute:
		{
			l_bStatus = 	mapp_CmdfuncSetInputMute ( pCommVar,cmdnum );
			break;
		}
		case eFunc_SetInputReversephase:
		{
			l_bStatus = 	mapp_CmdfuncSetInputReversephase ( pCommVar,cmdnum );
			break;
		}
		case eFunc_SetInputTestSignalCtrl:
		{
			l_bStatus = 	mapp_CmdfuncSetInputTestSignalCtrl ( pCommVar,cmdnum );
			break;
		}
		case eFunc_SetInputTestSignalFreq:
		{
			l_bStatus = 	mapp_CmdfuncSetInputTestSignalFreq ( pCommVar,cmdnum );
			break;
		}
		case eFunc_SetInputTestSignalLevel:
		{
			l_bStatus = 	mapp_CmdfuncSetInputTestSignalLevel ( pCommVar,cmdnum );
			break;
		}
		case eFunc_SetInputCompressorCtrl:
		{
			l_bStatus = 	mapp_CmdfuncSetInputCompressorCtrl ( pCommVar,cmdnum );
			break;
		}
		case eFunc_SetInputCompressorGain:
		{
			l_bStatus = 	mapp_CmdfuncSetInputCompressorGain ( pCommVar,cmdnum );
			break;
		}
		case eFunc_SetInputCompressorThreshold:
		{
			l_bStatus = 	mapp_CmdfuncSetInputCompressorThreshold ( pCommVar,cmdnum );
			break;
		}
		case eFunc_SetInputCompressorRatio:
		{
			l_bStatus = 	mapp_CmdfuncSetInputCompressorRatio ( pCommVar,cmdnum );
			break;
		}
		case eFunc_SetInputCompressorStartTime:
		{
			l_bStatus = 	mapp_CmdfuncSetInputCompressorStartTime ( pCommVar,cmdnum );
			break;
		}
		case eFunc_SetInputCompressorReleaseTime:
		{
			l_bStatus = 	mapp_CmdfuncSetInputCompressorReleaseTime ( pCommVar,cmdnum );
			break;
		}
		case eFunc_SetInputAutoGainCtrl:
		{
			l_bStatus = 	mapp_CmdfuncSetInputAutoGainCtrl ( pCommVar,cmdnum );
			break;
		}
		case eFunc_SetInputAutoGainThreshold:
		{
			l_bStatus = 	mapp_CmdfuncSetInputAutoGainThreshold ( pCommVar,cmdnum );
			break;
		}
		case eFunc_SetInputAutoGainTargetThreshold:
		{
			l_bStatus = 	mapp_CmdfuncSetInputAutoGainTargetThreshold ( pCommVar,cmdnum );
			break;
		}
		case eFunc_SetInputAutoGainRatio:
		{
			l_bStatus = 	mapp_CmdfuncSetInputAutoGainRatio ( pCommVar,cmdnum );
			break;
		}
		case eFunc_SetInputAutoGainStartTime:
		{
			l_bStatus = 	mapp_CmdfuncSetInputAutoGainStartTime ( pCommVar,cmdnum );
			break;
		}
		case eFunc_SetInputAutoGainReleaseTime:
		{
			l_bStatus = 	mapp_CmdfuncSetInputAutoGainReleaseTime ( pCommVar,cmdnum );
			break;
		}
		case eFunc_SetInputEQType:
		{
			l_bStatus = 	mapp_CmdfuncSetInputEQType ( pCommVar,cmdnum );
			break;
		}
		case eFunc_SetInputEQGain:
		{
			l_bStatus = 	mapp_CmdfuncSetInputEQGain ( pCommVar,cmdnum );
			break;
		}
		case eFunc_SetInputEQQualityFactor:
		{
			l_bStatus = 	mapp_CmdfuncSetInputEQQualityFactor ( pCommVar,cmdnum );
			break;
		}
		case eFunc_SetInputEQCtrl:
		{
			l_bStatus = 	mapp_CmdfuncSetInputEQCtrl ( pCommVar,cmdnum );
			break;
		}
		case eFunc_SetInputHowlingSuppressorCtrl:
		{
			l_bStatus = 	mapp_CmdfuncSetInputHowlingSuppressorCtrl ( pCommVar,cmdnum );
			break;
		}
		case eFunc_SetInputHowlingSuppressorGrade:
		{
			l_bStatus = 	mapp_CmdfuncSetInputHowlingSuppressorGrade ( pCommVar,cmdnum );
			break;
		}
		case eFunc_SetInputHowlingSuppressorFreqShift:
		{
			l_bStatus = 	mapp_CmdfuncSetInputHowlingSuppressorFreqShift ( pCommVar,cmdnum );
			break;
		}
		case eFunc_SetInputNoiseSuppressorGrade:
		{
			l_bStatus = 	mapp_CmdfuncSetInputNoiseSuppressorGrade ( pCommVar,cmdnum );
			break;
		}
		case eFunc_SetInputNoiseSuppressorThreshold:
		{
			l_bStatus = 	mapp_CmdfuncSetInputNoiseSuppressorThreshold ( pCommVar,cmdnum );
			break;
		}
		case eFunc_SetInputNoiseSuppressorRatio:
		{
			l_bStatus = 	mapp_CmdfuncSetInputNoiseSuppressorRatio ( pCommVar,cmdnum );
			break;
		}
		case eFunc_SetInputNoiseSuppressorStartTime:
		{
			l_bStatus = 	mapp_CmdfuncSetInputNoiseSuppressorStartTime ( pCommVar,cmdnum );
			break;
		}
		case eFunc_SetInputNoiseSuppressorReleaseTime:
		{
			l_bStatus = 	mapp_CmdfuncSetInputNoiseSuppressorReleaseTime ( pCommVar,cmdnum );
			break;
		}
		case eFunc_SetInputNoiseSuppressorCtrl:
		{
			l_bStatus = 	mapp_CmdfuncSetInputNoiseSuppressorCtrl ( pCommVar,cmdnum );
			break;
		}
		case eFunc_SetInputEchoCancellerGrade:
		{
			l_bStatus = 	mapp_CmdfuncSetInputEchoCancellerGrade ( pCommVar,cmdnum );
			break;
		}
		case eFunc_SetInputEchoCancellerCtrl:
		{
			l_bStatus = 	mapp_CmdfuncSetInputEchoCancellerCtrl ( pCommVar,cmdnum );
			break;
		}
		case eFunc_SetInputLfreqExciterGrade:
		{
			l_bStatus = 	mapp_CmdfuncSetInputLfreqExciterGrade ( pCommVar,cmdnum );
			break;
		}
		case eFunc_SetInputHfreqExciterGrade:
		{
			l_bStatus = 	mapp_CmdfuncSetInputHfreqExciterGrade ( pCommVar,cmdnum );
			break;
		}
		case eFunc_SetInputExciterCtrl:
		{
			l_bStatus = 	mapp_CmdfuncSetInputExciterCtrl ( pCommVar,cmdnum );
			break;
		}
		case eFunc_SetInputCallInput:
		{
			l_bStatus = 	mapp_CmdfuncSetInputCallInput ( pCommVar,cmdnum );
			break;
		}
		case eFunc_SetInputBackgroundInput:
		{
			l_bStatus = 	mapp_CmdfuncSetInputBackgroundInput ( pCommVar,cmdnum );
			break;
		}
		case eFunc_SetInputDuckingGain:
		{
			l_bStatus = 	mapp_CmdfuncSetInputDuckingGain ( pCommVar,cmdnum );
			break;
		}
		case eFunc_SetInputDuckingThreshold:
		{
			l_bStatus = 	mapp_CmdfuncSetInputDuckingThreshold ( pCommVar,cmdnum );
			break;
		}
		case eFunc_SetInputDuckingDepth:
		{
			l_bStatus = 	mapp_CmdfuncSetInputDuckingDepth ( pCommVar,cmdnum );
			break;
		}
		case eFunc_SetInputDuckingStartTime:
		{
			l_bStatus = 	mapp_CmdfuncSetInputDuckingStartTime ( pCommVar,cmdnum );
			break;
		}
		case eFunc_SetInputDuckingHoldTime:
		{
			l_bStatus = 	mapp_CmdfuncSetInputDuckingHoldTime ( pCommVar,cmdnum );
			break;
		}
		case eFunc_SetInputDuckingReleaseTime:
		{
			l_bStatus = 	mapp_CmdfuncSetInputDuckingReleaseTime ( pCommVar,cmdnum );
			break;
		}
		case eFunc_SetInputDuckingCtrl:
		{
			l_bStatus = 	mapp_CmdfuncSetInputDuckingCtrl ( pCommVar,cmdnum );
			break;
		}
		case eFunc_SetMatrixSwitching:
		{
			l_bStatus = 	mapp_CmdfuncSetMatrixSwitching ( pCommVar,cmdnum );
			break;
		}
		case eFunc_SetOutputDelayTime:
		{
			l_bStatus = 	mapp_CmdfuncSetOutputDelayTime ( pCommVar,cmdnum );
			break;
		}
		case eFunc_SetOutputDelayCtrl:
		{
			l_bStatus = 	mapp_CmdfuncSetOutputDelayCtrl ( pCommVar,cmdnum );
			break;
		}
		case eFunc_SetUSBplayerCtrl:
		{
			l_bStatus = 	mapp_CmdfuncSetUSBplayerCtrl ( pCommVar,cmdnum );
			break;
		}


		case eFunc_GetProductName:
		{
			l_bStatus = 	mapp_CmdfuncGetProductName ( pCommVar,cmdnum );
			break;
		}
		case eFunc_GetAllAudioOutput:
		{
#if 0
			dbg_printf ( "xxxxxxxxxxxxxxxxxxxx\r\n" );
#endif
			l_bStatus = 	mapp_CmdfuncGetAllAudioOutput ( pCommVar,cmdnum );
			break;
		}
		case eFunc_GetInputSensitivity:
		{
			l_bStatus = 	mapp_CmdfuncGetInputSensitivity ( pCommVar,cmdnum );
			break;
		}
		case eFunc_GetInputGain:
		{
			l_bStatus = 	mapp_CmdfuncGetInputGain ( pCommVar,cmdnum );
			break;
		}
		case eFunc_GetInputMute:
		{
			l_bStatus = 	mapp_CmdfuncGetInputMute ( pCommVar,cmdnum );
			break;
		}
		case eFunc_GetInputReversephase:
		{
			l_bStatus = 	mapp_CmdfuncGetInputReversephase ( pCommVar,cmdnum );
			break;
		}
		case eFunc_GetInputTestSignalCtrl:
		{
			l_bStatus = 	mapp_CmdfuncGetInputTestSignalCtrl ( pCommVar,cmdnum );
			break;
		}
		case eFunc_GetInputTestSignalFreq:
		{
			l_bStatus = 	mapp_CmdfuncGetInputTestSignalFreq ( pCommVar,cmdnum );
			break;
		}
		case eFunc_GetInputTestSignalLevel:
		{
			l_bStatus = 	mapp_CmdfuncGetInputTestSignalLevel ( pCommVar,cmdnum );
			break;
		}
		case eFunc_GetInputCompressorCtrl:
		{
			l_bStatus = 	mapp_CmdfuncGetInputCompressorCtrl ( pCommVar,cmdnum );
			break;
		}
		case eFunc_GetInputCompressorGain:
		{
			l_bStatus = 	mapp_CmdfuncGetInputCompressorGain ( pCommVar,cmdnum );
			break;
		}
		case eFunc_GetInputCompressorThreshold:
		{
			l_bStatus = 	mapp_CmdfuncGetInputCompressorThreshold ( pCommVar,cmdnum );
			break;
		}
		case eFunc_GetInputCompressorRatio:
		{
			l_bStatus = 	mapp_CmdfuncGetInputCompressorRatio ( pCommVar,cmdnum );
			break;
		}
		case eFunc_GetInputCompressorStartTime:
		{
			l_bStatus = 	mapp_CmdfuncGetInputCompressorStartTime ( pCommVar,cmdnum );
			break;
		}
		case eFunc_GetInputCompressorReleasetime:
		{
			l_bStatus = 	mapp_CmdfuncGetInputCompressorReleasetime ( pCommVar,cmdnum );
			break;
		}
		case eFunc_GetInputAutoGainCtrl:
		{
			l_bStatus = 	mapp_CmdfuncGetInputAutoGainCtrl ( pCommVar,cmdnum );
			break;
		}
		case eFunc_GetInputAutoGainThreshold:
		{
			l_bStatus = 	mapp_CmdfuncGetInputAutoGainThreshold ( pCommVar,cmdnum );
			break;
		}
		case eFunc_GetInputAutoGainTargetThreshold:
		{
			l_bStatus = 	mapp_CmdfuncGetInputAutoGainTargetThreshold ( pCommVar,cmdnum );
			break;
		}
		case eFunc_GetInputAutoGainRatio:
		{
			l_bStatus = 	mapp_CmdfuncGetInputAutoGainRatio ( pCommVar,cmdnum );
			break;
		}
		case eFunc_GetInputAutoGainStartTime:
		{
			l_bStatus = 	mapp_CmdfuncGetInputAutoGainStartTime ( pCommVar,cmdnum );
			break;
		}
		case eFunc_GetInputAutoGainReleasetime:
		{
			l_bStatus = 	mapp_CmdfuncGetInputAutoGainReleasetime ( pCommVar,cmdnum );
			break;
		}
		case eFunc_GetInputEQType:
		{
			l_bStatus = 	mapp_CmdfuncGetInputEQType ( pCommVar,cmdnum );
			break;
		}
		case eFunc_GetInputEQGain:
		{
			l_bStatus = 	mapp_CmdfuncGetInputEQGain ( pCommVar,cmdnum );
			break;
		}
		case eFunc_GetInputEQQualityFactor:
		{
			l_bStatus = 	mapp_CmdfuncGetInputEQQualityFactor ( pCommVar,cmdnum );
			break;
		}
		case eFunc_GetInputEQCtrl:
		{
			l_bStatus = 	mapp_CmdfuncGetInputEQCtrl ( pCommVar,cmdnum );
			break;
		}
		case eFunc_GetInputHowlingSuppressorCtrl:
		{
			l_bStatus = 	mapp_CmdfuncGetInputHowlingSuppressorCtrl ( pCommVar,cmdnum );
			break;
		}
		case eFunc_GetInputHowlingSuppressorGrade:
		{
			l_bStatus = 	mapp_CmdfuncGetInputHowlingSuppressorGrade ( pCommVar,cmdnum );
			break;
		}
		case eFunc_GetInputHowlingSuppressorFreqShift:
		{
			l_bStatus = 	mapp_CmdfuncGetInputHowlingSuppressorFreqShift ( pCommVar,cmdnum );
			break;
		}
		case eFunc_GetInputNoiseSuppressorGrade:
		{
			l_bStatus = 	mapp_CmdfuncGetInputNoiseSuppressorGrade ( pCommVar,cmdnum );
			break;
		}
		case eFunc_GetInputNoiseSuppressorThreshold:
		{
			l_bStatus = 	mapp_CmdfuncGetInputNoiseSuppressorThreshold ( pCommVar,cmdnum );
			break;
		}
		case eFunc_GetInputNoiseSuppressorRatio:
		{
			l_bStatus = 	mapp_CmdfuncGetInputNoiseSuppressorRatio ( pCommVar,cmdnum );
			break;
		}
		case eFunc_GetInputNoiseSuppressorStartTime:
		{
			l_bStatus = 	mapp_CmdfuncGetInputNoiseSuppressorStartTime ( pCommVar,cmdnum );
			break;
		}
		case eFunc_GetInputNoiseSuppressorReleasetime:
		{
			l_bStatus = 	mapp_CmdfuncGetInputNoiseSuppressorReleasetime ( pCommVar,cmdnum );
			break;
		}
		case eFunc_GetInputNoiseSuppressorCtrl:
		{
			l_bStatus = 	mapp_CmdfuncGetInputNoiseSuppressorCtrl ( pCommVar,cmdnum );
			break;
		}
		case eFunc_GetInputEchoCancellerGrade:
		{
			l_bStatus = 	mapp_CmdfuncGetInputEchoCancellerGrade ( pCommVar,cmdnum );
			break;
		}
		case eFunc_GetInputEchoCancellerCtrl:
		{
			l_bStatus = 	mapp_CmdfuncGetInputEchoCancellerCtrl ( pCommVar,cmdnum );
			break;
		}
		case eFunc_GetInputLfreqExciterGrade:
		{
			l_bStatus = 	mapp_CmdfuncGetInputLfreqExciterGrade ( pCommVar,cmdnum );
			break;
		}
		case eFunc_GetInputHfreqExciterGrade:
		{
			l_bStatus = 	mapp_CmdfuncGetInputHfreqExciterGrade ( pCommVar,cmdnum );
			break;
		}
		case eFunc_GetInputExciterCtrl:
		{
			l_bStatus = 	mapp_CmdfuncGetInputExciterCtrl ( pCommVar,cmdnum );
			break;
		}
		case eFunc_GetInputCallInput:
		{
			l_bStatus = 	mapp_CmdfuncGetInputCallInput ( pCommVar,cmdnum );
			break;
		}
		case eFunc_GetInputBackgroundInput:
		{
			l_bStatus = 	mapp_CmdfuncGetInputBackgroundInput ( pCommVar,cmdnum );
			break;
		}
		case eFunc_GetInputDuckingGain:
		{
			l_bStatus = 	mapp_CmdfuncGetInputDuckingGain ( pCommVar,cmdnum );
			break;
		}
		case eFunc_GetInputDuckingThreshold:
		{
			l_bStatus = 	mapp_CmdfuncGetInputDuckingThreshold ( pCommVar,cmdnum );
			break;
		}
		case eFunc_GetInputDuckingDepth:
		{
			l_bStatus = 	mapp_CmdfuncGetInputDuckingDepth ( pCommVar,cmdnum );
			break;
		}
		case eFunc_GetInputDuckingStartTime:
		{
			l_bStatus = 	mapp_CmdfuncGetInputDuckingStartTime ( pCommVar,cmdnum );
			break;
		}
		case eFunc_GetInputDuckingHoldTime:
		{
			l_bStatus = 	mapp_CmdfuncGetInputDuckingHoldTime ( pCommVar,cmdnum );
			break;
		}
		case eFunc_GetInputDuckingReleasetime:
		{
			l_bStatus = 	mapp_CmdfuncGetInputDuckingReleasetime ( pCommVar,cmdnum );
			break;
		}
		case eFunc_GetInputDuckingCtrl:
		{
			l_bStatus = 	mapp_CmdfuncGetInputDuckingCtrl ( pCommVar,cmdnum );
			break;
		}
		case eFunc_GetMatrixSwitching:
		{
			l_bStatus = 	mapp_CmdfuncGetMatrixSwitching ( pCommVar,cmdnum );
			break;
		}
		case eFunc_GetOutputDelayTime:
		{
			l_bStatus = mapp_CmdfuncGetOutputDelayTime ( pCommVar,cmdnum );
			break;
		}
		case eFunc_GetOutputDelayCtrl:
		{
			l_bStatus = mapp_CmdfuncGetOutputDelayCtrl ( pCommVar,cmdnum );
			break;
		}
		case eFunc_GetUSBplayerCtrl:
		{
			l_bStatus = 	mapp_CmdfuncGetUSBplayerCtrl ( pCommVar,cmdnum );
			break;
		}
		case eFunc_GetAllData:
		{
			l_bStatus =  mapp_CmdfuncGetAllData ( pCommVar,cmdnum );
			break;
		}
		case eFunc_ResetData:
		{
			l_bStatus =  mapp_CmdfuncResetData ( pCommVar,cmdnum );
			break;
		}





		case eFunc_GetGUIFunction:
		{
			mapp_CmdfuncGetGUIFunction ( pCommVar,cmdnum );
			break;
		}
#endif//音频卡 - if-END
		/*音频卡(GUI - JSON,以"{"开始)主要功能 - 结束*/
		/**********************************************************/






		case eFunc_SetSTKCardFunction:
		{
			l_bStatus = mapp_CmdfuncSetSTKCardFunction ( pCommVar,cmdnum );
		}
		break;

		case eFunc_NoUse:
		case eFunc_Max:
		default:
			break;
	}
	if ( ( mapp_GetCommandFunctionID() !=eFunc_NoUse ) && ( mapp_GetCommandFunctionID() !=eFunc_Max ) )
	{
		mapp_SetCommandFunctionID ( eFunc_NoUse );
	}
	return l_bStatus;
}

bool mapp_CmdlenIsOK ( u8 index, pstUartCom_t pCommVar )
{
	dbg_printf ( "cmdlen:%d \t index:%d \t len1:%d \t len2:%d\r\n",pCommVar->u16RecCnt,index, \
	             ( strlen ( cmd_list[index].ucmd )+cmd_list[index].valuelen+cmd_list[index].cmdoffset ), \
	             ( strlen ( cmd_list[index].ucmd )+cmd_list[index].cmdoffset ) );
	if ( cmd_list[index].flag&Flag_UserValueLength )
	{
		if ( ( pCommVar->u16RecCnt<= ( strlen ( cmd_list[index].ucmd )+cmd_list[index].valuelen+cmd_list[index].cmdoffset ) )
		        && ( pCommVar->u16RecCnt>= ( strlen ( cmd_list[index].ucmd )+cmd_list[index].cmdoffset ) ) )
		{
			dbg_printf ( "%s step.1 return true!\r\n",__FUNCTION__ );
			return TRUE;
		}
	}
	else
	{
		if ( pCommVar->u16RecCnt== ( strlen ( cmd_list[index].ucmd )+cmd_list[index].valuelen+cmd_list[index].cmdoffset ) )
		{
			dbg_printf ( "%s step.2 return true!\r\n",__FUNCTION__ );
			return TRUE;
		}
	}

	dbg_printf ( "%s step.3 return false!\r\n",__FUNCTION__ );
	return FALSE;
}

void mapp_UsartSystemCmdFun ( pstUartCom_t pCommVar )
{
	u8 i;
	u8 l_u8Flag = 0;
	u8 l_u8Cmdnumber = 0;
	emCmdFuncStaType l_bStatus=emCmdError;
	u8 l_u8MatchCnt = 0;
	char* l_ps8StartStr = pCommVar->pRecBuffer;
	char* l_ps8EndStr = l_ps8StartStr;

	RS232_printf ( "cmd - uart buffer: %s \r\n",pCommVar->pRecBuffer );
	{
	RecheckCmd:
		l_u8MatchCnt = 0;
		for ( i=0; i<MaxCmdNum; i++ )
		{
			if ( cmd_list[i].eCmdFun==eFunc_Max || cmd_list[i].flag==Flag_End )
			{
				break;
			}

			if ( ( cmd_list[i].flag&Flag_NoFunction ) == Flag_NoFunction )
			{
				continue;
			}

#if 0
			if ( pCommVar->u8MatchCmdCounter == 4 )
			{
				dbg_printf ( "11111111111111111111111 %d %s\r\n",pCommVar->u8MatchCmdCounter,l_ps8StartStr );
			}
#endif

			if ( ( cmd_list[i].flag & Flag_HeadMatch ) == Flag_HeadMatch )
			{
#if 0

				if ( pCommVar->u8MatchCmdCounter == 4 )
				{
					dbg_printf ( "22222222222 l_ps8StartStr:%s,ucmd:%s,len:%d strncmp:%d \r\n",l_ps8StartStr,cmd_list[i].ucmd,strlen ( cmd_list[i].ucmd ), strncmp ( l_ps8StartStr,cmd_list[i].ucmd,strlen ( cmd_list[i].ucmd ) ) );
				}
#endif
				if ( strncmp ( l_ps8StartStr,cmd_list[i].ucmd,strlen ( cmd_list[i].ucmd ) ) == 0 )
				{

#if 0

					if ( pCommVar->u8MatchCmdCounter == 4 )
					{
						dbg_printf ( "33333333333333 l_ps8StartStr:%s,ucmd:%s,len:%d\r\n",l_ps8StartStr,cmd_list[i].ucmd,strlen ( cmd_list[i].ucmd ) );
					}
#endif

					pCommVar->bIsMultiCmdDetect = TRUE;              //需要执行多条命令
					if ( pCommVar->u8MatchCmdCounter < MaxCmdlist )
					{
#if 0
						if ( pCommVar->u8MatchCmdCounter == 4 )
						{
							dbg_printf ( "44444444444444444444\r\n" );
						}
#endif

						if (* ( l_ps8StartStr + strlen ( cmd_list[i].ucmd ) - 1 ) != ')' ) // 指令不是以')'结尾
						{
#if 0
							if ( pCommVar->u8MatchCmdCounter == 4 )
							{
								dbg_printf ( "55555555555555555555\r\n" );
							}
#endif
#if 0
							dbg_printf ( "if - cmd_list[%d].ucmd: %s \r\n      \
                             										strlen cmd_list-ucmd: %d \r\n          \
                             										cmdlength: %d \r\n                    \
                             										match char: %c \r\n                   \
                             										counter: %d \r\n", \
							             i,cmd_list[i].ucmd, \
							             strlen ( cmd_list[i].ucmd ), \
							             Cmdlength ( i ), \
							             * ( l_ps8StartStr + strlen ( cmd_list[i].ucmd ) - 1 ), \
							             pCommVar->u8MatchCmdCounter );
#endif
							if ( cmd_list[i].valuelen == 0 )
							{
								l_ps8EndStr = FindChar ( l_ps8StartStr+strlen ( cmd_list[i].ucmd ),')',Cmdlength ( i ) - 1 ); // delet end char self
							}
							else
							{
								//l_ps8EndStr = FindChar(l_ps8StartStr + strlen(cmd_list[i].ucmd), ')' ,Cmdlength(i));
								l_ps8EndStr = FindChar ( l_ps8StartStr+strlen ( cmd_list[i].ucmd ),')',Cmdlength ( i ) ); //可以加快匹配速度
							}

							pCommVar->stMultiCmdType[pCommVar->u8MatchCmdCounter].u8CmdCounter = ( char* ) l_ps8EndStr - l_ps8StartStr/*+strlen(cmd_list[i].ucmd)*/ + 1; // 指令结尾加上结束符本身

#if 0
							dbg_printf ( "l_ps8EndStr:%x,l_ps8StartStr:%x\r\n",l_ps8EndStr,l_ps8StartStr );
							dbg_printf ( "u8CmdCounter:%d,l_ps8EndStr - l_ps8StartStr + 1:%d\r\n",pCommVar->stMultiCmdType[pCommVar->u8MatchCmdCounter].u8CmdCounter,l_ps8EndStr - l_ps8StartStr + 1 );
#endif
						}
						else
						{
#if 0
							if ( pCommVar->u8MatchCmdCounter == 4 )
							{
								dbg_printf ( "6666666666666666666\r\n" );
							}
#endif

#if 0
							dbg_printf ( "else - cmd_list[%d].ucmd: %s, \t strlen cmd_list-ucmd: %d\t ,cmdlength: %d \r\n",i,cmd_list[i].ucmd, strlen ( cmd_list[i].ucmd ), Cmdlength ( i ) );
#endif

							l_ps8EndStr = l_ps8StartStr + strlen ( cmd_list[i].ucmd );
							//l_ps8EndStr = FindChar(l_ps8StartStr+strlen(cmd_list[i].ucmd),')',Cmdlength(i));
							pCommVar->stMultiCmdType[pCommVar->u8MatchCmdCounter].u8CmdCounter = ( char* ) l_ps8EndStr - l_ps8StartStr/*+strlen(cmd_list[i].ucmd)*/;
						}

						memcpy ( pCommVar->stMultiCmdType[pCommVar->u8MatchCmdCounter].s8MultiCmd,l_ps8StartStr/*-strlen(cmd_list[i].ucmd)*/,pCommVar->stMultiCmdType[pCommVar->u8MatchCmdCounter].u8CmdCounter );
						memset ( l_ps8StartStr,'0',pCommVar->stMultiCmdType[pCommVar->u8MatchCmdCounter].u8CmdCounter ); // 覆盖已识别的指令
						l_ps8StartStr = l_ps8StartStr+pCommVar->stMultiCmdType[pCommVar->u8MatchCmdCounter].u8CmdCounter;

						dbg_printf ( "cmd:%s\r\n",pCommVar->stMultiCmdType[pCommVar->u8MatchCmdCounter].s8MultiCmd );
						dbg_printf ( "len:%d\r\n",pCommVar->stMultiCmdType[pCommVar->u8MatchCmdCounter].u8CmdCounter );

#if 0
						if ( pCommVar->u8MatchCmdCounter == 4 )
						{
							dbg_printf ( "777777777777777777777\r\n" );
						}
#endif

						//i = 0;
					}
					else
					{
						l_u8MatchCnt = 0;
						break;
					}

					pCommVar->u8MatchCmdCounter++;
					if ( pCommVar->u8MatchCmdCounter>MaxCmdlist )
					{
						pCommVar->u8MatchCmdCounter=MaxCmdlist;
					}

					l_u8MatchCnt++;

					dbg_printf ( "cnt:%d\r\n",pCommVar->u8MatchCmdCounter );

#if 0
					if ( pCommVar->u8MatchCmdCounter == 4 )
					{
						dbg_printf ( "888888888888888888888888\r\n" );
					}
#endif

					break;
				}
				else
				{
//                    if(pCommVar->u8MatchCmdCounter==0)
//                        pCommVar->bIsMultiCmdDetect = FALSE;
					if ( cmd_list[i].eCmdFun==eFunc_Max || cmd_list[i].flag==Flag_End )
					{
#if 0
						if ( pCommVar->u8MatchCmdCounter == 4 )
						{
							dbg_printf ( "aaaaaaaaaaaaaaaaaaaaaaaaaaaa\r\n" );
						}
#endif
						break;
					}
					else
					{
#if 0
						if ( pCommVar->u8MatchCmdCounter == 4 )
						{
							dbg_printf ( "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbb\r\n" );
						}
#endif
						continue;
					}
#if 0
					if ( pCommVar->u8MatchCmdCounter == 4 )
					{
						dbg_printf ( "9999999999999999999999999\r\n" );
					}
#endif
				}
				//break;
			}
			else if ( ( cmd_list[i].flag&Flag_NomalMatch ) ==Flag_NomalMatch )
			{
#if 0
				if ( strcmp ( pCommVar->pRecBuffer,cmd_list[i].ucmd ) ==0 )
				{
					mapp_SetCommandFunctionID ( cmd_list[i].eCmdFun );
					l_u8Flag = cmd_list[i].flag;
					l_u8Cmdnumber = i;
					break;
				}
#endif
				//ME - HY
				//extern SemaphoreHandle_t xSemaphore_PRINT_DBG;
				//xSemaphoreTake(xSemaphore_PRINT_DBG,portMAX_DELAY);

				//xSemaphoreGive(xSemaphore_PRINT_DBG);
				if ( ( strncmp ( pCommVar->pRecBuffer,cmd_list[i].ucmd,strlen ( cmd_list[i].ucmd ) ) == 0 ) //音频卡
				        && ( mapp_CmdlenIsOK ( i,pCommVar ) )
				   )
				{
					mapp_SetCommandFunctionID ( cmd_list[i].eCmdFun );
					l_u8Flag = cmd_list[i].flag;
					l_u8Cmdnumber = i;
					break;
				}
			}
			else if ( ( cmd_list[i].flag&Flag_MiddleMatch ) ==Flag_MiddleMatch )
			{
				char* l_ps8tempStr = my_StrStr ( l_ps8StartStr,cmd_list[i].ucmd );
				if ( l_ps8tempStr != NULL )
				{
					pCommVar->bIsMultiCmdDetect = TRUE;
					if ( pCommVar->u8MatchCmdCounter<MaxCmdlist )
					{
						if (* ( l_ps8tempStr-1 ) != ')' ) // 指令不是以')'结尾
						{
							if ( cmd_list[i].valuelen==0 )
							{
								l_ps8EndStr = FindChar ( l_ps8tempStr,')',Cmdlength ( i )-1 );    // delet end char self
							}
							else
							{
								l_ps8EndStr = FindChar ( l_ps8tempStr,')',Cmdlength ( i ) );
							}
							pCommVar->stMultiCmdType[pCommVar->u8MatchCmdCounter].u8CmdCounter = ( char* ) l_ps8EndStr-l_ps8tempStr+strlen ( cmd_list[i].ucmd )+1; // 指令结尾加上结束符本身
						}
						else
						{
							l_ps8EndStr = l_ps8tempStr;
							pCommVar->stMultiCmdType[pCommVar->u8MatchCmdCounter].u8CmdCounter = ( char* ) l_ps8EndStr-l_ps8tempStr+strlen ( cmd_list[i].ucmd );
						}
						memcpy ( pCommVar->stMultiCmdType[pCommVar->u8MatchCmdCounter].s8MultiCmd,l_ps8tempStr-strlen ( cmd_list[i].ucmd ),pCommVar->stMultiCmdType[pCommVar->u8MatchCmdCounter].u8CmdCounter );
						l_ps8StartStr = l_ps8StartStr+pCommVar->stMultiCmdType[pCommVar->u8MatchCmdCounter].u8CmdCounter;
						dbg_printf ( "cmd:%s\r\n",pCommVar->stMultiCmdType[pCommVar->u8MatchCmdCounter].s8MultiCmd );
						dbg_printf ( "len:%d\r\n",pCommVar->stMultiCmdType[pCommVar->u8MatchCmdCounter].u8CmdCounter );
					}
					else
					{
						l_u8MatchCnt = 0;
						break;
					}
					memset ( l_ps8tempStr-strlen ( cmd_list[i].ucmd ),'0',strlen ( cmd_list[i].ucmd ) ); // 覆盖已识别的指令
					pCommVar->u8MatchCmdCounter++;
					if ( pCommVar->u8MatchCmdCounter>MaxCmdlist )
					{
						pCommVar->u8MatchCmdCounter=MaxCmdlist;
					}
					l_u8MatchCnt++;

					break;
				}
				else
				{
					if ( pCommVar->u8MatchCmdCounter==0 )
					{
						pCommVar->bIsMultiCmdDetect = FALSE;
					}
				}
			}
		}

		if ( l_u8MatchCnt>0 )
		{
			goto RecheckCmd;
		}

#if 0
		if (!pstBasicSpecVar->bPowerOnSta )
		{
			if ( ( mapp_GetCommandFunctionID() != eFunc_SwitchPowerState )
			        && ( mapp_GetCommandFunctionID() != eFunc_GetPowerState )
			        && ( mapp_GetCommandFunctionID() != eFunc_FactoryReset )
			   )
			{
				mapp_SetCommandFunctionID ( eFunc_NoUse );
				return;
			}
		}
#endif

		if ( pCommVar->u8MatchCmdCounter )
		{
			l_bStatus = emCmdNone;
		}
		else
		{
			l_bStatus = mapp_CommandFunctionProcess ( l_u8Cmdnumber,l_u8Flag, pCommVar );
		}
	}

	if ( l_bStatus == emCmdError )
	{
		pCommVar->SendPrintf ( "err\r\n" );
	}
	else if ( l_bStatus == emCmdOutOfRange )
	{
		pCommVar->SendPrintf ( "out of range\r\n" );
	}
	else if ( l_bStatus == emCmdSucess )
	{
		pCommVar->SendPrintf ( "ok\r\n" );
	}
}

#if 1
void mapp_MultiCmdMatchFunction ( pstUartCom_t pCommVar )
{
	u8 i/*,j*/;
	char* l_ps8Cmdbuf = NULL;  //g_CMMFCmd;
	//u8 l_u8RankingCmdCnt[MaxCmdlist];
	static u8 sl_u8CmdIndex = 0;
	u8 l_u8Flag = 0;
	u8 l_u8Cmdnumber = 0;
	emCmdFuncStaType l_bStatus=emCmdError;

	if ( g_u8MultiCmdDelayCounter )
	{
		g_u8MultiCmdDelayCounter--;
		return;
	}

	l_ps8Cmdbuf = pCommVar->stMultiCmdType[sl_u8CmdIndex].s8MultiCmd;

#if 0
	dbg_printf ( "%s: %s\r\n",__FUNCTION__,l_ps8Cmdbuf );
#endif

	for ( i=0; i<MaxCmdNum ; i++ )
	{
		if ( pCommVar->stMultiCmdType[sl_u8CmdIndex].u8CmdCounter!=0 )
		{
			if ( strncmp ( l_ps8Cmdbuf,cmd_list[i].ucmd,strlen ( cmd_list[i].ucmd ) ) ==NULL ) // 识别命令
			{
				mapp_SetCommandFunctionID ( cmd_list[i].eCmdFun );
				l_u8Flag = cmd_list[i].flag;
				l_u8Cmdnumber = i;
				pCommVar->bIsMultiCmdDetect = TRUE;
				memcpy ( pCommVar->pRecBuffer, l_ps8Cmdbuf,pCommVar->stMultiCmdType[sl_u8CmdIndex].u8CmdCounter );
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

	l_bStatus = mapp_CommandFunctionProcess ( l_u8Cmdnumber,l_u8Flag, pCommVar );
	if ( i >= MaxCmdNum|| ( sl_u8CmdIndex>=MaxCmdlist ) || ( sl_u8CmdIndex>=pCommVar->u8MatchCmdCounter ) )
	{
		pCommVar->bIsMultiCmdDetect = FALSE;
		sl_u8CmdIndex = 0;
		pCommVar->u8MatchCmdCounter= 0;
		memset ( pCommVar->stMultiCmdType,0,sizeof ( stMultiCmdType_t ) *MaxCmdlist ); // clean buffer
		//_Printf("end: %d\r\n",0);
	}
	if ( l_bStatus == emCmdError )
	{
		pCommVar->SendPrintf ( "err\r\n" );
	}
	else if ( l_bStatus == emCmdOutOfRange )
	{
		pCommVar->SendPrintf ( "out of range\r\n" );
	}
	else if ( l_bStatus == emCmdSucess )
	{
		pCommVar->SendPrintf ( "ok\r\n" );
	}
}
#endif

void mapp_SetPowerState ( bool bPwrSta )
{
	pstProjectSpecVar_t			pstSpecVar = &stLMX_4IUHS_CSpecVar;
	pstBasicSpecVar_t			pstBasicSpecVar = &pstSpecVar->stBasSpecVar;

	dbg_printf ( "%s,%d\r\n",__FUNCTION__,__LINE__ );

	if ( bPwrSta )
	{
		if (!pstBasicSpecVar->bPowerOnSta )
		{
			pstBasicSpecVar->bPowerOnSta = TRUE;
			SetUserData_SpecBasicVar();
		}
	}
	else
	{
		if ( pstBasicSpecVar->bPowerOnSta )
		{
			pstBasicSpecVar->bPowerOnSta = FALSE;
			SetUserData_SpecBasicVar();
		}
	}
}

void mapp_Usart1SystemCmdFun ( pstUartCom_t pCommVar )
{
	u8 l_u8Addr;
	u8 l_u8Cmd;
//    u8 l_u8ID=0;
	if ( ( pCommVar->pRecBuffer[0]==0xFF ) && ( pCommVar->pRecBuffer[1]==0xFF ) && ( pCommVar->pRecBuffer[2]==0xA5 ) )
	{
		l_u8Addr = pCommVar->pRecBuffer[3];
		l_u8Cmd = pCommVar->pRecBuffer[4];

		dbg_printf ( "addr[0x%x],cmd[0x%x]\r\n",l_u8Addr,l_u8Cmd );
	}
}

#if _ENABLE_USER_EDID_LEARNING_FUNCTION
void mapp_UartUserEdidReceive ( pstUartCom_t pUartCommVar )
{
}
#endif

