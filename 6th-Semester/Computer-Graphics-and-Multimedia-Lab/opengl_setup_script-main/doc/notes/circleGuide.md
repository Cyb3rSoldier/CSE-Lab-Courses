# Circle Drawing Methods in Modern & Legacy OpenGL

In OpenGL, there is no built-in `glDrawCircle()` command. Circles are drawn by approximating a smooth curve using polygons, line loops, triangle fans, or modern GLSL Fragment Shader distance functions.

---

## 1. Approach 1: Trigonometric & Loop Approximation (`cos` / `sin`)

### Concept
A loop generates vertices around the circle perimeter using basic trigonometry:
$$x = cx + r \cdot \cos(\theta), \quad y = cy + r \cdot \sin(\theta)$$

### Modern OpenGL VBO/VAO Generation Code
```cpp
#include <vector>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Generate circle vertex buffer data
std::vector<float> generateCircleVertices(float cx, float cy, float radius, int segments = 100) {
    std::vector<float> vertices;
    // Center point for GL_TRIANGLE_FAN
    vertices.push_back(cx);
    vertices.push_back(cy);
    vertices.push_back(0.0f);

    for (int i = 0; i <= segments; ++i) {
        float theta = 2.0f * M_PI * float(i) / float(segments);
        float x = cx + radius * cosf(theta);
        float y = cy + radius * sinf(theta);
        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(0.0f);
    }
    return vertices;
}
```

---

## 2. Approach 2: Legacy GLUT Immediate Mode (`glBegin` / `glEnd`)

```cpp
#include <GL/glut.h>
#include <cmath>

void drawCircleGL(float cx, float cy, float radius, int segments = 100) {
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy); // Center
        for (int i = 0; i <= segments; ++i) {
            float theta = 2.0f * 3.14159265f * float(i) / float(segments);
            float x = cx + radius * cosf(theta);
            float y = cy + radius * sinf(theta);
            glVertex2f(x, y);
        }
    glEnd();
}
```

---

## 3. Approach 3: Midpoint / Bresenham's Circle Algorithm

Calculates pixel positions using 8-way symmetry without floating-point trigonometric evaluations:

```cpp
void drawMidpointCircle(float cx, float cy, float radius) {
    int r = (int)(radius * 500);
    int x = 0, y = r;
    int p = 1 - r;

    auto plot8Points = [&](int x, int y) {
        float s = 1.0f / 500.0f;
        // Plot (cx ± x, cy ± y) across 8 octants
    };

    plot8Points(x, y);
    while (x < y) {
        x++;
        if (p < 0) p += 2 * x + 1;
        else { y--; p += 2 * (x - y) + 1; }
        plot8Points(x, y);
    }
}
```

---

## 4. Approach 4: Modern GLSL Fragment Shader Circles

In Modern OpenGL 3.3 Core Profile, per-pixel circles are drawn inside the Fragment Shader using distance calculations:

**Fragment Shader (`circle.frag`)**:
```glsl
#version 330 core
out vec4 FragColor;
in vec2 TexCoord; // Normalized coordinates [0, 1]

void main() {
    // Distance from center (0.5, 0.5)
    float dist = length(TexCoord - vec2(0.5));
    if (dist > 0.5) {
        discard; // Transparent background outside circle radius
    }
    FragColor = vec4(0.2, 0.6, 1.0, 1.0); // Filled Circle Color
}
```

---

## Summary Comparison

| Approach | Smoothness | Rendering Technique | Recommended Use Case |
|---|---|---|---|
| **Trig Loop (Cos/Sin)** | High | `GL_TRIANGLE_FAN` / VBO | General 2D Graphics Labs |
| **Midpoint Algorithm** | Pixel Level | `GL_POINTS` | Computer Graphics Theory Assignments |
| **GLSL Shader Distance** | Perfect (Resolution Independent) | Fragment Shader Procedural | Modern GUI & Particle Engines |
