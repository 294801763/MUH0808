#include "includes.h"

#if (_ENABLE_CHIP_BP1048 == _MACRO_ENABLE)
#ifndef STK_SIZE_TASK_BP1048
#define STK_SIZE_TASK_BP1048                        2048
#endif
#ifndef PRIORITY_TASK_BP1048
#define PRIORITY_TASK_BP1048                        3
#endif
vvFuncPoint pvvFuncBP1048UserFunctionInit = NULL;
vvFuncPoint pvvFuncBP1048UserFunctionProcess = NULL;


#if _SYSTEM_SUPPORT_RTOS
void vTask_BP1048(void *pvParameters)
{
	(void)pvParameters;

    if(pvvFuncBP1048UserFunctionInit != NULL)
    {
        pvvFuncBP1048UserFunctionInit();
    }
  	/* Infinite loop */
  	for(;;)
  	{
            app_BP1048_process(1);

        if(pvvFuncBP1048UserFunctionProcess != NULL)
        {
            pvvFuncBP1048UserFunctionProcess();
        }
		vTaskDelay(10);
  	}
}
void vTaskCreate_BP1048(void)
{
    xTaskCreate( vTask_BP1048,
                 "vTask_BP1048",
                 STK_SIZE_TASK_BP1048,
                 NULL,
                 PRIORITY_TASK_BP1048,
                 NULL );
}
#endif


#endif

