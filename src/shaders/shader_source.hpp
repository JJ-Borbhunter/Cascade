#pragma once

//#define DEGUB_GRID
#undef DEBUG_GRID

#ifndef DEGUB_GRID
const char* VERTEX_SHADER_SOURCE = R"(

#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texcoords;

uniform mat4 transformations;

out vec2 UV;

void main() {
    gl_Position = transformations * vec4(position, 0.0, 1.0);
    UV = texcoords;
}

)";

const char* FRAGMENT_SHADER_SOURCE = R"(

#version 330 core

in vec2 UV;

uniform sampler2D image;
out vec4 Color; 

void main() {
    Color = vec4(texture(image, UV).rgba);
}

)";
#endif


#ifdef DEGUB_GRID
const char* VERTEX_SHADER_SOURCE = R"(

#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texcoords;

uniform mat4 transformations;

out vec2 UV;
out vec2 pos;

void main() {
    gl_Position = transformations * vec4(position, 0.0, 1.0);
    UV = texcoords;
    pos = position;
}

)";


const char* FRAGMENT_SHADER_SOURCE = R"(


#version 330 core

in vec2 UV;
in vec2 pos;

uniform sampler2D image;
out vec4 Color;

bool is_grid(vec2 posi){
    bool r = false;
    float grid_size = 75;
    float x = posi.x;
    float y = posi.y;

    
    //y -= grid_size/2.14;

    float a = x * 0.5773502691896258 - y;
    float b = x * 0.5773502691896258 + y;
    a /= grid_size;
    b /= grid_size;
    if((a <= floor(a) + 0.05 && a >= floor(a) - 0.05) ||
        (b <= floor(b) + 0.05 && b >= floor(b) - 0.05)
    ) {
        r = true;
    }
    return r;
}  

void main() {
    Color = vec4(texture(image, UV).rgba);

    if(is_grid(pos)){
        Color = vec4(0.0, 0.0, 0.0, 1.0);
    }

    if(Color.a < 0.2){
        discard;
    }
}

)";
#endif