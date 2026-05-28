#ifndef __BP1048_APP_C
#define __BP1048_APP_C
#include "includes.h"
#if (_ENABLE_CHIP_BP1048 == _MACRO_ENABLE)
#include "bp1048_app.h"

stBp1048FunctionEvent_t stBP1048Event;


u8 app_All_AudioOutput_Ctrl(u8 u8Dev,u8 *command)
{

	u8 ret = 0;
	BP1048_i2c_write(u8Dev, command);
	return ret;
}
u8 app_Input_Sensitivity(u8 u8Dev,u8 *command)
{
u8 ret = 0;
	BP1048_i2c_write(u8Dev, command);
	return ret;
}
u8 app_Input_Gain(u8 u8Dev,u8 *command)
{
 u8 ret = 0;
	BP1048_i2c_write(u8Dev, command);
	return ret;
}
u8 app_Input_Mute(u8 u8Dev,u8 *command)
{
	u8 ret = 0;
	BP1048_i2c_write(u8Dev, command);
	return ret;
}
u8 app_Input_Reverse_phase(u8 u8Dev,u8 *command)
{
	u8 ret = 0;
	BP1048_i2c_write(u8Dev, command);
	return ret;
}
u8 app_Input_TestSignal_Ctrl(u8 u8Dev,u8 *command)
{
	u8 ret = 0;
	BP1048_i2c_write(u8Dev, command);
	return ret;
}
u8 app_Input_TestSignal_Freq(u8 u8Dev,u8 *command)
{
 u8 ret = 0;
	BP1048_i2c_write(u8Dev, command);
	return ret;
}
u8 app_Input_TestSignal_Level(u8 u8Dev,u8 *command)
{
	u8 ret = 0;
	BP1048_i2c_write(u8Dev, command);
	return ret;
}
u8 app_Input_Compressor_Ctrl(u8 u8Dev,u8 *command)
{
 u8 ret = 0;
	BP1048_i2c_write(u8Dev, command);
	return ret;
}
u8 app_Input_Compressor_Gain(u8 u8Dev,u8 *command)
{
	u8 ret = 0;
	BP1048_i2c_write(u8Dev, command);
	return ret;
}
u8 app_Input_Compressor_Threshold(u8 u8Dev,u8 *command)
{
 u8 ret = 0;
	BP1048_i2c_write(u8Dev, command);
	return ret;
}
u8 app_Input_Compressor_Ratio(u8 u8Dev,u8 *command)
{
 u8 ret = 0;
	BP1048_i2c_write(u8Dev, command);
	return ret;
}
u8 app_Input_Compressor_StartTime(u8 u8Dev,u8 *command)
{
 u8 ret = 0;
	BP1048_i2c_write(u8Dev, command);
	return ret;
}
u8 app_Input_Compressor_ReleaseTime(u8 u8Dev,u8 *command)
{
	u8 ret = 0;
	BP1048_i2c_write(u8Dev, command);
	return ret;
}
u8 app_Input_AutoGain_Ctrl(u8 u8Dev,u8 *command)
{
 u8 ret = 0;
	BP1048_i2c_write(u8Dev, command);
	return ret;
}
u8 app_Input_AutoGain_Threshold(u8 u8Dev,u8 *command)
{
 u8 ret = 0;
	BP1048_i2c_write(u8Dev, command);
	return ret;
}
u8 app_Input_AutoGain_TargetThreshold(u8 u8Dev,u8 *command)
{
 u8 ret = 0;

	BP1048_i2c_write(u8Dev, command);
	return ret;
}
u8 app_Input_AutoGain_Ratio(u8 u8Dev,u8 *command)
{
 u8 ret = 0;

	BP1048_i2c_write(u8Dev, command);
	return ret;
}
u8 app_Input_AutoGain_StartTime(u8 u8Dev,u8 *command)
{
 u8 ret = 0;

	BP1048_i2c_write(u8Dev, command);
	return ret;
}
u8 app_Input_AutoGain_ReleaseTime(u8 u8Dev,u8 *command)
{
 u8 ret = 0;

	BP1048_i2c_write(u8Dev, command);
	return ret;
}
u8 app_Input_EQ_Type(u8 u8Dev,u8 *command)
{
 u8 ret = 0;

	BP1048_i2c_write(u8Dev, command);
	return ret;
}
u8 app_Input_EQ_Gain(u8 u8Dev,u8 *command)
{
 u8 ret = 0;

	BP1048_i2c_write(u8Dev, command);
	return ret;
}
u8 app_Input_EQ_QualityFactor(u8 u8Dev,u8 *command)
{
 u8 ret = 0;

	BP1048_i2c_write(u8Dev, command);
	return ret;
}
u8 app_Input_EQ_Ctrl(u8 u8Dev,u8 *command)
{
 u8 ret = 0;

	BP1048_i2c_write(u8Dev, command);
	return ret;
}
u8 app_Input_HowlingSuppressor_Ctrl(u8 u8Dev,u8 *command)
{
 u8 ret = 0;

	BP1048_i2c_write(u8Dev, command);
	return ret;
}
u8 app_Input_HowlingSuppressor_Grade(u8 u8Dev,u8 *command)
{
 u8 ret = 0;

	BP1048_i2c_write(u8Dev, command);
	return ret;
}
u8 app_Input_HowlingSuppressor_FreqShift(u8 u8Dev,u8 *command)
{
 u8 ret = 0;

	BP1048_i2c_write(u8Dev, command);
	return ret;
}
u8 app_Input_NoiseSuppressor_Grade(u8 u8Dev,u8 *command)
{
 u8 ret = 0;

	BP1048_i2c_write(u8Dev, command);
	return ret;
}
u8 app_Input_NoiseSuppressor_Threshold(u8 u8Dev,u8 *command)
{
 u8 ret = 0;

	BP1048_i2c_write(u8Dev, command);
	return ret;
}
u8 app_Input_NoiseSuppressor_Ratio(u8 u8Dev,u8 *command)
{
 u8 ret = 0;

	BP1048_i2c_write(u8Dev, command);
	return ret;
}
u8 app_Input_NoiseSuppressor_StartTime(u8 u8Dev,u8 *command)
{
 u8 ret = 0;

	BP1048_i2c_write(u8Dev, command);
	return ret;
}
u8 app_Input_NoiseSuppressor_ReleaseTime(u8 u8Dev,u8 *command)
{
 u8 ret = 0;

	BP1048_i2c_write(u8Dev, command);
	return ret;
}
u8 app_Input_NoiseSuppressor_Ctrl(u8 u8Dev,u8 *command)
{
 u8 ret = 0;

	BP1048_i2c_write(u8Dev, command);
	return ret;
}
u8 app_Input_EchoCanceller_Ctrl(u8 u8Dev,u8 *command)
{
 u8 ret = 0;

	BP1048_i2c_write(u8Dev, command);
	return ret;
}
u8 app_Input_EchoCanceller_Grade(u8 u8Dev,u8 *command)
{
 u8 ret = 0;

	BP1048_i2c_write(u8Dev, command);
	return ret;
}
u8 app_Input_Exciter_Ctrl(u8 u8Dev,u8 *command)
{
 u8 ret = 0;

	BP1048_i2c_write(u8Dev, command);
	return ret;
}
u8 app_Input_HfreqExciter_Grade(u8 u8Dev,u8 *command)
{
 u8 ret = 0;

	BP1048_i2c_write(u8Dev, command);
	return ret;
}
u8 app_Input_LfreqExciter_Grade(u8 u8Dev,u8 *command)
{
 u8 ret = 0;

	BP1048_i2c_write(u8Dev, command);
	return ret;
}
u8 app_Input_CallInput(u8 u8Dev,u8 *command)
{
 u8 ret = 0;

	BP1048_i2c_write(u8Dev, command);
	return ret;
}
u8 app_Input_BackgroundInput(u8 u8Dev,u8 *command)
{
 u8 ret = 0;

	BP1048_i2c_write(u8Dev, command);
	return ret;
}
u8 app_Input_Ducking_Gain(u8 u8Dev,u8 *command)
{
 u8 ret = 0;

	BP1048_i2c_write(u8Dev, command);
	return ret;
}
u8 app_Input_Ducking_Threshold(u8 u8Dev,u8 *command)
{
 u8 ret = 0;

	BP1048_i2c_write(u8Dev, command);
	return ret;
}
u8 app_Input_Ducking_Depth(u8 u8Dev,u8 *command)
{
 u8 ret = 0;

	BP1048_i2c_write(u8Dev, command);
	return ret;
}
u8 app_Input_Ducking_StartTime(u8 u8Dev,u8 *command)
{
 u8 ret = 0;

	BP1048_i2c_write(u8Dev, command);
	return ret;
}
u8 app_Input_Ducking_HoldTime(u8 u8Dev,u8 *command)
{
 u8 ret = 0;

	BP1048_i2c_write(u8Dev, command);
	return ret;
}
u8 app_Input_Ducking_ReleaseTime(u8 u8Dev,u8 *command)
{
 u8 ret = 0;

	BP1048_i2c_write(u8Dev, command);
	return ret;
}
u8 app_Input_Ducking_Ctrl(u8 u8Dev,u8 *command)
{
 u8 ret = 0;

	BP1048_i2c_write(u8Dev, command);
	return ret;
}
u8 app_MatrixSwitching(u8 u8Dev,u8 *command)
{
 u8 ret = 0;

	BP1048_i2c_write(u8Dev, command);
	return ret;
}
u8 app_Output_DelayTime(u8 u8Dev,u8 *command)
{
 u8 ret = 0;

	BP1048_i2c_write(u8Dev, command);
	return ret;
}
u8 app_Output_Delay_Ctrl(u8 u8Dev,u8 *command)
{
 u8 ret = 0;

	BP1048_i2c_write(u8Dev, command);
	return ret;
}
u8 app_USBplayer_Ctrl(u8 u8Dev,u8 *command)
{
 u8 ret = 0;

	BP1048_i2c_write(u8Dev, command);
	return ret;
}
void app_BP1048_process(u8 dev)
{

	if(stBP1048Event.bAllAudioOutputChangeFlag)
	{
		stBP1048Event.bAllAudioOutputChangeFlag = FALSE;
		app_All_AudioOutput_Ctrl(dev, &stBP1048Event.u8AllAudioOutput);
	}
	for(u8 i =0; i<Def_inport_num; i++)
	{
		if(stBP1048Event.bSensitivityChangeFlag[i])
		{
			stBP1048Event.bSensitivityChangeFlag[i] = FALSE;
			app_All_AudioOutput_Ctrl(dev, stBP1048Event.u8Sensitivity[i]);
		}
		if(stBP1048Event.bInputGainChangeFlag[i])
		{
			stBP1048Event.bSensitivityChangeFlag[i] = FALSE;
			app_All_AudioOutput_Ctrl(dev, stBP1048Event.u8Sensitivity[i]);
		}
		if(stBP1048Event.bInputMuteChangeFlag[i])
		{
			stBP1048Event.bInputMuteChangeFlag[i] = FALSE;
			app_All_AudioOutput_Ctrl(dev, stBP1048Event.u8InputMute[i]);
		}
		if(stBP1048Event.bReversePhaseChangeFlag[i])
		{
			stBP1048Event.bReversePhaseChangeFlag[i] = FALSE;
			app_All_AudioOutput_Ctrl(dev, stBP1048Event.u8ReversePhase[i]);
		}
		if(stBP1048Event.bTestSignalCtrlChangeFlag[i])
		{
			stBP1048Event.bTestSignalCtrlChangeFlag[i] = FALSE;
			app_All_AudioOutput_Ctrl(dev, stBP1048Event.u8TestSignalCtrl[i]);
		}
		if(stBP1048Event.bTestSignalFreqChangeFlag[i])
		{
			stBP1048Event.bTestSignalFreqChangeFlag[i] = FALSE;
			app_All_AudioOutput_Ctrl(dev, stBP1048Event.u8TestSignalFreq[i]);
		}
		if(stBP1048Event.bTestSignalLevelChangeFlag[i])
		{
			stBP1048Event.bTestSignalLevelChangeFlag[i] = FALSE;
			app_All_AudioOutput_Ctrl(dev, stBP1048Event.u8TestSignalLevel[i]);
		}
		if(stBP1048Event.bCompressorCtrlChangeFlag[i])
		{
			stBP1048Event.bCompressorCtrlChangeFlag[i] = FALSE;
			app_All_AudioOutput_Ctrl(dev, stBP1048Event.u8CompressorCtrl[i]);
		}
		if(stBP1048Event.bCompressorGainChangeFlag[i])
		{
			stBP1048Event.bCompressorGainChangeFlag[i] = FALSE;
			app_All_AudioOutput_Ctrl(dev, stBP1048Event.u8CompressorGain[i]);
		}
		if(stBP1048Event.bCompressorThresholdChangeFlag[i])
		{
			stBP1048Event.bCompressorThresholdChangeFlag[i] = FALSE;
			app_All_AudioOutput_Ctrl(dev, stBP1048Event.u8CompressorThreshold[i]);
		}
		if(stBP1048Event.bCompressorRatioChangeFlag[i])
		{
			stBP1048Event.bCompressorRatioChangeFlag[i] = FALSE;
			app_All_AudioOutput_Ctrl(dev, stBP1048Event.u8CompressorRatio[i]);
		}
		if(stBP1048Event.bCompressorStartTimeChangeFlag[i])
		{
			stBP1048Event.bCompressorStartTimeChangeFlag[i] = FALSE;
			app_All_AudioOutput_Ctrl(dev, stBP1048Event.u8CompressorStartTime[i]);
		}
		if(stBP1048Event.bCompressorReleaseTimeChangeFlag[i])
		{
			stBP1048Event.bCompressorReleaseTimeChangeFlag[i] = FALSE;
			app_All_AudioOutput_Ctrl(dev, stBP1048Event.u8CompressorReleaseTime[i]);
		}
		if(stBP1048Event.bAutoGainCtrlChangeFlag[i])
		{
			stBP1048Event.bAutoGainCtrlChangeFlag[i] = FALSE;
			app_All_AudioOutput_Ctrl(dev, stBP1048Event.u8AutoGainCtrl[i]);
		}
		if(stBP1048Event.bAutoGainThresholdChangeFlag[i])
		{
			stBP1048Event.bAutoGainThresholdChangeFlag[i] = FALSE;
			app_All_AudioOutput_Ctrl(dev, stBP1048Event.u8AutoGainThreshold[i]);
		}
		if(stBP1048Event.bAutoGainTargetThresholdChangeFlag[i])
		{
			stBP1048Event.bAutoGainTargetThresholdChangeFlag[i] = FALSE;
			app_All_AudioOutput_Ctrl(dev, stBP1048Event.u8AutoGainTargetThreshold[i]);
		}
		if(stBP1048Event.bAutoGainStartTimeChangeFlag[i])
		{
			stBP1048Event.bAutoGainStartTimeChangeFlag[i] = FALSE;
			app_All_AudioOutput_Ctrl(dev, stBP1048Event.u8AutoGainStartTime[i]);
		}
		if(stBP1048Event.bAutoGainReleaseTimeChangeFlag[i])
		{
			stBP1048Event.bAutoGainReleaseTimeChangeFlag[i] = FALSE;
			app_All_AudioOutput_Ctrl(dev, stBP1048Event.u8AutoGainReleaseTime[i]);
		}
		if(stBP1048Event.bEQTypeChangeFlag[i])
		{
			stBP1048Event.bEQTypeChangeFlag[i] = FALSE;
			app_All_AudioOutput_Ctrl(dev, stBP1048Event.u8EQType[i]);
		}
		if(stBP1048Event.bEQGainChangeFlag[i])
		{
			stBP1048Event.bEQGainChangeFlag[i] = FALSE;
			app_All_AudioOutput_Ctrl(dev, stBP1048Event.u8EQGain[i]);
		}
		if(stBP1048Event.bEQQualityFactorChangeFlag[i])
		{
			stBP1048Event.bEQQualityFactorChangeFlag[i] = FALSE;
			app_All_AudioOutput_Ctrl(dev, stBP1048Event.u8EQQualityFactor[i]);
		}
		if(stBP1048Event.bEQCtrlChangeFlag[i])
		{
			stBP1048Event.bEQCtrlChangeFlag[i] = FALSE;
			app_All_AudioOutput_Ctrl(dev, stBP1048Event.u8EQCtrl[i]);
		}
		if(stBP1048Event.bInputMuteChangeFlag[i])
		{
			stBP1048Event.bInputMuteChangeFlag[i] = FALSE;
			app_All_AudioOutput_Ctrl(dev, stBP1048Event.u8InputMute[i]);
		}
		if(stBP1048Event.bInputMuteChangeFlag[i])
		{
			stBP1048Event.bInputMuteChangeFlag[i] = FALSE;
			app_All_AudioOutput_Ctrl(dev, stBP1048Event.u8InputMute[i]);
		}
		if(stBP1048Event.bInputMuteChangeFlag[i])
		{
			stBP1048Event.bInputMuteChangeFlag[i] = FALSE;
			app_All_AudioOutput_Ctrl(dev, stBP1048Event.u8InputMute[i]);
		}
		if(stBP1048Event.bInputMuteChangeFlag[i])
		{
			stBP1048Event.bInputMuteChangeFlag[i] = FALSE;
			app_All_AudioOutput_Ctrl(dev, stBP1048Event.u8InputMute[i]);
		}
		if(stBP1048Event.bInputMuteChangeFlag[i])
		{
			stBP1048Event.bInputMuteChangeFlag[i] = FALSE;
			app_All_AudioOutput_Ctrl(dev, stBP1048Event.u8InputMute[i]);
		}
	}
}



#endif
#endif

