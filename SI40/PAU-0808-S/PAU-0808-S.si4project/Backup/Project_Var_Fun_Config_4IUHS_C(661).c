#define __PROJECT_VAR_FUN_CONFIG_C__

#include "includes.h"

#if USER_FUNCTION_DEBUG
#define DBG_USER_FUN        Uart_printf
#else
#define DBG_USER_FUN(...)
#endif

stProjectSpecVar_t  stLMX_4IUHS_CSpecVar;

static volatile u32 g_LMX_4IUHS_C_Timers[emUserTimer_Max];

extern stProjectGlobalAllVar_t g_stPrjGloVar;



const u8 cg_u8ChannelTable[4][3]=
{
  //TXIndex,RxPort,AudioPort
    {0,         2,          1},
    {1,         1,          0},
    {2,         0,          3},
    {3,         3,          2},
};


//========================================================================================
// add by wf8421 20190820
//------------------------------------------------------------------------------
// Function:    mapp_MHD1616STX_PlatformTimerSet
// Description: 设置相关功能定时器时间
//------------------------------------------------------------------------------
void mapp_LMX_4IUHS_C_PlatformTimerSet( uint8_t index, u32 m_sec )
{
    switch ( index )
    {
        default:
            if (index<emUserTimer_Max)
            {
                g_LMX_4IUHS_C_Timers[index] = m_sec;
            }
            break;
    }
}

//------------------------------------------------------------------------------
// Function:    mapp_MHD1616STX_PlatformTimerGet
// Description: 获取相关功能定时器时间
//------------------------------------------------------------------------------
u32 mapp_LMX_4IUHS_C_PlatformTimerGet(uint8_t eTimer)
{
    return(g_LMX_4IUHS_C_Timers[eTimer]);
}

//------------------------------------------------------------------------------
// Function:    mapp_MHD1616STX_PlatformTimerInit
// Description: 定时器初始化
//------------------------------------------------------------------------------
void mapp_LMX_4IUHS_C_PlatformTimerInit (void)
{
    int i;
    //initializer timer counters in array
    for ( i = 0; i < emUserTimer_Max; i++ )
    {
        g_LMX_4IUHS_C_Timers[ i ] = 0;
    }

    //PlatformTimerSet(etKEY_Detect,5000);
}

//------------------------------------------------------------------------------
// Function:    mapp_MHD1616STX_PlatformTimerTask
// Description: 定时器递减函数
//------------------------------------------------------------------------------
void mapp_LMX_4IUHS_C_PlatformTimerTask(void)
{
    int i;
    for(i=0;i<emUserTimer_Max;i++)
    {
        if(g_LMX_4IUHS_C_Timers[i] > 0)
        {
            g_LMX_4IUHS_C_Timers[i]--;
        }
    }
}

//------------------------------------------------------------------------------
// Function:    mapp_MHD1616STX_PlatformTimerExpired
// Description: 相关功能定时器时间是否为0
//------------------------------------------------------------------------------
uint8_t mapp_LMX_4IUHS_C_PlatformTimerExpired ( uint8_t timer )           //定时时间到函数
{
    if ( timer < emUserTimer_Max )
    {
        return( g_LMX_4IUHS_C_Timers[ timer ] == 0);              //定时时间到时返回1
    }

    return( 0 );                                           //定时时间还没到时返回0
}
//========================================================================================
void LMX_4IUHS_C_1msTimerIrq(void)
{
    mapp_LMX_4IUHS_C_PlatformTimerTask();
}

void LMX_4IUHS_C_SpecificVarInit(void)
{
    pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
    pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
    pstProjectSpecVar_t         pstSpecVar = &stLMX_4IUHS_CSpecVar;

    memset(pstSpecVar, 0, sizeof(stProjectSpecVar_t));
    pstPrjSaveVar->stSaveSpecVar.pvSpecVar = (void *)pstSpecVar;
    pstPrjSaveVar->stSaveSpecVar.u16SpecVarSize = sizeof(stProjectSpecVar_t);

}

void LMX_4IUHS_C_SpecificVarDefault(void)
{
    LMX_4IUHS_C_SpecBasicVarDefault();
    LMX_4IUHS_C_SpecCustomEdidVarDefault();
}

void LMX_4IUHS_C_SpecBasicVarDefault(void)
{
    pstProjectSpecVar_t         pstSpecVar = &stLMX_4IUHS_CSpecVar;
    u8 i;

    pstSpecVar->stBasSpecVar.bPowerOnSta = TRUE;
//    pstSpecVar->stBasSpecVar.bIsDebugEn = FALSE;

    for(i=0;i<Def_outport_num;i++)
    {
    }

    for(i=0;i<_HDMI_INPUT_PORT_USED_NUMBER;i++)
    {
    }
}

void LMX_4IUHS_C_SpecCustomEdidVarDefault(void)
{

}

bool LMX_4IUHS_C_SpecVarValidCheck(void)
{
    pstProjectSpecVar_t         pstSpecVar = &stLMX_4IUHS_CSpecVar;
    bool                        isSpecVarValid = TRUE;

    if(pstSpecVar->stBasSpecVar.u8CheckSum != CRC8Calculate((uint8_t *)&pstSpecVar->stBasSpecVar,((uint8_t *)&pstSpecVar->stBasSpecVar.u8CheckSum-(uint8_t *)&pstSpecVar->stBasSpecVar)))
    {
        LMX_4IUHS_C_SpecBasicVarDefault();
        pstSpecVar->stBasSpecVar.u8CheckSum = CRC8Calculate((uint8_t *)&pstSpecVar->stBasSpecVar,((uint8_t *)&pstSpecVar->stBasSpecVar.u8CheckSum-(uint8_t *)&pstSpecVar->stBasSpecVar));

        isSpecVarValid = FALSE;
    }


#if 0
    if(pstSpecVar->stCustomEdidPre2.u8CheckSum != CRC8Calculate((uint8_t *)&pstSpecVar->stCustomEdidPre2,((uint8_t *)&pstSpecVar->stCustomEdidPre2.u8CheckSum-(uint8_t *)&pstSpecVar->stCustomEdidPre2)))
    {
        memcpy(pstSpecVar->stCustomEdidPre2.pu8EdidContext, System_Default_Edid_table, 256);
        pstSpecVar->stCustomEdidPre2.u8CheckSum = CRC8Calculate((uint8_t *)&pstSpecVar->stCustomEdidPre2,((uint8_t *)&pstSpecVar->stCustomEdidPre2.u8CheckSum-(uint8_t *)&pstSpecVar->stCustomEdidPre2));

        isSpecVarValid = FALSE;
    }

    if(pstSpecVar->stCustomEdidPre3.u8CheckSum != CRC8Calculate((uint8_t *)&pstSpecVar->stCustomEdidPre3,((uint8_t *)&pstSpecVar->stCustomEdidPre3.u8CheckSum-(uint8_t *)&pstSpecVar->stCustomEdidPre3)))
    {
        memcpy(pstSpecVar->stCustomEdidPre3.pu8EdidContext, System_Default_Edid_table, 256);
        pstSpecVar->stCustomEdidPre3.u8CheckSum = CRC8Calculate((uint8_t *)&pstSpecVar->stCustomEdidPre3,((uint8_t *)&pstSpecVar->stCustomEdidPre3.u8CheckSum-(uint8_t *)&pstSpecVar->stCustomEdidPre3));

        isSpecVarValid = FALSE;
    }

    if(pstSpecVar->stCustomEdidPre4.u8CheckSum != CRC8Calculate((uint8_t *)&pstSpecVar->stCustomEdidPre4,((uint8_t *)&pstSpecVar->stCustomEdidPre4.u8CheckSum-(uint8_t *)&pstSpecVar->stCustomEdidPre4)))
    {
        memcpy(pstSpecVar->stCustomEdidPre4.pu8EdidContext, System_Default_Edid_table, 256);
        pstSpecVar->stCustomEdidPre4.u8CheckSum = CRC8Calculate((uint8_t *)&pstSpecVar->stCustomEdidPre4,((uint8_t *)&pstSpecVar->stCustomEdidPre4.u8CheckSum-(uint8_t *)&pstSpecVar->stCustomEdidPre4));

        isSpecVarValid = FALSE;
    }
#endif

    return isSpecVarValid;
}

void SetUserData_SpecBasicVar(void)
{
    pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
    pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
    pstProjectSpecVar_t         pstSpecVar = &stLMX_4IUHS_CSpecVar;
    pstBasicSpecVar_t           pstBasicVar = &pstSpecVar->stBasSpecVar;

    pstBasicVar->u8CheckSum = CRC8Calculate((uint8_t *)pstBasicVar, ((uint8_t *)&pstBasicVar->u8CheckSum-(uint8_t *)pstBasicVar));
    SaveUserDataToEep(eEepDataIndex_SpecBlock1,\
        (ADDR_EEPROM_USER_START+((uint8_t *)&pstPrjSaveVar->stSaveSpecVar-(uint8_t *)pstPrjSaveVar)),\
        (uint8_t *)pstBasicVar, sizeof(stBasicSpecVar_t), TIME_SAVE_TO_EEPROM_IMMEDIATELY, FALSE);
}

void SetUserData_SpecCustomEdid(uint8_t u8CustomEdidIndex)
{
}

// the status when power on device
void LMX_4IUHS_C_PrjStatePowerOnInit(void)
{
    pstProjectSpecVar_t         pstSpecVar = &stLMX_4IUHS_CSpecVar;
    pstBasicSpecVar_t           pstBasicVar = &pstSpecVar->stBasSpecVar;

    // prj 1ms loop hook
    pFuncPrj1MsLoopHook = LMX_4IUHS_C_1msTimerIrq;
    g_bEnableDbgFlag = pstBasicVar->bIsDebugEn;

    mapp_RevisionMake();
}

void LMX_4IUHS_C_LedWork_Loop(void)
{
    static bool sl_bLedSta = FALSE;
    if(!mapp_LMX_4IUHS_C_PlatformTimerExpired(emUserTimer_LedActive))
        return;
    mapp_LMX_4IUHS_C_PlatformTimerSet(emUserTimer_LedActive,500);

    if(sl_bLedSta)
    {
        sl_bLedSta = FALSE;
        led_on(led_name_ActiveLed);
    }
    else
    {
        sl_bLedSta = TRUE;
        led_off(led_name_ActiveLed);
    }
}

// the status of led when running system
void LMX_4IUHS_C_FuncWork_LoopRunning(void)
{
    LMX_4IUHS_C_LedWork_Loop();
}

void mapp_LMX_4IUHS_CStartupMessage(void)
{
    pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
    pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
    pstProjectSpecVar_t         pstSpecVar = &stLMX_4IUHS_CSpecVar;
    pstBasicSpecVar_t           pstBasicVar = &pstSpecVar->stBasSpecVar;
    u8 i;

    RS232_printf("\r\n");
    RS232_printf("System Initializing...\r\n");
    RS232_printf("\r\n");
    RS232_printf("Initialization Finished!\r\n");
    RS232_printf("%s %s\r\n",_STRING_FW_VERSION,_STRING_FW_VER_NUM);
    for(i=0;i<Def_outport_num;i++)
    {
    }
}



