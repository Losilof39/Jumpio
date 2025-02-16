#ifndef PONG_H
#define PONG_H

#include "engine/data_types.h"
#include "engine/engine.h"

typedef struct Object
{
    vec3 pos;
    vec2 size;
    vec3 col;
    vec2 vel;
    i8 dir;
}Object;

void Test_Init();
void Test_Update();
void Test_Cleanup();

void Test_Menu();
void Test_Active(f32 delta);
void Test_RestartRound();

b8 Collision(Object* a, Object* b);

#endif