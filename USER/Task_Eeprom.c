#include "includes.h"

stEepDataSave_t g_EepromDataSave[eEepDataIndex_Max-1];
//stGUIEepDataSave_t g_GUIEepDataSave;
//stGUIEepDataSave_t g_GUIEepromDataSave[eEepDataIndex_Max - 1];
extern stProjectGlobalAllVar_t g_stPrjGloVar;

#if _SYSTEM_SUPPORT_RTOS
#if _EN_MAIN_TASK_EEPROM
extern QueueHandle_t xQueue_EProcess;
//extern QueueHandle_t xQueue_EGUIProcess;

void v_hexdump ( unsigned char* v_first_address, u32 v_length )
{
#if 0
	u32 i,j,k;
	unsigned char v_binstr[256];

	for ( i = 0l; i<v_length; i++ )
	{
		if ( 0 == ( i%16 ) )
		{
			sprintf ( v_binstr,"%p -",i+v_first_address );
			sprintf ( v_binstr,"%s %02x",v_binstr, ( unsigned char ) v_first_address[i] );
		}
		else if ( 15 == ( i%16 ) )
		{
			sprintf ( v_binstr,"%s %02x",v_binstr, ( unsigned char ) v_first_address[i] );
			sprintf ( v_binstr,"%s  ",v_binstr );

			for ( j = i-15; j <= i; j++ )
			{
				sprintf ( v_binstr,"%s%c",v_binstr, ( '!'<v_first_address[j]&&v_first_address[j]<='~' ) ?v_first_address[j]:'.' );
			}
			dbg_printf ( "%s\n",v_binstr );
		}
		else
		{
			sprintf ( v_binstr,"%s %02x",v_binstr, ( unsigned char ) v_first_address[i] );
		}
	}

	if ( 0 != ( i%16 ) )
	{
		k = 16 - ( i%16 );

		for ( j = 0; j < k; j++ )
		{
			sprintf ( v_binstr,"%s   ",v_binstr );
		}

		sprintf ( v_binstr,"%s  ",v_binstr );
		k = 16 - k;

		for ( j = i - k; j < i; j++ )
		{
			sprintf ( v_binstr,"%s%c",v_binstr, ( '!'<v_first_address[j]&&v_first_address[j]<='~' ) ?v_first_address[j]:'.' );
		}
		dbg_printf ( "%s\n",v_binstr );
	}
#endif
}

void hexdump ( const void* pdata, int len )
{
	int i, j, k, l;
	const char* data = ( const char* ) pdata;
	char buf[256], str[64], t[] = "0123456789ABCDEF";
	for ( i = j = k = 0; i < len; i++ )
	{
		if ( 0 == i % 16 )
		{
			j += sprintf ( buf + j, "%04xh: ", i );
		}
		buf[j++] = t[0x0f & ( data[i] >> 4 )];
		buf[j++] = t[0x0f & data[i]];
		buf[j++] = ' ';
		str[k++] = isprint ( data[i] ) ? data[i] : '.';
		if ( 0 == ( i + 1 ) % 16 )
		{
			str[k] = 0;
			j += sprintf ( buf + j, "; %s\n", str );
			dbg_printf ( "%s", buf );
			j = k = buf[0] = str[0] = 0;
		}
	}
	str[k] = 0;
	if ( k )
	{
		for ( l = 0; l < 3 * ( 16 - k ); l++ )
		{
			buf[j++] = ' ';
		}
		j += sprintf ( buf + j, "; %s\n", str );
	}
	if ( buf[0] )
	{
		dbg_printf ( "%s", buf );
	}
}


#if 0
void vTaskEGUIeprom ( void* pvParameters )
{
	const TickType_t    xTicksToWait = 20;//0;//20;//
	BaseType_t          xResult;
	pstEepDataSave_t    pEeData, pData1;

	( void ) pvParameters;
	for (;; )
	{
		memset ( pEeData, 0, sizeof ( pststMachVal_t ) );
		xResult = xQueueReceive ( xQueue_EGUIProcess, ( void* ) &pEeData, ( TickType_t ) xTicksToWait );
		if ( xResult == pdPASS )
		{
			dbg_printf ( "%s:%d\r\n",__FUNCTION__,__LINE__ );
			v_hexdump ( pData1->pvBufferAdr,sizeof ( stMachVal_t ) );

		}
	}

}
#endif

void vTaskGUIEeprom ( void* pvParameters )
{
	pststMachVal_t    pGUIEeData;
	const TickType_t    xTicksToWait = 0;//0;//20;//
	BaseType_t          xResult;

	for (;; )
	{
		xResult = xQueueReceive ( xQueue_EProcess, ( void* ) &pGUIEeData, ( TickType_t ) xTicksToWait );

	}
}


void vTaskEeprom ( void* pvParameters )
{
	//u8 index = 0;
	//const TickType_t    xTicksToWait = 20;//0;//20;//
	const TickType_t    xTicksToWait = 0;//0;//20;//
	//const TickType_t    xTicksToWait = portMAX_DELAY;//0;//20;//
	BaseType_t          xResult;
	pstEepDataSave_t    pEeData, pData1;
	eEepDataIndex_t     i;

	( void ) pvParameters;

	dbg_printf ( "e2prom %s %d portMAX_DELAY:%d \r\n",__FUNCTION__,__LINE__,portMAX_DELAY );
	dbg_printf ( "AT24CM01_MAX_ADDR:%d\r\n",AT24CM01_MAX_ADDR );
	dbg_printf ( "AT24CM01_PAGE_SIZE:%d\r\n",AT24CM01_PAGE_SIZE );

	//xMutex = xSemaphoreCreateMutex();
	memset ( g_EepromDataSave, 0, sizeof ( stEepDataSave_t ) * ( eEepDataIndex_Max-1 ) );

	for (;; )
	{
		xResult = xQueueReceive ( xQueue_EProcess, ( void* ) &pEeData, ( TickType_t ) xTicksToWait );

		if ( xResult == pdPASS )
		{
			//dbg_printf("index:%d 11111111111111111111111111111111111111111111111111\r\n",index);
			//index++;

			for ( i= ( eEepDataIndex_t ) 1; i < eEepDataIndex_Max; i++ )
			{
				pData1 = pEeData + ( i - 1 );

				if ( pData1->u16EepSaveAfT > 0 )
				{
					pData1->u16EepSaveAfT --;
					if ( pData1->u16EepSaveAfT == 0 )
					{
						dbg_printf ( "Save pData1          == 0x%08x\r\n",pData1 );
						dbg_printf ( "Save u32EepSaveAdr   == 0x%x\r\n",pData1->u32EepSaveAdr );
						dbg_printf ( "Save pvBufferAdr     == 0x%08x\r\n",pData1->pvBufferAdr );
						dbg_printf ( "Save u32EepSaveLen   == %d\r\n",pData1->u32EepSaveLen );

						dbg_printf ( "%s:%d\r\n",__FUNCTION__,__LINE__ );
						v_hexdump ( pData1->pvBufferAdr,sizeof ( stMachVal_t ) );

						eeprom_write ( pData1->u32EepSaveAdr, ( uint8_t* ) pData1->pvBufferAdr, pData1->u32EepSaveLen );
						vTaskDelay ( 5 );
						pData1->bEepSaveOkFlag = TRUE;
					}
				}
			}
		}

		vTaskDelay ( 10 );
	}
}

#endif

//save eeprom data
#if 0
void SaveUserDataToGUIEep ( eEepDataIndex_t eIndex, uint32_t u32EepAdr, uint8_t* pu8Buffer, uint32_t u32Len, uint16_t u16SaveTime, bool bFromIsr )
{
#if _EN_MAIN_TASK_EEPROM
	u8 i = 1;
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	const TickType_t    xTicksToWait = 20;
	pstGUIEepDataSave_t pData1 = g_GUIEepromDataSave, pData2;

	pData2 = pData1 + i;
	pData2->pvBufferAdr = ( void* ) pu8Buffer;
	pData2->u32EepSaveAdr = u32EepAdr;
	pData2->u16EepSaveAfT = u16SaveTime;
	pData2->u32EepSaveLen = u32Len;
	pData2->bEepSaveOkFlag = FALSE;

	dbg_printf ( "e2prom %s %d\r\n",__FUNCTION__,__LINE__ );
	v_hexdump ( ( char* ) pu8Buffer, sizeof ( stMachVal_t ) );

	if ( bFromIsr )
	{
		xQueueSendFromISR ( xQueue_EGUIProcess, ( void* ) &pData1, &xHigherPriorityTaskWoken );
		portYIELD_FROM_ISR ( xHigherPriorityTaskWoken );
	}
	else
	{
		//xQueueSend ( xQueue_EProcess, ( void* ) &pData1, xTicksToWait );
		xQueueSendToBack ( xQueue_EGUIProcess, ( void* ) &pData1, xTicksToWait );
		if ( i >= eEepDataIndex_Max )
		{
			i = 1;
		}
		else
		{
			i++;
		}

		dbg_printf ( "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% \r\n" );
	}

#else
	UNUSED ( eIndex );
	UNUSED ( u32EepAdr );
	UNUSED ( pu8Buffer );
	UNUSED ( u32Len );
	UNUSED ( u16SaveTime );
	UNUSED ( bFromIsr );
#endif
}
#endif

void SaveUserDataToEep ( eEepDataIndex_t eIndex, uint32_t u32EepAdr, uint8_t* pu8Buffer, uint32_t u32Len, uint16_t u16SaveTime, bool bFromIsr )
{
#if _EN_MAIN_TASK_EEPROM
	//u8 i = 1;
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	const TickType_t xTicksToWait = 0;//portMAX_DELAY;
	//const TickType_t xTicksToWait = portMAX_DELAY;//portMAX_DELAY;
	//const TickType_t    xTicksToWait = 20;
	pstEepDataSave_t pData1 = g_EepromDataSave, pData2;

	pData2 = pData1 + eIndex - 1;
	//pData2 = pData1 + i;
	pData2->pvBufferAdr = ( void* ) pu8Buffer;
	pData2->u32EepSaveAdr = u32EepAdr;  //u16EepSaveAfT
	pData2->u16EepSaveAfT = u16SaveTime;
	pData2->u32EepSaveLen = u32Len;
	pData2->bEepSaveOkFlag = FALSE;

	//dbg_printf("pData2      == 0x%08x\r\n",pData2);
	//dbg_printf("pvBufferAdr == 0x%08x\r\n",pu8Buffer);
	//dbg_printf("u32EepAdr   == 0x%x\r\n",u32EepAdr);
	//dbg_printf("u16SaveTime == %d\r\n",u16SaveTime);
	//dbg_printf("u32Len      == %d\r\n",u32Len);

	dbg_printf ( "e2prom %s %d\r\n",__FUNCTION__,__LINE__ );
	v_hexdump ( pData2->pvBufferAdr, sizeof ( stMachVal_t ) );

	dbg_printf ( "g_EepromDataSave - hexdump u32EepSaveAdr:%d \r\n",pData2->u32EepSaveAdr );
	v_hexdump ( g_EepromDataSave->pvBufferAdr, sizeof ( stMachVal_t ) );

	dbg_printf ( "pData1 - hexdump u32EepSaveAdr:%d \r\n",pData2->u32EepSaveAdr );
	v_hexdump ( pData1->pvBufferAdr, sizeof ( stMachVal_t ) );

	if (!bFromIsr )
	{
		xQueueSendFromISR ( xQueue_EProcess, ( void* ) &pData1, &xHigherPriorityTaskWoken );
		portYIELD_FROM_ISR ( xHigherPriorityTaskWoken );

		dbg_printf ( "55555555555555555555555555555555555555555555555555555555555555555555\r\n" );
	}
	else
	{
		//xQueueSend ( xQueue_EProcess, ( void* ) &pData1, xTicksToWait );
		xQueueSendToBack ( xQueue_EProcess, ( void* ) &pData1, xTicksToWait );
		dbg_printf ( "444444444444444444444444444444444444444444444444444444444444444444\r\n" );
	}
#else
	UNUSED ( eIndex );
	UNUSED ( u32EepAdr );
	UNUSED ( pu8Buffer );
	UNUSED ( u32Len );
	UNUSED ( u16SaveTime );
	UNUSED ( bFromIsr );
#endif
}

void WriteGUIDataToEep ( uint32_t u32EepAdr, uint8_t* pu8Buffer, uint32_t u32Len )
{
#if _EN_MAIN_TASK_EEPROM
	//u8 i = 1;
	//BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	//const TickType_t xTicksToWait = 0;//portMAX_DELAY;

	dbg_printf ( "%s %d\r\n",__FUNCTION__,__LINE__ );
	v_hexdump ( pu8Buffer, sizeof ( stMachVal_t ) );

	eeprom_write ( u32EepAdr, pu8Buffer, u32Len );
#else
	UNUSED ( u32EepAdr );
	UNUSED ( pu8Buffer );
	UNUSED ( u32Len );
	UNUSED ( bFromIsr );
#endif
}

void ReadGUIDataFromEep ( uint32_t u32EepAdr, uint8_t* pu8Buffer, uint32_t u32Len )
{
#if _EN_MAIN_TASK_EEPROM
	//u8 i = 1;
	//BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	//const TickType_t xTicksToWait = 0;//portMAX_DELAY;

	//dbg_printf ( "%s %d\r\n",__FUNCTION__,__LINE__ );
	//v_hexdump ( pu8Buffer, sizeof ( stMachVal_t ) );

	eeprom_read ( u32EepAdr, pu8Buffer, u32Len );
#else
	UNUSED ( u32EepAdr );
	UNUSED ( pu8Buffer );
	UNUSED ( u32Len );
	UNUSED ( bFromIsr );
#endif
}

#else

void vTaskEeprom ( void* pvParameters )
{
	( void ) pvParameters;

}

//save eeprom data
void SaveUserDataToEep ( eEepDataIndex_t eIndex, uint32_t u32EepAdr, uint8_t* pu8Buffer, uint32_t u32Len, uint16_t u16SaveTime, bool bFromIsr )
{
	eeprom_write ( u32EepAdr, ( uint8_t* ) pu8Buffer, u32Len );
	UNUSED ( eIndex );
	UNUSED ( u16SaveTime );
	UNUSED ( bFromIsr );
}

#endif

#if _EN_MAIN_TASK_EEPROM
void EepromVarInit ( void )
{
	bool bDefaultSet = FALSE;//reset to default value
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	u8 l_u8MainVer[2];
	u16 l_u16MainVer;

	dbg_printf ( "e2prom %s %d\r\n",__FUNCTION__,__LINE__ );

	eeprom_read ( ADDR_EEPROM_CHECK_MAIN_VER, l_u8MainVer, 2 );
	dbg_printf ( "ADDR_EEPROM_CHECK_MAIN_VER 0x%02x 0x%02x DEF_MAIN_VER:0x%04x \r\n",l_u8MainVer[0],l_u8MainVer[1],DEF_MAIN_VER );

	l_u16MainVer = ( l_u8MainVer[1]<<8 ) |l_u8MainVer[0];
	if ( l_u16MainVer!=DEF_MAIN_VER )
	{
		l_u16MainVer = DEF_MAIN_VER;
		l_u8MainVer[0] = l_u16MainVer&0xFF;
		l_u8MainVer[1] = ( l_u16MainVer>>8 ) &0xFF;

		//写入主版本号
		dbg_printf ( "e2prom - step.1 l_u8MainVer %s %d E2PROM PARAM Address:%d data:0x%04x len:%d \r\n",__FUNCTION__,__LINE__,ADDR_EEPROM_CHECK_MAIN_VER,l_u8MainVer,2 );
		v_hexdump ( ( uint8_t* ) l_u8MainVer,2 );
		eeprom_write ( ADDR_EEPROM_CHECK_MAIN_VER, l_u8MainVer, 2 );

		app_UserDataToDefault();

		bDefaultSet = TRUE;
		if ( bDefaultSet )
		{
			//*测试代码*//
#if 0
			memcpy ( pstPrjSaveVar->stPrjNameSet.sPrjName,"xxxxxxxxxxxxxxxxxx",strlen ( "xxxxxxxxxxxxxxxxxx" ) );
			pstPrjSaveVar->stPrjNameSet.m_u8Len = strlen ( "xxxxxxxxxxxxxxxxxx" );
			pstPrjSaveVar->stPrjNameSet.u8CheckSum = 0xdd;
			pstPrjSaveVar->guiParamter[0].ch = 1;
			pstPrjSaveVar->guiParamter[0].param1[0] = 1;
			pstPrjSaveVar->guiParamter[0].param1[1] = 2;
			pstPrjSaveVar->guiParamter[0].param1[2] = 3;
			pstPrjSaveVar->guiParamter[0].param1[3] = 4;
			pstPrjSaveVar->guiParamter[0].param1[4] = 5;
			pstPrjSaveVar->guiParamter[0].param1[5] = 6;
			pstPrjSaveVar->guiParamter[0].param1[6] = 7;
			pstPrjSaveVar->guiParamter[0].param1[7] = 8;

			pstPrjSaveVar->guiParamter[0].param2[0] = 1;
			pstPrjSaveVar->guiParamter[0].param2[1] = 2;
			pstPrjSaveVar->guiParamter[0].param1[2] = 3;
			pstPrjSaveVar->guiParamter[0].param2[3] = 4;
			pstPrjSaveVar->guiParamter[0].param2[4] = 5;
			pstPrjSaveVar->guiParamter[0].param2[5] = 6;
			pstPrjSaveVar->guiParamter[0].param2[6] = 7;
			pstPrjSaveVar->guiParamter[0].param2[7] = 8;

			pstPrjSaveVar->guiParamter[0].param3[0] = 1;
			pstPrjSaveVar->guiParamter[0].param3[1] = 2;
			pstPrjSaveVar->guiParamter[0].param3[2] = 3;
			pstPrjSaveVar->guiParamter[0].param3[3] = 4;
			pstPrjSaveVar->guiParamter[0].param3[4] = 5;
			pstPrjSaveVar->guiParamter[0].param3[5] = 6;
			pstPrjSaveVar->guiParamter[0].param3[6] = 7;
			pstPrjSaveVar->guiParamter[0].param3[7] = 8;

			pstPrjSaveVar->guiParamter[0].param4[0] = 1;
			pstPrjSaveVar->guiParamter[0].param4[1] = 2;
			pstPrjSaveVar->guiParamter[0].param4[2] = 3;
			pstPrjSaveVar->guiParamter[0].param4[3] = 4;
			pstPrjSaveVar->guiParamter[0].param4[4] = 5;
			pstPrjSaveVar->guiParamter[0].param4[5] = 6;
			pstPrjSaveVar->guiParamter[0].param4[6] = 7;
			pstPrjSaveVar->guiParamter[0].param4[7] = 8;

			pstPrjSaveVar->guiParamter[0].command[0] = 0x01;
			pstPrjSaveVar->guiParamter[0].command[1] = 0x01;
			pstPrjSaveVar->guiParamter[0].command[2] = 0x01;
			pstPrjSaveVar->guiParamter[0].command[3] = 0x01;
			pstPrjSaveVar->guiParamter[0].command[4] = 0x01;
#endif


			dbg_printf ( "size:%d \r\n", ( sizeof ( stProjectGlobalSaveVar_t ) - sizeof ( stPrjSpecVarVector_t ) ) );
			dbg_printf ( "e2prom - step.2 write pstPrjSaveVar %s %d E2PROM PARAM Address:%d data:0x%x len:%d \r\n",__FUNCTION__,__LINE__,ADDR_EEPROM_USER_START,pstPrjSaveVar, ( sizeof ( stProjectGlobalSaveVar_t ) - sizeof ( stPrjSpecVarVector_t ) ) );
			v_hexdump ( ( uint8_t* ) pstPrjSaveVar, ( sizeof ( stProjectGlobalSaveVar_t ) - sizeof ( stPrjSpecVarVector_t ) ) );

			//写入工程名
			eeprom_write ( ADDR_EEPROM_USER_START, ( uint8_t* ) pstPrjSaveVar, ( sizeof ( stProjectGlobalSaveVar_t ) - sizeof ( stPrjSpecVarVector_t ) ) );
		}

		if ( ( pstPrjSaveVar->stSaveSpecVar.pvSpecVar != NULL ) && ( pstPrjSaveVar->stSaveSpecVar.u16SpecVarSize != 0 ) )
		{
			//SpecificSaveVarDefault();

			if ( bDefaultSet )
			{
				dbg_printf ( "( ( uint8_t* ) (&pstPrjSaveVar->stSaveSpecVar ) - ( uint8_t* ) pstPrjSaveVar ):%d size:%d \r\n", ( ( uint8_t* ) (&pstPrjSaveVar->stSaveSpecVar ) - ( uint8_t* ) pstPrjSaveVar ),pstPrjSaveVar->stSaveSpecVar.u16SpecVarSize );
				dbg_printf ( "e2prom - step.3 write pstPrjSaveVar->stSaveSpecVar.pvSpecVar %s %d E2PROM PARAM Address:%d data:0x%04x len:%d \r\n",__FUNCTION__,__LINE__, ( ADDR_EEPROM_USER_START+ ( ( uint8_t* ) (&pstPrjSaveVar->stSaveSpecVar )- ( uint8_t* ) pstPrjSaveVar ) ),pstPrjSaveVar->stSaveSpecVar.pvSpecVar,pstPrjSaveVar->stSaveSpecVar.u16SpecVarSize );
				v_hexdump ( ( uint8_t* ) pstPrjSaveVar->stSaveSpecVar.pvSpecVar,pstPrjSaveVar->stSaveSpecVar.u16SpecVarSize );

				//写入特殊值
				eeprom_write ( ( ADDR_EEPROM_USER_START + ( ( uint8_t* ) (&pstPrjSaveVar->stSaveSpecVar ) - ( uint8_t* ) pstPrjSaveVar ) ), ( uint8_t* ) pstPrjSaveVar->stSaveSpecVar.pvSpecVar, pstPrjSaveVar->stSaveSpecVar.u16SpecVarSize );
			}
		}
	}
	else
	{
		eeprom_read ( ADDR_EEPROM_USER_START, ( uint8_t* ) pstPrjSaveVar, ( sizeof ( stProjectGlobalSaveVar_t ) - sizeof ( stPrjSpecVarVector_t ) ) );

#if 0

		//ir study key
#if ((_IR_FUNCTION_USE&_IR_FUNCTION_KEY_STUDY)==_IR_FUNCTION_KEY_STUDY)
		if (!mapp_UserDataIrStudyValCheck() )
		{
			bDefaultSet = TRUE;
		}
#endif

		//uart study key
#if _ENABLE_UART_LEARNING_MESSAGE_FUNCTION
		if (!mapp_UserDataUartKeyValCheck() )
		{
			bDefaultSet = TRUE;
		}
#endif

#endif

		//project name set
		if (!mapp_UserDataProjectNameCheck() )
		{
			bDefaultSet = TRUE;
		}

		//set to default value
		if ( bDefaultSet )
		{
			eeprom_write ( ADDR_EEPROM_USER_START, ( uint8_t* ) pstPrjSaveVar, ( sizeof ( stProjectGlobalSaveVar_t ) - sizeof ( stPrjSpecVarVector_t ) ) );
		}

		if ( ( pstPrjSaveVar->stSaveSpecVar.pvSpecVar != NULL ) && ( pstPrjSaveVar->stSaveSpecVar.u16SpecVarSize != 0 ) )
		{
			eeprom_read ( ( ADDR_EEPROM_USER_START + ( ( uint8_t* ) (&pstPrjSaveVar->stSaveSpecVar ) - ( uint8_t* ) pstPrjSaveVar ) ), ( uint8_t* ) pstPrjSaveVar->stSaveSpecVar.pvSpecVar, pstPrjSaveVar->stSaveSpecVar.u16SpecVarSize );

			if ( CheckSaveSpecVarValid() )
			{
				bDefaultSet = FALSE;
			}
			else
			{
				bDefaultSet = TRUE;
			}

			if ( bDefaultSet )
			{
				eeprom_write ( ( ADDR_EEPROM_USER_START + ( ( uint8_t* ) (&pstPrjSaveVar->stSaveSpecVar ) - ( uint8_t* ) pstPrjSaveVar ) ), ( uint8_t* ) pstPrjSaveVar->stSaveSpecVar.pvSpecVar, pstPrjSaveVar->stSaveSpecVar.u16SpecVarSize );
			}
		}

	}
}
#endif

// check eeprom save ok
bool mapp_CheckAllDataHasSave ( void )
{
#if _EN_MAIN_TASK_EEPROM
	pstEepDataSave_t pData1 = g_EepromDataSave, pData2;
	eEepDataIndex_t i;
	u8 l_u8SaveCnt = 0;

	dbg_printf ( "e2prom %s %d\r\n",__FUNCTION__,__LINE__ );

	for ( i= ( eEepDataIndex_t ) 1; i<eEepDataIndex_Max; i++ )
	{
		pData2 = pData1 + ( i-1 );

		if ( ( pData2->bEepSaveOkFlag != TRUE ) && ( pData2->pvBufferAdr!=NULL ) )
		{
			l_u8SaveCnt++;
		}
	}

	if ( l_u8SaveCnt != 0 )
	{
		return FALSE;
	}
	else
#endif
		return TRUE;

}

void app_UserDataToDefault ( void )
{
	pstProjectGlobalAllVar_t    pstPrjAllVar = &g_stPrjGloVar;
	pstProjectGlobalSaveVar_t   pstPrjSaveVar = &pstPrjAllVar->stPrjSaveVar;
	u8 l_u8Index;

	dbg_printf ( "e2prom - app_UserDataToDefault %s %d\r\n",__FUNCTION__,__LINE__ );

#if 0

#if ((_IR_FUNCTION_USE&_IR_FUNCTION_KEY_STUDY)==_IR_FUNCTION_KEY_STUDY)
	for ( l_u8Index=0; l_u8Index<_NUM_IR_STUDY_KEYS; l_u8Index++ )
	{
		mapp_UserDataIrStudyValInit ( l_u8Index );
	}
#endif //add by wf8421

#if _ENABLE_UART_LEARNING_MESSAGE_FUNCTION
	for ( l_u8Index=0; l_u8Index<_NUM_UART_STUDY_KEYS; l_u8Index++ )
	{
		mapp_UserDataUartKeyValInit ( l_u8Index );
	}
#endif

#endif
	mapp_UserDataProjectNameInit();                 //清空工程名

	if ( ( pstPrjSaveVar->stSaveSpecVar.pvSpecVar != NULL ) && ( pstPrjSaveVar->stSaveSpecVar.u16SpecVarSize != 0 ) )
	{
		SpecificSaveVarDefault();                 //保存默认的特殊变量
	}
	UNUSED ( l_u8Index );
}







