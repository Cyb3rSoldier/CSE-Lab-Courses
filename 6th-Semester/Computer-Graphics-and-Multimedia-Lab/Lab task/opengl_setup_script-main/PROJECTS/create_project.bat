@echo off
setlocal EnableDelayedExpansion

:: ------------------------------------------------------------
:: Automated Modern OpenGL Project Generator
:: Scaffolds a complete OpenGL (GLFW + GLAD) project folder
:: inside the PROJECTS directory.
:: ------------------------------------------------------------

set "SCRIPT_DIR=%~dp0"
for %%I in ("%SCRIPT_DIR%..") do set "ROOT_DIR=%%~fI"
set "TEMPLATE_DIR=%ROOT_DIR%\Dependencies\template"
if not exist "%TEMPLATE_DIR%\include" (
    set "TEMPLATE_DIR=%ROOT_DIR%\sample_projects\Lab0_Basic_Window"
)
set "BLANK_SRC=%ROOT_DIR%\Dependencies\template\src\main.cpp"
set "MESA_DIR=%ROOT_DIR%\Dependencies\mesa3d"

echo ============================================================
echo   Modern OpenGL Project Generator (GLFW + GLAD + MinGW)
echo ============================================================
echo.

:: Get project title / folder name from argument or interactive prompt
set "PROJECT_NAME=%~1"

if "%PROJECT_NAME%"=="" (
    set /p "PROJECT_NAME=Enter project title / folder name (e.g. Lab3_Lighting): "
)

:: Validate project name
if "%PROJECT_NAME%"=="" (
    echo [ERROR] Project name cannot be empty.
    goto END_PAUSE
)

:: Sanitize input quotes
set "PROJECT_NAME=%PROJECT_NAME:"=%"
set "TARGET_DIR=%SCRIPT_DIR%%PROJECT_NAME%"

if exist "%TARGET_DIR%" (
    echo.
    echo [ERROR] A project folder named '%PROJECT_NAME%' already exists in:
    echo         %SCRIPT_DIR%
    goto END_PAUSE
)

echo.
echo [*] Initializing blank project '%PROJECT_NAME%' in:
echo     %TARGET_DIR%
echo.

:: 1. Create project folder structure
echo [1/4] Creating folder structure...
mkdir "%TARGET_DIR%"
mkdir "%TARGET_DIR%\build"
mkdir "%TARGET_DIR%\include"
mkdir "%TARGET_DIR%\lib"
mkdir "%TARGET_DIR%\src"

:: 2. Copy Headers & Build Files from Template
echo [2/4] Copying headers, GLAD loader, and Makefile...
if exist "%TEMPLATE_DIR%\include" (
    copy /Y "%TEMPLATE_DIR%\include\*" "%TARGET_DIR%\include\" >nul
) else (
    echo [WARNING] Include template not found at: %TEMPLATE_DIR%\include
)

if exist "%TEMPLATE_DIR%\src\glad.c" (
    copy /Y "%TEMPLATE_DIR%\src\glad.c" "%TARGET_DIR%\src\" >nul
)

if exist "%TEMPLATE_DIR%\Makefile" (
    copy /Y "%TEMPLATE_DIR%\Makefile" "%TARGET_DIR%\" >nul
)

:: 3. Copy Link and Runtime Dependencies (lib and build folders)
echo [3/4] Copying runtime dependencies and DLLs into 'lib' and 'build'...

:: Copy glfw3.dll to lib/ (for compilation/link reference)
if exist "%TEMPLATE_DIR%\lib\glfw3.dll" (
    copy /Y "%TEMPLATE_DIR%\lib\glfw3.dll" "%TARGET_DIR%\lib\" >nul
)

:: Copy glfw3.dll to build/ (for executable dynamic loading at runtime)
if exist "%TEMPLATE_DIR%\build\glfw3.dll" (
    copy /Y "%TEMPLATE_DIR%\build\glfw3.dll" "%TARGET_DIR%\build\" >nul
) else if exist "%TEMPLATE_DIR%\lib\glfw3.dll" (
    copy /Y "%TEMPLATE_DIR%\lib\glfw3.dll" "%TARGET_DIR%\build\" >nul
)

:: 4. Generate Blank Starter main.cpp
echo [4/4] Generating blank starter source code in 'src\main.cpp'...
if exist "%BLANK_SRC%" (
    copy /Y "%BLANK_SRC%" "%TARGET_DIR%\src\main.cpp" >nul
) else if exist "%TEMPLATE_DIR%\src\main.cpp" (
    copy /Y "%TEMPLATE_DIR%\src\main.cpp" "%TARGET_DIR%\src\main.cpp" >nul
)

echo.
echo ============================================================
echo   [SUCCESS] Blank project '%PROJECT_NAME%' created successfully!
echo ============================================================
echo.
echo Location:
echo   %TARGET_DIR%
echo.
echo ------------------------------------------------------------
echo   Instructions to Open and Run Your Project:
echo ------------------------------------------------------------
echo   1. Open Command Prompt (CMD), PowerShell, or VS Code.
echo   2. Navigate to your project folder:
echo        cd /d "%TARGET_DIR%"
echo   3. Compile and launch your OpenGL application:
echo        make win
echo.
echo   To edit your code:
echo        Open '%TARGET_DIR%\src\main.cpp' in your code editor.
echo.
echo ------------------------------------------------------------
echo   Creating More Projects in the Future:
echo ------------------------------------------------------------
echo   - You can create new projects anytime directly from this folder!
echo   - Simply double-click 'create_project.bat' (No Admin needed)
echo     or run via command line:
echo        create_project.bat "Lab_Title"
echo ============================================================
echo.

:: Automatically open the newly created project folder in Windows File Explorer
start "" "%TARGET_DIR%"

:: Automatically open a Command Prompt window inside the new project folder
start "OpenGL Project - %PROJECT_NAME%" /D "%TARGET_DIR%" cmd.exe /k "echo ============================================================ & echo   Project: %PROJECT_NAME% & echo   Type 'make win' to compile and run your OpenGL application. & echo ============================================================ & echo."

:END_PAUSE
if "%~1"=="" (
    pause
)
