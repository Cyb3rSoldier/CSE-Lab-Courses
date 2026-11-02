# OpenGL 3.3 Setup & Hardware Diagnostic Test

This diagnostic project verifies Modern OpenGL (v3.3 Core Profile) capability, GLFW window initialization, and GLAD loader support. It creates a **hidden window** (`GLFW_VISIBLE = GLFW_FALSE`) so it can be safely executed by automated installation scripts (`install_opengl_admin.bat`) and CLI tools without flashing a window or blocking execution.

## Features
- Validates GLFW and GLAD initialization
- Tests OpenGL 3.3 Core Profile context creation
- Queries and prints active GPU Vendor, Renderer, OpenGL Version, and GLSL Version
- Exits cleanly with status code `0` on success or `-1` on failure

## How to Run Diagnostic Test

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
