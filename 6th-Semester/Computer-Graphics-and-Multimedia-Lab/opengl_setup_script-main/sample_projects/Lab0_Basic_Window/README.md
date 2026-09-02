# Lab 0: Basic 2D House Graphics

This reference project demonstrates how to render 2D geometric shapes (Triangle Roof, Quadrilateral House Body, Door, and Windows) in Modern OpenGL (v3.3 Core Profile) using GLFW, GLAD, VBO/VAO arrays, and GLSL shaders.

## Graphic Design Breakdown (Based on CGM Lab-3.1)
- **Roof**: Blue Triangle (`glColor3f(0.1, 0.3, 0.8)`)
- **House Body**: Yellow Quadrilateral (`glColor3f(0.95, 0.85, 0.2)`)
- **Door**: Brown Quadrilateral (`glColor3f(0.55, 0.27, 0.07)`)
- **Windows**: Cyan Quadrilaterals (`glColor3f(0.2, 0.8, 0.9)`)

## Controls
- `ESC` - Close window and exit application

## How to Build and Run

### Windows (MSYS2 / MinGW-w64)
Run in Terminal / Command Prompt:
```bash
make win
```

### Linux
Run in Terminal:
```bash
make linux
```
