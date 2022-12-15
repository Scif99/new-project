#version 330 core
layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec2 a_tex_coord; 

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 projection;


void main()
{
    TexCoord = a_tex_coord;
    gl_Position =  projection * model * vec4(a_pos.xy, 0.0, 1.0);


}