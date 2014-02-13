#version 150

out vec4 fColor;

void
main()
{
    float lerpValue = gl_FragCoord.y / 512.0f;
    fColor = mix(vec4(0.0, 0.0, 0.0, 1.0),
                 vec4(1.0, 0.0, 1.0, 1.0),
                 lerpValue);
}
