#include "font.h"
#include "engine/engine.h"

#include <ft2build.h>
#include FT_FREETYPE_H

typedef struct Character {
    unsigned int textureID; // ID handle of the glyph texture
    vec2   size;      // Size of glyph
    vec2   bearing;   // Offset from baseline to left/top of glyph
    unsigned int advance;   // Horizontal offset to advance to next glyph
}Character;

static FT_Library ft;
static Character characters[128];

void R2D_FontInit()
{
    if (FT_Init_FreeType(&ft))
    {
        log_error("Could not init freetype library");
    }
}

void R2D_FontCleanup()
{
}
