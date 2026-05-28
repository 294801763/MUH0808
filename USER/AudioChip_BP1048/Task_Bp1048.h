#ifndef __TASK_BP1048_H_
#define __TASK_BP1048_H_

#if (_ENABLE_CHIP_BP1048 == _MACRO_ENABLE)
#include "bp1048_app.h"

typedef struct _stBP1048Config_T_
{
    u8 u8I2cIndex;
    u8 u8WorkMode;
}stMS1826Config_T;

extern vvFuncPoint      pvvFuncBP1048UserFunctionInit;
extern vvFuncPoint      pvvFuncBP1048UserFunctionProcess;

void vTask_BP1048(void *pvParameters);
void vTaskCreate_BP1048(void);

#endif

#endif

