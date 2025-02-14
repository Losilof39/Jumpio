#ifndef INPUT_H
#define INPUT_H

#define MOUSE_BOTTONS_MAX 5

void Input_Init();
void Input_Update();
void Input_Cleanup();

void Input_IsKeyDown();
void Input_IsKeyUp();

void Input_WasKeyDown();
void Input_WasKeyUp();

#endif