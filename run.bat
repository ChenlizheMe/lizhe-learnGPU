@echo off
setlocal

echo ========================================
echo  CUDA Learning Project Build Script
echo ========================================
echo.

REM Check if build directory exists
if not exist "build" (
    echo Creating build directory...
    mkdir build
)

REM Enter build directory
cd build

echo.
echo [1/2] Configuring CMake...
echo ========================================
cmake .. -G "Visual Studio 17 2022" -A x64
if %ERRORLEVEL% NEQ 0 (
    echo.
    echo ERROR: CMake configuration failed!
    cd ..
    pause
    exit /b 1
)

echo.
echo [2/2] Building project...
echo ========================================
cmake --build . --config Release
if %ERRORLEVEL% NEQ 0 (
    echo.
    echo ERROR: Build failed!
    cd ..
    pause
    exit /b 1
)

echo.
echo ========================================
echo  Build completed successfully!
echo ========================================
echo.
echo Executables are located in:
echo   build\bin\lecture0\Release\
echo   build\bin\lecture1\Release\
echo   ... etc
echo.

cd ..
pause
