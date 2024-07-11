#version 150 core
in vec4 position;

uniform vec2 size;
uniform float scale;

void main()
{
    gl_Position = position * vec4( scale / size, 1.0, 1.0 );
}