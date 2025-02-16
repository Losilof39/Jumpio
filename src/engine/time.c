#include "data_types.h"

f32 deltaTime;

void Time_SetDeltaTime(f32 delta)
{
	deltaTime = delta;
}

f32 Time_GetDeltaTime()
{
	return deltaTime;
}