#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

uniform float Time; // The animation time

// Wave parameters
uniform float K; // Wavenumber
uniform float Velocity; // Wave's velocity
uniform float Amp; // Wave's amplitude

//MVP stuff
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{
    vec4 pos = vec4(aPos,1.0);

    // Translate the y coordinate
    float u = K * (pos.z - Velocity * Time);
    pos.y = Amp * sin( u );

    
    gl_Position = projection * view * model * pos;
}

