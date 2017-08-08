@echo off

set CMAKE_PATH=%~dp0Tools\CMake\bin
set MAKE_PATH=%~dp0Tools\Make
set PATH=%PATH%;%CMAKE_PATH%;%MAKE_PATH%
IF EXIST Builds GOTO start_build
mkdir Builds
cd Builds
cmake .. -G "MinGW Makefiles"
cmake .. -G "MinGW Makefiles"
call mingw32-make all -j4
GOTO :Test_output

:start_build
IF EXIST .\Builds\bin\bin.exe (
	del .\Builds\bin\bin.exe
	)
cd Builds
cmake .. -G "MinGW Makefiles"
call mingw32-make all -j4

:Test_output
IF EXIST .\bin\bin.exe (
	echo ****************************
	echo * Build Successfull *
) ELSE (
		echo ****************************
		echo *    Build Faild    *)
echo ****************************
cd ..
:END
cd %PROJ_PATH%