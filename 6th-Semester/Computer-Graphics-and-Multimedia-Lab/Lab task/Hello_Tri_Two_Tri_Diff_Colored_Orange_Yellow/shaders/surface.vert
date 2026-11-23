#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normalMatrix;   // transpose(inverse(mat3(model)))

out vec3 vFragPos;           // world space
out vec3 vNormal;            // world space

void main()
{
    vec4 world = model * vec4(aPos, 1.0);
    vFragPos   = world.xyz;
    vNormal    = normalMatrix * aNormal;
    gl_Position = projection * view * world;
}
