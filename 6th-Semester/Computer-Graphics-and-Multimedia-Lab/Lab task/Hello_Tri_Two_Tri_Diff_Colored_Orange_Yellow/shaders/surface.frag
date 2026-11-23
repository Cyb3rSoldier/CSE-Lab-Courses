#version 330 core
in vec3 vFragPos;
in vec3 vNormal;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 baseColor;
uniform bool flatShading;    // true: face normal from screen-space derivatives

out vec4 FragColor;

void main()
{
    vec3 N = flatShading
           ? normalize(cross(dFdx(vFragPos), dFdy(vFragPos)))
           : normalize(vNormal);

    vec3 V = normalize(viewPos - vFragPos);
    if (dot(N, V) < 0.0) N = -N;          // two-sided lighting (patch seen from inside)

    vec3 L = normalize(lightPos - vFragPos);
    vec3 H = normalize(L + V);            // Blinn-Phong half vector

    float diff = max(dot(N, L), 0.0);
    float spec = (diff > 0.0) ? pow(max(dot(N, H), 0.0), 64.0) : 0.0;

    vec3 color = 0.15 * baseColor + diff * baseColor + 0.45 * spec * vec3(1.0);
    FragColor = vec4(color, 1.0);
}
