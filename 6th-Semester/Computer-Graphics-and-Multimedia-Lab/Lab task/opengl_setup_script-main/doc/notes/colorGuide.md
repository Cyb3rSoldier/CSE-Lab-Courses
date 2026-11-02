# Modern & Legacy OpenGL Color & Gradient Guide

In OpenGL, colors are represented using the **RGB (Red, Green, Blue)** and **RGBA (Red, Green, Blue, Alpha)** color models. In legacy OpenGL (GLUT), colors are set via `glColor3f(r, g, b)`, whereas in Modern OpenGL (v3.3+ Core Profile), colors are passed to GLSL shaders via **Uniforms** or **Vertex Attributes**.

---

## 1. RGB Color Representation & Conversion Formula

- OpenGL color components are normalized floating-point values from **`0.0f` (0%) to `1.0f` (100%)**.
- **RGB Conversion Formula**: To convert standard 8-bit RGB values (0 to 255) into OpenGL floats:
  $$\text{OpenGL Color Component} = \frac{\text{RGB Value (0--255)}}{255.0}$$

> **Example**: Sky Blue in RGB is `(135, 206, 235)`.  
> In OpenGL float: $\left(\frac{135}{255}, \frac{206}{255}, \frac{235}{255}\right) = (0.53\text{f}, 0.81\text{f}, 0.92\text{f})$.

---

## 2. Solid Color Palette Table

| Color Name | Hex Code | OpenGL Float `(r, g, b)` | Standard RGB (0–255) |
|---|---|---|---|
| **Black** | `#000000` | `(0.0f, 0.0f, 0.0f)` | `(0, 0, 0)` |
| **White** | `#FFFFFF` | `(1.0f, 1.0f, 1.0f)` | `(255, 255, 255)` |
| **Red** | `#FF0000` | `(1.0f, 0.0f, 0.0f)` | `(255, 0, 0)` |
| **Green** | `#00FF00` | `(0.0f, 1.0f, 0.0f)` | `(0, 255, 0)` |
| **Blue** | `#0000FF` | `(0.0f, 0.0f, 1.0f)` | `(0, 0, 255)` |
| **Yellow** | `#FFFF00` | `(1.0f, 1.0f, 0.0f)` | `(255, 255, 0)` |
| **Cyan** | `#00FFFF` | `(0.0f, 1.0f, 1.0f)` | `(0, 255, 255)` |
| **Magenta** | `#FF00FF` | `(1.0f, 0.0f, 1.0f)` | `(255, 0, 255)` |
| **Orange** | `#FFA500` | `(1.0f, 0.65f, 0.0f)` | `(255, 165, 0)` |
| **Purple** | `#800080` | `(0.5f, 0.0f, 0.5f)` | `(128, 0, 128)` |
| **Pink** | `#FFC0CB` | `(1.0f, 0.75f, 0.8f)` | `(255, 192, 203)` |
| **Lime** | `#32CD32` | `(0.2f, 0.8f, 0.2f)` | `(50, 205, 50)` |
| **Sky Blue** | `#87CEEB` | `(0.53f, 0.81f, 0.92f)` | `(135, 206, 235)` |
| **Navy Blue** | `#000080` | `(0.0f, 0.0f, 0.5f)` | `(0, 0, 128)` |
| **Gold** | `#FFD700` | `(1.0f, 0.84f, 0.0f)` | `(255, 215, 0)` |
| **Teal** | `#008080` | `(0.0f, 0.5f, 0.5f)` | `(0, 128, 128)` |
| **Brown** | `#8B4513` | `(0.55f, 0.27f, 0.07f)` | `(139, 69, 19)` |
| **Light Gray** | `#D3D3D3` | `(0.83f, 0.83f, 0.83f)` | `(211, 211, 211)` |
| **Dark Gray** | `#A9A9A9` | `(0.3f, 0.3f, 0.3f)` | `(77, 77, 77)` |

---

## 3. Setting Colors in Modern OpenGL vs. GLUT

### A. Modern OpenGL (GLSL Uniforms & Shaders)
In Modern OpenGL 3.3 Core Profile, color is passed into a Fragment Shader via a uniform variable:

**Fragment Shader (`fragmentShader.glsl`)**:
```glsl
#version 330 core
out vec4 FragColor;
uniform vec4 ourColor; // Dynamic uniform color

void main() {
    FragColor = ourColor;
}
```

**C++ Execution Code**:
```cpp
// Get location of uniform variable in shader program
int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
glUseProgram(shaderProgram);

// Set color dynamically (Red = 1.0, Green = 0.5, Blue = 0.2, Alpha = 1.0)
glUniform4f(vertexColorLocation, 1.0f, 0.5f, 0.2f, 1.0f);
```

### B. Legacy OpenGL / GLUT (`glColor3f`)
```cpp
// Set active color state to Red
glColor3f(1.0f, 0.0f, 0.0f);
glBegin(GL_TRIANGLES);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f( 0.5f, -0.5f);
    glVertex2f( 0.0f,  0.5f);
glEnd();
```

---

## 4. Creating Color Gradients

### A. Multi-Color Vertex Interpolation (Triangle)
When distinct colors are assigned to different vertices, OpenGL rasterizer automatically interpolates colors smoothly across the polygon surface.

**Vertex Data Array (Position + Color Attributes)**:
```cpp
float vertices[] = {
    // Positions         // Colors (R, G, B)
     0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // Top (Red)
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // Bottom-Left (Green)
     0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f  // Bottom-Right (Blue)
};
```

---

## 5. Summary Rules for Colors

1. **Normalized Range**: All color values in C++ and GLSL shaders must remain in $[0.0, 1.0]$.
2. **Background Clear**: Set window background canvas color using `glClearColor(r, g, b, alpha)` before entering the render loop.
3. **State Machine**: In legacy OpenGL, `glColor3f` sets a persistent state until changed. In Modern OpenGL, attributes or uniforms control vertex colors.
