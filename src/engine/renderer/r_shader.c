#include <glad/glad.h>
#include <string.h>
#include "r_shader.h"
#include "engine/log.h"
#include "engine/zone.h"
#include "engine/filesystem.h"
#include "engine/common.h"

char* Shader_GetSource(const char* fileName)
{
    FILE* fp;
    long size = 0;
    char* shaderContent;
    const char* pathToShaders = Filesystem_GetShaderPath();

    char* filePath = FormatText("%s/%s", pathToShaders, fileName);

    /* Read File to get size */
    fp = fopen(filePath, "rb");
    if (fp == NULL) {
        log_error("Failed to read shader: %s\n", filePath);
        return "";
    }
    fseek(fp, 0L, SEEK_END);
    size = ftell(fp) + 1;
    fclose(fp);

    /* Read File for Content */
    fp = fopen(filePath, "r");
    shaderContent = memset(Z_Malloc(size, PU_STATIC, NULL), '\0', size);
    fread(shaderContent, 1, size - 1, fp);
    fclose(fp);

    return shaderContent;
}

Shader Shader_Create(const char* name, const char* pVertPath, const char* pFragPath)
{
    GLuint mVertShader, mFragShader;
    char* VertSource;
    char* FragSource;
    Shader shader = { 0 };
    int success;

    shader.name = name;

    VertSource = Shader_GetSource(pVertPath);
    FragSource = Shader_GetSource(pFragPath);

    // create shaders and program
    mVertShader = glCreateShader(GL_VERTEX_SHADER);
    mFragShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(mVertShader, 1, (const GLchar**)&VertSource, NULL);
    glShaderSource(mFragShader, 1, (const GLchar**)&FragSource, NULL);

    glCompileShader(mVertShader);
    glCompileShader(mFragShader);

    // Vertex Shader
    glGetShaderiv(mVertShader, GL_COMPILE_STATUS, &success);

    // Fragment Shader
    glGetShaderiv(mFragShader, GL_COMPILE_STATUS, &success);

    shader.programID = glCreateProgram();
    glAttachShader(shader.programID, mVertShader);
    glAttachShader(shader.programID, mFragShader);

    glLinkProgram(shader.programID);

    glDeleteShader(mVertShader);
    glDeleteShader(mFragShader);

    Z_Free(VertSource);
    Z_Free(FragSource);

    return shader;
}

void Shader_Use(Shader shader)
{
    glUseProgram(shader.programID);
}

void Shader_Unbind()
{
    glUseProgram(0);
}

void Shader_SetInt(Shader shader, const char* uniform, int value)
{
    glUniform1i(glGetUniformLocation(shader.programID, uniform), value);

    if (glGetUniformLocation(shader.programID, uniform) == -1)
        log_error("%s not found in %s shader", uniform, shader.name);
}

void Shader_SetBoolean(Shader shader, const char* uniform, bool value)
{
    glUniform1i(glGetUniformLocation(shader.programID, uniform), (GLint)value);

    if (glGetUniformLocation(shader.programID, uniform) == -1)
        log_error("%s not found in %s shader", uniform, shader.name);
}

void Shader_SetFloat(Shader shader, const char* uniform, float value)
{
    glUniform1f(glGetUniformLocation(shader.programID, uniform), value);

    if (glGetUniformLocation(shader.programID, uniform) == -1)
        log_error("%s not found in %s shader", uniform, shader.name);
}

void Shader_SetMat4(Shader shader, const char* uniform, mat4 value)
{
    glUniformMatrix4fv(glGetUniformLocation(shader.programID, uniform), 1, GL_FALSE, value[0]);

    if (glGetUniformLocation(shader.programID, uniform) == -1)
        log_error("%s not found in %s shader", uniform, shader.name);
}

void Shader_SetVec3(Shader shader, const char* uniform, vec3 value)
{
    glUniform3fv(glGetUniformLocation(shader.programID, uniform), 1, value);

    if (glGetUniformLocation(shader.programID, uniform) == -1)
        log_error("%s not found in %s shader", uniform, shader.name);
}

void Shader_SetVec4(Shader shader, const char* uniform, vec4 value)
{
    glUniform4fv(glGetUniformLocation(shader.programID, uniform), 1, value);

    if (glGetUniformLocation(shader.programID, uniform) == -1)
        log_error("%s not found in %s shader", uniform, shader.name);
}