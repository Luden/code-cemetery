@echo off
set wifi=192.168.1.1
rem set xx=route print|find /C "%wifi%"
 
FOR /F "delims=: tokens=1 usebackq" %%i IN (`route print`) DO (
FOR /F "tokens=3 usebackq" %%j IN ('%%i') DO (
 	set xx=%%j
	
	if %%j==%wifi% goto asd	
 )
 )
:asd
if %xx%==%wifi% (
set xx=1
) else (
set xx=0
)

echo %xx%
exit /b

pause