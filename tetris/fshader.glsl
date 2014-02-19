#version 150

in  vec3 in_Color;
out vec4 out_Color;

void main()
{
    out_Color = (vec4(0.8, 0.8, 0.8, 1.0)); //vec4(in_Color, 1.0);
}
