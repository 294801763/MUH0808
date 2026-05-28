#include "includes.h"

stProjectGlobalAllVar_t g_stPrjGloVar;
const unsigned char DataStr[]=__DATE__;
const unsigned char TimeStr[]=__TIME__;
stVersionType g_stTestVersion;
static volatile u32 gTimerCounters[etINVALID];


uint8_t CRC8Calculate(void *pBuf ,unsigned pBufSize)
{
    uint8_t     retCRCValue = 0x00, *pData, i=0, pDataBuf=0;

    pData=(unsigned char *)pBuf;
    while(pBufSize--)
    {
        pDataBuf=*pData++;
        for(i=0;i<8;i++)
        {
            if((retCRCValue^(pDataBuf))&0x01)
            {
                retCRCValue^=0x18;
                retCRCValue>>=1;
                retCRCValue|=0x80;
            }
            else
            {
                retCRCValue>>=1;
            }
            pDataBuf>>=1;
        }
    }
    return retCRCValue;
}


#if _ENABLE_UART_LEARNING_MESSAGE_FUNCTION
void mapp_UserDataUartKeyValInit(u8 u8Index)
{
    pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
    pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
    pstUartKeyValue_t           pstUartKey = &pstPrjSaveVar->stUartStudyKeyData[u8Index];

    memset(pstUartKey->sKeyValueBuffer, 0 ,SIZE_UART_KEY_VALUE_MAX);
    pstUartKey->u16KeyValueLen = 0;
    pstUartKey->u32BaudRate = 9600;

    pstUartKey->bUartValueHexOrAsciiFlag = FALSE;  // TRUE: HEX ; FALSE: ASCII
    pstUartKey->u16UartValueSendDelayTime = Def_Uart_MessageSendDelayTime;
    pstUartKey->u8UartValueSendMessageNum = Def_Uart_MessageCounter;
    pstUartKey->u16UartValueCounterDelayTime = Def_Uart_CounterDelayTime;
    #if _ENABLE_UART_LEARN_TO_MULTI_FUNCTION
    pstUartKey->u8SendPort = 0;
    pstUartKey->u8SendWhoFollow = 0;
    #endif
}

bool mapp_UserDataUartKeyValCheck(void)
{
    pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
    pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
    u8 l_u8Index;
    u8 l_u8CheckSum;
    bool l_bState = TRUE;

    for(l_u8Index=0; l_u8Index<_NUM_UART_STUDY_KEYS; l_u8Index++)
    {
        pstUartKeyValue_t           pstUartKey = &pstPrjSaveVar->stUartStudyKeyData[l_u8Index];
        l_u8CheckSum = CRC8Calculate((uint8_t *)pstUartKey, ((uint8_t *)&pstUartKey->u8CheckSum - (uint8_t *)pstUartKey));
        if(l_u8CheckSum != pstUartKey->u8CheckSum)
        {
            mapp_UserDataUartKeyValInit(l_u8Index);
            pstUartKey->u8CheckSum = l_u8CheckSum;
            l_bState = FALSE;
        }
    }

    return l_bState;
}

void SetUserData_UartKeyVal(uint8_t u8KeyIndex)
{
    pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
    pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
    pstUartKeyValue_t           pstUartKey = &pstPrjSaveVar->stUartStudyKeyData[u8KeyIndex];

				dbg_printf("e2prom %s %d\r\n",__FUNCTION__,__LINE__);
				
    pstUartKey->u8CheckSum = CRC8Calculate((uint8_t *)pstUartKey, ((uint8_t *)&pstUartKey->u8CheckSum - (uint8_t *)pstUartKey));

    #if (_EN_EEPROM_FUN_SAVE_UART_STUDY_KEYS==_MACRO_ENABLE)
    SaveUserDataToEep(eEepDataIndex_UartKeys,(ADDR_EEPROM_USER_START+((uint8_t *)pstUartKey-(uint8_t *)pstPrjSaveVar)),(uint8_t *)pstUartKey,sizeof(stUartKeyValue_t),TIME_SAVE_TO_EEPROM_IMMEDIATELY, FALSE);
    #endif
}

void SetUserData_UartKeyValSaveAll(void)
{
    pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
    pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
    pstUartKeyValue_t           pstUartKey = &pstPrjSaveVar->stUartStudyKeyData[0];

				dbg_printf("e2prom %s %d\r\n",__FUNCTION__,__LINE__);
				
    pstUartKey->u8CheckSum = CRC8Calculate((uint8_t *)pstUartKey, ((uint8_t *)&pstUartKey->u8CheckSum - (uint8_t *)pstUartKey));

    #if (_EN_EEPROM_FUN_SAVE_UART_STUDY_KEYS==_MACRO_ENABLE)
    SaveUserDataToEep(eEepDataIndex_UartKeys,(ADDR_EEPROM_USER_START+((uint8_t *)pstUartKey-(uint8_t *)pstPrjSaveVar)),(uint8_t *)pstUartKey,(sizeof(stUartKeyValue_t)*(_NUM_UART_STUDY_KEYS)),TIME_SAVE_TO_EEPROM_IMMEDIATELY, FALSE);
    #endif
}

#endif

#if ((_IR_FUNCTION_USE&_IR_FUNCTION_KEY_STUDY)==_IR_FUNCTION_KEY_STUDY)
void mapp_UserDataIrStudyValInit(u8 u8Index)
{
    pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
    pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;

    memset((u8 *)pstPrjSaveVar->stIrStudyKeyData[u8Index].u16KeyWave, 0 ,IR_WAVE_STUDY_BIT_CNT_MAX*2);
    pstPrjSaveVar->stIrStudyKeyData[u8Index].u16BitCnt = 0;
}

bool mapp_UserDataIrStudyValCheck(void)
{
    pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
    pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
    u8 l_u8Index;
    u8 l_u8CheckSum;
    bool l_bState = TRUE;

    for(l_u8Index=0; l_u8Index<_NUM_IR_STUDY_KEYS; l_u8Index++)
    {
        pstIrKeyWave_t           pstIrStudy = &pstPrjSaveVar->stIrStudyKeyData[l_u8Index];
        l_u8CheckSum = CRC8Calculate((uint8_t *)pstIrStudy, ((uint8_t *)&pstIrStudy->u8CheckSum - (uint8_t *)pstIrStudy));
        if(l_u8CheckSum != pstIrStudy->u8CheckSum)
        {
            mapp_UserDataIrStudyValInit(l_u8Index);
            pstIrStudy->u8CheckSum = l_u8CheckSum;
            l_bState = FALSE;
        }
    }

    return l_bState;
}

void SetUserData_IrStudyVal(uint8_t u8KeyIndex, bool bIsr)
{
    pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
    pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
    pstIrKeyWave_t          pstIrStudy = &pstPrjSaveVar->stIrStudyKeyData[u8KeyIndex];

				dbg_printf("e2prom %s %d\r\n",__FUNCTION__,__LINE__);
				
    pstIrStudy->u8CheckSum = CRC8Calculate((uint8_t *)pstIrStudy, ((uint8_t *)&pstIrStudy->u8CheckSum - (uint8_t *)pstIrStudy));

    #if ((_IR_FUNCTION_USE&_IR_FUNCTION_KEY_STUDY)==_IR_FUNCTION_KEY_STUDY)
    SaveUserDataToEep(eEepDataIndex_IrKeys,(ADDR_EEPROM_USER_START+((uint8_t *)pstIrStudy-(uint8_t *)pstPrjSaveVar)),(uint8_t *)pstIrStudy,sizeof(stIrKeyWave_t),TIME_SAVE_TO_EEPROM_IMMEDIATELY, bIsr);
    #endif
}

void SetUserData_IrStudyValSaveAll(bool bIsr)
{
    pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
    pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
    pstIrKeyWave_t          pstIrStudy = &pstPrjSaveVar->stIrStudyKeyData[0];

			 dbg_printf("e2prom %s %d\r\n",__FUNCTION__,__LINE__);
			
    pstIrStudy->u8CheckSum = CRC8Calculate((uint8_t *)pstIrStudy, ((uint8_t *)&pstIrStudy->u8CheckSum - (uint8_t *)pstIrStudy));

    #if ((_IR_FUNCTION_USE&_IR_FUNCTION_KEY_STUDY)==_IR_FUNCTION_KEY_STUDY)
    SaveUserDataToEep(eEepDataIndex_IrKeys,(ADDR_EEPROM_USER_START+((uint8_t *)pstIrStudy-(uint8_t *)pstPrjSaveVar)),(uint8_t *)pstIrStudy,(sizeof(stIrKeyWave_t)*(_NUM_IR_STUDY_KEYS)),TIME_SAVE_TO_EEPROM_IMMEDIATELY, bIsr);
    #endif
}
#endif //add by wf8421


void mapp_UserDataProjectNameInit(void)
{
    pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
    pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
    pstProjectNameSet_t         pstPrjNameSet = &pstPrjSaveVar->stPrjNameSet;
    
    dbg_printf("e2prom - app_UserDataToDefault %s %d\r\n",__FUNCTION__,__LINE__);
    
    memset(pstPrjNameSet->sPrjName, 0, SIZE_PRJ_NAME_CHARS_MAX);
    pstPrjNameSet->m_u8Len = 0;
}

bool mapp_UserDataProjectNameCheck(void)
{
    pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
    pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
    pstProjectNameSet_t         pstPrjNameSet = &pstPrjSaveVar->stPrjNameSet;
    u8 l_u8CheckSum;
    bool l_bState = TRUE;

    l_u8CheckSum = CRC8Calculate((uint8_t *)pstPrjNameSet, ((uint8_t *)&pstPrjNameSet->u8CheckSum - (uint8_t *)pstPrjNameSet));
    if(l_u8CheckSum != pstPrjNameSet->u8CheckSum)
    {
        pstPrjNameSet->u8CheckSum = l_u8CheckSum;
        mapp_UserDataProjectNameInit();
        l_bState = FALSE;
    }

    return l_bState;
}

void SetUserData_ProjectName(char *strPrjName, uint8_t len)
{
    pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
    pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
    pstProjectNameSet_t         pstPrjNameSet = &pstPrjSaveVar->stPrjNameSet;

				dbg_printf("e2prom %s %d\r\n",__FUNCTION__,__LINE__);
				
    memset(pstPrjNameSet->sPrjName, 0, SIZE_PRJ_NAME_CHARS_MAX);
    memcpy(pstPrjNameSet->sPrjName, strPrjName, len);
    pstPrjNameSet->m_u8Len = len;

    pstPrjNameSet->u8CheckSum = CRC8Calculate((uint8_t *)pstPrjNameSet, ((uint8_t *)&pstPrjNameSet->u8CheckSum - (uint8_t *)pstPrjNameSet));

    SaveUserDataToEep(eEepDataIndex_ProjectName,(ADDR_EEPROM_USER_START+((uint8_t *)pstPrjNameSet-(uint8_t *)pstPrjSaveVar)),(uint8_t *)pstPrjNameSet,sizeof(stProjectNameSet_t),TIME_SAVE_TO_EEPROM_IMMEDIATELY, FALSE);
}


//------------------------------------------------------------------------------
// Function:    HexAndAsciiChange
// Description: Hex 和 Ascii之间的转换
// cmode : 1 Hex to Ascii    0: Ascii to Hex
//------------------------------------------------------------------------------
u8 HexAndAsciiChange(u8 cvalue,u8 cmode)
{
    u8 reValue=0;

    if(cmode == 1)
    {
        if((cvalue&0x0F)>=0&&(cvalue&0x0F)<=9)
        {
            reValue=cvalue+'0';
        }
        else if((cvalue&0x0F)>=0x0A&&(cvalue&0x0F)<=0x0F)
        {
            reValue=cvalue-0x0A+'A';
        }
        else
        {
            reValue=cvalue;
            //printf("Change error: %x\n",cvalue);
        }
    }
    else
    {
        if(((cvalue)>='0'&&(cvalue)<='9'))
        {
            reValue=cvalue-'0';
        }
        else if((cvalue)>='A'&&(cvalue)<='F')
        {
            reValue=cvalue+0x0A-'A';
        }
        else if((cvalue)>='a'&&(cvalue)<='f')
        {
            reValue=cvalue+0x0A-'a';
        }
        else
        {
            reValue=cvalue;
            //printf("Change error: %x\n",cvalue);
        }
    }

    return reValue;
}

//========================================================================================
//------------------------------------------------------------------------------
// Function:    isNumberCmd
// Description: 判断数据是否为数字
//------------------------------------------------------------------------------
bool isNumberCmd(char *cmd, uint16_t len)
{
    uint16_t i;

    for(i=0; i<len; i++)
    {
        if((cmd[i]<'0')||(cmd[i]>'9'))
        {
            return FALSE;
        }
    }

    return TRUE;
}

//========================================================================================
// add by wf8421 20180426
//------------------------------------------------------------------------------
// Function:    PlatformTimerSet
// Description: 设置相关功能定时器时间
//------------------------------------------------------------------------------
void PlatformTimerSet( uint8_t index, u32 m_sec )
{
    switch ( index )
    {
        default:
            if (index<etINVALID)
            {
                gTimerCounters[index] = m_sec;
            }
            break;
    }
}

//------------------------------------------------------------------------------
// Function:    PlatformTimerSet
// Description: 获取相关功能定时器时间
//------------------------------------------------------------------------------
u32 PlatformTimerGet(uint8_t eTimer)
{
    return(gTimerCounters[eTimer]);
}

//------------------------------------------------------------------------------
// Function:    PlatformTimerSet
// Description: 定时器初始化
//------------------------------------------------------------------------------
void PlatformTimerInit (void)
{
    int i;
    //initializer timer counters in array
    for ( i = 0; i < etINVALID; i++ )
    {
        gTimerCounters[ i ] = 0;
    }

    //PlatformTimerSet(etKEY_Detect,5000);
}

//------------------------------------------------------------------------------
// Function:    PlatformTimerSet
// Description: 定时器递减函数
//------------------------------------------------------------------------------
void PlatformTimerTask(void)
{
    int i;
    for(i=0;i<etINVALID;i++)
    {
        if(gTimerCounters[i] > 0)
        {
            gTimerCounters[i]--;
        }
    }
}

//------------------------------------------------------------------------------
// Function:    PlatformTimerSet
// Description: 相关功能定时器时间是否为0
//------------------------------------------------------------------------------
uint8_t PlatformTimerExpired ( uint8_t timer )         //定时时间到函数
{
    if ( timer < etINVALID )
    {
        return( gTimerCounters[ timer ] == 0);             //定时时间到时返回1
    }

    return( 0 );                                           //定时时间还没到时返回0
}
//========================================================================================

#if 0
char *my_StrStr(char *inBuffer,char *inSerchStr)
{
    char *pCurrBuffer = inBuffer;
    while(*pCurrBuffer != '\0')
    {
        char *pCompareOne = pCurrBuffer;
        char *pCompareTow = inSerchStr;
        //while(tolower(*pCompareOne) == tolower(*pCompareTow))
        while((*pCompareOne) == (*pCompareTow))
        {
            pCompareOne++;
            pCompareTow++;
            if(*pCompareTow == '\0')
            {
                return (char*)pCompareOne;
            }
        }
        pCurrBuffer++;
    }
    return NULL;
}
#else
char *my_StrStr(char *inBuffer,char *inSerchStr)//参照strstr函数原型构建自己的strstr函数
{
	char*s1 = NULL;//创建一个空指针；
	char*s2 = NULL;
	char*cur = inBuffer;
	if (*inSerchStr == '\0')
	{
		return (char*)inBuffer;                    //如果我们所要找的子串inSerchStr为'\0',返回总串的首元素地址
	}

	while (*cur)//cur代表指向的是子串第一次出现的首元素地址
	{
		s1 = cur;                      //把cur指向字符串的首元素地址赋给s1
		s2 = (char*)inSerchStr;                    //把inSerchStr指向的首元素地址赋给s2，每一次循环都要从inSerchStr的首元素地址开始重新比较
		while ((*s1 != 0) && (*s2 != 0) && *s1 == *s2)           //只有在s1指向的首元素地址，s2指向的首元素地址都不为'\0'的时候，才可以在总串中找子串的首地址第一次出现的时候
		{                                            // 比较s1，s2指向的地址所对应的字符是否相等，若相等，各自指向的地址向后跳一个字节比较下一位是否相等在满足以上的条件下不断循环，若不满足，
			s1++;                                    //开始一下比较
			s2++;
		}
		if (*s2 == '\0')             //若经过上面的比较，s2指向的内容恰好是'\0',代表找到子串首次出现的地址
		{                              //若不满足以上情况的比较，开始以下比较
			return (char*)cur;
		}
		if (*s1 == '\0')
		{
			return NULL;            //若在s2指向的内容不为'\0'时，s1指向的内容率先为0，代表总串长度比子串长度短，必不存在子串，返回一个空指针
		}
		cur++;//代表当前cur指向的并不是子串第一次出现的首元素地址，指向的地址要往后跳一个字节
	}

	return NULL;//如果经过以上比较都不能得出结果，代表找不到子串，要返回空指针
}
#endif

char *my_CaseStrStr(char *inBuffer,char *inSerchStr)
{
    char *pCurrBuffer = inBuffer;
    while(*pCurrBuffer != '\0')
    {
        char *pCompareOne = pCurrBuffer;
        char *pCompareTow = inSerchStr;
        while(tolower(*pCompareOne) == tolower(*pCompareTow))
        {
            pCompareOne++;
            pCompareTow++;
            if(*pCompareTow == '\0')
            {
                return (char*)pCompareOne;
            }
        }
        pCurrBuffer++;
    }
    return NULL;
}

char *FindChar(char *buf,char Taildata,uint16_t Bitwide)
{
    //char MemberArr[4];
//  unsigned char Arrcur=0;
    unsigned char bitcnt=0;

    while(*buf!=Taildata)
    {
        buf++;
        bitcnt++;
        if(bitcnt > Bitwide)
            return 0;
    }
    return buf;
}

/*输入字符buf转成数字 返回数字*/
unsigned short StrToNum(char *Str,unsigned char cursor)
{
    unsigned char i;
    unsigned short Num=0;
    for(i=0;i<10;i++)
    {
        if(i<cursor)
        {
            //Num+=(Str[i]-0x30)*pow(10,cursor-1-i);
            Num=Num*10+(Str[i]-0x30);
        }
        else
            Str[i]=' ';
    }
    return Num;
}

/*数字转换成字符buf 返回buf的字符个数*/
unsigned short NumToStr(char* buf,char* Str,unsigned char member)
{
    unsigned char tempB=0,tempS=0,tempG=0;
    unsigned short i;
    unsigned short strcursor=0;
    for(i=0;i<member;i++)
    {
        tempB=buf[i]/100;
        if(tempB)
        {
            Str[strcursor++]=tempB+0x30;
        }
        tempS=buf[i]%100/10;
        if(tempS||tempB)
        {
            Str[strcursor++]=tempS+0x30;
        }
        tempG=buf[i]%10;
        if(tempS||tempB||tempG)
        {
            Str[strcursor++]=tempG+0x30;
            if(i+1<member)
                Str[strcursor++]=',';
        }
    }
    return strcursor;
}

/*在字符串中寻找数字 并返回数字 未找到返回-1*/
short GetNumofStr(char *buf,char Taildata,unsigned char Bitwide)
{
    char MemberArr[10];
    unsigned char Arrcur=0;
    unsigned char bitcnt=0;

    while(*buf!=Taildata)
    {
        if(*buf>='0'&&*buf<='9')
        {
            MemberArr[Arrcur]=*buf;
            Arrcur++;
        }
        else
            return -1;
        buf++;
        bitcnt++;
        if(bitcnt>Bitwide)
            return -1;
    }
    return StrToNum(MemberArr,bitcnt);
}

/*在字符串中寻找数字 并返回数字字符个数 未找到返回0*/
unsigned char GetLenOfStr(char *buf,char Taildata,unsigned char Bitwide)
{
    //char MemberArr[4];
    unsigned char Arrcur=0;
    unsigned char bitcnt=0;

    while(*buf!=Taildata)
    {
        if(*buf>='0'&&*buf<='9')
        {
            //MemberArr[Arrcur]=*buf;
            Arrcur++;
        }
        else
            return 0;
        buf++;
        bitcnt++;
        if(bitcnt>Bitwide)
            return 0;
    }
    return bitcnt;
}

//  mode = 1   high->low
//  mode = 0   low->high
void bubble_sort(u8* a, u8 n,u8 mode)
{
    u8 i, j, temp;
    for (j = 0; j < n - 1; j++)
        for (i = 0; i < n - 1 - j; i++)
        {
            if(!mode)
            {
                if(a[i] > a[i + 1])
                {
                    temp = a[i];
                    a[i] = a[i + 1];
                    a[i + 1] = temp;
                }
            }
            else
            {
                if(a[i] < a[i + 1])
                {
                    temp = a[i];
                    a[i] = a[i + 1];
                    a[i + 1] = temp;
                }
            }
        }
}

void mapp_RevisionMake(void)
{
    u16 l_u16Year;
    u8  l_u8Month;
    u8  l_u8Date;
    u8  l_u8Hour;
    u8  l_u8minute;
    u8  l_u8Second;

    switch(DataStr[2])      //月份字符转成日期数字，先判断第三个字幕，再判断第二个字幕，获取月份
    {
        case 'n':   // Jan / Jun
            {
                l_u8Month = DataStr[1] == 'a' ? 1 : 6;
            }
            break;
        case 'b':   // Feb
            {
                l_u8Month = 2;
            }
            break;
        case 'r':   // Mar / Apr
            {
                l_u8Month = DataStr[1] == 'a' ? 3 : 4;
            }
            break;
        case 'y':   // May
            {
                l_u8Month = 5;
            }
            break;
        case 'l':   // Jul
            {
                l_u8Month = 7;
            }
            break;
        case 'g':   // Aug
            {
                l_u8Month = 8;
            }
            break;
        case 'p':   // Sep
            {
                l_u8Month = 9;
            }
            break;
        case 't':   // Oct
            {
                l_u8Month = 10;
            }
            break;
        case 'v':   // Nov
            {
                l_u8Month = 11;
            }
            break;
        case 'c':   // Dec
            {
                l_u8Month = 12;
            }
            break;
    }

    l_u16Year = HexAndAsciiChange(DataStr[7],0)*1000
                +HexAndAsciiChange(DataStr[8],0)*100
                +HexAndAsciiChange(DataStr[9],0)*10
                +HexAndAsciiChange(DataStr[10],0);
    l_u8Date = ((DataStr[4]!=' ')?(HexAndAsciiChange(DataStr[4],0)*10):0)
                +HexAndAsciiChange(DataStr[5],0);

    l_u8Hour = HexAndAsciiChange(TimeStr[0],0)*10
                +HexAndAsciiChange(TimeStr[1],0);
    l_u8minute = HexAndAsciiChange(TimeStr[3],0)*10
                +HexAndAsciiChange(TimeStr[4],0);
    l_u8Second = HexAndAsciiChange(TimeStr[6],0)*10
                +HexAndAsciiChange(TimeStr[7],0);

    g_stTestVersion.u16Year  = l_u16Year;
    g_stTestVersion.u8Month  = l_u8Month;
    g_stTestVersion.u8Date   = l_u8Date;
    g_stTestVersion.u8Hour   = l_u8Hour;
    g_stTestVersion.u8minute = l_u8minute;
    g_stTestVersion.u8Second = l_u8Second;
}

bool buffer_compare(pu8 arry1,pu8 arry2,u16 u16Len)
{
	u16 i;
	bool ret=TRUE;

	for(i=0;i<u16Len;i++)
	{
		if(*(arry1+i) != *(arry2+i))
		{
			ret = FALSE;
			break;
		}
	}
	return ret;
}

u16 U16ToU8MsbCovert(pu16 arry1,pu8 arry2,u16 u16Len)
{
	u16 i;
	u16 l_u16RealLen=0;

	for(i=0;i<u16Len;i++)
	{
        arry2[l_u16RealLen++] = (arry1[i]>>8)&0xFF;
        arry2[l_u16RealLen++] = (arry1[i])&0xFF;
	}
	return l_u16RealLen;
}

u16 U8ToU16MsbCovert(pu8 arry1,pu16 arry2,u16 u16Len)
{
	u16 i;
	u16 l_u16RealLen=0;

	for(i=0;i<u16Len;i=i+2)
	{
        arry2[l_u16RealLen] = arry1[i];
        arry2[l_u16RealLen] = (arry2[l_u16RealLen]<<8) | arry1[i+1];
        l_u16RealLen++;
	}
	return l_u16RealLen;
}





