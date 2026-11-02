# Modern OpenGL (GLFW + GLAD + MinGW/MSYS2) Setup & Technical Guide

## 1. Overview
This technical guide documents the complete automated setup and manual configuration of Modern OpenGL (v3.3 Core Profile using GLFW and GLAD) on Windows 10/11 using MSYS2 and MinGW-w64. It addresses PATH registration, pacman package installation, `#include <KHR/khrplatform.h>` header issues, dynamic DLL loading, and Makefile automation.

---

## 2. Technical Causes of Setup Errors & Solutions

### 1. Missing Compiler Toolchain (`'g++' or 'make' not recognized`)
* **Problem**: Windows command prompt does not natively recognize `g++` or `make`.
* **Root Cause**: Fresh Windows installations lack a GNU C++ compiler suite and build utility.
* **Fix**: Installed MSYS2 and executed `pacman -Sy --noconfirm base-devel gcc`, placing `make.exe` in `C:\msys64\usr\bin` and `g++.exe` in `C:\msys64\mingw64\bin`.

### 2. Missing System PATH Environment Variable
* **Problem**: Terminal shows command not found errors even after installing MSYS2.
* **Root Cause**: `C:\msys64\usr\bin` and `C:\msys64\mingw64\bin` are not in System `PATH`.
* **Fix**: `install_opengl_admin.bat` uses PowerShell environment registry modification to permanently register both directories without truncating long PATH variables.

### 3. GLAD Header Include Error (`fatal error: KHR/khrplatform.h: No such file or directory`)
* **Problem**: Building GLAD throws a missing header error for `KHR/khrplatform.h`.
* **Root Cause**: The auto-generated `glad.h` specifies `#include <KHR/khrplatform.h>`, expecting a `KHR` subfolder in the include path.
* **Fix**: Placed `khrplatform.h` in `include/` and updated `glad.h` to use relative `#include "khrplatform.h"`.

### 4. Dynamic DLL Search Failure (`glfw3.dll not found`)
* **Problem**: Executable fails to launch with a missing DLL dialog.
* **Root Cause**: Windows dynamic linker (`LoadLibrary`) searches current working directory (`./build/`) and system paths for `glfw3.dll`.
* **Fix**: Automatically deploy `glfw3.dll` into `./build/` alongside `main.exe`.

### 5. GLFW Window Creation Failure (`OpenGL 3.3 unsupported`)
* **Problem**: Console output: `Failed to create GLFW window` (Error 255 in make).
* **Root Cause**: The system display driver lacks OpenGL 3.3 Core Profile support (common on older integrated GPUs like 2nd Gen Intel Core i3-2100 / Sandy Bridge Intel HD 2000/3000, or missing GPU drivers with Microsoft Basic Display Adapter).
* **Fix**:
  1. **Fully Automated Background Deployment**: `install_opengl_admin.bat` automatically tests the OpenGL 3.3 context in Step 5. If native context creation fails, it stores Mesa3D in `C:\msys64\opt\mesa3d` and installs a transparent build-tool automation hook for `g++.exe` and `make.exe`. Whenever `make win` or `g++` is executed on **any** project folder on the system, the required Mesa3D DLLs (`opengl32.dll` and `libgallium_wgl.dll`) are auto-copied to the project's `./build/` folder on the fly with zero manual copying needed.
  2. **Manual Fallback**: Copy `opengl32.dll` and `libgallium_wgl.dll` from `Dependencies\mesa3d\` into your project's `build/` folder (next to `main.exe`). Windows will use CPU-based OpenGL 4.6 software rendering with full SSE4/AVX vector acceleration.

---

## 3. Automated 1-Click Setup (`install_opengl_admin.bat`)

To automatically install MSYS2, package dependencies, verify hardware capabilities, and update PATH environment variables:

1. Right-click **`install_opengl_admin.bat`** and select **Run as administrator** (or double-click to self-elevate).
2. Click **Yes** on the Windows UAC elevation prompt.
3. The script executes the automated 5-step setup workflow:
   - **[1/5] MSYS2 Detection/Installation**: Checks for an existing MSYS2 installation at `C:\msys64` (installs `msys2-x86_64-20260611.exe` if missing).
   - **[2/5] Offline-First Toolchain Setup**: Populates MSYS2 pacman cache using pre-packaged offline archives from `Dependencies\msys2_packages` and installs `base-devel`, `gcc`, `g++`, and `make`.
   - **[3/5] Safe System PATH Registration**: Safely adds `C:\msys64\usr\bin` and `C:\msys64\mingw64\bin` to Machine/System `PATH` via PowerShell environment registry modification without string-length truncation.
   - **[4/5] Toolchain Verification**: Verifies `g++.exe` and `make.exe` availability.
   - **[5/5] Graphics Hardware & Live OpenGL 3.3 Diagnostic Verification**: Runs automated live hardware detection and headless context tests using `setup_hardware_test`. If older hardware or missing drivers fail native context creation, it automatically deploys the localized **Mesa3D (llvmpipe OpenGL 4.6)** software renderer from `Dependencies\mesa3d`.
4. **Interactive Completion Dashboard**:
   - **`[1]`** Create a New Custom Project (Runs `PROJECTS\create_project.bat`).
   - **`[2]`** Open local `sample_projects` folder in Windows File Explorer and view build instructions.
   - **`[3]`** Open online OpenGL technical notes on GitHub in your default browser.
   - **`[4]`** Deploy / Refresh Mesa3D software renderer across all sample projects and custom projects.
   - **`[0]`** Exit setup (or press Enter).

### Creating New Projects (`PROJECTS\create_project.bat`):
To scaffold a new custom OpenGL project with full boilerplate, libraries, and build scripts:
1. Double-click **`PROJECTS\create_project.bat`** (no Administrator privileges required) or run:
   ```cmd
   create_project.bat "Lab3_Lighting"
   ```
2. The script will:
   - Scaffold the complete project directory structure (`src/`, `include/`, `lib/`, `build/`).
   - Copy required headers, GLAD loader, and link libraries.
   - Automatically open the new project folder in **Windows File Explorer**.
   - Automatically launch a **Command Prompt (CMD)** window inside the new folder.
3. In the opened CMD window, simply type:
   ```cmd
   make win
   ```

### Uninstallation & Cleanup (`uninstall_opengl_admin.bat`):
To clean up compiled binaries, uninstall packages, or completely remove MSYS2:
1. Right-click **`uninstall_opengl_admin.bat`** and select **Run as administrator**.
2. Select your desired option:
   - **`[1]`** Remove MSYS2 paths from System `PATH`
   - **`[2]`** Delete output binaries (`main.exe`) across sample projects
   - **`[3]`** Uninstall pacman packages (`base-devel`, `gcc`) and clear cache
   - **`[4]`** **Full Uninstallation** (Completely remove `C:\msys64` folder, clean System `PATH`, and delete output binaries)

---

## 4. How to Build & Run OpenGL Projects

### Using Makefile (Recommended)
Open **Command Prompt (CMD)**, **PowerShell**, or **VS Code Terminal**, navigate to any lab folder (e.g. `sample_projects/Lab0_Basic_Window` or `sample_projects/Lab1_Color_Triangle`), and execute:

```bash
# Windows Command Prompt (CMD) or PowerShell
make win

# Linux Terminal
make linux
```

### Manual Command Line Compilation
```cmd
g++.exe -fdiagnostics-color=always -I./include ./src/main.cpp ./src/glad.c -o ./build/main.exe -Llib -lglfw3 -lopengl32 -lgdi32
./build/main.exe
```

---

## 5. Sample Projects Included

1. **`setup_hardware_test`**: Headless/hidden window diagnostic test for GLFW initialization, OpenGL 3.3 Core Profile context creation, and GLAD loading.
2. **`Lab0_Basic_Window`**: Basic 2D House Graphics (Blue Roof, Yellow House Body, Brown Door, Cyan Windows), viewport callbacks, and buffer clearing.
3. **`Lab1_Color_Triangle`**: OpenGL 3.3 Core Profile programmable shader pipeline, VBO/VAO setup, shader compilation, and uniform color manipulation.
4. **`Lab2_Interactive_Input`**: Keyboard input callbacks (`ESC` to exit, `R`/`G`/`B` to tweak background RGB, `SPACE` to reset).
