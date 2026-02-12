@echo off
echo Building MAI_verb for Windows...

REM Setup Visual Studio environment
call "C:\Program Files\Microsoft Visual Studio\18\Enterprise\Common7\Tools\VsDevCmd.bat"

REM Clean and create build directory
if exist build rmdir /s /q build
mkdir build
cd build

REM Configure with CMake
echo.
echo Configuring with CMake...
cmake .. -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=Release
if errorlevel 1 (
    echo Configuration failed!
    exit /b 1
)

REM Build
echo.
echo Building Release...
cmake --build . --config Release
if errorlevel 1 (
    echo Build failed!
    exit /b 1
)

echo.
echo Build completed successfully!
cd ..
