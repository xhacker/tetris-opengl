#version 150

in  vec4 vPosition;
in  vec3 in_Color;
out vec3 out_Color;

void main()
{
    gl_Position = vPosition;
    out_Color = in_Color;
}
