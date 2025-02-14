#include "input.h"

typedef struct KeyboardState
{
	b8 keys[KEYBOARD_KEY_MAX];
}KeyboardState;

typedef struct MouseState
{
	i16 x;
	i16 y;
	i16 xrel;
	i16 yrel;
	b8 buttons[MOUSE_BOTTONS_MAX];
}MouseState;

typedef struct InputState
{
	KeyboardState prevKeyboard;
	KeyboardState curKeyboard;

	MouseState prevMouse;
	MouseState curMouse;
}InputState;

static InputState* input;

void Input_Init()
{
	input = (InputState*)malloc(sizeof(InputState));
	memset(input, 0, sizeof(InputState));
}

void Input_ProcessKey(SDL_KeyboardEvent* key)
{
	SDL_Scancode c;
	b8 down;

	c = key->scancode;
	down = key->down;

	input->prevKeyboard.keys[c] = input->curKeyboard.keys[c];

	input->curKeyboard.keys[c] = down;
}

void Input_ProcessMouseButton(SDL_MouseButtonEvent* button)
{
	i16 b;
	b8 down;

	b = button->button;
	down = button->down;

	input->prevMouse.buttons[b] = input->curMouse.buttons[b];

	input->curMouse.buttons[b] = down;
}

void Input_ProcessMouseMotion(SDL_MouseMotionEvent* motion)
{
	input->curMouse.x = (i16)motion->x;
	input->curMouse.y = (i16)motion->y;

	input->curMouse.xrel = (i16)motion->xrel;
	input->curMouse.yrel = (i16)motion->yrel;
}

void Input_Cleanup()
{
	free(input);
}

b8 Input_IsKeyDown(SDL_Scancode c)
{
	if (input == NULL)
		return false;

	return input->curKeyboard.keys[c];
}

b8 Input_IsKeyUp(SDL_Scancode c)
{
	if (input == NULL)
		return true;

	return !input->curKeyboard.keys[c];
}

b8 Input_IsButtonDown(u8 button)
{
	if (input == NULL)
		return false;

	return input->curMouse.buttons[button];
}

b8 Input_IsButtonUp(u8 button)
{
	if (input == NULL)
		return true;

	return !input->curMouse.buttons[button];
}

i16 Input_GetMouseX()
{
	return input->curMouse.x;
}

i16 Input_GetMouseY()
{
	return input->curMouse.y;
}

//b8 Input_WasKeyDown(SDL_Scancode c)
//{
//}
//
//b8 Input_WasKeyUp(SDL_Scancode c)
//{
//}