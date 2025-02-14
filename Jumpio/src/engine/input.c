#include "input.h"
#include "engine/core.h"

typedef struct KeyboardState
{
	b8 keys[256];
}KeyboardState;

typedef struct MouseState
{
	i16 x;
	i16 y;
	b8 buttons[MOUSE_BOTTONS_MAX];
}MouseState;

void Input_Init()
{
}

void Input_Update()
{
}

void Input_Cleanup()
{
}

void Input_IsKeyDown()
{
}

void Input_IsKeyUp()
{
}

void Input_WasKeyDown()
{
}

void Input_WasKeyUp()
{
}