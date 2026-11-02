# Modern OpenGL (GLFW + GLAD + MinGW/MSYS2) 1-Click Setup & Automation

An automated setup package and comprehensive technical guide for configuring **Modern OpenGL (v3.3 Core Profile with GLFW and GLAD)** on Windows environments (Windows 10 / 11 64-Bit). Automates MSYS2 installation, offline-first `pacman` toolchain configuration (`base-devel`, `gcc`/`g++`, `make`), safe Windows System `PATH` environment variable registration, `#include <KHR/khrplatform.h>` header fixes, and `glfw3.dll` deployment out of the box.

Some files are taken from: https://github.com/AudityGhosh/Computer_Graphics_and_Animations_Modern_OpenGL

---

> [!IMPORTANT]
> 📖 **Full Technical & Troubleshooting Guide Available**  
> For in-depth explanations of root causes, MSYS2 package manager configuration, header include fixes, Makefile automation, and driver diagnostics:  
> 👉 **[Read the complete technical guide in guide.md](guide.md)**

---

## ⚡ Quick Start (Automated Setup)


### 1. Download or Clone the Repository

- **Option A — Clone with Git:**
  ```bash
  git clone https://github.com/b1tranger/opengl_setup_script.git
  cd opengl_setup_script
  ```

- **Option B — Download ZIP:**
  1. Click the green **Code** button at the top of the GitHub repository page and select **Download ZIP** (or [Click here to download ZIP](https://github.com/b1tranger/opengl_setup_script/archive/refs/heads/main.zip)).
  2. Extract the downloaded `.zip` folder to your preferred location.

---

### 2. Run the Automated Installer

1. Right-click **`install_opengl_admin.bat`** and select **Run as Administrator** (or double-click to run with self-elevation).
2. Confirm the Windows UAC prompt when prompted.
3. The script executes the automated 5-step setup workflow:
   - **[1/5] MSYS2 Detection/Installation**: Checks for an existing MSYS2 installation at `C:\msys64`. If missing, launches the bundled `Dependencies\Graphics_Lab_Install_AG\msys2-x86_64-20260611.exe` installer.
   - **[2/5] Offline-First Toolchain Setup**: Populates MSYS2 pacman cache using pre-packaged offline archives from `Dependencies\msys2_packages` (with automatic network fallback) and installs `base-devel`, `gcc`, `g++`, and `make`.
   - **[3/5] Safe System PATH Registration**: Safely adds `C:\msys64\usr\bin` and `C:\msys64\mingw64\bin` to Machine/System `PATH` via PowerShell environment registry modification without character-length truncation.
   - **[4/5] Toolchain Verification**: Verifies `g++.exe` and `make.exe` availability.
   - **[5/5] Graphics Hardware & Live OpenGL 3.3 Diagnostic Verification**: Runs automated live hardware detection and headless context tests using `setup_hardware_test`. If older hardware (e.g. Intel HD Graphics 2000/3000) or missing drivers fail native context creation, it automatically deploys the localized **Mesa3D (llvmpipe OpenGL 4.6)** software renderer from `Dependencies\mesa3d`.
4. **Interactive Completion Dashboard**:
   - Choose **`[1]`** to create a new custom OpenGL project (runs `PROJECTS\create_project.bat`).
   - Choose **`[2]`** to open the local `sample_projects` folder in Windows File Explorer and view project build instructions.
   - Choose **`[3]`** to open online OpenGL technical notes on GitHub in your default browser.
   - Choose **`[4]`** to deploy or refresh Mesa3D software renderer across all projects.
   - Press **`Enter`** (or type **`0`**) to exit setup.

---


## 🎥 Video Walkthrough

Watch the step-by-step video guide:

<a href="https://youtu.be/AXdDEYzfdxI"><img width="1488" height="837" alt="Modern OpenGL Setup Video Guide" src="https://github.com/user-attachments/assets/a9f2f281-d7be-4b21-8a2f-58d0e232fb4b" /></a>

---

## 🛠️ How to Build & Run Projects

### Using Makefile (Recommended)
Open **Command Prompt (CMD)**, **PowerShell**, or **VS Code Terminal**, navigate to any sample project directory (e.g., `sample_projects/Lab0_Basic_Window` or `sample_projects/Lab1_Color_Triangle`), and execute:

```bash
# Windows (CMD / PowerShell / VS Code)
make win

# Linux Terminal
make linux
```

### Manual Command Line Compilation (Windows)
```cmd
g++.exe -fdiagnostics-color=always -I./include ./src/main.cpp ./src/glad.c -o ./build/main.exe -Llib -lglfw3 -lopengl32 -lgdi32
./build/main.exe
```

> [!NOTE]
> For Linux environments, install dependencies via your package manager first:  
> `sudo apt update && sudo apt install build-essential libglfw3-dev libgl1-mesa-dev`  
> Then run `make linux` in any project directory.

### Creating Custom Projects Automatically
To scaffold a new custom OpenGL project with full boilerplate, libraries, and build scripts:

```cmd
cd PROJECTS
create_project.bat "Lab3_Lighting"
```
* **No Administrator privileges required**: Generates the project folder inside `PROJECTS/`.
* **Automatic Exploration**: Automatically opens the new project in Windows File Explorer and launches a Command Prompt (CMD) window navigated directly into the folder.
* Simply type `make win` to build and run!

---

## 🎨 Sample Projects Included

| Project Folder | Description |
| :--- | :--- |
| **`sample_projects/setup_hardware_test`** | OpenGL 3.3 Core Profile environment diagnostic test (headless/hidden window verification, GLAD loading, GPU info logging). |
| **`sample_projects/Lab0_Basic_Window`** | Basic 2D House Graphics (Blue Roof, Yellow House Body, Brown Door, Cyan Windows, viewport callbacks, GLAD loading). |
| **`sample_projects/Lab1_Color_Triangle`** | Modern OpenGL 3.3 Core Profile pipeline, VAO/VBO vertex attribute buffers, GLSL vertex & fragment shaders, RGB interpolation. |
| **`sample_projects/Lab2_Interactive_Input`** | Real-time keyboard event callbacks (`ESC` to exit, `R`/`G`/`B` to manipulate background color channels, `SPACE` to reset). |

---

## ✨ Key Features & Technical Fixes

- ⚡ **1-Click Self-Elevating Installer**: `install_opengl_admin.bat` automatically requests Administrator privileges and automates the entire toolchain installation in 5 streamlined steps.
- 📦 **Offline-First Package Deployment**: Installs GCC compiler and Make build utilities from pre-downloaded package archives in `Dependencies\msys2_packages` without requiring an active internet connection.
- 🛠️ **Non-Destructive PATH Registration**: Appends MSYS2 binary directories to Windows Machine environment variables using PowerShell registry access, preventing legacy `setx` string-truncation bugs.
- 🖥️ **Live GPU & OpenGL 3.3 Diagnostic Verification**: Runs automated live hardware detection and headless context tests to ensure your GPU is ready.
- 🚀 **Conditional Mesa3D Software Renderer Auto-Fix**: Automatically detects legacy GPUs (e.g. Intel HD Graphics 2000/3000 / Sandy Bridge on Intel Core i3-2100) and transparently hooks `make win` on older machines without bloating modern PCs.
- ⚡ **Ultralight Project Scaffolding**: `PROJECTS/create_project.bat` creates projects with only ~305 KB `glfw3.dll`, auto-opening both File Explorer and a ready-to-use CMD prompt.
- 🔧 **GLAD Include Fixes**: Resolves `#include <KHR/khrplatform.h>` compiler errors out of the box using clean relative include paths.
- 📁 **Cross-Platform Makefiles**: Ready-to-use Makefile configuration with targets for both Windows (`make win`) and Linux (`make linux`).

---

## 🧹 Uninstallation & Maintenance

To remove compiled binaries, uninstall packages, or completely uninstall MSYS2:

1. Right-click **`uninstall_opengl_admin.bat`** and select **Run as Administrator**.
2. Select your desired maintenance operation:
   - **`[1]` Remove PATH entries**: Removes MSYS2 paths from System `PATH`.
   - **`[2]` Delete build binaries**: Deletes all compiled `main.exe` files across sample projects.
   - **`[3]` Uninstall MSYS2 packages**: Runs `pacman -Rns base-devel gcc` and cleans package cache.
   - **`[4]` Full Uninstallation**: Completely removes the `C:\msys64` directory, cleans System PATH entries, and deletes output binaries.

---

## 📚 Technical Guides & Reference Notes

- **[guide.md](guide.md)** — Comprehensive technical setup guide, root causes of common setup errors, and troubleshooting steps.
- **[doc/notes/manualSetupGuide.md](doc/notes/manualSetupGuide.md)** — Manual step-by-step setup guide for MSYS2, MinGW toolchains, compiler commands, and PATH configuration.
- **[doc/notes/colorGuide.md](doc/notes/colorGuide.md)** — OpenGL RGB color model, normalized color floats `[0.0, 1.0]`, and shader gradient interpolation.
- **[doc/notes/circleGuide.md](doc/notes/circleGuide.md)** — Circle rasterization techniques (trigonometric polygon approximation, Midpoint circle algorithm, and GLSL fragment shaders).

---

## 📂 Project File Structure

```
opengl_setup_script/
├── README.md                      # Project overview & quick start guide
├── guide.md                       # Comprehensive technical troubleshooting guide & manual setup
├── install_opengl_admin.bat       # Self-elevating Administrator installer (1-Click setup)
├── uninstall_opengl_admin.bat     # Administrator cleanup & uninstallation script
├── Dependencies/                  # Localized offline setup dependencies
│   ├── Graphics_Lab_Install_AG/   # Core offline MSYS2 installer & original setup reference
│   │   ├── msys2-x86_64-20260611.exe
│   │   └── Setup.pdf
│   ├── mesa3d/                    # Localized Mesa3D (llvmpipe OpenGL 4.6) software renderer DLLs
│   ├── msys2_packages/            # Pre-downloaded pacman package archives (.pkg.tar.zst)
│   ├── template/                  # Pristine blank Modern OpenGL starter template for create_project.bat
│   └── vscode_extensions/         # Localized VS Code Makefile Tools extension (.vsix)
├── PROJECTS/                      # Directory for user-created custom projects
│   └── create_project.bat         # Automated scaffolding script for new projects
├── sample_projects/               # Structured Modern OpenGL sample projects
│   ├── setup_hardware_test/       # Headless diagnostic hardware test
│   ├── Lab0_Basic_Window/         # Basic 2D House Graphics & viewport callbacks
│   ├── Lab1_Color_Triangle/       # OpenGL 3.3 Core Profile programmable shader RGB triangle
│   └── Lab2_Interactive_Input/    # Interactive keyboard callbacks & background color controls
└── doc/                           # Documentation and technical reference notes
    └── notes/                     # Technical guides & Computer Graphics lab notes
        ├── manualSetupGuide.md    # Consolidated manual setup, PATH, Makefile, & batch architecture guide
        ├── colorGuide.md          # OpenGL RGB color palettes & gradient interpolation guide
        └── circleGuide.md         # Circle drawing algorithms (Trig loops, Midpoint, GLSL Shaders)
```

---

## ❓ Troubleshooting Quick Reference

| Issue | Cause | Solution |
| :--- | :--- | :--- |
| **`'g++' or 'make' is not recognized`** | Compiler or build tool missing from PATH | Run `install_opengl_admin.bat` or manually verify `C:\msys64\usr\bin` and `C:\msys64\mingw64\bin` in System PATH. Restart terminal. |
| **`fatal error: KHR/khrplatform.h`** | GLAD unable to find platform include | Use `#include "khrplatform.h"` relative include in `glad.h` or place `khrplatform.h` in `include/`. |
| **`glfw3.dll not found`** | Dynamic library missing from binary directory | Ensure `glfw3.dll` exists in `./build/` alongside `main.exe`. |
| **`Failed to create GLFW window`** | Display driver lacks OpenGL 3.3 Core Profile support (e.g. Intel HD Graphics 2000/3000) | `install_opengl_admin.bat` automatically deploys the localized Mesa3D software renderer from `Dependencies\mesa3d` to enable OpenGL 4.6 on older hardware. You can also select Option `[3]` in the installer menu. |

👉 For full troubleshooting details, see **[guide.md](guide.md)**.
