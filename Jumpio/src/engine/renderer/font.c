#include "font.h"
#include "engine/zone.h"

#include <ft2build.h>
#include FT_FREETYPE_H

static FT_Library ft;
static Character* characters;
static u16 fontSize;

void Font_Init()
{
    characters = (Character*)Z_Malloc(sizeof(Character) * 128, PU_STATIC, NULL);
    memset(characters, 0, sizeof(Character) * 128);

    char* fontFile = "assets/font/PressStart2P-vaV7.ttf";
    //char* fontFile = "assets/font/arial.ttf";

    if (FT_Init_FreeType(&ft))
    {
        log_error("Could not init freetype library");
    }

    FT_Face face;

    if (FT_New_Face(ft, fontFile, 0, &face)) {
        log_error("Failed to load font at path: %s", *fontFile);
    }
    else {
        // set size to load glyphs as
        FT_Set_Pixel_Sizes(face, 0, 48);

        // disable byte-alignment restriction
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        // load first 128 characters of ASCII set
        for (unsigned char c = 0; c < 128; c++)
        {
            // Load character glyph 
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                log_error("Failed to load Glyph");
                continue;
            }
            // generate texture
            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
            );
            // set texture options
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            // now store character for later use
            Character character = {
                texture,
                {face->glyph->bitmap.width, face->glyph->bitmap.rows},
                {face->glyph->bitmap_left, face->glyph->bitmap_top},
                (u16)(face->glyph->advance.x)
            };

            characters[c] = character;
        }

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    fontSize = face->size->metrics.y_ppem;

    // destroy FreeType once we're finished
    FT_Done_Face(face);
}

Character* Font_GetCharactersBuffer()
{
    return characters;
}

void Font_Cleanup()
{
    FT_Done_FreeType(ft);
    Z_Free(characters);
}

u16 Font_GetFontSize()
{
    return fontSize;
}
