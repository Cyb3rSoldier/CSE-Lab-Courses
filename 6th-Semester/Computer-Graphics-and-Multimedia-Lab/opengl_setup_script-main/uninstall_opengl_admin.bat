@echo off
:: Self-elevating uninstaller script for OpenGL (MSYS2 & build artifacts) setup
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
echo   Uninstalling / Cleaning OpenGL Setup & Build Artifacts
echo ============================================================
echo.

set "MSYS2_DIR=C:\msys64"

echo Select Uninstallation / Cleanup Actions:
echo   [1] Remove MSYS2 paths from System PATH
echo   [2] Clean compiled output binaries (main.exe) across sample projects
echo   [3] Uninstall MSYS2 packages (base-devel, gcc) & clear pacman cache
echo   [4] Full Uninstallation (Remove C:\msys64 directory, clean PATH, & delete build binaries)
echo.

set /p CHOICE="Select option [1-4]: "

if "%CHOICE%"=="1" goto CLEAN_PATH
if "%CHOICE%"=="2" goto CLEAN_BINARIES
if "%CHOICE%"=="3" goto UNINSTALL_PACKAGES
if "%CHOICE%"=="4" goto FULL_UNINSTALL

echo Invalid selection. Defaulting to Full Uninstallation...
goto FULL_UNINSTALL

:CLEAN_PATH
echo.
echo Removing MSYS2 entries from System Environment PATH...
powershell -Command ^
    "$sysPath = [System.Environment]::GetEnvironmentVariable('Path', 'Machine'); " ^
    "$usrBin = 'C:\msys64\usr\bin'; $mingwBin = 'C:\msys64\mingw64\bin'; " ^
    "$paths = $sysPath -split ';' | Where-Object { $_ -ne $usrBin -and $_ -ne $mingwBin -and $_ -ne '' }; " ^
    "$newPath = $paths -join ';'; " ^
    "[System.Environment]::SetEnvironmentVariable('Path', $newPath, 'Machine'); " ^
    "Write-Host '[SUCCESS] Removed MSYS2 from System PATH.'"
if "%CHOICE%"=="1" goto END
exit /b 0

:CLEAN_BINARIES
echo.
echo Cleaning generated binaries main.exe inside build directories...
for /r "%PROJECT_ROOT%" %%f in (main.exe) do (
    if exist "%%f" (
        echo   - Removing: %%f
        del /F /Q "%%f"
    )
)
if "%CHOICE%"=="2" goto END
exit /b 0

:UNINSTALL_PACKAGES
echo.
if exist "%MSYS2_DIR%\usr\bin\g++_orig.exe" (
    echo Restoring original g++.exe compiler binary...
    copy /Y "%MSYS2_DIR%\usr\bin\g++_orig.exe" "%MSYS2_DIR%\usr\bin\g++.exe" >nul 2>&1
    del /F /Q "%MSYS2_DIR%\usr\bin\g++_orig.exe" >nul 2>&1
)
if exist "%MSYS2_DIR%\usr\bin\make_orig.exe" (
    echo Restoring original make.exe build tool binary...
    copy /Y "%MSYS2_DIR%\usr\bin\make_orig.exe" "%MSYS2_DIR%\usr\bin\make.exe" >nul 2>&1
    del /F /Q "%MSYS2_DIR%\usr\bin\make_orig.exe" >nul 2>&1
)
if exist "%MSYS2_DIR%\opt\mesa3d" (
    echo Removing central Mesa3D directory: %MSYS2_DIR%\opt\mesa3d ...
    rmdir /S /Q "%MSYS2_DIR%\opt\mesa3d" >nul 2>&1
)
powershell -Command "[System.Environment]::SetEnvironmentVariable('GALLIUM_DRIVER', $null, 'Machine')" >nul 2>&1

if exist "%MSYS2_DIR%\usr\bin\bash.exe" (
    echo Uninstalling pacman packages base-devel and gcc...
    if exist "%MSYS2_DIR%\var\lib\pacman\db.lck" del /F /Q "%MSYS2_DIR%\var\lib\pacman\db.lck" >nul 2>&1
    "%MSYS2_DIR%\usr\bin\bash.exe" -lc "export MSYSTEM=MSYS && pacman -Rns --noconfirm base-devel gcc 2>/dev/null"
    echo Cleaning pacman cache...
    "%MSYS2_DIR%\usr\bin\bash.exe" -lc "export MSYSTEM=MSYS && pacman -Scc --noconfirm 2>/dev/null"
    echo [SUCCESS] Pacman packages uninstalled.
) else (
    echo [INFO] MSYS2 installation not found at %MSYS2_DIR%. Skipping package uninstall.
)
if "%CHOICE%"=="3" goto END
exit /b 0

:FULL_UNINSTALL
echo.
echo Performing Full Uninstallation...

call :CLEAN_PATH
call :CLEAN_BINARIES

if exist "%MSYS2_DIR%" (
    echo Terminating any active MSYS2 background processes...
    taskkill /F /IM gpg-agent.exe /IM pacman.exe /IM bash.exe >nul 2>&1
    echo Removing MSYS2 directory: "%MSYS2_DIR%" ...
    powershell -Command "Remove-Item -Recurse -Force '%MSYS2_DIR%' -ErrorAction SilentlyContinue"
    if exist "%MSYS2_DIR%" rmdir /S /Q "%MSYS2_DIR%" >nul 2>&1
    echo [SUCCESS] Removed %MSYS2_DIR% completely.
) else (
    echo [INFO] MSYS2 directory "%MSYS2_DIR%" does not exist.
)
goto END

:END
echo.
echo ============================================================
echo   SUCCESS! Uninstallation operation completed.
echo ============================================================
echo.
pause
exit /b 0
