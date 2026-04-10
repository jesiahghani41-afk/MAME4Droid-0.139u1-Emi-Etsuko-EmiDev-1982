@echo off

REM Set up the Visual Studio build environment (adjust path as needed)
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

REM Navigate to the MAME source directory (assuming this script is in the root of the MAME source)
cd /d "%~dp0"

REM Clean previous build (optional, but good practice)
nmake clean

REM Build MAME with the Emi Etsuko driver
nmake -j%NUMBER_OF_PROCESSORS% SOURCES=src/mame/drivers/emietsko.cpp

REM You might need to copy the compiled ROM to the MAME ROMs directory after a successful build.
REM For MAME4Droid, this usually means placing the emietsko.zip in the ROMs folder.

pause
