#ifndef FONT_H
#define FONT_H

#include <glad/glad.h>
#include <cglm.h>
#include "engine/data_types.h"
#include "engine/log.h"

typedef struct Character {
    unsigned int textureID; // ID handle of the glyph texture
    ivec2   size;      // Size of glyph
    ivec2   bearing;   // Offset from baseline to left/top of glyph
    unsigned int advance;   // Horizontal offset to advance to next glyph
}Character;

void R2D_FontInit();
void R2D_FontCleanup();

Character* R2D_GetCharactersBuffer();

#endif