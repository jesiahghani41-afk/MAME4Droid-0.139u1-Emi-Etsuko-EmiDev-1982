@echo off

REM This script builds the Emi Etsuko MAME driver using NMAKE from Visual Studio.
REM It is designed to be run from the Visual Studio Code terminal.

REM --- Configuration ---
REM Set the path to your Visual Studio vcvarsall.bat. Adjust this if your VS installation is different.
REM Example paths:
REM Visual Studio 2022: "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat"
REM Visual Studio 2019: "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat"
SET "VS_VCVARSALL_PATH=C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat"

REM --- Script Logic ---

REM Navigate to the script's directory
cd /d "%~dp0"

REM Check if vcvarsall.bat exists
IF NOT EXIST "%VS_VCVARSALL_PATH%" (
    echo ERROR: vcvarsall.bat not found at "%VS_VCVARSALL_PATH%"
    echo Please update the VS_VCVARSALL_PATH variable in this script to match your Visual Studio installation.
    goto :eof
)

REM Call vcvarsall.bat to set up the Visual Studio build environment
call "%VS_VCVARSALL_PATH%" x64
IF %ERRORLEVEL% NEQ 0 (
    echo ERROR: Failed to set up Visual Studio build environment.
    goto :eof
)

echo Visual Studio build environment set up successfully.

REM Clean previous build (optional, but good practice)
echo Cleaning previous build...
nmake clean
IF %ERRORLEVEL% NEQ 0 (
    echo WARNING: NMAKE clean failed or encountered issues. Continuing with build.
)

REM Build MAME with the Emi Etsuko driver
echo Building Emi Etsuko driver...
nmake -j%NUMBER_OF_PROCESSORS% SOURCES=src/mame/drivers/emietsko.cpp

IF %ERRORLEVEL% NEQ 0 (
    echo ERROR: MAME build failed for Emi Etsuko driver.
    echo Please check the output above for details.
) ELSE (
    echo SUCCESS: Emi Etsuko driver built successfully.
    echo You might need to copy the compiled ROM to the MAME ROMs directory.
    echo For MAME4Droid, this usually means placing the emietsko.zip in the ROMs folder.
)

pause
