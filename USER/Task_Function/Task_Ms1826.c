#include "includes.h"

#if (_ENABLE_CHIP_MS1826 == _MACRO_ENABLE)
#include "ms1826_videoprocess.h"

#ifndef STK_SIZE_TASK_MS1826
#define STK_SIZE_TASK_MS1826                        2048
#endif
#ifndef PRIORITY_TASK_MS1826
#define PRIORITY_TASK_MS1826                        3
#endif

vvFuncPoint pvvFuncMS1826UserFunctionInit = NULL;
vvFuncPoint pvvFuncMS1826UserFunctionProcess = NULL;
static bool sg_bMS1826HoldFlag = FALSE;

const stMS1826Config_T cg_stMs1826DevCfgTable[] =
{
    {_I2C_TABLE_INDEX_MS1826_0,_MS1826_WORK_MODE_0},
#if (DEV_NUM_MS1826>1)
    {_I2C_TABLE_INDEX_MS1826_1,_MS1826_WORK_MODE_1},
#endif
#if (DEV_NUM_MS1826>2)
    {_I2C_TABLE_INDEX_MS1826_2,_MS1826_WORK_MODE_2},
#endif
#if (DEV_NUM_MS1826>3)
    {_I2C_TABLE_INDEX_MS1826_3,_MS1826_WORK_MODE_3},
#endif
#if (DEV_NUM_MS1826>4)
    {_I2C_TABLE_INDEX_MS1826_4,_MS1826_WORK_MODE_4},
#endif
#if (DEV_NUM_MS1826>5)
    {_I2C_TABLE_INDEX_MS1826_5,_MS1826_WORK_MODE_5},
#endif
};

/* Function prototypes -------------------------------------------------------*/
extern void MS1826_SystemReset(void);
extern void ms1826_startup_timer_counter(UINT8 u8Dev);

void app_MS18261MsTimerTask(void)
{
    u8 u8DevId;
    for(u8DevId=0;u8DevId<DEV_NUM_MS1826;u8DevId++)
    {
        app_MS1826SwFreezeTimer(u8DevId);
        ms1826_startup_timer_counter(u8DevId);
    }
}

void app_MS1826SetHoldFlag(bool bEn)
{
    sg_bMS1826HoldFlag = bEn;
}

bool app_MS1826HoldSystem(void)
{
    return sg_bMS1826HoldFlag;
}

#if _SYSTEM_SUPPORT_RTOS
void vTask_Ms1826(void *pvParameters)
{
    u8 l_u8OsdTimer = 0;
	(void)pvParameters;
    MS1826_SystemReset();

    for(g_u8MS1826DevIndex=0;g_u8MS1826DevIndex<DEV_NUM_MS1826;g_u8MS1826DevIndex++)
    {
        g_u8MS1826_I2CDevID = (u8)cg_stMs1826DevCfgTable[g_u8MS1826DevIndex].u8I2cIndex;
        app_ms1826_variable_init(g_u8MS1826DevIndex,cg_stMs1826DevCfgTable[g_u8MS1826DevIndex].u8WorkMode);
        video_process_init(g_u8MS1826DevIndex);
    }

    if(pvvFuncMS1826UserFunctionInit != NULL)
    {
        pvvFuncMS1826UserFunctionInit();
    }
  	/* Infinite loop */
  	for(;;)
  	{
        if(app_MS1826HoldSystem())
        {
            vTaskDelay(10);
            continue;
        }

        for(g_u8MS1826DevIndex=0;g_u8MS1826DevIndex<DEV_NUM_MS1826;g_u8MS1826DevIndex++)
        {
            g_u8MS1826_I2CDevID = (u8)cg_stMs1826DevCfgTable[g_u8MS1826DevIndex].u8I2cIndex;
            if(app_MS1826GetStandby(g_u8MS1826DevIndex))
            {
                app_MS1826StandbyProcess(g_u8MS1826DevIndex);
                continue;
            }
            video_process(g_u8MS1826DevIndex);
            app_MS1826FunctionProcess(g_u8MS1826DevIndex);
            if(l_u8OsdTimer++>50)
            {
                osd_service(g_u8MS1826DevIndex);
                l_u8OsdTimer = 0;
            }
            app_MS1826StandbyProcess(g_u8MS1826DevIndex);
            vTaskDelay(1);
        }

        if(pvvFuncMS1826UserFunctionProcess != NULL)
        {
            pvvFuncMS1826UserFunctionProcess();
        }
		vTaskDelay(10);
  	}
}
void vTaskCreate_MS1826(void)
{
    xTaskCreate( vTask_Ms1826,
                 "vTask_Ms1826",
                 STK_SIZE_TASK_MS1826,
                 NULL,
                 PRIORITY_TASK_MS1826,
                 NULL );
}

#else
void vTask_Ms1826(void *pvParameters)
{
    static u8 sl_u8OsdTimer = 0;
    static u8 sl_u8LoopStatus = 0;
	(void)pvParameters;
  	/* Infinite loop */

    switch(sl_u8LoopStatus)
    {
        default:
        case 0:
            {
                MS1826_SystemReset();

                for(g_u8MS1826DevIndex=0;g_u8MS1826DevIndex<DEV_NUM_MS1826;g_u8MS1826DevIndex++)
                {
                    g_u8MS1826_I2CDevID = (u8)cg_stMs1826DevCfgTable[g_u8MS1826DevIndex].u8I2cIndex;
                    app_ms1826_variable_init(g_u8MS1826DevIndex,cg_stMs1826DevCfgTable[g_u8MS1826DevIndex].u8WorkMode);
                    video_process_init(g_u8MS1826DevIndex);
                }

                if(pvvFuncMS1826UserFunctionInit != NULL)
                {
                    pvvFuncMS1826UserFunctionInit();
                }
                sl_u8LoopStatus=1;
            }
            break;
        case 1:
            {
                if(app_MS1826HoldSystem())
                {
                    break;
                }

                for(g_u8MS1826DevIndex=0;g_u8MS1826DevIndex<DEV_NUM_MS1826;g_u8MS1826DevIndex++)
                {
                    g_u8MS1826_I2CDevID = (u8)cg_stMs1826DevCfgTable[g_u8MS1826DevIndex].u8I2cIndex;
                    video_process(g_u8MS1826DevIndex);
                    app_MS1826FunctionProcess(g_u8MS1826DevIndex);
                    if(sl_u8OsdTimer++>50)
                    {
                        osd_service(g_u8MS1826DevIndex);
                        sl_u8OsdTimer = 0;
                    }
                }

                if(pvvFuncMS1826UserFunctionProcess != NULL)
                {
                    pvvFuncMS1826UserFunctionProcess();
                }
            }
            break;
  	}
}
#endif


#endif  // #if (INC_TASK_VIDEOCHIP1 == _MACRO_ENABLE)























