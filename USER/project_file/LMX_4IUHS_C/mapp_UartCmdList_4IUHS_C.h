#ifndef __CMD_LIST_H__
#define __CMD_LIST_H__

typedef enum
{
	eFunc_NoUse = 0,
	eFunc_GetVersion,
	eFunc_FactoryReset,
	eFunc_Reboot,
	eFunc_SwitchInputPort,
	eFunc_GetInputStutus,
	eFunc_PowerStandby,
	eFunc_PowerWakeup,
	eFunc_GetPowerState,
	eFunc_HelpFunction,
	eFunc_GetTestVersion,
	eFunc_SetTxResolution,
	eFunc_GetTxResolution,
	eFunc_GetRxResolution,
	eFunc_SetTxHdcpMode,
	eFunc_GetTxHdcpMode,
	eFunc_SetTxFormat,
	eFunc_GetTxFormat,

	eFunc_SetFreezeState,
	eFunc_GetFreezeState,
	eFunc_SwitchFreeze,

	eFunc_SetBrightness,
	eFunc_GetBrightness,
	eFunc_SetContrast,
	eFunc_GetContrast,
	eFunc_SetSaturation,
	eFunc_GetSaturation,
	eFunc_SetHue,
	eFunc_GetHue,

	eFunc_SetRxEdidMode,
	eFunc_GetRxEdidMode,
	eFunc_UpdateUserEdid,
	eFunc_GetTxEdidData,

	eFunc_SetTxTiming,
	eFunc_SetTxPattern,
	eFunc_GetTxPattern,
	eFunc_SetColor,
	eFunc_GetColor,
	eFunc_SetDebugEn,
	eFunc_SetMs1826Hold,
	eFunc_BypassSwitchPort,
	eFunc_ModeSwitch,

	//add by hy 2024/12/18 START
	eFunc_SetProductName,
	eFunc_SetAllAudioOutput,
	eFunc_SetInputSensitivity,
	eFunc_SetInputGain,
	eFunc_SetInputMute,
	eFunc_SetInputReversephase,
	eFunc_SetInputTestSignalCtrl,
	eFunc_SetInputTestSignalFreq,
	eFunc_SetInputTestSignalLevel,
	eFunc_SetInputCompressorCtrl,
	eFunc_SetInputCompressorGain,
	eFunc_SetInputCompressorThreshold,
	eFunc_SetInputCompressorRatio,
	eFunc_SetInputCompressorStartTime,
	eFunc_SetInputCompressorReleaseTime,
	eFunc_SetInputAutoGainCtrl,
	eFunc_SetInputAutoGainThreshold,
	eFunc_SetInputAutoGainTargetThreshold,
	eFunc_SetInputAutoGainRatio,
	eFunc_SetInputAutoGainStartTime,
	eFunc_SetInputAutoGainReleaseTime,
	eFunc_SetInputEQType,
	eFunc_SetInputEQGain,
	eFunc_SetInputEQQualityFactor,
	eFunc_SetInputEQCtrl,
	eFunc_SetInputHowlingSuppressorCtrl,
	eFunc_SetInputHowlingSuppressorGrade,
	eFunc_SetInputHowlingSuppressorFreqShift,
	eFunc_SetInputNoiseSuppressorGrade,
	eFunc_SetInputNoiseSuppressorThreshold,
	eFunc_SetInputNoiseSuppressorRatio,
	eFunc_SetInputNoiseSuppressorStartTime,
	eFunc_SetInputNoiseSuppressorReleaseTime,
	eFunc_SetInputNoiseSuppressorCtrl,
	eFunc_SetInputEchoCancellerGrade,
	eFunc_SetInputEchoCancellerCtrl,
	eFunc_SetInputLfreqExciterGrade,
	eFunc_SetInputHfreqExciterGrade,
	eFunc_SetInputExciterCtrl,
	eFunc_SetInputCallInput,
	eFunc_SetInputBackgroundInput,
	eFunc_SetInputDuckingGain,
	eFunc_SetInputDuckingThreshold,
	eFunc_SetInputDuckingDepth,
	eFunc_SetInputDuckingStartTime,
	eFunc_SetInputDuckingHoldTime,
	eFunc_SetInputDuckingReleaseTime,
	eFunc_SetInputDuckingCtrl,
	eFunc_SetMatrixSwitching,
	eFunc_SetOutputDelayTime,
	eFunc_SetOutputDelayCtrl,
	eFunc_SetUSBplayerCtrl,

	eFunc_GetProductName,
	eFunc_GetAllAudioOutput,
	eFunc_GetInputSensitivity,
	eFunc_GetInputGain,
	eFunc_GetInputMute,
	eFunc_GetInputReversephase,
	eFunc_GetInputTestSignalCtrl,
	eFunc_GetInputTestSignalFreq,
	eFunc_GetInputTestSignalLevel,
	eFunc_GetInputCompressorCtrl,
	eFunc_GetInputCompressorGain,
	eFunc_GetInputCompressorThreshold,
	eFunc_GetInputCompressorRatio,
	eFunc_GetInputCompressorStartTime,
	eFunc_GetInputCompressorReleasetime,
	eFunc_GetInputAutoGainCtrl,
	eFunc_GetInputAutoGainThreshold,
	eFunc_GetInputAutoGainTargetThreshold,
	eFunc_GetInputAutoGainRatio,
	eFunc_GetInputAutoGainStartTime,
	eFunc_GetInputAutoGainReleasetime,
	eFunc_GetInputEQType,
	eFunc_GetInputEQGain,
	eFunc_GetInputEQQualityFactor,
	eFunc_GetInputEQCtrl,
	eFunc_GetInputHowlingSuppressorCtrl,
	eFunc_GetInputHowlingSuppressorGrade,
	eFunc_GetInputHowlingSuppressorFreqShift,
	eFunc_GetInputNoiseSuppressorGrade,
	eFunc_GetInputNoiseSuppressorThreshold,
	eFunc_GetInputNoiseSuppressorRatio,
	eFunc_GetInputNoiseSuppressorStartTime,
	eFunc_GetInputNoiseSuppressorReleasetime,
	eFunc_GetInputNoiseSuppressorCtrl,
	eFunc_GetInputEchoCancellerGrade,
	eFunc_GetInputEchoCancellerCtrl,
	eFunc_GetInputLfreqExciterGrade,
	eFunc_GetInputHfreqExciterGrade,
	eFunc_GetInputExciterCtrl,
	eFunc_GetInputCallInput,
	eFunc_GetInputBackgroundInput,
	eFunc_GetInputDuckingGain,
	eFunc_GetInputDuckingThreshold,
	eFunc_GetInputDuckingDepth,
	eFunc_GetInputDuckingStartTime,
	eFunc_GetInputDuckingHoldTime,
	eFunc_GetInputDuckingReleasetime,
	eFunc_GetInputDuckingCtrl,
	eFunc_GetMatrixSwitching,
	eFunc_GetOutputDelayTime,
	eFunc_GetOutputDelayCtrl,
	eFunc_GetUSBplayerCtrl,
	eFunc_GetAllData,
  eFunc_ResetData,

	eFunc_AUDIO_END,
	//add by hy 2024/12/18 END

	eFunc_CheckOutputCardType,
	eFunc_CheckCardFWVersion,
#if ENABLE_CARD_YBJ_RECORD
	eFunc_CheckYBJCardType,
	eFunc_CheckYBJ2CardType,
#endif
	eFunc_SetCardFunction,
	eFunc_GetCardFunction,
	eFunc_SetGUIFunction,
	eFunc_GetGUIFunction,
	eFunc_SetSTKCardFunction,
	eFunc_CheckCardMode,
	eFunc_CheckSetEdidData,
	eFunc_FactoryReset2,

	eFunc_Max,
} eCmdFun_t;

typedef enum _emCommandFunctionStatusType_
{
	emCmdError = 0,
	emCmdSucess,
	emCmdOutOfRange,
	emCmdNone,

	emCmdStatusMax,
} emCmdFuncStaType;

typedef enum _emInDirection
{
	emInLeft = 0,
	emInRight = 1,
} emInDirection;

typedef enum _emOutDirection
{
	emOutLeft = 0,
	emOutRight = 1,
} emOutDirection;


typedef struct _stUartCmdList2
{
	u8      flag;           // ��־
	char*   ucmd;           // ָ�����ָ�ͷ����
	u8      cmdlen;          // ָ���
	u16      valuelen;       // ָ�����������,ȫ��ƥ����Ϊ0
	u8     cmdoffset;       // ָ��ƫ����,һ�㶼��ָ���β���ĳ��� ,���ݲ�ָͬ���ʽ��д
	eCmdFun_t    eCmdFun;   // ָ���
	char* feedbackstring;
} stUartCmdList2;

// command list Flag define
#define UserOffset      255
#define MaxCmdNum       255
#define UseStrlen       0
#define NoString        NULL

#define Flag_End            0
#define Flag_BackCodeNomal  0x01
#define Flag_BackCodeFunc   0x02
#define Flag_ShowHelpCommand    0x04
#define Flag_UserValueLength    0x08
#define Flag_NomalMatch     0x10
#define Flag_HeadMatch      0x20
#define Flag_MiddleMatch    0x40
#define Flag_NoFunction     0x80

const stUartCmdList2 cmd_list[]=
{
#if 0
	{
		Flag_HeadMatch|Flag_ShowHelpCommand,       /*flag*/
		"(ver)",/*ucmd*/
		UseStrlen,              /*cmdlen*/
		0,                      // valuelen
		0,                      /*cmdoffset*/
		eFunc_GetVersion,       /*eCmdFun*/
		_STRING_FW_VER_NUM,           /*feedbackstring*/
	},
	{
		Flag_HeadMatch|Flag_ShowHelpCommand,       // flag
		"(reset)",                 //ucmd
		UseStrlen,              // cmdlen
		0,                      // valuelen
		0,                      // cmdoffset
		eFunc_FactoryReset,     // eCmdFun
		"factory reset",        // feedbackstring
	},
	{
		Flag_HeadMatch|Flag_ShowHelpCommand,        // flag
		"(reboot)",              //ucmd
		UseStrlen,              // cmdlen
		0,                      // valuelen
		0,                      // cmdoffset
		eFunc_Reboot,           // eCmdFun
		"system reboot",    // feedbackstring
	},
	//(sw,01,01,02,03,04,05,06,07,08,09,10,11,12,13,14,15,16)
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(sw,",              //ucmd
		4,                      // cmdlen
		50,                      // valuelen
		1,                      // cmdoffset
		eFunc_SwitchInputPort,  // eCmdFun
		" ",                    // feedbackstring
	},
	{
		Flag_HeadMatch|Flag_ShowHelpCommand,       // flag
		"(get,sw)",              //ucmd
		UseStrlen,              // cmdlen
		0,                      // valuelen
		0,                      // cmdoffset
		eFunc_GetInputStutus,   // eCmdFun
		" ",             // feedbackstring
	},

	{
		Flag_HeadMatch|Flag_ShowHelpCommand,       // flag
		"(standby)",           //ucmd
		UseStrlen,                     // cmdlen
		0,                      // valuelen
		0,                      // cmdoffset
		eFunc_PowerStandby, // eCmdFun
		" ",        // feedbackstring
	},
	{
		Flag_HeadMatch|Flag_ShowHelpCommand,       // flag
		"(wakeup)",           //ucmd
		UseStrlen,                     // cmdlen
		0,                      // valuelen
		0,                      // cmdoffset
		eFunc_PowerWakeup, // eCmdFun
		" ",        // feedbackstring
	},
	{
		Flag_HeadMatch|Flag_ShowHelpCommand,       // flag
		"(get,power)",           //ucmd
		UseStrlen,              // cmdlen
		0,                      // valuelen
		2,                      // cmdoffset
		eFunc_GetPowerState,    // eCmdFun
		" ",              // feedbackstring
	},
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,        // flag
		"(help)",                //ucmd
		5,                      // cmdlen
		40,                     // valuelen
		2,                      // cmdoffset
		eFunc_HelpFunction,     // eCmdFun
		" ",    // feedbackstring
	},
	{
		Flag_HeadMatch,        // flag
		"(info,testversion)",         //ucmd
		UseStrlen,              // cmdlen
		0,                      // valuelen
		2,                      // cmdoffset
		eFunc_GetTestVersion,   // eCmdFun
		" ",    // feedbackstring
	},
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,     // flag
		"(set,o.res,",     //ucmd
		11,                     // cmdlen
		5,                      // valuelen
		2,                      // cmdoffset
		eFunc_SetTxResolution,  // eCmdFun
		" ",         // feedbackstring
	},
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,     // flag
		"(get,o.res,",     //ucmd
		11,              // cmdlen
		2,                      // valuelen
		2,                      // cmdoffset
		eFunc_GetTxResolution,  // eCmdFun
		" ",         // feedbackstring
	},
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,     // flag
		"(get,i.res,",     //ucmd
		11,              // cmdlen
		2,                      // valuelen
		1,                      // cmdoffset
		eFunc_GetRxResolution,  // eCmdFun
		" ",         // feedbackstring
	},
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,     // flag
		"(set,o.hdcp,",     //ucmd
		12,                     // cmdlen
		5,                      // valuelen
		2,                      // cmdoffset
		eFunc_SetTxHdcpMode,  // eCmdFun
		" ",         // feedbackstring
	},
	{
		Flag_HeadMatch|Flag_ShowHelpCommand|Flag_UserValueLength,     // flag
		"(get,o.hdcp,",     //ucmd
		12,              // cmdlen
		2,                      // valuelen
		2,                      // cmdoffset
		eFunc_GetTxHdcpMode,  // eCmdFun
		" ",         // feedbackstring
	},
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,     // flag
		"(set,o.format,",     //ucmd
		14,                     // cmdlen
		5,                      // valuelen
		2,                      // cmdoffset
		eFunc_SetTxFormat,      // eCmdFun
		" ",                    // feedbackstring
	},
	{
		Flag_HeadMatch|Flag_ShowHelpCommand|Flag_UserValueLength,     // flag
		"(get,o.format,",     //ucmd
		14,              // cmdlen
		2,                      // valuelen
		2,                      // cmdoffset
		eFunc_GetTxFormat,      // eCmdFun
		" ",                    // feedbackstring
	},
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,     // flag
		"(set,freeze,",         //ucmd
		12,                     // cmdlen
		1,                      // valuelen
		2,                      // cmdoffset
		eFunc_SetFreezeState,   // eCmdFun
		" ",                    // feedbackstring
	},
	{
		Flag_HeadMatch|Flag_ShowHelpCommand|Flag_UserValueLength,     // flag
		"(get,freeze,",         //ucmd
		12,              // cmdlen
		2,                      // valuelen
		2,                      // cmdoffset
		eFunc_GetFreezeState,   // eCmdFun
		" ",                    // feedbackstring
	},
	{
		Flag_NomalMatch|Flag_UserValueLength|Flag_ShowHelpCommand,     // flag
		"G0",                   //ucmd
		2,                      // cmdlen
		1,                      // valuelen
		2,                      // cmdoffset
		eFunc_SwitchFreeze,     // eCmdFun
		" ",                    // feedbackstring
	},
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,     // flag
		"(set,brightness,",         //ucmd
		16,                     // cmdlen
		6,                      // valuelen
		2,                      // cmdoffset
		eFunc_SetBrightness,    // eCmdFun
		" ",                    // feedbackstring
	},
	{
		Flag_HeadMatch|Flag_ShowHelpCommand|Flag_UserValueLength,     // flag
		"(get,brightness,",     //ucmd
		16,                     // cmdlen
		2,                      // valuelen
		2,                      // cmdoffset
		eFunc_GetBrightness,    // eCmdFun
		" ",                    // feedbackstring
	},
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,     // flag
		"(set,contrast,",       //ucmd
		14,                     // cmdlen
		6,                      // valuelen
		2,                      // cmdoffset
		eFunc_SetContrast,      // eCmdFun
		" ",                    // feedbackstring
	},
	{
		Flag_HeadMatch|Flag_ShowHelpCommand|Flag_UserValueLength,     // flag
		"(get,contrast,",       //ucmd
		14,                     // cmdlen
		2,                      // valuelen
		2,                      // cmdoffset
		eFunc_GetContrast,      // eCmdFun
		" ",                    // feedbackstring
	},
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,     // flag
		"(set,saturation,",     //ucmd
		16,                     // cmdlen
		6,                      // valuelen
		2,                      // cmdoffset
		eFunc_SetSaturation,    // eCmdFun
		" ",                    // feedbackstring
	},
	{
		Flag_HeadMatch|Flag_ShowHelpCommand|Flag_UserValueLength,     // flag
		"(get,saturation,",     //ucmd
		16,                     // cmdlen
		2,                      // valuelen
		2,                      // cmdoffset
		eFunc_GetSaturation,    // eCmdFun
		" ",                    // feedbackstring
	},
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,     // flag
		"(set,hue,",            //ucmd
		9,                      // cmdlen
		6,                      // valuelen
		2,                      // cmdoffset
		eFunc_SetHue,           // eCmdFun
		" ",                    // feedbackstring
	},
	{
		Flag_HeadMatch|Flag_ShowHelpCommand|Flag_UserValueLength,     // flag
		"(get,hue,",            //ucmd
		8,                      // cmdlen
		2,                      // valuelen
		2,                      // cmdoffset
		eFunc_GetHue,           // eCmdFun
		" ",                    // feedbackstring
	},
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       // flag
		"(edid,config,",        //ucmd
		13,                     // cmdlen
		5,                      // valuelen
		2,                      // cmdoffset
		eFunc_SetRxEdidMode,    // eCmdFun
		" ",                    // feedbackstring
	},
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,        // flag
		"(get,i.edid,",         //ucmd
		12,                     // cmdlen
		2,                      // valuelen
		1,                      // cmdoffset
		eFunc_GetRxEdidMode,    // eCmdFun
		" ",                    // feedbackstring
	},
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,        // flag
		"(update,edid,",        //ucmd
		13,                     // cmdlen
		2,                      // valuelen
		1,                      // cmdoffset
		eFunc_UpdateUserEdid,   // eCmdFun
		" ",    // feedbackstring
	},

	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,        // flag
		"(get,o.edid,",         //ucmd
		12,                     // cmdlen
		2,                      // valuelen
		1,                      // cmdoffset
		eFunc_GetTxEdidData,    // eCmdFun
		" ",                    // feedbackstring
	},
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,        // flag
		"(set,timing,",         //ucmd
		12,                     // cmdlen
		60,                     // valuelen
		2,                      // cmdoffset
		eFunc_SetTxTiming,      // eCmdFun
		" ",                    // feedbackstring
	},
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,        // flag
		"(set,pattern,",         //ucmd
		13,                     // cmdlen
		6,                     // valuelen
		2,                      // cmdoffset
		eFunc_SetTxPattern,      // eCmdFun
		" ",                    // feedbackstring
	},
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,        // flag
		"(get,pattern,",         //ucmd
		13,                     // cmdlen
		2,                      // valuelen
		1,                      // cmdoffset
		eFunc_GetTxPattern,    // eCmdFun
		" ",                    // feedbackstring
	},
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       // flag
		"(set,color,",        //ucmd
		11,                     // cmdlen
		13,                      // valuelen
		2,                      // cmdoffset
		eFunc_SetColor,    // eCmdFun
		" ",                    // feedbackstring
	},
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,        // flag
		"(get,color,",         //ucmd
		11,                     // cmdlen
		2,                      // valuelen
		1,                      // cmdoffset
		eFunc_GetColor,    // eCmdFun
		" ",                    // feedbackstring
	},
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,     // flag
		"(debug,",     //ucmd
		7,              // cmdlen
		2,                      // valuelen
		1,                      // cmdoffset
		eFunc_SetDebugEn,  // eCmdFun
		" ",         // feedbackstring
	},
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,     // flag
		"(set,ms1826hold,",     //ucmd
		16,              // cmdlen
		2,                      // valuelen
		1,                      // cmdoffset
		eFunc_SetMs1826Hold,  // eCmdFun
		" ",         // feedbackstring
	},
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(set,bypass,",              //ucmd
		12,                      // cmdlen
		50,                      // valuelen
		1,                      // cmdoffset
		eFunc_BypassSwitchPort,  // eCmdFun
		" ",                    // feedbackstring
	},
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(set,workmode,",              //ucmd
		14,                      // cmdlen
		5,                      // valuelen
		1,                      // cmdoffset
		eFunc_ModeSwitch,  // eCmdFun
		" ",                    // feedbackstring
	},
#endif
	//add by hy 2024/12/18 START
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,     // flag
		"(rename,product,",     //ucmd
		16,              // cmdlen
		20,                      // valuelen
		1,                      // cmdoffset
		eFunc_SetProductName,  // eCmdFun
		" ",         // feedbackstring
	},

	//总音频开�?
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(set,AllAudioOutput,",              //ucmd
		20,                      // cmdlen
		2,                      // valuelen
		1,                      // cmdoffset
		eFunc_SetAllAudioOutput,  // eCmdFun
		" ",                    // feedbackstring
	},
	//输入源灵敏度
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(set,InputSensitivity,",              //ucmd
		22,                      // cmdlen
		6,                      // valuelen
		1,                      // cmdoffset
		eFunc_SetInputSensitivity,  // eCmdFun
		" ",                    // feedbackstring
	},
	//输入增益
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(set,InputGain,",              //ucmd
		15,                      // cmdlen
		8,                      // valuelen
		1,                      // cmdoffset
		eFunc_SetInputGain,  // eCmdFun
		" ",                    // feedbackstring
	},
	//输入静音
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(set,InputMute,",              //ucmd
		15,                      // cmdlen
		4,                      // valuelen
		1,                      // cmdoffset
		eFunc_SetInputMute,  // eCmdFun
		" ",                    // feedbackstring
	},
	//输入反相
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(set,InputReversephase,",              //ucmd
		23,                      // cmdlen
		4,                      // valuelen
		1,                      // cmdoffset
		eFunc_SetInputReversephase,  // eCmdFun
		" ",                    // feedbackstring
	},
	//输入通道测试信号�?�?
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(set,InputTestSignalCtrl,",              //ucmd
		25,                      // cmdlen
		4,                      // valuelen
		1,                      // cmdoffset
		eFunc_SetInputTestSignalCtrl,  // eCmdFun
		" ",                    // feedbackstring
	},
	//测试信号频率
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(set,InputTestSignalFreq,",              //ucmd
		25,                      // cmdlen
		8,                      // valuelen
		1,                      // cmdoffset
		eFunc_SetInputTestSignalFreq,  // eCmdFun
		" ",                    // feedbackstring
	},
	//测试信号电平
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(set,InputTestSignalLevel,",              //ucmd
		26,                      // cmdlen
		6,                      // valuelen
		1,                      // cmdoffset
		eFunc_SetInputTestSignalLevel,  // eCmdFun
		" ",                    // feedbackstring
	},
	//输入通道压缩器开�?
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(set,InputCompressorCtrl,",              //ucmd
		25,                      // cmdlen
		4,                      // valuelen
		1,                      // cmdoffset
		eFunc_SetInputCompressorCtrl,  // eCmdFun
		" ",                    // feedbackstring
	},
	//输入压缩器增�?
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(set,InputCompressorGain,",              //ucmd
		25,                      // cmdlen
		6,                      // valuelen
		1,                      // cmdoffset
		eFunc_SetInputCompressorGain,  // eCmdFun
		" ",                    // feedbackstring
	},
	//输入压缩器阈�?
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(set,InputCompressorThreshold,",              //ucmd
		30,                      // cmdlen
		6,                      // valuelen
		1,                      // cmdoffset
		eFunc_SetInputCompressorThreshold,  // eCmdFun
		" ",                    // feedbackstring
	},
	//输入压缩器比�?
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(set,InputCompressorRatio,",              //ucmd
		26,                      // cmdlen
		6,                      // valuelen
		1,                      // cmdoffset
		eFunc_SetInputCompressorRatio,  // eCmdFun
		" ",                    // feedbackstring
	},
	//输入压缩器启动时�?
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(set,InputCompressorStartTime,",              //ucmd
		31,                      // cmdlen
		6,                      // valuelen
		1,                      // cmdoffset
		eFunc_SetInputCompressorStartTime,  // eCmdFun
		" ",                    // feedbackstring
	},
	//输入压缩器释放时�?
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(set,InputCompressorReleaseTime,",              //ucmd
		32,                      // cmdlen
		8,                      // valuelen
		1,                      // cmdoffset
		eFunc_SetInputCompressorReleaseTime,  // eCmdFun
		" ",                    // feedbackstring
	},
	//输入通道自动增益�?�?
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(set,InputAutoGainCtrl,",              //ucmd
		23,                      // cmdlen
		4,                      // valuelen
		1,                      // cmdoffset
		eFunc_SetInputAutoGainCtrl,  // eCmdFun
		" ",                    // feedbackstring
	},
	//输入通道自动增益阈�??
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(set,InputAutoGainThreshold,",              //ucmd
		28,                      // cmdlen
		6,                      // valuelen
		1,                      // cmdoffset
		eFunc_SetInputAutoGainThreshold,  // eCmdFun
		" ",                    // feedbackstring
	},
	//输入通道自动增益目标阈�??
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(set,InputAutoGainTargetThreshold,",              //ucmd
		34,                      // cmdlen
		6,                      // valuelen
		1,                      // cmdoffset
		eFunc_SetInputAutoGainTargetThreshold,  // eCmdFun
		" ",                    // feedbackstring
	},
	//输入通道自动增益比率
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(set,InputAutoGainRatio,",              //ucmd
		24,                      // cmdlen
		6,                      // valuelen
		1,                      // cmdoffset
		eFunc_SetInputAutoGainRatio,  // eCmdFun
		" ",                    // feedbackstring
	},
	//输入通道自动增益启动时间
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(set,InputAutoGainStartTime,",              //ucmd
		28,                      // cmdlen
		8,                      // valuelen
		1,                      // cmdoffset
		eFunc_SetInputAutoGainStartTime,  // eCmdFun
		" ",                    // feedbackstring
	},
	//输入通道自动增益释放时间
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(set,InputAutoGainReleaseTime,",              //ucmd
		30,                      // cmdlen
		8,                      // valuelen
		1,                      // cmdoffset
		eFunc_SetInputAutoGainReleaseTime,  // eCmdFun
		" ",                    // feedbackstring
	},
	//输入参量均衡某段类型
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(set,InputEQType,",              //ucmd
		17,                      // cmdlen
		6,                      // valuelen
		1,                      // cmdoffset
		eFunc_SetInputEQType,  // eCmdFun
		" ",                    // feedbackstring
	},
	//输入参量均衡某段增益
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(set,InputEQGain,",              //ucmd
		17,                      // cmdlen
		8,                      // valuelen
		1,                      // cmdoffset
		eFunc_SetInputEQGain,  // eCmdFun
		" ",                    // feedbackstring
	},
	//输入参量均衡某段品质因数
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(set,InputEQQualityFactor,",              //ucmd
		26,                      // cmdlen
		8,                      // valuelen
		1,                      // cmdoffset
		eFunc_SetInputEQQualityFactor,  // eCmdFun
		" ",                    // feedbackstring
	},
	//输入参量均衡某段�?�?
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(set,InputEQCtrl,",              //ucmd
		17,                      // cmdlen
		6,                      // valuelen
		1,                      // cmdoffset
		eFunc_SetInputEQCtrl,  // eCmdFun
		" ",                    // feedbackstring
	},
	//啸叫抑制器开�?
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(set,InputHowlingSuppressorCtrl,",              //ucmd
		32,                      // cmdlen
		4,                      // valuelen
		1,                      // cmdoffset
		eFunc_SetInputHowlingSuppressorCtrl,  // eCmdFun
		" ",                    // feedbackstring
	},
	//啸叫抑制等级
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(set,InputHowlingSuppressorGrade,",              //ucmd
		33,                      // cmdlen
		4,                      // valuelen
		1,                      // cmdoffset
		eFunc_SetInputHowlingSuppressorGrade,  // eCmdFun
		" ",                    // feedbackstring
	},
	//移频参数
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(set,InputHowlingSuppressorFreqShift,",              //ucmd
		37,                      // cmdlen
		4,                      // valuelen
		1,                      // cmdoffset
		eFunc_SetInputHowlingSuppressorFreqShift,  // eCmdFun
		" ",                    // feedbackstring
	},
	//噪声抑制等级
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(set,InputNoiseSuppressorGrade,",              //ucmd
		31,                      // cmdlen
		4,                      // valuelen
		1,                      // cmdoffset
		eFunc_SetInputNoiseSuppressorGrade,  // eCmdFun
		" ",                    // feedbackstring
	},
	//阈�??
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(set,InputNoiseSuppressorThreshold,",              //ucmd
		35,                      // cmdlen
		6,                      // valuelen
		1,                      // cmdoffset
		eFunc_SetInputNoiseSuppressorThreshold,  // eCmdFun
		" ",                    // feedbackstring
	},
	//比率
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(set,InputNoiseSuppressorRatio,",              //ucmd
		31,                      // cmdlen
		6,                      // valuelen
		1,                      // cmdoffset
		eFunc_SetInputNoiseSuppressorRatio,  // eCmdFun
		" ",                    // feedbackstring
	},
	//启动时间
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(set,InputNoiseSuppressorStartTime,",              //ucmd
		35,                      // cmdlen
		6,                      // valuelen
		1,                      // cmdoffset
		eFunc_SetInputNoiseSuppressorStartTime,  // eCmdFun
		" ",                    // feedbackstring
	},
	//释放时间
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(set,InputNoiseSuppressorReleaseTime,",              //ucmd
		37,                      // cmdlen
		6,                      // valuelen
		1,                      // cmdoffset
		eFunc_SetInputNoiseSuppressorReleaseTime,  // eCmdFun
		" ",                    // feedbackstring
	},
	//噪声抑制�?�?
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(set,InputNoiseSuppressorCtrl,",              //ucmd
		30,                      // cmdlen
		2,                      // valuelen
		1,                      // cmdoffset
		eFunc_SetInputNoiseSuppressorCtrl,  // eCmdFun
		" ",                    // feedbackstring
	},
	//回声消除等级
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(set,InputEchoCancellerGrade,",              //ucmd
		29,                      // cmdlen
		6,                      // valuelen
		1,                      // cmdoffset
		eFunc_SetInputEchoCancellerGrade,  // eCmdFun
		" ",                    // feedbackstring
	},
	//回声消除�?�?
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(set,InputEchoCancellerCtrl,",              //ucmd
		28,                      // cmdlen
		2,                      // valuelen
		1,                      // cmdoffset
		eFunc_SetInputEchoCancellerCtrl,  // eCmdFun
		" ",                    // feedbackstring
	},
	//某路低频�?励器等级
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(set,InputLfreqExciterGrade,",              //ucmd
		28,                      // cmdlen
		4,                      // valuelen
		1,                      // cmdoffset
		eFunc_SetInputLfreqExciterGrade,  // eCmdFun
		" ",                    // feedbackstring
	},
	//某路高频�?励器等级
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(set,InputHfreqExciterGrade,",              //ucmd
		28,                      // cmdlen
		4,                      // valuelen
		1,                      // cmdoffset
		eFunc_SetInputHfreqExciterGrade,  // eCmdFun
		" ",                    // feedbackstring
	},
	//某路�?励器�?�?
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(set,InputExciterCtrl,",              //ucmd
		22,                      // cmdlen
		2,                      // valuelen
		1,                      // cmdoffset
		eFunc_SetInputExciterCtrl,  // eCmdFun
		" ",                    // feedbackstring
	},
	//第几路为呼叫输入
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(set,InputCallInput,",              //ucmd
		20,                      // cmdlen
		2,                      // valuelen
		1,                      // cmdoffset
		eFunc_SetInputCallInput,  // eCmdFun
		" ",                    // feedbackstring
	},
	//背景输入
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(set,InputBackgroundInput,",              //ucmd
		26,                      // cmdlen
		2,                      // valuelen
		1,                      // cmdoffset
		eFunc_SetInputBackgroundInput,  // eCmdFun
		" ",                    // feedbackstring
	},
	//某一路闪避器增益
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(set,InputDuckingGain,",              //ucmd
		22,                      // cmdlen
		6,                      // valuelen
		1,                      // cmdoffset
		eFunc_SetInputDuckingGain,  // eCmdFun
		" ",                    // feedbackstring
	},
	//阈�??
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(set,InputDuckingThreshold,",              //ucmd
		27,                      // cmdlen
		6,                      // valuelen
		1,                      // cmdoffset
		eFunc_SetInputDuckingThreshold,  // eCmdFun
		" ",                    // feedbackstring
	},
	//深度
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(set,InputDuckingDepth,",              //ucmd
		23,                      // cmdlen
		4,                      // valuelen
		1,                      // cmdoffset
		eFunc_SetInputDuckingDepth,  // eCmdFun
		" ",                    // feedbackstring
	},
	//启动时间
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(set,InputDuckingStartTime,",              //ucmd
		27,                      // cmdlen
		8,                      // valuelen
		1,                      // cmdoffset
		eFunc_SetInputDuckingStartTime,  // eCmdFun
		" ",                    // feedbackstring
	},
	//保持时间
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(set,InputDuckingHoldTime,",              //ucmd
		26,                      // cmdlen
		6,                      // valuelen
		1,                      // cmdoffset
		eFunc_SetInputDuckingHoldTime,  // eCmdFun
		" ",                    // feedbackstring
	},
	//释放时间
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(set,InputDuckingReleaseTime,",              //ucmd
		29,                      // cmdlen
		8,                      // valuelen
		1,                      // cmdoffset
		eFunc_SetInputDuckingReleaseTime,  // eCmdFun
		" ",                    // feedbackstring
	},
	//闪避器开�?
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(set,InputDuckingCtrl,",              //ucmd
		22,                      // cmdlen
		2,                      // valuelen
		1,                      // cmdoffset
		eFunc_SetInputDuckingCtrl,  // eCmdFun
		" ",                    // feedbackstring
	},
	//矩阵切换
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(set,MatrixSwitching,",              //ucmd
		21,                      // cmdlen
		6,                      // valuelen
		1,                      // cmdoffset
		eFunc_SetMatrixSwitching,  // eCmdFun
		" ",                    // feedbackstring
	},
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(set,OutputDelayTime,",              //ucmd
		21,                      // cmdlen
		6,                      // valuelen
		1,                      // cmdoffset
		eFunc_SetOutputDelayTime,  // eCmdFun
		" ",                    // feedbackstring
	},
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(set,OutputDelayCtrl,",              //ucmd
		21,                      // cmdlen
		2,                      // valuelen
		1,                      // cmdoffset
		eFunc_SetOutputDelayCtrl,  // eCmdFun
		" ",                    // feedbackstring
	},
	//USB播放�?
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(set,USBplayerCtrl,",              //ucmd
		19,                      // cmdlen
		6,                      // valuelen
		1,                      // cmdoffset
		eFunc_SetUSBplayerCtrl,  // eCmdFun
		" ",                    // feedbackstring
	},

	//获取工程名
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,     // flag
		"(get,product,",     //ucmd
		16,              // cmdlen
		20,                      // valuelen
		1,                      // cmdoffGet
		eFunc_GetProductName,  // eCmdFun
		" ",         // feedbackstring
	},

	//总音频开�?
	{
		Flag_HeadMatch|Flag_ShowHelpCommand,       //flag
		"(get,AllAudioOutput)",              //ucmd
		0,                      // cmdlen
		0,                      // valuelen
		0,                      // cmdoffset
		eFunc_GetAllAudioOutput,  // eCmdFun
		" ",                    // feedbackstring
	},
	//输入源灵敏度
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(get,InputSensitivity,",              //ucmd
		22,                      // cmdlen
		4,                      // valuelen
		1,                      // cmdoffset
		eFunc_GetInputSensitivity,  // eCmdFun
		" ",                    // feedbackstring
	},
	//输入增益
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(get,InputGain,",              //ucmd
		15,                      // cmdlen
		6,                      // valuelen
		1,                      // cmdoffset
		eFunc_GetInputGain,  // eCmdFun
		" ",                    // feedbackstring
	},
	//输入静音
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(get,InputMute,",              //ucmd
		15,                      // cmdlen
		4,                      // valuelen
		1,                      // cmdoffset
		eFunc_GetInputMute,  // eCmdFun
		" ",                    // feedbackstring
	},
	//输入反相
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(get,InputReversephase,",              //ucmd
		23,                      // cmdlen
		4,                      // valuelen
		1,                      // cmdoffGet
		eFunc_GetInputReversephase,  // eCmdFun
		" ",                    // feedbackstring
	},
	//输入通道测试信号�?�?
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(get,InputTestSignalCtrl,",              //ucmd
		25,                      // cmdlen
		4,                      // valuelen
		1,                      // cmdoffGet
		eFunc_GetInputTestSignalCtrl,  // eCmdFun
		" ",                    // feedbackstring
	},
	//测试信号频率
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(get,InputTestSignalFreq,",              //ucmd
		25,                      // cmdlen
		6,                      // valuelen
		1,                      // cmdoffGet
		eFunc_GetInputTestSignalFreq,  // eCmdFun
		" ",                    // feedbackstring
	},
	//测试信号电平
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(get,InputTestSignalLevel,",              //ucmd
		26,                      // cmdlen
		6,                      // valuelen
		1,                      // cmdoffGet
		eFunc_GetInputTestSignalLevel,  // eCmdFun
		" ",                    // feedbackstring
	},
	//输入通道压缩器开�?
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(get,InputCompressorCtrl,",              //ucmd
		25,                      // cmdlen
		4,                      // valuelen
		1,                      // cmdoffGet
		eFunc_GetInputCompressorCtrl,  // eCmdFun
		" ",                    // feedbackstring
	},
	//输入压缩器增�?
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(get,InputCompressorGain,",              //ucmd
		25,                      // cmdlen
		6,                      // valuelen
		1,                      // cmdoffGet
		eFunc_GetInputCompressorGain,  // eCmdFun
		" ",                    // feedbackstring
	},
	//输入压缩器阈�?
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(get,InputCompressorThreshold,",              //ucmd
		30,                      // cmdlen
		6,                      // valuelen
		1,                      // cmdoffGet
		eFunc_GetInputCompressorThreshold,  // eCmdFun
		" ",                    // feedbackstring
	},
	//输入压缩器比�?
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(get,InputCompressorRatio,",              //ucmd
		26,                      // cmdlen
		6,                      // valuelen
		1,                      // cmdoffGet
		eFunc_GetInputCompressorRatio,  // eCmdFun
		" ",                    // feedbackstring
	},
	//输入压缩器启动时�?
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(get,InputCompressorStartTime,",              //ucmd
		31,                      // cmdlen
		6,                      // valuelen
		1,                      // cmdoffGet
		eFunc_GetInputCompressorStartTime,  // eCmdFun
		" ",                    // feedbackstring
	},
	//输入压缩器释放时�?
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(get,InputCompressorReleaseTime,",              //ucmd
		32,                      // cmdlen
		6,                      // valuelen
		1,                      // cmdoffGet
		eFunc_GetInputCompressorReleasetime,  // eCmdFun
		" ",                    // feedbackstring
	},
	//输入通道自动增益�?�?
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(get,InputAutoGainCtrl,",              //ucmd
		23,                      // cmdlen
		4,                      // valuelen
		1,                      // cmdoffGet
		eFunc_GetInputAutoGainCtrl,  // eCmdFun
		" ",                    // feedbackstring
	},
	//输入通道自动增益阈�??
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(get,InputAutoGainThreshold,",              //ucmd
		28,                      // cmdlen
		6,                      // valuelen
		1,                      // cmdoffGet
		eFunc_GetInputAutoGainThreshold,  // eCmdFun
		" ",                    // feedbackstring
	},
	//输入通道自动增益目标阈�??
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(get,InputAutoGainTargetThreshold,",              //ucmd
		34,                      // cmdlen
		6,                      // valuelen
		1,                      // cmdoffGet
		eFunc_GetInputAutoGainTargetThreshold,  // eCmdFun
		" ",                    // feedbackstring
	},
	//输入通道自动增益比率
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(get,InputAutoGainRatio,",              //ucmd
		24,                      // cmdlen
		6,                      // valuelen
		1,                      // cmdoffGet
		eFunc_GetInputAutoGainRatio,  // eCmdFun
		" ",                    // feedbackstring
	},
	//输入通道自动增益启动时间
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(get,InputAutoGainStartTime,",              //ucmd
		28,                      // cmdlen
		6,                      // valuelen
		1,                      // cmdoffGet
		eFunc_GetInputAutoGainStartTime,  // eCmdFun
		" ",                    // feedbackstring
	},
	//输入通道自动增益释放时间
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(get,InputAutoGainReleaseTime,",              //ucmd
		30,                      // cmdlen
		6,                      // valuelen
		1,                      // cmdoffGet
		eFunc_GetInputAutoGainReleasetime,  // eCmdFun
		" ",                    // feedbackstring
	},
	//输入参量均衡某段类型
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(get,InputEQType,",              //ucmd
		17,                      // cmdlen
		6,                      // valuelen
		1,                      // cmdoffGet
		eFunc_GetInputEQType,  // eCmdFun
		" ",                    // feedbackstring
	},
	//输入参量均衡某段增益
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(get,InputEQGain,",              //ucmd
		17,                      // cmdlen
		8,                      // valuelen
		1,                      // cmdoffGet
		eFunc_GetInputEQGain,  // eCmdFun
		" ",                    // feedbackstring
	},
	//输入参量均衡某段品质因数
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(get,InputEQQualityFactor,",              //ucmd
		26,                      // cmdlen
		8,                      // valuelen
		1,                      // cmdoffGet
		eFunc_GetInputEQQualityFactor,  // eCmdFun
		" ",                    // feedbackstring
	},
	//输入参量均衡某段�?�?
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(get,InputEQCtrl,",              //ucmd
		17,                      // cmdlen
		6,                      // valuelen
		1,                      // cmdoffGet
		eFunc_GetInputEQCtrl,  // eCmdFun
		" ",                    // feedbackstring
	},
	//啸叫抑制器开�?
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(get,InputHowlingSuppressorCtrl,",              //ucmd
		32,                      // cmdlen
		4,                      // valuelen
		1,                      // cmdoffGet
		eFunc_GetInputHowlingSuppressorCtrl,  // eCmdFun
		" ",                    // feedbackstring
	},
	//啸叫抑制等级
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(get,InputHowlingSuppressorGrade,",              //ucmd
		33,                      // cmdlen
		2,                      // valuelen
		1,                      // cmdoffGet
		eFunc_GetInputHowlingSuppressorGrade,  // eCmdFun
		" ",                    // feedbackstring
	},
	//移频参数
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(get,InputHowlingSuppressorFreqShift,",              //ucmd
		37,                      // cmdlen
		2,                      // valuelen
		1,                      // cmdoffGet
		eFunc_GetInputHowlingSuppressorFreqShift,  // eCmdFun
		" ",                    // feedbackstring
	},
	//噪声抑制等级
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(get,InputNoiseSuppressorGrade,",              //ucmd
		31,                      // cmdlen
		4,                      // valuelen
		1,                      // cmdoffGet
		eFunc_GetInputNoiseSuppressorGrade,  // eCmdFun
		" ",                    // feedbackstring
	},
	//阈�??
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(get,InputNoiseSuppressorThreshold,",              //ucmd
		35,                      // cmdlen
		6,                      // valuelen
		1,                      // cmdoffGet
		eFunc_GetInputNoiseSuppressorThreshold,  // eCmdFun
		" ",                    // feedbackstring
	},
	//比率
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(get,InputNoiseSuppressorRatio,",              //ucmd
		31,                      // cmdlen
		6,                      // valuelen
		1,                      // cmdoffGet
		eFunc_GetInputNoiseSuppressorRatio,  // eCmdFun
		" ",                    // feedbackstring
	},
	//启动时间
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(get,InputNoiseSuppressorStartTime,",              //ucmd
		35,                      // cmdlen
		6,                      // valuelen
		1,                      // cmdoffGet
		eFunc_GetInputNoiseSuppressorStartTime,  // eCmdFun
		" ",                    // feedbackstring
	},
	//释放时间
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(get,InputNoiseSuppressorReleaseTime,",              //ucmd
		37,                      // cmdlen
		6,                      // valuelen
		1,                      // cmdoffGet
		eFunc_GetInputNoiseSuppressorReleasetime,  // eCmdFun
		" ",                    // feedbackstring
	},
	//噪声抑制�?�?
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(get,InputNoiseSuppressorCtrl,",              //ucmd
		30,                      // cmdlen
		2,                      // valuelen
		1,                      // cmdoffGet
		eFunc_GetInputNoiseSuppressorCtrl,  // eCmdFun
		" ",                    // feedbackstring
	},
	//回声消除等级
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(get,InputEchoCancellerGrade,",              //ucmd
		29,                      // cmdlen
		2,                      // valuelen
		1,                      // cmdoffGet
		eFunc_GetInputEchoCancellerGrade,  // eCmdFun
		" ",                    // feedbackstring
	},
	//回声消除�?�?
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(get,InputEchoCancellerCtrl,",              //ucmd
		28,                      // cmdlen
		2,                      // valuelen
		1,                      // cmdoffGet
		eFunc_GetInputEchoCancellerCtrl,  // eCmdFun
		" ",                    // feedbackstring
	},
	//某路低频�?励器等级
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(get,InputLfreqExciterGrade,",              //ucmd
		28,                      // cmdlen
		2,                      // valuelen
		1,                      // cmdoffGet
		eFunc_GetInputLfreqExciterGrade,  // eCmdFun
		" ",                    // feedbackstring
	},
	//某路高频�?励器等级
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(get,InputHfreqExciterGrade,",              //ucmd
		28,                      // cmdlen
		2,                      // valuelen
		1,                      // cmdoffGet
		eFunc_GetInputHfreqExciterGrade,  // eCmdFun
		" ",                    // feedbackstring
	},
	//某路�?励器�?�?
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(get,InputExciterCtrl,",              //ucmd
		22,                      // cmdlen
		2,                      // valuelen
		1,                      // cmdoffGet
		eFunc_GetInputExciterCtrl,  // eCmdFun
		" ",                    // feedbackstring
	},
	//第几路为呼叫输入
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(get,InputCallInput,",              //ucmd
		20,                      // cmdlen
		2,                      // valuelen
		1,                      // cmdoffGet
		eFunc_GetInputCallInput,  // eCmdFun
		" ",                    // feedbackstring
	},
	//背景输入
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(get,InputBackgroundInput,",              //ucmd
		26,                      // cmdlen
		2,                      // valuelen
		1,                      // cmdoffGet
		eFunc_GetInputBackgroundInput,  // eCmdFun
		" ",                    // feedbackstring
	},
	//某一路闪避器增益
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(get,InputDuckingGain,",              //ucmd
		22,                      // cmdlen
		2,                      // valuelen
		1,                      // cmdoffGet
		eFunc_GetInputDuckingGain,  // eCmdFun
		" ",                    // feedbackstring
	},
	//阈�??
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(get,InputDuckingThreshold,",              //ucmd
		27,                      // cmdlen
		2,                      // valuelen
		1,                      // cmdoffGet
		eFunc_GetInputDuckingThreshold,  // eCmdFun
		" ",                    // feedbackstring
	},
	//深度
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(get,InputDuckingDepth,",              //ucmd
		23,                      // cmdlen
		2,                      // valuelen
		1,                      // cmdoffGet
		eFunc_GetInputDuckingDepth,  // eCmdFun
		" ",                    // feedbackstring
	},
	//启动时间
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(get,InputDuckingStartTime,",              //ucmd
		27,                      // cmdlen
		2,                      // valuelen
		1,                      // cmdoffGet
		eFunc_GetInputDuckingStartTime,  // eCmdFun
		" ",                    // feedbackstring
	},
	//保持时间
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(get,InputDuckingHoldTime,",              //ucmd
		26,                      // cmdlen
		2,                      // valuelen
		1,                      // cmdoffGet
		eFunc_GetInputDuckingHoldTime,  // eCmdFun
		" ",                    // feedbackstring
	},
	//释放时间
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(get,InputDuckingReleaseTime,",              //ucmd
		29,                      // cmdlen
		2,                      // valuelen
		1,                      // cmdoffGet
		eFunc_GetInputDuckingReleasetime,  // eCmdFun
		" ",                    // feedbackstring
	},
	//闪避器开�?
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(get,InputDuckingCtrl,",              //ucmd
		22,                      // cmdlen
		2,                      // valuelen
		1,                      // cmdoffGet
		eFunc_GetInputDuckingCtrl,  // eCmdFun
		" ",                    // feedbackstring
	},
	//矩阵切换
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(get,MatrixSwitching,",              //ucmd
		21,                      // cmdlen
		2,                      // valuelen
		1,                      // cmdoffGet
		eFunc_GetMatrixSwitching,  // eCmdFun
		" ",                    // feedbackstring
	},
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(get,OutputDelayTime,",              //ucmd
		21,                      // cmdlen
		2,                      // valuelen
		1,                      // cmdoffGet
		eFunc_GetOutputDelayTime,  // eCmdFun
		" ",                    // feedbackstring
	},
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(get,OutputDelayCtrl,",              //ucmd
		21,                      // cmdlen
		2,                      // valuelen
		1,                      // cmdoffGet
		eFunc_GetOutputDelayCtrl,  // eCmdFun
		" ",                    // feedbackstring
	},
	//USB播放�?
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(get,USBplayerCtrl",              //ucmd
		18,                      // cmdlen
		2,                      // valuelen
		1,                      // cmdoffGet
		eFunc_GetUSBplayerCtrl,  // eCmdFun
		" ",                    // feedbackstring
	},
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(get,AllData)",              //ucmd
		13,                      // cmdlen
		2,                      // valuelen
		1,                      // cmdoffGet
		eFunc_GetAllData,  // eCmdFun
		" ",                    // feedbackstring
	},
	{
		Flag_HeadMatch|Flag_UserValueLength|Flag_ShowHelpCommand,       //flag
		"(rst)",              //ucmd
		4,                      // cmdlen
		2,                      // valuelen
		1,                      // cmdoffGet
		eFunc_ResetData,  // eCmdFun
		" ",                    // feedbackstring
	},
	//add by hy 2024/12/18 END
	{
		Flag_NomalMatch|Flag_UserValueLength|Flag_ShowHelpCommand,     // flag
		"RFF.",                   //ucmd
		4,                      // cmdlen
		10,                      // valuelen
		0,                      // cmdoffset
		eFunc_FactoryReset2,     // eCmdFun
		" ",                    // feedbackstring
	},
	{
		Flag_NomalMatch|Flag_UserValueLength|Flag_ShowHelpCommand,     // flag
		"FFF.",                   //ucmd
		4,                      // cmdlen
		10,                      // valuelen
		0,                      // cmdoffset
		eFunc_FactoryReset2,     // eCmdFun
		" ",                    // feedbackstring
	},
	{
		Flag_NomalMatch|Flag_UserValueLength|Flag_ShowHelpCommand,     // flag
		"M",                   //ucmd
		1,                      // cmdlen
		2,                      // valuelen
		2,                      // cmdoffset
		eFunc_CheckOutputCardType,     // eCmdFun
		" ",                    // feedbackstring
	},
	{
		Flag_NomalMatch|Flag_UserValueLength|Flag_ShowHelpCommand,     // flag
		"V",                   //ucmd
		1,                      // cmdlen
		2,                      // valuelen
		2,                      // cmdoffset
		eFunc_CheckCardFWVersion,     // eCmdFun
		" ",                    // feedbackstring
	},
#if ENABLE_CARD_YBJ_RECORD
	{
		Flag_NomalMatch|Flag_UserValueLength|Flag_ShowHelpCommand,     // flag
		"K",                   //ucmd
		1,                      // cmdlen
		2,                      // valuelen
		2,                      // cmdoffset
		eFunc_CheckYBJCardType,     // eCmdFun
		" ",                    // feedbackstring
	},
	{
		Flag_NomalMatch|Flag_UserValueLength|Flag_ShowHelpCommand,     // flag
		"B",                   //ucmd
		1,                      // cmdlen
		2,                      // valuelen
		2,                      // cmdoffset
		eFunc_CheckYBJ2CardType,     // eCmdFun
		" ",                    // feedbackstring
	},
#endif
	{
		Flag_NomalMatch|Flag_UserValueLength|Flag_ShowHelpCommand,     // flag
		"T",                   //ucmd
		1,                      // cmdlen
		2,                      // valuelen
		2,                      // cmdoffset
		eFunc_CheckCardMode,     // eCmdFun
		" ",                    // feedbackstring
	},
	{
		Flag_NomalMatch|Flag_UserValueLength|Flag_ShowHelpCommand,     // flag
		"S",                   //ucmd
		1,                      // cmdlen
		300,                      // valuelen
		2,                      // cmdoffset
		eFunc_CheckSetEdidData,     // eCmdFun
		" ",                    // feedbackstring
	},
	{
		Flag_NomalMatch|Flag_UserValueLength|Flag_ShowHelpCommand,     // flag
		":",                   //ucmd
		1,                      // cmdlen
		50,                      // valuelen
		2,                      // cmdoffset
		eFunc_SetCardFunction,     // eCmdFun
		" ",                    // feedbackstring
	},
	//add by hy - START
	//{ Flag_NomalMatch|Flag_UserValueLength|Flag_ShowHelpCommand,     // flag
	//    "{",                   //ucmd
	//    1,                      // cmdlen
	//    2048,                      // valuelen
	//    2,                      // cmdoffset
	//    eFunc_SetGUIFunction,     // eCmdFun
	//    " ",                    // feedbackstring
	//},
	//add by hy - END
	{
		Flag_NomalMatch|Flag_UserValueLength|Flag_ShowHelpCommand,     // flag
		"P",                   //ucmd
		1,                      // cmdlen
		50,                      // valuelen
		2,                      // cmdoffset
		eFunc_SetSTKCardFunction,     // eCmdFun
		" ",                    // feedbackstring
	},


	// end
	{Flag_End,  "", 0,  0, 0,  eFunc_Max,  ""},
};

#if 0
char json[4096]="                                         \
{                                                    \
    \"SET_Input_HowlingSuppressor_Ctrl\":{           \
        \"cnt\":5,                                   \
        \"0\":{                                      \
            \"aisle\": 0,                            \
            \"suppressor\": 0                        \
        },                                           \
        \"1\":{                                      \
            \"aisle\": 1,                            \
            \"suppressor\": 0                        \
        },                                           \
        \"2\":{                                      \
            \"aisle\": 2,                            \
            \"suppressor\": 0                        \
        },                                           \
        \"3\":{                                      \
            \"aisle\": 3,                            \
            \"suppressor\": 0                        \
        },                                           \
        \"4\":{                                      \
            \"aisle\": 4,                            \
            \"suppressor\": 0                        \
        },                                           \
        \"@remark\": \"Х������������ 0x19\"         \
    }                                                \
}                                                    \
";
#endif

#if 0
char str2[50000]="                                    \
{                                                        \
    \"All_AudioOutput\": {                                 \
        \"switch\": 0,                                     \
        \"@remark\": \"????? 0x01\"                     \
    },                                                   \
    \"SET_Input_Sensitivity\": {                           \
        \"cnt\":4,                                         \
        \"0\": {                                           \
            \"aisle\": 0,                                  \
            \"sensitivity\": 0                             \
        },                                               \
        \"1\": {                                           \
            \"aisle\": 1,                                  \
            \"sensitivity\": 0                             \
        },                                               \
        \"2\": {                                           \
            \"aisle\": 2,                                  \
            \"sensitivity\": 0                             \
        },                                               \
        \"3\": {                                           \
            \"aisle\": 3,                                  \
            \"sensitivity\": 0                             \
        },                                               \
        \"@remark\": \"?????? 0x02\"                   \
    },                                                   \
    \"SET_Input_Gain\":{                                   \
        \"cnt\":4,                                         \
        \"0\":{                                            \
            \"aisle\": 0,                                  \
            \"P1\": 0.0,                                   \
            \"P2\": 0.0                                    \
        },                                               \
        \"1\":{                                            \
            \"aisle\": 1,                                  \
            \"P1\": 0.0,                                   \
            \"P2\": 0.0                                    \
        },                                               \
        \"2\":{                                            \
            \"aisle\": 2,                                  \
            \"P1\": 0.0,                                   \
            \"P2\": 0.0                                    \
        },                                               \
        \"3\":{                                            \
            \"aisle\": 3,                                  \
            \"P1\": 0.0,                                   \
            \"P2\": 0.0                                    \
        },                                               \
        \"@remark\": \"???? 0x03\"                       \
    },                                                   \
    \"SET_Input_Mute\":{                                   \
        \"cnt\":4,                                         \
        \"0\":{                                            \
            \"aisle\": 0,                                  \
            \"mute\": 0                                    \
        },                                               \
        \"1\":{                                            \
            \"aisle\": 1,                                  \
            \"mute\": 0                                    \
        },                                               \
        \"2\":{                                            \
            \"aisle\": 2,                                  \
            \"mute\": 0                                    \
        },                                               \
        \"3\":{                                            \
            \"aisle\": 3,                                  \
            \"mute\": 0                                    \
        },                                               \
        \"@remark\": \"???? 0x04\"                       \
    },                                                   \
    \"SET_Input_Reverse_phase\":{                          \
        \"cnt\":4,                                         \
        \"0\":{                                            \
            \"aisle\": 0,                                  \
            \"reverse\": 0                                 \
        },                                               \
        \"1\":{                                            \
            \"aisle\": 1,                                  \
            \"reverse\": 0                                 \
        },                                               \
        \"2\":{                                            \
            \"aisle\": 2,                                  \
            \"reverse\": 0                                 \
        },                                               \
        \"3\":{                                            \
            \"aisle\": 3,                                  \
            \"reverse\": 0                                 \
        },                                               \
        \"@remark\": \"???? 0x05\"                       \
    },                                                   \
    \"SET_Input_TestSignal_Ctrl\":{                        \
        \"cnt\":4,                                         \
        \"0\":{                                            \
            \"aisle\": 0,                                  \
            \"signal\": 0                                  \
        },                                               \
        \"1\":{                                            \
            \"aisle\": 1,                                  \
            \"signal\": 0                                  \
        },                                               \
        \"2\":{                                            \
            \"aisle\": 2,                                  \
            \"signal\": 0                                  \
        },                                               \
        \"3\":{                                            \
            \"aisle\": 3,                                  \
            \"signal\": 0                                  \
        },                                               \
        \"@remark\": \"?????????? 0x06\"           \
    },                                                   \
    \"SET_Input_TestSignal_Freq\":{                        \
        \"cnt\":4,                                         \
        \"0\":{                                            \
            \"aisle\": 0,                                  \
            \"hdata\": 0,                                  \
            \"ldata\": 0                                   \
        },                                               \
        \"1\":{                                            \
            \"aisle\": 1,                                  \
            \"hdata\": 0,                                  \
            \"ldata\": 0                                   \
        },                                               \
        \"2\":{                                            \
            \"aisle\": 2,                                  \
            \"hdata\": 0,                                  \
            \"ldata\": 0                                   \
        },                                               \
        \"3\":{                                            \
            \"aisle\": 3,                                  \
            \"hdata\": 0,                                  \
            \"ldata\": 0                                   \
        },                                               \
        \"@remark\": \"?????? 0x07\"                   \
    },                                                   \
    \"SET_Input_TestSignal_Level\":{                       \
        \"cnt\":4,                                         \
        \"0\":{                                            \
            \"aisle\": 0,                                  \
            \"data1\": 0,                                  \
            \"data2\": 0                                   \
        },                                               \
        \"1\":{                                            \
            \"aisle\": 1,                                  \
            \"data1\": 0,                                  \
            \"data2\": 0                                   \
        },                                               \
        \"2\":{                                            \
            \"aisle\": 2,                                  \
            \"data1\": 0,                                  \
            \"data2\": 0                                   \
        },                                               \
        \"3\":{                                            \
            \"aisle\": 3,                                  \
            \"data1\": 0,                                  \
            \"data2\": 0                                   \
        },                                               \
        \"@remark\": \"?????? 0x08\"                   \
    },                                                   \
    \"SET_Input_Compressor_Ctrl\":{                        \
        \"cnt\":4,                                         \
        \"0\":{                                            \
            \"aisle\": 0,                                  \
            \"compressor\": 0                              \
        },                                               \
        \"1\":{                                            \
            \"aisle\": 1,                                  \
            \"compressor\": 0                              \
        },                                               \
        \"2\":{                                            \
            \"aisle\": 2,                                  \
            \"compressor\": 0                              \
        },                                               \
        \"3\":{                                            \
            \"aisle\": 3,                                  \
            \"compressor\": 0                              \
        },                                               \
        \"@remark\": \"????????? 0x09\"             \
    },                                                   \
    \"SET_Input_Compressor_Gain\":{                        \
        \"cnt\":4,                                         \
        \"0\":{                                            \
            \"aisle\": 0,                                  \
            \"data1\": 0,                                  \
            \"data2\": 0                                   \
        },                                               \
        \"1\":{                                            \
            \"aisle\": 1,                                  \
            \"data1\": 0,                                  \
            \"data2\": 0                                   \
        },                                               \
        \"2\":{                                            \
            \"aisle\": 2,                                  \
            \"data1\": 0,                                  \
            \"data2\": 0                                   \
        },                                               \
        \"3\":{                                            \
            \"aisle\": 3,                                  \
            \"data1\": 0,                                  \
            \"data2\": 0                                   \
        },                                               \
        \"@remark\": \"??????? 0x0a\"                 \
    },                                                   \
    \"SET_Input_Compressor_Threshold\":{                   \
        \"cnt\":4,                                         \
        \"0\":{                                  \
            \"aisle\": 0,                                  \
            \"data1\": 0,                                  \
            \"data2\": 0                                  \
        },                                  \
        \"1\":{                                  \
            \"aisle\": 1,                                  \
            \"data1\": 0,                                  \
            \"data2\": 0                                  \
        },                                  \
        \"2\":{                                  \
            \"aisle\": 2,                                  \
            \"data1\": 0,                                  \
            \"data2\": 0                                  \
        },                                  \
        \"3\":{                             \
            \"aisle\": 3,                                  \
            \"data1\": 0,                                  \
            \"data2\": 0                                  \
        },                                  \
        \"@remark\": \"??????? 0x0b\"                                  \
    },                                  \
    \"SET_Input_Compressor_Ratio\":{                                  \
        \"cnt\":4,                                  \
        \"0\":{                                  \
            \"aisle\": 0,                                  \
            \"data1\": 0,                                  \
            \"data2\": 0                                  \
        },                                  \
        \"1\":{                                  \
            \"aisle\": 1,                                  \
            \"data1\": 0,                                  \
            \"data2\": 0                                  \
        },                                  \
        \"2\":{                                  \
            \"aisle\": 2,                                  \
            \"data1\": 0,                                  \
            \"data2\": 0                                  \
        },                                  \
        \"3\":{                                  \
            \"aisle\": 3,                                  \
            \"data1\": 0,                                  \
            \"data2\": 0                                  \
        },                                  \
        \"@remark\": \"??????? 0x0c\"                                  \
    },                                  \
    \"SET_Input_Compressor_StartTime\":{                                  \
        \"cnt\":4,                                  \
        \"0\":{                                  \
            \"aisle\": 0,                                  \
            \"hdata\": 0,                                  \
            \"ldata\": 0                                  \
        },                                  \
        \"1\":{                                  \
            \"aisle\": 1,                                  \
            \"hdata\": 0,                                  \
            \"ldata\": 0                                  \
        },                                  \
        \"2\":{                                  \
            \"aisle\": 2,                                  \
            \"hdata\": 0,                                  \
            \"ldata\": 0                                  \
        },                                  \
        \"3\":{                                  \
            \"aisle\": 3,                                  \
            \"hdata\": 0,                                  \
            \"ldata\": 0                                  \
        },                                  \
        \"@remark\": \"????????? 0x0d\"                                  \
    },                                  \
    \"SET_Input_Compressor_ReleaseTime\":{                                  \
        \"cnt\":4,                                  \
        \"0\":{                                  \
            \"aisle\": 0,                                  \
            \"hdata\": 0,                                  \
            \"ldata\": 0                                  \
        },                                  \
        \"1\":{                                  \
            \"aisle\": 1,                                  \
            \"hdata\": 0,                                  \
            \"ldata\": 0                                  \
        },                                  \
        \"2\":{                                  \
            \"aisle\": 2,                                  \
            \"hdata\": 0,                                  \
            \"ldata\": 0                                  \
        },                                  \
        \"3\":{                                  \
            \"aisle\": 3,                                  \
            \"hdata\": 0,                                  \
            \"ldata\": 0                                  \
        },                                  \
        \"@remark\": \"????????? 0x0e\"                                  \
    },                                  \
    \"SET_Input_AutoGain_Ctrl\":{                                  \
        \"cnt\":4,                                  \
        \"0\":{                                  \
            \"aisle\": 0,                                  \
            \"gain\": 0                                  \
        },                                  \
        \"1\":{                                  \
            \"aisle\": 1,                                  \
            \"gain\": 0                                  \
        },                                  \
        \"2\":{                                  \
            \"aisle\": 2,                                  \
            \"gain\": 0                                  \
        },                                  \
        \"3\":{                                  \
            \"aisle\": 3,                                  \
            \"gain\": 0                                  \
        },                                  \
        \"@remark\": \"?????????? 0x0f\"                                  \
    },                                  \
    \"SET_Input_AutoGain_Threshold\":{                                  \
        \"cnt\":4,                                  \
        \"0\":{                                  \
            \"aisle\": 0,                                  \
            \"data1\": 0,                                  \
            \"data2\": 0                                  \
        },                                  \
        \"1\":{                                  \
            \"aisle\": 1,                                  \
            \"data1\": 0,                                  \
            \"data2\": 0                                  \
        },                                  \
        \"2\":{                                  \
            \"aisle\": 2,                                  \
            \"data1\": 0,                                  \
            \"data2\": 0                                  \
        },                                  \
        \"3\":{                                  \
            \"aisle\": 3,                                  \
            \"data1\": 0,                                  \
            \"data2\": 0                                  \
        },                                  \
        \"@remark\": \"?????????? 0x10\"                                  \
    },                                  \
    \"SET_Input_AutoGain_TargetThreshold\":{                                  \
        \"cnt\":4,                                  \
        \"0\":{                                  \
            \"aisle\": 0,                                  \
            \"data1\": 0,                                  \
            \"data2\": 0                                  \
        },                                  \
        \"1\":{                                  \
            \"aisle\": 1,                                  \
            \"data1\": 0,                                  \
            \"data2\": 0                                  \
        },                                  \
        \"2\":{                                  \
            \"aisle\": 2,                                  \
            \"data1\": 0,                                  \
            \"data2\": 0                                  \
        },                                  \
        \"3\":{                                  \
            \"aisle\": 3,                                  \
            \"data1\": 0,                                  \
            \"data2\": 0                                  \
        },                                  \
        \"@remark\": \"???????????? 0x11\"                                  \
    },                                  \
    \"SET_Input_AutoGain_Ratio\":{                                  \
        \"cnt\":4,                                  \
        \"0\":{                                  \
            \"aisle\": 0,                                  \
            \"data1\": 0,                                  \
            \"data2\": 0                                  \
        },                                  \
        \"1\":{                                  \
            \"aisle\": 1,                                  \
            \"data1\": 0,                                  \
            \"data2\": 0                                  \
        },                                  \
        \"2\":{                                  \
            \"aisle\": 2,                                  \
            \"data1\": 0,                                  \
            \"data2\": 0                                  \
        },                                  \
        \"3\":{                                  \
            \"aisle\": 3,                                  \
            \"data1\": 0,                                  \
            \"data2\": 0                                  \
        },                                  \
        \"@remark\": \"?????????? 0x12\"                                  \
    },                                  \
    \"SET_Input_AutoGain_StartTime\":{                                  \
        \"cnt\":4,                                  \
        \"0\":{                                  \
            \"aisle\": 0,                                  \
            \"hdata\": 0,                                  \
            \"ldata\": 0                                  \
        },                                  \
        \"1\":{                                  \
            \"aisle\": 1,                                  \
            \"hdata\": 0,                                  \
            \"ldata\": 0                                  \
        },                                  \
        \"2\":{                                  \
            \"aisle\": 2,                                  \
            \"hdata\": 0,                                  \
            \"ldata\": 0                                  \
        },                                  \
        \"3\":{                                  \
            \"aisle\": 3,                                  \
            \"hdata\": 0,                                  \
            \"ldata\": 0                                  \
        },                                  \
        \"@remark\": \"???????????? 0x13\"                                  \
    },                                  \
    \"SET_Input_AutoGain_ReleaseTime\":{                                  \
        \"cnt\":4,                                  \
        \"0\":{                                  \
            \"aisle\": 0,                                  \
            \"hdata\": 0,                                  \
            \"ldata\": 0                                  \
        },                                  \
        \"1\":{                                  \
            \"aisle\": 1,                                  \
            \"hdata\": 0,                                  \
            \"ldata\": 0                                  \
        },                                  \
        \"2\":{                                  \
            \"aisle\": 2,                                  \
            \"hdata\": 0,                                  \
            \"ldata\": 0                                  \
        },                                  \
        \"3\":{                                  \
            \"aisle\": 3,                                  \
            \"hdata\": 0,                                  \
            \"ldata\": 0                                  \
        },                                  \
        \"@remark\": \"???????????? 0x14\"                                  \
    },                                  \
    \"SET_Input_EQ_Type\":{                                  \
        \"cnt\":4,                                  \
        \"0\":{                                  \
            \"aisle\": 0,                                  \
            \"segment\": 0,                                  \
            \"type\": 0                                  \
        },                                  \
        \"1\":{                                  \
            \"aisle\": 1,                                  \
            \"segment\": 0,                                  \
            \"type\": 0                                  \
        },                                  \
        \"2\":{                                  \
            \"aisle\": 2,                                  \
            \"segment\": 0,                                  \
            \"type\": 0                                  \
        },                                  \
        \"3\":{                                  \
            \"aisle\": 3,                                  \
            \"segment\": 0,                                  \
            \"type\": 0                                  \
        },                                  \
        \"@remark\": \"?????????? 0x15\"                                  \
    },                                  \
    \"SET_Input_EQ_Gain\":{                                  \
        \"cnt\":4,                                  \
        \"0\":{                                  \
            \"aisle\": 0,                                  \
            \"segment\": 0,                                  \
            \"data1\": 0,                                  \
            \"data2\": 0                                  \
        },                                  \
        \"1\":{                                  \
            \"aisle\": 1,                                  \
            \"segment\": 0,                                  \
            \"data1\": 0,                                  \
            \"data2\": 0                                  \
        },                                  \
        \"2\":{                                  \
            \"aisle\": 2,                                  \
            \"segment\": 0,                                  \
            \"data1\": 0,                                  \
            \"data2\": 0                                  \
        },                                  \
        \"3\":{                                  \
            \"aisle\": 3,                                  \
            \"segment\": 0,                                  \
            \"data1\": 0,                                  \
            \"data2\": 0                                  \
        },                                                \
        \"@remark\": \"?????????? 0x16\"                                  \
    },                                  \
    \"SET_Input_EQ_QualityFactor\":{                                  \
        \"cnt\":4,                                  \
        \"0\":{                                  \
            \"aisle\": 0,                                  \
            \"segment\": 0,                                  \
            \"data1\": 0,                                  \
            \"data2\": 0                                  \
        },                                  \
        \"1\":{                                  \
            \"aisle\": 1,                                  \
            \"segment\": 0,                                  \
            \"data1\": 0,                                  \
            \"data2\": 0                                  \
        },                                  \
        \"2\":{                                  \
            \"aisle\": 2,                                  \
            \"segment\": 0,                                  \
            \"data1\": 0,                                  \
            \"data2\": 0                                  \
        },                                  \
        \"3\":{                                  \
            \"aisle\": 3,                                  \
            \"segment\": 0,                                  \
            \"data1\": 0,                                  \
            \"data2\": 0                                  \
        },                                  \
        \"@remark\": \"???????????? 0x17\"                                  \
    },                                  \
    \"SET_Input_EQ_Ctrl\":{                                  \
        \"cnt\":4,                                  \
        \"0\":{                                  \
            \"aisle\": 0,                                  \
            \"segment\": 0,                                  \
            \"eq\": 0                                  \
        },                                  \
        \"1\":{                                  \
            \"aisle\": 1,                                  \
            \"segment\": 0,                                  \
            \"eq\": 0                                  \
        },                                  \
        \"2\":{                                  \
            \"aisle\": 2,                                  \
            \"segment\": 0,                                  \
            \"eq\": 0                                  \
        },                                  \
        \"3\":{                                  \
            \"aisle\": 3,                                  \
            \"segment\": 0,                                  \
            \"eq\": 0                                  \
        },                                             \
        \"@remark\": \"?????????? 0x18\"                                  \
    },                                  \
    \"SET_Input_HowlingSuppressor_Ctrl\":{                                  \
        \"cnt\":5,                                  \
        \"0\":{                                  \
            \"aisle\": 0,                                  \
            \"suppressor\": 0                                  \
        },                                  \
        \"1\":{                                  \
            \"aisle\": 1,                                  \
            \"suppressor\": 0                                  \
        },                                  \
        \"2\":{                                  \
            \"aisle\": 2,                                  \
            \"suppressor\": 0                                  \
        },                                  \
        \"3\":{                                  \
            \"aisle\": 3,                                  \
            \"suppressor\": 0                                  \
        },                                  \
        \"4\":{                                  \
            \"aisle\": 4,                                  \
            \"suppressor\": 0                                  \
        },                                  \
        \"@remark\": \"??????? 0x19\"                                  \
    },                                  \
    \"SET_Input_HowlingSuppressor_Grade\":{                                  \
        \"grade\": 0,                                  \
        \"@remark\": \"?????? 0x1a\"                                  \
    },                                  \
    \"SET_Input_HowlingSuppressor_FreqShift\":{                                  \
        \"freq\": 0,                                  \
        \"@remark\": \"???? 0x1b\"                                  \
    },                                  \
    \"SET_Input_NoiseSuppressor_Grade\":{                                  \
        \"grade\": 0,                                                      \
        \"@remark\": \"?????? 0x1c\"                                  \
    },                                  \
    \"SET_Input_NoiseSuppressor_Threshold\":{                                  \
        \"data1\": 0,                                  \
        \"data2\": 0,                                  \
        \"@remark\": \"?? 0x1d\"                                  \
    },                                  \
    \"SET_Input_NoiseSuppressor_Ratio\":{                                  \
        \"data1\": 0,                                  \
        \"data2\": 0,                                  \
        \"@remark\": \"?? 0x1e\"                                  \
    },                                  \
    \"SET_Input_NoiseSuppressor_StartTime\":{                                  \
        \"hdata\": 0,                                  \
        \"ldata\": 0,                                  \
        \"@remark\": \"???? 0x1f\"                                  \
    },                                  \
    \"SET_Input_NoiseSuppressor_ReleaseTime\":{                                  \
        \"hdata\": 0,                                  \
        \"ldata\": 0,                                  \
        \"@remark\": \"???? 0x20\"                                  \
    },                                  \
    \"SET_Input_NoiseSuppressor_Ctrl\":{                                  \
        \"cnt\":5,                                  \
        \"0\":{                                  \
            \"aisle\": 0,                                  \
            \"suppressor\": 0                                  \
        },                                  \
        \"1\":{                                  \
            \"aisle\": 1,                                  \
            \"suppressor\": 0                                  \
        },                                  \
        \"2\":{                                  \
            \"aisle\": 2,                                  \
            \"suppressor\": 0                                  \
        },                                  \
        \"3\":{                                  \
            \"aisle\": 3,                                  \
            \"suppressor\": 0                                  \
        },                                  \
        \"4\":{                                  \
            \"aisle\": 4,                                  \
            \"suppressor\": 0                                  \
        },                                  \
        \"@remark\": \"?????? 0x21\"                                  \
    },                                  \
    \"SET_Input_EchoCanceller_Grade\":{                                  \
        \"grade\": 0,                                  \
        \"@remark\": \"?????? 0x22\"                                  \
    },                                  \
    \"SET_Input_EchoCanceller_Ctrl\":{                                  \
        \"cnt\":5,                                  \
        \"0\":{                                  \
            \"aisle\": 0,                                  \
            \"canceller\": 0                                  \
        },                                  \
        \"1\":{                                  \
            \"aisle\": 1,                                  \
            \"canceller\": 0                                  \
        },                                  \
        \"2\":{                                  \
            \"aisle\": 2,                                  \
            \"canceller\": 0                                  \
        },                                  \
        \"3\":{                                  \
            \"aisle\": 3,                                  \
            \"canceller\": 0                                  \
        },                                  \
        \"4\":{                                  \
            \"aisle\": 4,                                  \
            \"canceller\": 0                                  \
        },                                  \
        \"@remark\": \"?????? 0x23\"                                  \
    },                                  \
    \"SET_Input_LfreqExciter_Grade\":{                                  \
        \"cnt\":4,                                  \
        \"0\":{                                  \
            \"aisle\": 0,                                  \
            \"grade\": 0                                  \
        },                                  \
        \"1\":{                                  \
            \"aisle\": 1,                                  \
            \"grade\": 0                                  \
        },                                  \
        \"2\":{                                  \
            \"aisle\": 2,                                  \
            \"grade\": 0                                  \
        },                                  \
        \"3\":{                                  \
            \"aisle\": 3,                                  \
            \"grade\": 0                                  \
        },                                  \
        \"@remark\": \"????????? 0x24\"                                  \
    },                                  \
    \"SET_Input_HfreqExciter_Grade\":{                                  \
        \"cnt\":4,                                  \
        \"0\":{                                  \
            \"aisle\": 0,                                  \
            \"grade\": 0                                  \
        },                                  \
        \"1\":{                                  \
            \"aisle\": 1,                                  \
            \"grade\": 0                                  \
        },                                  \
        \"2\":{                                  \
            \"aisle\": 2,                                  \
            \"grade\": 0                                  \
        },                                  \
        \"3\":{                                  \
            \"aisle\": 3,                                  \
            \"grade\": 0                                  \
        },                                  \
        \"@remark\": \"????????? 0x25\"                                  \
    },                                  \
    \"SET_Input_Exciter_Ctrl\":{                                  \
        \"cnt\":4,                                  \
        \"0\":{                                  \
            \"aisle\": 0,                                  \
            \"exciter\": 0                                  \
        },                                  \
        \"1\":{                                  \
            \"aisle\": 1,                                  \
            \"exciter\": 0                                  \
        },                                  \
        \"2\":{                                  \
            \"aisle\": 2,                                  \
            \"exciter\": 0                                  \
        },                                  \
        \"3\":{                                  \
            \"aisle\": 3,                                  \
            \"exciter\": 0                                  \
        },                                  \
        \"@remark\": \"??????? 0x26\"                                  \
    },                                  \
    \"SET_Input_CallInput\":{                                  \
        \"cnt\":5,                                  \
        \"0\":{                                  \
            \"aisle\": 0,                                  \
            \"call\": 0                                  \
        },                                  \
        \"1\":{                                  \
            \"aisle\": 1,                                  \
            \"call\": 0                                  \
        },                                  \
        \"2\":{                                  \
            \"aisle\": 2,                                  \
            \"call\": 0                                  \
        },                                  \
        \"3\":{                                  \
            \"aisle\": 3,                                  \
            \"call\": 0                                  \
        },                                  \
        \"4\":{                                  \
            \"aisle\": 4,                                  \
            \"call\": 0                                  \
        },                                  \
        \"@remark\": \"???????? 0x27\"                                  \
    },                                  \
    \"SET_Input_BackgroundInput\":{                                  \
        \"cnt\":5,                                  \
        \"0\":{                                  \
            \"aisle\": 0,                                  \
            \"background\": 0                                  \
        },                                  \
        \"1\":{                                  \
            \"aisle\": 1,                                  \
            \"background\": 0                                  \
        },                                  \
        \"2\":{                                  \
            \"aisle\": 2,                                  \
            \"background\": 0                                  \
        },                                  \
        \"3\":{                                  \
            \"aisle\": 3,                                  \
            \"background\": 0                                  \
        },                                  \
        \"4\":{                                  \
            \"aisle\": 4,                                  \
            \"background\": 0                                  \
        },                                  \
        \"@remark\": \"???? 0x28\"                                  \
    },                                  \
    \"SET_Input_Ducking_Gain\":{                                  \
        \"cnt\":5,                                  \
        \"0\":{                                  \
            \"aisle\": 0,                                  \
            \"data1\": 0,                                  \
            \"data2\": 0                                  \
        },                                  \
        \"1\":{                                  \
            \"aisle\": 1,                                  \
            \"background\": 0,                                  \
            \"data1\": 0,                                  \
            \"data2\": 0                                  \
        },                                  \
        \"2\":{                                  \
            \"aisle\": 2,                                  \
            \"background\": 0,                                  \
            \"data1\": 0,                                  \
            \"data2\": 0                                  \
        },                                  \
        \"3\":{                                  \
            \"aisle\": 3,                                  \
            \"background\": 0,                                  \
            \"data1\": 0,                                  \
            \"data2\": 0                                  \
        },                                  \
        \"4\":{                                  \
            \"aisle\": 4,                                  \
            \"background\": 0,                                  \
            \"data1\": 0,                                  \
            \"data2\": 0                                  \
        },                                  \
        \"@remark\": \"???????? 0x29\"                                  \
    },                                  \
    \"SET_Input_Ducking_Threshold\":{                                  \
        \"data1\": 0,                                  \
        \"data2\": 0,                                  \
        \"@remark\": \"?? 0x2a\"                                  \
    },                                  \
    \"SET_Input_Ducking_Depth\":{                                  \
        \"data1\": 0,                                  \
        \"data2\": 0,                                  \
        \"@remark\": \"?? 0x2b\"                                  \
    },                                  \
    \"SET_Input_Ducking_StartTime\":{                                  \
        \"hdata\": 0,                                  \
        \"ldata\": 0,                                  \
        \"@remark\": \"???? 0x2c\"                                  \
    },                                  \
    \"SET_Input_Ducking_HoldTime\":{                                  \
        \"hdata\": 0,                                  \
        \"ldata\": 0,                                   \
        \"@remark\": \"???? 0x2d\"                                  \
    },                                                              \
    \"SET_Input_Ducking_ReleaseTime\":{                                  \
        \"hdata\": 0,                                  \
        \"ldata\": 0,                                  \
        \"@remark\": \"???? 0x2e\"                                  \
    },                                  \
    \"SET_Input_Ducking_Ctrl\":{                                  \
        \"ducking\": 0,                                  \
        \"@remark\": \"????? 0x2f\"                                  \
    },                                  \
    \"SET_MatrixSwitching\":{                                  \
        \"input\": 0,                                  \
        \"output\": 0,                                  \
        \"matrix\": 0,                                  \
        \"@remark\": \"???? 0x30\"                                  \
    },                                  \
    \"SET_Output_DelayTime\":{                                  \
        \"cnt\":4,                                  \
        \"0\":{                                  \
            \"aisle\": 0,                                  \
            \"hdata\": 0,                                  \
            \"ldata\": 0                                  \
        },                                  \
        \"1\":{                                  \
            \"aisle\": 1,                                  \
            \"hdata\": 0,                                  \
            \"ldata\": 0                                  \
        },                                  \
        \"2\":{                                  \
            \"aisle\": 2,                                  \
            \"hdata\": 0,                                  \
            \"ldata\": 0                                  \
        },                                  \
        \"3\":{                                  \
            \"aisle\": 3,                                  \
            \"hdata\": 0,                                  \
            \"ldata\": 0                                  \
        },                                  \
        \"@remark\": \"?????? 0x31\"                                  \
    },                                  \
    \"SET_Output_Delay_Ctrl\":{                                  \
        \"cnt\":4,                                  \
        \"0\":{                                  \
            \"aisle\": 0,                                  \
            \"switch\": 0                                  \
        },                                  \
        \"1\":{                                  \
            \"aisle\": 1,                                  \
            \"switch\": 0                                  \
        },                                  \
        \"2\":{                                  \
            \"aisle\": 2,                                  \
            \"switch\": 0                                  \
        },                                  \
        \"3\":{                                  \
            \"aisle\": 3,                                  \
            \"switch\": 0                                  \
        },                                  \
        \"@remark\": \"?????? 0x32\"                                  \
    },                                  \
    \"SET_USBplayer_Ctrl\":{                                  \
        \"key\": 0,                                  \
        \"@remark\": \"USB??? 0x33\"                                  \
    }                                  \
}";
#endif

#define Cmdlength(x)    (strlen(cmd_list[x].ucmd)+cmd_list[x].valuelen+cmd_list[x].cmdoffset)

#endif

