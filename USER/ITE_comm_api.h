#ifndef __ITE_COMM_API_H_
#define __ITE_COMM_API_H_

#ifndef EDID_START_ADDR_SAME_WITH_BOOT
#define EDID_START_ADDR_SAME_WITH_BOOT			0x08038000
#endif

#ifndef SIZE_UART_KEY_VALUE_MAX
#define SIZE_UART_KEY_VALUE_MAX						80
#endif
#ifndef SIZE_PRJ_NAME_CHARS_MAX
#define SIZE_PRJ_NAME_CHARS_MAX						60
#endif

typedef enum
{
    etKEY_Detect,
    #if _ENABLE_NEW_USER_KEY_DEFINE_FUNCTION
    etKEY_CobomTime,
    #endif
    #if _ENABLE_USER_EDID_LEARNING_FUNCTION
    etUserEdidReceiveTime,
    #endif
    #if _ENABLE_UART_LEARNING_MESSAGE_FUNCTION
    etUserMsgTimer0,// = 3,
    etUserMsgTimerLast = etUserMsgTimer0+uart_study_key_type_max-1,
    #endif
    #if _ENABLE_SYSTEM_RESET_DELAY_TIME
    etSysResetTimer,
    #endif
    #if _ENABLE_STARTUP_TO_MATCHING_CHIPID
    etSysChipIDErrFuncTimer,
    #endif
    #if _ENABLE_SWITCH_PORT_INIT_CEC_FUNCTION
    etUser_CecInitTimer,
    #endif
    #if _ENABLE_SWITCH_PORT_AFTER_A_FEW_TIME_LATER
    etUser_SwitchPortTimer,
    #endif
    #if _ENABLE_START_UP_TO_ENABLE_EXTERNAL_AUDIO
    etUser_StartupAudioTimer,
    #endif
	#if  _ENABLE_DETECT_SYNC_TO_SEND_CEC_AND_RS232CMD  /*Ìí¼Ó2019.2.14*/
	etDetectDisplayTimer,
	#endif          /*Ìí¼Ó2019.2.14*/
    #if _ENABLE_AUDIO_SOURCE_SWITCH_TIMER
    etUser_AudioSrcSwitchTimer,
    #endif
    #if _ENABLE_IT6615_STARTUP_TODO_HDCP_TIMER
    etUser_It6615StartupTimer,
    #endif
    #if _ENABLE_SWITCH_LED_TIMER
    etUser_SwitchLedTimer,
    #endif
    #if _ENABLE_WIN_CONFIG_UPD_TIMER
    etUser_WinCfgUpdTimer,
    #endif
    etINVALID,  // not remove

}eTIMER;

typedef __packed struct _stUartKeyValue_t_
{
    #if(_ENABLE_UART_KEY_VALUE_MAX_BUG == _MACRO_ENABLE)
	char 		sKeyValueBuffer[SIZE_UART_KEY_VALUE_MAX+1];
    #else
	char 		sKeyValueBuffer[SIZE_UART_KEY_VALUE_MAX];
    #endif
	uint16_t 	u16KeyValueLen;
	uint32_t 	u32BaudRate;
    bool        bUartValueHexOrAsciiFlag;  // TRUE: HEX ; FALSE: ASCII
    u16         u16UartValueSendDelayTime;
    u8          u8UartValueSendMessageNum;
    u16         u16UartValueCounterDelayTime;
    #if _ENABLE_UART_LEARN_TO_MULTI_FUNCTION
    u8          u8SendPort;     // add by wf8421 20190819
    u8          u8SendWhoFollow;     // add by wf8421 20190822
    #endif
	uint8_t 	u8CheckSum;
}stUartKeyValue_t, *pstUartKeyValue_t;

#define EQ 10
#define EQ_CMD_SIZE 4
#define MAX_CH_LEN 9
#define MAX_SET_CMD_SIZE 52
#define MAX_BP_CMD_LEN 5

typedef struct _stMachineVal_
{
	u32 				ch;
	//u8		no[9];
	u16		 param1[MAX_CH_LEN];
	u16		 param2[MAX_CH_LEN];
	u8		  param3[MAX_CH_LEN];
	//u8		  param4[9];
	//u8		param5[9];
	u8  command[MAX_BP_CMD_LEN];
} stMachVal_t, *pststMachVal_t;

typedef struct _stEQVal_
{
 u32 ch;
}stEQVal_t, *pstEQVal_t;


typedef __packed struct _stProjectNameSet_t_
{
	char 		sPrjName[SIZE_PRJ_NAME_CHARS_MAX];
    uint8_t     m_u8Len;
	uint8_t 	u8CheckSum;
}stProjectNameSet_t, *pstProjectNameSet_t;

typedef struct _stPrjSpecVarVector_t_
{
	void *					pvSpecVar;
	uint16_t				u16SpecVarSize;
}stPrjSpecVarVector_t, *pstPrjSpecVarVector_t;

typedef struct _stProjectGlobalSaveVar_t_
{
	#if 0
#if ((_IR_FUNCTION_USE&_IR_FUNCTION_KEY_STUDY)==_IR_FUNCTION_KEY_STUDY)
	stIrKeyWave_t			stIrStudyKeyData[_NUM_IR_STUDY_KEYS];
#endif //add by wf8421
    #if _ENABLE_UART_LEARNING_MESSAGE_FUNCTION
	stUartKeyValue_t		stUartStudyKeyData[_NUM_UART_STUDY_KEYS];
    #endif
  #endif 

	#if 1 
		stMachVal_t guiParamter[MAX_SET_CMD_SIZE];
	 u16 EQParamter[EQ_CMD_SIZE][MAX_CH_LEN*EQ];
	#endif 
  
	stProjectNameSet_t		stPrjNameSet;

	stPrjSpecVarVector_t	stSaveSpecVar;//The project specific var one should be the last one
}stProjectGlobalSaveVar_t, *pstProjectGlobalSaveVar_t;

typedef struct _stProjectGlobalAllVar_t_
{
	stProjectGlobalSaveVar_t	stPrjSaveVar;
}stProjectGlobalAllVar_t, *pstProjectGlobalAllVar_t;


typedef struct
{
    uint16_t u16Year;
    uint8_t  u8Month;
    uint8_t  u8Date;
    uint8_t  u8Hour;
    uint8_t  u8minute;
    uint8_t  u8Second;
}stVersionType;

extern const unsigned char DataStr[];
extern const unsigned char TimeStr[];
extern stVersionType g_stTestVersion;
extern stProjectGlobalAllVar_t g_stPrjGloVar;

uint8_t CRC8Calculate(void *pBuf ,unsigned pBufSize);

#if _ENABLE_UART_LEARNING_MESSAGE_FUNCTION

void mapp_UserDataUartKeyValInit(u8 u8Index);
bool mapp_UserDataUartKeyValCheck(void);
void SetUserData_UartKeyVal(uint8_t u8KeyIndex);
void SetUserData_UartKeyValSaveAll(void);

void mapp_UserDataIrStudyValInit(u8 u8Index);
bool mapp_UserDataIrStudyValCheck(void);
void SetUserData_IrStudyVal(uint8_t u8KeyIndex, bool bIsr);
void SetUserData_IrStudyValSaveAll(bool bIsr);
#endif


void mapp_UserDataProjectNameInit(void);
bool mapp_UserDataProjectNameCheck(void);
void SetUserData_ProjectName(char *strPrjName, uint8_t len);



u8 HexAndAsciiChange(u8 cvalue,u8 cmode);
bool isNumberCmd(char *cmd, uint16_t len);

u32 PlatformTimerGet(uint8_t eTimer);
void PlatformTimerSet( uint8_t index, u32 m_sec );
void PlatformTimerInit (void);
void PlatformTimerTask(void);
uint8_t PlatformTimerExpired( uint8_t timer );

char *my_StrStr(char *inBuffer,char *inSerchStr);
char *my_CaseStrStr(char *inBuffer,char *inSerchStr);
char *FindChar(char *buf,char Taildata,uint16_t Bitwide);
unsigned short StrToNum(char *Str,unsigned char cursor);
unsigned short NumToStr(char* buf,char* Str,unsigned char member);
short GetNumofStr(char *buf,char Taildata,unsigned char Bitwide);
unsigned char GetLenOfStr(char *buf,char Taildata,unsigned char Bitwide);
void bubble_sort(u8* a, u8 n,u8 mode);
void mapp_RevisionMake(void);
bool buffer_compare(pu8 arry1,pu8 arry2,u16 u16Len);
u16 U16ToU8MsbCovert(pu16 arry1,pu8 arry2,u16 u16Len);
u16 U8ToU16MsbCovert(pu8 arry1,pu16 arry2,u16 u16Len);

#endif


































