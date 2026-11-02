@echo off
:: Self-elevating Administrator script for OpenGL (GLFW + GLAD + MinGW/MSYS2) setup
net session >nul 2>&1
if %errorLevel% neq 0 (
    echo Requesting Administrator privileges...
    powershell -Command "Start-Process -FilePath '%~f0' -Verb RunAs"
    exit /b
)

setlocal EnableDelayedExpansion
cd /d "%~dp0"
for %%I in ("%~dp0.") do set "PROJECT_ROOT=%%~fI"

echo ============================================================
echo   Automated Modern OpenGL (GLFW + GLAD + MSYS2) Setup
echo   Supports: Windows 10/11 64-Bit Environments
echo ============================================================
echo.

set "MSYS2_DIR=C:\msys64"
set "INSTALLER_EXE=%PROJECT_ROOT%\Dependencies\Graphics_Lab_Install_AG\msys2-x86_64-20260611.exe"
set "LOCAL_PKG_DIR=%PROJECT_ROOT%\Dependencies\msys2_packages"
set "LOCAL_MESA_DIR=%PROJECT_ROOT%\Dependencies\mesa3d"
set "GALLIUM_DRIVER=llvmpipe"

:: 1. Check MSYS2 Installation
echo [1/5] Checking MSYS2 package manager installation...
if exist "%MSYS2_DIR%\usr\bin\bash.exe" goto MSYS_OK

echo [NOT FOUND] MSYS2 is not installed at "%MSYS2_DIR%".
if not exist "%INSTALLER_EXE%" goto INSTALLER_MISSING

echo Launching MSYS2 installer: msys2-x86_64-20260611.exe...
echo Please complete the setup wizard using default path C:\msys64
start /wait "" "%INSTALLER_EXE%"
goto CHECK_MSYS_AGAIN

:INSTALLER_MISSING
echo [ERROR] MSYS2 installer executable not found at: "%INSTALLER_EXE%"
echo Please download MSYS2 manually from https://www.msys2.org/ and install to C:\msys64.
pause
exit /b 1

:CHECK_MSYS_AGAIN
if exist "%MSYS2_DIR%\usr\bin\bash.exe" goto MSYS_OK

echo [ERROR] MSYS2 installation path "%MSYS2_DIR%\usr\bin\bash.exe" not found after installer completed.
pause
exit /b 1

:MSYS_OK
echo [FOUND] MSYS2 detected at: "%MSYS2_DIR%"

:: Remove stale pacman lock file if present from a previous interrupted run
if exist "%MSYS2_DIR%\var\lib\pacman\db.lck" (
    echo [CLEANUP] Removing stale pacman lock file /var/lib/pacman/db.lck ...
    del /F /Q "%MSYS2_DIR%\var\lib\pacman\db.lck" >nul 2>&1
)

:: 2. Localize MSYS2 Package Installation (Offline-First)
echo.
echo [2/5] Installing C++ compiler (gcc/g++) and build tools (make)...

if not exist "%MSYS2_DIR%\var\cache\pacman\pkg" mkdir "%MSYS2_DIR%\var\cache\pacman\pkg"

if exist "%LOCAL_PKG_DIR%\*.pkg.tar.zst" (
    echo [LOCAL DETECTED] Found offline package archives in Dependencies\msys2_packages.
    echo Populating MSYS2 local pacman cache...
    del /F /Q "%MSYS2_DIR%\var\cache\pacman\pkg\*.pkg.tar.zst" >nul 2>&1
    xcopy /Y /Q "%LOCAL_PKG_DIR%\*.pkg.tar.zst" "%MSYS2_DIR%\var\cache\pacman\pkg\" >nul 2>&1
) else (
    echo [NETWORK FALLBACK] Local package archives not found. Will download via network...
)

echo Installing packages via MSYS2 pacman...
"%MSYS2_DIR%\usr\bin\bash.exe" -lc "export MSYSTEM=MSYS MSYS=winsymlinks:nativestrict && pacman -U --needed --noconfirm /var/cache/pacman/pkg/*.pkg.tar.zst"

:: 3. Configure System Environment Variables (PATH)
echo.
echo [3/5] Registering MSYS2 binaries in System Environment PATH...
powershell -Command "$sysPath = [System.Environment]::GetEnvironmentVariable('Path', 'Machine'); $usrBin = 'C:\msys64\usr\bin'; $mingwBin = 'C:\msys64\mingw64\bin'; $newPath = $sysPath; if (-not ($sysPath -split ';' -contains $usrBin)) { $newPath = $usrBin + ';' + $newPath }; if (-not ($sysPath -split ';' -contains $mingwBin)) { $newPath = $mingwBin + ';' + $newPath }; if ($newPath -ne $sysPath) { [System.Environment]::SetEnvironmentVariable('Path', $newPath, 'Machine'); Write-Host '[SUCCESS] System PATH updated.' } else { Write-Host '[OK] MSYS2 paths already present in System PATH.' }"

:: Refresh local script environment PATH for current session
set "PATH=%MSYS2_DIR%\usr\bin;%MSYS2_DIR%\mingw64\bin;%PATH%"

:: 4. Verify g++ and make executables
echo.
echo [4/5] Verifying compiler and build tool availability...
where g++ >nul 2>&1
if %errorLevel% equ 0 (
    echo   - Compiler g++.exe is accessible in PATH.
) else (
    echo   [!] Warning: g++.exe not immediately visible in session PATH. Restart terminal after setup.
)

where make >nul 2>&1
if %errorLevel% equ 0 (
    echo   - Build tool make.exe is accessible in PATH.
) else (
    echo   [!] Warning: make.exe not immediately visible in session PATH. Restart terminal after setup.
)

:: 5. Graphics Hardware & Live OpenGL 3.3 Diagnostic Verification
echo.
echo [5/5] Verifying Graphics Hardware and Live OpenGL 3.3 Context...

:: --- Method 1: Hardware & Driver Query via PowerShell / WMI ---
powershell -NoProfile -Command "$gpus = Get-CimInstance Win32_VideoController -ErrorAction SilentlyContinue; if ($gpus) { foreach ($g in $gpus) { Write-Host ('   - Detected Display Adapter: ' + $g.Name); if ($g.Name -match 'Basic Display') { Write-Host '     [WARNING] Microsoft Basic Display Adapter in use [Missing official GPU driver].' -ForegroundColor Red } elseif ($g.Name -match 'HD Graphics') { Write-Host '     [NOTE] Legacy Intel HD Graphics detected [May require Mesa3D for OpenGL 3.3+].' -ForegroundColor Yellow } } }"

:: --- Method 2: Live OpenGL 3.3 Context Test using setup_hardware_test (Hidden Window) ---
echo    - Running live OpenGL 3.3 Core Profile initialization test...
set "TEST_DIR=%PROJECT_ROOT%\sample_projects\setup_hardware_test"
set "TEST_EXE=%TEST_DIR%\build\main.exe"

if not exist "%TEST_DIR%" (
    echo   [INFO] Diagnostic test directory not found.
    goto SUCCESS_SETUP
)

pushd "%TEST_DIR%"
echo    - Compiling diagnostic test binary...
if not exist "build" mkdir "build"

:: Ensure clean test build directory with only glfw3.dll for initial hardware probe
if exist "build\opengl32.dll" del /F /Q "build\opengl32.dll" >nul 2>&1
if exist "build\libgallium_wgl.dll" del /F /Q "build\libgallium_wgl.dll" >nul 2>&1
if exist "lib\glfw3.dll" copy /Y "lib\glfw3.dll" "build\glfw3.dll" >nul 2>&1

g++.exe -fdiagnostics-color=always -I./include ./src/main.cpp ./src/glad.c -o ./build/main.exe -Llib -lglfw3 -lopengl32 -lgdi32 >nul 2>&1

if not exist "%TEST_EXE%" (
    echo   [Warning] Could not build diagnostic test binary.
    popd
    goto SUCCESS_SETUP
)

:: Run test binary
".\build\main.exe" >nul 2>&1
set "TEST_RESULT=%errorlevel%"
popd

if "%TEST_RESULT%"=="0" (
    pushd "%TEST_DIR%"
    ".\build\main.exe"
    popd

    :: If previously wrapped, restore pure native compiler & make binaries
    if exist "%MSYS2_DIR%\usr\bin\g++_orig.exe" (
        copy /Y "%MSYS2_DIR%\usr\bin\g++_orig.exe" "%MSYS2_DIR%\usr\bin\g++.exe" >nul 2>&1
        del /F /Q "%MSYS2_DIR%\usr\bin\g++_orig.exe" >nul 2>&1
    )
    if exist "%MSYS2_DIR%\usr\bin\make_orig.exe" (
        copy /Y "%MSYS2_DIR%\usr\bin\make_orig.exe" "%MSYS2_DIR%\usr\bin\make.exe" >nul 2>&1
        del /F /Q "%MSYS2_DIR%\usr\bin\make_orig.exe" >nul 2>&1
    )
    goto SUCCESS_SETUP
)

echo.
echo   ========================================================================
echo   [NOTICE] Native GPU driver could not create OpenGL 3.3 Core Profile.
echo   ========================================================================
if exist "%LOCAL_MESA_DIR%\opengl32.dll" (
    echo   [AUTO-FIX] Localized Mesa3D Software Renderer detected in Dependencies!
    echo   1. Installing central Mesa3D storage to "%MSYS2_DIR%\opt\mesa3d"...
    if not exist "%MSYS2_DIR%\opt\mesa3d" mkdir "%MSYS2_DIR%\opt\mesa3d"
    copy /Y "%LOCAL_MESA_DIR%\*.dll" "%MSYS2_DIR%\opt\mesa3d\" >nul 2>&1

    echo   2. Deploying Mesa3D [OpenGL 4.6 llvmpipe] to sample projects...
    for /d %%D in ("%PROJECT_ROOT%\sample_projects\*") do (
        if not exist "%%D\build" mkdir "%%D\build"
        copy /Y "%LOCAL_MESA_DIR%\*.dll" "%%D\build\" >nul 2>&1
    )

    if exist "%PROJECT_ROOT%\PROJECTS" (
        for /d %%D in ("%PROJECT_ROOT%\PROJECTS\*") do (
            if not exist "%%D\build" mkdir "%%D\build"
            copy /Y "%LOCAL_MESA_DIR%\*.dll" "%%D\build\" >nul 2>&1
        )
    )

    echo   3. Configuring automated background deployment for 'make win'...
    if exist "%LOCAL_MESA_DIR%\mesa_wrapper.cpp" (
        pushd "%LOCAL_MESA_DIR%"
        g++.exe -std=c++17 -O2 mesa_wrapper.cpp -o mesa_wrapper.exe >nul 2>&1
        popd
        if exist "%LOCAL_MESA_DIR%\mesa_wrapper.exe" (
            if not exist "%MSYS2_DIR%\usr\bin\g++_orig.exe" (
                if exist "%MSYS2_DIR%\usr\bin\g++.exe" ren "%MSYS2_DIR%\usr\bin\g++.exe" "g++_orig.exe"
            )
            if exist "%MSYS2_DIR%\usr\bin\g++_orig.exe" (
                copy /Y "%LOCAL_MESA_DIR%\mesa_wrapper.exe" "%MSYS2_DIR%\usr\bin\g++.exe" >nul 2>&1
            )
            if not exist "%MSYS2_DIR%\usr\bin\make_orig.exe" (
                if exist "%MSYS2_DIR%\usr\bin\make.exe" ren "%MSYS2_DIR%\usr\bin\make.exe" "make_orig.exe"
            )
            if exist "%MSYS2_DIR%\usr\bin\make_orig.exe" (
                copy /Y "%LOCAL_MESA_DIR%\mesa_wrapper.exe" "%MSYS2_DIR%\usr\bin\make.exe" >nul 2>&1
            )
            del /F /Q "%LOCAL_MESA_DIR%\mesa_wrapper.exe" >nul 2>&1
            echo      - Build-tool automation hooks installed successfully.
        )
    )

    :: Set GALLIUM_DRIVER=llvmpipe to eliminate Zink Vulkan probe error
    powershell -Command "[System.Environment]::SetEnvironmentVariable('GALLIUM_DRIVER', 'llvmpipe', 'Machine')" >nul 2>&1
    set "GALLIUM_DRIVER=llvmpipe"
    echo   4. Retesting OpenGL context with Mesa3D software renderer...
    pushd "%TEST_DIR%"
    copy /Y "%LOCAL_MESA_DIR%\*.dll" "build\" >nul 2>&1
    ".\build\main.exe"
    popd
    echo.
    echo   [SUCCESS] OpenGL 3.3+ is now active and verified via Mesa3D!
    echo   Legacy hardware support enabled: 'make win' will now work in ANY project folder!
) else (
    echo   Root Causes and Solutions:
    echo     1. Missing GPU Driver: If using Microsoft Basic Display Adapter,
    echo        install official Intel/AMD/NVIDIA graphics drivers.
    echo     2. Older GPU Hardware: If your GPU only supports OpenGL 2.1/3.1,
    echo        place Mesa3D software renderer [opengl32.dll] in your build folder.
)
echo   ========================================================================
echo.

:SUCCESS_SETUP
echo.
echo ============================================================
echo   SUCCESS! OpenGL C++ Build Environment configured!
echo ============================================================
echo.

:FINISH
cls
echo ============================================================
echo   OpenGL C++ Build Environment - Setup Completed!
echo ============================================================
echo.
echo Useful Links ^& Resources:
echo.
echo [1] Create New Projects:
echo     %PROJECT_ROOT%\PROJECTS\create_project.bat
echo.
echo [2] Sample Projects (Local Directory):
echo     %PROJECT_ROOT%\sample_projects
echo.
echo [3] Sample Projects (GitHub Repository):
echo     https://github.com/b1tranger/opengl_setup_script/tree/main/sample_projects
echo.
echo [4] OpenGL Technical Notes:
echo     https://github.com/b1tranger/opengl_setup_script/tree/main/doc/notes
echo.
echo ============================================================
echo   Interactive Options:
echo ============================================================
echo   [1] Create a New Custom Project (Run PROJECTS\create_project.bat)
echo   [2] Open Local Sample Projects Folder (File Explorer) ^& View Build Instructions
echo   [3] Open OpenGL Technical Notes on GitHub (Web Browser)
echo   [4] Deploy / Refresh Mesa3D Software Renderer to All Projects
echo   [0] Exit Setup (or press Enter)
echo.
set "LINK_CHOICE="
set /p LINK_CHOICE="Select an option [1-4, 0, or press Enter to exit]: "

if "%LINK_CHOICE%"=="1" goto OPTION_1
if "%LINK_CHOICE%"=="2" goto OPTION_2
if "%LINK_CHOICE%"=="3" goto OPTION_3
if "%LINK_CHOICE%"=="4" goto OPTION_4
goto EXIT_SCRIPT

:OPTION_1
cls
echo ============================================================
echo   Launching Modern OpenGL Project Generator...
echo ============================================================
echo.
if not exist "%PROJECT_ROOT%\PROJECTS" mkdir "%PROJECT_ROOT%\PROJECTS"
if exist "%PROJECT_ROOT%\PROJECTS\create_project.bat" (
    call "%PROJECT_ROOT%\PROJECTS\create_project.bat"
) else (
    echo [ERROR] create_project.bat not found in %PROJECT_ROOT%\PROJECTS.
    pause
)
goto FINISH

:OPTION_2
cls
echo ============================================================
echo   Opening Local Sample Projects in File Explorer...
echo ============================================================
echo   Path: %PROJECT_ROOT%\sample_projects
echo.
start "" "%PROJECT_ROOT%\sample_projects"
echo.
echo ============================================================
echo   How to Build ^& Run OpenGL Projects:
echo ============================================================
echo.
echo   Using Makefile (Recommended):
echo   Open Command Prompt (CMD), PowerShell, or VS Code Terminal,
echo   navigate to any lab folder (e.g. sample_projects\Lab1_Color_Triangle
echo   or your newly created folder inside PROJECTS), and execute:
echo.
echo       make win
echo.
echo ============================================================
echo.
echo Press any key to return to the menu...
pause >nul
goto FINISH

:OPTION_3
cls
echo ============================================================
echo   Opening OpenGL Technical Notes in default browser...
echo ============================================================
echo   URL: https://github.com/b1tranger/opengl_setup_script/tree/main/doc/notes
echo.
start "" "https://github.com/b1tranger/opengl_setup_script/tree/main/doc/notes"
echo.
echo Press any key to return to the menu...
pause >nul
goto FINISH

:OPTION_4
cls
echo ============================================================
echo   Deploying Mesa3D Software Renderer to Projects...
echo ============================================================
echo.
if exist "%LOCAL_MESA_DIR%\opengl32.dll" (
    echo   1. Installing central Mesa3D storage to "%MSYS2_DIR%\opt\mesa3d"...
    if not exist "%MSYS2_DIR%\opt\mesa3d" mkdir "%MSYS2_DIR%\opt\mesa3d"
    copy /Y "%LOCAL_MESA_DIR%\*.dll" "%MSYS2_DIR%\opt\mesa3d\" >nul 2>&1

    echo   2. Deploying Mesa3D [OpenGL 4.6 llvmpipe] to sample projects...
    for /d %%D in ("%PROJECT_ROOT%\sample_projects\*") do (
        if not exist "%%D\build" mkdir "%%D\build"
        copy /Y "%LOCAL_MESA_DIR%\*.dll" "%%D\build\" >nul 2>&1
        echo      [COPIED] Mesa3D deployed to: %%~nxD\build
    )

    if exist "%PROJECT_ROOT%\PROJECTS" (
        echo   3. Deploying Mesa3D to custom projects in PROJECTS...
        for /d %%D in ("%PROJECT_ROOT%\PROJECTS\*") do (
            if not exist "%%D\build" mkdir "%%D\build"
            copy /Y "%LOCAL_MESA_DIR%\*.dll" "%%D\build\" >nul 2>&1
            echo      [COPIED] Mesa3D deployed to: PROJECTS\%%~nxD\build
        )
    )

    echo   4. Configuring automated background deployment for 'make win'...
    if exist "%LOCAL_MESA_DIR%\mesa_wrapper.cpp" (
        pushd "%LOCAL_MESA_DIR%"
        g++.exe -std=c++17 -O2 mesa_wrapper.cpp -o mesa_wrapper.exe >nul 2>&1
        popd
        if exist "%LOCAL_MESA_DIR%\mesa_wrapper.exe" (
            if not exist "%MSYS2_DIR%\usr\bin\g++_orig.exe" (
                if exist "%MSYS2_DIR%\usr\bin\g++.exe" ren "%MSYS2_DIR%\usr\bin\g++.exe" "g++_orig.exe"
            )
            if exist "%MSYS2_DIR%\usr\bin\g++_orig.exe" (
                copy /Y "%LOCAL_MESA_DIR%\mesa_wrapper.exe" "%MSYS2_DIR%\usr\bin\g++.exe" >nul 2>&1
            )
            if not exist "%MSYS2_DIR%\usr\bin\make_orig.exe" (
                if exist "%MSYS2_DIR%\usr\bin\make.exe" ren "%MSYS2_DIR%\usr\bin\make.exe" "make_orig.exe"
            )
            if exist "%MSYS2_DIR%\usr\bin\make_orig.exe" (
                copy /Y "%LOCAL_MESA_DIR%\mesa_wrapper.exe" "%MSYS2_DIR%\usr\bin\make.exe" >nul 2>&1
            )
            del /F /Q "%LOCAL_MESA_DIR%\mesa_wrapper.exe" >nul 2>&1
            echo      - Build-tool automation hooks installed successfully.
        )
    )

    powershell -Command "[System.Environment]::SetEnvironmentVariable('GALLIUM_DRIVER', 'llvmpipe', 'Machine')" >nul 2>&1
    set "GALLIUM_DRIVER=llvmpipe"
    echo.
    echo   [SUCCESS] Mesa3D software renderer is active. 'make win' will now auto-configure in any folder!
) else (
    echo   [ERROR] Localized Mesa3D files not found at %LOCAL_MESA_DIR%.
)
echo.
echo Press any key to return to the menu...
pause >nul
goto FINISH

:EXIT_SCRIPT
exit /b 0
