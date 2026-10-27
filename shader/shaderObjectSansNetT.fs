
#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec2 TexCoords;

uniform sampler2D t;
uniform float factor;

void main()
{

    float r = fract(gl_PrimitiveID * 0.137);
    float g = fract(gl_PrimitiveID * 0.517);
    float b = fract(gl_PrimitiveID * 0.731);
    float gray = fract(float(gl_PrimitiveID) * 0.137);
    vec3 c = vec3(gray);
    vec3 ct = texture(t , TexCoords).rgb;
    vec3 cc = mix(c, ct, factor);

    FragColor = vec4(cc, 1.0);
}