#ifndef INPUT_H
#define INPUT_H

#include "engine/core.h"

#define KEYBOARD_KEY_MAX 256
#define MOUSE_BOTTONS_MAX 5

void Input_Init();
void Input_ProcessKey(SDL_KeyboardEvent* key);
void Input_ProcessMouseButton(SDL_MouseButtonEvent* button);
void Input_ProcessMouseMotion(SDL_MouseMotionEvent* motion);
void Input_Cleanup();

b8 Input_IsKeyDown(SDL_Scancode c);
b8 Input_IsKeyUp(SDL_Scancode c);

//b8 Input_WasKeyDown(SDL_Scancode c);
//b8 Input_WasKeyUp(SDL_Scancode c);

#endif