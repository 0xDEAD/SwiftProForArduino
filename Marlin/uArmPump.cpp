/**
  ******************************************************************************
  * @file	uArmPump.cpp
  * @author	David.Long	
  * @email	xiaokun.long@ufactory.cc
  * @date	2017-05-25
  ******************************************************************************
  */

#include "uArmPump.h" 

#define VALVE_ON_TIMES_MAX	10

pump_state_t pump_state = PUMP_STATE_OFF;


void pump_set_state(pump_state_t state)
{
	if (state >= PUMP_STATE_COUNT)
		return;
	
	pump_state = state;
}

void pump_run()
{
	static uint8_t valve_on_times = 0;

	
	switch (pump_state)
	{
	case PUMP_STATE_OFF:
		valve_on_times = 0;
		break;
		
	case PUMP_STATE_ON:
		valve_on_times = 0;
		break;
	
	case PUMP_STATE_VALVE_ON:
		valve_on_times++;
		digitalWrite(VALVE_EN, HIGH);
		if (valve_on_times >= VALVE_ON_TIMES_MAX)
		{
			valve_on_times = 0;
			pump_state = PUMP_STATE_OFF;
		}
		else
		{		
			pump_state = PUMP_STATE_VALVE_OFF;
		}
		break;		
		
	case PUMP_STATE_VALVE_OFF:
		digitalWrite(VALVE_EN, LOW); 
		pump_state = PUMP_STATE_VALVE_ON;
		
		break;
		

	}
}