#include "pong.h"

enum GameState { G_MENU = 0, G_ACTIVE, G_ENDGAME, G_EXIT };

Object padLeft  = { 0 };
Object padRight = { 0 };
Object ball     = { 0 };

enum GameState gState = G_MENU;
Mix_Chunk* bounce1;
Mix_Chunk* bounce2;

u8 scorePlayer1 = 0;
u8 scorePlayer2 = 0;

vec3 pos = { 0 };

b8 Collision(Object* a, Object* b)
{
    if (a->pos[0] < b->pos[0] + b->size[0] &&
        a->pos[0] + a->size[0] > b->pos[0] &&
        a->pos[1] < b->pos[1] + b->size[1] &&
        a->pos[1] + a->size[1] > b->pos[1])
    {
        return true;
    }

    return false;
}

void Test_Menu()
{
    if (Input_IsKeyDown(SDL_SCANCODE_SPACE))
    {
        gState = G_ACTIVE;
        Audio_PlaySound(bounce2, false);
    }

    R2D_DrawText("Press SPACEBAR to play", WINDOW_WIDTH - 550, WINDOW_HEIGHT - 48, 0.4f, (vec3){1.0f, 1.0f, 1.0f});
}

void Test_Active(f32 delta)
{

    padLeft.pos[1] += delta * Input_IsKeyDown(SDL_SCANCODE_S) * 500.0f;
    padLeft.pos[1] -= delta * Input_IsKeyDown(SDL_SCANCODE_W) * 500.0f;

    padRight.pos[1] += delta * Input_IsKeyDown(SDL_SCANCODE_DOWN) * 500.0f;
    padRight.pos[1] -= delta * Input_IsKeyDown(SDL_SCANCODE_UP) * 500.0f;

    if (padLeft.pos[1] < 0.0f)
        padLeft.pos[1] = 0.0f;

    if (padRight.pos[1] < 0.0f)
        padRight.pos[1] = 0.0f;

    if ((padLeft.pos[1] + padLeft.size[1]) > WINDOW_HEIGHT)
    {
        padLeft.pos[1] = WINDOW_HEIGHT - padLeft.size[1];
    }

    if ((padRight.pos[1] + padRight.size[1]) > WINDOW_HEIGHT)
    {
        padRight.pos[1] = WINDOW_HEIGHT - padRight.size[1];
    }

    if (ball.pos[1] > (WINDOW_HEIGHT - ball.size[0]))
    {
        ball.vel[1] = -10;
        Audio_PlaySound(bounce1, false);
    }

    if (ball.pos[1] < 0)
    {
        ball.vel[1] = 10;
        Audio_PlaySound(bounce1, false);
    }

    if (Collision(&padRight, &ball))
    {
        ball.vel[0] = -10;
        Audio_PlaySound(bounce1, false);
    }

    if (Collision(&padLeft, &ball))
    { 
        ball.vel[0] = 10;
        Audio_PlaySound(bounce1, false);
    }

    ball.pos[0] += ball.vel[0] * delta * 20.0f;
    ball.pos[1] += ball.vel[1] * delta * 20.0f;

    if (ball.pos[0] < padLeft.pos[0])
    {
        gState = G_MENU;
        scorePlayer2++;
        Audio_PlaySound(bounce2, false);
    }

    if (ball.pos[0] > padRight.pos[0])
    {
        gState = G_MENU;
        scorePlayer1++;
        Audio_PlaySound(bounce2, false);
    }

    if (scorePlayer1 == 3 || scorePlayer2 == 3)
    {
        if (scorePlayer1 > scorePlayer2)
        {
            R2D_DrawText("PLAYER 1 WINS", WINDOW_WIDTH / 4, WINDOW_HEIGHT / 2, 0.5f, (vec3) { 1.0f, 1.0f, 1.0f });
        }
        else
        {
            R2D_DrawText("PLAYER 2 WINS", WINDOW_WIDTH / 4, WINDOW_HEIGHT / 2 - 40, 0.5f, (vec3) { 1.0f, 1.0f, 1.0f });
        }
        
        gState = G_ENDGAME;
        Audio_PlaySound(bounce2, false);
    }
}

void Test_RestartRound()
{
    padLeft.pos[0] = padLeft.size[0];
    padLeft.pos[1] = (WINDOW_HEIGHT - padLeft.size[1]) / 2;

    padRight.pos[0] = WINDOW_WIDTH - 2 * padRight.size[0];
    padRight.pos[1] = (WINDOW_HEIGHT - padRight.size[1]) / 2;

    glm_vec3_copy((vec3) { (WINDOW_WIDTH - ball.size[0]) / 2, (WINDOW_HEIGHT - ball.size[0]) / 2, 0 }, ball.pos);

    glm_vec2_copy((vec2) { 10, 10 }, ball.vel);
}

void Test_Init()
{
    bounce1 = Audio_LoadWav(FormatText("%s/%s", Filesystem_GetAssetPath(),"sound/bounce1.wav"));
    bounce2 = Audio_LoadWav(FormatText("%s/%s", Filesystem_GetAssetPath(),"sound/bounce2.wav"));

    glm_vec3_copy((vec3) { 1.0f, 1.0f, 1.0f }, padLeft.col);
    glm_vec3_copy((vec3) { 1.0f, 1.0f, 1.0f }, padRight.col);
    glm_vec3_copy((vec3) { 1.0f, 1.0f, 1.0f }, ball.col);

    glm_vec2_copy((vec3) { 20, 150 }, padLeft.size);
    glm_vec2_copy((vec3) { 20, 150 }, padRight.size);
    glm_vec2_copy((vec2) { 10, 10  }, ball.size);

    Test_RestartRound();
}

void Test_Update()
{
    f32 deltaTime = Time_GetDeltaTime();

    switch (gState)
        {
        case G_MENU:
        {
            Test_Menu(deltaTime);

            Test_RestartRound();
        }break;

        case G_ACTIVE:
        {
            Test_Active(deltaTime);
        }break;

        case G_ENDGAME:
        {
            SDL_Delay(2000);

            Test_RestartRound();
            scorePlayer1 = 0;
            scorePlayer2 = 0;

            gState = G_MENU;
        }break;

        default:
            break;
        }

    R2D_DrawColoredQuad(padLeft.pos, padLeft.size, padLeft.col);
    R2D_DrawColoredQuad(padRight.pos, padRight.size, padRight.col);
    R2D_DrawColoredQuad(ball.pos, ball.size, ball.col);

    R2D_DrawText(FormatText("%d", scorePlayer1), WINDOW_WIDTH / 4, 40, 0.75f, (vec3) { 1.0f, 1.0f, 1.0f });
    R2D_DrawText(FormatText("%d", scorePlayer2), WINDOW_WIDTH * 3/4, 40, 0.75f, (vec3) { 1.0f, 1.0f, 1.0f });
}

void Test_Cleanup()
{
}