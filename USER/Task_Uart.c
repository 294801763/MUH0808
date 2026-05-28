#include "includes.h"

extern const stUartDeclare_t stProjectUartWorkTable[];

#if 1
char json_1[100]="{\"All_AudioOutput\":{\"switch\":0}}";
char json_2[100]="{\"SET_Input_Sensitivity\":{\"0\":{\"aisle\":0,\"sensitivity\":0},\"cnt\":1}}";
#endif

//测试json解析,添加一项
void tst_json_v1_0()
{
	json_t *all_audio_output = NULL;
	json_t *item = NULL;

	all_audio_output = json_object();
	item = json_object();

	char *str = NULL;

	json_object_set_new(item,"switch",json_string("0"));
	json_object_set_new(all_audio_output,"All_AudioOutput",item);

	str = json_dumps(all_audio_output,JSON_INDENT(0));
	dbg_printf("json dump %s:%s\r\n",__FUNCTION__,str); // {"All_AudioOutput": {"switch": "0"}}
	free(str);
	json_decref(all_audio_output);
}

//添加两项
void tst_json_v1_1()
{
	json_t *input_sensitivity = NULL;
	json_t *item = NULL;

	input_sensitivity = json_object();
	item = json_object();

	char *str = NULL;

	json_object_set_new(item,"aisle",json_integer(0));
	json_object_set_new(item,"sensitivity",json_integer(0));
	json_object_set_new(input_sensitivity,"SET_Input_Sensitivity",item);

	str = json_dumps(input_sensitivity,JSON_INDENT(0));
	dbg_printf("json dump %s:%s\r\n",__FUNCTION__,str); //json dump tst_json_v1_1:{"SET_Input_Sensitivity": {"aisle": 0, "sensitivity": 0}}
	free(str);
	json_decref(input_sensitivity);
}

//数组
void tst_json_v1_2()
{
	json_t *input_sensitivity = NULL;
	json_t *array = NULL;
	json_t *item = NULL;

	input_sensitivity = json_object();
	array = json_array();
	item = json_object();
	
	char *str = NULL;

	json_object_set_new(item,"aisle",json_integer(0));
	json_object_set_new(item,"sensitivity",json_integer(0));
	json_array_append_new(array,item);

	json_object_set_new(item,"aisle",json_integer(1));
	json_object_set_new(item,"sensitivity",json_integer(0));
	json_array_append_new(array,item);
	
	json_object_set_new(input_sensitivity,"SET_Input_Sensitivity",array);

	str = json_dumps(input_sensitivity,JSON_INDENT(0));
	dbg_printf("json dump %s:%s\r\n",__FUNCTION__,str); //json dump tst_json_v1_2:{"SET_Input_Sensitivity": [{"aisle": 1, "sensitivity": 0}, {"aisle": 1, "sensitivity": 0}]}
	free(str);
	json_decref(input_sensitivity);
}

//加载json字符串
void tst_json_v1_3()
{
	json_error_t err;

	json_t *root = json_loads(json_1,strlen(json_1),&err);
	if(NULL != root && json_is_object(root))
	{
		json_t *All_AudioOutput = json_object_get(root,"All_AudioOutput");
		if(NULL != All_AudioOutput && json_is_object(All_AudioOutput))
		{
			char *str = json_dumps(All_AudioOutput,JSON_INDENT(0));
			dbg_printf("json dump %s:%s\r\n",__FUNCTION__,str);
			free(str);
		}

		if(NULL != All_AudioOutput && json_is_real(All_AudioOutput))
		{

		}
	}

	json_decref(root);
}

//加载json字符串
void tst_json_v1_4()
{
	json_error_t err;

	json_t *root = json_loads(json_2,strlen(json_1),&err);
	if(NULL != root && json_is_object(root))
	{
		json_t *input_sensitivity = json_object_get(root,"SET_Input_Sensitivity");
		if(NULL != input_sensitivity && json_is_object(input_sensitivity))
		{
			char *str = json_dumps(input_sensitivity,JSON_INDENT(0));
			dbg_printf("json dump %s:%s\r\n",__FUNCTION__,str);
			free(str);
		}

		if(NULL != input_sensitivity && json_is_real(input_sensitivity))
		{

		}
	}

	json_decref(root);
}


#if _SYSTEM_SUPPORT_RTOS
void vTaskUart(void *pvParameters)
{
	pstUartDeclare_t	pstUart, pstUartOrg = (pstUartDeclare_t)&stProjectUartWorkTable[0];

	(void)pvParameters;
    
    #if 0
	dbg_printf("%s\r\n",json_1);
    dbg_printf("%s\r\n",json_2);
    #endif

	//测试json解析
	#if 0
	tst_json_v1_0();
	tst_json_v1_1();
	tst_json_v1_2();
	tst_json_v1_3();
	tst_json_v1_4();
	#endif
	
	for(;;)
	{
		pstUart = pstUartOrg;

		while(pstUart->u8UartPort != _UART_PORT_NONE)
		{
			if(pstUart->funUartParser != NULL)
			{
				pstUart->funUartParser();
			}
			pstUart ++;
		}

		vTaskDelay(10);
	}
}
#else
void vTaskUart(void *pvParameters)
{
	pstUartDeclare_t	pstUart, pstUartOrg = (pstUartDeclare_t)&stProjectUartWorkTable[0];

	(void)pvParameters;

	pstUart = pstUartOrg;

	while(pstUart->u8UartPort != _UART_PORT_NONE)
	{
		if(pstUart->funUartParser != NULL)
		{
			pstUart->funUartParser();
		}
		pstUart ++;
	}
}

#endif

void drv_UartTaskInit(void)
{
	pstUartDeclare_t 	pstUart = (pstUartDeclare_t)&stProjectUartWorkTable[0];

	while(pstUart->u8UartPort != _UART_PORT_NONE)
	{
		if(pstUart->funUartVarInit != NULL)
		{
			pstUart->funUartVarInit();
		}
		USARTx_Configuration(pstUart);

		pstUart ++;
	}
}










