@echo off
rem: Note %~dp0 get path of this batch file
rem: Need to change drive if My Documents is on a drive other than C:

set driverLetter=%~dp0
set driverLetter=%driverLetter:~0,2%
%driverLetter%
cd %~dp0
rem: the two line below are needed to fix path issues with incorrect slashes before the bin file name
set str=%4
set str=%str:/=\%



:FLASH
echo f >stm32.jlink
echo loadfile %str%,, >>stm32.jlink
echo r >>stm32.jlink
echo g >>stm32.jlink
echo qc >>stm32.jlink
GOTO UPLOAD

:NOR
echo f >stm32.jlink
echo loadfile %str%,%6 >>stm32.jlink
echo r >>stm32.jlink
echo g >>stm32.jlink
echo qc >>stm32.jlink
GOTO UPLOAD

:OTHER
rem and other here

:UPLOAD
rem "%ProgramFiles%\SEGGER\JLink_V614b\JLink.exe"  -device STM32F103ZE -If SWD -Speed 4000 -CommanderScript  stm32.jlink
jlink502\JLink.exe                                    -device %5 -If SWD -Speed auto -CommanderScript  stm32.jlink

:EXIT