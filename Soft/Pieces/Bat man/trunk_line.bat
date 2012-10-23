@echo off
cls

set test_ip=74.125.87.147
set wifi=192.168.1.1

call :getip
set bilan=%ans%
rem если жпрс не подключен
if %bilan%==notfound (
	rasdial Beeline
	call :getip
	set bilan=%ans%
	if %bilan%==notfound (
		rem если жпрс нет вобще, то тлку от скрипта чуть
		echo NO GPRS!
		pause
		exit
	)
)

route add %test_ip% mask 255.255.255.255 %wifi% metric 10 

:Ethernet
	echo connection up 
	route delete 0.0.0.0 
	route add 0.0.0.0 mask 0.0.0.0 %wifi% metric 20 
	goto start_proverka 

rem когда всё хорошо - просто пингуем гугл. как только пропадает в подряд три пакета - переключаемся на жпрс
:start_proverka
	echo connection OK
	set counter=0
	:proverka 
		ping -n 1 %test_ip%>nul 
		if errorlevel 1 (
			set /a counter=counter+1
			echo packet lost!
		) else (
			set counter=0
		)
		if %counter%==3 goto beeline
		sleep -m 333
		goto proverka 

:beeline 
	echo connection lost
	route delete 0.0.0.0
	route add 0.0.0.0 mask 0.0.0.0 %bilan% metric 20 
	goto start_proverka2 

rem проверим, может обрыв линии вифи. если так, то будем ждать её восстановления (о котором нам скажет появление новых маршрутов в таблице)
rem ежели дело не с обрывом вифи, а с обрывом адсл - то пингуем гугл через вифи. как только пинги пошли - связь восстановилась
:start_proverka2
	echo gprs up
	set routs=route print|find /C "%wifi%"
	if %routs%==0 goto start_proverka3
	echo adsl down
	:proverka2 
		ping -n 1 %test_ip%>nul
		if errorlevel 0 (
			echo adsl up
			goto Ethernet
		)	
		goto proverka2

:start_proverka3
	echo wifi down
	:proverka3
		set routs=route print|find /C "%wifi%"
		sleep 1
		if %routs%==0 goto proverka3
	echo wifi up
	goto Ethernet

:getip
	set ans=notfound
	FOR /F "delims=: tokens=2 usebackq" %%i IN (`ipconfig`) DO (
		FOR /F "tokens=1,2,3,4 usebackq delims=. " %%j IN ('%%i') DO	(
			if %%j== 172 (
				set ans=%%j.%%k.%%l.%%m
			)
		)
	)
	echo dinamic ip: %ans%
exit /b