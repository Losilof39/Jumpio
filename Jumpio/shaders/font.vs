#version 460 core
layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>
out vec2 TexCoords;

uniform mat4 u_Ortho;

void main()
{
    gl_Position = u_Ortho * vec4(vertex.xy, 0.0, 1.0);
    TexCoords = vertex.zw;
}  