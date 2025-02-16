#ifndef INPUT_H
#define INPUT_H

#include <SDL3/SDL.h>
#include "data_types.h"

#define KEYBOARD_KEY_MAX 256
#define MOUSE_BOTTONS_MAX 5

void Input_Init();
void Input_Cleanup();

void Input_ProcessKey(SDL_KeyboardEvent* key);
void Input_ProcessMouseButton(SDL_MouseButtonEvent* button);
void Input_ProcessMouseMotion(SDL_MouseMotionEvent* motion);

b8 Input_IsKeyDown(SDL_Scancode c);
b8 Input_IsKeyUp(SDL_Scancode c);

b8 Input_WasKeyDown(SDL_Scancode c);
b8 Input_WasKeyUp(SDL_Scancode c);

b8 Input_IsButtonDown(u8 button);
b8 Input_IsButtonUp(u8 button);

i16 Input_GetMouseX();
i16 Input_GetMouseY();



#endif